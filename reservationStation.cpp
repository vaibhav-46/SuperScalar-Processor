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

void fillReservationStation ( int PC , Instruction *insList , ROB &reOrderBuffer , int count )
{
    int j = 0;
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( instructions[i].busy )
            continue;
        else
        {
            instructions[i].busy = 1;
            insInfo insDetails = insList[j]->getDetails();       // A new structure 
            // TODO : Fill in the rest of the values using the structure
            instructions[i].dataTag = insDetails.op1;
            instructions[i].dataTag2 = insDetails.op2;
            instructions[i].valid = insDetails.op1tag;
            instructions[i].valid2 = insDetails.op2tag;

            if ( instructions[i].valid && instructions[i].valid2 )
                instructions[i].readyForDispatch = true;
            else
                instructions[i].readyForDispatch = false;

            int renameIndex = reOrderBuffer.addInsRob ( insList[j] );
            instructions[i].robIndex = renameIndex;
            instructions[i].destination = insDetails.destination;
            instructions[i].doesWrite = insDetails.doesWrite;
            // TODO : Rename the output register of the command 

            j++;
            if ( j == count )
                break;
        }
    }
}

void updateReservationStation(int index , int value )
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

int dispatchInstructions ( ROB & reOrderBuffer )
{
    int count = 0;
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( instructions[i].readyForDispatch )
        {
            reOrderBuffer.updateData ( instructions[i].robIndex , instructions[i].dataTag , instructions[i].dataTag2 , instructions[i].doesWrite , instructions[i].destination );
            count++;
            instructions[i].busy = 0;
        }
    }
    return count;
}
