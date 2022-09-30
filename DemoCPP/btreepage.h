#ifndef __CBTreePage_H__
#define __CBTreePage_H__

#include "types.h"
#include <vector>
#include <assert.h>
#include <functional>
#include <type_traits>

// TODO: #1 Crear una function para agregarla al demo.cpp ( no trivial )
// TODO: #3 crear un iterator ( no trivial )
//       Sugerencia: Tarea1 cada pagina debe tener un puntero al padre primero ( no trivial )
// TODO: #4 integrarlo al recorrer ( no trivial )


// TODO: #2 Agregarle un Trait (prueba git) ( no trivial )

template <typename Traits>
class BTree;

template <typename Traits>
bool is_Void = std::is_void<Traits>::value;
//assert(is_Void)

using namespace std;
enum bt_ErrorCode {bt_ok, bt_overflow, bt_underflow, bt_duplicate, bt_nofound, bt_rootmerged};

// template <typename Container, typename ObjType>
template <typename Container, typename ObjType, typename CompareFn>
size_t binary_search(Container& container, size_t first, size_t last, ObjType &object, CompareFn CompFn)
{
       if( first >= last )
               return first;
       while( first < last )
       {
               size_t mid = (first+last)/2;
               if( object == (ObjType)container[mid ] )
                       return mid;
               // if( object > (ObjType)container[mid ] )
               if( CompFn((ObjType)container[mid ],object) )
                       first = mid+1;
               else
                       last  = mid;
       }
       // if( object <= (ObjType)container[first] )
       if( CompFn(object,(ObjType)container[first]) || object == (ObjType)container[first])
               return first;
       return last;
}

// Error al poner size_t
// Posible motivo: El i está disminuyendo
template <typename Container, typename ObjType>
void insert_at(Container& container, ObjType object, int pos)
{
        // TODO: #5 replace int, long by types such as size_t
       size_t size = container.size();
       for(int i = size-2 ; i >= pos ; i--)
               container[i+1] = container[i];
       container[pos] =  object;	
}

template <typename Container>
void remove(Container& container, size_t pos)
{
       size_t size = container.size();
       for(auto i = pos+1 ; i < size ; i++)
           container[i-1] = container[i];
}

//template <typename keyType, typename ObjIDType>
template <typename Traits>
struct tagObjectInfo
{
       typedef typename Traits::Type  keyType;
       typedef typename Traits::ObjIDType ObjIDType;
       keyType                 key;
       ObjIDType               ObjID;
       size_t                  UseCounter;
       tagObjectInfo(const keyType     &_key, ObjIDType _ObjID)
               : key(_key), ObjID(_ObjID), UseCounter(0) {}
       tagObjectInfo(const tagObjectInfo &objInfo)
               : key(objInfo.key), ObjID(objInfo.ObjID), UseCounter(0) {}
       tagObjectInfo()                          {}
       operator keyType                         ()     { return key; }
       size_t                    GetUseCounter() { return UseCounter;    }
};

