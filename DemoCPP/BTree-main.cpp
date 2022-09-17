//tstbtree.cc  
//Author: Chicana D�az, Johan Pier
//Bachelor in Engineering of System
//#include <iostream.h>
#include <time.h>
#include <stdlib.h>

#include "btree.h"
#include <string>

//const char * keys="CDAMPIWNBKEHOLJYQZFXVRTSGU";
const char * keys1 = "D1XJ2xTg8zKL9AhijOPQcEowRSp0NbW567BUfCqrs4FdtYZakHIuvGV3eMylmn";
const char * keys2 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char * keys3 = "DYZakHIUwxVJ203ejOP9Qc8AdtuEop1XvTRghSNbW567BfiCqrs4FGMyzKLlmn";
const char * keys4 = "ABCDEFGHIJKLMNRPO";
string keys = "";

const size_t BTreeSize = 3;
int main ()
{
       size_t result, i=2, aux=1;
       //BTree <char> bt (BTreeSize);
       BTree <char> bt;
       system("cls");
       while (i > 1 && aux < 2)
       { 

        for( i = 0; keys4[i]; i++)
        {
                //cout<<"Inserting "<<keys1[i]<<endl;
                //result = bt.Insert(keys4[i], i*i);
                bt.Insert(keys4[i], i*i);
                //bt.Print(cout);
        }
        i++;
        bt.Print(cout);
        for( i = 0; keys4[i]; i++)
        {
                bt.Remove(keys4[i], i*i);
        }
        i++;

       }
        //a++
       return 0;
}











