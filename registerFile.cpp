/*
 * =====================================================================================
 *
 *       Filename:  registerFile.cpp
 *
 *    Description:  RegisterFile implementation
 *
 *        Version:  1.0
 *        Created:  Saturday 03 November 2012 07:47:13  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <iostream>
#include "registerFile.h"
#include "rob.h"
using namespace std;

RegisterFile::RegisterFile()
{
    int i = 0;
    for ( i = 0; i < NoOfRegisters ; i++ )
    {
        registers[i] = 0;        
        busy[i] = 0;
        tag[i] = -1;
    }
    // Update values of registers here
    registers[0] = 0;
    registers[5] = 5;
    registers[1] = 1;
    registers[6] = 0;
    registers[8] = 2;
    registers[9] = 24;
    registers[7] = 144;
}

int RegisterFile::noPortsWritable ()
{
    int count=0;
    for ( int i = 0 ; i < WRITEPORTS ; i++ )
    {
        if ( writePort[i] == 0 )
            count++;
    }
    return count;
}

int RegisterFile::noPortsReadable()
{
    int count = 0;
    for ( int i = 0; i < READPORTS ; i++ )
    {
        if ( readPort[i] == 0 )
            count++;
    }
    return count;
}

void RegisterFile::setWritePortsValue ( int number , int set )
{
    for ( int i = 0 ; i < WRITEPORTS ; i++ )
    {
        if ( set )
        {
            if ( writePort[i] == 0 )
            {
                number--;
                writePort[i] = 1;
            }
        }
        else
        {
            if ( writePort[i] == 1 )
            {
                number--;
                writePort[i] = 0;
            }
        }
        if ( number == 0 )
            break;
    }
}

void RegisterFile::setReadPortsValue ( int number , int set )
{
    for ( int i = 0 ; i < READPORTS ; i++ )
    {
        if ( set )
        {
            if ( readPort[i] == 0 )
            {
                number--;
                readPort[i] = 1;
            }
        }
        else
        {
            if ( readPort[i] == 1 )
            {
                number--;
                readPort[i] = 0;
            }
        }
        if ( number == 0 )
            break;
    }
}

void RegisterFile::printContents()
{
    cout << "Register file contents : " << endl;
    for ( int i = 0; i < NoOfRegisters ; i++ )
    {
        cout << "R" << i << " : " << registers[i]<<"  ";
        if ( i > 0 && i % 4 == 0 )
            cout << endl;
    }
}

int RegisterFile::renameVariable ( int index , int ROBindex )
{
    busy[index] = 1;
    tag[index] = ROBindex;
    return ROBindex;
}


void RegisterFile::updateRegisters ( int index , int value )
{
    int i;
    for ( i = 0; i < NoOfRegisters ; i++ )
    {
        if ( tag[i] == index )
            break;
    }
    if ( i == NoOfRegisters )
        return;
    registers[i] = value;
    busy[i] = 0;
    tag[i] = -1;
}

void RegisterFile::updateRegisterTags ()
{
    for ( int i = 0 ; i < NoOfRegisters; i++ )
    {
        if ( tag[i] >= 0 )
            tag[i]--;
    }
}

bool RegisterFile::isValid ( int regTag , ROB & reOrderBuffer )
{
    if ( busy[regTag] )
    {
        if ( reOrderBuffer.isValid ( tag[regTag] ) )
            return true;
        else
            return false;
    }
    else
        return true;
}

int RegisterFile::getValue ( int regTag , ROB & reOrderBuffer )
{
    if ( busy[regTag] )
        return reOrderBuffer.getValue ( tag[regTag] );
    else
        return registers[regTag];
}

int RegisterFile::getTag ( int regTag )
{
    return tag[regTag];
}