template <typename Traits>
class CBTreePage //: public SimpleIndex <keyType>
// this is the in-memory version of the CBTreePage
{
       friend class BTree<Traits>;
       typedef typename Traits::Type  keyType;
       typedef typename Traits::ObjIDType  ObjIDType; 

       typedef CBTreePage<Traits>    BTPage;         // useful shorthand
       // typedef tagObjectInfo<keyType, ObjIDType> ObjectInfo;
       typedef tagObjectInfo<Traits> ObjectInfo;

       typedef void (*lpfnForEach2)(ObjectInfo &info, size_t level, void *pExtra1);
       typedef void (*lpfnForEach3)(ObjectInfo &info, size_t level, void *pExtra1, void *pExtra2);

       typedef ObjectInfo *(*lpfnFirstThat2)(ObjectInfo &info, size_t level, void *pExtra1);
       typedef ObjectInfo *(*lpfnFirstThat3)(ObjectInfo &info, size_t level, void *pExtra1, void *pExtra2);
 public:
       CBTreePage(size_t maxKeys, bool unique = true);
       using Type       = keyType;  // para el iterador
       virtual ~CBTreePage();

       BTPage         *m_pParent = nullptr;
       bt_ErrorCode    Insert (const keyType &key, const ObjIDType ObjID);
       bt_ErrorCode    Remove (const keyType &key, const ObjIDType ObjID);
       bool            Search (const keyType &key, ObjIDType &ObjID);
       void            Print  (ostream &os);

       keyType         &getDataRef()            {   return m_Keys[0].key;    }
       keyType         &getDataRef(size_t pos)  {   return m_Keys[pos].key;  }

       // TODO: #6 change by Invoke
       // TODO: #7 ForEach must be a template inside this template
       // void            ForEach(lpfnForEach2 lpfn, size_t level, void *pExtra1);
       // void            ForEach(lpfnForEach3 lpfn, size_t level, void *pExtra1, void *pExtra2);
       template <typename lpfnForEach, typename... Args>
       void            ForEachG(lpfnForEach lpfn, size_t level, Args... args);

       // TODO: #8 You may reduce these two function by using Invoke
       // ObjectInfo*     FirstThat(lpfnFirstThat2 lpfn, size_t level, void *pExtra1);
       // ObjectInfo*     FirstThat(lpfnFirstThat3 lpfn, size_t level, void *pExtra1, void *pExtra2);
       template <typename lpfnFirstThat, typename... Args>
       ObjectInfo*     FirstThatG(lpfnFirstThat lpfn, size_t level, Args... args);

       void            PrintKeysAndSubPages(size_t height);
       BTPage          *&GetFirstObject(size_t key);
       BTPage          *&GetLastObject();
       BTPage          *&GetPage(size_t num_page) {  return m_SubPages[num_page];   }
       size_t           NoK()  { return m_KeyCount; }
       string          KeysToString()
                        {       string KTS = "";
                                for (size_t i = 0; i < NumberOfKeys(); i++)
                                        KTS += m_Keys[i];
                                return KTS;
                        }
        void            SetParent(BTPage *Parent) {  m_pParent = Parent;   }

protected:
       // TODO: #9 change by size_t
       size_t  m_MinKeys; // minimum number of keys in a node
       size_t  m_MaxKeys, // maximum number of keys in a node

                m_MaxKeysForChilds; // just to distinguish the root
       bool m_Unique;
       bool m_isRoot;
       //size_t           NextNode; // address of next node at same level
       //size_t RecAddr; // address of this node in the BTree file
       vector<ObjectInfo> m_Keys;
       vector<BTPage *>m_SubPages;
       
       // TODO: #10 size_t
       size_t  m_KeyCount;
       void  Create();
       void  Reset ();
       void  Destroy () {   Reset(); delete this;}
       void  clear ();

       bool  Redistribute1   (size_t &pos);
       bool  Redistribute2   (size_t pos);
       void  RedistributeR2L (size_t pos);
       void  RedistributeL2R (size_t pos);

       bool    TreatUnderflow  (size_t &pos)
       {       return Redistribute1(pos) || Redistribute2(pos);}

       bt_ErrorCode    Merge  (size_t pos);
       bt_ErrorCode    MergeRoot ();
       void  SplitChild (size_t pos);

       ObjectInfo &GetFirstObjectInfo();
       ObjectInfo &GetLastObjectInfo();

       bool Overflow()  { return m_KeyCount > m_MaxKeys; }
       bool Underflow() { return m_KeyCount < MinNumberOfKeys(); }
       bool IsFull()    { return m_KeyCount >= m_MaxKeys; }


       size_t  MinNumberOfKeys()  { return 2*m_MaxKeys/3.0; }
       size_t  GetFreeCells()  { return m_MaxKeys - m_KeyCount; }
       size_t& NumberOfKeys()  { return m_KeyCount; }
       size_t  GetNumberOfKeys()  { return m_KeyCount; }
       bool IsRoot()  { return m_MaxKeysForChilds != m_MaxKeys; }
       void SetMaxKeysForChilds(size_t orderforchilds)
       {        m_MaxKeysForChilds = orderforchilds;       }
       size_t GetFreeCellsOnLeft(size_t pos)
       {        if( pos > 0 )                                   // there is some page on left ?
                        return m_SubPages[pos-1]->GetFreeCells();
                return 0;
       }
       size_t GetFreeCellsOnRight(size_t pos)
       {    if( pos < GetNumberOfKeys() )   // there is some page on right ?
                return m_SubPages[pos+1]->GetFreeCells();
            return 0;
       }

private:
       bool SplitRoot();
       void SplitPageInto3(vector<ObjectInfo>   & tmpKeys,
                                               vector<BTPage *>  & SubPages,
                                               BTPage           *& pChild1,
                                               BTPage           *& pChild2,
                                               BTPage           *& pChild3,
                                               ObjectInfo        & oi1,
                                               ObjectInfo        & oi2);
       void MovePage(BTPage *  pChildPage,vector<ObjectInfo> & tmpKeys,vector<BTPage *> & tmpSubPages);
};

template <typename Traits>
CBTreePage<Traits>:: CBTreePage(size_t maxKeys, bool unique)
                               : m_MaxKeys(maxKeys), m_Unique(unique), m_KeyCount(0)
{
       Create();
       SetMaxKeysForChilds(m_MaxKeys);
}

template <typename Traits>
CBTreePage<Traits>::~CBTreePage()
{
       Reset();
}

