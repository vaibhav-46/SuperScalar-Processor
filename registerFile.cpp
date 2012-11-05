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
    int i = 0;
    for ( i = 0; i < NoOfRegisters ; i++ )
    {
        registers[i] = 0;        
        busy[i] = 0;
        tag[i] = -1;
    }
    for ( i = 0; i < NoOfRenameRegisters ; i++ )
    {
        registers[ NoOfRegisters + i ] = 0;
        valid[i] = 0;
        RRFbusy[i] = 0;
    }
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
    assert( i < 32 )
    {
        cout << "Renaming a renamed variable !! " << endl;
        exit(-1);
    }
    for ( int i = NoOfRegisters ; i < NoOfRegisters+NoOfRenameRegisters ; i++ )
    {
        if ( RRFbusy[i-NoOfRegisters]  )
            continue;
        RRFbusy[i-NoOfRegisters] = 1;
        busy[index] = 1;
        tag[index] = i;
        valid[i-NoOfRegisters] = 0;
        return i;
    }
    cout << "ERROR : All the renameRegisters are taken !! " << endl;
    return -1;
}

void updateRegisters ( int index , T value )
{
    assert ( index < 32 )
    {
        cout << "Writing to a non-renamed variable !! " << endl;
        exit(-1);
    }
    registers[index] = value;
    valid[index-NoOfRegisters] = 1;
}

void finishExecutionRegister ( int index )
{
    for ( int i = 0; i < NoOfRegisters ; i++ )
    {
        if ( tag[i] == index )
        {
            tag[i] = -1;
            RRFbusy[index] = 0;
            busy[i] = 0;
        }
    }
    registers[index] = value;
    valid[index-NoOfRegisters]  = 0;
}

bool isValid ( int registerTag )
{
    if ( registerTag < NoOfRegisters )
    {
        if ( busy[registerTag] )
        {
            if ( tag[registerTag] != -1 )
            {
                if ( valid[tag[registerTag]-NoOfRegisters] == 1 )
                    return 1;
                else
                    return 0;
            }
            else
            {
                cout << "Error : Register renamed , Busy but Tag not found!!";
                exit(-1);
            }
        }
        else
            return 1;
    }
    else
    {
        if ( RRFbusy [ registerTag - NoOfRegisters ] == 1 )
        {
            if ( valid[registerTag-NoOfRegisters] == 1 )
                return 1;
            else
                return 0;
        }
        else
        {
                cout << "Renamed register but not busy !! " << endl;
                exit(-1);
       }

    }
    return 0;
}

int getValue ( int regTag )
{
    if ( regTag < 31 )
    {
        if ( busy[regTag] )
        {
            if ( valid[tag[regTag] - NoOfRegisters] )
                return registers[tag[regTag] - NoOfRegisters];
            else
            {
                cout << " Error : Not valid , but asking for value" << endl;
                exit(-1);
            }
        }
        else
        {
            return registers[regTag];
        }
    }
    else
    {
        if ( valid [ regTag - NoOfRegisters ] )
            return registers [ regTag ];
        else
            cout << "Error : Not a valid renamed register !!" << endl;
    }
    return -1;
}

int getTag ( int regTag )
{
    if ( regTag > NoOfRegisters - 1 )
        return regTag;
    else
    {
        return tag[regTag];
    }
}


