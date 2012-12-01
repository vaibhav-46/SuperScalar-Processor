/*
 * =====================================================================================
 *
 *       Filename:  instructions.h
 *
 *    Description:  Instructions Header file ( Takes all different types of instructions into account )
 *
 *        Version:  1.0
 *        Created:  Tuesday 13 November 2012 03:20:50  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define ADD_ALU 2
#define MUL_ALU 2
#define DIV_ALU 2
#define BIT_ALU 2
#define MUL_LATENCY 3
#define DIV_LATENCY 2
#define ADD_LATENCY 1
#define BIT_LATENCY 1

class RegisterFile;
class StoreBuffer;

typedef struct _funcUnit
{
    bool execute;
    bool mul[MUL_ALU][MUL_LATENCY];
    bool div[DIV_ALU][DIV_LATENCY];
    bool add[ADD_ALU][ADD_LATENCY];
    bool bitOp[BIT_ALU][BIT_LATENCY];
}funcUnit;

typedef struct _insInfo
{
    bool branch;
    int nextPC;
    float op1;
    float op2;
    int destination;
    bool op1tag;
    bool op2tag;
    bool doesWrite;
}insInfo;

class Instruction
{
    public:
        int instruction;
        insInfo insSet;
        int value;

        Instruction (  int ins );
        Instruction ();
        insInfo IDstage(int PC, RegisterFile & intRegisterFile);
        int execute ( int stage , int op1 , int op2 , int PC );
        void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer &storeBuffer , int * memory );
        bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
        int computeValue ( int op1 , int op2 , int PC );
};

class JInstruction : public Instruction
{
    public:
        insInfo insSet;
        int opcode , offset;
        int value;
        bool addFlag;

        JInstruction (  int ins );
        JInstruction ();
        insInfo IDstage(int PC, RegisterFile & intRegisterFile);
        int execute ( int stage , int op1 , int op2 , int PC );
        void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer & storeBuffer , int * memory );
        bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
        int computeValue ( int op1 , int op2 , int PC );
};

class RInstruction : public Instruction
{
    public:
        int opcode , source , second , destination, shamt , func;
        insInfo insSet;
        int value;

        RInstruction (  int ins );
        RInstruction ();
        insInfo IDstage(int PC, RegisterFile & intRegisterFile);
        int execute ( int stage , int op1 , int op2 , int PC );
        void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer & storeBuffer , int * memory );
        bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
        int computeValue ( int op1 , int op2 , int PC );
};

class IInstruction : public Instruction
{
    public:
        int opcode , offset, source , second , immediate;
        insInfo insSet;
        int value;
        int tempStore;
        bool addFlag;

        IInstruction (  int ins );
        IInstruction ();
        insInfo IDstage(int PC, RegisterFile & intRegisterFile);
        int execute ( int stage , int op1 , int op2 , int PC );
        void commit( RegisterFile & intRegisterFile , int destination , StoreBuffer & storeBuffer , int * memory );
        bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
        int computeValue ( int op1 , int op2 , int PC );
};

#endif