template <typename Traits>
bt_ErrorCode CBTreePage<Traits>::Insert(const keyType& key, const ObjIDType ObjID)
{
       typename Traits::CompareFn CompFn; 
       size_t pos = binary_search(m_Keys, 0, m_KeyCount, key, CompFn);
       bt_ErrorCode error = bt_ok;

       if( pos < m_KeyCount && (keyType)m_Keys[pos] == key && m_Unique)
               return bt_duplicate; // this key is duplicate

       if( !m_SubPages[pos] ) // this is a leave
       {
               ::insert_at(m_Keys, ObjectInfo(key, ObjID), pos);
               m_KeyCount++;
               if( Overflow() )
                       return bt_overflow;
               return bt_ok;
       }
       else
       {
               // recursive insertion
               error = m_SubPages[pos]->Insert(key, ObjID);
               if( error == bt_overflow )
               {
                       if( !Redistribute1(pos) )
                               SplitChild(pos);
                       if( Overflow() )          // Propagate overflow
                               return bt_overflow;
                       return bt_ok;
               }
       }
       if( Overflow() ) // node overflow
               return bt_overflow;
       return bt_ok;
}

template <typename Traits>
bool CBTreePage<Traits>::Redistribute1(size_t &pos)
{
       if( m_SubPages[pos]->Underflow() )
       {
               size_t NumberOfKeyOnLeft = 0,
                       NumberOfKeyOnRight = 0;
               // is this the first element or there are more elements on right brother
               if( pos > 0 )
                       NumberOfKeyOnLeft = m_SubPages[pos-1]->NumberOfKeys();
               if( pos < NumberOfKeys() )
                       NumberOfKeyOnRight = m_SubPages[pos+1]->NumberOfKeys();

               if( NumberOfKeyOnLeft > NumberOfKeyOnRight )
                       if( m_SubPages[pos-1]->NumberOfKeys() > m_SubPages[pos-1]->MinNumberOfKeys() )
                               RedistributeL2R(pos-1); // bring elements from left brother
                       else
                               if( pos == NumberOfKeys() )
                                       return (--pos, false);
                               else
                                       return false;
               else //NumberOfKeyOnLeft < NumberOfKeyOnRight )
                       if( m_SubPages[pos+1]->NumberOfKeys() > m_SubPages[pos+1]->MinNumberOfKeys() )
                               RedistributeR2L(pos+1); // bring elements from right brother
                       else
                               if( pos == 0 )
                                       return (++pos, false);
                               else
                                       return false;
       }
       else // it is due to overflow
       {
               size_t FreeCellsOnLeft = GetFreeCellsOnLeft(pos),   // Free Cells On Left
               fcor = GetFreeCellsOnRight(pos);  // Free Cells On Right

               if( !FreeCellsOnLeft && !fcor && m_SubPages[pos]->IsFull() )
                       return false;
               if( FreeCellsOnLeft > fcor ) // There is more space on left
                       RedistributeR2L(pos);
               else
                       RedistributeL2R(pos);

       }
       return true;
}

// Redistribute2 function
// it considers two brothers m_SubPages[pos-1] && m_SubPages[pos+1]
// if it fails the only way is merge !
template <typename Traits>
bool CBTreePage<Traits>::Redistribute2(size_t pos)
{
       assert( pos > 0 && pos < NumberOfKeys()  );
       assert( m_SubPages[pos-1] != 0 && m_SubPages[pos] != 0 && m_SubPages[pos+1] != 0 );
       assert( m_SubPages[pos-1]->Underflow() ||
                       m_SubPages[ pos ]->Underflow() ||
                       m_SubPages[pos+1]->Underflow() );

       if( m_SubPages[pos-1]->Underflow() )
       {       // Rotate R2L
               RedistributeR2L(pos+1);
               RedistributeR2L(pos);
               if( m_SubPages[pos-1]->Underflow() )
                       return false;
       }
       else if( m_SubPages[pos+1]->Underflow() )
       {       // Rotate L2R
               RedistributeL2R(pos-1);
               RedistributeL2R(pos);
               if( m_SubPages[pos+1]->Underflow() )
                       return false;
       }
       else // The problem is exactly at pos !
       {
               // Rotate L2R
               RedistributeL2R(pos-1);
               RedistributeR2L(pos+1);
               if( m_SubPages[pos]->Underflow() )
                       return false;
       }
       return true;
}

template <typename Traits>
void CBTreePage<Traits>::RedistributeR2L(size_t pos)  
{
       BTPage  *pSource = m_SubPages[ pos ],
               *pTarget = m_SubPages[pos-1];
       ObjectInfo oi_empty;

       while(pSource->GetNumberOfKeys() > pSource->MinNumberOfKeys() &&
                 pTarget->GetNumberOfKeys() < pSource->GetNumberOfKeys() )
       {
               // Move from this page to the down-left page \/
               ::insert_at(pTarget->m_Keys, m_Keys[pos-1], pTarget->NumberOfKeys()++);
               // Move the pointer leftest pointer to the rightest position
               ::insert_at(pTarget->m_SubPages, pSource->m_SubPages[0], pTarget->NumberOfKeys());

               // Move the leftest element to the root
               m_Keys[pos-1] = pSource->m_Keys[0];

               // Remove the leftest element from rigth page
               ::remove(pSource->m_Keys    , 0);
               ::remove(pSource->m_SubPages, 0);
               pSource->m_Keys[pSource->NumberOfKeys()-1] = oi_empty;
               pSource->NumberOfKeys()--;
               if (pTarget->m_SubPages[0]) {  pTarget->m_SubPages[pTarget->NumberOfKeys()]->SetParent(pTarget);  }
       }
}

