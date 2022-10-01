#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
#include "btreepage.h"
#define DEFAULT_BTREE_ORDER 3

template <typename Container>
class btree_iterator : public general_iterator<Container,  class btree_iterator<Container> > // 
{public: 
    typedef class general_iterator<Container, btree_iterator<Container> > Parent; 
    typedef typename Container::Node Node; // 
    typedef btree_iterator<Container> myself;
       
 public:
    btree_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    btree_iterator(myself &other)  : Parent (other) {}
    btree_iterator(myself &&other) : Parent(other) {} 
    size_t H = Parent::m_pContainer->height();
    size_t N = H;
    vector<size_t> pos = {0, 0, 0, 0, 0};
    //size_t ord = Parent::m_pContainer->GetOrder();
    size_t ord;
    typename Parent::Type &operator*()     
       {      size_t _pos = pos[N-1];
              ord = Parent::m_pNode->NoK();
              return Parent::m_pNode->getDataRef(_pos);   }

 public:
    btree_iterator operator++() 
       {       
         if (N == H)
         { if (pos[N-1] < ord-1) {   pos[N-1]++;  }
           else{
             pos[N-1]=0;
             N--;
             Parent::m_pNode = (Node *)Parent::m_pNode->m_pParent; 
           }
         }
         else{
           if (pos[N-1] < ord)
           { 
             pos[N-1]++;
             Parent::m_pNode = (Node *)Parent::m_pNode->GetFirstObject(pos[N-1]);
             N = H;
           }
           else{
             pos[N-1]=0;
             N--;
             Parent::m_pNode = (Node *)Parent::m_pNode->m_pParent; 
           }
         }
         return *this;
       }
};

const size_t MaxHeight = 5; 
template <typename Traits>
class BTree // this is the full version of the BTree
{
       typedef typename Traits::Type keyType;
       typedef typename Traits::ObjIDType ObjIDType;

public:
       typedef CBTreePage<Traits> Node;// useful shorthand
       //typedef ObjectInfo iterator;
       typedef typename Node::lpfnForEach2 lpfnForEach2;
       typedef typename Node::lpfnForEach3 lpfnForEach3;
       typedef typename Node::lpfnFirstThat2 lpfnFirstThat2;
       typedef typename Node::lpfnFirstThat3 lpfnFirstThat3;
       typedef typename Node::ObjectInfo ObjectInfo;
       typedef BTree<Traits> myself;
       typedef btree_iterator<myself> iterator;

public:
       BTree(size_t order = DEFAULT_BTREE_ORDER, bool unique = true)
              : m_Order(order),
                m_Root(2 * order + 1, unique),
                m_Unique(unique),
                m_NumKeys(0)
       {
              m_Root.SetMaxKeysForChilds(order);
              m_Height = 1;
       }
       ~BTree() {}
       //int           Open (char * name, int mode);
       //int           Create (char * name, int mode);
       //int           Close ();
       bool            Insert (const keyType key, const long ObjID);
       bool            Remove (const keyType key, const long ObjID);
       void            PrintDet(bool op_variantes = true);
       ObjIDType       Search (const keyType key)
       {      ObjIDType ObjID = -1;
              m_Root.Search(key, ObjID);
              return ObjID;
       }
       size_t            size()  { return m_NumKeys; }
       size_t            height() { return m_Height;      }
       size_t            GetOrder() { return m_Order;     }

       void            Print (ostream &os)
       {               m_Root.Print(os);                              }
       void            ForEach( lpfnForEach2 lpfn, void *pExtra1 )
       {               m_Root.ForEach(lpfn, 0, pExtra1);              }
       void            ForEach( lpfnForEach3 lpfn, void *pExtra1, void *pExtra2)
       {               m_Root.ForEach(lpfn, 0, pExtra1, pExtra2);     }
       ObjectInfo*     FirstThat( lpfnFirstThat2 lpfn, void *pExtra1 )
       {               return m_Root.FirstThat(lpfn, 0, pExtra1);     }
       ObjectInfo*     FirstThat( lpfnFirstThat3 lpfn, void *pExtra1, void *pExtra2)
       {               return m_Root.FirstThat(lpfn, 0, pExtra1, pExtra2);   }
       //typedef               ObjectInfo iterator;
       iterator begin() { iterator iter(this, m_Root.GetFirstObject(0));    return iter;    }
       //iterator end()   { iterator iter(this, m_Root.GetLastObject()) ;    return iter;    }
       iterator end()   { iterator iter(this, nullptr) ;    return iter;    }

protected:
       Node            m_Root;
       size_t          m_Height;  // height of tree
       size_t          m_Order;   // order of tree
       size_t          m_NumKeys; // number of keys
       bool            m_Unique;  // Accept the elements only once ?
};     

template <typename Traits>
bool BTree<Traits>::Insert(const keyType key, const long ObjID)
{
       bt_ErrorCode error = m_Root.Insert(key, ObjID);
       if( error == bt_duplicate )
               return false;
       m_NumKeys++;
       if( error == bt_overflow )
       {
               m_Root.SplitRoot();
               m_Height++;
       }
       return true;
}

template <typename Traits>
bool BTree<Traits>::Remove (const keyType key, const long ObjID)
{
       bt_ErrorCode error = m_Root.Remove(key, ObjID);
       if( error == bt_duplicate || error == bt_nofound )
               return false;
       m_NumKeys--;

       if( error == bt_rootmerged )
               m_Height--;
       return true;
}

template <typename Traits>
void BTree<Traits>::PrintDet(bool var)
{
       if (var) {
              cout << "Detalles" << endl;
              cout << "Llaves en la raiz: " << m_Root.NumberOfKeys() << endl;
              cout << "Tamaño  : " << size() << endl;
              cout << "Altura: " << height() << endl;
              cout << endl;
       } else {
              cout << "Orden: " << GetOrder() << endl;
              cout << "Tamaño del vector SubPages: " << m_Root.m_SubPages.size() << endl;
              m_Root.PrintKeysAndSubPages((height())); cout << endl;
       }
}

#endif
