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

//And
TEST_F(ClassDeclaration,test1){
    Word word = 0b00111001001100101111001010010011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::And, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
    ASSERT_EQ(obj._imm, expected_instr->_imm.value());
}

TEST_F(ClassDeclaration,test2){
    cout<<"Start testing executor.";
    Word val1=0b101;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val&expected_instruction->_imm.value());
}

//Add
TEST_F(ClassDeclaration, test3) {
    Word word = 0b00000000000000000000000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Add, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test4){
    Word val1=0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1, val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val+expected_instruction->_src2Val);
}

//Sll
TEST_F(ClassDeclaration, test5) {
    Word word = 0b00000000000000000001000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Sll, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test6){
    Word val1=0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val<<expected_instruction->_src2Val);
}

//Slt
TEST_F(ClassDeclaration, test7) {
    Word word = 0b00000000000000000010000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Slt, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test8){
    Word val1=-0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, 1);
}

//Sltu
TEST_F(ClassDeclaration, test9) {
    Word word = 0b00000000000000000011000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Sltu, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test10){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, 0);
}

//Xor
TEST_F(ClassDeclaration, test11) {
    Word word = 0b00000000000000000100000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Xor, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test12){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val^expected_instruction->_src2Val);
}

//Srl
TEST_F(ClassDeclaration, test13) {
    Word word = 0b00000000000000000101000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Srl, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test14){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val>>expected_instruction->_src2Val);
}

//Sra
TEST_F(ClassDeclaration, test15) {
    Word word = 0b01000000000000000101000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Sra, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test16){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_FALSE(expected_instruction->_data == expected_instruction->_src1Val>>expected_instruction->_src2Val);
    val1= 0b111;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val>>expected_instruction->_src2Val);
}

//Or
TEST_F(ClassDeclaration, test17) {
    Word word = 0b00000000000000000110000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Or, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test18){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val|expected_instruction->_src2Val);
}

//Sub
TEST_F(ClassDeclaration, test19) {
    Word word = 0b01000000000000000000000000110011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(AluFunc::Sub, expected_instr->_aluFunc);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test20){
    Word val1= -0b111;
    Word val2 = 0b1;
    auto expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src1Val-expected_instruction->_src2Val);
}

//LUI
TEST_F(ClassDeclaration, test21) {
    Word word = 0b01000000000000000000000000110111;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Alu, expected_instr->_type);
}

TEST_F(ClassDeclaration,test22){
    /*Word val1= -0b111;
    Word val2 = 0b1;*/
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_imm.value());
}

//Auipc
TEST_F(ClassDeclaration, test23) {
    Word word = 0b01000000000000000000000000010111;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Auipc, expected_instr->_type);
}

TEST_F(ClassDeclaration,test24){
    /*Word val1= -0b111;
    Word val2 = 0b1;*/
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_imm.value());
}

//JAL
TEST_F(ClassDeclaration, test25) {
    Word word = 0b01000000000000000000000001101111;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::J, expected_instr->_type);
    ASSERT_EQ(BrFunc::AT, expected_instr->_brFunc);
}

TEST_F(ClassDeclaration,test26){
    /*Word val1= -0b111;
    Word val2 = 0b1;*/
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//JALR
TEST_F(ClassDeclaration, test27) {
    Word word = 0b01000000000000000000000001100111;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Jr, expected_instr->_type);
    ASSERT_EQ(BrFunc::AT, expected_instr->_brFunc);
}

TEST_F(ClassDeclaration,test28){
    /*Word val1= -0b111;
    Word val2 = 0b1;*/
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//BEQ
TEST_F(ClassDeclaration, test29) {
    Word word = 0b01000000000000000000000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test30){
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
    Word val1= -0b111;
    Word val2 = 0b1;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_nextIp, 4);
}

//BNE
TEST_F(ClassDeclaration, test31) {
    Word word = 0b01000000000000000001000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test32){
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_nextIp, 4);
    Word val1= -0b111;
    Word val2 = 0b1;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//BLT
TEST_F(ClassDeclaration, test33) {
    Word word = 0b01000000000000000100000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test34){
    auto expected_instruction = obj.testing_executor(0,0);
    ASSERT_EQ(expected_instruction->_nextIp, 4);
    Word val1= -0b111;
    Word val2 = 0b1;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//BGE
TEST_F(ClassDeclaration, test35) {
    Word word = 0b01000000000000000101000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test36){
    auto expected_instruction = obj.testing_executor(1,0);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//BLTU
TEST_F(ClassDeclaration, test37) {
    Word word = 0b01000000000000000110000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test38){
    auto expected_instruction = obj.testing_executor(0,-1);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
    Word val1= -0b111;
    Word val2 = 0b1;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_nextIp, 4);
}

//BGEU
TEST_F(ClassDeclaration, test39) {
    Word word = 0b01000000000000000111000001100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Br, expected_instr->_type);
}

TEST_F(ClassDeclaration,test40){
    auto expected_instruction = obj.testing_executor(0,-1);
    ASSERT_EQ(expected_instruction->_nextIp, 4);
    Word val1= -0b111;
    Word val2 = 0b1;
    expected_instruction = obj.testing_executor(val1,val2);
    ASSERT_EQ(expected_instruction->_nextIp, expected_instruction->_imm.value());
}

//LW
TEST_F(ClassDeclaration, test41) {
    Word word = 0b00000000000000000010000000000011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Ld, expected_instr->_type);
    ASSERT_EQ(AluFunc::Add, expected_instr->_aluFunc);
}

TEST_F(ClassDeclaration,test42){
    auto expected_instruction = obj.testing_executor(3,0);
    ASSERT_EQ(expected_instruction->_addr, expected_instruction->_src1Val+expected_instruction->_imm.value());
}

//LB & LH
TEST_F(ClassDeclaration, test43) {
    Word word = 0b00000000000000000000000000000011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Unsupported, expected_instr->_type);
    word = 0b00000000000000000001000000000011;
    expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Unsupported, expected_instr->_type);
}

//SW
TEST_F(ClassDeclaration, test44) {
    Word word = 0b00000000000000000010000000100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::St, expected_instr->_type);
    ASSERT_EQ(AluFunc::Add, expected_instr->_aluFunc);
}

TEST_F(ClassDeclaration,test45){
    auto expected_instruction = obj.testing_executor(3,0);
    ASSERT_EQ(expected_instruction->_addr, expected_instruction->_src1Val+expected_instruction->_imm.value());
    ASSERT_EQ(expected_instruction->_data, expected_instruction->_src2Val);
}

//SB & SH
TEST_F(ClassDeclaration, test46) {
    Word word = 0b00000000000000000000000000100011;
    auto expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Unsupported, expected_instr->_type);
    word = 0b00000000000000000001000000100011;
    expected_instr = obj.testing_decoder(word);
    ASSERT_EQ(IType::Unsupported, expected_instr->_type);
}