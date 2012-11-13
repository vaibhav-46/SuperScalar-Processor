/*
 * =====================================================================================
 *
 *       Filename:  branch.cpp
 *
 *    Description:  Branch related implementation for prediction and confirmation
 *
 *        Version:  1.0
 *        Created:  Monday 12 November 2012 09:45:00  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include "branch.h"
#include <iostream>
using namespace std;

BTB::BTB()
{
    for ( int i = 0 ; i < BTBsize ; i++ )
    {
        entries[i].PC = -1;
        entries[i].branchAddress = -1;
    }
}

int BTB::getBranchAddress ( int currentPC )
{
    int i = 0;
    while ( entries[i].PC != -1 )
    {
        if ( entries[i].PC == currentPC )
            return entries[i].branchAddress;
        i++;
    }
    return -1;
}

void BTB::addBranchAddress ( int currentPC , int currentBranchAddress )
{
    int i = 0;
    int p = getBranchAddress ( currentPC );
    if ( p != -1 )
        return;
    while ( entries[i].PC != -1 )
        i++;
    if ( i == BTBsize )
        i = 0;
    entries[i].PC = currentPC;
    entries[i].branchAddress = currentBranchAddress;
}

BranchPrediction::BranchPrediction()
{
    for ( int i = 0 ; i < HISTORY_TABLE_LENGTH ; i++ )
        historyTableEntries[i] = 0;
    for ( int i = 0; i < 2^NO_OF_BITS ; i++ )
        localPredictionEntries[i] = 0;
}

bool predictBranch ( int currentPC )
{
    int index = 0;
    for ( int i = 0; i < NO_OF_BITS ; i++ )
    {
        index += 2^i * ( currentPC % 2 );
        currentPC = currentPC / 2 ;
    }
    index = historyTableEntries[index];
    if ( localPredictionEntries[index] < 2 )
        return false;
    else
        return true;
}

void setBranchResult ( int currentPC , bool taken )
{
    int index = 0;
    for ( int i = 0; i < NO_OF_BITS ; i++ )
    {
        index += 2^i * ( currentPC % 2 );
        currentPC = currentPC / 2 ;
    }
    int localIndex = historyTableEntries[index];
    if ( localPredictionEntries[localIndex] < 2 )
    {
        if ( !taken )
            localPredictionEntries[localIndex] = 0;
        else
        {
            if ( localPredictionEntries[localIndex] == 0 )
                localPredictionEntries[localIndex] = 1;
            else
                localPredictionEntries[localIndex] = 2;
        }
    }
    else
    {
        if ( taken )
            localPredictionEntries[localIndex] = 1;
        else
        {
            if ( localPredictionEntries[localIndex] == 1 )
                localPredictionEntries[localIndex] = 2;
            else
                localPredictionEntries[localIndex] = 0;
        }
    }
    historyTableEntries[index] *= 2;
    if ( taken )
        historyTableEntries[index] += 1;
    else
        historyTableEntries[index] += 0;
    historyTableEntries[index] = historyTableEntries[index] % 2^NO_OF_BITS;
}
