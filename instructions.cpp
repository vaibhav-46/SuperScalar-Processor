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
int execute ( int stage , int op1 , int op2 )
{
    return 0;
}
/* ---------------------- Instruction class dummy instructions end -------------------------------------- */



/* ---------------------- JInstruction class functions ------------------------------------------------ */

/* ---------------------- JInstruction class functions end ------------------------------------------------ */


/* ---------------------- IInstruction class functions ------------------------------------------------ */
IInstruction::IInstruction ( int ins ) : Instruction ( ins )
{
    int temp = ins;
    int base = pow(2,16);
    immediate  = temp % base;
    temp = temp / base;
    second = temp % 32;
    temp = temp / 32;
    source = temp % 32;
    temp = temp / 32;
    opcode = temp;
    cout << "I ins :"  << opcode << " " << source << " " << second << " " << immediate;
}

int IInstruction::IInstruction()
{
    stage = 0;
}

insInfo IDstage ( int PC , RegisterFile & intRegisterFile )
{
    if ( opcode < 8 )
    {
        insSet.branch = true;
        if ( intRegisterFile.isValid(op1) && intRegisterFile.isValid(op2) )
        {
            switch(opcode):
            {
                // TODO : Set appropriate branch instructions for all these commands
                case 4:
                    if ( intRegisterFile.getValue(op1) == intRegisterFile.getValue(op2) )
                    else
                case 5:
                        if ( intRegisterFile.getValue(op1) != intRegisterFile.getValue(op2) )
                        else
                case 6:
                        if ( intRegisterFile.getValue(op1) )
            }
        }
        else
        {
            insSet.nextPC = 0;
            insSet.op1 = intRegisterFile.getTag(source);
            insSet.op2 = intRegisterFile.getTag(second);
            insSet.op1tag = false;
            insSet.op2tag = false;
            insSet.doesWrite = false; 
            insSet.destination = -1;
        }
    }
    else if ( opcode < 16 )
    {
       insSet.Branch = false; 
       insSet.doesWrite = true;
       insSet.destination = destination;
       if ( intRegisterFile.isValid ( source ) )
       {
           insSet.op1 = intRegisterFile.getValue(source);
           insSet.op1tag = true;
       }
       else
       {
           insSet.op1 = intRegisterFile.getTag ( source );
           insSet.op1tag = false;
       }
       if ( intRegisterFile.isValid ( second ) )
       {
           insSet.op2 = intRegisterFile.getValue ( second );
           insSet.op2tag = true;
       }
       else
       {
           insSet.op2 = intRegisterFile.getTag(second);
           insSet.op2tag = false;
       }
       insSet.nextPC = PC + 1;
    }
    else 
    {
        insSet.Branch = false;
        insSet.doesWrite = true;
        // TODO : Figure out what to do for load-store
    }
}

insInfo IInstruction::getDetails ( )
{
    return insSet;
}

bool lastStage (int stage)
{
    if ( opcode < 8 )
        return true;
    else if ( opcode < 10 )
    {
        if ( stage+1 == ADD_LATENCY )
        {
            return true;
        }
        else
            return false;
    }
    else if ( opcode < 16 )
    {
        if ( stage+1 == BIT_LATENCY )
            return true;
        else
            return false;
    }
    else
        // Assuming that load-store instructions take one cycle to compute the effective address
        return true;
}

