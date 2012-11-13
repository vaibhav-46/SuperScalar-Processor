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

#include <string>
#include <vector>
#include "instructions.h"
#include "rob.h"
#include "branch.h"

#define MAXINSTRUCTIONS 1000
#define ADD_LEVEL 4
#define MUL_LEVEL 7
#define DIV_LEVEL 10

typedef struct _newInstr
{
    Instruction *ins;
    int PC;
}newInstr;

class Processor
{
    public:

        RegisterFile intRegisterFile;
        RegisterFile floatRegisterFile;
        ROB reOrderBuffer;
        BTB btb;
        BranchPrediction branchPredictor;
        funcUnit FUdetails;

        double PC;
        unsigned int jCount , iCount , rCount , sCount;
        unsigned int registerDuringPipeline[NoOfRegisters];

        // Instructions stored
        JInstruction jInstruction[MAXINSTRUCTIONS];
        IInstruction iInstruction[MAXINSTRUCTIONS];
        RInstruction rInstruction[MAXINSTRUCTIONS];
        Instruction * listInstructions[MAXINSTRUCTIONS];

        unsigned int insCount , stalls , cycles;

        unsigned int updatingRegisters[NoOfRegisters] , gotValueRegisters[NoOfRegisters];
 
        void computeStuff ( int * currentExecution , int * completed , int * valid , int currentIndex , int oldest);
        void addInstruction ( std::string hexValue );
        void execute();
        void printDetails();
};
