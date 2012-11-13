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

void addInsRob( Instruction *p , int PC , bool isSpec )
{
    insDetails *newInsEntry = i(insDetails *)new (sizeof(insDetails));
    newInsEntry->busy = 1;
    newInsEntry->valid = 0;
    newInsEntry->issued = 0;
    newInsEntry->PCaddress = PC;
    newInsEntry->speculative = isSpec;
    newInsEntry->ins = p;
    robEntries.push_back(*newInsEntry);
}

void execute ( )
{
}


