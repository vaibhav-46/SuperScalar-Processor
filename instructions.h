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

#define MUL_LATENCY 2
#define DIV_LATENCY 2
#define ADD_LATENCY 1

typedef struct _insInfo
{
    bool branch;
    int nextPC;
    float op1;
    float op2;
    int destination;
    bool op1tag;
    bool op2tag;
    bool doesWrite
}insInfo;

class Instruction
{
    public:
        int instruction;
        insInfo insSet;

        Instruction (  int ins );
        Instruction ();
        insInfo IDstage(int PC);
        float execute();            // Maybe in this , once we are done executing the instruction , we then compute the memory location if necessary.
        void commit();
        // TODO : In canExecute , make sure you take FUnit by reference and update the ALU unit corresponding entry
        int canExecute (funcUnit & FUnit);          // Arguments to be given to this
        int lastStage();            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
};

class JInstruction : public Instruction
{
    public:
        int instruction;
        insInfo insSet;

        JInstruction (  int ins );
        JInstruction ();
        insInfo IDstage();
        float execute();   
        void commit();
        int canExecute ();          // Arguments to be given to this
        int lastStage();            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
};

class RInstruction : public Instruction
{
    public:
        int instruction;
        unsigned int opcode , source , second , destination, shamt , function;
        insInfo insSet;

        RInstruction (  int ins );
        RInstruction ();
        insInfo IDstage();
        float execute();    
        void commit();
        int canExecute ();          // Arguments to be given to this
        int lastStage();            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
};

class IInstruction : public Instruction
{
    public:
        int instruction;
        unsigned int opcode , offset;
        insInfo insSet;

        IInstruction (  int ins );
        IInstruction ();
        insInfo IDstage();
        float execute();     
        void commit();
        int canExecute ();          // Arguments to be given to this
        int lastStage();            // If execution completed  ( Instruction Dependent )
        insInfo getDetails();
};

#endif
