#pragma once

#include "core/types.hpp"

// From Dolphin
enum class Opcode : Toolbox::u8 {
    OP_TWI           = 3,
    OP_PAIRED_SINGLE = 4,
    OP_MULLI         = 7,
    OP_SUBFIC        = 8,
    OP_CMPLI         = 10,
    OP_CMPL          = 11,
    OP_ADDIC         = 12,
    OP_ADDIC_RC      = 13,
    OP_ADDI          = 14,
    OP_ADDIS         = 15,
    OP_BC            = 16,
    OP_SC            = 17,
    OP_B             = 18,
    OP_CONTROL_FLOW  = 19,
    OP_RLWIMI        = 20,
    OP_RLWINM        = 21,
    OP_RLWNM         = 23,
    OP_ORI           = 24,
    OP_ORIS          = 25,
    OP_XORI          = 26,
    OP_XORIS         = 27,
    OP_ANDI          = 28,
    OP_ANDIS         = 29,
    OP_FIXED         = 31,
    OP_LWZ           = 32,
    OP_LWZU          = 33,
    OP_LBZ           = 34,
    OP_LBZU          = 35,
    OP_STW           = 36,
    OP_STWU          = 37,
    OP_STB           = 38,
    OP_STBU          = 39,
    OP_LHZ           = 40,
    OP_LHZU          = 41,
    OP_LHA           = 42,
    OP_LHAU          = 43,
    OP_STH           = 44,
    OP_STHU          = 45,
    OP_LMW           = 46,
    OP_STMW          = 47,
    OP_LFS           = 48,
    OP_LFSU          = 49,
    OP_LFD           = 50,
    OP_LFDU          = 51,
    OP_STFS          = 52,
    OP_STFSU         = 53,
    OP_STFD          = 54,
    OP_STFDU         = 55,
    OP_PSQ_L         = 56,
    OP_PSQ_LU        = 57,
    OP_FS_MATH       = 59,
    OP_PSQ_ST        = 60,
    OP_PSQ_STU       = 61,
    OP_FLOAT         = 63,
};

enum class TableSubOpcode4 : Toolbox::u16 {
    PS_CMPU0   = 0,
    PSQ_L      = 6,
    PSQ_ST     = 7,
    PS_SUM0    = 10,
    PS_SUM1    = 11,
    PS_MULS0   = 12,
    PS_MULS1   = 13,
    PS_MADDS0  = 14,
    PS_MADDS1  = 15,
    PS_DIV     = 18,
    PS_SUB     = 20,
    PS_ADD     = 21,
    PS_SEL     = 23,
    PS_RES     = 24,
    PS_MUL     = 25,
    PS_RSQRTE  = 26,
    PS_MSUB    = 28,
    PS_MADD    = 29,
    PS_NMSUB   = 30,
    PS_NMADD   = 31,
    PS_CMPO0   = 32,
    PSQ_LU     = 38,
    PSQ_STU    = 39,
    PS_NEG     = 40,
    PS_CMPU1   = 64,
    PS_MR      = 72,
    PS_CMPO1   = 96,
    PS_NABS    = 136,
    PS_ABS     = 264,
    PS_MERGE00 = 528,
    PS_MERGE01 = 560,
    PS_MERGE10 = 592,
    PS_MERGE11 = 624,
    DCBZ_L     = 1014,
};

enum class TableSubOpcode19 : Toolbox::u16 {
    MCRF   = 0,
    BCLR   = 16,
    CRNOR  = 33,
    RFI    = 50,
    CRANDC = 129,
    ISYNC  = 150,
    CRXOR  = 193,
    CRNAND = 225,
    CRAND  = 257,
    CREQV  = 289,
    CRORC  = 417,
    CROR   = 449,
    BCCTR  = 528,
};

