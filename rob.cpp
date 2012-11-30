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

ROB::ROB()
{
    int index = 0;
}

int addInsRob( Instruction *p )
{
    insDetails *newInsEntry = (insDetails *)new (sizeof(insDetails));
    newInsEntry->busy = 1;
    newInsEntry->valid = 0;
    newInsEntry->issued = 0;
    newInsEntry->ins = p;
    robEntries.push_back(*newInsEntry);
    return robEntries.size()-1;
}

void execute ( ReservationStation &station )
{
    vector<int>::iterator start , end;
    start = robEntries.begin();
    end = robEntries.end();

    funcUnit FUnit;

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
                if ( ins->canExecute ( stage , FUnit) )
                {
                    final = ins->execute(stage , op1 , op2 );
                    if ( ins->lastStage ( stage ) ) 
                    {
                        start->valid = 1;
                        station.updateReservationStation ( index , final );
                    }
                }
            }
        }
    }
}

bool commitIns( RegisterFile & intRegisterFile )
{
    if ( robEntries[0].busy )
    {
        if ( robEntries[0].valid )
        {
            if ( !isBranch )
            {
                    if ( intRegisterFile.tag[destinationRegister] == 0 )
                    {
                        intRegisterFile.tag[destinationRegister] = -1;
                        intRegisterFile.busy[destinationRegister] = 0;
                        intRegisterFile.registers[destinationRegister] = (int)final;
                    }
            }
            intRegisterFile.updateRegisterTags();
            // TODO : Remove the zeroth element of the vector
            return 1;
        }
    }
    return 0;
}

void updateData ( int index , float operand1 , float operand2 , bool doesWrite , int destination )
{
    robEntries[index].op1 = operand1;
    robEnries[index].op2 = operand2;
    robEntries[index].issued = 1;
    robEntries[index].branch = !doesWrite;
    robEntries[index].destinationRegister = destination;
}
