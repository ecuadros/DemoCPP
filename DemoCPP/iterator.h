#ifndef __ITERATOR_H__
#define __ITERATOR_H__
//#include <algorithm>
//#include <utility>

template <typename Container, class IteratorBase> // 
class general_iterator
{public:
    using Node = typename Container::Node;
    using Type = typename Node::Type;
    //typedef class general_iterator<Container> Parent;
    using myself = general_iterator<Container, IteratorBase>; // 
    
protected:
    Container *m_pContainer;
    Node      *m_pNode;
public:
    general_iterator(Container *pContainer, Node *pNode)
        : m_pContainer(pContainer), m_pNode(pNode) {}
    general_iterator(myself &other) 
          : m_pContainer(other.m_pContainer), m_pNode(other.m_pNode){}
    general_iterator(myself &&other) // Move constructor
          {   m_pContainer = move(other.m_pContainer);
              m_pNode      = move(other.m_pNode);
          }
    IteratorBase operator=(IteratorBase &iter)
          {   m_pContainer = move(iter.m_pContainer);
              m_pNode = move(iter.m_pNode);
              return *(IteratorBase *)this; // Pending static_cast?
          }

    bool operator==(IteratorBase iter)   { return m_pNode == iter.m_pNode; }
    bool operator!=(IteratorBase iter)   { return !(*this == iter);        }
    Type &operator*()                    { return m_pNode->getDataRef();   }
          
};

#endif
 