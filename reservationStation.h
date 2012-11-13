/*
 * =====================================================================================
 *
 *       Filename:  reservationStation.h
 *
 *    Description:  Centralised Reservation station for the Super scalar processor
 *
 *        Version:  1.0
 *        Created:  Saturday 03 November 2012 09:43:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef RESERVATIONSTATION_H
#define RESERVATIONSTATION_H

#include "rob.h"
#include "instruction.h"

#define SIZEOFSTATION 10

typedef struct _entry
{
    bool busy;
    int dataTag;
    bool valid;
    int datatag2;
    bool valid2;
    bool readyForDispatch;
    int robIndex;
    int destination;
    bool doesWrite;
}insEntry;

class ReservationStation
{
    private:
        insEntry instructions[SIZEOFSTATION];        
        static bool centralized = 1;

    public:

        void fillReservationStation(int PC , Instruction *insList , ROB &reOrderBuffer );          // For every instruction added to the Reservation Station , add it to the ROB in Program order
        void updateReservationStation(int *);
        int dispatchInstructions(ROB &reOrderBuffer );            // Set up the dispatched bit in the ROB for all instructions that can be dispatched

};

#endif
