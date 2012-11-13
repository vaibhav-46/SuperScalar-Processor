/*
 * =====================================================================================
 *
 *       Filename:  rob.h
 *
 *    Description:  Reorder Buffer for Super Scalar Processor
 *                      - It takes care of the inorder execution of the entire program.
 *                      - Makes sure that all the instructions happen in order
 *
 *        Version:  1.0
 *        Created:  Saturday 03 November 2012 10:00:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ROB_H
#define ROB_H

#include <vector>
#include "instructions.h"
#include "registerFile.h"

#define ROBSIZE 100

typedef struct _funcUnit
{
    bool execute;
    bool fAdd[ADD_LEVEL];
    bool fMul[MUL_LEVEL];
    bool fDiv[DIV_LEVEL];
}funcUnit;


typedef struct _robentry
{
    bool busy;
    bool issued;
    int destinationRegister;
    bool valid;
    int stage
    bool intResult;
    float final;
    Instruction *ins;
    float op1 , op2;
    bool isBranch;
}insDetails;

class ROB
{
    private:
        vector<insDetails> robEntries;
        int index;

    public:
        ROB();

        int addInsRob(Instruction *p );
        void execute();
        void updateOperands ( int , float , float );
        void commitIns(RegisterFile & intRegFile , RegisterFile &floatRegFile );
};

#endif
