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
    Node *  m_pParent = nullptr;
    vector<Node *> m_pChild = {nullptr, nullptr}; // 2 hijos inicializados en nullptr
  public:
    NodeBinaryTree(Node *pParent, T data, Node *p0 = nullptr, Node *p1 = nullptr) 
        : m_pParent(pParent), m_data(data)
    {   m_pChild[0] = p0;   m_pChild[1] = p1;   }
    T         getData()                {   return m_data;    }
    T        &getDataRef()             {   return m_data;    }
    void      setpChild(Node *pChild, size_t pos)  {   m_pChild[pos] = pChild;  }
    Node    * getChild(size_t branch){ return m_pChild[branch];  }
    Node    *&getChildRef(size_t branch){ return m_pChild[branch];  }
    Node    * getParent() { return m_pParent;   }
};

#define _DEF(_Container, _iter)  \
public: \
    typedef class general_iterator<_Container, _iter<Container> > Parent;     \
    typedef typename _Container::Node                             Node;       \
    typedef _iter<_Container>                                     myself;

template <typename Container>
class binary_tree_iterator : public general_iterator<Container,  class binary_tree_iterator<Container> > // 
{  _DEF(Container, binary_tree_iterator); // TODO: llevar esta misma idea a todos container ya existentes

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
    void    insert(value_type &elem) { internal_insert1(elem, nullptr, m_pRoot);  }

protected:
    Node *CreateNode(Node *pParent, value_type &elem){ return new Node(pParent, elem); }
    Node *internal_insert1(value_type &elem, Node *pParent, Node *&rpOrigin)
    {
        if( !rpOrigin ) //  llegué al fondo de una rama
        {   ++m_size;
            return (rpOrigin = CreateNode(pParent, elem));
        }
        size_t branch = Compfn(elem, rpOrigin->getDataRef() );
        return internal_insert1(elem, rpOrigin, rpOrigin->getChildRef(branch));
    }
public:
    void inorder  (ostream &os)    {   inorder  (m_pRoot, os, 0);  }
    void postorder(ostream &os)    {   postorder(m_pRoot, os, 0);  }
    void preorder (ostream &os)    {   preorder (m_pRoot, os, 0);  }
    void print    (ostream &os)    {   print    (m_pRoot, os, 0);  }
    void inorder(void (*visit) (value_type& item))
    {   inorder(m_pRoot, visit);    }

protected:
    void inorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   Node *pParent = pNode->getParent();
            inorder(pNode->getChild(0), os, level+1);
            os << " --> " << pNode->getDataRef();
            inorder(pNode->getChild(1), os, level+1);
        }
    }

    void postorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   
            postorder(pNode->getChild(0), os, level+1);
            postorder(pNode->getChild(1), os, level+1);
            os << " --> " << pNode->getDataRef();
        }
    }

    void preorder(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   
            os << " --> " << pNode->getDataRef();
            preorder(pNode->getChild(0), os, level+1);
            preorder(pNode->getChild(1), os, level+1);            
        }
    }
    
    void print(Node  *pNode, ostream &os, size_t level)
    {
        if( pNode )
        {   Node *pParent = pNode->getParent();
            print(pNode->getChild(1), os, level+1);
            //os << string(" | ") * level << pNode->getDataRef() << "(" << (pParent?(pNode->getBranch()?"R-":"L-") + to_string(pParent->getData()):"Root") << ")" <<endl;
            os << string(" | ") * level << pNode->getDataRef() << "(" << (pParent?to_string(pParent->getData()):"Root") << ")" <<endl;
            print(pNode->getChild(0), os, level+1);
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