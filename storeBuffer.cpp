/*
 * =====================================================================================
 *
 *       Filename:  storeBuffer.cpp
 *
 *    Description:  Store Buffer functions
 *
 *        Version:  1.0
 *        Created:  Wednesday 28 November 2012 09:39:49  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include "storeBuffer.h"
#include <iostream>

using namespace std;

void StoreBuffer::addFinishedStore ( int address , int value  )
{
    storeBufferEntry newEntry;
    newEntry.address = address;
    newEntry.value = value;
    finishedStores.push_back(newEntry);
}

void StoreBuffer::writeBack ( int address , float * memory )
{
    vector<storeBufferEntry>::iterator beginIt , endIt;
    beginIt = finishedStores.begin();
    endIt = finishedStores.end();
    int flag = 0;
    for ( beginIt ; beginIt != endIt ; beginIt++ )
    {
        if ( beginIt->address == address )
        {
            flag = 1;
            break;
        }
    }
    if ( flag )
    {
        completedStores.push_back(*beginIt);
        memory[beginIt->address] = beginIt->value;
        finishedStores.erase(beginIt);
    }
    else
    {
        cout << "Trying to write something that has not yet been completed !!!" << endl;
        exit(-1);
    }
}

float StoreBuffer::loadForwardingValue ( int address )
{
    vector<storeBufferEntry>::iterator beginIt , endIt;
    beginIt = finishedStores.begin();
    endIt = finishedStores.end();
    for ( beginIt ; beginIt != endIt ; beginIt++ )
    {
        if ( beginIt->address == address )
            return beginIt->value;
    }
    return -1;
}

bool StoreBuffer::isValueUpdated ( int address )
{
    vector<storeBufferEntry>::iterator beginIt , endIt;
    beginIt = finishedStores.begin();
    endIt = finishedStores.end();
    for ( beginIt ; beginIt != endIt ; beginIt++ )
    {
        if ( beginIt->address == address )
            return true;
    }
    return false;
}
