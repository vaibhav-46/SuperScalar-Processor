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

typedef struct _entry
{
    bool busy;
    int opcode;
    int dataTag;
    bool valid;
    int datatag2;
    bool valid2;
    bool readyForDispatch;
}insEntry;

class ReservationStation
{
    private:
        insEntry instructions[SIZEOFSTATION];        
        static bool centralized = 1;

    public:
        ReservationStation();

        void fillReservationStation();          // For every instruction added to the Reservation Station , add it to the ROB in Program order
        void updateReservationStation();
        void dispatchInstructions();            // Set up the dispatched bit in the ROB for all instructions that can be dispatched

};

#endif
