//
// Created by makar on 10.04.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestClass.h"


using testing::Eq;
using namespace std;

namespace {
class ClassDeclaration : public testing::Test {
    public:
        TestClass obj;
        ClassDeclaration(){

        }
    };
}

TEST_F(ClassDeclaration,test1){
    cout<<"Start testing decoder";
    auto expected_instr = obj.testing_decoder();
    ASSERT_EQ(AluFunc::And, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
    ASSERT_EQ(obj._imm, expected_instr->_imm.value());
}

TEST_F(ClassDeclaration,test2){
    cout<<"Start testing executor.";
    Word val1=0b101;
    auto expected_instruction = obj.testing_executor(val1);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val&expected_instruction->_imm.value());
}



