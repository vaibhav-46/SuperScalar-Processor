/*
 * =====================================================================================
 *
 *       Filename:  instructions.cpp
 *
 *    Description:  Instructions execution for MIPS Super-scalar processor
 *
 *        Version:  1.0
 *        Created:  Wednesday 14 November 2012 07:59:45  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <iostream>
#include "instructions.h"

/*  --------------------- Instruction class dummy instructions  --------------------------------- */
Instruction::Instruction( int ins )
{
   instruction = ins; 
}

Instruction::Instruction (  )
{
    instruction = -1;
}

insInfo Instruction::IDstage(int PC )
{
    insInfo object;
    object.branch = false;
    object.nextPC = PC + 1 ;
}

// Return the 
float execute ()
{
    return 0;
}
/* ---------------------- Instruction class dummy instructions end -------------------------------------- */



/* ---------------------- JInstruction class functions ------------------------------------------------ */

/* ---------------------- JInstruction class functions end ------------------------------------------------ */


/* ---------------------- IInstruction class functions ------------------------------------------------ */

/* ---------------------- IInstruction class functions end ------------------------------------------------ */


/* ---------------------- RInstruction class functions ------------------------------------------------ */

RInstruction::RInstruction ( int  ins ): Instruction ( ins )
{
    int temp = ins;
    int base = pow(2,6);
    func = ins % base;
    temp = temp / base;
    base = base/2;
    shamt = temp % base;
    temp = temp / base;
    destination = temp % base;
    temp = temp / base;
    second = temp % base;
    temp = temp / base;
    source = temp % base;
    opcode = temp / base;
    cout << " R Ins : " << opcode << " " << source << " " << second << " " << destination << " " << shamt << " " << func << endl;
}

RInstruction::RInstruction()
{
    insSet.stage = 0;
}

insInfo IDstage(int PC , RegisterFile & intRegisterFile )
{
    insSet.branch = false;
    insSet.nextPC = PC + 1;
    // TODO : Based on each opcode, set the corresponding values
    if ( intRegisterFile.isValid( source ) )
    {
        insSet.op1 = intRegisterFile.getValue ( source );
        insSet.op1tag = true;
    }
    else
    {
        insSet.op1tag = false;
        insSet.op1 = intRegisterFile.getTag ( source );
    }
    if ( intRegisterFile.isValid( second ) )
    {
        insSet.op2 = intRegisterFile.getValue ( second );
        insSet.op2tag = true;
    }
    else
    {
        insSet.op2tag = false;
        insSet.op2 = intRegisterFile.getTag ( second );
    }
    insSet.destination = destination;
    insSet.doesWrite = true;
    return insSet;
}

insInfo RInstruction::getDetails ()
{
    return insSet;
}

int canExecute()
{

}

/* ---------------------- RInstruction class functions end ------------------------------------------------ */
