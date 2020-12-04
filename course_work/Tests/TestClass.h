//
// Created by makar on 10.04.20.
//

#ifndef ACS_SPRING_L2_CLASSNAME_H
#define ACS_SPRING_L2_CLASSNAME_H

#include "../src/BaseTypes.h"
#include "../src/Decoder.h"
#include "../src/Executor.h"

using namespace std;

class TestClass {
public:
    Word _imm=0b001110010011;
    Word oppcode = 0b111;
    Word word;
    TestClass(){

    }
    InstructionPtr testing_decoder(Word word){
        // page 130
        this->word = word;
        Decoder dec;
        return dec.Decode(word);
    }
    InstructionPtr testing_executor(Word val1, Word val2){
        Decoder _decoder;
        Executor _exe;
        InstructionPtr instr = _decoder.Decode(word);
        instr->_src1Val = val1;
        instr->_src2Val = val2;
        _exe.Execute(instr,0);
        return instr;
    }
};


#endif //ACS_SPRING_L2_CLASSNAME_H