template <typename Traits>
void CBTreePage<Traits>::RedistributeL2R(size_t pos)
{
       BTPage  *pSource = m_SubPages[pos],
                       *pTarget = m_SubPages[pos+1];
       ObjectInfo oi_empty;
       while(pSource->GetNumberOfKeys() > pSource->MinNumberOfKeys() &&
                 pTarget->GetNumberOfKeys() < pSource->GetNumberOfKeys() )
       {
               // Move from this page to the down-RIGHT page \/
               ::insert_at(pTarget->m_Keys, m_Keys[pos], 0);
               // Move the pointer rightest pointer to the leftest position
               ::insert_at(pTarget->m_SubPages, pSource->m_SubPages[pSource->NumberOfKeys()], 0);
               pTarget->NumberOfKeys()++;

               // Move the rightest element to the root
               m_Keys[pos] = pSource->m_Keys[pSource->NumberOfKeys()-1];
               pSource->m_Keys[pSource->NumberOfKeys()-1] = oi_empty;

               // Remove the leftest element from rigth page
               // it is not necessary erase because m_KeyCount controls
               pSource->NumberOfKeys()--;
               if (pTarget->m_SubPages[0]) {  pTarget->m_SubPages[0]->SetParent(pTarget);  }
       }
}

template <typename Traits>
void CBTreePage<Traits>::SplitChild(size_t pos)
{
       // FIRST: deciding the second page to split
       BTPage  *pChild1 = 0, *pChild2 = 0;
       if( pos > 0 )                                   // is left page full ?
               if( m_SubPages[pos-1]->IsFull() )
               {
                       pChild1 = m_SubPages[pos-1];
                       pChild2 = m_SubPages[pos--];
               }
       if( pos < GetNumberOfKeys() )   // is right page full ?
               if( m_SubPages[pos+1]->IsFull() )
               {
                       pChild1 = m_SubPages[pos];
                       pChild2 = m_SubPages[pos+1];
               }
       // size_t nKeys = pChild1->GetNumberOfKeys() + pChild2->GetNumberOfKeys() + 1;

       // SECOND: copy both pages to a temporal one
       // Create two tmp vector
       vector<ObjectInfo> tmpKeys;
       //tmpKeys.resize(nKeys);
       vector<BTPage *>   tmpSubPages;
       //tmpKeys.resize(nKeys+1);

       // copy from left child
       MovePage(pChild1, tmpKeys, tmpSubPages);
       // copy a key from parent
       tmpKeys    .push_back(m_Keys[pos]);

       // copy from right child
       MovePage(pChild2, tmpKeys, tmpSubPages);

       BTPage *pChild3 = 0;
       ObjectInfo oi1, oi2;
       SplitPageInto3(tmpKeys, tmpSubPages, pChild1, pChild2, pChild3, oi1, oi2);

       // copy the first element to the root
       m_Keys    [pos] = oi1;
       m_SubPages[pos] = pChild1;

       // copy the second element to the root
       ::insert_at(m_Keys, oi2, pos+1);
       ::insert_at(m_SubPages, pChild2, pos+1);
       NumberOfKeys()++;

       m_SubPages[pos+2] = pChild3;
}

