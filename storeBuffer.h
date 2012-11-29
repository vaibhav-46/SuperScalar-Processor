/*
 * =====================================================================================
 *
 *       Filename:  storeBuffer.h
 *
 *    Description:  Store Buffer for memory consistency of Load and Stores
 *
 *        Version:  1.0
 *        Created:  Wednesday 28 November 2012 09:29:20  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef STOREBUFFER_H
#define STOREBUFFER_H

#include <vector>

typedef struct _entry
{
    int address;
    float value;
}storeBufferEntry;

class StoreBuffer
{
    vector<storeBufferEntry> finishedStores;
    vector<storeBufferEntry> completedStores;

    void addFinishedStore(int address, int value );
    void writeBack ( int address, float *memory );
    float loadForwardingValue ( int address );
    bool isValueUpdated ( int address );
}
#endif
