/*
 * =====================================================================================
 *
 *       Filename:  branch.h
 *
 *    Description:  All branching related classes
 *
 *        Version:  1.0
 *        Created:  Monday 12 November 2012 09:30:29  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BRANCH_H
#define BRANCH_H

#define BTBSIZE 32
#define HISTORY_TABLE_LENGTH 128
#define NO_OF_BITS 3
#define LENGTH_PREDICTOR 2

typedef struct _BTBentry
{
    int PC;
    int branchAddress;
}BTBentry;

class BTB
{
    private:
        BTBentry entries[BTBSIZE];

    public:
        BTB();
        int getBranchAddress ( int PC );
        void addBranchAddress ( int PC , int branchAddress );
};

class BranchPrediction
{
    private:
        int historyTableEntries[HISTORY_TABLE_LENGTH];
        int localPredictionEntries[2^NO_OF_BITS];

    public:
        BranchPrediction();
        bool predictBranch ( int PC );
        void setBranchResult ( int PC );
};

#endif
