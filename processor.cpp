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


#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "processor.h"

using namespace std;

bool branchStall = false;

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

Processor::Processor()
{
    // Update which ever memory location is necessary 
    memory[0] = 1;
    memory[1] = 0;
    memory[2] = 0;
    memory[3] = 1;
    memory[4] = 1;
    memory[5] = 2;
    memory[6] = 3;
    memory[7] = 4;
}
void Processor::addInstruction ( string hexValue )
{
    unsigned int ins;
    stringstream ss;
    ss << std::hex << hexValue;
    ss >> ins;
    char type;
    type = getType( ins );
    //cout << " Instruction : " << ins << "   " ;
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
                //cout << "Last instruction read in" << endl;
                return;
            }
    }
}

/*
 *  Stages in the execution :
 *      
 *      1. Commit the last instruction in ROB ( Returns bool )
 *      2. Execute the instructions present in the FU. ( Returns the list of registers whose values have been changed )
 *      5. Dispatch the next set of instructions. ( List of all instructions that are currently in the FU )
 *      6. ID - Decode instructions and add them to reservation station. 
 *      7. IF - Fetch the next k instructions. ( New structure - list of instructions , whether in the BTB , PCvalue  )
*/
void Processor::execute()
{
    newInstr *insList = new newInstr[SIZEOFSTATION];
    int index = 0;
    int wastage = 0;
    bool commited;
    int numberInsGot = 0, numberInsDecoded = 0;
    int execute, numberInsDispatched = 0;
    //cout << " Ready to execute !! Ins count : " << sCount << endl;
    while ( ! ( (PC >= sCount) && !commited && !(numberInsDecoded ) && !(numberInsGot) ) )
    {
        commited = reOrderBuffer.commitIns(intRegisterFile , storeBuffer , memory , resStation );
        execute = reOrderBuffer.execute( resStation );
        numberInsDispatched = resStation.dispatchInstructions ( reOrderBuffer );
       numberInsDispatched = resStation.emptySpace(); 
        if ( index == 0 )
            numberInsGot = getInstructions ( SIZEOFSTATION , insList );
        else
            numberInsGot = getInstructions ( numberInsDispatched , insList );
        numberInsDecoded = decodeInstructions ( insList , numberInsGot );
        while ( branchStall )
        {
            commited = reOrderBuffer.commitIns(intRegisterFile , storeBuffer , memory , resStation );
            execute = reOrderBuffer.execute ( resStation );
            numberInsDispatched += resStation.dispatchInstructions ( reOrderBuffer );
            if ( execute != -1 )
            {
                PC = execute;
                branchStall = false;
            }
        }
        index++;
    }
}

int Processor::decodeInstructions ( newInstr * listIns , int numberIns )
{
    int i = 0;
    int flag = 0;
    for ( i = 0 ; i < numberIns ; i++ )
    {
        insInfo returnVal= listIns[i].ins->IDstage ( listIns[i].PC , intRegisterFile , reOrderBuffer );
        if ( returnVal.branch )
        {
            resStation.fillReservationStation ( listIns[i].PC , listIns[i].ins , reOrderBuffer , intRegisterFile );
            if ( returnVal.nextPC == -1769 )
            {
                branchStall = true;
                return i+1;
            }
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
        else
            resStation.fillReservationStation( listIns[i].PC , listIns[i].ins , reOrderBuffer , intRegisterFile );
    }
    if ( flag )
        return i+1;
    else
        return i;
}

// Gets the required number of instructions that can be fit into the reservation station ( which is an argument -> numberIns )
int Processor::getInstructions ( int numberIns , newInstr * listIns )
{
    int i;
    for ( i = 0 ; i < numberIns ; i++ )
    {
        if ( PC >= sCount )
            break;
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
    /*
    if ( i != 0 )
        cout << "Getting Instructions : " << i << endl;
    */
    return i;
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
    intRegisterFile.printContents();
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

// TODO : Add the branch instructions to the BTB
