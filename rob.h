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

#define ROBSIZE 100

typedef struct _robentry
{
    bool busy;
    bool issued;
    bool finished;
    int PCaddress;
    int renameRegister;
    int destinationRegister;
    bool speculative;
    bool valid;
    Instruction *ins;
}insDetails;

class ROB
{
    private:
        vector<insDetails> robEntries;
        int index;

    public:
        ROB();

        void addInsRob();
        void execute();
        void commitIns();
};


#endif
