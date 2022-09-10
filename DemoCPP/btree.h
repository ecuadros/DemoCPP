#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
#include "btreepage.h"
#define DEFAULT_BTREE_ORDER 3

const size_t MaxHeight = 5; 

template <typename K, typename ID>
struct SimpleTrait
{
       using Type = K;
       using ObjIDType = ID;
};

template <typename Container>
class btree_forward_iterator : public general_iterator<Container,  class btree_forward_iterator<Container> > // 
{
  public:   
    typedef class general_iterator<Container, btree_forward_iterator<Container> >   Parent; 
    typedef typename Container::Node                                                Node; // 
    typedef btree_forward_iterator<Container>                                       myself;

  public:
    btree_forward_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    btree_forward_iterator(myself &other)  : Parent (other) {}
    btree_forward_iterator(myself &&other) : Parent(other) {} // Move constructor C++11 en adelante

  public:
    btree_forward_iterator operator++() {
      Parent::m_pNode -> visit(); 
      Parent::m_pNode = Parent::m_pNode -> getNext();
      return *this;
    }
};

template <typename Trait>
class BTree // this is the full version of the BTree
{
       typedef typename Trait::Type              Type;
       typedef typename Trait::ObjIDType         ObjIDType;     
       typedef BTree <Trait>                     myself;

public:
       //typedef ObjectInfo iterator;
       typedef CBTreePage <Trait>                Node;// useful shorthand
       typedef typename Node::lpfnForEach2    lpfnForEach2;
       typedef typename Node::lpfnForEach3    lpfnForEach3;
       typedef typename Node::lpfnFirstThat2  lpfnFirstThat2;
       typedef typename Node::lpfnFirstThat3  lpfnFirstThat3;
       typedef typename Node::ObjectInfo      ObjectInfo;
       typedef btree_forward_iterator <myself>    iterator;

public:
       BTree(size_t order = DEFAULT_BTREE_ORDER, bool unique = true)
              : m_Order(order),
                m_Root(2 * order  + 1, unique),
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
       bool            Insert (const Type key, const size_t ObjID);
       bool            Remove (const Type key, const size_t ObjID);
       ObjIDType       Search (const Type key)
       {      ObjIDType ObjID = 0;
              m_Root.Search(key, ObjID);
              return ObjID;
       }
       size_t            size()  { return m_NumKeys; }
       size_t            height() { return m_Height;      }
       size_t            GetOrder() { return m_Order;     }
       iterator          begin()   { iterator iter(this, m_Root.getMostLeft()); return iter; }
       iterator          end()     { iterator iter(this, nullptr); return iter; }

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

protected:
       Node          m_Root;
       size_t          m_Height;  // height of tree
       size_t          m_Order;   // order of tree
       size_t          m_NumKeys; // number of keys
       bool            m_Unique;  // Accept the elements only once ?
};     

template <typename Trait>
bool BTree<Trait>::Insert(const Type key, const size_t ObjID)
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

template <typename Trait>
bool BTree<Trait>::Remove (const Type key, const size_t ObjID)
{
       bt_ErrorCode error = m_Root.Remove(key, ObjID);
       if( error == bt_duplicate || error == bt_nofound )
               return false;
       m_NumKeys--;

       if( error == bt_rootmerged )
               m_Height--;
       return true;
}

#endif