#include <iostream>
#include <tuple>
#include "demo.h"
using namespace std;

// Test desde Mac
// g++ -pthread -std=c++17 -o main main.cpp demo.cpp
// Comentario extra de Mac
// Texto sugerido

template <typename T>
void Exe(std::string msg, T func)
{
  cout << "\n>>>>>>>>>>>>> " << msg << "(); ..." << endl;
  func();
}

int main()
{
  Exe("CounterTest", CounterTest);
  Exe("DemoInitializer1", DemoInitializer1);
  Exe("DemoInitializer2", DemoInitializer2);
  Exe("DemoInitializer3", DemoInitializer3);
  exit(0);

  Exe("DemoMultipleParams", DemoMultipleParams);
  Exe("DemoTupleOverload", DemoTupleOverload);
  Exe("DemoVariadicOverload", DemoVariadicOverload);
  Exe("demoVariadic", demoVariadic);
  Exe("DemoFoldedFunctions", DemoFoldedFunctions);
  Exe("DemoHomogeneous", DemoHomogeneous);
  Exe("DemoInvoke", DemoInvoke);
  
  Exe("DemoFoldTraverse", DemoFoldTraverse);
  Exe("DemoPrintAuto", DemoPrintAuto);
  Exe("DemoLambdaFunctions", DemoLambdaFunctions);
  Exe("DemoVarTmplAuto", DemoVarTmplAuto);

  Exe("DemoMultiBase1", DemoMultiBase1);
  Exe("DemoMultiBase2", DemoMultiBase2);
  Exe("DemoVirtual", DemoVirtual);

  Exe("DemoCallBacks", DemoCallBacks);
  Exe("DemoIfCompTime", DemoIfCompTime);
  Exe("DemoCheckPath3", DemoCheckPath3);
  Exe("DemoCreateFile", DemoCreateFile);

  //  Exe("DemoTimeAsString", DemoTimeAsString);
  Exe("DemoSymlink", DemoSymlink);
  Exe("DemoConvert", DemoConvert);
  Exe("DemoIncomplete", DemoIncomplete);

  Exe("DemoMapHandle", DemoMapHandle);
  Exe("DemoMapNodeMerge", DemoMapNodeMerge);
  Exe("DemoMapNodeMove", DemoMapNodeMove);

  Exe("DemoVariantPoly1", DemoVariantPoly1);
  Exe("DemoVariantPoly2", DemoVariantPoly2);
  Exe("DemoVariantPoly3", DemoVariantPoly3);
  Exe("DemoVariantPoly4", DemoVariantPoly4);
  Exe("DemoMutex", DemoMutex);

  cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  Exe("DemoAngleBracketHack", DemoAngleBracketHack);
  Exe("DemoMakeUnique", DemoMakeUnique);
  Exe("DemoIsBaseOf", DemoIsBaseOf);
  Exe("DemoTraits", DemoTraits);
  Exe("DemoTestArray", DemoTestArray);
  Exe("DemoTemplateParamTypes", DemoTemplateParamTypes);

  Exe("DemoForeach", DemoForeach);
  Exe("DemoForeachInvoke", DemoForeachInvoke);

  Exe("DemoLen", DemoLen);
  Exe("DemoMax", DemoMax);
  Exe("DemoConstructor", DemoConstructor);
  Exe("DemoSizeScope", DemoSizeScope);

  Exe("DemoBitset", DemoBitset); 
  Exe("demoLinkedListSorted", demoLinkedListSorted);
  Exe("demoDoubleLinkedListSorted", demoDoubleLinkedListSorted);
  Exe("DemoDSMap", DemoDSMap);
  Exe("DemoStack", DemoStack);
  Exe("DemoMultiset", DemoMultiset);

  Exe("DemoSort1", DemoSort1);
  Exe("DemoSort2", DemoSort2);
  Exe("DemoPermutation", DemoPermutation);

  return 0;
}

int main1()
{
  cout << "Hola mundo\nOtra linea\n";
  return 0;
}