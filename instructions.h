/*
 * =====================================================================================
 *
 *       Filename:  instructions.h
 *
 *    Description:  Class of Instructions for the processor
 *
 *        Version:  1.0
 *        Created:  Tuesday 06 November 2012 07:53:36  IST
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

class Instruction
{
    public:
        unsigned int instruction;
        unsigned int stage;

        Instruction ( unsigned int ins );
        Instruction ();
        unsigned int IFstage();
        virtual unsigned int IDstage( unsigned int* updatingRegisters , unsigned int* gotValueRegisters , RegisterFile & registerFile );
        virtual unsigned int EXstage ( unsigned int *updatingRegisters  , unsigned int *gotValueRegisters , RegisterFile & registerFile );
        virtual unsigned int MEMstage ( unsigned int *updatingRegisters , unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int WBstage(RegisterFile & registerFile );
        virtual unsigned int execute( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int getStage ();
};

class IInstruction : public Instruction
{
    public:
        unsigned int opcode , source , second , immediate;
        unsigned int value;

        IInstruction(unsigned int ins);
        IInstruction();
        virtual unsigned int execute( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int IDstage( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int EXstage ( unsigned int *updatingRegisters , unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int MEMstage ( unsigned int *updatingRegisters , unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int WBstage(RegisterFile & registerFile );
        unsigned int computeValue(unsigned int registers[]);
        void updateUpdatingRegisters( unsigned int *updatingRegisters);
        void clearBothRegisterArrays ( unsigned int *updatingRegisters, unsigned int *gotValueRegisters);
        virtual unsigned int getStage ();
};


class RInstruction : public Instruction
{
    public: 
        unsigned int opcode , source , second , destination , shamt , func;
        unsigned int value;
    
        RInstruction(unsigned int ins);
        RInstruction();
        virtual unsigned int execute( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int IDstage( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int EXstage ( unsigned int *updatingRegisters , unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int MEMstage ( unsigned int *updatingRegisters , unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int WBstage(RegisterFile & registerFile );
        unsigned int computeValue(unsigned int registers[]);
        void updateUpdatingRegisters( unsigned int *updatingRegisters);
        void clearBothRegisterArrays ( unsigned int *updatingRegisters, unsigned int *gotValueRegisters);
        virtual unsigned int getStage ();
};

class JInstruction : public Instruction
{
    public:
        unsigned int opcode , offset;

        JInstruction ( unsigned int ins );
        JInstruction();
        virtual unsigned int execute( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int IDstage( unsigned int *updatingRegisters, unsigned int *gotValueRegisters, RegisterFile & registerFile );
        virtual unsigned int getStage ();
};

#endif