template <typename Traits>
void CBTreePage<Traits>::SplitPageInto3(vector<ObjectInfo>& tmpKeys,
                                                vector<BTPage *>  & tmpSubPages,
                                                BTPage*                   &     pChild1,
                                                BTPage*                   &     pChild2,
                                                BTPage*                   &     pChild3,
                                                ObjectInfo                & oi1,
                                                ObjectInfo                & oi2)
{
       assert(tmpKeys.size() >= 8);
       assert(tmpSubPages.size() >= 9);
       if( !pChild1 )
       {
               pChild1 = new BTPage(m_MaxKeysForChilds, m_Unique);
               pChild1->SetParent(this);
       }
       // Split tmpKeys page into 3 pages
       // copy 1/3 elements to the first child
       // pChild1->clear();
       pChild1->Reset();
       size_t nKeys = (tmpKeys.size()-2)/3;
       size_t i = 0;
       for(; i < nKeys; i++ )
       {
               if (tmpSubPages[i]) {  tmpSubPages[i]->SetParent(pChild1);  }
               pChild1->m_Keys    [i] = tmpKeys    [i];
               pChild1->m_SubPages[i] = tmpSubPages[i];
               pChild1->NumberOfKeys()++;
       }
       if (tmpSubPages[i]) {  tmpSubPages[i]->SetParent(pChild1);  }
       pChild1->m_SubPages[i] = tmpSubPages[i];

       // first element to go up !
       oi1 = tmpKeys[i++];

       if( !pChild2 )
       {
               pChild2 = new BTPage(m_MaxKeysForChilds, m_Unique);
               pChild2->m_pParent = this;
       }
       // pChild2->clear();
       pChild2->Reset();
       // copy 1/3 to the second child
       nKeys += (tmpKeys.size()-2)/3 + 1;
       size_t j = 0;
       for(; i < nKeys; i++, j++ )
       {
               if (tmpSubPages[i]) {  tmpSubPages[i]->m_pParent = pChild2;  }
               pChild2->m_Keys    [j] = tmpKeys    [i];
               pChild2->m_SubPages[j] = tmpSubPages[i];
               pChild2->NumberOfKeys()++;
       }
       if (tmpSubPages[i]) {  tmpSubPages[i]->m_pParent = pChild2;  }
       pChild2->m_SubPages[j] = tmpSubPages[i];

       // copy the second element to the root
       oi2 = tmpKeys[i++];

       // copy 1/3 to the third child
       if( !pChild3 )
       {
               pChild3 = new BTPage(m_MaxKeysForChilds, m_Unique);
               pChild3->m_pParent = this;
       }
       // pChild3->clear();
       pChild3->Reset();
       nKeys = tmpKeys.size();
       for(j = 0; i < nKeys; i++, j++)
       {
               if (tmpSubPages[i]) {  tmpSubPages[i]->m_pParent = pChild3;  }
               pChild3->m_Keys    [j] = tmpKeys    [i];
               pChild3->m_SubPages[j] = tmpSubPages[i];
               pChild3->NumberOfKeys()++;
       }
       if (tmpSubPages[i]) {  tmpSubPages[i]->m_pParent = pChild3;  }
       pChild3->m_SubPages[j] = tmpSubPages[i];
}

template <typename Traits>
bool CBTreePage<Traits>::SplitRoot()
{
       BTPage  *pChild1 = 0, *pChild2 = 0, *pChild3 = 0, *pChild_empty = 0;
       ObjectInfo oi1, oi2, oi_empty;
       SplitPageInto3( m_Keys,m_SubPages,pChild1, pChild2, pChild3, oi1, oi2);
       clear();

       // copy the first element to the root
       m_Keys    [0] = oi1;
       m_SubPages[0] = pChild1;
       NumberOfKeys()++;

       // copy the second element to the root
       m_Keys    [1] = oi2;
       m_SubPages[1] = pChild2;
       NumberOfKeys()++;

       m_SubPages[2] = pChild3;

       for (size_t i=2; i < m_MaxKeys; i++)
       {
                m_Keys[i] = oi_empty;
                m_SubPages[i+1] = pChild_empty;
       }
       return true;
}

template <typename Traits>
bool CBTreePage<Traits>::Search(const keyType &key, ObjIDType &ObjID)
{
       size_t pos = binary_search(m_Keys, 0, m_KeyCount, key);
       if( pos >= m_KeyCount )
       {    if( m_SubPages[pos] )
                return m_SubPages[pos]->Search(key, ObjID);
            else
                return false;
       }
       if( key == m_Keys[pos].key )
       {
               ObjID = m_Keys[pos].ObjID;
               m_Keys[pos].UseCounter++;
               return true;
       }
       if( key < m_Keys[pos].key )
               if( m_SubPages[pos] )
                       return m_SubPages[pos]->Search(key, ObjID);
       return false;
}

/*template <typename keyType, typename ObjIDType>
void CBTreePage<keyType, ObjIDType>::ForEachReverse(lpfnForEach2 lpfn, size_t level, void *pExtra1)
{
       if( m_SubPages[m_KeyCount] )
               m_SubPages[m_KeyCount]->ForEach(lpfn, level+1, pExtra1);
       for(size_t i = m_KeyCount-1 ; i >= 0  ; i--)
       {
               lpfn(m_Keys[i], level, pExtra1);
               if( m_SubPages[i] )
                       m_SubPages[i]->ForEach(lpfn, level+1, pExtra1);
       }
}*/

/*template <typename Trait>
void CBTreePage<Trait>::ForEach(lpfnForEach2 lpfn, size_t level, void *pExtra1)
{
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       m_SubPages[i]->ForEach(lpfn, level+1, pExtra1);
               lpfn(m_Keys[i], level, pExtra1);
       }
       if( m_SubPages[m_KeyCount] )
               m_SubPages[m_KeyCount]->ForEach(lpfn, level+1, pExtra1);
}*/

/*template <typename keyType, typename ObjIDType>
void CBTreePage<keyType, ObjIDType>::ForEachReverse(lpfnForEach3 lpfn,
                                                                                                       size_t level, void *pExtra1, void *pExtra2)
{
       if( m_SubPages[m_KeyCount] )
               m_SubPages[m_KeyCount]->ForEach(lpfn, level+1, pExtra1, pExtra2);
       for(size_t i = m_KeyCount-1 ; i >= 0  ; i--)
       {
               lpfn(m_Keys[i], level, pExtra1, pExtra2);
               if( m_SubPages[i] )
                       m_SubPages[i]->ForEach(lpfn, level+1, pExtra1, pExtra2);
       }
}*/

