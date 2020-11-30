
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"
#include <cmath>

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
        //Alu
        Word result;
        if (instr->_src1.has_value()){
            if (instr->_imm.has_value()){
                result = Alu_function(instr->_aluFunc, instr->_src1Val, instr->_imm.value());
            }
            else {
                result = Alu_function(instr->_aluFunc, instr->_src1Val, instr->_src2Val);
            }

        }
        switch (instr->_type) {
            case IType::Alu:
                if (instr->_src1.has_value())
                    instr->_data = result;
                break;
            case IType::Csrr:
                instr->_data = instr->_csrVal;
                break;
            case IType::Csrw:
                instr->_data = instr->_src1Val;
                break;
            case IType::Auipc:
                instr->_data = ip + instr->_imm.value();
                break;
            case IType::St:
                instr->_addr = result;
                instr->_data = instr->_src2Val;
                break;
            case IType::Ld:
                instr->_addr = result;
                break;
            case IType::J:
            case IType::Jr:
                instr->_data = ip + 4;
                break;
        }
        // Branch
        bool verdict = Branch_function(instr->_brFunc, instr->_src1Val, instr->_src2Val);
        if (verdict) {
            switch (instr->_type) {
                case IType::Br:
                case IType::J:
                    instr->_nextIp = ip + instr->_imm.value();
                    break;
                case IType::Jr:
                    instr->_nextIp = instr->_imm.value() + instr->_src1Val;
                    break;
            }
        } else {
            instr->_nextIp = ip + 4;
        }
    }

private:
    Word Alu_function(AluFunc _type, Word A, Word B){
        switch (_type) {
            case AluFunc::Add:
                return A + B;
            case AluFunc::Sub:
                return A - B;
            case AluFunc::And:
                return A & B;
            case AluFunc::Or:
                return A | B;
            case AluFunc::Xor:
                return A ^ B;
            case AluFunc::Slt:
                return (signed)A < (signed)B;
            case AluFunc::Sltu:
                return A < B;
            case AluFunc::Sll:
                B = B % 32;
                return A << B;
            case AluFunc::Srl:
                B = B % 32;
                return A >> B;
            case AluFunc::Sra:
                B = B % 32;
                return (signed)A >> (signed)B;
        }
    }
    bool Branch_function(BrFunc _brFunc, Word A, Word B) {
        switch (_brFunc) {
            case BrFunc::Eq:
                return A==B;
            case BrFunc::Neq:
                return A!=B;
            case BrFunc::AT:
                return true;
            case BrFunc::Ge:
                return (signed)A >= (signed)B;
            case BrFunc::Geu:
                return A >= B;
            case BrFunc::Lt:
                return (signed)A < (signed)B;
            case BrFunc::Ltu:
                return A < B;
            case BrFunc::NT:
                return false;
        }
    }
};

#endif // RISCV_SIM_EXECUTOR_H