enum class TableSubOpcode31 : Toolbox::u16 {
    ADD     = 266,
    ADDO    = 778,
    ADDC    = 10,
    ADDCO   = 522,
    ADDE    = 138,
    ADDEO   = 650,
    ADDME   = 234,
    ADDMEO  = 746,
    ADDZE   = 202,
    ADDZEO  = 714,
    DIVW    = 491,
    DIVWO   = 1003,
    DIVWU   = 459,
    DIVWUO  = 971,
    MULHW   = 75,
    MULHWU  = 11,
    MULLW   = 235,
    MULLWO  = 747,
    NEG     = 104,
    NEGO    = 616,
    SUBF    = 40,
    SUBFOs  = 552,
    SUBFC   = 8,
    SUBFCO  = 520,
    SUBFE   = 136,
    SUBFEO  = 648,
    SUBFME  = 232,
    SUBFMEO = 744,
    SUBFZE  = 200,
    SUBFZEO = 712,
    AND     = 28,
    ANDC    = 60,
    OR      = 444,
    NOR     = 124,
    XOR     = 316,
    ORC     = 412,
    NAND    = 476,
    EQV     = 284,
    CMP     = 0,
    CMPL    = 32,
    CNTLZW  = 26,
    EXTSH   = 922,
    EXTSB   = 954,
    SRW     = 536,
    SRAW    = 792,
    SRAWI   = 824,
    SLW     = 24,
    DCBST   = 54,
    DCBF    = 86,
    DCBTST  = 246,
    DCBT    = 278,
    DCBI    = 470,
    DCBA    = 758,
    DCBZ    = 1014,
    LWZ     = 23,
    LWZU    = 55,
    LHZ     = 279,
    LHZU    = 311,
    LHA     = 343,
    LHAU    = 375,
    LBZ     = 87,
    LBZU    = 119,
    LWBR    = 534,
    LHBR    = 790,
    STWCXD  = 150,
    LWAR    = 20,
    LSW     = 533,
    LSWI    = 597,
    STW     = 151,
    STWU    = 183,
    STH     = 407,
    STHU    = 439,
    STB     = 215,
    STBU    = 247,
    STWBR   = 662,
    STHBR   = 918,
    STSW    = 661,
    STSWI   = 725,
    LFS     = 535,
    LFSU    = 567,
    LFD     = 599,
    LFDU    = 631,
    STFS    = 663,
    STFSU   = 695,
    STFD    = 727,
    STFDU   = 759,
    STFIW   = 983,
    MFCR    = 19,
    MFMSR   = 83,
    MTCRF   = 144,
    MTMSR   = 146,
    MTSR    = 210,
    MTSRIN  = 242,
    MFSPR   = 339,
    MTSPR   = 467,
    MFTB    = 371,
    MCRXR   = 512,
    MFSR    = 595,
    MFSRIN  = 659,
    TW      = 4,
    SYNC    = 598,
    ICBI    = 982,
    ECIW    = 310,
    ECOW    = 438,
    EIEIO   = 854,
    TLBIE   = 306,
    TLBSYNC = 566,
};

enum class TableSubOpcode59 : Toolbox::u16 {
    FDIVS   = 18,
    FSUBS   = 20,
    FADDS   = 21,
    FRES    = 24,
    FMULS   = 25,
    FMSUBS  = 28,
    FMADDS  = 29,
    FNMSUBS = 30,
    FNMADDS = 31,
};

enum class TableSubOpcode63 : Toolbox::u16 {
    FCMPU  = 0,
    FRSP   = 12,
    FCTIW  = 14,
    FCTIWZ = 15,
    FDIV   = 18,
    FSUB   = 20,
    FADD   = 21,
    FRES   = 24,
    FMUL   = 25,
    FMSUB  = 28,
    FMADD  = 29,
    FNMSUB = 30,
    FNMADD = 31,
    FCMPO  = 32,
    MTFSB1 = 38,
    FNEG   = 40,
    MCRFS  = 64,
    MTFSB0 = 70,
    FMR    = 72,
    MTFSFI = 134,
    FNABS  = 136,
    FABS   = 264,
    MFFS   = 583,
    MTFS   = 711,
};