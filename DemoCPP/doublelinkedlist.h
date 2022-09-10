#ifndef __DOUBLE_LINKEDLIST_H__  
#define __DOUBLE_LINKEDLIST_H__ 

#include "linkedlist.h"

template <typename Container>
class backward_iterator : public general_iterator<Container,  class backward_iterator<Container> > // 
{ public: 
    // TODO: subir al padre  
    using Node   = typename Container::Node;
    using Parent = class general_iterator<Container, backward_iterator<Container> >;  // 
    using myself = backward_iterator<Container>;

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
  using Parent = class NodeLE<T>;
private:
  using Node = NodeDLL<T>;
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
    using   T        = _T;
    using  Node      = NodeDLL<T>;
    using  CompareFn = less<T>;
};

template <typename _T>
struct DLLDescTraits
{
    using T         = _T;
    using Node      = NodeDLL<T>;
    using CompareFn = greater<T>;
};

template <typename Traits>
class DoubleLinkedList : public LinkedList<Traits>
{
 public:
    using value_type = typename Traits::T;
    using Node       = typename Traits::Node;
    using CompareFn  = typename Traits::CompareFn;
    using myself     = DoubleLinkedList<Traits>;
    using iterator   = forward_iterator<myself>;
    
    using Parent     = LinkedList<Traits>;
    using riterator  = backward_iterator<myself>;
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