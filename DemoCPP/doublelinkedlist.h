#ifndef __DOUBLE_LINKEDLIST_H__  
#define __DOUBLE_LINKEDLIST_H__ 

#include "linkedlist.h"

template <typename Container>
class backward_iterator : public general_iterator<Container,  class backward_iterator<Container> > // 
{ public: 
    // TODO: subir al padre  
    typedef typename Container::Node                                         Node;
    typedef class general_iterator<Container, backward_iterator<Container> > Parent;  // 
    typedef backward_iterator<Container>                                     myself;

  public:
    backward_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    backward_iterator(myself &other)  : Parent (other) {}
    backward_iterator(myself &&other) : Parent(other) {}

  public:
    backward_iterator operator++() { Parent::m_pNode = ((Node *)Parent::m_pNode)->getpPrev();  
                                     return *this;
                                   }
};

template <typename T>
class NodeDLL : public NodeLE<T>
{
public:
  //typedef T               Type;
  typedef class NodeLE<T> Parent;
private:
  typedef NodeDLL<T> Node;
  public: 
    Node   *m_pPrev;//
  public:
    NodeDLL(T data, Node *pNext = nullptr, Node *pPrev = nullptr) 
        : Parent(data, pNext), m_pPrev(pPrev)
    {}
   
    void      setpPrev(Node *pPrev)  {   m_pPrev = pPrev;  }
    Node     *getpPrev()             {   return getpPrevRef();   }
    Node    *&getpPrevRef()          {   return m_pPrev;   }
};

template <typename _T>
struct DLLAscTraits
{
    typedef   _T          T;
    typedef  NodeDLL<T>  Node;
    typedef  less<T>     CompareFn;
};

template <typename _T>
struct DLLDescTraits
{
    typedef   _T         T;
    typedef  NodeDLL<T>  Node;
    typedef  greater<T>  CompareFn;
};

template <typename Traits>
class DoubleLinkedList : public LinkedList<Traits>
{
 public:
    typedef typename Traits::T          value_type;
    typedef typename Traits::Node       Node;
    typedef typename Traits::CompareFn  CompareFn;
    typedef DoubleLinkedList<Traits>    myself;
    typedef LinkedList<Traits>          Parent;
    typedef forward_iterator<myself>    iterator;
    typedef backward_iterator<myself>   riterator;
public:
    DoubleLinkedList() {}
    void    insert(value_type elem)
    {   
        Node *pPrevTail = Parent::m_pTail;
        Node *pNew = *Parent::insert_forward(elem);
        if( pNew != Parent::m_pTail )
            ::CreateBridge( ((Node *)pNew->getpNext())->getpPrevRef(), pNew, &Node::m_pPrev);
        else
            pNew->setpPrev(pPrevTail);
    }
    riterator rbegin() { riterator iter(this, Parent::m_pTail);     return iter;    }
    riterator rend()   { riterator iter(this, nullptr);             return iter;    }
    void    push_front(value_type elem)
    {
        Parent::push_front(elem);
        if(Parent::size() > 1)
            ((Node *)Parent::m_pHead->m_pNext)->m_pPrev = Parent::m_pHead;
    }
    void    push_back(value_type elem)
    {   Node *pPrevTail = Parent::m_pTail;
        Parent::push_back(elem);
        Parent::m_pTail->setpPrev(pPrevTail);
    }
};

#endif