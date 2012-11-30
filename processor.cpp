/*
 * =====================================================================================
 *
 *       Filename:  processor.cpp
 *
 *    Description:  Super Scalar Processor with centralised pipeline system
 *
 *        Version:  1.0
 *        Created:  Monday 12 November 2012 06:28:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */


#include "processor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;


unsigned int opOpcode = pow(2,26);
int lastIns = 0;
// ------------------------ Generic functions ---------------------------------

// Assumption : The instruction are 32 bit instructions
char getType ( unsigned int ins )
{
    unsigned int opcode = ins / opOpcode;
    if ( opcode == 2 || opcode == 3 )
        return 'J';
    else if ( opcode == 0 )
        return 'R';
    else
        return 'I';
}
// --------------------------- Processor Class Begins ----------------------------------

void Processor::addInstruction ( string hexValue )
{
    unsigned int ins;
    stringstream ss;
    ss << std::hex << hexValue;
    ss >> ins;
    char type;
    type = getType( ins );
    cout << "INS : " << ins <<  "   Type : " << type << endl;
    switch(type)
    {
        case 'J' : 
            {
                JInstruction *temp1= new JInstruction(ins);
                jInstruction[jCount] = *temp1;
                listInstructions[sCount] = &jInstruction[jCount] ;
                jCount++;
                sCount++;
                break;
            }
        case 'R' : 
            {
                RInstruction *temp2 = new RInstruction(ins);
                rInstruction[rCount] = *temp2;
                listInstructions[sCount] = &rInstruction[rCount] ;
                rCount++;
                sCount++;
                break;
            }
        case 'I' : 
            {
                IInstruction *temp3 = new IInstruction(ins);
                iInstruction[iCount] = *temp3;
                listInstructions[sCount]= &iInstruction[iCount] ;
                iCount++;
                sCount++;
                break;
            }
        default:
            {
                cout << "Last instruction read in" << endl;
                return;
            }
    }
}

/*
 *  Stages in the execution :
 *      
 *      1. Commit the last instruction in ROB ( Returns bool )
 *      2. Update Registers for the last round of instructions ( void )
 *      3. Update Reservation Station for the indices and new values received. ( void )
 *      4. Execute the instructions present in the FU. ( Returns the list of registers whose values have been changed )
 *      5. Dispatch the next set of instructions. ( List of all instructions that are currently in the FU )
 *      6. ID - Decode instructions and add them to reservation station. 
 *      7. IF - Fetch the next k instructions. ( New structure - list of instructions , whether in the BTB , PCvalue  )
*/
void Processor::execute()
{
     int bool = reOrderBuffer.commit();
     // TODO : Have to write the execute instructions. Still pending ( To be written in the end )
}

// TODO : In case of branch instruction with no return address, stall all further instructions till the return address is got and add appropriate register values for the later on instructions to get values.
// TODO : For each instruction , add to the Reservation Station ( not all at once )
int Processor::decodeInstructions ( newInstr * listIns , int numberIns )
{
    int i = 0;
    int flag = 0;
    for ( i = 0 ; i < numberIns ; i++ )
    {
        insInfo returnVal= listIns[i].ins->IDstage();      
        if ( returnVal.branch )
        {
            if ( i == numberIns - 1 )
            {
                if ( PC != returnVal.nextPC )
                {
                    PC = returnVal.nextPC;
                    flag = 1;
                    break;
                }
            }
            else
            {
                if ( returnVal.nextPC != listIns[i+1].PC )
                {
                    PC = returnVal.nextPC;
                    flag = 1;
                    break;
                }
            }
        }
    }
    if ( flag )
    {
        listIns[i+1] = NULL;
        return i+1;
    }
    else
    {
        listIns[i] = NULL;
        return i;
    }
}

int Processor::getInstructions ( int numberIns , newInstr * listIns )
{
    cout << "Getting Instructions : " << numberIns << endl;
    for ( int i = 0 ; i < numberIns ; i++ )
    {
        if ( PC == sCount )
            return i+1;
        else
        {
            listIns[i].ins = listInstructions[PC];
            listIns[i].PC = PC;
            int branchAddress = btb.getBranchAddress ( PC );
            if ( branchAddress == -1 )
                PC = PC + 1;
            else
            {
                bool p = branchPredictor.predictBranch( PC );
                if ( p )
                    PC = branchAddress;
                else
                    PC = PC+1;
            }
        }
    }
    return i+1;
}

void Processor::printDetails ()
{
    cout << " Super Scalar processor : " << endl;
    cout << " No of instructions executed : " << insCount << endl;
    cout << " No of stalls                : " << stalls << endl;
    cout << " No of cycles                : " << cycles << endl;
    double temp = (double)cycles / (double)insCount;
    cout << " Cycles per instruction      : " << temp << endl;
    cout << "====================================================================="<<endl;
    registerFile.printContents();
}

/*  
    void Processor::codeRunning()
    {
    cout << "_----------------------------------------------------------" << endl;
    vector<Instruction *>::iterator startIt , endIt;
    startIt = listInstructions.begin();
    endIt = listInstructions.end();

    cout << "List of instructions : " << endl;
    for ( ; startIt != endIt ; startIt++ )
    {
    cout << (*startIt)->instruction << endl;
    }

    cout << "List of R instructions : " << endl;
    vector<RInstruction>::iterator startRIt , endRIt;
    startRIt = rInstruction.begin();
    endRIt = rInstruction.end();
    for ( ; startRIt != endRIt ; startRIt++ )
    cout << (*startRIt).instruction << endl;
    cout << "_----------------------------------------------------------" << endl;
    }

*/
