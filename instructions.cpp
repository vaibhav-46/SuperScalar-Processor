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



/* ---------------------- Instruction class dummy instructions end -------------------------------------- */



/* ---------------------- JInstruction class functions ------------------------------------------------ */
