#ifndef __DEMO_H__  
#define __DEMO_H__ 

#include <iostream>

template <typename T>
void Exe(std::string msg, T func)
{
  std::cout << "\n>>>>>>>>>>>>> " << msg << "() ..." << std::endl;
  func();
}

// Basics
void DemoBasics();
void CounterTest();
void DemoInitializer1();
void DemoInitializer2();
void DemoInitializer3();
void DemoTypeId();
void DemoConditional();

void DemoMultipleParams();
void DemoTupleOverload();
void DemoVariadicOverload();

void demoVariadic();
void DemoFoldedFunctions();
void DemoHomogeneous();
void DemoInvoke();

// Inheritance
void DemoMultiBase1();
void DemoMultiBase2();         // # Pending Er !
void DemoVirtual();

void DemoFoldTraverse();
void DemoPrintAuto();

void DemoLambdaFunctions();
void DemoVarTmplAuto();

void DemoCallBacks();
void DemoCheckPath3();

void DemoCreateFile();
void DemoTimeAsString();
void DemoSymlink();

void DemoConvert();
void DemoIncomplete();

void DemoMapHandle();
void DemoMapNodeMerge();
void DemoMapNodeMove();

void DemoVariantPoly1();
void DemoVariantPoly2();
void DemoVariantPoly3();
void DemoVariantPoly4();

void DemoMutex();
void DemoAngleBracketHack();
void DemoMakeUnique();

void DemoTestArray();
void DemoTemplateParamTypes();
void DemoForeach();
void DemoForeachInvoke();

void DemoLen();
void DemoMax();
void DemoConstructor();
void DemoSizeScope();

void DemoBitset();
void demoLinkedListSorted();
void demoDoubleLinkedListSorted();
void DemoDSMap();
void DemoStack();
void DemoMultiset();

void DemoSort1();
void DemoSort2();
void DemoPermutation();

void DemoIsBaseOf();
void DemoBasicTraits();
void DemoTraits();

void DemoInnerProduct();

void DemoSmartPtr();
void DemoRegex();

void DemoAmpersand();
void DemoPointersL1();
void DemoPointersL2Vectors();
void DemoPointersL2VectorX();
void DemoPointersL3Matrix();
void DemoPointerstoFn();

#endif