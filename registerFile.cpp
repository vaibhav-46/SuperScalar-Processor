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

RegisterFile RegisterFile()
{
    for ( int i = 0,j=0; i < NoOfRegisters ; i++ )
    {
        registers[i] = 0;
        tag[i] = -1;
        busy[j] = busy[j+1] = busy[j+2] = 0;
        j = j+3;
    }
    notBusyIndex = 0;
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

int renameVariable ( int index )
{
    for ( int i = 0 ; i < NoOfRenameRegisters ; i++ )
    {
        if ( busy[i] )
            continue;
        busy[i] = 1;
        tag[index] = i;
        return i;
    }
    cout << "ERROR : All the renameRegisters are taken !! " << endl;
    return -1;
}

void updateRegisters ( int index , T value )
{
    for ( int i = 0; i < NoOfRegisters ; i++ )
    {
        if ( tag[i] == index )
        {
            tag[i] = -1;
            busy[index] = 0;
            registers[i] = value;
        }
    }
    renamedRegisters[index] = value;
}
