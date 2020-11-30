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
    InstructionPtr testing_decoder(){
        // page 130
        word = 0b00111001001100101111001010010011;
        Decoder dec;
        return dec.Decode(word);
    }
    InstructionPtr testing_executor(Word val1){
        Decoder _decoder;
        Executor _exe;
        InstructionPtr instr = _decoder.Decode(word);
        instr->_src1Val = val1;
        _exe.Execute(instr,0);
        return instr;
    }
};


#endif //ACS_SPRING_L2_CLASSNAME_H
