#ifndef __BINARYTREE_H__  
#define __BINARYTREE_H__ 
//#include <utility>
//#include <algorithm>
#include <cassert>
//#include "iterator.h"
//#include "types.h"
#include "util.h"
using namespace std;

template <typename T>
class NodeBinaryTree
{
  public:
    typedef T         Type;
  private:
    typedef NodeBinaryTree<T> Node;
  public:
    T       m_data;
    Node    *m_pParent = nullptr;
    vector<Node *> m_pChild = {nullptr, nullptr}; // 2 hijos inicializados en nullptr
    bool    m_visitedFlag = false;
  public:
    NodeBinaryTree(Node *pParent, T data, Node *p0 = nullptr, Node *p1 = nullptr) 
        : m_pParent(pParent), m_data(data)
    {   m_pChild[0] = p0;   m_pChild[1] = p1;   }
    T         getData()                {   return m_data;    }
    T        &getDataRef()             {   return m_data;    }
    Node    * getChild(size_t branch){ return m_pChild[branch];  }
    Node    *&getChildRef(size_t branch){ return m_pChild[branch];  }
    Node    * getParent() { return m_pParent;   }
    void      visitNode() { m_visitedFlag = !m_visitedFlag; }
    bool     &getVisitedFlag()  { return m_visitedFlag; }
    Node    *&getSibling() {
      if ( !m_pParent)  return m_pParent;
      if ( this == m_pParent -> getChildRef(0)) return m_pParent -> getChildRef(1);
      return m_pParent -> getChildRef(0);
    }
};

template <typename Container>
class in_order_iterator : public general_iterator<Container,  class in_order_iterator<Container> > // 
{
  public:   
    typedef class general_iterator<Container, in_order_iterator<Container> > Parent; 
    typedef typename Container::Node                                  Node; // 
    typedef in_order_iterator<Container>                               myself;

  public:
    in_order_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    in_order_iterator(myself &other)  : Parent (other) {}
    in_order_iterator(myself &&other) : Parent(other) {} // Move constructor C++11 en adelante

  public:
    in_order_iterator operator++() {
      Parent::m_pNode -> visitNode();
      Parent::m_pNode = getNext(Parent::m_pNode);
      return *this;
    }

  protected:
    Node *getNext(Node *&rCurrent) {
      Node *rightChild = rCurrent -> getChildRef(1);
      if (rightChild && rightChild -> getVisitedFlag() != true) return Parent::m_pContainer -> getMostLeft(rightChild);
      Node *parent = rCurrent -> getParent();
      if (!parent || parent -> getVisitedFlag() != true) return parent;
      return getNext(parent);
    }

};

template <typename Container>
class pre_order_iterator : public general_iterator <Container, class pre_order_iterator <Container> >
{
  public:
    typedef class general_iterator <Container, pre_order_iterator <Container> >     Parent;
    typedef typename Container::Node                                                Node;
    typedef pre_order_iterator <Container>                                          myself;

  public:
    pre_order_iterator(Container *pContainer, Node *pNode) : Parent (pContainer, pNode) {}
    pre_order_iterator(myself &other) : Parent (other) {}
    pre_order_iterator(myself &&other) : Parent (other) {}

  public:
    pre_order_iterator operator++() {
      Parent::m_pNode -> visitNode();
      Parent::m_pNode = getNext(Parent::m_pNode);
      return *this;
    }

  protected:
    Node *getNext(Node *&rCurrent) {
      Node *leftChild = rCurrent -> getChildRef(0);
      if (leftChild && leftChild -> getVisitedFlag() != true) return leftChild;
      Node *rightChild = rCurrent -> getChildRef(1);
      if (rightChild && rightChild -> getVisitedFlag() != true) return rightChild;
      Node *parent = rCurrent -> getParent();
      if (!parent)  return parent;
      return getNext(parent);
    }
};

template <typename Container>
class post_order_iterator : public general_iterator <Container, class post_order_iterator <Container> >
{
  public:
    typedef class general_iterator <Container, post_order_iterator <Container> >    Parent;
    typedef typename  Container::Node                                               Node;
    typedef post_order_iterator <Container>                                         myself;

  public:
    post_order_iterator(Container *pContainer, Node *pNode) : Parent (pContainer, pNode) {}
    post_order_iterator(myself &other) : Parent (other) {}
    post_order_iterator(myself &&other) : Parent (other) {}

  public:
    post_order_iterator operator++() {
      Parent::m_pNode -> visitNode();
      Parent::m_pNode = getNext(Parent::m_pNode);
      return *this;
    }

