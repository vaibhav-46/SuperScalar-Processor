/*
 * =====================================================================================
 *
 *       Filename:  rob.cpp
 *
 *    Description:  Re-Order Buffer Execution
 *
 *        Version:  1.0
 *        Created:  Tuesday 06 November 2012 08:13:10  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <iostream>
#include "rob.h"
#include "instructions.h"
#include "registerFile.h"
using namespace std;
ROB::ROB()
{
    int index = 0;
}

int ROB::addInsRob( Instruction *p )
{
    insDetails *newInsEntry = new insDetails;
    newInsEntry->busy = 1;
    newInsEntry->valid = 0;
    newInsEntry->issued = 0;
    newInsEntry->ins = p;
    newInsEntry->stage = 1;
    robEntries.push_back(*newInsEntry);
    return robEntries.size()-1;
}

// HACK : Returns the next PC value in case of a branch instruction ( if branch is not yet found, return -1 )  
int ROB::execute ( ReservationStation &station )
{
    vector<insDetails>::iterator start , end;
    start = robEntries.begin();
    end = robEntries.end();
    int returnVal = -1;
    funcUnit FUnit;
    int final = 0;
    int index = -1;
    for ( start ; start != end ; start++ )
    {
        if ( ! start->busy )
        {
            index++;
            break;
        }
        else
        {
            index++;
            if ( start->issued && ! start->valid )
            {
                if ( start->ins->canExecute ( start->stage , FUnit) )
                {
                    final = start->ins->execute(start->stage , start->op1 , start->op2 , start->PC );
                    if ( start->ins->lastStage ( start->stage ) ) 
                    {
                        start->valid = 1;
                        station.updateReservationStation ( index , final );
                        if ( returnVal == -1 && start->isBranch )
                            returnVal = final;
                    }
                    else
                        start->stage++;
                }
            }
        }
    }
    return returnVal;
}

bool ROB::commitIns( RegisterFile & intRegisterFile , StoreBuffer & storeBuffer , int * memory )
{
    if ( robEntries.size() > 0 )
    {
        if ( robEntries[0].busy )
        {
            if ( robEntries[0].valid )
            {
                robEntries[0].ins->commit( intRegisterFile , robEntries[0].destinationRegister , storeBuffer , memory );
                robEntries.erase( robEntries.begin() );
                intRegisterFile.updateRegisterTags();
                return 1;
            }
        }
    }
    return 0;
}

void ROB::updateData ( int index , int operand1 , int operand2 , bool doesWrite , int destination, bool isInsBranch , int PC )
{
    robEntries[index].op1 = operand1;
    robEntries[index].op2 = operand2;
    robEntries[index].issued = 1;
    robEntries[index].destinationRegister = destination;
    robEntries[index].isBranch = isInsBranch;
    robEntries[index].PC = PC ;
}
