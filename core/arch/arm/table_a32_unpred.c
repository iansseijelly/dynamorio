/* **********************************************************
 * Copyright (c) 2014-2015 Google, Inc.  All rights reserved.
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

#include "../globals.h" /* need this to include decode.h (uint, etc.) */
#include "arch.h"    /* need this to include decode.h (byte, etc. */
#include "decode.h"
#include "decode_private.h"
#include "table_private.h"

/* Indexed by bits 27:23,21:20.
 * The D bit (0x04) has been removed.  We are including the U bit.  Is
 * there some other order we could do to group the related instrs better
 * while still minimizing the number of table lookup steps and keeping
 * dense tables?
 */
const instr_info_t A32_unpred_opc7[] = {
    /* {op/type, op encoding, name, dst1, dst2, src1, src2, src3, flags, eflags, code} */
    /* 00 */
    {INVALID,    0xf0000000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0100000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0900000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0a00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf0b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 10 */
    {EXT_BITS16, 0xf1000000, "(ext bits16 8)", xx, xx, xx, xx, xx, no, x, 8},
    {INVALID,    0xf1100000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1900000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1a00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf1b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 20 */
    {EXT_SIMD6,  0xf2000000, "(ext simd6  0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_SIMD6,  0xf2100000, "(ext simd6  1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_SIMD6,  0xf2200000, "(ext simd6  2)", xx, xx, xx, xx, xx, no, x, 2},
    {EXT_SIMD6,  0xf2300000, "(ext simd6  3)", xx, xx, xx, xx, xx, no, x, 3},
    {EXT_BIT4,   0xf2800000, "(ext bit4  13)", xx, xx, xx, xx, xx, no, x, 13},
    {EXT_BIT4,   0xf2900000, "(ext bit4  14)", xx, xx, xx, xx, xx, no, x, 14},
    {EXT_BIT4,   0xf2a00000, "(ext bit4  15)", xx, xx, xx, xx, xx, no, x, 15},
    {EXT_BIT4,   0xf2b00000, "(ext bit4  16)", xx, xx, xx, xx, xx, no, x, 16},
    /* 30 */
    {EXT_SIMD6,  0xf3000000, "(ext simd6  6)", xx, xx, xx, xx, xx, no, x, 6},
    {EXT_SIMD6,  0xf3100000, "(ext simd6  7)", xx, xx, xx, xx, xx, no, x, 7},
    {EXT_SIMD6,  0xf3200000, "(ext simd6  8)", xx, xx, xx, xx, xx, no, x, 8},
    {EXT_SIMD6,  0xf3300000, "(ext simd6  9)", xx, xx, xx, xx, xx, no, x, 9},
    {EXT_BIT4,   0xf3800000, "(ext bit4  17)", xx, xx, xx, xx, xx, no, x, 17},
    {EXT_BIT4,   0xf3900000, "(ext bit4  18)", xx, xx, xx, xx, xx, no, x, 18},
    {EXT_BIT4,   0xf3a00000, "(ext bit4  19)", xx, xx, xx, xx, xx, no, x, 19},
    {EXT_BIT4,   0xf3b00000, "(ext bit4  20)", xx, xx, xx, xx, xx, no, x, 20},
    /* 40 */
    {EXT_VLDA,   0xf4000000, "(ext vldA  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {OP_pli,     0xf450f000, "pli",            xx, xx, MN12z, xx, xx, no, x, top7[0x35]},/*PUW=000*/
    {EXT_VLDA,   0xf4200000, "(ext vldA  1)",  xx, xx, xx, xx, xx, no, x, 1},
    {INVALID,    0xf4300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_VLDB,   0xf4800000, "(ext vldB  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {OP_pli,     0xf4d0f000, "pli",            xx, xx, MP12z, xx, xx, no, x, top7[0x21]},/*PUW=010*/
    {EXT_VLDB,   0xf4a00000, "(ext vldB  1)",  xx, xx, xx, xx, xx, no, x, 1},
    {INVALID,    0xf4b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 50 */
    {INVALID,    0xf5000000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_BIT22,  0xf5100000, "(ext bit22  0)", xx, xx, xx, xx, xx, no, x, 0},
    {INVALID,    0xf5200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_FPB,    0xf5300000, "(ext fpb 14)",   xx, xx, xx, xx, xx, no, x, 14},
    {INVALID,    0xf5800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_BIT22,  0xf5900000, "(ext bit22  1)", xx, xx, xx, xx, xx, no, x, 1},
    {INVALID,    0xf5a00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf5b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 60 */
    {INVALID,    0xf6000000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_pli,     0xf650f000, "pli",            xx, xx, MNSz, xx, xx, no, x, END_LIST},/*PUW=000*/
    {INVALID,    0xf6200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf6300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf6800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_pli,     0xf6d0f000, "pli",            xx, xx, MPSz, xx, xx, no, x, top7[0x31]},/*PUW=010*/
    {INVALID,    0xf6a00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf6b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 70 */
    {INVALID,    0xf7000000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_BIT22,  0xf7100000, "(ext bit22  2)", xx, xx, xx, xx, xx, no, x, 2},
    {INVALID,    0xf7200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf7300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf7800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {EXT_BIT22,  0xf7900000, "(ext bit22  3)", xx, xx, xx, xx, xx, no, x, 3},
    {INVALID,    0xf7a00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xf7b00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 80 */
    {OP_srsda,   0xf84d0500, "srsda",       Mq, xx, i5, LRw, SPSR, no, x, top7[0x42]},/*PUW=000*/
    {OP_rfeda,   0xf8100a00, "rfeda",       CPSR, xx, Mq, xx, xx, no, x, END_LIST},/*PUW=000*/
    {OP_srsda,   0xf86d0500, "srsda",       Mq, SPw, i5, SPw, LRw, xop, x, exop[0x6]},/*PUW=001*/
    {OP_rfeda,   0xf8300a00, "rfeda",       RAw, CPSR, Mq, RAw, xx, no, x, top7[0x41]},/*PUW=001*/
    {OP_srsdb,   0xf8cd0500, "srsdb",       Mq, xx, i5, LRw, SPSR, no, x, top7[0x46]},/*PUW=010*/
    {OP_rfedb,   0xf8900a00, "rfedb",       CPSR, xx, Mq, xx, xx, no, x, END_LIST},/*PUW=010*/
    {OP_srsdb,   0xf8ed0500, "srsdb",       Mq, SPw, i5, SPw, LRw, xop, x, exop[0x6]},/*PUW=011*/
    {OP_rfedb,   0xf8b00a00, "rfedb",       RAw, CPSR, Mq, RAw, xx, no, x, top7[0x45]},/*PUW=011*/
    /* 90 */
    {OP_srs,     0xf94d0500, "srs",         Mq, xx, i5, LRw, SPSR, no, x, top7[0x4a]},/*PUW=100*/
    {OP_rfe,     0xf9100a00, "rfe",         CPSR, xx, Mq, xx, xx, no, x, top7[0x4b]},/*PUW=100*/
    {OP_srs,     0xf96d0500, "srs",         Mq, SPw, i5, SPw, LRw, xop, x, exop[0x6]},/*PUW=101*/
    {OP_rfe,     0xf9300a00, "rfe",         RAw, CPSR, Mq, RAw, xx, no, x, END_LIST},/*PUW=101*/
    {OP_srsib,   0xf9cd0500, "srsib",       Mq, xx, i5, LRw, SPSR, no, x, top7[0x4e]},/*PUW=110*/
    {OP_rfeib,   0xf9900a00, "rfeib",       CPSR, xx, Mq, xx, xx, no, x, top7[0x4f]},/*PUW=110*/
    {OP_srsib,   0xf9ed0500, "srsib",       Mq, SPw, i5, SPw, LRw, xop, x, exop[0x6]},/*PUW=111*/
    {OP_rfeib,   0xf9b00a00, "rfeib",       RAw, CPSR, Mq, RAw, xx, no, x, END_LIST},/*PUW=111*/
    /* a0 */
    {OP_blx,     0xfa000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, END_LIST},
    {OP_blx,     0xfa100000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfa200000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfa300000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfa800000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfa900000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfaa00000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfab00000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    /* b0 */
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    {OP_blx,     0xfb000000, "blx",         LRw, xx, j25x0_24, xx, xx, no, x, DUP_ENTRY},
    /* c0 */
    {EXT_BITS20, 0xfc000000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfc100000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfc200000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfc300000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfc800000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfc900000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfca00000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_BITS20, 0xfcb00000, "(ext bits20 0)", xx, xx, xx, xx, xx, no, x, 0},
    /* d0 */
    {EXT_BITS20, 0xfd000000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfd100000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfd200000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfd300000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfd800000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfd900000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfda00000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_BITS20, 0xfdb00000, "(ext bits20 1)", xx, xx, xx, xx, xx, no, x, 1},
    /* e0 */
    {EXT_FP,     0xfe000000, "(ext fp 46)",    xx, xx, xx, xx, xx, no, x, 46},
    {EXT_FP,     0xfe100000, "(ext fp 47)",    xx, xx, xx, xx, xx, no, x, 47},
    {EXT_FP,     0xfe200000, "(ext fp 48)",    xx, xx, xx, xx, xx, no, x, 48},
    {EXT_FP,     0xfe300000, "(ext fp 49)",    xx, xx, xx, xx, xx, no, x, 49},
    {EXT_FP,     0xfe800000, "(ext fp 50)",    xx, xx, xx, xx, xx, no, x, 50},
    {EXT_FP,     0xfe900000, "(ext fp 51)",    xx, xx, xx, xx, xx, no, x, 51},
    {EXT_FP,     0xfea00000, "(ext fp 52)",    xx, xx, xx, xx, xx, no, x, 52},
    {EXT_FP,     0xfeb00000, "(ext fp 53)",    xx, xx, xx, xx, xx, no, x, 53},
    /* f0 */
    {INVALID,    0xff000000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xff100000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xff200000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xff300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xff800000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xff900000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xffa00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,    0xffb00000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
};

/* Indexed by bits 23:20 */
const instr_info_t A32_ext_bits20[][16] = {
  { /* 0 */
    {INVALID,    0xfc000000, "(bad)",   xx, xx, xx, xx, xx, no, x, NA},/*PUW=000*/
    {INVALID,    0xfc100000, "(bad)",   xx, xx, xx, xx, xx, no, x, NA},/*PUW=000*/
    {OP_stc2,    0xfc200000, "stc2",    Mw, RAw, i4_8, CRBw, n8x4, xop_wb, x, END_LIST},/*PUW=001*/
    {OP_ldc2,    0xfc300000, "ldc2",    CRBw, RAw, Mw, i4_8, n8x4, xop_wb, x, END_LIST},/*PUW=001*/
    {OP_mcrr2,   0xfc400000, "mcrr2",   CRDw, RAw, RBw, i4_8, i4_7, srcX4, x, END_LIST},
    {OP_mrrc2,   0xfc500000, "mrrc2",   RBw, RAw, i4_8, i4_7, CRDw, no, x, END_LIST},
    {OP_stc2l,   0xfc600000, "stc2l",   Mw, RAw, i4_8, CRBw, n8x4, xop_wb, x, END_LIST},/*PUW=001*/
    {OP_ldc2l,   0xfc700000, "ldc2l",   CRBw, RAw, Mw, i4_8, n8x4, xop_wb, x, END_LIST},/*PUW=001*/
    {OP_stc2,    0xfc800000, "stc2",    Mw, xx, i4_8, CRBw, i8, no, x, tb20[0][0x02]},/*PUW=010*/
    {OP_ldc2,    0xfc900000, "ldc2",    CRBw, xx, Mw, i4_8, i8, no, x, tb20[0][0x03]},/*PUW=010*/
    {OP_stc2,    0xfca00000, "stc2",    Mw, RAw, i4_8, CRBw, i8x4, xop_wb, x, tb20[0][0x08]},/*PUW=011*/
    {OP_ldc2,    0xfcb00000, "ldc2",    CRBw, RAw, Mw, i4_8, i8x4, xop_wb, x, tb20[0][0x09]},/*PUW=011*/
    {OP_stc2l,   0xfcc00000, "stc2l",   Mw, xx, i4_8, CRBw, i8, no, x, tb20[0][0x06]},/*PUW=010*/
    {OP_ldc2l,   0xfcd00000, "ldc2l",   CRBw, xx, Mw, i4_8, i8, no, x, tb20[0][0x07]},/*PUW=010*/
    {OP_stc2l,   0xfce00000, "stc2l",   Mw, RAw, i4_8, CRBw, i8x4, xop_wb, x, tb20[0][0x0c]},/*PUW=011*/
    {OP_ldc2l,   0xfcf00000, "ldc2l",   CRBw, RAw, Mw, i4_8, i8x4, xop_wb, x, tb20[0][0x0d]},/*PUW=011*/
  }, { /* 1 */
    {OP_stc2,    0xfd000000, "stc2",    MN8Xw, xx, i4_8, CRBw, n8x4, no, x, tb20[1][0x0a]},/*PUW=100*/
    {OP_ldc2,    0xfd100000, "ldc2",    CRBw, xx, MN8Xw, i4_8, i8x4, no, x, tb20[1][0x0b]},/*PUW=100*/
    {OP_stc2,    0xfd200000, "stc2",    MN8Xw, RAw, i4_8, CRBw, n8x4, xop_wb, x, tb20[0][0x0a]},/*PUW=101*/
    {OP_ldc2,    0xfd300000, "ldc2",    CRBw, RAw, MN8Xw, i4_8, n8x4, xop_wb, x, tb20[0][0x0b]},/*PUW=101*/
    {OP_stc2l,   0xfd400000, "stc2l",   MN8Xw, xx, i4_8, CRBw, n8x4, no, x, tb20[1][0x0e]},/*PUW=100*/
    {OP_ldc2l,   0xfd500000, "ldc2l",   CRBw, xx, MN8Xw, i4_8, i8x4, no, x, tb20[1][0x0f]},/*PUW=100*/
    {OP_stc2l,   0xfd600000, "stc2l",   MN8Xw, RAw, i4_8, CRBw, n8x4, xop_wb, x, tb20[0][0x0e]},/*PUW=101*/
    {OP_ldc2l,   0xfd700000, "ldc2l",   CRBw, RAw, MN8Xw, i4_8, n8x4, xop_wb, x, tb20[0][0x0f]},/*PUW=101*/
    {OP_stc2,    0xfd800000, "stc2",    MP8Xw, xx, i4_8, CRBw, i8x4, no, x, tb20[1][0x00]},/*PUW=110*/
    {OP_ldc2,    0xfd900000, "ldc2",    CRBw, xx, MP8Xw, i4_8, i8x4, no, x, tb20[1][0x01]},/*PUW=110*/
    {OP_stc2,    0xfda00000, "stc2",    MP8Xw, RAw, i4_8, CRBw, i8x4, xop_wb, x, tb20[1][0x02]},/*PUW=111*/
    {OP_ldc2,    0xfdb00000, "ldc2",    CRBw, RAw, MP8Xw, i4_8, i8x4, xop_wb, x, tb20[1][0x03]},/*PUW=111*/
    {OP_stc2l,   0xfdc00000, "stc2l",   MP8Xw, xx, i4_8, CRBw, i8x4, no, x, tb20[1][0x04]},/*PUW=110*/
    {OP_ldc2l,   0xfdd00000, "ldc2l",   CRBw, xx, MP8Xw, i4_8, i8x4, no, x, tb20[1][0x05]},/*PUW=110*/
    {OP_stc2l,   0xfde00000, "stc2l",   MP8Xw, RAw, i4_8, CRBw, i8x4, xop_wb, x, tb20[1][0x06]},/*PUW=111*/
    {OP_ldc2l,   0xfdf00000, "ldc2l",   CRBw, RAw, MP8Xw, i4_8, i8x4, xop_wb, x, tb20[1][0x07]},/*PUW=111*/
  },
};

/* Indexed by whether imm4 in 20:16 is zero or not */
const instr_info_t A32_ext_imm2016[][2] = {
  { /* 0 */
    {OP_vmovl_s32,      0xf2a00a10, "vmovl.s32",      VBdq, xx, VCq, xx, xx, no, x, END_LIST},
    {OP_vshll_s32,      0xf2a00a10, "vshll.s32",      VBdq, xx, VCq, i5_16, xx, no, x, END_LIST},/*20:16 cannot be 0*/
  }, { /* 1 */
    {OP_vmovl_u32,      0xf3a00a10, "vmovl.u32",      VBdq, xx, VCq, xx, xx, no, x, END_LIST},
    {OP_vshll_u32,      0xf3a00a10, "vshll.u32",      VBdq, xx, VCq, i5_16, xx, no, x, END_LIST},/*20:16 cannot be 0*/
  },
};

/* Indexed by whether imm4 in 18:16 is zero or not */
const instr_info_t A32_ext_imm1816[][2] = {
  { /* 0 */
    {OP_vmovl_s8,       0xf2880a10, "vmovl.s8",       VBdq, xx, VCq, xx, xx, no, x, END_LIST},
    {OP_vshll_s8,       0xf2880a10, "vshll.s8",       VBdq, xx, VCq, i3_16, xx, no, x, END_LIST},/*18:16 cannot be 0*/
  }, { /* 1 */
    {OP_vmovl_u8,       0xf3880a10, "vmovl.u8",       VBdq, xx, VCq, xx, xx, no, x, END_LIST},
    {OP_vshll_u8,       0xf3880a10, "vshll.u8",       VBdq, xx, VCq, i3_16, xx, no, x, END_LIST},/*18:16 cannot be 0*/
  },
};

/* Indexed by bit 6 */
const instr_info_t A32_ext_bit6[][2] = {
  { /* 0 */
    {OP_vext,           0xf2b00000, "vext.8",         VBq, xx, VAq, VCq, i4_8, no, x, tb6[0][0x01]},/*XXX: reads from part of srcs, but complex which part*/
    {OP_vext,           0xf2b00040, "vext.8",         VBdq, xx, VAdq, VCdq, i4_8, no, x, END_LIST},/*XXX: reads from part of srcs, but complex which part*/
  }, { /* 1 */
    {OP_vmaxnm_f32,     0xfe800a00, "vmaxnm.f32",     WBd, xx, WAd, WCd, xx, v8|vfp, x, END_LIST},
    {OP_vminnm_f32,     0xfe800a40, "vminnm.f32",     WBd, xx, WAd, WCd, xx, v8|vfp, x, END_LIST},
  }, { /* 2 */
    {OP_vmaxnm_f64,     0xfe800b00, "vmaxnm.f64",     VBq, xx, VAq, VCq, xx, v8|vfp, x, END_LIST},
    {OP_vminnm_f64,     0xfe800b40, "vminnm.f64",     VBq, xx, VAq, VCq, xx, v8|vfp, x, END_LIST},
  },
};

/* Indexed by bit 7 */
const instr_info_t A32_ext_bit7[][2] = {
  { /* 0 */
    {EXT_BIT19,  0xf2800010, "(ext bit19  0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_IMM6L,  0xf2800090, "(ext imm6L  0)", xx, xx, xx, xx, xx, no, x, 0},
  }, { /* 1 */
    {EXT_SIMD6,  0xf2900010, "(ext simd6  4)", xx, xx, xx, xx, xx, no, x, 4},
    {EXT_IMM6L,  0xf2900090, "(ext imm6L  0)", xx, xx, xx, xx, xx, no, x, 0},
  }, { /* 2 */
    /* The .*32 versions of the high-immed instrs can be 0xf2a or 0xf3b so we
     * point at the same simd6[5], w/ bit4=1 ensuring we skip the right entries
     * that we should not hit if we went there w/o checking bit4 first.
     */
    {EXT_SIMD6,  0xf2a00010, "(ext simd6  5)", xx, xx, xx, xx, xx, no, x, 5},
    {EXT_IMM6L,  0xf2a00090, "(ext imm6L  0)", xx, xx, xx, xx, xx, no, x, 0},
  }, { /* 3 */
    {EXT_BIT19,  0xf3800010, "(ext bit19  1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_IMM6L,  0xf3800090, "(ext imm6L  1)", xx, xx, xx, xx, xx, no, x, 1},
  }, { /* 4 */
    {EXT_SIMD6,  0xf3900010, "(ext simd6 10)", xx, xx, xx, xx, xx, no, x, 10},
    {EXT_IMM6L,  0xf3900090, "(ext imm6L  1)", xx, xx, xx, xx, xx, no, x, 1},
  }, { /* 5 */
    /* Similarly, we need to share 0xffa with 0xffb when bit4 is set. */
    {EXT_SIMD6,  0xf3a00010, "(ext simd6 11)", xx, xx, xx, xx, xx, no, x, 11},
    {EXT_IMM6L,  0xf3a00090, "(ext imm6L  1)", xx, xx, xx, xx, xx, no, x, 1},
  },
};

/* Indexed by bit 19.  This up-front split is simpler than having to split
 * 37+ entries inside A32_ext_simd5[] into 2-entry members of this table.
 */
const instr_info_t A32_ext_bit19[][2] = {
  { /* 0 */
    {EXT_SIMD8,         0xf2800000, "(ext simd8  0)", xx, xx, xx, xx, xx, no, x, 0},
    {EXT_SIMD5,         0xf2880000, "(ext simd5  0)", xx, xx, xx, xx, xx, no, x, 0},
  }, { /* 1 */
    {EXT_SIMD8,         0xf3800000, "(ext simd8  1)", xx, xx, xx, xx, xx, no, x, 1},
    {EXT_SIMD5,         0xf3880000, "(ext simd5  1)", xx, xx, xx, xx, xx, no, x, 1},
  },
};

/* Indexed by bit 22 */
const instr_info_t A32_ext_bit22[][2] = {
  { /* 0 */
    {OP_pldw,           0xf510f000, "pld",            xx, xx, MN12z, xx, xx, no, x, tb22[3][0x00]},/*PUW=100*/
    {OP_pld,            0xf550f000, "pld",            xx, xx, MN12z, xx, xx, no, x, tb22[3][0x01]},/*PUW=100*/
  }, { /* 1 */
    {OP_pldw,           0xf590f000, "pld",            xx, xx, MP12z, xx, xx, no, x, tb22[0][0x00]},/*PUW=110*/
    {OP_pld,            0xf5d0f000, "pld",            xx, xx, MP12z, xx, xx, no, x, tb22[0][0x01]},/*PUW=110*/
  }, { /* 2 */
    {OP_pldw,           0xf710f000, "pld",            xx, xx, MNSz, xx, xx, no, x, END_LIST},/*PUW=100*/
    {OP_pld,            0xf750f000, "pld",            xx, xx, MNSz, xx, xx, no, x, END_LIST},/*PUW=100*/
  }, { /* 3 */
    {OP_pldw,           0xf790f000, "pld",            xx, xx, MPSz, xx, xx, no, x, tb22[2][0x00]},/*PUW=110*/
    {OP_pld,            0xf7d0f000, "pld",            xx, xx, MPSz, xx, xx, no, x, tb22[2][0x01]},/*PUW=110*/
  },
};

/* Indexed by 6 bits 11:8,6,4 (thus: a-f | 0,1,4,5) */
const instr_info_t A32_ext_simd6[][64] = {
  { /* 0 */
    {OP_vhadd_s8,       0xf2000000, "vhadd.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x02]},
    {OP_vqadd_s8,       0xf2000010, "vqadd.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x03]},
    {OP_vhadd_s8,       0xf2000040, "vhadd.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_s8,       0xf2000050, "vqadd.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_s8,      0xf2000100, "vrhadd.s8",      VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x06]},
    {OP_vand,           0xf2000110, "vand",           VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x07]},
    {OP_vrhadd_s8,      0xf2000140, "vrhadd.s8",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vand,           0xf2000150, "vand",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vhsub_s8,       0xf2000200, "vhsub.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x0a]},
    {OP_vqsub_s8,       0xf2000210, "vqsub.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x0b]},
    {OP_vhsub_s8,       0xf2000240, "vhsub.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_s8,       0xf2000250, "vqsub.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_s8,        0xf2000300, "vcgt.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6b[0][0x01]},
    {OP_vcge_s8,        0xf2000310, "vcge.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6b[0][0x03]},
    {OP_vcgt_s8,        0xf2000340, "vcgt.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_s8,        0xf2000350, "vcge.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_s8,        0xf2000400, "vshl.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x12]},
    {OP_vqshl_s8,       0xf2000410, "vqshl.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi5[0][0x0f]},
    {OP_vshl_s8,        0xf2000440, "vshl.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_s8,       0xf2000450, "vqshl.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_s8,       0xf2000500, "vrshl.s8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x16]},
    {OP_vqrshl_s8,      0xf2000510, "vqrshl.s8",      VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x17]},
    {OP_vrshl_s8,       0xf2000540, "vrshl.s8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_s8,      0xf2000550, "vqrshl.s8",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_s8,        0xf2000600, "vmax.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x1a]},
    {OP_vmin_s8,        0xf2000610, "vmin.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x1b]},
    {OP_vmax_s8,        0xf2000640, "vmax.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_s8,        0xf2000650, "vmin.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vabd_s8,        0xf2000700, "vabd.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x1e]},
    {OP_vaba_s8,        0xf2000710, "vaba.s8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x1f]},
    {OP_vabd_s8,        0xf2000740, "vabd.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_s8,        0xf2000750, "vaba.s8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    /* 0x80 */
    {OP_vadd_i8,        0xf2000800, "vadd.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x22]},
    {OP_vtst_8,         0xf2000810, "vtst.8",         VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x23]},
    {OP_vadd_i8,        0xf2000840, "vadd.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vtst_8,         0xf2000850, "vtst.8",         VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmla_i8,        0xf2000900, "vmla.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x26]},
    {OP_vmul_i8,        0xf2000910, "vmul.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x27]},
    {OP_vmla_i8,        0xf2000940, "vmla.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmul_i8,        0xf2000950, "vmul.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_s8,       0xf2000a00, "vpmax.s8",       VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_s8,       0xf2000a10, "vpmin.s8",       VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf2000a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2000a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2000b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpadd_i8,       0xf2000b10, "vpadd.i8",       VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf2000b40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2000b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2000c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vfma_f32,       0xf2000c10, "vfma.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x33]},
    {OP_sha1c_32,       0xf2000c40, "sha1c.32",       VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {OP_vfma_f32,       0xf2000c50, "vfma.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, tfpA[10][0x00]},
    {OP_vadd_f32,       0xf2000d00, "vadd.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x36]},
    {OP_vmla_f32,       0xf2000d10, "vmla.f32",       VBq, xx, VAq, VCq, xx, v8, x, tsi6[0][0x37]},
    {OP_vadd_f32,       0xf2000d40, "vadd.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, tfpA[3][0x00]},
    {OP_vmla_f32,       0xf2000d50, "vmla.f32",       VBdq, xx, VAdq, VCdq, xx, v8, x, tfpA[0][0x00]},
    {OP_vceq_f32,       0xf2000e00, "vceq.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x14]},
    {INVALID,           0xf2000e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vceq_f32,       0xf2000e40, "vceq.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2000e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmax_f32,       0xf2000f00, "vmax.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x3e]},
    {OP_vrecps_f32,     0xf2000f10, "vrecps.f32",     VBq, xx, VAq, VCq, xx, no, x, tsi6[0][0x3f]},
    {OP_vmax_f32,       0xf2000f40, "vmax.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrecps_f32,     0xf2000f50, "vrecps.f32",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
  }, { /* 1 */
    {OP_vhadd_s16,      0xf2100000, "vhadd.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x02]},
    {OP_vqadd_s16,      0xf2100010, "vqadd.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x03]},
    {OP_vhadd_s16,      0xf2100040, "vhadd.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_s16,      0xf2100050, "vqadd.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_s16,     0xf2100100, "vrhadd.s16",     VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x06]},
    {OP_vbic,           0xf2100110, "vbic",           VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x07]},
    {OP_vrhadd_s16,     0xf2100140, "vrhadd.s16",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vbic,           0xf2100150, "vbic",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vhsub_s16,      0xf2100200, "vhsub.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x0a]},
    {OP_vqsub_s16,      0xf2100210, "vqsub.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x0b]},
    {OP_vhsub_s16,      0xf2100240, "vhsub.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_s16,      0xf2100250, "vqsub.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_s16,       0xf2100300, "vcgt.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[3][0x01]},
    {OP_vcge_s16,       0xf2100310, "vcge.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[3][0x03]},
    {OP_vcgt_s16,       0xf2100340, "vcgt.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_s16,       0xf2100350, "vcge.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_s16,       0xf2100400, "vshl.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x12]},
    {OP_vqshl_s16,      0xf2100410, "vqshl.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[4][0x1f]},
    {OP_vshl_s16,       0xf2100440, "vshl.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_s16,      0xf2100450, "vqshl.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_s16,      0xf2100500, "vrshl.s16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x16]},
    {OP_vqrshl_s16,     0xf2100510, "vqrshl.s16",     VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x17]},
    {OP_vrshl_s16,      0xf2100540, "vrshl.s16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_s16,     0xf2100550, "vqrshl.s16",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_s16,       0xf2100600, "vmax.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x1a]},
    {OP_vmin_s16,       0xf2100610, "vmin.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x1b]},
    {OP_vmax_s16,       0xf2100640, "vmax.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_s16,       0xf2100650, "vmin.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vabd_s16,       0xf2100700, "vabd.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x1e]},
    {OP_vaba_s16,       0xf2100710, "vaba.s16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x1f]},
    {OP_vabd_s16,       0xf2100740, "vabd.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_s16,       0xf2100750, "vaba.s16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    /* 0x80 */
    {OP_vadd_i16,       0xf2100800, "vadd.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x22]},
    {OP_vtst_16,        0xf2100810, "vtst.16",        VBq, xx, VAq, VCq, xx, no, x, tsi6[1][0x23]},
    {OP_vadd_i16,       0xf2100840, "vadd.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vtst_16,        0xf2100850, "vtst.16",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmla_i16,       0xf2100900, "vmla.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[10][0x02]},
    {OP_vmul_i16,       0xf2100910, "vmul.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[10][0x22]},
    {OP_vmla_i16,       0xf2100940, "vmla.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmul_i16,       0xf2100950, "vmul.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_s16,      0xf2100a00, "vpmax.s16",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_s16,      0xf2100a10, "vpmin.s16",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf2100a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s16,    0xf2100b00, "vqdmulh.s16",    VBq, xx, VAq, VCq, xx, no, x, tsi6[10][0x2e]},
    {OP_vpadd_i16,      0xf2100b10, "vpadd.i16",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqdmulh_s16,    0xf2100b40, "vqdmulh.s16",    VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2100b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha1p_32,       0xf2100c40, "sha1p.32",       VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {INVALID,           0xf2100c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2100f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 2 */
    {OP_vhadd_s32,      0xf2200000, "vhadd.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x02]},
    {OP_vqadd_s32,      0xf2200010, "vqadd.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x03]},
    {OP_vhadd_s32,      0xf2200040, "vhadd.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_s32,      0xf2200050, "vqadd.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_s32,     0xf2200100, "vrhadd.s32",     VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x06]},
    {OP_vorr,           0xf2200110, "vorr",           VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x07]},/*XXX: if src1==src2 then "vmov"*/
    {OP_vrhadd_s32,     0xf2200140, "vrhadd.s32",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vorr,           0xf2200150, "vorr",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},/*XXX: if src1==src2 then "vmov"*/
    {OP_vhsub_s32,      0xf2200200, "vhsub.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x0a]},
    {OP_vqsub_s32,      0xf2200210, "vqsub.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x0b]},
    {OP_vhsub_s32,      0xf2200240, "vhsub.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_s32,      0xf2200250, "vqsub.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_s32,       0xf2200300, "vcgt.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x01]},
    {OP_vcge_s32,       0xf2200310, "vcge.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x03]},
    {OP_vcgt_s32,       0xf2200340, "vcgt.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_s32,       0xf2200350, "vcge.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_s32,       0xf2200400, "vshl.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x12]},
    {OP_vqshl_s32,      0xf2200410, "vqshl.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[5][0x1f]},
    {OP_vshl_s32,       0xf2200440, "vshl.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_s32,      0xf2200450, "vqshl.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_s32,      0xf2200500, "vrshl.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x16]},
    {OP_vqrshl_s32,     0xf2200510, "vqrshl.s32",     VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x17]},
    {OP_vrshl_s32,      0xf2200540, "vrshl.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_s32,     0xf2200550, "vqrshl.s32",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_s32,       0xf2200600, "vmax.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x1a]},
    {OP_vmin_s32,       0xf2200610, "vmin.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x1b]},
    {OP_vmax_s32,       0xf2200640, "vmax.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_s32,       0xf2200650, "vmin.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vabd_s32,       0xf2200700, "vabd.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x1e]},
    {OP_vaba_s32,       0xf2200710, "vaba.s32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x1f]},
    {OP_vabd_s32,       0xf2200740, "vabd.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_s32,       0xf2200750, "vaba.s32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vadd_i32,       0xf2200800, "vadd.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x22]},
    {OP_vtst_32,        0xf2200810, "vtst.32",        VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x23]},
    {OP_vadd_i32,       0xf2200840, "vadd.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vtst_32,        0xf2200850, "vtst.32",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmla_i32,       0xf2200900, "vmla.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[11][0x02]},
    {OP_vmul_i32,       0xf2200910, "vmul.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[11][0x22]},
    {OP_vmla_i32,       0xf2200940, "vmla.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmul_i32,       0xf2200950, "vmul.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_s32,      0xf2200a00, "vpmax.s32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_s32,      0xf2200a10, "vpmin.s32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf2200a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2200a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s32,    0xf2200b00, "vqdmulh.s32",    VBq, xx, VAq, VCq, xx, no, x, tsi6[11][0x32]},
    {OP_vpadd_i32,      0xf2200b10, "vpadd.i32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqdmulh_s32,    0xf2200b40, "vqdmulh.s32",    VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2200b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2200c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vfms_f32,       0xf2200c10, "vfms.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x33]},
    {OP_sha1m_32,       0xf2200c40, "sha1m.32",       VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {OP_vfms_f32,       0xf2200c50, "vfms.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, tfpA[10][0x02]},
    {OP_vsub_f32,       0xf2200d00, "vsub.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x36]},
    {OP_vmls_f32,       0xf2200d10, "vmls.f32",       VBq, xx, VAq, VCq, xx, v8, x, tsi6[2][0x37]},
    {OP_vsub_f32,       0xf2200d40, "vsub.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, tfpA[3][0x02]},
    {OP_vmls_f32,       0xf2200d50, "vmls.f32",       VBdq, xx, VAdq, VCdq, xx, v8, x, tfpA[0][0x02]},
    {INVALID,           0xf2200e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2200e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2200e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2200e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmin_f32,       0xf2200f00, "vmin.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x3e]},
    {OP_vrsqrts_f32,    0xf2200f10, "vrsqrts.f32",    VBq, xx, VAq, VCq, xx, no, x, tsi6[2][0x3f]},
    {OP_vmin_f32,       0xf2200f40, "vmin.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrsqrts_f32,    0xf2200f50, "vrsqrts.f32",    VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
  }, { /* 3 */
    /* XXX: this entry is sparse: should we make a new table to somehow compress it? */
    {INVALID,           0xf2300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqadd_s64,      0xf2300010, "vqadd.s32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x03]},
    {INVALID,           0xf2300040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqadd_s64,      0xf2300050, "vqadd.s32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2300100, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorn,           0xf2300110, "vorn",           VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x07]},
    {INVALID,           0xf2300140, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorn,           0xf2300150, "vorn",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2300200, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqsub_s64,      0xf2300210, "vqsub.s64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x0b]},
    {INVALID,           0xf2300240, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqsub_s64,      0xf2300250, "vqsub.s64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2300300, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300310, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300350, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vshl_s64,       0xf2300400, "vshl.s64",       VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x12]},
    {OP_vqshl_s64,      0xf2300410, "vqshl.s64",      VBq, xx, VAq, VCq, xx, no, x, ti6l[0][0x0f]},
    {OP_vshl_s64,       0xf2300440, "vshl.s64",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_s64,      0xf2300450, "vqshl.s64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_s64,      0xf2300500, "vrshl.s64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x16]},
    {OP_vqrshl_s64,     0xf2300510, "vqrshl.s64",     VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x17]},
    {OP_vrshl_s64,      0xf2300540, "vrshl.s64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_s64,     0xf2300550, "vqrshl.s64",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2300600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300610, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300650, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300710, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300750, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0x80 */
    {OP_vadd_i64,       0xf2300800, "vadd.i64",       VBq, xx, VAq, VCq, xx, no, x, tsi6[3][0x22]},
    {INVALID,           0xf2300810, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vadd_i64,       0xf2300840, "vadd.i64",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2300850, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300910, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300940, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300950, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300a00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300a10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300b40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha1su0_32,     0xf2300c40, "sha1su0.32",     VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {INVALID,           0xf2300c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2300f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 4 */
    {OP_vaddl_s16,      0xf2900000, "vaddl.s16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshr_s16,       0xf2900010, "vshr.s16",       VBq, xx, VCq, i4_16, xx, no, x, tsi6[4][0x03]},/*XXX: imm = 16-imm*/
    {OP_vmla_i16,       0xf2900040, "vmla.i16",       VBq, xx, VAq, VC3h_q, i2x5_3, no, x, tsi6[1][0x24]},
    {OP_vshr_s16,       0xf2900050, "vshr.s16",       VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vaddw_s16,      0xf2900100, "vaddw.s16",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vsra_s16,       0xf2900110, "vsra.s16",       VBq, xx, VCq, i4_16, xx, no, x, tsi6[4][0x07]},/*XXX: imm = 16-imm*/
    {INVALID,           0xf2900140, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vsra_s16,       0xf2900150, "vsra.s16",       VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vsubl_s16,      0xf2900200, "vsubl.s16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vrshr_s16,      0xf2900210, "vrshr.s16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[4][0x0b]},/*XXX: imm = 16-imm*/
    {OP_vmlal_s16,      0xf2900240, "vmlal.s16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {OP_vrshr_s16,      0xf2900250, "vrshr.s16",      VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vsubw_s16,      0xf2900300, "vsubw.s16",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vrsra_s16,      0xf2900310, "vrsra.s16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[4][0x0f]},/*XXX: imm = 16-imm*/
    {OP_vqdmlal_s16,    0xf2900340, "vqdmlal.s16",    VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {OP_vrsra_s16,      0xf2900350, "vrsra.s16",      VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vaddhn_i32,     0xf2900400, "vaddhn.i32",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2900410, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmls_i16,       0xf2900440, "vmls.i16",       VBq, xx, VAq, VC3h_q, i2x5_3, no, x, tsi6[10][0x12]},
    {INVALID,           0xf2900450, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabal_s16,      0xf2900500, "vabal.s16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshl_i16,       0xf2900510, "vshl.i16",       VBq, xx, VCq, i4_16, xx, no, x, tsi6[4][0x17]},/*XXX: imm = 16-imm?*/
    {INVALID,           0xf2900540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vshl_i16,       0xf2900550, "vshl.i16",       VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm?*/
    {OP_vsubhn_i32,     0xf2900600, "vsubhn.i32",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2900610, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmlsl_s16,      0xf2900640, "vmlsl.s16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {INVALID,           0xf2900650, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabdl_s16,      0xf2900700, "vabdl.s16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqshl_s16,      0xf2900710, "vqshl.s16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[1][0x11]},/*XXX: imm = imm-16*/
    {OP_vqdmlsl_s16,    0xf2900740, "vqdmlsl.s16",    VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {OP_vqshl_s16,      0xf2900750, "vqshl.s16",      VBdq, xx, VCdq, i4_16, xx, no, x, tsi6[1][0x13]},/*XXX: imm = imm-16*/
    /* 0x80 */
    {OP_vmlal_s16,      0xf2900800, "vmlal.s16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x0a]},
    {OP_vshrn_i16,      0xf2900810, "vshrn.i16",      VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vmul_i16,       0xf2900840, "vmul.i16",       VBq, xx, VAq, VC3h_q, i2x5_3, no, x, tsi6[1][0x25]},
    {OP_vrshrn_i16,     0xf2900850, "vrshrn.i16",     VBq, xx, VCq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vqdmlal_s16,    0xf2900900, "vqdmlal.s16",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x0e]},
    {OP_vqshrn_s32,     0xf2900910, "vqshrn.s32",     VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {INVALID,           0xf2900940, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrshrn_s32,    0xf2900950, "vqrshrn.s32",    VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vmlsl_s16,      0xf2900a00, "vmlsl.s16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x1a]},
    {EXT_IMM1916,       0xf2900a10, "(ext imm1916 1)", xx, xx, xx, xx, xx, no, x, 1},
    {OP_vmull_s16,      0xf2900a40, "vmull.s16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {INVALID,           0xf2900a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmlsl_s16,    0xf2900b00, "vqdmlsl.s16",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x1e]},
    {INVALID,           0xf2900b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmull_s16,    0xf2900b40, "vqdmull.s16",    VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {INVALID,           0xf2900b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmull_s16,      0xf2900c00, "vmull.s16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x2a]},
    {INVALID,           0xf2900c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s16,    0xf2900c40, "vqdmulh.s16",    VBq, xx, VAq, VC3h_q, i2x5_3, no, x, tsi6[1][0x2c]},
    {INVALID,           0xf2900c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmull_s16,    0xf2900d00, "vqdmull.s16",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[4][0x2e]},
    {INVALID,           0xf2900d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s16,   0xf2900d40, "vqrdmulh.s16",   VBq, xx, VAq, VC3h_q, i2x5_3, no, x, tsi6[10][0x32]},
    {INVALID,           0xf2900d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2900f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 5 */
    {OP_vaddl_s32,      0xf2a00000, "vaddl.s32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshr_s32,       0xf2a00010, "vshr.s32",       VBq, xx, VCq, i5_16, xx, no, x, tsi6[5][0x03]},/*XXX: imm = 32-imm*/
    {OP_vmla_i32,       0xf2a00040, "vmla.i32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[2][0x24]},
    {OP_vshr_s32,       0xf2a00050, "vshr.s32",       VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vaddw_s32,      0xf2a00100, "vaddw.s32",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vsra_s32,       0xf2a00110, "vsra.s32",       VBq, xx, VCq, i5_16, xx, no, x, tsi6[5][0x07]},/*XXX: imm = 32-imm*/
    {OP_vmla_f32,       0xf2a00140, "vmla.f32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[11][0x06]},
    {OP_vsra_s32,       0xf2a00150, "vsra.s32",       VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vsubl_s32,      0xf2a00200, "vsubl.s32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vrshr_s32,      0xf2a00210, "vrshr.s32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[5][0x0b]},/*XXX: imm = 32-imm*/
    {OP_vmlal_s32,      0xf2a00240, "vmlal.s32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {OP_vrshr_s32,      0xf2a00250, "vrshr.s32",      VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vsubw_s32,      0xf2a00300, "vsubw.s32",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vrsra_s32,      0xf2a00310, "vrsra.s32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[5][0x0f]},/*XXX: imm = 32-imm*/
    {OP_vqdmlal_s32,    0xf2a00340, "vqdmlal.s32",    VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {OP_vrsra_s32,      0xf2a00350, "vrsra.s32",      VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vaddhn_i64,     0xf2a00400, "vaddhn.i64",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2a00410, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmls_i32,       0xf2a00440, "vmls.i32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[11][0x12]},
    {INVALID,           0xf2a00450, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabal_s32,      0xf2a00500, "vabal.s32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshl_i32,       0xf2a00510, "vshl.i32",       VBq, xx, VCq, i5_16, xx, no, x, tsi6[5][0x17]},/*XXX: imm = 32-imm?*/
    {OP_vmls_f32,       0xf2a00540, "vmls.f32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[11][0x16]},
    {OP_vshl_i32,       0xf2a00550, "vshl.i32",       VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm?*/
    {OP_vsubhn_i64,     0xf2a00600, "vsubhn.i64",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf2a00610, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmlsl_s32,      0xf2a00640, "vmlsl.s32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {INVALID,           0xf2a00650, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabdl_s32,      0xf2a00700, "vabdl.s32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqshl_s32,      0xf2a00710, "vqshl.s32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[2][0x11]},/*XXX: imm = imm-32*/
    {OP_vqdmlsl_s32,    0xf2a00740, "vqdmlsl.s32",    VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {OP_vqshl_s32,      0xf2a00750, "vqshl.s32",      VBdq, xx, VCdq, i5_16, xx, no, x, tsi6[2][0x13]},/*XXX: imm = imm-32*/
    /* 0x80 */
    {OP_vmlal_s32,      0xf2a00800, "vmlal.s32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x0a]},
    {OP_vshrn_i32,      0xf2a00810, "vshrn.i32",      VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmul_i32,       0xf2a00840, "vmul.i32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[2][0x25]},
    {OP_vrshrn_i32,     0xf2a00850, "vrshrn.i32",     VBq, xx, VCq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vqdmlal_s32,    0xf2a00900, "vqdmlal.s32",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x0e]},
    {OP_vqshrn_s64,     0xf2a00910, "vqshrn.s64",     VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmul_f32,       0xf2a00940, "vmul.f32",       VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[11][0x26]},
    {OP_vqrshrn_s64,    0xf2a00950, "vqrshrn.s64",    VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmlsl_s32,      0xf2a00a00, "vmlsl.s32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x1a]},
    {EXT_IMM2016,       0xf2a00a10, "(ext imm2016 0)", xx, xx, xx, xx, xx, no, x, 0},
    {OP_vmull_s32,      0xf2a00a40, "vmull.s32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {INVALID,           0xf2a00a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmlsl_s32,    0xf2a00b00, "vqdmlsl.s32",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x1e]},
    {INVALID,           0xf2a00b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmull_s32,    0xf2a00b40, "vqdmull.s32",    VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {INVALID,           0xf2a00b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmull_s32,      0xf2a00c00, "vmull.s32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x2a]},
    {INVALID,           0xf2a00c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s32,    0xf2a00c40, "vqdmulh.s32",    VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[2][0x2c]},
    {INVALID,           0xf2a00c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmull_s32,    0xf2a00d00, "vqdmull.s32",    VBdq, xx, VAq, VCq, xx, no, x, tsi6[5][0x2e]},
    {INVALID,           0xf2a00d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s32,   0xf2a00d40, "vqrdmulh.s32",   VBq, xx, VAq, VC4d_q, i1_5, no, x, tsi6[11][0x36]},
    {INVALID,           0xf2a00d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmull_p32,      0xf2a00e00, "vmull.p32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vcvt_f32_s32,   0xf2a00e10, "vcvt.f32.s32",   VBq, xx, VCq, i6_16, xx, no, x, tsi2[0][0x01]},
    {INVALID,           0xf2a00e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_f32_s32,   0xf2a00e50, "vcvt.f32.s32",   VBdq, xx, VCdq, i6_16, xx, no, x, t16[1][0x0a]},
    {OP_vcvt_s32_f32,   0xf2a00f10, "vcvt.s32.f32",   VBq, xx, VCq, i6_16, xx, no, x, tsi6b[8][0x1b]},
    {INVALID,           0xf2a00f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_s32_f32,   0xf2a00f50, "vcvt.s32.f32",   VBdq, xx, VCdq, i6_16, xx, no, x, t16[1][0x0e]},
  }, { /* 6 */
    {OP_vhadd_u8,       0xf3000000, "vhadd.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x02]},
    {OP_vqadd_u8,       0xf3000010, "vqadd.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x03]},
    {OP_vhadd_u8,       0xf3000040, "vhadd.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_u8,       0xf3000050, "vqadd.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_u8,      0xf3000100, "vrhadd.u8",      VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x06]},
    {OP_veor,           0xf3000110, "veor",           VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x07]},
    {OP_vrhadd_u8,      0xf3000140, "vrhadd.u8",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_veor,           0xf3000150, "veor",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vhsub_u8,       0xf3000200, "vhsub.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x0a]},
    {OP_vqsub_u8,       0xf3000210, "vqsub.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x0b]},
    {OP_vhsub_u8,       0xf3000240, "vhsub.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_u8,       0xf3000250, "vqsub.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_u8,        0xf3000300, "vcgt.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x0e]},
    {OP_vcge_u8,        0xf3000310, "vcge.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x0f]},
    {OP_vcgt_u8,        0xf3000340, "vcgt.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_u8,        0xf3000350, "vcge.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_u8,        0xf3000400, "vshl.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x12]},
    {OP_vqshl_u8,       0xf3000410, "vqshl.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi5[1][0x0f]},
    {OP_vshl_u8,        0xf3000440, "vshl.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_u8,       0xf3000450, "vqshl.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_u8,       0xf3000500, "vrshl.u8",       VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x16]},
    {OP_vqrshl_u8,      0xf3000510, "vqrshl.u8",      VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x17]},
    {OP_vrshl_u8,       0xf3000540, "vrshl.u8",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_u8,      0xf3000550, "vqrshl.u8",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_u8,        0xf3000600, "vmax.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x1a]},
    {OP_vmin_u8,        0xf3000610, "vmin.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x1b]},
    {OP_vmax_u8,        0xf3000640, "vmax.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_u8,        0xf3000650, "vmin.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshlu_s64,     0xf30006d0, "vqshlu.s64",     VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},
    {OP_vabd_u8,        0xf3000700, "vabd.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x1f]},
    {OP_vaba_u8,        0xf3000710, "vaba.u8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x20]},
    {OP_vabd_u8,        0xf3000740, "vabd.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_u8,        0xf3000750, "vaba.u8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    /* 0x80 */
    {OP_vsub_i8,        0xf3000800, "vsub.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x23]},
    {OP_vceq_i8,        0xf3000810, "vceq.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6b[0][0x05]},
    {OP_vsub_i8,        0xf3000840, "vsub.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vceq_i8,        0xf3000850, "vceq.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmls_i8,        0xf3000900, "vmls.i8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x27]},
    {OP_vmul_p8,        0xf3000910, "vmul.p8",        VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x28]},
    {OP_vmls_i8,        0xf3000940, "vmls.i8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmul_p8,        0xf3000950, "vmul.p8",        VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_u8,       0xf3000a00, "vpmax.u8",       VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_u8,       0xf3000a10, "vpmin.u8",       VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf3000a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3000a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpadd_f32,      0xf3000b00, "vpadd.f32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmul_f32,       0xf3000b10, "vmul.p32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[5][0x26]},
    {INVALID,           0xf3000b40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmul_f32,       0xf3000b50, "vmul.p32",       VBdq, xx, VAdq, VCdq, xx, no, x, tfpA[2][0x00]},
    {INVALID,           0xf3000c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3000c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha256h_32,     0xf3000c40, "sha256h.32",     VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {INVALID,           0xf3000c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcge_f32,       0xf3000e00, "vcge.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x12]},
    {OP_vacge_f32,      0xf3000e10, "vacge.f32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[6][0x38]},
    {OP_vcge_f32,       0xf3000e40, "vcge.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vacge_f32,      0xf3000e50, "vacge.f32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_f32,      0xf3000f00, "vpmax.f32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmaxnm_f32,     0xf3000f10, "vmaxnm.f32",     VBq, xx, VAq, VCq, xx, v8, x, tsi6[6][0x3c]},
    {INVALID,           0xf3000f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmaxnm_f32,     0xf3000f50, "vmaxnm.f32",     VBdq, xx, VAdq, VCdq, xx, v8, x, tb6[1][0x00]},
  }, { /* 7 */
    {OP_vhadd_u16,      0xf3100000, "vhadd.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x02]},
    {OP_vqadd_u16,      0xf3100010, "vqadd.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x03]},
    {OP_vhadd_u16,      0xf3100040, "vhadd.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_u16,      0xf3100050, "vqadd.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_u16,     0xf3100100, "vrhadd.u16",     VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x06]},
    {OP_vbsl,           0xf3100110, "vbsl",           VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x07]},
    {OP_vrhadd_u16,     0xf3100140, "vrhadd.u16",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vbsl,           0xf3100150, "vbsl",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vhsub_u16,      0xf3100200, "vhsub.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x0a]},
    {OP_vqsub_u16,      0xf3100210, "vqsub.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x0b]},
    {OP_vhsub_u16,      0xf3100240, "vhsub.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_u16,      0xf3100250, "vqsub.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_u16,       0xf3100300, "vcgt.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x0e]},
    {OP_vcge_u16,       0xf3100310, "vcge.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x0f]},
    {OP_vcgt_u16,       0xf3100340, "vcgt.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_u16,       0xf3100350, "vcge.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_u16,       0xf3100400, "vshl.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x12]},
    {OP_vqshl_u16,      0xf3100410, "vqshl.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[10][0x1f]},
    {OP_vshl_u16,       0xf3100440, "vshl.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_u16,      0xf3100450, "vqshl.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_u16,      0xf3100500, "vrshl.u16",      VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x16]},
    {OP_vqrshl_u16,     0xf3100510, "vqrshl.u16",     VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x17]},
    {OP_vrshl_u16,      0xf3100540, "vrshl.u16",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_u16,     0xf3100550, "vqrshl.u16",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_u16,       0xf3100600, "vmax.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x1a]},
    {OP_vmin_u16,       0xf3100610, "vmin.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x1b]},
    {OP_vmax_u16,       0xf3100640, "vmax.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_u16,       0xf3100650, "vmin.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vabd_u16,       0xf3100700, "vabd.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x1e]},
    {OP_vaba_u16,       0xf3100710, "vaba.u16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x1f]},
    {OP_vabd_u16,       0xf3100740, "vabd.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_u16,       0xf3100750, "vaba.u16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vsub_i16,       0xf3100800, "vsub.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[7][0x22]},
    {OP_vceq_i16,       0xf3100810, "vceq.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[3][0x05]},
    {OP_vsub_i16,       0xf3100840, "vsub.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vceq_i16,       0xf3100850, "vceq.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmls_i16,       0xf3100900, "vmls.i16",       VBq, xx, VAq, VCq, xx, no, x, tsi6[4][0x12]},
    {INVALID,           0xf3100910, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmls_i16,       0xf3100940, "vmls.i16",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3100950, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpmax_u16,      0xf3100a00, "vpmax.u16",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_u16,      0xf3100a10, "vpmin.u16",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf3100a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s16,   0xf3100b00, "vqrdmulh.s16",   VBq, xx, VAq, VCq, xx, no, x, tsi6[4][0x36]},
    {INVALID,           0xf3100b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s16,   0xf3100b40, "vqrdmulh.s16",   VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3100b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha256h2_32,    0xf3100c40, "sha256h2.32",    VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {INVALID,           0xf3100c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3100f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 8 */
    {OP_vhadd_u32,      0xf3200000, "vhadd.u32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x02]},
    {OP_vqadd_u32,      0xf3200010, "vqadd.u64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x03]},
    {OP_vhadd_u32,      0xf3200040, "vhadd.u32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqadd_u32,      0xf3200050, "vqadd.u64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrhadd_u32,     0xf3200100, "vrhadd.u32",     VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x06]},
    {OP_vbit,           0xf3200110, "vbit",           VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x07]},
    {OP_vrhadd_u32,     0xf3200140, "vrhadd.u32",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vbit,           0xf3200150, "vbit",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vhsub_u32,      0xf3200200, "vhsub.u32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x0a]},
    {OP_vqsub_u32,      0xf3200210, "vqsub.u32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x0b]},
    {OP_vhsub_u32,      0xf3200240, "vhsub.u32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqsub_u32,      0xf3200250, "vqsub.u32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcgt_u32,       0xf3200300, "vcgt.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x0e]},
    {OP_vcge_u32,       0xf3200310, "vcge.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x0f]},
    {OP_vcgt_u32,       0xf3200340, "vcgt.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vcge_u32,       0xf3200350, "vcge.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vshl_u32,       0xf3200400, "vshl.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x12]},
    {OP_vqshl_u32,      0xf3200410, "vqshl.u32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[11][0x1f]},
    {OP_vshl_u32,       0xf3200440, "vshl.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_u32,      0xf3200450, "vqshl.u32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_u32,      0xf3200500, "vrshl.u32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x16]},
    {OP_vqrshl_u32,     0xf3200510, "vqrshl.u32",     VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x17]},
    {OP_vrshl_u32,      0xf3200540, "vrshl.u32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_u32,     0xf3200550, "vqrshl.u32",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmax_u32,       0xf3200600, "vmax.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x1a]},
    {OP_vmin_u32,       0xf3200610, "vmin.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x1b]},
    {OP_vmax_u32,       0xf3200640, "vmax.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmin_u32,       0xf3200650, "vmin.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vaba_u32,       0xf3200700, "vaba.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x1e]},
    {OP_vabd_u32,       0xf3200710, "vabd.u32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x1f]},
    {OP_vaba_u32,       0xf3200740, "vaba.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vabd_u32,       0xf3200750, "vabd.u32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    /* 0x80 */
    {OP_vsub_i32,       0xf3200800, "vsub.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x22]},
    {OP_vceq_i32,       0xf3200810, "vceq.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x05]},
    {OP_vsub_i32,       0xf3200840, "vsub.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vceq_i32,       0xf3200850, "vceq.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmls_i32,       0xf3200900, "vmls.i32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[5][0x12]},
    {OP_vmul_p32,       0xf3200910, "vmul.p32",       VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x27]},
    {OP_vmls_i32,       0xf3200940, "vmls.i32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmul_p32,       0xf3200950, "vmul.p32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmax_u32,      0xf3200a00, "vpmax.u32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vpmin_u32,      0xf3200a10, "vpmin.u32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {INVALID,           0xf3200a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s32,   0xf3200b00, "vqrdmulh.s32",   VBq, xx, VAq, VCq, xx, no, x, tsi6[5][0x36]},
    {INVALID,           0xf3200b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s32,   0xf3200b40, "vqrdmulh.s32",   VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3200b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha256su1_32,   0xf3200c40, "sha256su1.32",   VBdq, xx, VAdq, VCdq, xx, v8, x, END_LIST},
    {INVALID,           0xf3200c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3200d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcgt_f32,       0xf3200e00, "vcgt.f32",       VBq, xx, VAq, VCq, xx, no, x, tsi6b[6][0x10]},
    {OP_vacgt_f32,      0xf3200e10, "vacgt.f32",      VBq, xx, VAq, VCq, xx, no, x, tsi6[8][0x3b]},
    {OP_vcgt_f32,       0xf3200e40, "vcgt.f32",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vacgt_f32,      0xf3200e50, "vacgt.f32",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vpmin_f32,      0xf3200f00, "vpmin.f32",      VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vminnm_f32,     0xf3200f10, "vminnm.f32",     VBq, xx, VAq, VCq, xx, v8, x, tsi6[8][0x3f]},
    {INVALID,           0xf3200f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vminnm_f32,     0xf3200f50, "vminnm.f32",     VBdq, xx, VAdq, VCdq, xx, v8, x, tb6[1][0x01]},
  }, { /* 9 */
    /* XXX: this entry is sparse: should we make a new table to somehow compress it? */
    {INVALID,           0xf3300000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqadd_u64,      0xf3300010, "vqadd.u64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x03]},
    {INVALID,           0xf3300040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqadd_u64,      0xf3300050, "vqadd.u64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3300100, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vbif,           0xf3300110, "vbif",           VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x07]},
    {INVALID,           0xf3300140, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vbif,           0xf3300150, "vbif",           VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3300200, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqsub_u64,      0xf3300210, "vqsub.u64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x0b]},
    {INVALID,           0xf3300240, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqsub_u64,      0xf3300250, "vqsub.u64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3300300, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300310, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300350, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vshl_u64,       0xf3300400, "vshl.u64",       VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x12]},
    {OP_vqshl_u64,      0xf3300410, "vqshl.u64",      VBq, xx, VAq, VCq, xx, no, x, ti6l[1][0x0f]},
    {OP_vshl_u64,       0xf3300440, "vshl.u64",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshl_u64,      0xf3300450, "vqshl.u64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vrshl_u64,      0xf3300500, "vrshl.u64",      VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x16]},
    {OP_vqrshl_u64,     0xf3300510, "vqrshl.u64",     VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x17]},
    {OP_vrshl_u64,      0xf3300540, "vrshl.u64",      VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqrshl_u64,     0xf3300550, "vqrshl.u64",     VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3300600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300610, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300650, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300710, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300750, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0x80 */
    {OP_vsub_i64,       0xf3300800, "vsub.i64",       VBq, xx, VAq, VCq, xx, no, x, tsi6[9][0x22]},
    {INVALID,           0xf3300810, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vsub_i64,       0xf3300840, "vsub.i64",       VBdq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {INVALID,           0xf3300850, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300910, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300940, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300950, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300a00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300a10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300a40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300b40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300c40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3300f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 10 */
    {OP_vaddl_u16,      0xf3900000, "vaddl.u16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshr_u16,       0xf3900010, "vshr.u16",       VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x03]},/*XXX: imm = 16-imm*/
    {OP_vmla_i16,       0xf3900040, "vmla.i16",       VBdq, xx, VAdq, VC3h_q, i2x5_3, no, x, tsi6[1][0x26]},
    {OP_vshr_u16,       0xf3900050, "vshr.u16",       VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vaddw_u16,      0xf3900100, "vaddw.u16",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vsra_u16,       0xf3900110, "vsra.u16",       VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x07]},/*XXX: imm = 16-imm*/
    {INVALID,           0xf3900140, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vsra_u16,       0xf3900150, "vsra.u16",       VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vsubl_u16,      0xf3900200, "vsubl.u16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vrshr_u16,      0xf3900210, "vrshr.u16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x0b]},/*XXX: imm = 16-imm*/
    {OP_vmlal_u16,      0xf3900240, "vmlal.u16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {OP_vrshr_u16,      0xf3900250, "vrshr.u16",      VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vsubw_u16,      0xf3900300, "vsubw.u16",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vrsra_u16,      0xf3900310, "vrsra.u16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x0f]},/*XXX: imm = 16-imm*/
    {INVALID,           0xf3900340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrsra_u16,      0xf3900350, "vrsra.u16",      VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vraddhn_i32,    0xf3900400, "vraddhn.i32",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vsri_16,        0xf3900410, "vsri.16",        VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x13]},/*XXX: imm = 16-imm?*/
    {OP_vmls_i16,       0xf3900440, "vmls.i16",       VBdq, xx, VAdq, VC3h_q, i2x5_3, no, x, tsi6[7][0x26]},
    {OP_vsri_16,        0xf3900450, "vsri.16",        VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm?*/
    {OP_vabal_u16,      0xf3900500, "vabal.u16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vsli_16,        0xf3900510, "vsli.16",        VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x17]},/*XXX: imm = 16-imm?*/
    {INVALID,           0xf3900540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vsli_16,        0xf3900550, "vsli.16",        VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm?*/
    {OP_vrsubhn_i32,    0xf3900600, "vrsubhn.i32",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshlu_s16,     0xf3900610, "vqshlu.s16",     VBq, xx, VCq, i4_16, xx, no, x, tsi6[10][0x1b]},/*XXX: imm = imm-16*/
    {OP_vmlsl_u16,      0xf3900640, "vmlsl.u16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {OP_vqshlu_s16,     0xf3900650, "vqshlu.s16",     VBdq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = imm-16*/
    {OP_vabdl_u16,      0xf3900700, "vabdl.u16",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqshl_u16,      0xf3900710, "vqshl.u16",      VBq, xx, VCq, i4_16, xx, no, x, tsi6[7][0x11]},/*XXX: imm = imm-16*/
    {INVALID,           0xf3900740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshl_u16,      0xf3900750, "vqshl.u16",      VBdq, xx, VCdq, i4_16, xx, no, x, tsi6[7][0x13]},/*XXX: imm = imm-16*/
    /* 0x80 */
    {OP_vmlal_u16,      0xf3900800, "vmlal.u16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[10][0x0a]},
    {OP_vqshrn_u32,     0xf3900810, "vqshrn.u32",     VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vmul_i16,       0xf3900840, "vmul.i16",       VBdq, xx, VAdq, VC3h_q, i2x5_3, no, x, tsi6[1][0x27]},
    {OP_vqrshrn_u32,    0xf3900850, "vqrshrn.u32",    VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {INVALID,           0xf3900900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshrun_s32,    0xf3900910, "vqshrun.s32",    VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {INVALID,           0xf3900940, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrshrun_s32,   0xf3900950, "vqrshrun.s32",   VBq, xx, VCdq, i4_16, xx, no, x, END_LIST},/*XXX: imm = 16-imm*/
    {OP_vmlsl_u16,      0xf3900a00, "vmlsl.u16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[10][0x1a]},
    {EXT_IMM1916,       0xf3900a10, "(ext imm1916 2)", xx, xx, xx, xx, xx, no, x, 2},
    {OP_vmull_u16,      0xf3900a40, "vmull.u16",      VBdq, xx, VAq, VC3h_q, i2x5_3, no, x, END_LIST},
    {INVALID,           0xf3900a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmull_u16,      0xf3900c00, "vmull.u16",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[10][0x2a]},
    {INVALID,           0xf3900c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s16,    0xf3900c40, "vqdmulh.s16",    VBdq, xx, VAdq, VC3h_q, i2x5_3, no, x, tsi6[1][0x2e]},
    {INVALID,           0xf3900c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s16,   0xf3900d40, "vqrdmulh.s16",   VBdq, xx, VAdq, VC3h_q, i2x5_3, no, x, tsi6[7][0x2e]},
    {INVALID,           0xf3900d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3900f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 11 */
    /* 0xf3b with bit 4 set will also come here */
    {OP_vaddl_u32,      0xf3a00000, "vaddl.u32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vshr_u32,       0xf3a00010, "vshr.u32",       VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x03]},/*XXX: imm = 32-imm*/
    {OP_vmla_i32,       0xf3a00040, "vmla.i32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[2][0x26]},
    {OP_vshr_u32,       0xf3a00050, "vshr.u32",       VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vaddw_u32,      0xf3a00100, "vaddw.u32",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vsra_u32,       0xf3a00110, "vsra.u32",       VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x07]},/*XXX: imm = 32-imm*/
    {OP_vmla_f32,       0xf3a00140, "vmla.f32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[0][0x35]},
    {OP_vsra_u32,       0xf3a00150, "vsra.u32",       VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vsubl_u32,      0xf3a00200, "vsubl.u32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vrshr_u32,      0xf3a00210, "vrshr.u32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x0b]},/*XXX: imm = 32-imm*/
    {OP_vmlal_u32,      0xf3a00240, "vmlal.u32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {OP_vrshr_u32,      0xf3a00250, "vrshr.u32",      VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vsubw_u32,      0xf3a00300, "vsubw.u32",      VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vrsra_u32,      0xf3a00310, "vrsra.u32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x0f]},/*XXX: imm = 32-imm*/
    {INVALID,           0xf3a00340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrsra_u32,      0xf3a00350, "vrsra.u32",      VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vraddhn_i64,    0xf3a00400, "vraddhn.i64",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vsri_32,        0xf3a00410, "vsri.32",        VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x13]},/*XXX: imm = 32-imm?*/
    {OP_vmls_i32,       0xf3a00440, "vmls.i32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[8][0x26]},
    {OP_vsri_32,        0xf3a00450, "vsri.32",        VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm?*/
    {OP_vabal_u32,      0xf3a00500, "vabal.u32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vsli_32,        0xf3a00510, "vsli.32",        VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x17]},/*XXX: imm = 32-imm?*/
    {OP_vmls_f32,       0xf3a00540, "vmls.f32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[2][0x35]},
    {OP_vsli_32,        0xf3a00550, "vsli.32",        VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm?*/
    {OP_vrsubhn_i64,    0xf3a00600, "vrsubhn.i64",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vqshlu_s32,     0xf3a00610, "vqshlu.s32",     VBq, xx, VCq, i5_16, xx, no, x, tsi6[11][0x1b]},/*XXX: imm = imm-32*/
    {OP_vmlsl_u32,      0xf3a00640, "vmlsl.u32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {OP_vqshlu_s32,     0xf3a00650, "vqshlu.s32",     VBdq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = imm-32*/
    {OP_vabdl_u32,      0xf3a00700, "vabdl.u32",      VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vqshl_u32,      0xf3a00710, "vqshl.u32",      VBq, xx, VCq, i5_16, xx, no, x, tsi6[8][0x11]},/*XXX: imm = imm-32*/
    {INVALID,           0xf3a00740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshl_u32,      0xf3a00750, "vqshl.u32",      VBdq, xx, VCdq, i5_16, xx, no, x, tsi6[8][0x13]},/*XXX: imm = imm-32*/
    /* 0x80 */
    {OP_vmlal_u32,      0xf3a00800, "vmlal.u32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[11][0x0a]},
    {OP_vqshrn_u64,     0xf3a00810, "vqshrn.u64",     VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmul_i32,       0xf3a00840, "vmul.i32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[2][0x27]},
    {OP_vqrshrn_u64,    0xf3a00850, "vqrshrn.u64",    VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {INVALID,           0xf3a00900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshrun_s64,    0xf3a00910, "vqshrun.s64",    VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmul_f32,       0xf3a00940, "vmul.f32",       VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[6][0x30]},
    {OP_vqrshrun_s64,   0xf3a00950, "vqrshrun.s64",   VBq, xx, VCdq, i5_16, xx, no, x, END_LIST},/*XXX: imm = 32-imm*/
    {OP_vmlsl_u32,      0xf3a00a00, "vmlsl.u32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[11][0x1a]},
    {EXT_IMM2016,       0xf3a00a10, "(ext imm2016 1)", xx, xx, xx, xx, xx, no, x, 1},
    {OP_vmull_u32,      0xf3a00a40, "vmull.u32",      VBdq, xx, VAq, VC4d_q, i1_5, no, x, END_LIST},
    {INVALID,           0xf3a00a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00b40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmull_u32,      0xf3a00c00, "vmull.u32",      VBdq, xx, VAq, VCq, xx, no, x, tsi6[11][0x2a]},
    {INVALID,           0xf3a00c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqdmulh_s32,    0xf3a00c40, "vqdmulh.s32",    VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[2][0x2e]},
    {INVALID,           0xf3a00c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqrdmulh_s32,   0xf3a00d40, "vqrdmulh.s32",   VBdq, xx, VAdq, VC4d_q, i1_5, no, x, tsi6[8][0x2e]},
    {INVALID,           0xf3a00d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3a00e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_f32_u32,   0xf3a00e10, "vcvt.f32.u32",   VBq, xx, VCq, i6_16, xx, no, x, tsi2[1][0x01]},
    {INVALID,           0xf3a00e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_f32_u32,   0xf3a00e50, "vcvt.f32.u32",   VBdq, xx, VCdq, i6_16, xx, no, x, t16[1][0x0b]},
    {INVALID,           0xf3a00f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_u32_f32,   0xf3a00f10, "vcvt.u32.f32",   VBq, xx, VCq, i6_16, xx, no, x, tsi2[5][0x01]},
    {INVALID,           0xf3a00f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_u32_f32,   0xf3a00f50, "vcvt.u32.f32",   VBdq, xx, VCdq, i6_16, xx, no, x, t16[1][0x0f]},
  },
};

/* Indexed by bits 11:8,6 */
const instr_info_t A32_ext_simd5[][32] = {
  { /* 0 */
    {OP_vshr_s8,        0xf2880010, "vshr.s8",        VBq, xx, VCq, i3_16, xx, no, x, tsi5[0][0x01]},/*XXX: imm = 8-imm*/
    {OP_vshr_s8,        0xf2880050, "vshr.s8",        VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vsra_s8,        0xf2880110, "vsra.s8",        VBq, xx, VCq, i3_16, xx, no, x, tsi5[0][0x03]},/*XXX: imm = 8-imm*/
    {OP_vsra_s8,        0xf2880150, "vsra.s8",        VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vrshr_s8,       0xf2880210, "vrshr.s8",       VBq, xx, VCq, i3_16, xx, no, x, tsi5[0][0x05]},/*XXX: imm = 8-imm*/
    {OP_vrshr_s8,       0xf2880250, "vrshr.s8",       VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vrsra_s8,       0xf2880310, "vrsra.s8",       VBq, xx, VCq, i3_16, xx, no, x, tsi5[0][0x07]},/*XXX: imm = 8-imm*/
    {OP_vrsra_s8,       0xf2880350, "vrsra.s8",       VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {INVALID,           0xf2880410, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880450, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vshl_i8,        0xf2880510, "vshl.i8",        VBq, xx, VCq, i3_16, xx, no, x, tsi5[0][0x0b]},/*XXX: imm = 8-imm?*/
    {OP_vshl_i8,        0xf2880550, "vshl.i8",        VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm?*/
    {INVALID,           0xf2880610, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880650, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshl_s8,       0xf2880710, "vqshl.s8",       VBq, xx, VCq, i3_16, xx, no, x, tsi6[0][0x11]},/*XXX: imm = imm-8*/
    {OP_vqshl_s8,       0xf2880750, "vqshl.s8",       VBdq, xx, VCdq, i3_16, xx, no, x, tsi6[0][0x13]},/*XXX: imm = imm-8*/
    {OP_vshrn_i8,       0xf2880810, "vshrn.i8",       VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vrshrn_i8,      0xf2880850, "vrshrn.i8",      VBq, xx, VCq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vqshrn_s16,     0xf2880910, "vqshrn.s16",     VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vqrshrn_s16,    0xf2880950, "vqrshrn.s16",    VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {EXT_IMM1816,       0xf2880a10, "(ext imm1816 0)", xx, xx, xx, xx, xx, no, x, 0},
    {INVALID,           0xf2880a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2880f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 1 */
    {OP_vshr_u8,        0xf3880010, "vshr.u8",        VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x01]},/*XXX: imm = 8-imm*/
    {OP_vshr_u8,        0xf3880050, "vshr.u8",        VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vsra_u8,        0xf3880110, "vsra.u8",        VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x03]},/*XXX: imm = 8-imm*/
    {OP_vsra_u8,        0xf3880150, "vsra.u8",        VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vrshr_u8,       0xf3880210, "vrshr.u8",       VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x05]},/*XXX: imm = 8-imm*/
    {OP_vrshr_u8,       0xf3880250, "vrshr.u8",       VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vrsra_u8,       0xf3880310, "vrsra.u8",       VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x07]},/*XXX: imm = 8-imm*/
    {OP_vrsra_u8,       0xf3880350, "vrsra.u8",       VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vsri_8,         0xf3880410, "vsri.8",         VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x09]},/*XXX: imm = 8-imm?*/
    {OP_vsri_8,         0xf3880450, "vsri.8",         VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm?*/
    {OP_vsli_8,         0xf3880510, "vsli.8",         VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x0b]},/*XXX: imm = 8-imm?*/
    {OP_vsli_8,         0xf3880550, "vsli.8",         VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm?*/
    {OP_vqshlu_s8,      0xf3880610, "vqshlu.s8",      VBq, xx, VCq, i3_16, xx, no, x, tsi5[1][0x0d]},/*XXX: imm = imm-8*/
    {OP_vqshlu_s8,      0xf3880650, "vqshlu.s8",      VBdq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = imm-8*/
    {OP_vqshl_u8,       0xf3880710, "vqshl.u8",       VBq, xx, VCq, i3_16, xx, no, x, tsi6[6][0x11]},/*XXX: imm = imm-8*/
    {OP_vqshl_u8,       0xf3880750, "vqshl.u8",       VBdq, xx, VCdq, i3_16, xx, no, x, tsi6[6][0x13]},/*XXX: imm = imm-8*/
    {OP_vqshrn_u16,     0xf3880810, "vqshrn.u16",     VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vqrshrn_u16,    0xf3880850, "vqrshrn.u16",    VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vqshrun_s16,    0xf3880910, "vqshrun.s16",    VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {OP_vqrshrun_s16,   0xf3880950, "vqrshrun.s16",   VBq, xx, VCdq, i3_16, xx, no, x, END_LIST},/*XXX: imm = 8-imm*/
    {EXT_IMM1816,       0xf3880a10, "(ext imm1816 1)", xx, xx, xx, xx, xx, no, x, 1},
    {INVALID,           0xf3880a50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880b10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880b50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880c10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880c50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880d10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880d50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880e10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880e50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3880f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  },
};

/* Indexed by bits 18:16,8:7 */
const instr_info_t A32_ext_simd5b[][32] = {
  { /* 0 */
    {OP_vrinta_f32_f32, 0xfeb80a40, "vrinta.f32.f32", WBd, xx, WCd, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeb80ac0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrinta_f64_f64, 0xfeb80b40, "vrinta.f64.f64", VBq, xx, VCq, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeb80bc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintn_f32_f32, 0xfeb90a40, "vrintn.f32.f32", WBd, xx, WCd, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeb90ac0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintn_f64_f64, 0xfeb90b40, "vrintn.f64.f64", VBq, xx, VCq, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeb90bc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintp_f32_f32, 0xfeba0a40, "vrintp.f32.f32", WBd, xx, WCd, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeba0ac0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintp_f64_f64, 0xfeba0b40, "vrintp.f64.f64", VBq, xx, VCq, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfeba0bc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintm_f32_f32, 0xfebb0a40, "vrintm.f32.f32", WBd, xx, WCd, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfebb0ac0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintm_f64_f64, 0xfebb0b40, "vrintm.f64.f64", VBq, xx, VCq, xx, xx, v8, x, END_LIST},
    {INVALID,           0xfebb0bc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvta_u32_f32,  0xfebc0a40, "vcvta.u32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvta_s32_f32,  0xfebc0ac0, "vcvta.s32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvta_u32_f64,  0xfebc0b40, "vcvta.u32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvta_s32_f64,  0xfebc0bc0, "vcvta.s32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtn_u32_f32,  0xfebd0a40, "vcvtn.u32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtn_s32_f32,  0xfebd0ac0, "vcvtn.s32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtn_u32_f64,  0xfebd0b40, "vcvtn.u32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtn_s32_f64,  0xfebd0bc0, "vcvtn.s32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtp_u32_f32,  0xfebe0a40, "vcvtp.u32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtp_s32_f32,  0xfebe0ac0, "vcvtp.s32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtp_u32_f64,  0xfebe0b40, "vcvtp.u32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtp_s32_f64,  0xfebe0bc0, "vcvtp.s32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtm_u32_f32,  0xfebf0a40, "vcvtm.u32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtm_s32_f32,  0xfebf0ac0, "vcvtm.s32.f32",  WBd, xx, WCd, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtm_u32_f64,  0xfebf0b40, "vcvtm.u32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
    {OP_vcvtm_s32_f64,  0xfebf0bc0, "vcvtm.s32.f32",  WBd, xx, VCq, xx, xx, v8|vfp, x, END_LIST},
  },
};

/* Indexed by bits 11:8,6:4, but 6:4 are in the following manner:
 * + If bit 4 == 0, offset is 0;
 * + Else, offset is 1 + bits 6:5.
 * (Thus, 0 followed by odds < 8).
 */
const instr_info_t A32_ext_simd8[][80] = {
  { /* 0 */
    {OP_vaddl_s8,       0xf2800000, "vaddl.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf2800010, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x03]},
    {OP_vmvn_i32,       0xf2800030, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x04]},
    {OP_vmov_i32,       0xf2800050, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    {OP_vmvn_i32,       0xf2800070, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    /* 0x10 */
    {OP_vaddw_s8,       0xf2800100, "vaddw.s8",       VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf2800110, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x08]},
    {OP_vbic_i32,       0xf2800130, "vbic.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x09]},
    {OP_vorr_i32,       0xf2800150, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    {OP_vbic_i32,       0xf2800170, "vbic.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    /* 0x20 */
    {OP_vsubl_s8,       0xf2800200, "vsubl.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf2800210, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800230, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf2800250, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800270, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x30 */
    {OP_vsubw_s8,       0xf2800300, "vsubw.s8",       VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf2800310, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800330, "vbic.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i32,       0xf2800350, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800370, "vbic.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x40 */
    {OP_vaddhn_i16,     0xf2800400, "vaddhn.i16",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf2800410, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800430, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf2800450, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800470, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x50 */
    {OP_vabal_s8,       0xf2800500, "vabal.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf2800510, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800530, "vbic.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i32,       0xf2800550, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800570, "vbic.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x60 */
    {OP_vsubhn_i16,     0xf2800600, "vsubhn.i16",     VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf2800610, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800630, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf2800650, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf2800670, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x70 */
    {OP_vabdl_s8,       0xf2800700, "vabdl.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf2800710, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800730, "vbic.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i32,       0xf2800750, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf2800770, "vbic.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x80 */
    {OP_vmlal_s8,       0xf2800800, "vmlal.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i16,       0xf2800810, "vmov.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x2b]},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmvn_i16,       0xf2800830, "vmvn.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x2c]},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmov_i16,       0xf2800850, "vmov.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmvn_i16,       0xf2800870, "vmvn.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},/*XXX: different <cmode> immed expansions are complex*/
    /* 0x90 */
    {INVALID,           0xf2800900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf2800910, "vorr.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x30]},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vbic_i16,       0xf2800930, "vbic.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x31]},
    {OP_vorr_i16,       0xf2800950, "vorr.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vbic_i16,       0xf2800970, "vbic.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    /* 0xa0 */
    {OP_vmlsl_s8,       0xf2800a00, "vmlsl.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i16,       0xf2800a10, "vmov.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i16,       0xf2800a30, "vmvn.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i16,       0xf2800a50, "vmov.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i16,       0xf2800a70, "vmvn.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0xb0 */
    {INVALID,           0xf2800b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf2800b10, "vorr.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i16,       0xf2800b30, "vbic.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i16,       0xf2800b50, "vorr.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i16,       0xf2800b70, "vbic.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0xc0 */
    {OP_vmull_s8,       0xf2800c00, "vmull.s8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf2800c10, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmvn_i32,       0xf2800c30, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmov_i32,       0xf2800c50, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmvn_i32,       0xf2800c70, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    /* 0xd0 */
    {INVALID,           0xf2800d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmov_i32,       0xf2800d10, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmvn_i32,       0xf2800d30, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmov_i32,       0xf2800d50, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmvn_i32,       0xf2800d70, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    /* 0xe0 */
    {OP_vmull_p8,       0xf2800e00, "vmull.p8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i8,        0xf2800e10, "vmov.i8",        VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x49]},
    {OP_vmov_i64,       0xf2800e30, "vmov.i64",       VBq, xx, i8x24_16_0, xx, xx, no, x, tsi8[0][0x4a]},
    {OP_vmov_i8,        0xf2800e50, "vmov.i8",        VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    {OP_vmov_i64,       0xf2800e70, "vmov.i64",       VBdq, xx, i8x24_16_0, xx, xx, no, x, END_LIST},
    /* 0xf0 */
    {INVALID,           0xf2800f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2800f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2800f30, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2800f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf2800f70, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 1 */
    {OP_vaddl_u8,       0xf3800000, "vaddl.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf3800010, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800030, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf3800050, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800070, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x10 */
    {OP_vaddw_u8,       0xf3800100, "vaddw.u8",       VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf3800110, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i16,       0xf3800130, "vbic.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i32,       0xf3800150, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i16,       0xf3800170, "vbic.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x20 */
    {OP_vsubl_u8,       0xf3800200, "vsubl.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf3800210, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800230, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf3800250, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800270, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x30 */
    {OP_vsubw_u8,       0xf3800300, "vsubw.u8",       VBdq, xx, VAdq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf3800310, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf3800330, "vbic.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vorr_i32,       0xf3800350, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vbic_i32,       0xf3800370, "vbic.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x40 */
    {OP_vraddhn_i16,    0xf3800400, "vraddhn.i16",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf3800410, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800430, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf3800450, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800470, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x50 */
    {OP_vabal_u8,       0xf3800500, "vabal.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf3800510, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800530, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i32,       0xf3800550, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800570, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0x60 */
    {OP_vrsubhn_i16,    0xf3800600, "vrsubhn.i16",    VBq, xx, VAdq, VCdq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf3800610, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800630, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i32,       0xf3800650, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i32,       0xf3800670, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0x70 */
    {OP_vabdl_u8,       0xf3800700, "vabdl.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vorr_i32,       0xf3800710, "vorr.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800730, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i32,       0xf3800750, "vorr.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800770, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0x80 */
    {OP_vmlal_u8,       0xf3800800, "vmlal.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i16,       0xf3800810, "vmov.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmvn_i16,       0xf3800830, "vmvn.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmov_i16,       0xf3800850, "vmov.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    {OP_vmvn_i16,       0xf3800870, "vmvn.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    /* 0x90 */
    {INVALID,           0xf3800900, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf3800910, "vorr.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    {INVALID,           0xf3800930, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf3800950, "vorr.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: different <cmode> immed expansions are complex*/
    {INVALID,           0xf3800970, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0xa0 */
    {OP_vmlsl_u8,       0xf3800a00, "vmlsl.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i16,       0xf3800a10, "vmov.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i16,       0xf3800a30, "vmvn.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i16,       0xf3800a50, "vmov.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmvn_i16,       0xf3800a70, "vmvn.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0xb0 */
    {INVALID,           0xf3800b00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf3800b10, "vorr.i16",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800b30, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vorr_i16,       0xf3800b50, "vorr.i16",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3800b70, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    /* 0xc0 */
    {OP_vmull_u8,       0xf3800c00, "vmull.u8",       VBdq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vmov_i32,       0xf3800c10, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmvn_i32,       0xf3800c30, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmov_i32,       0xf3800c50, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    {OP_vmvn_i32,       0xf3800c70, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xff added*/
    /* 0xd0 */
    {INVALID,           0xf3800d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmov_i32,       0xf3800d10, "vmov.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmvn_i32,       0xf3800d30, "vmvn.i32",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmov_i32,       0xf3800d50, "vmov.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    {OP_vmvn_i32,       0xf3800d70, "vmvn.i32",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},/*XXX: has 0xffff added*/
    /* 0xe0 */
    {INVALID,           0xf3800e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vmov_i8,        0xf3800e10, "vmov.i8",        VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i64,       0xf3800e30, "vmov.i64",       VBq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i8,        0xf3800e50, "vmov.i8",        VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    {OP_vmov_i64,       0xf3800e70, "vmov.i64",       VBdq, xx, i8x24_16_0, xx, xx, no, x, DUP_ENTRY},
    /* 0xf0 */
    {INVALID,           0xf3800f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3800f10, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3800f30, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3800f50, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3800f70, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  },
};

/* Indexed by bits 10:8,7:6 with one extra set of 7:6 for bit 11 being set */
const instr_info_t A32_ext_simd6b[][36] = {
  { /* 0 */
    {OP_vcgt_s8,        0xf3b10000, "vcgt.s8",        VBq, xx, VCq, k0, xx, no, x, tsi6[0][0x0c]},
    {OP_vcgt_s8,        0xf3b10040, "vcgt.s8",        VBdq, xx, VCdq, k0, xx, no, x, tsi6[0][0x0e]},
    {OP_vcge_s8,        0xf3b10080, "vcge.s8",        VBq, xx, VCq, k0, xx, no, x, tsi6[0][0x0d]},
    {OP_vcge_s8,        0xf3b100c0, "vcge.s8",        VBdq, xx, VCdq, k0, xx, no, x, tsi6[0][0x0f]},
    {OP_vceq_i8,        0xf3b10100, "vceq.i8",        VBq, xx, VCq, k0, xx, no, x, tsi6[6][0x22]},
    {OP_vceq_i8,        0xf3b10140, "vceq.i8",        VBdq, xx, VCdq, k0, xx, no, x, tsi6[6][0x24]},
    {OP_vcle_s8,        0xf3b10180, "vcle.s8",        VBq, xx, VCq, k0, xx, no, x, tsi6b[0][0x07]},
    {OP_vcle_s8,        0xf3b101c0, "vcle.s8",        VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {OP_vclt_s8,        0xf3b10200, "vclt.s8",        VBq, xx, VCq, k0, xx, no, x, tsi6b[0][0x09]},
    {OP_vclt_s8,        0xf3b10240, "vclt.s8",        VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {INVALID,           0xf3b10280, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b102c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabs_s8,        0xf3b10300, "vabs.s8",        VBq, xx, VCq, xx, xx, no, x, tsi6b[0][0x0d]},
    {OP_vabs_s8,        0xf3b10340, "vabs.s8",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vneg_s8,        0xf3b10380, "vneg.s8",        VBq, xx, VCq, xx, xx, no, x, tsi6b[0][0x0f]},
    {OP_vneg_s8,        0xf3b103c0, "vneg.s8",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b10400, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10440, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10480, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b104c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b105c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10680, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b106c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10780, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b107c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_8,         0xf3b10c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, tsi6b[0][0x21]},
    {OP_vdup_8,         0xf3b10c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, tfpB[13][0x01]},
    {INVALID,           0xf3b10c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 1 */
    {OP_vswp,           0xf3b20000, "vswp.8",         VBq, xx, VCq, xx, xx, no, x, tsi6b[1][0x01]},
    {OP_vswp,           0xf3b20040, "vswp.8",         VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vtrn_8,         0xf3b20080, "vtrn.8",         VBq, xx, VCq, xx, xx, no, x, tsi6b[1][0x03]},
    {OP_vtrn_8,         0xf3b200c0, "vtrn.8",         VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vuzp_8,         0xf3b20100, "vuzp.8",         VBq, xx, VCq, xx, xx, no, x, tsi6b[1][0x05]},
    {OP_vuzp_8,         0xf3b20140, "vuzp.8",         VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vzip_8,         0xf3b20180, "vzip.8",         VBq, xx, VCq, xx, xx, no, x, tsi6b[1][0x07]},
    {OP_vzip_8,         0xf3b201c0, "vzip.8",         VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vmovn_i16,      0xf3b20200, "vmovn.i16",      VBd, xx, VCdq, xx, xx, no, x, END_LIST},/*XXX: doesn't read entire src*/
    {OP_vqmovun_s16,    0xf3b20240, "vqmovun.s16",    VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_s16,     0xf3b20280, "vqmovn.s16",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_u16,     0xf3b202c0, "vqmovn.u16",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vshll_i8,       0xf3b20300, "vshll.i8",       VBdq, xx, VCq, k8, xx, no, x, END_LIST},
    {INVALID,           0xf3b20340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20380, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b203c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20400, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20440, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20480, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b204c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b20580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b205c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_f16_f32,   0xf3b20600, "vcvt.f16.f32",   VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b10640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10680, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b106c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_f32_f16,   0xf3b20700, "vcvt.f32.f16",   VBdq, xx, VCq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b10740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10780, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b107c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_16,        0xf3b20c00, "vdup.16",        VBq, xx, VCh_q, i2_18, xx, no, x, tsi6b[1][0x21]},
    {OP_vdup_16,        0xf3b20c40, "vdup.16",        VBdq, xx, VCh_q, i2_18, xx, no, x, tfpB[10][0x03]},
    {INVALID,           0xf3b10c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b10cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 2 */
    {OP_vrev64_16,      0xf3b40000, "vrev64.16",      VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x01]},
    {OP_vrev64_16,      0xf3b40040, "vrev64.16",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrev32_16,      0xf3b40080, "vrev32.16",      VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x03]},
    {OP_vrev32_16,      0xf3b400c0, "vrev32.16",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrev16_16,      0xf3b40100, "vrev16.16",      VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x05]},
    {OP_vrev16_16,      0xf3b40140, "vrev16.16",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b40180, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b401c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpaddl_s16,     0xf3b40200, "vpaddl.s16",     VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x09]},
    {OP_vpaddl_s16,     0xf3b40240, "vpaddl.s16",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpaddl_u16,     0xf3b40280, "vpaddl.u16",     VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x0b]},
    {OP_vpaddl_u16,     0xf3b402c0, "vpaddl.u16",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b40300, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b40340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b40380, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b403c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcls_s16,       0xf3b40400, "vcls.s16",       VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x11]},
    {OP_vcls_s16,       0xf3b40440, "vcls.s16",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vclz_i16,       0xf3b40480, "vclz.i16",       VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x13]},
    {OP_vclz_i16,       0xf3b404c0, "vclz.i16",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b40500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b40540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b40580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b405c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpadal_s16,     0xf3b40600, "vpadal.s16",     VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x19]},
    {OP_vpadal_s16,     0xf3b40640, "vpadal.s16",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpadal_u16,     0xf3b40680, "vpadal.u16",     VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x1b]},
    {OP_vpadal_u16,     0xf3b406c0, "vpadal.u16",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqabs_s16,      0xf3b40700, "vqabs.s16",      VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x1d]},
    {OP_vqabs_s16,      0xf3b40740, "vqabs.s16",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqneg_s16,      0xf3b40780, "vqneg.s16",      VBq, xx, VCq, xx, xx, no, x, tsi6b[2][0x1f]},
    {OP_vqneg_s16,      0xf3b407c0, "vqneg.s16",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vdup_32,        0xf3b40c00, "vdup.32",        VBq, xx, VCd_q, i1_19, xx, no, x, tsi6b[2][0x21]},
    {OP_vdup_32,        0xf3b40c40, "vdup.32",        VBdq, xx, VCd_q, i1_19, xx, no, x, tfpB[10][0x01]},
    {INVALID,           0xf3b40c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b40cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 3 */
    {OP_vcgt_s16,       0xf3b50000, "vcgt.s16",       VBq, xx, VCq, k0, xx, no, x, tsi6[1][0x0c]},
    {OP_vcgt_s16,       0xf3b50040, "vcgt.s16",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[1][0x0e]},
    {OP_vcge_s16,       0xf3b50080, "vcge.s16",       VBq, xx, VCq, k0, xx, no, x, tsi6[1][0x0d]},
    {OP_vcge_s16,       0xf3b500c0, "vcge.s16",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[1][0x0f]},
    {OP_vceq_i16,       0xf3b50100, "vceq.i16",       VBq, xx, VCq, k0, xx, no, x, tsi6[7][0x21]},
    {OP_vceq_i16,       0xf3b50140, "vceq.i16",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[7][0x23]},
    {OP_vcle_s16,       0xf3b50180, "vcle.s16",       VBq, xx, VCq, k0, xx, no, x, tsi6b[3][0x07]},
    {OP_vcle_s16,       0xf3b501c0, "vcle.s16",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {OP_vclt_s16,       0xf3b50200, "vclt.s16",       VBq, xx, VCq, k0, xx, no, x, tsi6b[3][0x09]},
    {OP_vclt_s16,       0xf3b50240, "vclt.s16",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {INVALID,           0xf3b50280, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b502c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabs_s16,       0xf3b50300, "vabs.s16",       VBq, xx, VCq, xx, xx, no, x, tsi6b[3][0x0d]},
    {OP_vabs_s16,       0xf3b50340, "vabs.s16",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vneg_s16,       0xf3b50380, "vneg.s16",       VBq, xx, VCq, xx, xx, no, x, tsi6b[3][0x0f]},
    {OP_vneg_s16,       0xf3b503c0, "vneg.s16",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b50400, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50440, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50480, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b504c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b505c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50680, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b506c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50780, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b507c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_8,         0xf3b50c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3b50c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3b50c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b50cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 4 */
    {INVALID,           0xf3b60000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vtrn_16,        0xf3b60080, "vtrn.16",        VBq, xx, VCq, xx, xx, no, x, tsi6b[4][0x03]},
    {OP_vtrn_16,        0xf3b600c0, "vtrn.16",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vuzp_16,        0xf3b60100, "vuzp.16",        VBq, xx, VCq, xx, xx, no, x, tsi6b[4][0x05]},
    {OP_vuzp_16,        0xf3b60140, "vuzp.16",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vzip_16,        0xf3b60180, "vzip.16",        VBq, xx, VCq, xx, xx, no, x, tsi6b[4][0x07]},
    {OP_vzip_16,        0xf3b601c0, "vzip.16",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vmovn_i32,      0xf3b60200, "vmovn.i32",      VBd, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovun_s32,    0xf3b60240, "vqmovun.s32",    VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_s32,     0xf3b60280, "vqmovn.s32",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_u32,     0xf3b602c0, "vqmovn.u32",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vshll_i16,      0xf3b60300, "vshll.i16",      VBdq, xx, VCq, k16, xx, no, x, END_LIST},
    {INVALID,           0xf3b60340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60380, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b603c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60400, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60440, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60480, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b604c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b605c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60680, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b606c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60780, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b607c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_16,        0xf3b60c00, "vdup.16",        VBq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
    {OP_vdup_16,        0xf3b60c40, "vdup.16",        VBdq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3b60c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b60cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 5 */
    {OP_vrev64_32,      0xf3b80000, "vrev64.32",      VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x01]},
    {OP_vrev64_32,      0xf3b80040, "vrev64.32",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrev32_32,      0xf3b80080, "vrev32.32",      VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x03]},
    {OP_vrev32_32,      0xf3b800c0, "vrev32.32",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b80100, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80140, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80180, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b801c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpaddl_s32,     0xf3b80200, "vpaddl.s32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x09]},
    {OP_vpaddl_s32,     0xf3b80240, "vpaddl.s32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpaddl_u32,     0xf3b80280, "vpaddl.u32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x0b]},
    {OP_vpaddl_u32,     0xf3b802c0, "vpaddl.u32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b80300, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80380, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b803c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcls_s32,       0xf3b80400, "vcls.s32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x11]},
    {OP_vcls_s32,       0xf3b80440, "vcls.s32",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vclz_i32,       0xf3b80480, "vclz.i32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x13]},
    {OP_vclz_i32,       0xf3b804c0, "vclz.i32",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b80500, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80540, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80580, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b805c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpadal_s32,     0xf3b80600, "vpadal.s32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x19]},
    {OP_vpadal_s32,     0xf3b80640, "vpadal.s32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpadal_u32,     0xf3b80680, "vpadal.u32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x1b]},
    {OP_vpadal_u32,     0xf3b806c0, "vpadal.u32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqabs_s32,      0xf3b80700, "vqabs.s32",      VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x1d]},
    {OP_vqabs_s32,      0xf3b80740, "vqabs.s32",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqneg_s32,      0xf3b80780, "vqneg.s32",      VBq, xx, VCq, xx, xx, no, x, tsi6b[5][0x1f]},
    {OP_vqneg_s32,      0xf3b807c0, "vqneg.s32",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b80c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80c40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b80cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 6 */
    {OP_vcgt_s32,       0xf3b90000, "vcgt.s32",       VBq, xx, VCq, k0, xx, no, x, tsi6[2][0x0c]},
    {OP_vcgt_s32,       0xf3b90040, "vcgt.s32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[2][0x0e]},
    {OP_vcge_s32,       0xf3b90080, "vcge.s32",       VBq, xx, VCq, k0, xx, no, x, tsi6[2][0x0d]},
    {OP_vcge_s32,       0xf3b900c0, "vcge.s32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[2][0x0f]},
    {OP_vceq_i32,       0xf3b90100, "vceq.i32",       VBq, xx, VCq, k0, xx, no, x, tsi6[8][0x21]},
    {OP_vceq_i32,       0xf3b90140, "vceq.i32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[8][0x23]},
    {OP_vcle_s32,       0xf3b90180, "vcle.s32",       VBq, xx, VCq, k0, xx, no, x, tsi6b[6][0x07]},
    {OP_vcle_s32,       0xf3b901c0, "vcle.s32",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {OP_vclt_s32,       0xf3b90200, "vclt.s32",       VBq, xx, VCq, k0, xx, no, x, tsi6b[6][0x09]},
    {OP_vclt_s32,       0xf3b90240, "vclt.s32",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {OP_sha1h_32,       0xf3b902c0, "sha1h.32",       VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_vabs_s32,       0xf3b90300, "vabs.s32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[6][0x0c]},
    {OP_vabs_s32,       0xf3b90340, "vabs.s32",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vneg_s32,       0xf3b90380, "vneg.s32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[6][0x0e]},
    {OP_vneg_s32,       0xf3b903c0, "vneg.s32",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vcgt_f32,       0xf3b90400, "vcgt.f32",       VBq, xx, VCq, k0, xx, no, x, tsi6[8][0x38]},
    {OP_vcgt_f32,       0xf3b90440, "vcgt.f32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[8][0x3a]},
    {OP_vcge_f32,       0xf3b90480, "vcge.f32",       VBq, xx, VCq, k0, xx, no, x, tsi6[6][0x35]},
    {OP_vcge_f32,       0xf3b904c0, "vcge.f32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[6][0x37]},
    {OP_vceq_f32,       0xf3b90500, "vceq.f32",       VBq, xx, VCq, k0, xx, no, x, tsi6[0][0x38]},
    {OP_vceq_f32,       0xf3b90540, "vceq.f32",       VBdq, xx, VCdq, k0, xx, no, x, tsi6[0][0x3a]},
    {OP_vcle_f32,       0xf3b90580, "vcle.f32",       VBq, xx, VCq, k0, xx, no, x, tsi6b[6][0x16]},
    {OP_vcle_f32,       0xf3b905c0, "vcle.f32",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {OP_vclt_f32,       0xf3b90600, "vclt.f32",       VBq, xx, VCq, k0, xx, no, x, tsi6b[6][0x18]},
    {OP_vclt_f32,       0xf3b90640, "vclt.f32",       VBdq, xx, VCdq, k0, xx, no, x, END_LIST},
    {INVALID,           0xf3b90680, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b906c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vabs_f32,       0xf3b90700, "vabs.f32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[6][0x1c]},
    {OP_vabs_f32,       0xf3b90740, "vabs.f32",       VBdq, xx, VCdq, xx, xx, no, x, t16[1][0x00]},
    {OP_vneg_f32,       0xf3b90780, "vneg.f32",       VBq, xx, VCq, xx, xx, no, x, tsi6b[6][0x1e]},
    {OP_vneg_f32,       0xf3b907c0, "vneg.f32",       VBdq, xx, VCdq, xx, xx, no, x, t16[0][0x01]},
    {OP_vdup_8,         0xf3b90c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3b90c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3b90c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b90cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 7 */
    {INVALID,           0xf3ba0000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3ba0040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vtrn_32,        0xf3ba0080, "vtrn.32",        VBq, xx, VCq, xx, xx, no, x, tsi6b[7][0x03]},
    {OP_vtrn_32,        0xf3ba00c0, "vtrn.32",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vuzp_32,        0xf3ba0100, "vuzp.32",        VBq, xx, VCq, xx, xx, no, x, tsi6b[7][0x05]},
    {OP_vuzp_32,        0xf3ba0140, "vuzp.32",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vzip_32,        0xf3ba0180, "vzip.32",        VBq, xx, VCq, xx, xx, no, x, tsi6b[7][0x07]},
    {OP_vzip_32,        0xf3ba01c0, "vzip.32",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vmovn_i64,      0xf3ba0200, "vmovn.i64",      VBd, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovun_s64,    0xf3ba0240, "vqmovun.s64",    VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_s64,     0xf3ba0280, "vqmovn.s64",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqmovn_u64,     0xf3ba02c0, "vqmovn.u64",     VBq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vshll_i32,      0xf3ba0300, "vshll.i32",      VBdq, xx, VCq, k32, xx, no, x, END_LIST},
    {INVALID,           0xf3ba0340, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_sha1su1_32,     0xf3ba0380, "sha1su1.32",     VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_sha256su0_32,   0xf3ba03c0, "sha256su0.32",   VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_vrintn_f32_f32, 0xf3ba0400, "vrintn.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x11]},
    {OP_vrintn_f32_f32, 0xf3ba0440, "vrintn.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x04]},
    {OP_vrintx_f32_f32, 0xf3ba0480, "vrintx.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x13]},
    {OP_vrintx_f32_f32, 0xf3ba04c0, "vrintx.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_vrinta_f32_f32, 0xf3ba0500, "vrinta.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x15]},
    {OP_vrinta_f32_f32, 0xf3ba0540, "vrinta.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x00]},
    {OP_vrintz_f32_f32, 0xf3ba0580, "vrintz.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x17]},
    {OP_vrintz_f32_f32, 0xf3ba05c0, "vrintz.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {INVALID,           0xf3ba0600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3ba0640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintm_f32_f32, 0xf3ba0680, "vrintm.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x1b]},
    {OP_vrintm_f32_f32, 0xf3ba06c0, "vrintm.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x0c]},
    {INVALID,           0xf3ba0700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3ba0740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vrintp_f32_f32, 0xf3ba0780, "vrintp.f32.f32", VBq, xx, VCq, xx, xx, v8, x, tsi6b[7][0x1f]},
    {OP_vrintp_f32_f32, 0xf3ba07c0, "vrintp.f32.f32", VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x08]},
    {OP_vdup_16,        0xf3ba0c00, "vdup.16",        VBq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
    {OP_vdup_16,        0xf3ba0c40, "vdup.16",        VBdq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3ba0c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3ba0cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 8 */
    {OP_vcvta_s32_f32,  0xf3bb0000, "vcvta.s32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x01]},
    {OP_vcvta_s32_f32,  0xf3bb0040, "vcvta.s32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x11]},
    {OP_vcvta_u32_f32,  0xf3bb0080, "vcvta.u32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x03]},
    {OP_vcvta_u32_f32,  0xf3bb00c0, "vcvta.u32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x10]},
    {OP_vcvtn_s32_f32,  0xf3bb0100, "vcvtn.s32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x05]},
    {OP_vcvtn_s32_f32,  0xf3bb0140, "vcvtn.s32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x15]},
    {OP_vcvtn_u32_f32,  0xf3bb0180, "vcvtn.u32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x07]},
    {OP_vcvtn_u32_f32,  0xf3bb01c0, "vcvtn.u32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x14]},
    {OP_vcvtp_s32_f32,  0xf3bb0200, "vcvtp.s32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x09]},
    {OP_vcvtp_s32_f32,  0xf3bb0240, "vcvtp.s32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x19]},
    {OP_vcvtp_u32_f32,  0xf3bb0280, "vcvtp.u32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x0b]},
    {OP_vcvtp_u32_f32,  0xf3bb02c0, "vcvtp.u32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x18]},
    {OP_vcvtm_s32_f32,  0xf3bb0300, "vcvtm.s32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x0d]},
    {OP_vcvtm_s32_f32,  0xf3bb0340, "vcvtm.s32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x1d]},
    {OP_vcvtm_u32_f32,  0xf3bb0380, "vcvtm.u32.f32",  VBq, xx, VCq, xx, xx, v8, x, tsi6b[8][0x0f]},
    {OP_vcvtm_u32_f32,  0xf3bb03c0, "vcvtm.u32.f32",  VBdq, xx, VCdq, xx, xx, v8, x, tsi5b[0][0x1c]},
    {OP_vrecpe_u32,     0xf3bb0400, "vrecpe.u32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[8][0x11]},
    {OP_vrecpe_u32,     0xf3bb0440, "vrecpe.u32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrsqrte_u32,    0xf3bb0480, "vrsqrte.u32",    VBq, xx, VCq, xx, xx, no, x, tsi6b[8][0x13]},
    {OP_vrsqrte_u32,    0xf3bb04c0, "vrsqrte.u32",    VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrecpe_f32,     0xf3bb0500, "vrecpe.f32",     VBq, xx, VCq, xx, xx, no, x, tsi6b[8][0x15]},
    {OP_vrecpe_f32,     0xf3bb0540, "vrecpe.f32",     VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrsqrte_f32,    0xf3bb0580, "vrsqrte.f32",    VBq, xx, VCq, xx, xx, no, x, tsi6b[8][0x17]},
    {OP_vrsqrte_f32,    0xf3bb05c0, "vrsqrte.f32",    VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3bb0600, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bb0640, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vcvt_s32_f32,   0xf3bb0680, "vcvt.s32.f32",   VBq, xx, VCq, xx, xx, no, x, tsi6[5][0x3c]},
    {OP_vcvt_s32_f32,   0xf3bb06c0, "vcvt.s32.f32",   VBdq, xx, VCdq, xx, xx, no, x, tsi6[5][0x3e]},
    {INVALID,           0xf3bb0700, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bb0740, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bb0780, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bb07c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_8,         0xf3bb0c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3bb0c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {INVALID,           0xf3bb0c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bb0cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 9 */
    {OP_vrev64_8,       0xf3b00000, "vrev64.8",       VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x01]},
    {OP_vrev64_8,       0xf3b00040, "vrev64.8",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrev32_8,       0xf3b00080, "vrev32.8",       VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x03]},
    {OP_vrev32_8,       0xf3b000c0, "vrev32.8",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vrev16_8,       0xf3b00100, "vrev16.8",       VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x05]},
    {OP_vrev16_8,       0xf3b00140, "vrev16.8",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b00180, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b001c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vpaddl_s8,      0xf3b00200, "vpaddl.s8",      VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x09]},
    {OP_vpaddl_s8,      0xf3b00240, "vpaddl.s8",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpaddl_u8,      0xf3b00280, "vpaddl.u8",      VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x0b]},
    {OP_vpaddl_u8,      0xf3b002c0, "vpaddl.u8",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_aese_8,         0xf3b00300, "aese.8",         VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_aesd_8,         0xf3b00340, "aesd.8",         VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_aesmc_8,        0xf3b00380, "aesmc.8",        VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_aesimc_8,       0xf3b003c0, "aesimc.8",       VBdq, xx, VCdq, xx, xx, v8, x, END_LIST},
    {OP_vcls_s8,        0xf3b00400, "vcls.s8",        VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x11]},
    {OP_vcls_s8,        0xf3b00440, "vcls.s8",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vclz_i8,        0xf3b00480, "vclz.i8",        VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x13]},
    {OP_vclz_i8,        0xf3b004c0, "vclz.i8",        VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vcnt_8,         0xf3b00500, "vcnt.8",         VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x15]},
    {OP_vcnt_8,         0xf3b00540, "vcnt.8",         VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vmvn,           0xf3b00580, "vmvn",           VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x17]},
    {OP_vmvn,           0xf3b005c0, "vmvn",           VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpadal_s8,      0xf3b00600, "vpadal.s8",      VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x19]},
    {OP_vpadal_s8,      0xf3b00640, "vpadal.s8",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vpadal_u8,      0xf3b00680, "vpadal.u8",      VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x1b]},
    {OP_vpadal_u8,      0xf3b006c0, "vpadal.u8",      VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqabs_s8,       0xf3b00700, "vqabs.s8",       VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x1d]},
    {OP_vqabs_s8,       0xf3b00740, "vqabs.s8",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {OP_vqneg_s8,       0xf3b00780, "vqneg.s8",       VBq, xx, VCq, xx, xx, no, x, tsi6b[9][0x1f]},
    {OP_vqneg_s8,       0xf3b007c0, "vqneg.s8",       VBdq, xx, VCdq, xx, xx, no, x, END_LIST},
    {INVALID,           0xf3b00c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b00c40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b00c80, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3b00cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  },
};

/* Indexed by bits 11,6 (0x......840) */
const instr_info_t A32_ext_simd2[][4] = {
  { /* 0 */
    {OP_vcvt_f32_s32,   0xf3b30680, "vcvt.f32.s32",   VBq, xx, VCq, xx, xx, no, x, tsi6[5][0x39]},
    {OP_vcvt_f32_s32,   0xf3b306c0, "vcvt.f32.s32",   VBdq, xx, VCdq, xx, xx, no, x, tsi6[5][0x3b]},
    {OP_vdup_8,         0xf3b30c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3b30c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
  }, { /* 1 */
    {OP_vcvt_f32_u32,   0xf3b70680, "vcvt.f32.u32",   VBq, xx, VCq, xx, xx, no, x, tsi6[11][0x39]},
    {OP_vcvt_f32_u32,   0xf3b706c0, "vcvt.f32.u32",   VBdq, xx, VCdq, xx, xx, no, x, tsi6[11][0x3b]},
    {OP_vdup_8,         0xf3b70c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3b70c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
  }, { /* 2 */
    {INVALID,           0xf3bc0000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bc0040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_32,        0xf3bc0c00, "vdup.32",        VBq, xx, VCd_q, i1_19, xx, no, x, DUP_ENTRY},
    {OP_vdup_32,        0xf3bc0c40, "vdup.32",        VBdq, xx, VCd_q, i1_19, xx, no, x, DUP_ENTRY},
  }, { /* 3 */
    {INVALID,           0xf3bd0000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3bd0040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_8,         0xf3bd0c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3bd0c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
  }, { /* 4 */
    {INVALID,           0xf3be0000, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf3be0040, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vdup_16,        0xf3be0c00, "vdup.16",        VBq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
    {OP_vdup_16,        0xf3be0c40, "vdup.16",        VBdq, xx, VCh_q, i2_18, xx, no, x, DUP_ENTRY},
  }, { /* 5 */
    {OP_vcvt_u32_f32,   0xf3bf0680, "vcvt.u32.f32",   VBq, xx, VCq, xx, xx, no, x, tsi6[11][0x3d]},
    {OP_vcvt_u32_f32,   0xf3bf06c0, "vcvt.u32.f32",   VBdq, xx, VCdq, xx, xx, no, x, tsi6[11][0x3f]},
    {OP_vdup_8,         0xf3bf0c00, "vdup.8",         VBq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
    {OP_vdup_8,         0xf3bf0c40, "vdup.8",         VBdq, xx, VCb_q, i3_17, xx, no, x, DUP_ENTRY},
  },
};

/* Indexed by bits 10:8,6.  Bits 4 and 7 are already set.  These have
 * i6_16 with the L bit which means their upper bits can vary quite a bit.
 */
const instr_info_t A32_ext_imm6L[][16] = {
  { /* 0 */
    {OP_vshr_s64,       0xf2800090, "vshr.s64",       VBq, xx, VCq, i6_16, xx, no, x, ti6l[0][0x01]},/*XXX: imm = 64-imm*/
    {OP_vshr_s64,       0xf28000d0, "vshr.s64",       VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vsra_s64,       0xf2800190, "vsra.s64",       VBq, xx, VCq, i6_16, xx, no, x, ti6l[0][0x03]},/*XXX: imm = 64-imm*/
    {OP_vsra_s64,       0xf28001d0, "vsra.s64",       VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vrshr_s64,      0xf2800290, "vrshr.s64",      VBq, xx, VCq, i6_16, xx, no, x, ti6l[0][0x05]},/*XXX: imm = 64-imm*/
    {OP_vrshr_s64,      0xf28002d0, "vrshr.s64",      VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vrsra_s64,      0xf2800390, "vrsra.s64",      VBq, xx, VCq, i6_16, xx, no, x, ti6l[0][0x07]},/*XXX: imm = 64-imm*/
    {OP_vrsra_s64,      0xf28003d0, "vrsra.s64",      VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {INVALID,           0xf2800490, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf28004d0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vshl_i64,       0xf2800590, "vshl.i64",       VBq, xx, VCq, i6_16, xx, no, x, ti6l[0][0x0b]},/*XXX: imm = 64-imm?*/
    {OP_vshl_i64,       0xf28005d0, "vshl.i64",       VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm?*/
    {INVALID,           0xf2800690, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf28006d0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshl_s64,      0xf2800790, "vqshl.s64",      VBq, xx, VCq, i6_16, xx, no, x, tsi6[3][0x11]},
    {OP_vqshl_s64,      0xf28007d0, "vqshl.s64",      VBdq, xx, VCdq, i6_16, xx, no, x, tsi6[3][0x13]},
  }, { /* 1 */
    {OP_vshr_u64,       0xf3800090, "vshr.u64",       VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x01]},/*XXX: imm = 64-imm*/
    {OP_vshr_u64,       0xf38000d0, "vshr.u64",       VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vsra_u64,       0xf3800190, "vsra.u64",       VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x03]},/*XXX: imm = 64-imm*/
    {OP_vsra_u64,       0xf38001d0, "vsra.u64",       VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vrshr_u64,      0xf3800290, "vrshr.u64",      VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x05]},/*XXX: imm = 64-imm*/
    {OP_vrshr_u64,      0xf38002d0, "vrshr.u64",      VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vrsra_u64,      0xf3800390, "vrsra.u64",      VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x07]},/*XXX: imm = 64-imm*/
    {OP_vrsra_u64,      0xf38003d0, "vrsra.u64",      VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm*/
    {OP_vsri_64,        0xf3800490, "vsri.64",        VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x09]},/*XXX: imm = 64-imm?*/
    {OP_vsri_64,        0xf38004d0, "vsri.64",        VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm?*/
    {OP_vsli_64,        0xf3800590, "vsli.64",        VBq, xx, VCq, i6_16, xx, no, x, ti6l[1][0x0b]},/*XXX: imm = 64-imm?*/
    {OP_vsli_64,        0xf38005d0, "vsli.64",        VBdq, xx, VCdq, i6_16, xx, no, x, END_LIST},/*XXX: imm = 64-imm?*/
    {OP_vqshlu_s64,     0xf3800690, "vqshlu.s64",     VBq, xx, VCq, i6_16, xx, no, x, tsi6[6][0x1c]},
    {INVALID,           0xf38006d0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vqshl_u64,      0xf3800790, "vqshl.u64",      VBq, xx, VCq, i6_16, xx, no, x, tsi6[9][0x11]},
    {OP_vqshl_u64,      0xf38007d0, "vqshl.u64",      VBdq, xx, VCdq, i6_16, xx, no, x, tsi6[9][0x13]},
  },
};

/* Indexed by bits (11:8,7:6)*3+X where X is based on the value of 3:0:
 * + 0xd => 0
 * + 0xf => 1
 * + else => 2
 * However, the top 11:8 stops at 0xa.
 */
const instr_info_t A32_ext_vldA[][132] = {
  { /* 0 */
    {OP_vst4_8,         0xf400000d, "vst4.8",         Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst4_8,         0xf400000f, "vst4.8",         Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x00]},
    {OP_vst4_8,         0xf4000000, "vst4.8",         Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x01]},
    {OP_vst4_16,        0xf400004d, "vst4.16",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst4_16,        0xf400004f, "vst4.16",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x03]},
    {OP_vst4_16,        0xf4000040, "vst4.16",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x04]},
    {OP_vst4_32,        0xf400008d, "vst4.32",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst4_32,        0xf400008f, "vst4.32",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x06]},
    {OP_vst4_32,        0xf4000080, "vst4.32",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x07]},
    {INVALID,           0xf40000cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40000cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40000c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst4_8,         0xf400010d, "vst4.8",         Mqq, RAw, LX4Dq, i2_4, RAw, no, x, tvlA[0][0x02]},
    {OP_vst4_8,         0xf400010f, "vst4.8",         Mqq, xx, LX4Dq, i2_4, xx, no, x, tvlA[0][0x0c]},
    {OP_vst4_8,         0xf4000100, "vst4.8",         Mqq, RAw, LX4Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x0d]},
    {OP_vst4_16,        0xf400014d, "vst4.16",        Mqq, RAw, LX4Dq, i2_4, RAw, no, x, tvlA[0][0x05]},
    {OP_vst4_16,        0xf400014f, "vst4.16",        Mqq, xx, LX4Dq, i2_4, xx, no, x, tvlA[0][0x0f]},
    {OP_vst4_16,        0xf4000140, "vst4.16",        Mqq, RAw, LX4Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x10]},
    {OP_vst4_32,        0xf400018d, "vst4.32",        Mqq, RAw, LX4Dq, i2_4, RAw, no, x, tvlA[0][0x08]},
    {OP_vst4_32,        0xf400018f, "vst4.32",        Mqq, xx, LX4Dq, i2_4, xx, no, x, tvlA[0][0x12]},
    {OP_vst4_32,        0xf4000180, "vst4.32",        Mqq, RAw, LX4Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x13]},
    {INVALID,           0xf40001cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40001cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40001c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst1_8,         0xf400020d, "vst1.8",         Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst1_8,         0xf400020f, "vst1.8",         Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x18]},
    {OP_vst1_8,         0xf4000200, "vst1.8",         Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x19]},
    {OP_vst1_16,        0xf400024d, "vst1.16",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst1_16,        0xf400024f, "vst1.16",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x1b]},
    {OP_vst1_16,        0xf4000240, "vst1.16",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x1c]},
    {OP_vst1_32,        0xf400028d, "vst1.32",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst1_32,        0xf400028f, "vst1.32",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x1e]},
    {OP_vst1_32,        0xf4000280, "vst1.32",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x1f]},
    {OP_vst1_64,        0xf40002cd, "vst1.64",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst1_64,        0xf40002cf, "vst1.64",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x21]},
    {OP_vst1_64,        0xf40002c0, "vst1.64",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x22]},
    {OP_vst2_8,         0xf400030d, "vst2.8",         Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst2_8,         0xf400030f, "vst2.8",         Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x24]},
    {OP_vst2_8,         0xf4000300, "vst2.8",         Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x25]},
    {OP_vst2_16,        0xf400034d, "vst2.16",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst2_16,        0xf400034f, "vst2.16",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x27]},
    {OP_vst2_16,        0xf4000340, "vst2.16",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x28]},
    {OP_vst2_32,        0xf400038d, "vst2.32",        Mqq, RAw, LX4q, i2_4, RAw, no, x, END_LIST},
    {OP_vst2_32,        0xf400038f, "vst2.32",        Mqq, xx, LX4q, i2_4, xx, no, x, tvlA[0][0x2a]},
    {OP_vst2_32,        0xf4000380, "vst2.32",        Mqq, RAw, LX4q, i2_4, RDw, xop_wb, x, tvlA[0][0x2b]},
    {INVALID,           0xf40003cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40003cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40003c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst3_8,         0xf400040d, "vst3.8",         M24, RAw, LX3q, i2_4, RAw, no, x, END_LIST},
    {OP_vst3_8,         0xf400040f, "vst3.8",         M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x30]},
    {OP_vst3_8,         0xf4000400, "vst3.8",         M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x31]},
    {OP_vst3_16,        0xf400044d, "vst3.16",        M24, RAw, LX3q, i2_4, RAw, no, x, END_LIST},
    {OP_vst3_16,        0xf400044f, "vst3.16",        M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x33]},
    {OP_vst3_16,        0xf4000440, "vst3.16",        M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x34]},
    {OP_vst3_32,        0xf400048d, "vst3.32",        M24, RAw, LX3q, i2_4, RAw, no, x, END_LIST},
    {OP_vst3_32,        0xf400048f, "vst3.32",        M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x36]},
    {OP_vst3_32,        0xf4000480, "vst3.32",        M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x37]},
    {INVALID,           0xf40004cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40004cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40004c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst3_8,         0xf400050d, "vst3.8",         M24, RAw, LX3Dq, i2_4, RAw, no, x, tvlA[0][0x32]},
    {OP_vst3_8,         0xf400050f, "vst3.8",         M24, xx, LX3Dq, i2_4, xx, no, x, tvlA[0][0x3c]},
    {OP_vst3_8,         0xf4000500, "vst3.8",         M24, RAw, LX3Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x3d]},
    {OP_vst3_16,        0xf400054d, "vst3.16",        M24, RAw, LX3Dq, i2_4, RAw, no, x, tvlA[0][0x35]},
    {OP_vst3_16,        0xf400054f, "vst3.16",        M24, xx, LX3Dq, i2_4, xx, no, x, tvlA[0][0x3f]},
    {OP_vst3_16,        0xf4000540, "vst3.16",        M24, RAw, LX3Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x40]},
    {OP_vst3_32,        0xf400058d, "vst3.32",        M24, RAw, LX3Dq, i2_4, RAw, no, x, tvlA[0][0x38]},
    {OP_vst3_32,        0xf400058f, "vst3.32",        M24, xx, LX3Dq, i2_4, xx, no, x, tvlA[0][0x42]},
    {OP_vst3_32,        0xf4000580, "vst3.32",        M24, RAw, LX3Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x43]},
    {INVALID,           0xf40005cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40005cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40005c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst1_8,         0xf400060d, "vst1.8",         M24, RAw, LX3q, i2_4, RAw, no, x, tvlA[0][0x1a]},
    {OP_vst1_8,         0xf400060f, "vst1.8",         M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x48]},
    {OP_vst1_8,         0xf4000600, "vst1.8",         M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x49]},
    {OP_vst1_16,        0xf400064d, "vst1.16",        M24, RAw, LX3q, i2_4, RAw, no, x, tvlA[0][0x1d]},
    {OP_vst1_16,        0xf400064f, "vst1.16",        M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x4b]},
    {OP_vst1_16,        0xf4000640, "vst1.16",        M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x4c]},
    {OP_vst1_32,        0xf400068d, "vst1.32",        M24, RAw, LX3q, i2_4, RAw, no, x, tvlA[0][0x20]},
    {OP_vst1_32,        0xf400068f, "vst1.32",        M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x4e]},
    {OP_vst1_32,        0xf4000680, "vst1.32",        M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x4f]},
    {OP_vst1_64,        0xf40006cd, "vst1.64",        M24, RAw, LX3q, i2_4, RAw, no, x, tvlA[0][0x23]},
    {OP_vst1_64,        0xf40006cf, "vst1.64",        M24, xx, LX3q, i2_4, xx, no, x, tvlA[0][0x51]},
    {OP_vst1_64,        0xf40006c0, "vst1.64",        M24, RAw, LX3q, i2_4, RDw, xop_wb, x, tvlA[0][0x52]},
    {OP_vst1_8,         0xf400070d, "vst1.8",         Mq, RAw, VBq, i2_4, RAw, no, x, tvlA[0][0x7a]},/*XXX: some align values => undefined*/
    {OP_vst1_8,         0xf400070f, "vst1.8",         Mq, xx, VBq, i2_4, xx, no, x, tvlA[0][0x54]},/*XXX: combine align into memop?*/
    {OP_vst1_8,         0xf4000700, "vst1.8",         Mq, RAw, VBq, i2_4, RDw, xop_wb, x, tvlA[0][0x55]},
    {OP_vst1_16,        0xf400074d, "vst1.16",        Mq, RAw, VBq, i2_4, RAw, no, x, tvlA[0][0x7d]},
    {OP_vst1_16,        0xf400074f, "vst1.16",        Mq, xx, VBq, i2_4, xx, no, x, tvlA[0][0x57]},
    {OP_vst1_16,        0xf4000740, "vst1.16",        Mq, RAw, VBq, i2_4, RDw, xop_wb, x, tvlA[0][0x58]},
    {OP_vst1_32,        0xf400078d, "vst1.32",        Mq, RAw, VBq, i2_4, RAw, no, x, tvlA[0][0x80]},
    {OP_vst1_32,        0xf400078f, "vst1.32",        Mq, xx, VBq, i2_4, xx, no, x, tvlA[0][0x5a]},
    {OP_vst1_32,        0xf4000780, "vst1.32",        Mq, RAw, VBq, i2_4, RDw, xop_wb, x, tvlA[0][0x5b]},
    {OP_vst1_64,        0xf40007cd, "vst1.64",        Mq, RAw, VBq, i2_4, RAw, no, x, tvlA[0][0x83]},
    {OP_vst1_64,        0xf40007cf, "vst1.64",        Mq, xx, VBq, i2_4, xx, no, x, tvlA[0][0x5d]},
    {OP_vst1_64,        0xf40007c0, "vst1.64",        Mq, RAw, VBq, i2_4, RDw, xop_wb, x, tvlA[0][0x5e]},
    /* 0x80 */
    {OP_vst2_8,         0xf400080d, "vst2.8",         Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x26]},
    {OP_vst2_8,         0xf400080f, "vst2.8",         Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x60]},
    {OP_vst2_8,         0xf4000800, "vst2.8",         Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x61]},
    {OP_vst2_16,        0xf400084d, "vst2.16",        Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x29]},
    {OP_vst2_16,        0xf400084f, "vst2.16",        Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x63]},
    {OP_vst2_16,        0xf4000840, "vst2.16",        Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x64]},
    {OP_vst2_32,        0xf400088d, "vst2.32",        Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x2c]},
    {OP_vst2_32,        0xf400088f, "vst2.32",        Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x66]},
    {OP_vst2_32,        0xf4000880, "vst2.32",        Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x67]},
    {INVALID,           0xf40008cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40008cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40008c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst2_8,         0xf400090d, "vst2.8",         Mdq, RAw, LX2Dq, i2_4, RAw, no, x, tvlA[0][0x62]},
    {OP_vst2_8,         0xf400090f, "vst2.8",         Mdq, xx, LX2Dq, i2_4, xx, no, x, tvlA[0][0x6c]},
    {OP_vst2_8,         0xf4000900, "vst2.8",         Mdq, RAw, LX2Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x6d]},
    {OP_vst2_16,        0xf400094d, "vst2.16",        Mdq, RAw, LX2Dq, i2_4, RAw, no, x, tvlA[0][0x65]},
    {OP_vst2_16,        0xf400094f, "vst2.16",        Mdq, xx, LX2Dq, i2_4, xx, no, x, tvlA[0][0x6f]},
    {OP_vst2_16,        0xf4000940, "vst2.16",        Mdq, RAw, LX2Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x70]},
    {OP_vst2_32,        0xf400098d, "vst2.32",        Mdq, RAw, LX2Dq, i2_4, RAw, no, x, tvlA[0][0x68]},
    {OP_vst2_32,        0xf400098f, "vst2.32",        Mdq, xx, LX2Dq, i2_4, xx, no, x, tvlA[0][0x72]},
    {OP_vst2_32,        0xf4000980, "vst2.32",        Mdq, RAw, LX2Dq, i2_4, RDw, xop_wb, x, tvlA[0][0x73]},
    {INVALID,           0xf40009cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40009cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf40009c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vst1_8,         0xf4000a0d, "vst1.8",         Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x4a]},
    {OP_vst1_8,         0xf4000a0f, "vst1.8",         Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x78]},
    {OP_vst1_8,         0xf4000a00, "vst1.8",         Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x79]},
    {OP_vst1_16,        0xf4000a4d, "vst1.16",        Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x4d]},
    {OP_vst1_16,        0xf4000a4f, "vst1.16",        Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x7b]},
    {OP_vst1_16,        0xf4000a40, "vst1.16",        Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x7c]},
    {OP_vst1_32,        0xf4000a8d, "vst1.32",        Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x50]},
    {OP_vst1_32,        0xf4000a8f, "vst1.32",        Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x7e]},
    {OP_vst1_32,        0xf4000a80, "vst1.32",        Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x7f]},
    {OP_vst1_64,        0xf4000acd, "vst1.64",        Mdq, RAw, LX2q, i2_4, RAw, no, x, tvlA[0][0x53]},
    {OP_vst1_64,        0xf4000acf, "vst1.64",        Mdq, xx, LX2q, i2_4, xx, no, x, tvlA[0][0x81]},
    {OP_vst1_64,        0xf4000ac0, "vst1.64",        Mdq, RAw, LX2q, i2_4, RDw, xop_wb, x, tvlA[0][0x82]},
  }, { /* 1 */
    {OP_vld4_8,         0xf420000d, "vld4.8",         LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld4_8,         0xf420000f, "vld4.8",         LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x00]},
    {OP_vld4_8,         0xf4200000, "vld4.8",         LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x01]},
    {OP_vld4_16,        0xf420004d, "vld4.16",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld4_16,        0xf420004f, "vld4.16",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x03]},
    {OP_vld4_16,        0xf4200040, "vld4.16",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x04]},
    {OP_vld4_32,        0xf420008d, "vld4.32",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld4_32,        0xf420008f, "vld4.32",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x06]},
    {OP_vld4_32,        0xf4200080, "vld4.32",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x07]},
    {INVALID,           0xf42000cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42000cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42000c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld4_8,         0xf420010d, "vld4.8",         LX4Dq, RAw, Mqq, i2_4, RAw, no, x, tvlA[1][0x02]},
    {OP_vld4_8,         0xf420010f, "vld4.8",         LX4Dq, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x0c]},
    {OP_vld4_8,         0xf4200100, "vld4.8",         LX4Dq, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x0d]},
    {OP_vld4_16,        0xf420014d, "vld4.16",        LX4Dq, RAw, Mqq, i2_4, RAw, no, x, tvlA[1][0x05]},
    {OP_vld4_16,        0xf420014f, "vld4.16",        LX4Dq, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x0f]},
    {OP_vld4_16,        0xf4200140, "vld4.16",        LX4Dq, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x10]},
    {OP_vld4_32,        0xf420018d, "vld4.32",        LX4Dq, RAw, Mqq, i2_4, RAw, no, x, tvlA[1][0x08]},
    {OP_vld4_32,        0xf420018f, "vld4.32",        LX4Dq, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x12]},
    {OP_vld4_32,        0xf4200180, "vld4.32",        LX4Dq, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x13]},
    {INVALID,           0xf42001cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42001cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42001c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld1_8,         0xf420020d, "vld1.8",         LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld1_8,         0xf420020f, "vld1.8",         LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x18]},
    {OP_vld1_8,         0xf4200200, "vld1.8",         LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x19]},
    {OP_vld1_16,        0xf420024d, "vld1.16",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld1_16,        0xf420024f, "vld1.16",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x1b]},
    {OP_vld1_16,        0xf4200240, "vld1.16",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x1c]},
    {OP_vld1_32,        0xf420028d, "vld1.32",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld1_32,        0xf420028f, "vld1.32",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x1e]},
    {OP_vld1_32,        0xf4200280, "vld1.32",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x1f]},
    {OP_vld1_64,        0xf42002cd, "vld1.64",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld1_64,        0xf42002cf, "vld1.64",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x21]},
    {OP_vld1_64,        0xf42002c0, "vld1.64",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x22]},
    {OP_vld2_8,         0xf420030d, "vld2.8",         LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld2_8,         0xf420030f, "vld2.8",         LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x24]},
    {OP_vld2_8,         0xf4200300, "vld2.8",         LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x25]},
    {OP_vld2_16,        0xf420034d, "vld2.16",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld2_16,        0xf420034f, "vld2.16",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x27]},
    {OP_vld2_16,        0xf4200340, "vld2.16",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x28]},
    {OP_vld2_32,        0xf420038d, "vld2.32",        LX4q, RAw, Mqq, i2_4, RAw, no, x, END_LIST},
    {OP_vld2_32,        0xf420038f, "vld2.32",        LX4q, xx, Mqq, i2_4, xx, no, x, tvlA[1][0x2a]},
    {OP_vld2_32,        0xf4200380, "vld2.32",        LX4q, RAw, Mqq, i2_4, RDw, xop_wb, x, tvlA[1][0x2b]},
    {INVALID,           0xf42003cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42003cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42003c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld3_8,         0xf420040d, "vld3.8",         LX3q, RAw, M24, i2_4, RAw, no, x, END_LIST},
    {OP_vld3_8,         0xf420040f, "vld3.8",         LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x30]},
    {OP_vld3_8,         0xf4200400, "vld3.8",         LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x31]},
    {OP_vld3_16,        0xf420044d, "vld3.16",        LX3q, RAw, M24, i2_4, RAw, no, x, END_LIST},
    {OP_vld3_16,        0xf420044f, "vld3.16",        LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x33]},
    {OP_vld3_16,        0xf4200440, "vld3.16",        LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x34]},
    {OP_vld3_32,        0xf420048d, "vld3.32",        LX3q, RAw, M24, i2_4, RAw, no, x, END_LIST},
    {OP_vld3_32,        0xf420048f, "vld3.32",        LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x36]},
    {OP_vld3_32,        0xf4200480, "vld3.32",        LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x37]},
    {INVALID,           0xf42004cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42004cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42004c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld3_8,         0xf420050d, "vld3.8",         LX3Dq, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x32]},
    {OP_vld3_8,         0xf420050f, "vld3.8",         LX3Dq, xx, M24, i2_4, xx, no, x, tvlA[1][0x3c]},
    {OP_vld3_8,         0xf4200500, "vld3.8",         LX3Dq, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x3d]},
    {OP_vld3_16,        0xf420054d, "vld3.16",        LX3Dq, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x35]},
    {OP_vld3_16,        0xf420054f, "vld3.16",        LX3Dq, xx, M24, i2_4, xx, no, x, tvlA[1][0x3f]},
    {OP_vld3_16,        0xf4200540, "vld3.16",        LX3Dq, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x40]},
    {OP_vld3_32,        0xf420058d, "vld3.32",        LX3Dq, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x38]},
    {OP_vld3_32,        0xf420058f, "vld3.32",        LX3Dq, xx, M24, i2_4, xx, no, x, tvlA[1][0x42]},
    {OP_vld3_32,        0xf4200580, "vld3.32",        LX3Dq, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x43]},
    {INVALID,           0xf42005cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42005cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42005c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld1_8,         0xf420060d, "vld1.8",         LX3q, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x7a]},
    {OP_vld1_8,         0xf420060f, "vld1.8",         LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x48]},
    {OP_vld1_8,         0xf4200600, "vld1.8",         LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x49]},
    {OP_vld1_16,        0xf420064d, "vld1.16",        LX3q, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x7d]},
    {OP_vld1_16,        0xf420064f, "vld1.16",        LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x4b]},
    {OP_vld1_16,        0xf4200640, "vld1.16",        LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x4c]},
    {OP_vld1_32,        0xf420068d, "vld1.32",        LX3q, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x80]},
    {OP_vld1_32,        0xf420068f, "vld1.32",        LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x4e]},
    {OP_vld1_32,        0xf4200680, "vld1.32",        LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x4f]},
    {OP_vld1_64,        0xf42006cd, "vld1.64",        LX3q, RAw, M24, i2_4, RAw, no, x, tvlA[1][0x83]},
    {OP_vld1_64,        0xf42006cf, "vld1.64",        LX3q, xx, M24, i2_4, xx, no, x, tvlA[1][0x51]},
    {OP_vld1_64,        0xf42006c0, "vld1.64",        LX3q, RAw, M24, i2_4, RDw, xop_wb, x, tvlA[1][0x52]},
    {OP_vld1_8,         0xf420070d, "vld1.8",         VBq, RAw, Mq, i2_4, RAw, no, x, tvlA[1][0x4a]},/*XXX: some align values => undefined*/
    {OP_vld1_8,         0xf420070f, "vld1.8",         VBq, xx, Mq, i2_4, xx, no, x, tvlA[1][0x54]},/*XXX: combine align into memop?*/
    {OP_vld1_8,         0xf4200700, "vld1.8",         VBq, RAw, Mq, i2_4, RDw, xop_wb, x, tvlA[1][0x55]},
    {OP_vld1_16,        0xf420074d, "vld1.16",        VBq, RAw, Mq, i2_4, RAw, no, x, tvlA[1][0x4d]},
    {OP_vld1_16,        0xf420074f, "vld1.16",        VBq, xx, Mq, i2_4, xx, no, x, tvlA[1][0x57]},
    {OP_vld1_16,        0xf4200740, "vld1.16",        VBq, RAw, Mq, i2_4, RDw, xop_wb, x, tvlA[1][0x58]},
    {OP_vld1_32,        0xf420078d, "vld1.32",        VBq, RAw, Mq, i2_4, RAw, no, x, tvlA[1][0x50]},
    {OP_vld1_32,        0xf420078f, "vld1.32",        VBq, xx, Mq, i2_4, xx, no, x, tvlA[1][0x5a]},
    {OP_vld1_32,        0xf4200780, "vld1.32",        VBq, RAw, Mq, i2_4, RDw, xop_wb, x, tvlA[1][0x5b]},
    {OP_vld1_64,        0xf42007cd, "vld1.64",        VBq, RAw, Mq, i2_4, RAw, no, x, tvlA[1][0x53]},
    {OP_vld1_64,        0xf42007cf, "vld1.64",        VBq, xx, Mq, i2_4, xx, no, x, tvlA[1][0x5d]},
    {OP_vld1_64,        0xf42007c0, "vld1.64",        VBq, RAw, Mq, i2_4, RDw, xop_wb, x, tvlA[1][0x5e]},
    /* 0x80 */
    {OP_vld2_8,         0xf420080d, "vld2.8",         LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x26]},
    {OP_vld2_8,         0xf420080f, "vld2.8",         LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x60]},
    {OP_vld2_8,         0xf4200800, "vld2.8",         LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x61]},
    {OP_vld2_16,        0xf420084d, "vld2.16",        LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x29]},
    {OP_vld2_16,        0xf420084f, "vld2.16",        LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x63]},
    {OP_vld2_16,        0xf4200840, "vld2.16",        LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x64]},
    {OP_vld2_32,        0xf420088d, "vld2.32",        LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x2c]},
    {OP_vld2_32,        0xf420088f, "vld2.32",        LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x66]},
    {OP_vld2_32,        0xf4200880, "vld2.32",        LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x67]},
    {INVALID,           0xf42008cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42008cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42008c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld2_8,         0xf420090d, "vld2.8",         LX2Dq, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x62]},
    {OP_vld2_8,         0xf420090f, "vld2.8",         LX2Dq, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x6c]},
    {OP_vld2_8,         0xf4200900, "vld2.8",         LX2Dq, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x6d]},
    {OP_vld2_16,        0xf420094d, "vld2.16",        LX2Dq, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x65]},
    {OP_vld2_16,        0xf420094f, "vld2.16",        LX2Dq, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x6f]},
    {OP_vld2_16,        0xf4200940, "vld2.16",        LX2Dq, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x70]},
    {OP_vld2_32,        0xf420098d, "vld2.32",        LX2Dq, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x68]},
    {OP_vld2_32,        0xf420098f, "vld2.32",        LX2Dq, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x72]},
    {OP_vld2_32,        0xf4200980, "vld2.32",        LX2Dq, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x73]},
    {INVALID,           0xf42009cd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42009cf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf42009c0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld1_8,         0xf4200a0d, "vld1.8",         LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x1a]},
    {OP_vld1_8,         0xf4200a0f, "vld1.8",         LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x78]},
    {OP_vld1_8,         0xf4200a00, "vld1.8",         LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x79]},
    {OP_vld1_16,        0xf4200a4d, "vld1.16",        LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x1d]},
    {OP_vld1_16,        0xf4200a4f, "vld1.16",        LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x7b]},
    {OP_vld1_16,        0xf4200a40, "vld1.16",        LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x7c]},
    {OP_vld1_32,        0xf4200a8d, "vld1.32",        LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x20]},
    {OP_vld1_32,        0xf4200a8f, "vld1.32",        LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x7e]},
    {OP_vld1_32,        0xf4200a80, "vld1.32",        LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x7f]},
    {OP_vld1_64,        0xf4200acd, "vld1.64",        LX2q, RAw, Mdq, i2_4, RAw, no, x, tvlA[1][0x23]},
    {OP_vld1_64,        0xf4200acf, "vld1.64",        LX2q, xx, Mdq, i2_4, xx, no, x, tvlA[1][0x81]},
    {OP_vld1_64,        0xf4200ac0, "vld1.64",        LX2q, RAw, Mdq, i2_4, RDw, xop_wb, x, tvlA[1][0x82]},
  },
};

/* Indexed by bits (11:8,Y)*3+X where X is based on the value of 3:0:
 * + 0xd => 0
 * + 0xf => 1
 * + else => 2
 * And Y is:
 * + If bit 11 (0x.....8..) is set, the value of bit 6 (0x......4.)
 * + Else, the value of bit 5 (0x......2.).
 *
 * This requires some duplicate entries, marked below to make it easier to
 * reconfigure the table if we want to try a different arrangement.
 * It's just easier to deal w/ dups than tons of separate 2-entry tables
 * with indexes.
 */
const instr_info_t A32_ext_vldB[][96] = {
  { /* 0 */
    {OP_vst1_lane_8,    0xf480000d, "vst1.8",         Mb, RAw, VBb_q, i3_5, RAw, no, x, END_LIST},
    {OP_vst1_lane_8,    0xf480000f, "vst1.8",         Mb, xx, VBb_q, i3_5, xx, no, x, tvlB[0][0x00]},/*XXX: combine align into memop?*/
    {OP_vst1_lane_8,    0xf4800000, "vst1.8",         Mb, RAw, VBb_q, i3_5, RDw, xop_wb, x, tvlB[0][0x01]},
    {OP_vst1_lane_8,    0xf480002d, "vst1.8",/*dup*/  Mb, RAw, VBb_q, i3_5, RAw, no, x, tvlB[0][0x02]},
    {OP_vst1_lane_8,    0xf480002f, "vst1.8",/*dup*/  Mb, xx, VBb_q, i3_5, xx, no, x, tvlB[0][0x03]},/*XXX: combine align into memop?*/
    {OP_vst1_lane_8,    0xf4800020, "vst1.8",/*dup*/  Mb, RAw, VBb_q, i3_5, RDw, xop_wb, x, tvlB[0][0x04]},
    {OP_vst2_lane_8,    0xf480010d, "vst2.8",         Mh, RAw, LX2b_q, i3_5, i1_4, xop_wb, x, END_LIST},
    {OP_vst2_lane_8,    0xf480010f, "vst2.8",         Mh, xx, LX2b_q, i3_5, i1_4, no, x, tvlB[0][0x06]},
    {OP_vst2_lane_8,    0xf4800100, "vst2.8",         Mh, RAw, LX2b_q, i3_5, i1_4, xop_wb2, x, tvlB[0][0x07]},
    {OP_vst2_lane_8,    0xf480012d, "vst2.8",/*dup*/  Mh, RAw, LX2b_q, i3_5, i1_4, xop_wb, x, tvlB[0][0x08]},
    {OP_vst2_lane_8,    0xf480012f, "vst2.8",/*dup*/  Mh, xx, LX2b_q, i3_5, i1_4, no, x, tvlB[0][0x09]},
    {OP_vst2_lane_8,    0xf4800120, "vst2.8",/*dup*/  Mh, RAw, LX2b_q, i3_5, i1_4, xop_wb2, x, tvlB[0][0x0a]},
    {OP_vst3_lane_8,    0xf480020d, "vst3.8",         M3, RAw, LX3b_q, i3_5, RAw, no, x, END_LIST},
    {OP_vst3_lane_8,    0xf480020f, "vst3.8",         M3, xx, LX3b_q, i3_5, xx, no, x, tvlB[0][0x0c]},
    {OP_vst3_lane_8,    0xf4800200, "vst3.8",         M3, RAw, LX3b_q, i3_5, RDw, xop_wb, x, tvlB[0][0x0d]},
    {OP_vst3_lane_8,    0xf480022d, "vst3.8",/*dup*/  M3, RAw, LX3b_q, i3_5, RAw, no, x, tvlB[0][0x0e]},
    {OP_vst3_lane_8,    0xf480022f, "vst3.8",/*dup*/  M3, xx, LX3b_q, i3_5, xx, no, x, tvlB[0][0x0f]},
    {OP_vst3_lane_8,    0xf4800220, "vst3.8",/*dup*/  M3, RAw, LX3b_q, i3_5, RDw, xop_wb, x, tvlB[0][0x10]},
    {OP_vst4_lane_8,    0xf480030d, "vst4.8",         Md, RAw, LX4b_q, i3_5, i1_4, xop_wb, x, END_LIST},
    {OP_vst4_lane_8,    0xf480030f, "vst4.8",         Md, xx, LX4b_q, i3_5, i1_4, no, x, tvlB[0][0x12]},
    {OP_vst4_lane_8,    0xf4800300, "vst4.8",         Md, RAw, LX4b_q, i3_5, i1_4, xop_wb2, x, tvlB[0][0x13]},
    {OP_vst4_lane_8,    0xf480032d, "vst4.8",/*dup*/  Md, RAw, LX4b_q, i3_5, i1_4, xop_wb, x, tvlB[0][0x14]},
    {OP_vst4_lane_8,    0xf480032f, "vst4.8",/*dup*/  Md, xx, LX4b_q, i3_5, i1_4, no, x, tvlB[0][0x15]},
    {OP_vst4_lane_8,    0xf4800320, "vst4.8",/*dup*/  Md, RAw, LX4b_q, i3_5, i1_4, xop_wb2, x, tvlB[0][0x16]},
    {OP_vst1_lane_16,   0xf480040d, "vst1.16",        Mh, RAw, VBh_q, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vst1_lane_16,   0xf480040f, "vst1.16",        Mh, xx, VBh_q, i2_6, i1_4, no, x, tvlB[0][0x18]},
    {OP_vst1_lane_16,   0xf4800400, "vst1.16",        Mh, RAw, VBh_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x19]},
    {OP_vst1_lane_16,   0xf480042d, "vst1.16",/*dup*/ Mh, RAw, VBh_q, i2_6, i1_4, xop_wb, x, tvlB[0][0x1a]},
    {OP_vst1_lane_16,   0xf480042f, "vst1.16",/*dup*/ Mh, xx, VBh_q, i2_6, i1_4, no, x, tvlB[0][0x1b]},
    {OP_vst1_lane_16,   0xf4800420, "vst1.16",/*dup*/ Mh, RAw, VBh_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x1c]},
    {OP_vst2_lane_16,   0xf480050d, "vst2.16",        Md, RAw, LX2h_q, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vst2_lane_16,   0xf480050f, "vst2.16",        Md, xx, LX2h_q, i2_6, i1_4, no, x, tvlB[0][0x1e]},
    {OP_vst2_lane_16,   0xf4800500, "vst2.16",        Md, RAw, LX2h_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x1f]},
    {OP_vst2_lane_16,   0xf480052d, "vst2.16",        Md, RAw, LX2Dh_q, i2_6, i1_4, xop_wb, x, tvlB[0][0x20]},
    {OP_vst2_lane_16,   0xf480052f, "vst2.16",        Md, xx, LX2Dh_q, i2_6, i1_4, no, x, tvlB[0][0x21]},
    {OP_vst2_lane_16,   0xf4800520, "vst2.16",        Md, RAw, LX2Dh_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x22]},
    {OP_vst3_lane_16,   0xf480060d, "vst3.16",        M6, RAw, LX3h_q, i2_6, RAw, no, x, END_LIST},
    {OP_vst3_lane_16,   0xf480060f, "vst3.16",        M6, xx, LX3h_q, i2_6, xx, no, x, tvlB[0][0x24]},
    {OP_vst3_lane_16,   0xf4800600, "vst3.16",        M6, RAw, LX3h_q, i2_6, RDw, xop_wb, x, tvlB[0][0x25]},
    {OP_vst3_lane_16,   0xf480062d, "vst3.16",        M6, RAw, LX3Dh_q, i2_6, RAw, no, x, tvlB[0][0x26]},
    {OP_vst3_lane_16,   0xf480062f, "vst3.16",        M6, xx, LX3Dh_q, i2_6, xx, no, x, tvlB[0][0x27]},
    {OP_vst3_lane_16,   0xf4800620, "vst3.16",        M6, RAw, LX3Dh_q, i2_6, RDw, xop_wb, x, tvlB[0][0x28]},
    {OP_vst4_lane_16,   0xf480070d, "vst4.16",        Mq, RAw, LX4h_q, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vst4_lane_16,   0xf480070f, "vst4.16",        Mq, xx, LX4h_q, i2_6, i1_4, no, x, tvlB[0][0x2a]},
    {OP_vst4_lane_16,   0xf4800700, "vst4.16",        Mq, RAw, LX4h_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x2b]},
    {OP_vst4_lane_16,   0xf480072d, "vst4.16",        Mq, RAw, LX4Dh_q, i2_6, i1_4, xop_wb, x, tvlB[0][0x2c]},
    {OP_vst4_lane_16,   0xf480072f, "vst4.16",        Mq, xx, LX4Dh_q, i2_6, i1_4, no, x, tvlB[0][0x2d]},
    {OP_vst4_lane_16,   0xf4800720, "vst4.16",        Mq, RAw, LX4Dh_q, i2_6, i1_4, xop_wb2, x, tvlB[0][0x2e]},
    /* 0x80 */
    {OP_vst1_lane_32,   0xf480080d, "vst1.32",        Md, RAw, VBd_q, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vst1_lane_32,   0xf480080f, "vst1.32",        Md, xx, VBd_q, i1_7, i2_4, no, x, tvlB[0][0x30]},
    {OP_vst1_lane_32,   0xf4800800, "vst1.32",        Md, RAw, VBd_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x31]},
    {OP_vst1_lane_32,   0xf480084d, "vst1.32",/*dup*/ Md, RAw, VBd_q, i1_7, i2_4, xop_wb, x, tvlB[0][0x32]},
    {OP_vst1_lane_32,   0xf480084f, "vst1.32",/*dup*/ Md, xx, VBd_q, i1_7, i2_4, no, x, tvlB[0][0x33]},
    {OP_vst1_lane_32,   0xf4800840, "vst1.32",/*dup*/ Md, RAw, VBd_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x34]},
    {OP_vst2_lane_32,   0xf480090d, "vst2.32",        Mq, RAw, LX2d_q, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vst2_lane_32,   0xf480090f, "vst2.32",        Mq, xx, LX2d_q, i1_7, i2_4, no, x, tvlB[0][0x36]},
    {OP_vst2_lane_32,   0xf4800900, "vst2.32",        Mq, RAw, LX2d_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x37]},
    {OP_vst2_lane_32,   0xf480094d, "vst2.32",        Mq, RAw, LX2Dd_q, i1_7, i2_4, xop_wb, x, tvlB[0][0x38]},
    {OP_vst2_lane_32,   0xf480094f, "vst2.32",        Mq, xx, LX2Dd_q, i1_7, i2_4, no, x, tvlB[0][0x39]},
    {OP_vst2_lane_32,   0xf4800940, "vst2.32",        Mq, RAw, LX2Dd_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x3a]},
    {OP_vst3_lane_32,   0xf4800a0d, "vst3.32",        M12, RAw, LX3d_q, i1_7, RAw, no, x, END_LIST},
    {OP_vst3_lane_32,   0xf4800a0f, "vst3.32",        M12, xx, LX3d_q, i1_7, xx, no, x, tvlB[0][0x3c]},
    {OP_vst3_lane_32,   0xf4800a00, "vst3.32",        M12, RAw, LX3d_q, i1_7, RDw, xop_wb, x, tvlB[0][0x3d]},
    {OP_vst3_lane_32,   0xf4800a4d, "vst3.32",        M12, RAw, LX3Dd_q, i1_7, RAw, no, x, tvlB[0][0x3e]},
    {OP_vst3_lane_32,   0xf4800a4f, "vst3.32",        M12, xx, LX3Dd_q, i1_7, xx, no, x, tvlB[0][0x3f]},
    {OP_vst3_lane_32,   0xf4800a40, "vst3.32",        M12, RAw, LX3Dd_q, i1_7, RDw, xop_wb, x, tvlB[0][0x40]},
    {OP_vst4_lane_32,   0xf4800b0d, "vst4.32",        Mdq, RAw, LX4d_q, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vst4_lane_32,   0xf4800b0f, "vst4.32",        Mdq, xx, LX4d_q, i1_7, i2_4, no, x, tvlB[0][0x42]},
    {OP_vst4_lane_32,   0xf4800b00, "vst4.32",        Mdq, RAw, LX4d_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x43]},
    {OP_vst4_lane_32,   0xf4800b4d, "vst4.32",        Mdq, RAw, LX4Dd_q, i1_7, i2_4, xop_wb, x, tvlB[0][0x44]},
    {OP_vst4_lane_32,   0xf4800b4f, "vst4.32",        Mdq, xx, LX4Dd_q, i1_7, i2_4, no, x, tvlB[0][0x45]},
    {OP_vst4_lane_32,   0xf4800b40, "vst4.32",        Mdq, RAw, LX4Dd_q, i1_7, i2_4, xop_wb2, x, tvlB[0][0x46]},
    {INVALID,           0xf4800c0d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800c0f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800c00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800c4d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800c4f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800c40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d0d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d0f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d4d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d4f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800d40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e0d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e0f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e4d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e4f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800e40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f0d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f0f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f00, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f4d, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f4f, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4800f40, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  }, { /* 1 */
    {OP_vld1_lane_8,    0xf4a0000d, "vld1.8",         VBb_q, RAw, Mb, i3_5, RAw, no, x, END_LIST},
    {OP_vld1_lane_8,    0xf4a0000f, "vld1.8",         VBb_q, xx, Mb, i3_5, xx, no, x, tvlB[1][0x00]},/*XXX: combine align into memop?*/
    {OP_vld1_lane_8,    0xf4a00000, "vld1.8",         VBb_q, RAw, Mb, i3_5, RDw, xop_wb, x, tvlB[1][0x01]},
    {OP_vld1_lane_8,    0xf4a0002d, "vld1.8",/*dup*/  VBb_q, RAw, Mb, i3_5, RAw, no, x, tvlB[1][0x02]},
    {OP_vld1_lane_8,    0xf4a0002f, "vld1.8",/*dup*/  VBb_q, xx, Mb, i3_5, xx, no, x, tvlB[1][0x03]},/*XXX: combine align into memop?*/
    {OP_vld1_lane_8,    0xf4a00020, "vld1.8",/*dup*/  VBb_q, RAw, Mb, i3_5, RDw, xop_wb, x, tvlB[1][0x04]},
    {OP_vld2_lane_8,    0xf4a0010d, "vld2.8",         LX2b_q, RAw, Mh, i3_5, RAw, no, x, END_LIST},
    {OP_vld2_lane_8,    0xf4a0010f, "vld2.8",         LX2b_q, xx, Mh, i3_5, xx, no, x, tvlB[1][0x06]},
    {OP_vld2_lane_8,    0xf4a00100, "vld2.8",         LX2b_q, RAw, Mh, i3_5, RDw, xop_wb, x, tvlB[1][0x07]},
    {OP_vld2_lane_8,    0xf4a0012d, "vld2.8",/*dup*/  LX2b_q, RAw, Mh, i3_5, RAw, no, x, tvlB[1][0x08]},
    {OP_vld2_lane_8,    0xf4a0012f, "vld2.8",/*dup*/  LX2b_q, xx, Mh, i3_5, xx, no, x, tvlB[1][0x09]},
    {OP_vld2_lane_8,    0xf4a00120, "vld2.8",/*dup*/  LX2b_q, RAw, Mh, i3_5, RDw, xop_wb, x, tvlB[1][0x0a]},
    {OP_vld3_lane_8,    0xf4a0020d, "vld3.8",         LX3b_q, RAw, M3, i3_5, RAw, no, x, END_LIST},
    {OP_vld3_lane_8,    0xf4a0020f, "vld3.8",         LX3b_q, xx, M3, i3_5, xx, no, x, tvlB[1][0x0c]},
    {OP_vld3_lane_8,    0xf4a00200, "vld3.8",         LX3b_q, RAw, M3, i3_5, RDw, xop_wb, x, tvlB[1][0x0d]},
    {OP_vld3_lane_8,    0xf4a0022d, "vld3.8",/*dup*/  LX3b_q, RAw, M3, i3_5, RAw, no, x, tvlB[1][0x0e]},
    {OP_vld3_lane_8,    0xf4a0022f, "vld3.8",/*dup*/  LX3b_q, xx, M3, i3_5, xx, no, x, tvlB[1][0x0f]},
    {OP_vld3_lane_8,    0xf4a00220, "vld3.8",/*dup*/  LX3b_q, RAw, M3, i3_5, RDw, xop_wb, x, tvlB[1][0x10]},
    {OP_vld4_lane_8,    0xf4a0030d, "vld4.8",         LX4b_q, RAw, Md, i3_5, RAw, no, x, END_LIST},
    {OP_vld4_lane_8,    0xf4a0030f, "vld4.8",         LX4b_q, xx, Md, i3_5, xx, no, x, tvlB[1][0x12]},
    {OP_vld4_lane_8,    0xf4a00300, "vld4.8",         LX4b_q, RAw, Md, i3_5, RDw, xop_wb, x, tvlB[1][0x13]},
    {OP_vld4_lane_8,    0xf4a0032d, "vld4.8",/*dup*/  LX4b_q, RAw, Md, i3_5, RAw, no, x, tvlB[1][0x14]},
    {OP_vld4_lane_8,    0xf4a0032f, "vld4.8",/*dup*/  LX4b_q, xx, Md, i3_5, xx, no, x, tvlB[1][0x15]},
    {OP_vld4_lane_8,    0xf4a00320, "vld4.8",/*dup*/  LX4b_q, RAw, Md, i3_5, RDw, xop_wb, x, tvlB[1][0x16]},
    {OP_vld1_lane_16,   0xf4a0040d, "vld1.16",        VBh_q, RAw, Mh, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vld1_lane_16,   0xf4a0040f, "vld1.16",        VBh_q, xx, Mh, i2_6, i1_4, no, x, tvlB[1][0x18]},
    {OP_vld1_lane_16,   0xf4a00400, "vld1.16",        VBh_q, RAw, Mh, i2_6, i1_4, xop_wb2, x, tvlB[1][0x19]},
    {OP_vld1_lane_16,   0xf4a0042d, "vld1.16",/*dup*/ VBh_q, RAw, Mh, i2_6, i1_4, xop_wb, x, tvlB[1][0x1a]},
    {OP_vld1_lane_16,   0xf4a0042f, "vld1.16",/*dup*/ VBh_q, xx, Mh, i2_6, i1_4, no, x, tvlB[1][0x1b]},
    {OP_vld1_lane_16,   0xf4a00420, "vld1.16",/*dup*/ VBh_q, RAw, Mh, i2_6, i1_4, xop_wb2, x, tvlB[1][0x1c]},
    {OP_vld2_lane_16,   0xf4a0050d, "vld2.16",        LX2h_q, RAw, Md, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vld2_lane_16,   0xf4a0050f, "vld2.16",        LX2h_q, xx, Md, i2_6, i1_4, no, x, tvlB[1][0x1e]},
    {OP_vld2_lane_16,   0xf4a00500, "vld2.16",        LX2h_q, RAw, Md, i2_6, i1_4, xop_wb2, x, tvlB[1][0x1f]},
    {OP_vld2_lane_16,   0xf4a0052d, "vld2.16",        LX2Dh_q, RAw, Md, i2_6, i1_4, xop_wb, x, tvlB[1][0x20]},
    {OP_vld2_lane_16,   0xf4a0052f, "vld2.16",        LX2Dh_q, xx, Md, i2_6, i1_4, no, x, tvlB[1][0x21]},
    {OP_vld2_lane_16,   0xf4a00520, "vld2.16",        LX2Dh_q, RAw, Md, i2_6, i1_4, xop_wb2, x, tvlB[1][0x22]},
    {OP_vld3_lane_16,   0xf4a0060d, "vld3.16",        LX3h_q, RAw, M6, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vld3_lane_16,   0xf4a0060f, "vld3.16",        LX3h_q, xx, M6, i2_6, i1_4, no, x, tvlB[1][0x24]},
    {OP_vld3_lane_16,   0xf4a00600, "vld3.16",        LX3h_q, RAw, M6, i2_6, i1_4, xop_wb2, x, tvlB[1][0x25]},
    {OP_vld3_lane_16,   0xf4a0062d, "vld3.16",        LX3Dh_q, RAw, M6, i2_6, i1_4, xop_wb, x, tvlB[1][0x26]},
    {OP_vld3_lane_16,   0xf4a0062f, "vld3.16",        LX3Dh_q, xx, M6, i2_6, i1_4, no, x, tvlB[1][0x27]},
    {OP_vld3_lane_16,   0xf4a00620, "vld3.16",        LX3Dh_q, RAw, M6, i2_6, i1_4, xop_wb2, x, tvlB[1][0x28]},
    {OP_vld4_lane_16,   0xf4a0070d, "vld4.16",        LX4h_q, RAw, Mq, i2_6, i1_4, xop_wb, x, END_LIST},
    {OP_vld4_lane_16,   0xf4a0070f, "vld4.16",        LX4h_q, xx, Mq, i2_6, i1_4, no, x, tvlB[1][0x2a]},
    {OP_vld4_lane_16,   0xf4a00700, "vld4.16",        LX4h_q, RAw, Mq, i2_6, i1_4, xop_wb2, x, tvlB[1][0x2b]},
    {OP_vld4_lane_16,   0xf4a0072d, "vld4.16",        LX4Dh_q, RAw, Mq, i2_6, i1_4, xop_wb, x, tvlB[1][0x2c]},
    {OP_vld4_lane_16,   0xf4a0072f, "vld4.16",        LX4Dh_q, xx, Mq, i2_6, i1_4, no, x, tvlB[1][0x2d]},
    {OP_vld4_lane_16,   0xf4a00720, "vld4.16",        LX4Dh_q, RAw, Mq, i2_6, i1_4, xop_wb2, x, tvlB[1][0x2e]},
    {OP_vld1_lane_32,   0xf4a0080d, "vld1.32",        VBd_q, RAw, Md, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vld1_lane_32,   0xf4a0080f, "vld1.32",        VBd_q, xx, Md, i1_7, i2_4, no, x, tvlB[1][0x30]},
    {OP_vld1_lane_32,   0xf4a00800, "vld1.32",        VBd_q, RAw, Md, i1_7, i2_4, xop_wb2, x, tvlB[1][0x31]},
    {OP_vld1_lane_32,   0xf4a0082d, "vld1.32",/*dup*/ VBd_q, RAw, Md, i1_7, i2_4, xop_wb, x, tvlB[1][0x32]},
    {OP_vld1_lane_32,   0xf4a0082f, "vld1.32",/*dup*/ VBd_q, xx, Md, i1_7, i2_4, no, x, tvlB[1][0x33]},
    {OP_vld1_lane_32,   0xf4a00820, "vld1.32",/*dup*/ VBd_q, RAw, Md, i1_7, i2_4, xop_wb2, x, tvlB[1][0x34]},
    {OP_vld2_lane_32,   0xf4a0090d, "vld2.32",        LX2d_q, RAw, Mq, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vld2_lane_32,   0xf4a0090f, "vld2.32",        LX2d_q, xx, Mq, i1_7, i2_4, no, x, tvlB[1][0x36]},
    {OP_vld2_lane_32,   0xf4a00900, "vld2.32",        LX2d_q, RAw, Mq, i1_7, i2_4, xop_wb2, x, tvlB[1][0x37]},
    {OP_vld2_lane_32,   0xf4a0094d, "vld2.32",        LX2Dd_q, RAw, Mq, i1_7, i2_4, xop_wb, x, tvlB[1][0x38]},
    {OP_vld2_lane_32,   0xf4a0094f, "vld2.32",        LX2Dd_q, xx, Mq, i1_7, i2_4, no, x, tvlB[1][0x39]},
    {OP_vld2_lane_32,   0xf4a00940, "vld2.32",        LX2Dd_q, RAw, Mq, i1_7, i2_4, xop_wb2, x, tvlB[1][0x3a]},
    {OP_vld3_lane_32,   0xf4a00a0d, "vld3.32",        LX3d_q, RAw, M12, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vld3_lane_32,   0xf4a00a0f, "vld3.32",        LX3d_q, xx, M12, i1_7, i2_4, no, x, tvlB[1][0x3c]},
    {OP_vld3_lane_32,   0xf4a00a00, "vld3.32",        LX3d_q, RAw, M12, i1_7, i2_4, xop_wb2, x, tvlB[1][0x3d]},
    {OP_vld3_lane_32,   0xf4a00a4d, "vld3.32",        LX3Dd_q, RAw, M12, i1_7, i2_4, xop_wb, x, tvlB[1][0x3e]},
    {OP_vld3_lane_32,   0xf4a00a4f, "vld3.32",        LX3Dd_q, xx, M12, i1_7, i2_4, no, x, tvlB[1][0x3f]},
    {OP_vld3_lane_32,   0xf4a00a40, "vld3.32",        LX3Dd_q, RAw, M12, i1_7, i2_4, xop_wb2, x, tvlB[1][0x40]},
    {OP_vld4_lane_32,   0xf4a00b0d, "vld4.32",        LX4d_q, RAw, Mdq, i1_7, i2_4, xop_wb, x, END_LIST},
    {OP_vld4_lane_32,   0xf4a00b0f, "vld4.32",        LX4d_q, xx, Mdq, i1_7, i2_4, no, x, tvlB[1][0x42]},
    {OP_vld4_lane_32,   0xf4a00b00, "vld4.32",        LX4d_q, RAw, Mdq, i1_7, i2_4, xop_wb2, x, tvlB[1][0x43]},
    {OP_vld4_lane_32,   0xf4a00b4d, "vld4.32",        LX4Dd_q, RAw, Mdq, i1_7, i2_4, xop_wb, x, tvlB[1][0x44]},
    {OP_vld4_lane_32,   0xf4a00b4f, "vld4.32",        LX4Dd_q, xx, Mdq, i1_7, i2_4, no, x, tvlB[1][0x45]},
    {OP_vld4_lane_32,   0xf4a00b40, "vld4.32",        LX4Dd_q, RAw, Mdq, i1_7, i2_4, xop_wb2, x, tvlB[1][0x46]},
    {EXT_VLDC,          0xf4a00c0d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00c0f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00c00, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00c4d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00c4f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00c40, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d0d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d0f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d00, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d4d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d4f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00d40, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e0d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e0f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e00, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e4d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e4f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00e40, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f0d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f0f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f00, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f4d, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f4f, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
    {EXT_VLDC,          0xf4a00f40, "(ext vldC  0)",  xx, xx, xx, xx, xx, no, x, 0},
  },
};

/* Indexed by bits (9:8,7:5)*3+X where X is based on the value of 3:0:
 * + 0xd => 0
 * + 0xf => 1
 * + else => 2
 */
const instr_info_t A32_ext_vldC[][96] = {
  { /* 0 */
    {OP_vld1_dup_8,     0xf4a00c0d, "vld1.8",         VBq, RAw, Mb, RAw, xx, no, x, tvlC[0][0x05]},
    {OP_vld1_dup_8,     0xf4a00c0f, "vld1.8",         VBq, xx, Mb, xx, xx, no, x, tvlC[0][0x00]},
    {OP_vld1_dup_8,     0xf4a00c00, "vld1.8",         VBq, RAw, Mb, RDw, RAw, no, x, tvlC[0][0x01]},
    {OP_vld1_dup_8,     0xf4a00c2d, "vld1.8",         LX2q, RAw, Mb, RAw, xx, no, x, END_LIST},
    {OP_vld1_dup_8,     0xf4a00c2f, "vld1.8",         LX2q, xx, Mb, xx, xx, no, x, tvlC[0][0x03]},
    {OP_vld1_dup_8,     0xf4a00c20, "vld1.8",         LX2q, RAw, Mb, RDw, RAw, no, x, tvlC[0][0x04]},
    {OP_vld1_dup_16,    0xf4a00c4d, "vld1.16",        VBq, RAw, Mh, i1_4, RAw, no, x, tvlC[0][0x0b]},
    {OP_vld1_dup_16,    0xf4a00c4f, "vld1.16",        VBq, xx, Mh, i1_4, xx, no, x, tvlC[0][0x06]},
    {OP_vld1_dup_16,    0xf4a00c40, "vld1.16",        VBq, RAw, Mh, i1_4, RDw, xop_wb, x, tvlC[0][0x07]},
    {OP_vld1_dup_16,    0xf4a00c6d, "vld1.16",        LX2q, RAw, Mh, i1_4, RAw, no, x, END_LIST},
    {OP_vld1_dup_16,    0xf4a00c6f, "vld1.16",        LX2q, xx, Mh, i1_4, xx, no, x, tvlC[0][0x09]},
    {OP_vld1_dup_16,    0xf4a00c60, "vld1.16",        LX2q, RAw, Mh, i1_4, RDw, xop_wb, x, tvlC[0][0x0a]},
    {OP_vld1_dup_32,    0xf4a00c8d, "vld1.32",        VBq, RAw, Md, i1_4, RAw, no, x, tvlC[0][0x11]},
    {OP_vld1_dup_32,    0xf4a00c8f, "vld1.32",        VBq, xx, Md, i1_4, xx, no, x, tvlC[0][0x0c]},
    {OP_vld1_dup_32,    0xf4a00c80, "vld1.32",        VBq, RAw, Md, i1_4, RDw, xop_wb, x, tvlC[0][0x0d]},
    {OP_vld1_dup_32,    0xf4a00cad, "vld1.32",        LX2q, RAw, Md, i1_4, RAw, no, x, END_LIST},
    {OP_vld1_dup_32,    0xf4a00caf, "vld1.32",        LX2q, xx, Md, i1_4, xx, no, x, tvlC[0][0x0f]},
    {OP_vld1_dup_32,    0xf4a00ca0, "vld1.32",        LX2q, RAw, Md, i1_4, RDw, xop_wb, x, tvlC[0][0x10]},
    {INVALID,           0xf4a00ccd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ccf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00cc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ced, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00cef, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ce0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld2_dup_8,     0xf4a00d0d, "vld2.8",         LX2q, RAw, Mh, RAw, xx, no, x, END_LIST},
    {OP_vld2_dup_8,     0xf4a00d0f, "vld2.8",         LX2q, xx, Mh, xx, xx, no, x, tvlC[0][0x18]},
    {OP_vld2_dup_8,     0xf4a00d00, "vld2.8",         LX2q, RAw, Mh, RDw, RAw, no, x, tvlC[0][0x19]},
    {OP_vld2_dup_8,     0xf4a00d2d, "vld2.8",         LX2Dq, RAw, Mh, RAw, xx, no, x, tvlC[0][0x1a]},
    {OP_vld2_dup_8,     0xf4a00d2f, "vld2.8",         LX2Dq, xx, Mh, xx, xx, no, x, tvlC[0][0x1b]},
    {OP_vld2_dup_8,     0xf4a00d20, "vld2.8",         LX2Dq, RAw, Mh, RDw, RAw, no, x, tvlC[0][0x1c]},
    {OP_vld2_dup_16,    0xf4a00d4d, "vld2.16",        LX2q, RAw, Md, i1_4, RAw, no, x, END_LIST},
    {OP_vld2_dup_16,    0xf4a00d4f, "vld2.16",        LX2q, xx, Md, i1_4, xx, no, x, tvlC[0][0x1e]},
    {OP_vld2_dup_16,    0xf4a00d40, "vld2.16",        LX2q, RAw, Md, i1_4, RDw, xop_wb, x, tvlC[0][0x1f]},
    {OP_vld2_dup_16,    0xf4a00d6d, "vld2.16",        LX2Dq, RAw, Md, i1_4, RAw, no, x, tvlC[0][0x20]},
    {OP_vld2_dup_16,    0xf4a00d6f, "vld2.16",        LX2Dq, xx, Md, i1_4, xx, no, x, tvlC[0][0x21]},
    {OP_vld2_dup_16,    0xf4a00d60, "vld2.16",        LX2Dq, RAw, Md, i1_4, RDw, xop_wb, x, tvlC[0][0x22]},
    {OP_vld2_dup_32,    0xf4a00d8d, "vld2.32",        LX2q, RAw, Mq, i1_4, RAw, no, x, END_LIST},
    {OP_vld2_dup_32,    0xf4a00d8f, "vld2.32",        LX2q, xx, Mq, i1_4, xx, no, x, tvlC[0][0x24]},
    {OP_vld2_dup_32,    0xf4a00d80, "vld2.32",        LX2q, RAw, Mq, i1_4, RDw, xop_wb, x, tvlC[0][0x25]},
    {OP_vld2_dup_32,    0xf4a00dad, "vld2.32",        LX2Dq, RAw, Mq, i1_4, RAw, no, x, tvlC[0][0x26]},
    {OP_vld2_dup_32,    0xf4a00daf, "vld2.32",        LX2Dq, xx, Mq, i1_4, xx, no, x, tvlC[0][0x27]},
    {OP_vld2_dup_32,    0xf4a00da0, "vld2.32",        LX2Dq, RAw, Mq, i1_4, RDw, xop_wb, x, tvlC[0][0x28]},
    {INVALID,           0xf4a00dcd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00dcf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00dc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ded, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00def, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00de0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld3_dup_8,     0xf4a00e0d, "vld3.8",         LX3q, RAw, M3, RAw, xx, no, x, END_LIST},
    {OP_vld3_dup_8,     0xf4a00e0f, "vld3.8",         LX3q, xx, M3, xx, xx, no, x, tvlC[0][0x30]},
    {OP_vld3_dup_8,     0xf4a00e00, "vld3.8",         LX3q, RAw, M3, RDw, RAw, no, x, tvlC[0][0x31]},
    {OP_vld3_dup_8,     0xf4a00e2d, "vld3.8",         LX3Dq, RAw, M3, RAw, xx, no, x, tvlC[0][0x32]},
    {OP_vld3_dup_8,     0xf4a00e2f, "vld3.8",         LX3Dq, xx, M3, xx, xx, no, x, tvlC[0][0x33]},
    {OP_vld3_dup_8,     0xf4a00e20, "vld3.8",         LX3Dq, RAw, M3, RDw, RAw, no, x, tvlC[0][0x34]},
    {OP_vld3_dup_16,    0xf4a00e4d, "vld3.16",        LX3q, RAw, M6, i1_4, RAw, no, x, END_LIST},
    {OP_vld3_dup_16,    0xf4a00e4f, "vld3.16",        LX3q, xx, M6, i1_4, xx, no, x, tvlC[0][0x36]},
    {OP_vld3_dup_16,    0xf4a00e40, "vld3.16",        LX3q, RAw, M6, i1_4, RDw, xop_wb, x, tvlC[0][0x37]},
    {OP_vld3_dup_16,    0xf4a00e6d, "vld3.16",        LX3Dq, RAw, M6, i1_4, RAw, no, x, tvlC[0][0x38]},
    {OP_vld3_dup_16,    0xf4a00e6f, "vld3.16",        LX3Dq, xx, M6, i1_4, xx, no, x, tvlC[0][0x39]},
    {OP_vld3_dup_16,    0xf4a00e60, "vld3.16",        LX3Dq, RAw, M6, i1_4, RDw, xop_wb, x, tvlC[0][0x3a]},
    {OP_vld3_dup_32,    0xf4a00e8d, "vld3.32",        LX3q, RAw, M12, i1_4, RAw, no, x, END_LIST},
    {OP_vld3_dup_32,    0xf4a00e8f, "vld3.32",        LX3q, xx, M12, i1_4, xx, no, x, tvlC[0][0x3c]},
    {OP_vld3_dup_32,    0xf4a00e80, "vld3.32",        LX3q, RAw, M12, i1_4, RDw, xop_wb, x, tvlC[0][0x3d]},
    {OP_vld3_dup_32,    0xf4a00ead, "vld3.32",        LX3Dq, RAw, M12, i1_4, RAw, no, x, tvlC[0][0x3e]},
    {OP_vld3_dup_32,    0xf4a00eaf, "vld3.32",        LX3Dq, xx, M12, i1_4, xx, no, x, tvlC[0][0x3f]},
    {OP_vld3_dup_32,    0xf4a00ea0, "vld3.32",        LX3Dq, RAw, M12, i1_4, RDw, xop_wb, x, tvlC[0][0x40]},
    {INVALID,           0xf4a00ecd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ecf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ec0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00eed, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00eef, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00ee0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {OP_vld4_dup_8,     0xf4a00f0d, "vld4.8",         LX4q, RAw, Md, RAw, xx, no, x, END_LIST},
    {OP_vld4_dup_8,     0xf4a00f0f, "vld4.8",         LX4q, xx, Md, xx, xx, no, x, tvlC[0][0x48]},
    {OP_vld4_dup_8,     0xf4a00f00, "vld4.8",         LX4q, RAw, Md, RDw, RAw, no, x, tvlC[0][0x49]},
    {OP_vld4_dup_8,     0xf4a00f2d, "vld4.8",         LX4Dq, RAw, Md, RAw, xx, no, x, tvlC[0][0x4a]},
    {OP_vld4_dup_8,     0xf4a00f2f, "vld4.8",         LX4Dq, xx, Md, xx, xx, no, x, tvlC[0][0x4b]},
    {OP_vld4_dup_8,     0xf4a00f20, "vld4.8",         LX4Dq, RAw, Md, RDw, RAw, no, x, tvlC[0][0x4c]},
    {OP_vld4_dup_16,    0xf4a00f4d, "vld4.16",        LX4q, RAw, Mq, i1_4, RAw, no, x, END_LIST},
    {OP_vld4_dup_16,    0xf4a00f4f, "vld4.16",        LX4q, xx, Mq, i1_4, xx, no, x, tvlC[0][0x4e]},
    {OP_vld4_dup_16,    0xf4a00f40, "vld4.16",        LX4q, RAw, Mq, i1_4, RDw, xop_wb, x, tvlC[0][0x4f]},
    {OP_vld4_dup_16,    0xf4a00f6d, "vld4.16",        LX4Dq, RAw, Mq, i1_4, RAw, no, x, tvlC[0][0x50]},
    {OP_vld4_dup_16,    0xf4a00f6f, "vld4.16",        LX4Dq, xx, Mq, i1_4, xx, no, x, tvlC[0][0x51]},
    {OP_vld4_dup_16,    0xf4a00f60, "vld4.16",        LX4Dq, RAw, Mq, i1_4, RDw, xop_wb, x, tvlC[0][0x52]},
    {OP_vld4_dup_32,    0xf4a00f8d, "vld4.32",        LX4q, RAw, Mdq, i1_4, RAw, no, x, END_LIST},
    {OP_vld4_dup_32,    0xf4a00f8f, "vld4.32",        LX4q, xx, Mdq, i1_4, xx, no, x, tvlC[0][0x54]},
    {OP_vld4_dup_32,    0xf4a00f80, "vld4.32",        LX4q, RAw, Mdq, i1_4, RDw, xop_wb, x, tvlC[0][0x55]},
    {OP_vld4_dup_32,    0xf4a00fad, "vld4.32",        LX4Dq, RAw, Mdq, i1_4, RAw, no, x, tvlC[0][0x56]},
    {OP_vld4_dup_32,    0xf4a00faf, "vld4.32",        LX4Dq, xx, Mdq, i1_4, xx, no, x, tvlC[0][0x57]},
    {OP_vld4_dup_32,    0xf4a00fa0, "vld4.32",        LX4Dq, RAw, Mdq, i1_4, RDw, xop_wb, x, tvlC[0][0x58]},
    {INVALID,           0xf4a00fcd, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00fcf, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00fc0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00fed, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00fef, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
    {INVALID,           0xf4a00fe0, "(bad)",          xx, xx, xx, xx, xx, no, x, NA},
  },
};

/* Indexed by:
 * + if 11:10 != 2, then index 0;
 * + else, 9:8,6
 * XXX: this is to handle OP_vtb{l,x} only and it adds an extra step
 * for a lot of other opcodes -- can we do better?
 */
const instr_info_t A32_ext_vtb[][9] = {
  { /* 0 */
    {EXT_BITS16,        0xf3b00000, "(ext bits16 9)", xx, xx, xx, xx, xx, no, x, 9},
    {OP_vtbl_8,         0xf3b00800, "vtbl.8",         VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vtbx_8,         0xf3b00840, "vtbx.8",         VBq, xx, VAq, VCq, xx, no, x, END_LIST},
    {OP_vtbl_8,         0xf3b00900, "vtbl.8",         VBq, xx, LXA2q, VCq, xx, no, x, tvtb[0][0x01]},
    {OP_vtbx_8,         0xf3b00940, "vtbx.8",         VBq, xx, LXA2q, VCq, xx, no, x, tvtb[0][0x02]},
    {OP_vtbl_8,         0xf3b00a00, "vtbl.8",         VBq, xx, LXA3q, VCq, xx, no, x, tvtb[0][0x03]},
    {OP_vtbx_8,         0xf3b00a40, "vtbx.8",         VBq, xx, LXA3q, VCq, xx, no, x, tvtb[0][0x04]},
    {OP_vtbl_8,         0xf3b00b00, "vtbl.8",         VBq, xx, LXA4q, VCq, xx, no, x, tvtb[0][0x05]},
    {OP_vtbx_8,         0xf3b00b40, "vtbx.8",         VBq, xx, LXA4q, VCq, xx, no, x, tvtb[0][0x06]},
  },
};