  protected:
    Node *getNext(Node *&rCurrent) {
      Node *leftChild = rCurrent -> getChildRef(0);
      if (leftChild && leftChild -> getVisitedFlag() != true)  return getNext(leftChild);
      Node *rightChild = rCurrent -> getChildRef(1);
      if (rightChild && rightChild -> getVisitedFlag() != true) return getNext(rightChild);
      if (rCurrent -> getVisitedFlag() != true)                   return rCurrent;
      Node *sibling = rCurrent -> getSibling();
      if (sibling && sibling -> getVisitedFlag() != true)       return getNext(sibling);
      Node *parent = rCurrent -> getParent();
      if (!parent || parent -> getVisitedFlag() != true)        return parent;
      return getNext(parent);
    }
};

template <typename _T>
struct BinaryTreeAscTraits
{
    using  T         = _T;
    using  Node      = NodeBinaryTree<T>;
    using  CompareFn = greater<T>;
};

template <typename _T>
struct BinaryTreeDescTraits
{
    using  T         = _T;
    using  Node      = NodeBinaryTree<T>;
    using  CompareFn = less<T>;
};

template <typename Traits>
class BinaryTree
{
  public:
    typedef typename Traits::T          value_type;
    typedef typename Traits::Node       Node;
    
    typedef typename Traits::CompareFn      CompareFn;
    typedef BinaryTree<Traits>              myself;
    typedef in_order_iterator <myself>    iterator;
    // typedef pre_order_iterator <myself>     iterator;
    // typedef post_order_iterator <myself>    iterator;

  protected:
    Node    *m_pRoot = nullptr;
    size_t   m_size  = 0;
    CompareFn Compfn;
  public: 
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }
    void    insert(value_type &elem) { first_insert(elem);  }
    iterator  begin()     { iterator  iter(this, this -> getInitInOrder(m_pRoot));  return iter;  }
    // iterator  begin()     { iterator  iter(this, this -> getInitPreOrder(m_pRoot));  return iter;  }
    // iterator begin()      { iterator  iter(this, this -> getInitPostOrder(m_pRoot)); return iter;  }
    iterator  end()       { iterator  iter(this, nullptr); return iter;  }

  protected:
    Node *CreateNode(Node *pParent, value_type &elem){ return new Node(pParent, elem); } 
    void first_insert(value_type &elem) {
      if (!m_pRoot) {
        m_pRoot = CreateNode(nullptr, elem);
        return;
      }
      size_t branch = Compfn(elem, m_pRoot -> getDataRef());
      return recursive_insert(elem, m_pRoot, branch);
    }
    void recursive_insert(value_type &elem, Node *&m_pParent, size_t &branch) {
      if (!m_pParent -> getChildRef(branch))  {
        m_pParent -> getChildRef(branch) = CreateNode(m_pParent, elem);
        return;
      }
      size_t newBranch = Compfn(elem, m_pParent -> getChildRef(branch) -> getDataRef());
      return recursive_insert(elem, m_pParent -> getChildRef(branch), newBranch);
    }

  public:
    Node  *&getInitInOrder(Node *&rCurrent) {
      return getMostLeft(rCurrent);
    }
    Node *&getInitPreOrder(Node *&rCurrent) {
      return m_pRoot;
    }
    Node  *&getInitPostOrder(Node *&rCurrent) {
      if (rCurrent -> getChildRef(0)) return getInitPostOrder(rCurrent -> getChildRef(0));
      if (rCurrent -> getChildRef(1)) return getInitPostOrder(rCurrent -> getChildRef(1));
      return rCurrent;
    }
    Node  *&getMostLeft(Node *&rCurrent) {
      if (!rCurrent -> getChildRef(0))  return rCurrent;
      return getMostLeft(rCurrent -> getChildRef(0));
    }

  public:
    void inorder  (ostream &os)    {   inorder  (m_pRoot, os, 0);   }
    void postorder(ostream &os)    {   postorder(m_pRoot, os, 0); }
    void preorder (ostream &os)    {   preorder (m_pRoot, os, 0);  }
    void inorder(void (*visit) (value_type& item))
    {   inorder(m_pRoot, visit);    }

  protected:
    void inorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   Node *pParent = pNode->getParent();
            inorder(pNode->getChild(0), os, level+1);
            os << string("  ") * level << pNode->getDataRef() << "(" << (pParent?pParent->getData(): -1) << ")" <<endl;
            inorder(pNode->getChild(1), os, level+1);
        }
    }

    void postorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   
            postorder(pNode->getChild(0), os, level+1);
            postorder(pNode->getChild(1), os, level+1);
            os << string("  ") * level << pNode->getDataRef() << endl;
        }
    }

    void preorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   
            os << string("  ") * level << pNode->getDataRef() << endl;
            preorder(pNode->getChild(0), os, level+1);
            preorder(pNode->getChild(1), os, level+1);            
        }
    }

    void inorder(Node  *pNode, void (*visit) (value_type& item))
    {
        if( pNode )
        {   
            inorder(pNode->getChild(0), *visit);
            (*visit)(pNode->getDataRef());
            inorder(pNode->getChild(1), *visit);
        }
    }
};



#endif