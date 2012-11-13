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

// TODO : Complete this function
void execute ( )
{
    vector<int>::iterator start , end;
    start = robEntries.begin();
    end = robEntries.end();

    funcUnit FUnit;

    for ( start ; start != end ; start++ )
    {
        if ( ! start->busy )
            break;
        else
        {
            if ( start->issued && ! start->valid )
            {
                if ( ins->canExecute ( stage ) )
                {
                    final = ins->execute(stage , op1 , op2 , FUnit );
                    if ( ins->lastStage ( stage ) ) 
                    {
                        start->valid = 1;
                    }
                }
            }
        }
    }
}

bool commitIns( RegisterFile & intRegisterFile , RegisterFile & floatReisterFile  )
{
    if ( robEntries[0].busy )
    {
        if ( robEntries[0].valid )
        {
            if ( !isBranch )
            {
                if ( intResult )
                {
                    if ( intRegisterFile.tag[destinationRegister] == 0 )
                    {
                        intRegisterFile.tag[destinationRegister] = -1;
                        intRegisterFile.busy[destinationRegister] = 0;
                        intRegisterFile.registers[destinationRegister] = (int)final;
                    }
                }
                else
                {
                    if ( floatRegisterFile.tag[destinationRegister] == 0 )
                    {
                        floatRegisterFile.tag[destinationRegister] = -1;
                        floatRegisterFile.busy[destinationRegister] = 0;
                        floatRegisterFile.registers[destinationRegister] = (int)final;
                    }
                }
            }
            intRegisterFile.updateRegisterTags();
            floatRegisterFile.updateRegisterTags();
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
