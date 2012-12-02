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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "registerFile.h"
#include "storeBuffer.h"

using namespace std;

/*  --------------------- Instruction class dummy instructions  --------------------------------- */
Instruction::Instruction( unsigned int ins )
{
   instruction = ins; 
}

Instruction::Instruction (  )
{
    instruction = -1;
}

insInfo Instruction::IDstage(int PC , RegisterFile & intRegisterFile )
{
    insInfo object;
    object.branch = false;
    object.nextPC = PC + 1 ;
    return object;
}

int Instruction::execute ( int stage , int op1 , int op2 ,int PC )
{
    return 0;
}

void Instruction::commit ( RegisterFile & intRegisterFile , int destination , StoreBuffer & storeBuffer , int * memory )
{
    return;
}

bool Instruction::canExecute ( int stage , funcUnit & FUnit )
{
    return true;
}

bool Instruction::lastStage ( int stage )
{
    return false;
}

insInfo Instruction::getDetails()
{
    return insSet;
}

int Instruction::computeValue ( int op1 , int op2 , int PC )
{
    return 0;
}

int Instruction::random ()
{
    return 1;
}

/* ---------------------- Instruction class dummy instructions end -------------------------------------- */



/* ---------------------- JInstruction class functions ------------------------------------------------ */

JInstruction::JInstruction ( unsigned int ins )
: Instruction(ins)
{
    unsigned int base = pow(2,26);
    offset = ins % base;
    opcode = ins / base;
    addFlag = 1;
}

int JInstruction::randomMax()
{
    return 1;
}

JInstruction::JInstruction ()
{
    value = 0;
}

insInfo JInstruction::IDstage( int PC , RegisterFile & intRegisterFile )
{
    insSet.branch = true;
    if ( opcode == 2 )
    {
        insSet.doesWrite = false;
        insSet.nextPC = PC + offset;
        return insSet;
    }
    else if ( opcode == 3 )
    {
        insSet.doesWrite = true;
        insSet.nextPC = PC + offset;
        return insSet;
    }
    else
        return insSet;
}

void JInstruction::commit( RegisterFile & intRegisterFile , int destination , StoreBuffer & storeBuffer , int * memory )
{
    if ( opcode == 2 )
        return;
    else
    {
        intRegisterFile.updateRegisters ( destination , offset );
        return;
    }
}

// Since the return address is always given at the ID stage itself , we just have to return -1 and not the next PC
int JInstruction::execute ( int stage , int op1 , int op2 , int PC )
{
    return -1;
}

bool JInstruction::canExecute(int stage , funcUnit & FUnit)
{
    return 1;
}

bool JInstruction::lastStage ( int stage )
{
    return 1;
}

insInfo JInstruction::getDetails()
{
    return insSet;
}

int JInstruction::computeValue ( int op1 , int op2 , int PC )
{
    return offset;
}
/* ---------------------- JInstruction class functions end ------------------------------------------------ */


/* ---------------------- IInstruction class functions ------------------------------------------------ */
IInstruction::IInstruction ( unsigned int ins ) : Instruction ( ins )
{
    int temp = ins;
    unsigned int base = pow(2,16);
    immediate  = temp % base;
    temp = temp / base;
    second = temp % 32;
    temp = temp / 32;
    source = temp % 32;
    temp = temp / 32;
    opcode = temp;
    addFlag = 1;
    cout << "I ins :"  << opcode << " " << source << " " << second << " " << immediate << endl;
}

IInstruction::IInstruction()
{
    value = 0;
}

