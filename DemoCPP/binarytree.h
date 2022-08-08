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
  public:
    NodeBinaryTree(T data, Node *p0 = nullptr, Node *p1 = nullptr) 
        : m_data(data)
    {   m_pChild[0] = p0;   m_pChild[1] = p1;   }
    T         getData()                {   return m_data;    }
    T        &getDataRef()             {   return m_data;    }
    void      setpChild(Node *pChild, size_t pos)  {   m_pChild[pos] = pChild;  }
    Node    * getChild(size_t branch){ return m_pChild[branch];  }
    Node    *&getChildRef(size_t branch){ return m_pChild[branch];  }
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
    binary_tree_iterator operator++() { //Parent::m_pNode = (Node *)Parent::m_pNode->getpNext();  
                                        return *this;
                                  }
};

template <typename _T>
struct BinaryTreeAscTraits
{
    using  T         = _T;
    using  Node      = NodeBinaryTree<T>;
    using  CompareFn = less<T>;
};

template <typename _T>
struct BinaryTreeDescTraits
{
    using  T         = _T;
    using  Node      = NodeBinaryTree<T>;
    using  CompareFn = greater<T>;
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
    void    insert(value_type &elem) { internal_insert1(elem, m_pRoot);  }

protected:
    Node *CreateNode(value_type &elem){ return new Node(data); }
    Node *internal_insert1(value_type &elem, Node *&rParent)
    {
        if( !rParent ) //  llegué al fondo de una rama
            return (rParent = CreateNode(elem));
        size_t branch = Compfn(elem, rParent->getDataRef() );
        return internal_insert1(elem, rParent->getChildRef(branch));
    }
public:
    void inorden(ostream &os)
    {   inorden(m_pRoot, os);   }

protected:
    void inorden(Node  *pNode, ostream &os)
    {
        if( pNode )
        {   inorden(pNode->getChild(0), os);
            os << pNode->getDataRef() << endl;
            inorden(pNode->getChild(1), os);
        }
    }
};



#endif