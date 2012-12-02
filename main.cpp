/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 07 October 2012 03:15:32  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include "processor.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

/*  @Main : Function to read file, add instructions to the instruction cache. Assuming that the hit rate is 100%, 
 *          all the instructions are read into memory and then process execution begins.
 * 
 */
int main(int argc , char * argv[])
{
    if ( argc != 2 )
    {
        cout << "Usage : " << argv[0] << " " << "file_name" << endl; ;
        exit(-1);
    }
    cout << "Ready to go !!" << endl;
    Processor superScalar;
    superScalar.iCount = superScalar.rCount = superScalar.jCount = superScalar.sCount = 0;
    ifstream inputHandle;
    inputHandle.open(argv[1]);
    string line;
    while( true )
    {
        if ( !getline( inputHandle , line ) )
            break;
        if ( inputHandle.eof() )
            break;
        if ( !(line.empty()) )
            superScalar.addInstruction ( line );
        else
        {
            break;
        }
   }

    //superScalar.codeRunning();
    superScalar.execute();
    superScalar.printDetails();
    return 0;
}
