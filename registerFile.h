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

template <typename T>
class RegisterFile
{
    private:
        // Signed int / float registers for storing both positive and negative numbers
        T registers[NoOfRegisters];        
        bool busy[NoOfRegisters];
        int tag[NoOfRegisters];

        bool readPorts[READPORTS], writePorts[WRITEPORTS];

    public:
        RegisterFile();

        bool noPortsWritable();
        bool int noPortsReadable();
        void setReadPortsValue( int number , int SetorUnset );
        void setWritePortsValue( int number , int SetorUnset );

        int renameTag ( int index , int ROBindex );
        void updateRegisters ( int regTag );
//
        bool isValid ( int regTag );
        int getValue ( int regTag );
        int getTag ( int regTag );
//
        void printContents();
        void updateRegisterTags();

};

#endif