/*template <typename Trait>
void CBTreePage<Trait>::ForEach(lpfnForEach3 lpfn, size_t level, void *pExtra1, void *pExtra2)
{
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       m_SubPages[i]->ForEach(lpfn, level+1, pExtra1, pExtra2);
               lpfn(m_Keys[i], level, pExtra1, pExtra2);
       }
       if( m_SubPages[m_KeyCount] )
               m_SubPages[m_KeyCount]->ForEach(lpfn, level+1, pExtra1, pExtra2);
}*/

template <typename Traits>
template <typename lpfnForEach, typename... Args>
void CBTreePage<Traits>::ForEachG(lpfnForEach lpfn, size_t level, Args... args)
{
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       m_SubPages[i]->ForEachG(lpfn, level+1, args...);
               lpfn(m_Keys[i], level, args...);
       }
       if( m_SubPages[m_KeyCount] )
               m_SubPages[m_KeyCount]->ForEachG(lpfn, level+1, args...);
}

/* template <typename Trait>
typename CBTreePage<Trait>::ObjectInfo *
CBTreePage<Trait>::FirstThat(lpfnFirstThat2 lpfn, size_t level, void *pExtra1)
{
       ObjectInfo *pTmp;
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       if( (pTmp = m_SubPages[i]->FirstThat(lpfn, level+1, pExtra1)) )
                               return pTmp;
               if( lpfn(m_Keys[i], level, pExtra1) )
                       return &m_Keys[i];
       }
       if( m_SubPages[m_KeyCount] )
               if( (pTmp = m_SubPages[m_KeyCount]->FirstThat(lpfn, level+1, pExtra1)) )
                       return pTmp;
       return 0;
} */

/* template <typename Trait>
typename CBTreePage<Trait>::ObjectInfo *
CBTreePage<Trait>::FirstThat(lpfnFirstThat3 lpfn,size_t level, void *pExtra1, void *pExtra2)
{
       ObjectInfo *pTmp;
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       if( (pTmp = m_SubPages[i]->FirstThat(lpfn, level+1, pExtra1, pExtra2) ) )
                               return pTmp;
               if( lpfn(m_Keys[i], level, pExtra1, pExtra2) )
                       return &m_Keys[i];
       }
       if( m_SubPages[m_KeyCount] )
               if( (pTmp = m_SubPages[m_KeyCount]->FirstThat(lpfn, level+1, pExtra1, pExtra2) ) )
                       return pTmp;
       return 0;
} */

template <typename Traits>
template <typename lpfnFirstThat, typename... Args>
typename CBTreePage<Traits>::ObjectInfo *
CBTreePage<Traits>::FirstThatG(lpfnFirstThat lpfn, size_t level, Args... args)
{
       ObjectInfo *pTmp;
       for(size_t i = 0 ; i < m_KeyCount ; i++)
       {
               if( m_SubPages[i] )
                       if( (pTmp = m_SubPages[i]->FirstThatG(lpfn, level+1, args...)) )
                               return pTmp;
               if( lpfn(m_Keys[i], level, args...) )
                       return &m_Keys[i];
       }
       if( m_SubPages[m_KeyCount] )
               if( (pTmp = m_SubPages[m_KeyCount]->FirstThatG(lpfn, level+1, args...)) )
                       return pTmp;
       return 0;
}

template <typename Traits>
bt_ErrorCode CBTreePage<Traits>::Remove(const keyType &key, const ObjIDType ObjID)
{
       bt_ErrorCode error = bt_ok;
       typename Traits::CompareFn CompFn;
       size_t pos = binary_search(m_Keys, 0, m_KeyCount, key, CompFn);
       if( pos < NumberOfKeys() && key == m_Keys[pos].key /*&& m_Keys[pos].m_ObjID == ObjID*/) // We found it !
       {
               // This is a leave: First
               if( !m_SubPages[pos+1] )  // This is a leave ? FIRST CASE !
               {
                       ::remove(m_Keys, pos);
                       NumberOfKeys()--;
                       if( Underflow() )
                               return bt_underflow;
                       return bt_ok;
               }

               // We FOUND IT BUT it is NOT a leave ? SECOND CASE !
               {
                       // Get the first element from right branch
                       ObjectInfo &rFirstFromRight = m_SubPages[pos+1]->GetFirstObjectInfo();
                       // change with a leave
                       swap(m_Keys[pos], rFirstFromRight);
                       // Remove it from this leave

                       //Print(cout);
                       error = m_SubPages[++pos]->Remove(key, ObjID);
               }
       }
       else if( pos == NumberOfKeys() ) // it is not here, go by the last branch
               error = m_SubPages[pos]->Remove(key, ObjID);
       else if( key <= m_Keys[pos].key ) // = is because identical keys are inserted on left (see Insert)
       {        if( m_SubPages[pos] )
                       error = m_SubPages[pos]->Remove(key, ObjID);
               else
                       return bt_nofound;
       }
       if( error == bt_underflow )
       {
               // THIRD CASE: After removing the element we have an underflow
               // Print(cout);
               if( TreatUnderflow(pos) )
                       return bt_ok;
               // FOURTH CASE: it was not possible to redistribute -> Merge
               if( IsRoot() && NumberOfKeys() == 2 )
                       return MergeRoot();
               return Merge(pos);
       }
       if( error == bt_nofound )
               return bt_nofound;
       return bt_ok;   
}


