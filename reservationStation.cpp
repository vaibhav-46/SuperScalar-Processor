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

void fillReservationStation ( int PC , Instruction *insList , ROB &reOrderBuffer )
{
    int j = 0;
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( instructions[i].busy )
            continue;
        else
        {
            instructions[i].busy = 1;
            insList[j]->getDetails();       // A new structure 
            // TODO : Fill in the rest of the values using the structure

            reOrderBuffer.addInsRob ( insList[j] );
            j++;
        }
    }
}

void updateReservationStation(int *p)
{
    for ( int i = 0 ; i < SIZEOFSTATION ; i++ )
    {
        if ( ! instructions[i].valid )
        {
            if ( p[dataTag] != -1769 )
            {
                instructions[i].dataTag = p[dataTag];
                instructions[i].valid = true;
            }
        }
        if ( ! instructions[i].valid2 )
        {
            if ( p[dataTag2] != -1769 )
            {
                instructions[i].dataTag2 = p[dataTag2];
                instructions[i].valid2 = true;
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
            int count = 0;
            instructions[i].busy = 0;
        }
    }
}
