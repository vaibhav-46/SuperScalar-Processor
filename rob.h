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
#include "reservationStation.h"

#define ROBSIZE 100
#define ADD_ALU 2
#define MUL_ALU 2
#define DIV_ALU 2
#define BIT_ALU 2
#define MUL_LATENCY 3
#define DIV_LATENCY 2
#define ADD_LATENCY 1
#define BIT_LATENCY 1

class RegisterFile;

typedef struct insDetails
{
    bool busy;
    bool issued;
    int destinationRegister;
    bool valid;
    int stage;
    bool intResult;
    int final;
    Instruction *ins;
    int op1 , op2;
    bool isBranch;
    int PC;
}insDetails;

class ROB
{
    private:
        std::vector<insDetails> robEntries;
        int index;

    public:
        ROB();

        int addInsRob(Instruction *p );
        int execute(ReservationStation &r);
        void updateData ( int , int , int, bool ,int , bool , int );
        bool commitIns(RegisterFile & intRegFile , StoreBuffer & storeBuffer , int * memory );
};

#endif