template <typename Traits>
bt_ErrorCode CBTreePage<Traits>::Merge(size_t pos)
{
       assert( m_SubPages[pos-1]->NumberOfKeys() +
                       m_SubPages[ pos ]->NumberOfKeys() +
                       m_SubPages[pos+1]->NumberOfKeys() ==
                       3*m_SubPages[ pos ]->MinNumberOfKeys() - 1);

       // FIRST: Put all the elements into a vector
       vector<ObjectInfo> tmpKeys;
       //tmpKeys.resize(nKeys);
       vector<BTPage *>   tmpSubPages;

       BTPage  *pChild1 = m_SubPages[pos-1],
                       *pChild2 = m_SubPages[ pos ],
                       *pChild3 = m_SubPages[pos+1];
       MovePage(pChild1, tmpKeys, tmpSubPages);
       tmpKeys    .push_back(m_Keys[pos-1]);
       MovePage(pChild2, tmpKeys, tmpSubPages);
       tmpKeys    .push_back(m_Keys[ pos ]);
       MovePage(pChild3, tmpKeys, tmpSubPages);
       pChild3->Destroy();;

       // Move 1/2 elements to pChild1
       size_t nKeys = pChild1->GetFreeCells();
       size_t i = 0;
       for(; i < nKeys ; i++ )
       {
               pChild1->m_Keys    [i] = tmpKeys    [i];
               pChild1->m_SubPages[i] = tmpSubPages[i];
               pChild1->NumberOfKeys()++;
       }
       pChild1->m_SubPages[i] = tmpSubPages[i];

       m_Keys    [pos-1] = tmpKeys[i];
       m_SubPages[pos-1] = pChild1;
       //pChild1->m_pParent = this;

       ::remove(m_Keys    , pos);
       ::remove(m_SubPages, pos);
       NumberOfKeys()--;

       nKeys = pChild2->GetFreeCells();

       // TODO: #32 change int by size_t ✓
       size_t j = ++i;
       for(i = 0 ; i < nKeys ; i++, j++ )
       {
               pChild2->m_Keys    [i] = tmpKeys    [j];
               pChild2->m_SubPages[i] = tmpSubPages[j];
               pChild2->NumberOfKeys()++;
       }
       pChild2->m_SubPages[i] = tmpSubPages[j];
       m_SubPages[ pos ]          = pChild2;
       //pChild2->m_pParent = this;

       if( Underflow() )
               return bt_underflow;
       return bt_ok;
}

template <typename Traits>
bt_ErrorCode CBTreePage<Traits>::MergeRoot()
{
        // TODO: #33 change int by size_t ✓
       size_t pos = 1;
       assert( m_SubPages[pos-1]->NumberOfKeys() +
                       m_SubPages[ pos ]->NumberOfKeys() +
                       m_SubPages[pos+1]->NumberOfKeys() ==
                       3*m_SubPages[ pos ]->MinNumberOfKeys() - 1);

       BTPage  *pChild1 = m_SubPages[pos-1], *pChild2 = m_SubPages[ pos ], *pChild3 = m_SubPages[pos+1];
       // TODO: #34 change int by size_t ✓
       size_t nKeys = pChild1->NumberOfKeys() + pChild2->NumberOfKeys() + pChild3->NumberOfKeys() + 2;

       // FIRST: Put all the elements into a vector
       vector<ObjectInfo> tmpKeys;
       //tmpKeys.resize(nKeys);
       vector<BTPage *>   tmpSubPages;

       MovePage(pChild1, tmpKeys, tmpSubPages);
       tmpKeys    .push_back(m_Keys[pos-1]);
       MovePage(pChild2, tmpKeys, tmpSubPages);
       tmpKeys    .push_back(m_Keys[ pos ]);
       MovePage(pChild3, tmpKeys, tmpSubPages);

       clear();
       size_t i = 0;
       for( ; i < nKeys ; i++ )
       {
               m_Keys    [i] = tmpKeys    [i];
               m_SubPages[i] = tmpSubPages[i];
               NumberOfKeys()++;
       }
       m_SubPages[i] = tmpSubPages[i];

       //Print(cout);
       pChild1->Destroy();
       pChild2->Destroy();
       pChild3->Destroy();

       return bt_rootmerged;
}

