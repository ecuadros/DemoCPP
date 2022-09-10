//tstbtree.cc  
//Author: Chicana D�az, Johan Pier
//Bachelor in Engineering of System
//#include <iostream.h>
#include <time.h>
#include <stdlib.h>

#include "iterator.h"
#include "btree.h"
#include <string>

//const char * keys="CDAMPIWNBKEHOLJYQZFXVRTSGU";
const char * keys1 = "D1XJ2xTg8zKL9AhijOPQcEowRSp0NbW567BUfCqrs4FdtYZakHIuvGV3eMylmn";
const char * keys2 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char * keys3 = "DYZakHIUwxVJ203ejOP9Qc8AdtuEop1XvTRghSNbW567BfiCqrs4FGMyzKLlmn";
//const char * keys4 = "ABCDEFGH";
const char * keys4 = "Aa1Bb2Cc3Dd4Ee5Ff6Gg";
string keys = "";

const size_t BTreeSize = 3;
int main ()
{
       size_t result, i=2, aux=1;
       //BTree <char> bt (BTreeSize);
       BTree < BTreeTrait<char> > bt;
       system("cls");
       while (i > 1 && aux < 2)
       { 
        /*
        cout << "Ingresa keys: ";
        cin >> keys;
        system("cls");
        keys4 = &keys[0];
        */
        for( i = 0; keys4[i]; i++)
        {
                //cout<<"Inserting "<<keys1[i]<<endl;
                //result = bt.Insert(keys4[i], i*i);
                bt.Insert(keys4[i], i*i);
                //bt.Print(cout);
        }
        i++;
        bt.Print(cout);
        bt.PrintDetails();
        for( i = 0; keys4[i]; i++)
        {
                bt.Remove(keys4[i], i*i);
        }
        i++;
        //cout << i << endl;
        aux++;
       }
       /*for (i = 0; keys2[i]; i++)
       {
               cout << "Searching " << keys2[i] << " ";
               long ObjID = bt.Search(keys2[i]);
               if( ObjID != -1 )
                       cout << "Achei " << keys2[i] << " ID = " << ObjID << endl;
               else
                       cout <<"Nao achei!" << keys2[i] << endl;
       }*/
       /*cout.flush();

       for (i = 0; keys3[i]; i++)
       {
               cout << "Removing " << keys3[i] << " ";
               if( bt.Remove(keys3[i], -1) )
                       cout << keys3[i] << " removido !" << endl;
               else
                       cout <<"Nao achei!" << keys3[i] << endl;
               bt.Print(cout);
       }
       bt.Print(cout);
       cout.flush();*/
       return 1;
}









/*const char * keys="CDAMPIWNBKEHOLJYQZFXVRTSGU";
const char * keys2="CDAMPIWNBKEHOLJYQZFXVRTSGU";
const int BTreeSize = 3;
main (int argc, char * argv)
{
       //__int64 li;
       BTree <__int64> bt (BTreeSize);
       for (register int i = 0; i < 1000000; i++)
       {
               //cout<<"Inserting "<<keys[i]<<endl;
               bt.Insert(i, i-1);
               //bt.Print(cout);
       }

       for (i = 0; i < 1000; i++)
       {
               __int64 key = 975000+(::rand()%50000);
               //cout << "Searching " << (long)key << " ";
               long ObjID = bt.Search(key);
               if( ObjID != -1 )
                       cout << "Achei " << (long)key << " ID = " << ObjID << endl;
               else
                       cout <<"  Nao achei!" << (long)key << endl;
       }
       cout.flush();

       return 1;
}*/



/*const int BTreeSize = 3;
main (int argc, char * argv)
{
       int result, i;
       BTree <LONGLONG> bt(BTreeSize);
       result = bt.Create ("ernesto3-string-btree-start.dat",ios::in|ios::out);
       if (!result) { cout<<"Please delete testbt.dat"<<endl;return 0; }
       srand( (unsigned)time( NULL ) );
       LARGE_INTEGER key;
       for (i = 0; i < 1000000; i++)
       {
               //cout<<"Inserting "<<keys[i]<<endl;
               char strTmp[50];
               key.LowPart = rand();
               key.HighPart = rand();
               std::string str(strTmp);
               result = bt.Insert(key.QuadPart, i);
               //bt.Print(cout);
               if( i % 100000 == 0 )
               {       cout << i << endl; cout.flush();        }
       }
       //cout << "Searching D " << bt.Search();
       //bt.Search(1,1);
       cout.flush();
       return 1;
}*/
