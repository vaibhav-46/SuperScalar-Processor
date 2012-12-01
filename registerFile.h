/*
 * =====================================================================================
 *
 *       Filename:  registerFile.h
 *
 *    Description:  Register File which contains the register details for the processor
 *
 *        Version:  1.0
 *        Created:  Saturday 03 November 2012 07:13:13  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#define NoOfRegisters 32
#define READPORTS 2
#define WRITEPORTS 1

class RegisterFile
{
    private:
        int registers[NoOfRegisters];        
        bool busy[NoOfRegisters];
        int tag[NoOfRegisters];

        bool readPort[READPORTS], writePort[WRITEPORTS];

    public:
        RegisterFile();

        int noPortsWritable();
        int noPortsReadable();
        void setReadPortsValue( int number , int SetorUnset );
        void setWritePortsValue( int number , int SetorUnset );

        int renameVariable ( int index , int ROBindex );
        void updateRegisters ( int regTag , int value );
//
        bool isValid ( int regTag );
        int getValue ( int regTag );
        int getTag ( int regTag );
//
        void printContents();
        void updateRegisterTags();

};

#endif
