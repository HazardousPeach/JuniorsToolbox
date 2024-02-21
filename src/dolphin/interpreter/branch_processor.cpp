#pragma once

#include "core/core.hpp"
#include "core/memory.hpp"

#include "serial.hpp"

#include "dolphin/interpreter/processor.hpp"

namespace Toolbox::Interpreter {

    s32 s_depth = 0;

    void BranchProcessor::b(s32 target_addr, bool aa, bool lk, Register::PC &pc) {
        if (lk) {
            m_lr = (pc + 4) & 0xFFFFFFFC;
        }

        if (aa) {
            pc = target_addr & 0xFFFFFFFC;
        } else {
            pc = (pc + target_addr) & 0xFFFFFFFC;
        }

        if (lk) {
            s_depth++;
            TOOLBOX_DEBUG_LOG_V("[Interpreter] Calling function at: 0x{:08X}, depth: {}", pc, s_depth);
        }

        if (pc < 0x80000000 || pc >= 0x81800000) {
            std::cout << "Buhbuh\n";
        }
    }

    void BranchProcessor::bc(s32 target_addr, u8 bo, u8 bi, bool aa, bool lk, Register::PC &pc) {
        bool cond_true = m_cr.is(bi / 4, Register::CRCmp(bi % 4));

        // bdnz && !cri
        if ((bo & 0b11110) == 0b00000) {
            m_ctr -= 1;
            if (m_ctr != 0 && !cond_true) {
                b(target_addr, aa, lk, pc);
            }
            return;
        }

        // bdz && !cri
        if ((bo & 0b11110) == 0b00010) {
            m_ctr -= 1;
            if (m_ctr == 0 && !cond_true) {
                b(target_addr, aa, lk, pc);
            }
            return;
        }

        // bc !cri
        if ((bo & 0b11100) == 0b00100 && !cond_true) {
            b(target_addr, aa, lk, pc);
            return;
        }

        // bdnz && cri
        if ((bo & 0b11110) == 0b01000) {
            m_ctr -= 1;
            if (m_ctr != 0 && cond_true) {
                b(target_addr, aa, lk, pc);
            }
            return;
        }

        // bdz && cri
        if ((bo & 0b11110) == 0b01010) {
            m_ctr -= 1;
            if (m_ctr == 0 && cond_true) {
                b(target_addr, aa, lk, pc);
            }
            return;
        }

        // bc cri
        if ((bo & 0b11100) == 0b01100 && cond_true) {
            b(target_addr, aa, lk, pc);
            return;
        }

        // b (call branch directly to save performance)
        if ((bo & 0b10100) == 0b10100) [[likely]] {
            b(target_addr, aa, lk, pc);
            return;
        }

        pc += 4;
    }

    void BranchProcessor::bclr(u8 bo, u8 bi, bool lk, Register::PC &pc) {
        bool cond_true = m_cr.is(bi / 4, Register::CRCmp(bi % 4));

        // bdnz && !cri
        if ((bo & 0b11110) == 0b00000) {
            m_ctr -= 1;
            if (m_ctr != 0 && !cond_true) {
                b((s32)m_lr, true, lk, pc);
            }
            return;
        }

        // bdz && !cri
        if ((bo & 0b11110) == 0b00010) {
            m_ctr -= 1;
            if (m_ctr == 0 && !cond_true) {
                b((s32)m_lr, true, lk, pc);
            }
            return;
        }

        // bc !cri
        if ((bo & 0b11100) == 0b00100 && !cond_true) {
            b((s32)m_lr, true, lk, pc);
            if (!lk) {
                s_depth--;
                TOOLBOX_DEBUG_LOG_V(
                    "[Interpreter] Returning from function called at: 0x{:08X}, depth: {}", pc - 4,
                    s_depth);
                m_return_cb();
            }
            return;
        }

        // bdnz && cri
        if ((bo & 0b11110) == 0b01000) {
            m_ctr -= 1;
            if (m_ctr != 0 && cond_true) {
                b((s32)m_lr, true, lk, pc);
            }
            return;
        }

        // bdz && cri
        if ((bo & 0b11110) == 0b01010) {
            m_ctr -= 1;
            if (m_ctr == 0 && cond_true) {
                b((s32)m_lr, true, lk, pc);
            }
            return;
        }

        // bc cri
        if ((bo & 0b11100) == 0b01100 && cond_true) {
            b((s32)m_lr, true, lk, pc);
            if (!lk)
                m_return_cb();
            return;
        }

        // blr
        if ((bo & 0b10100) == 0b10100) [[likely]] {
            b((s32)m_lr, true, lk, pc);
            if (!lk) {
                s_depth--;
                TOOLBOX_DEBUG_LOG_V("[Interpreter] Returning from function called at: 0x{:08X}, depth: {}", pc - 4, s_depth);
                m_return_cb();
            }
            return;
        }

        pc += 4;
    }

    void BranchProcessor::bcctr(u8 bo, u8 bi, bool lk, Register::PC &pc) {
        bool cond_true = m_cr.is(bi / 4, Register::CRCmp(bi % 4));

        // CTR manip is invalid
        if ((bo & 0b00100) == 0) {
            m_invalid_cb(PROC_INVALID_MSG(BranchProcessor, bcctr,
                                          "CTR manipulation (bo & 0b00100) is invalid!"));
            return;
        }

        // bc !cri
        if ((bo & 0b11100) == 0b00100 && !cond_true) {
            b((s32)m_ctr, true, lk, pc);
            return;
        }

        // bc cri
        if ((bo & 0b11100) == 0b01100 && cond_true) {
            b((s32)m_ctr, true, lk, pc);
            return;
        }

        // b (call branch directly to save performance)
        if ((bo & 0b10100) == 0b10100) [[likely]] {
            b((s32)m_ctr, true, lk, pc);
            return;
        }

        pc += 4;
    }

    void BranchProcessor::crand(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) & GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, result, 32);
    }

    void BranchProcessor::crandc(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) & ~GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, result, 32);
    }

    void BranchProcessor::creqv(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) ^ GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, ~result, 32);
    }

    void BranchProcessor::cror(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) | GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, result, 32);
    }

    void BranchProcessor::crorc(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) | ~GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, result, 32);
    }

    void BranchProcessor::crnand(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) & GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, ~result, 32);
    }

    void BranchProcessor::crnor(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) | GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, ~result, 32);
    }

    void BranchProcessor::crxor(u8 bt, u8 ba, u8 bb) {
        bool result = GET_SIG_BIT(m_cr.m_crf, ba, 32) ^ GET_SIG_BIT(m_cr.m_crf, bb, 32);
        SET_SIG_BIT(m_cr.m_crf, bt, result, 32);
    }

    void BranchProcessor::mcrf(u8 bt, u8 ba) {
        u8 shift_src = ((7 - ba) * 4);
        u8 shift_dst = ((7 - bt) * 4);
        u8 result    = (m_cr.m_crf >> shift_src) & 0b1111;
        m_cr.m_crf = (m_cr.m_crf & ~(0b1111 << shift_dst)) | (result << shift_dst);
    }

    void BranchProcessor::mcrfs(u8 bt, u8 ba) {}

}  // namespace Toolbox::Interpreter