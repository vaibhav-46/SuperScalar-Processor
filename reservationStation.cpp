/*
 * =====================================================================================
 *
 *       Filename:  reservationStation.cpp
 *
 *    Description:  Functions relating to the Reservation Station that dispatches the instructions
 *
 *        Version:  1.0
 *        Created:  Tuesday 13 November 2012 12:37:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <iostream>
#include "reservationStation.h"
#include "instructions.h"
#include "registerFile.h"
#include "rob.h"
using namespace std;

ReservationStation::ReservationStation()
{
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        instructions[i].busy = 0;
        instructions[i].readyForDispatch = 0;
        instructions[i].dataTag = true;
        instructions[i].dataTag2 = true;
    }
}
// Adds the instruction to the reservation station . Fills in all the appropriate values
void ReservationStation::fillReservationStation ( int PC , Instruction *ins , ROB &reOrderBuffer  , RegisterFile & intRegiserFile )
{
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( instructions[i].busy )
            continue;
        else
        {
            instructions[i].busy = 1;
            insInfo insDetails = ins->getDetails();       // A new structure 
            instructions[i].dataTag = insDetails.op1;
            instructions[i].dataTag2 = insDetails.op2;
            instructions[i].valid = insDetails.op1tag;
            instructions[i].valid2 = insDetails.op2tag;
            instructions[i].PC = PC;

            if ( instructions[i].valid && instructions[i].valid2 )
                instructions[i].readyForDispatch = true;
            else
                instructions[i].readyForDispatch = false;

            int renameIndex = reOrderBuffer.addInsRob ( ins );
            instructions[i].robIndex = renameIndex;
            instructions[i].doesWrite = insDetails.doesWrite;
            instructions[i].branch = insDetails.branch;
            // Register Renaming in case the instruction is a write instruction
            int index;
            if ( insDetails.doesWrite )
                index = intRegiserFile.renameVariable ( insDetails.destination , renameIndex );
            instructions[i].destination = index;
            break;
        }
    }
}

void ReservationStation::updateReservationStation(int index , int value )
{
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( ! instructions[i].valid )
        {
            if ( instructions[i].dataTag == index )
            {
                instructions[i].dataTag = value;
                instructions[i].valid = 1;
            }
       }
        if ( ! instructions[i].valid2 )
        {
            if ( instructions[i].dataTag2 == index )
            {
                instructions[i].dataTag2 = value;
                instructions[i].valid2 = 1;
            }
        }
        if ( instructions[i].valid && instructions[i].valid2 )
            instructions[i].readyForDispatch = true;
    }
}

int ReservationStation::dispatchInstructions ( ROB & reOrderBuffer )
{
    int count = 0;
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( instructions[i].readyForDispatch )
        {
            reOrderBuffer.updateData ( instructions[i].robIndex , instructions[i].dataTag , instructions[i].dataTag2 , instructions[i].doesWrite , instructions[i].destination , instructions[i].branch , instructions[i].PC);
            count++;
            instructions[i].busy = 0;
        }
    }
    return count;
}