insInfo IInstruction::IDstage ( int PC , RegisterFile & intRegisterFile )
{
    if ( opcode < 8 )
    {
        insSet.branch = true;
        if ( intRegisterFile.isValid(source) && intRegisterFile.isValid(second) )
        {
            switch(opcode)
            {
                case 4:
                    if ( intRegisterFile.getValue(source) == intRegisterFile.getValue(second) )
                        insSet.nextPC = PC+immediate;
                    else
                        insSet.nextPC = PC+1;
                case 5:
                        if ( intRegisterFile.getValue(source) != intRegisterFile.getValue(second) )
                            insSet.nextPC = PC+immediate;
                        else
                            insSet.nextPC = PC+1;
                case 6:
                        if ( intRegisterFile.getValue(source) <= 0 )
                            insSet.nextPC = PC+immediate;
                        else
                            insSet.nextPC = PC+1;
                case 7:
                        if ( intRegisterFile.getValue(source) >= 0 )
                            insSet.nextPC = PC+immediate;
                        else
                            insSet.nextPC = PC+1;
            }
        }
        else
        {
            addFlag = false;
            insSet.nextPC = -1769;
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
       insSet.branch = false; 
       insSet.doesWrite = true;
       insSet.destination = second;
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
    else if ( opcode < 40 )
    {
        insSet.branch = false;
        insSet.doesWrite = true;
        if ( intRegisterFile.isValid( source ) )
        {
            insSet.op1 = intRegisterFile.getValue ( source );
            insSet.op1tag = true;
        }
        else
        {
            insSet.op1 = intRegisterFile.getTag ( source );
            insSet.op1tag = false;
        }
        insSet.destination = second;
    }
    else
    {
        insSet.branch = false;
        insSet.doesWrite = false;
        if ( intRegisterFile.isValid( source ) )
        {
            insSet.op1 = intRegisterFile.getValue ( source );
            insSet.op1tag = true;
        }
        else
        {
            insSet.op1 = intRegisterFile.getTag ( source );
            insSet.op1tag = false;
        }
        if ( intRegisterFile.isValid( second ) )
        {
            insSet.op2 = intRegisterFile.getValue ( second );
            insSet.op2tag = true;
        }
        else
        {
            insSet.op2 = intRegisterFile.getTag ( second );
            insSet.op2tag = false;
        }
    }
    return insSet;
}

int IInstruction::randomMax2()
{
    return 1;
}

insInfo IInstruction::getDetails ( )
{
    return insSet;
}

bool IInstruction::lastStage (int stage)
{
    if ( opcode < 8 )
        return true;
    else if ( opcode < 10 )
    {
        if ( stage == ADD_LATENCY )
        {
            return true;
        }
        else
            return false;
    }
    else if ( opcode < 16 )
    {
        if ( stage == BIT_LATENCY )
            return true;
        else
            return false;
    }
    else
    {
        if ( stage == ADD_LATENCY )
            return true;
        else
            return false;
    }
}

bool IInstruction::canExecute(int stage , funcUnit & FUnit)
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
            if ( FUnit.bitOp[i][stage-1] == 0 )
            {
                FUnit.bitOp[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else
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
}

int IInstruction::computeValue ( int op1 , int op2 , int PC )
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
            return op1 || immediate;
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

int IInstruction::execute ( int stage , int op1 , int op2 , int PC )
{
    if ( ! lastStage(stage) )
        return -1;
    else
    {
        value = computeValue ( op1 , op2 , PC );
        if ( opcode > 39 )
            tempStore = op2;
        if ( addFlag && opcode >= 8 )
            return value;
        else if ( addFlag && opcode < 8 )
            return -1;
        else if ( !addFlag )
            return value;
        else
            return value;
    }
}

void IInstruction::commit( RegisterFile & intRegisterFile , int destination , StoreBuffer & storeBuffer , int * memory )
{
    if ( opcode < 32 )
        intRegisterFile.updateRegisters ( destination , value );
    else if ( opcode == 32 )
    {
        if ( storeBuffer.isValueUpdated ( value ) )
        {
            intRegisterFile.updateRegisters ( destination , storeBuffer.loadForwardingValue ( value ) );
        }
        else
        {
            intRegisterFile.updateRegisters ( destination , memory[value] );
        }
    }
    else if ( opcode == 34 )
    {
        int temp = 0;
        for ( int i = 0 ; i < 4 ; i++ )
        {
            if ( storeBuffer.isValueUpdated ( value+i ) )
                temp = temp *2+storeBuffer.loadForwardingValue ( value+i ) ;
            else
                temp = temp*2+ memory[value+i];
        }
        intRegisterFile.updateRegisters ( destination , temp );
    }
    else if ( opcode == 40 )
        storeBuffer.addFinishedStore ( value , tempStore );
    else if ( opcode == 42 )
    {
        for ( int i = 0 ; i < 4 ; i++ )
            storeBuffer.addFinishedStore ( value+i , tempStore );
    }
}

/* ---------------------- IInstruction class functions end ------------------------------------------------ */


/* ---------------------- RInstruction class functions ------------------------------------------------ */

RInstruction::RInstruction ( unsigned int  ins ): Instruction ( ins )
{
    int temp = ins;
    unsigned int base = pow(2,6);
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
    value = 0;
}

insInfo RInstruction::IDstage(int PC , RegisterFile & intRegisterFile )
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

bool RInstruction::canExecute(int stage , funcUnit & FUnit)
{
    if ( opcode == 32 || opcode == 33 || opcode == 34 || opcode == 35 )
    {
        for ( int i = 0; i < ADD_ALU ; i++ )
        {
            if ( FUnit.add[i][stage-1] == 0 )
            {
                FUnit.add[i][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode > 35 || opcode < 8  )
    {
        for ( int j = 0 ; j < BIT_ALU ; j++ )
        {
            if ( FUnit.bitOp[j][stage-1] == 0 )
            {
                FUnit.bitOp[j][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode > 15 && opcode < 26 ) 
    {
        for ( int j = 0; j < MUL_ALU ; j++ )
        {
            if ( FUnit.mul[j][stage-1] == 0 )
            {
                FUnit.mul[j][stage-1] = 1;
                return true;
            }
        }
        return false;
    }
    else if ( opcode == 26 || opcode == 27 )
    {
        for ( int j = 0; j < DIV_ALU ; j++ )
        {
            if ( FUnit.div[j][stage-1] == 0 )
            {
                FUnit.div[j][stage-1] = 1;
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
        if ( stage == BIT_LATENCY )
            return true;
        else
            return false;
    }
    else if ( opcode > 32 )
    {
        if ( stage == ADD_LATENCY )
            return true;
        else
            return false;
    }
    else if ( opcode == 26 || opcode == 27 )
    {
        if ( stage == DIV_LATENCY )
            return true;
        else
            return false;
    }
    else
    {
        if ( stage == MUL_LATENCY )
            return true;
        else
            return false;
    }
}

int RInstruction::computeValue ( int op1 , int op2 , int PC )
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

int RInstruction::execute ( int stage , int op1 , int op2 , int PC )
{
    if ( ! lastStage ( stage ) )
        return 1;
    else
    {
        value = computeValue ( op1 , op2 , PC );
        return value;
    }
}

void RInstruction::commit ( RegisterFile & intRegisterFile, int destination , StoreBuffer & storeBuffer , int * memory )
{
   intRegisterFile.updateRegisters ( destination , value ); 
}

int RInstruction::randomDoubleMax()
{
    return 1;
}
/* ---------------------- RInstruction class functions end ------------------------------------------------ */
