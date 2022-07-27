/* **********************************************************
 * Copyright (c) 2022 Google, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Google, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* The drpttracer extension's tests.
 * TODO i#5505: This version only tests whether the function of the tracer can output
 * data. The tests of whether the output data is correct will come on the next version.
 */

#include <string.h>
#include "dr_api.h"
#include "client_tools.h"
#include "drmgr.h"
#include "drpttracer.h"

typedef struct _per_thread_t {
    /* Initialize the tracer_handle before each syscall, and free it after each syscall.
     */
    void *current_trace_handle;
} per_thread_t;

static int tls_idx;

static void
event_exit(void);

static void
event_thread_init(void *drcontext);

static void
event_thread_exit(void *drcontext);

static bool
event_filter_syscall(void *drcontext, int sysnum);

static bool
event_pre_syscall(void *drcontext, int sysnum);

static void
event_post_syscall(void *drcontext, int sysnum);

static void
end_tracing_and_dump_trace(void *drcontext);

DR_EXPORT void
dr_init(client_id_t id)
{
    bool ok;
    ok = drmgr_init();
    CHECK(ok, "drmgr_init failed");

    ok = drpttracer_init();
    CHECK(ok, "drpttracer_init failed");

    dr_register_exit_event(event_exit);

    ok = drmgr_register_thread_init_event(event_thread_init) &&
        drmgr_register_thread_exit_event(event_thread_exit) &&
        drmgr_register_pre_syscall_event(event_pre_syscall) &&
        drmgr_register_post_syscall_event(event_post_syscall);
    CHECK(ok, "drmgr_register_*_event failed");

    dr_register_filter_syscall_event(event_filter_syscall);

    tls_idx = drmgr_register_tls_field();
    CHECK(tls_idx > -1, "unable to reserve TLS field");
}

static void
event_exit(void)
{
    drpttracer_exit();
    dr_unregister_filter_syscall_event(event_filter_syscall);

    bool ok = drmgr_unregister_thread_init_event(event_thread_init) &&
        drmgr_unregister_thread_exit_event(event_thread_exit) &&
        drmgr_unregister_pre_syscall_event(event_pre_syscall) &&
        drmgr_unregister_post_syscall_event(event_post_syscall) &&
        drmgr_unregister_tls_field(tls_idx);
    CHECK(ok, "drmgr_unregister_*_event failed");

    drmgr_exit();
    dr_fprintf(STDERR, "all done\n");
}

static void
event_thread_init(void *drcontext)
{
    per_thread_t *pt = (per_thread_t *)dr_thread_alloc(drcontext, sizeof(*pt));
    memset(pt, 0, sizeof(*pt));
    drmgr_set_tls_field(drcontext, tls_idx, (void *)pt);
}

static void
event_thread_exit(void *drcontext)
{
    per_thread_t *pt = (per_thread_t *)drmgr_get_tls_field(drcontext, tls_idx);
    /* If the thread's last syscall doesn't trigger post_syscall event, we need to end the
     * tracing manually. (e.g. The 'exit_group' syscall.)
     */
    if (pt->current_trace_handle != NULL) {
        end_tracing_and_dump_trace(drcontext);
        pt->current_trace_handle = NULL;
    }
    dr_thread_free(drcontext, pt, sizeof(*pt));
}

static bool
event_filter_syscall(void *drcontext, int sysnum)
{
    return true;
}

static bool
event_pre_syscall(void *drcontext, int sysnum)
{
    per_thread_t *pt = (per_thread_t *)drmgr_get_tls_field(drcontext, tls_idx);
    /* If last syscall doesn't trigger post_syscall event, we need to stop its tracing
     * here.
     * XXX: In this case, We don't stop tracing when the application's system call
     * returns. So we might trace some system calls called by Dynamorio's internal code.
     */
    if (pt->current_trace_handle != NULL) {
        end_tracing_and_dump_trace(drcontext);
        pt->current_trace_handle = NULL;
    }

    /* Start trace before syscall. */
    bool ok = drpttracer_start_tracing(drcontext, DRPTTRACER_TRACING_ONLY_KERNEL, 8, 8,
                                       &pt->current_trace_handle) == DRPTTRACER_SUCCESS;
    CHECK(ok, "drpttracer_start_tracing failed");
    return true;
}

static void
event_post_syscall(void *drcontext, int sysnum)
{
    per_thread_t *pt = (per_thread_t *)drmgr_get_tls_field(drcontext, tls_idx);
    CHECK(pt->current_trace_handle != NULL, "current_trace_handle is NULL");

    /* End trace after syscall. */
    end_tracing_and_dump_trace(drcontext);
    pt->current_trace_handle = NULL;
}

static void
end_tracing_and_dump_trace(void *drcontext)
{
    per_thread_t *pt = (per_thread_t *)drmgr_get_tls_field(drcontext, tls_idx);
    CHECK(pt->current_trace_handle != NULL, "current_trace_handle is NULL");
    drpttracer_output_t *output;
    bool ok = drpttracer_end_tracing(drcontext, pt->current_trace_handle, &output) ==
        DRPTTRACER_SUCCESS;
    CHECK(ok, "drpttracer_end_tracing failed");

    CHECK(output->pt_buf != NULL, "PT trace data is NULL");
    CHECK(output->pt_buf_size != 0, "PT trace data size is 0");
    CHECK(output->sideband_buf == NULL, "PT's sideband data is not NULL");
    CHECK(output->sideband_buf_size == 0, "PT's sideband data size is not 0");

    drpttracer_destory_output(drcontext, output);
}