template <typename Traits>
typename CBTreePage<Traits>::ObjectInfo &
CBTreePage<Traits>::GetFirstObjectInfo()
{
        if( m_SubPages[0] )
                return m_SubPages[0]->GetFirstObjectInfo();
        return m_Keys[0];
}

template <typename Traits>
typename CBTreePage<Traits>::ObjectInfo &
CBTreePage<Traits>::GetLastObjectInfo()
{
        if( m_SubPages[m_KeyCount] )
                return m_SubPages[m_KeyCount]->GetLastObjectInfo();
        return m_Keys[m_KeyCount-1];
}

template <typename Traits>
CBTreePage<Traits> *&CBTreePage<Traits>::GetFirstObject(size_t key)
{
        if( m_SubPages[key]->m_SubPages[0])
                return m_SubPages[key]->GetFirstObject(0);
        return m_SubPages[key];
}

template <typename Traits>
CBTreePage<Traits> *&CBTreePage<Traits>::GetLastObject()
{
        if( m_SubPages[m_KeyCount]->m_SubPages[0])
                return m_SubPages[m_KeyCount]->GetLastObject();
        return m_SubPages[m_KeyCount];
}

template <typename Traits>
void Print(tagObjectInfo<Traits> &info, size_t level, void *pExtra)
{
       ostream &os = *(ostream *)pExtra;
       for(size_t i = 0; i < level ; i++)
               os << "\t";
       os << info.key << "->" << info.ObjID << "\n";
}

template <typename Traits>
void CBTreePage<Traits>::Print(ostream & os)
{
       lpfnForEach2 lpfn = &::Print<Traits>;
       ForEachG(lpfn, 0, &os);
}

template <typename Traits>
void CBTreePage<Traits>::Create()
{
       Reset();
       m_Keys.resize(m_MaxKeys+1);
       m_SubPages.resize(m_MaxKeys+2, nullptr);
       // Ya está dentro de Clear()
       //m_KeyCount = 0;
       m_MinKeys  = 2 * m_MaxKeys/3;
}

template <typename Traits>
void CBTreePage<Traits>::Reset()
{
        // TODO: #35 change int by size_t ✓
       for( size_t i = 0 ; i < m_KeyCount ; i++ )
               delete m_SubPages[i];
       clear();
}

template <typename Traits>
void CBTreePage<Traits>::clear()
{
       //m_Keys.clear();
       //m_SubPages.clear();
       m_KeyCount = 0;
}

template <typename Traits>
CBTreePage<Traits> * CreateBTreeNode (size_t maxKeys, bool unique)
{
       return new CBTreePage<Traits> (maxKeys, unique);
}

template <typename Traits>
void CBTreePage<Traits>::MovePage(BTPage *pChildPage, vector<ObjectInfo> &tmpKeys,vector<BTPage *> &tmpSubPages)
{
        // TODO: #37 change int by size_t ✓
       size_t nKeys = pChildPage->GetNumberOfKeys();
       size_t i = 0;
       for(; i < nKeys; i++ )
       {
                tmpKeys    .push_back(pChildPage->m_Keys[i]);
                tmpSubPages.push_back(pChildPage->m_SubPages[i]);
       }
       tmpSubPages.push_back(pChildPage->m_SubPages[i]);
       pChildPage->clear();
}

template <typename Traits>
void CBTreePage<Traits>::PrintKeysAndSubPages(size_t height)
{
       cout << " Recorrido árbol (keys del padre entre parentesis)" << endl;
       size_t i = 0;
       for( ; i < m_KeyCount+1 ; i++ )
       {
               size_t total_sub_pages_i = m_SubPages[i]->m_KeyCount+1;
               size_t j = 0;
               for( ; j < total_sub_pages_i ; j++ )
               {
                        if (height == 3)
                        {
                                size_t total_sub_pages_j = m_SubPages[i]->m_SubPages[j]->m_KeyCount+1;
                                cout << endl;
                                cout << "\t\t";
                                size_t k = 0;
                                for(; k < total_sub_pages_j ; k++ )
                                        cout << m_SubPages[i]->m_SubPages[j]->m_Keys[k] << "(" << m_SubPages[i]->m_SubPages[j]->m_pParent->KeysToString() << ")-";
                        }
                        cout << endl;
                        cout << "\t";
                        cout << m_SubPages[i]->m_Keys[j] << "(" << m_SubPages[i]->m_pParent->KeysToString() << ")-";
               }


               cout << "\nKey " << i << ": " << m_Keys[i] << endl;
       }
       if (m_SubPages[i])
       {
       size_t total_sub_pages_i = m_SubPages[i]->m_KeyCount;
       for( size_t j = 0 ; j < total_sub_pages_i ; j++ )
                cout << m_SubPages[i]->m_Keys[j] << "-";
        }
}

#endif