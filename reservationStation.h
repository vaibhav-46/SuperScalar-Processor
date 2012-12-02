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

#define SIZEOFSTATION 10

class ROB;
class Instruction;
class RegisterFile;

typedef struct _entry
{
    bool busy;
    int dataTag;
    bool valid;
    int dataTag2;
    bool valid2;
    bool readyForDispatch;
    int robIndex;
    int destination;
    bool doesWrite;
    bool branch;
    int PC ;
}insEntry;

class ReservationStation
{
    private:
        insEntry instructions[SIZEOFSTATION];        

    public:

        ReservationStation();
        void fillReservationStation(int PC , Instruction *ins , ROB &reOrderBuffer , RegisterFile & registerFile );          // For every instruction added to the Reservation Station , add it to the ROB in Program order
        void updateReservationStation(int Tag , int Value );
        int dispatchInstructions(ROB &reOrderBuffer );            // Set up the dispatched bit in the ROB for all instructions that can be dispatched
        void updateIndex();
        int emptySpace();

};

#endif