bool IInstruction:canExecute(int stage , funcUnit & FUnit)
{
    if ( opcode < 8 )
        return true;
    else if ( opcode < 10 )
    {
        for ( int i = 0 ; i < ADD_ALU ; i++ )
        {
            if ( FUnit.add[i][stage-1] == 0 )
            {
                FUnit.add[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode < 16 )
    {
        for ( int i = 0 ; i < BIT_ALU ; i++ )
        {
            if ( FUnit.bit[i][stage-1] == 0 )
            {
                FUnit.bit[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else
    {
        // TODO : Figure out what to do for load-store instructions
    }
}

int computeImmValue ( int op1 , int op2 , int PC )
{
    switch(opcode)
    {
        case 4:
            if ( op1 == op2 )
                return PC + immediate;
            else
                return PC+1;
        case 5:
            if ( op1 != op2 )
                return PC+immediate;
            else
                return PC+1;
        case 6:
            if ( op1 < 0 )
                return PC+immediate;
            else
                return PC+1;
        case 7:
            if ( op1 > 0 )
                return PC+1;
        case 8:
            return op1+op2;
        case 9:
            return op1+op2;
        case 10:
            return op1 < op2;
        case 11:
            return op1 < op2;
        case 12:
            return op1 && immediate;
        case 13:
            return op1 || imediate;
        case 14:
            return op1 ^ immediate;
        case 32:
        case 33:
        case 35:
        case 36:
        case 37:
        case 40:
        case 41:
        case 43:
            return op1 + immediate;
        default:
            {
            cout << "Wrong opcode for I type instructions . Computing value of a opcode unknown";
            exit(-1);
            }
    }
}

int IInstruction:execute ( int stage , int op1 , int op2 , int PC )
{
    if ( ! lastStage(stage) )
        return -1;
    else
        computeImmValue ( op1 , op2 , PC );
}

void commit()
{
    return;
}

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

bool canExecute(int stage , funcUnit & FUnit)
{
    if ( opcode == 32 || opcode == 33 || opcode == 34 || opcode == 35 )
    {
        for ( int i = 0; i < ADD_ALU ; i++ )
        {
            if ( FUnit.add[i][stage-1] == 0 )
            {
                FUnit[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode > 35 || opcode < 8  )
    {
        for ( int j = 0 ; j < BIT_ALU ; j++ )
        {
            if ( FUnit.bit[i][stage-1] == 0 )
            {
                FUnit[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode > 15 && opcode < 26 ) 
    {
        for ( int j = 0; j < MUL_ALU ; j++ )
        {
            if ( FUnit.mul[i][stage-1] == 0 )
            {
                FUnit[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode == 26 || opcode == 27 )
    {
        for ( int j = 0; j < DIV_ALU ; j++ )
        {
            if ( FUnit.div[i][stage-1] == 0 )
            {
                FUnit.div[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    cout << "Instruction not in any R type. Jr or Jalr found !! Not supported ";
    exit(-1);
}

bool RInstruction::lastStage ( int stage )
{
    if ( opcode < 8 || opcode > 35 )
    {
        if ( stage+1 == BIT_LATENCY )
            return true;
        else
            return false;
    }
    else if ( opcode > 32 )
    {
        if ( stage+1 == ADD_LATENCY )
            return true;
        else
            return false;
    }
    else if ( opcode == 26 || opcode == 27 )
    {
        if ( stage+1 == DIV_LATENCY )
            return true;
        else
            return false;
    }
    else
    {
        if ( stage+1 == MUL_LATENCY )
            return true;
        else
            return false;
    }
}

int computeValue ( int op1 , int op2 )
{
    switch(func)
    {
        case 0:
            return op2<<shamt;
        case 2:
            return op2>>shamt;
        case 3:
            return op2>>shamt;
        case 4:
            return op2<<op1;
        case 6:
            return op2>>op1;
        case 7:
            return op2>>op1;
        case 8:
            return -1;
        case 9:
            return op1;
        case 17:
            return op1;
        case 19:
            return op1;
        case 24:
            return op1*op2;
        case 25:
            return op1*op2;
        case 26:
            return op1/op2;
        case 27:
            return op1/op2;
        case 32:
            return op1+op2;
        case 33:
            return op1+op2;
        case 34:
            return op1-op2;
        case 35:
            return op1-op2;
        case 36:
            return op1&op2;
        case 37:
            return op1|op2;
        case 38:
            return op1^op2;
        case 39:
            return ~(op1|op2);
        case 42:
            return op1<op2;
        case 43:
            return op1<op2;
        default:
            cout << "Function opcode not found in the list . Wrong function code given : " << func << endl;

    }
    return -2;
}

int execute ( int stage , int op1 , int op2 )
{
    if ( ! lastStage ( stage ) )
        return 1;
    else
        return computeValue ( op1 , op2 );
}

void commit ( )
{
    return ;
}

/* ---------------------- RInstruction class functions end ------------------------------------------------ */
