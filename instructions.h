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
class ROB;

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
        unsigned int instruction;
        insInfo insSet;
        int value;

        Instruction (  unsigned int ins );
        Instruction ();
        virtual insInfo IDstage(int PC, RegisterFile & intRegisterFile, ROB & rob);
        virtual int execute ( int stage , int op1 , int op2 , int PC );
        virtual void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer &storeBuffer , int * memory );
        virtual bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        virtual bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        virtual insInfo getDetails();
        virtual int computeValue ( int op1 , int op2 , int PC );
        int random();
};

class JInstruction : public Instruction
{
    public:
        insInfo insSet;
        int opcode , offset;
        int value;
        bool addFlag;

        JInstruction (  unsigned int ins );
        JInstruction ();
        virtual insInfo IDstage(int PC, RegisterFile & intRegisterFile, ROB & rob);
        virtual int execute ( int stage , int op1 , int op2 , int PC );
        virtual void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer & storeBuffer , int * memory );
        virtual bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        virtual bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        virtual insInfo getDetails();
        virtual int computeValue ( int op1 , int op2 , int PC );
        int randomMax();
};

class RInstruction : public Instruction
{
    public:
        int opcode , source , second , destination, shamt , func;
        insInfo insSet;
        int value;

        RInstruction (  unsigned int ins );
        RInstruction ();
        virtual insInfo IDstage(int PC, RegisterFile & intRegisterFile, ROB & rob );
        virtual int execute ( int stage , int op1 , int op2 , int PC );
        virtual void commit( RegisterFile & intRegisterFile , int destination, StoreBuffer & storeBuffer , int * memory );
        virtual bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        virtual bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        virtual insInfo getDetails();
        virtual int computeValue ( int op1 , int op2 , int PC );
        int randomDoubleMax();
};

class IInstruction : public Instruction
{
    public:
        int opcode , offset, source , second , immediate;
        insInfo insSet;
        int value;
        int tempStore;
        bool addFlag;

        IInstruction (  unsigned int ins );
        IInstruction ();
        virtual insInfo IDstage(int PC, RegisterFile & intRegisterFile, ROB & rob );
        virtual int execute ( int stage , int op1 , int op2 , int PC );
        virtual void commit( RegisterFile & intRegisterFile , int destination , StoreBuffer & storeBuffer , int * memory );
        virtual bool canExecute (int stage, funcUnit & FUnit);          // Arguments to be given to this
        virtual bool lastStage(int stage);            // If execution completed  ( Instruction Dependent )
        virtual insInfo getDetails();
        virtual int computeValue ( int op1 , int op2 , int PC );
        int randomMax2();
};

#endif
