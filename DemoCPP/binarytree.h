#ifndef __BINARYTREE_H__  
#define __BINARYTREE_H__ 
//#include <utility>
//#include <algorithm>
#include <cassert>
//#include "iterator.h"
//#include "types.h"
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
    vector<Node *> m_pChild = {nullptr, nullptr}; // 2 hijos inicializados en nullptr
    bool    m_visitedFlag = false;
    Node* m_pParent = nullptr;
  public:
    NodeBinaryTree(T data, Node *p0 = nullptr, Node *p1 = nullptr, Node* p2 = nullptr) 
        : m_data(data)
    {   m_pChild[0] = p0;   m_pChild[1] = p1;   m_pParent = p2;   }
    T         getData()                {   return m_data;    }
    T        &getDataRef()             {   return m_data;    }
    // void      setpChild(Node *pChild, size_t pos)  {   m_pChild[pos] = pChild;  }
    Node    * getChild(size_t branch){ return m_pChild[branch];  }
    Node    *&getChildRef(size_t branch){ return m_pChild[branch];  }
    void      setParent(Node *pParent) { m_pParent = pParent; }
    Node    *&getParentRef()  { return m_pParent; }
    void     changeVisitedFlag()  { m_visitedFlag = !m_visitedFlag; }
    bool    &getVisitedFlag() { return m_visitedFlag; }
};

template <typename Container>
class binary_tree_iterator : public general_iterator<Container,  class binary_tree_iterator<Container> > // 
{public:   
    typedef class general_iterator<Container, binary_tree_iterator<Container> > Parent; 
    typedef typename Container::Node                                  Node; // 
    typedef binary_tree_iterator<Container>                               myself;

  public:
    binary_tree_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    binary_tree_iterator(myself &other)  : Parent (other) {}
    binary_tree_iterator(myself &&other) : Parent(other) {} // Move constructor C++11 en adelante

public:
    binary_tree_iterator operator++() {
      Parent::m_pNode -> changeVisitedFlag();
      Parent::m_pNode = getNext(Parent::m_pNode);
      return *this;
    }
protected:
    Node *getNext(Node* &rCurrent) {
      Node* possibleNext = rCurrent -> getChildRef(1);
      if (possibleNext && possibleNext -> getVisitedFlag() != true)  return Parent::m_pContainer -> getMostLeft(possibleNext);
      Node* parent = rCurrent -> getParentRef();
      if (parent -> getVisitedFlag() != true) return parent;
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
    typedef binary_tree_iterator<myself>    iterator;

protected:
    Node    *m_pRoot = nullptr;
    size_t   m_size  = 0;
    CompareFn Compfn;
public: 
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }
    void    insert(value_type &elem) { internal_insert1(elem, m_pRoot, m_pRoot);  }
    iterator  begin() { iterator iter(this, this -> getMostLeft(m_pRoot)); return iter; }
    iterator  end() { iterator iter(this, this -> getMostRight(m_pRoot)); return iter; }
    Node *&getMostLeft(Node* &rCurrent) {
      if (rCurrent -> getChildRef(0) == nullptr)  return rCurrent;
      return getMostLeft(rCurrent -> getChildRef(0));
    }
    Node *&getMostRight(Node* &rCurrent) {
      if (rCurrent -> getChildRef(1) == nullptr)  return rCurrent;
      return getMostRight(rCurrent -> getChildRef(1));
    }

protected:
    Node *CreateNode(value_type &elem){ return new Node(elem); }
    Node *internal_insert1(value_type &elem, Node *&rCurrent, Node* &rParent)
    {
        if( !rCurrent ) //  llegué al fondo de una rama
        {
          rCurrent = CreateNode(elem);
          if (rCurrent != rParent) {
            rCurrent -> setParent(rParent);
          }
          return rCurrent;
        }
        size_t branch = Compfn(elem, rCurrent->getDataRef() );
        return internal_insert1(elem, rCurrent->getChildRef(branch), rCurrent);
    }
public:
    void inorder(ostream &os){   
        inorder(m_pRoot, os);   
    }
    void preorder(ostream &os) {
        preorder(m_pRoot, os);
    }
    void postorder(ostream &os) {
        postorder(m_pRoot, os);
    }

protected:
    void inorder(Node  *pNode, ostream &os){
        if( pNode )
        {   inorder(pNode->getChild(0), os);
            os << pNode->getDataRef() << endl;
            inorder(pNode->getChild(1), os);
        }
    }

    void preorder(Node *pNode, ostream &os) {
        if (pNode) {
            os << pNode -> getDataRef() << endl;
            preorder(pNode -> getChild(0), os);
            preorder(pNode -> getChild(1), os);
        }
    }

    void postorder(Node *pNode, ostream &os) {
        if (pNode) {
            postorder(pNode -> getChild(0), os);
            postorder(pNode -> getChild(1), os);
            os << pNode -> getDataRef() << endl;
        }
    }
};



#endif