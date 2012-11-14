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

typedef struct _insInfo
{
    bool branch;
    int nextPC;
    float op1;
    float op2;
    int destination;
    bool op1tag;
    bool op2tag;
}insInfo;

class Instruction
{
    public:
        unsigned int instruction;
        insInfo insInfo;

        Instruction ( unsigned int ins );
        Instruction ();
        insInfo IDstage();
        float WBstage();            // TODO : Figure out what to do in this stage 
        float execute();            // Maybe in this , once we are done executing the instruction , we then compute the memory location if necessary.
};

class JInstruction : public Instruction
{
    public:
        unsigned int instruction;
        insInfo insInfo;

        JInstruction ( unsigned int ins );
        JInstruction ();
        insInfo IDstage();
        float WBstage();            // TODO : Figure out what to do in this stage 
        float execute();            // Maybe in this , once we are done executing the instruction , we then compute the memory location if necessary.
};

class RInstruction : public Instruction
{
    public:
        unsigned int instruction;
        insInfo insInfo;

        RInstruction ( unsigned int ins );
        RInstruction ();
        insInfo IDstage();
        float WBstage();            // TODO : Figure out what to do in this stage 
        float execute();            // Maybe in this , once we are done executing the instruction , we then compute the memory location if necessary.
};

class IInstruction : public Instruction
{
    public:
        unsigned int instruction;
        insInfo insInfo;

        IInstruction ( unsigned int ins );
        IInstruction ();
        insInfo IDstage();
        float WBstage();            // TODO : Figure out what to do in this stage 
        float execute();            // Maybe in this , once we are done executing the instruction , we then compute the memory location if necessary.
};



#endif
