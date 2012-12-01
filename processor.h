/*
 * =====================================================================================
 *
 *       Filename:  processor.h
 *
 *    Description:  Header file for processor
 *
 *        Version:  1.0
 *        Created:  Saturday 06 October 2012 06:53:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
#include <stdlib.h>
#include "registerFile.h"
#include "rob.h"
#include "reservationStation.h"
#include "branch.h"
#include "instructions.h"
#include "storeBuffer.h"


#define MAXINSTRUCTIONS 1000
#define MEMORY_SIZE 1024

typedef struct _newInstr
{
    Instruction *ins;
    int PC;
}newInstr;

class Processor
{
    public:

        RegisterFile intRegisterFile;
        ReservationStation resStation;
        ROB reOrderBuffer;
        BTB btb;
        BranchPrediction branchPredictor;
        funcUnit FUdetails;
        int memory[MEMORY_SIZE];
        StoreBuffer storeBuffer;


        int PC ;
        int jCount , iCount , rCount , sCount;
        int registerDuringPipeline[NoOfRegisters];

        // Instructions stored
        JInstruction jInstruction[MAXINSTRUCTIONS];
        IInstruction iInstruction[MAXINSTRUCTIONS];
        RInstruction rInstruction[MAXINSTRUCTIONS];
        Instruction * listInstructions[MAXINSTRUCTIONS];

        int insCount , stalls , cycles;

        int updatingRegisters[NoOfRegisters] , gotValueRegisters[NoOfRegisters];
 
        void addInstruction ( std::string hexValue );
        void execute();
        void printDetails();

        int decodeInstructions ( newInstr *listIns , int numberIns );
        int getInstructions (int numIns , newInstr * listIns );
};

#endif
