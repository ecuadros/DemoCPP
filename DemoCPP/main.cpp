#include <iostream>
#include <tuple>
#include "demo.h"
using namespace std;

// Test desde Mac
// g++ -pthread -std=c++17 -o main main.cpp demo.cpp
// Comentario extra de Mac
// Texto sugerido

auto foo()
{
  struct retVals        // Declare a local structure 
  { int i1, i2;
    string str;
  };
  return make_tuple(10, 20, "Hi", 5.4, 8.2); // Return the 
}

template <typename T>
void Exe(std::string msg, T func)
{
  cout << "\n>>>>>>>>>>>>> " << msg << "(); ..." << endl;
  func();
}

int main()
{
  auto [v1, v2, v3, v4, v5] = foo(); // structured binding declaration
  cout << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ", " << v5 << endl;

  cout << "\n>>>>>>>>>>>>> demoVariadic(); ..." << endl;
  demoVariadic();

  cout << "\n>>>>>>>>>>>>> DemoFoldedFunctions(); ..." << endl;
  DemoFoldedFunctions();

  cout << "\n>>>>>>>>>>>>> DemoHomogeneous(); ..." << endl;
  DemoHomogeneous();

  cout << "\n>>>>>>>>>>>>> DemoInvoke(); ..." << endl;
  DemoInvoke();

  cout << "\n>>>>>>>>>>>>> DemoFoldTraverse(); ..." << endl;
  DemoFoldTraverse();

  cout << "\n>>>>>>>>>>>>> DemoPrintAuto(); ..." << endl;
  DemoPrintAuto();

  cout << "\n>>>>>>>>>>>>> DemoLambdaFunctions(); ..." << endl;
  DemoLambdaFunctions();

  cout << "\n>>>>>>>>>>>>> DemoVarTmplAuto(); ..." << endl;
  DemoVarTmplAuto();

  cout << "\n>>>>>>>>>>>>> DemoMultiBase1(); ..." << endl;
  DemoMultiBase1();
  cout << "\n>>>>>>>>>>>>> DemoMultiBase2(); ..." << endl;
  DemoMultiBase2();

  cout << "\n>>>>>>>>>>>>> DemoCallBacks(); ..." << endl;
  DemoCallBacks();

  cout << "\n>>>>>>>>>>>>> DemoIfCompTime(); ..." << endl;
  DemoIfCompTime();

  cout << "\n>>>>>>>>>>>>> DemoCheckPath3(); ..." << endl;
  DemoCheckPath3();

  cout << "\n>>>>>>>>>>>>> DemoCreateFile(); ..." << endl;
  DemoCreateFile();

  //cout << "\n>>>>>>>>>>>>> DemoTimeAsString(); ..." << endl;
  //DemoTimeAsString();

  cout << "\n>>>>>>>>>>>>> DemoSymlink(); ..." << endl;
  DemoSymlink();

  cout << "\n>>>>>>>>>>>>> DemoConvert(); ..." << endl;
  DemoConvert();

  cout << "\n>>>>>>>>>>>>> DemoIncomplete(); ..." << endl;
  DemoIncomplete();

  cout << "\n>>>>>>>>>>>>> DemoMapHandle(); ..." << endl;
  DemoMapHandle();
  cout << "\n>>>>>>>>>>>>> DemoMapNodeMerge(); ..." << endl;
  DemoMapNodeMerge();
  cout << "\n>>>>>>>>>>>>> DemoMapNodeMove(); ..." << endl;
  DemoMapNodeMove();

  cout << "\n>>>>>>>>>>>>> DemoVariantPoly1(); ..." << endl;
  DemoVariantPoly1();
  cout << "\n>>>>>>>>>>>>> DemoVariantPoly2(); ..." << endl;
  DemoVariantPoly2();
  cout << "\n>>>>>>>>>>>>> DemoVariantPoly3(); ..." << endl;
  DemoVariantPoly3();
  cout << "\n>>>>>>>>>>>>> DemoVariantPoly4(); ..." << endl;
  DemoVariantPoly4();

  cout << "\n>>>>>>>>>>>>> DemoMutex(); ..." << endl;
  DemoMutex();


  cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << "\n>>>>>>>>>>>>> DemoAngleBracketHack(); ..." << endl;
  DemoAngleBracketHack();

  cout << "\n>>>>>>>>>>>>> DemoMakeUnique(); ..." << endl;
  DemoMakeUnique();

  cout << "\n>>>>>>>>>>>>> DemoIsBaseOf(); ..." << endl;
  DemoIsBaseOf();

  cout << "\n>>>>>>>>>>>>> DemoTraits(); ..." << endl;
  DemoTraits();

  cout << "\n>>>>>>>>>>>>> DemoTestArray(); ..." << endl;
  DemoTestArray();

  Exe("DemoBitset", DemoBitset); 
  Exe("demoLinkedListSorted", demoLinkedListSorted);
  Exe("demoDoubleLinkedListSorted", demoDoubleLinkedListSorted);
  Exe("DemoDSMap", DemoDSMap);

  Exe("DemoForeach", DemoForeach);
  Exe("DemoForeachInvoke", DemoForeachInvoke);
}