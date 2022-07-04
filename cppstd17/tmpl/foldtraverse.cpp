
#include "foldtraverse.hpp"
#include <iostream>

int main()
{
  // init binary tree structure:
  Node* root = new Node{5};
  root->subLeft = new Node{2};
  root->subLeft->subRight = new Node{4};
  root->subRight = new Node{10};
  root->subRight->subRight = new Node{20};
  root->subRight->subLeft = new Node{8};
  root->subRight->subLeft->subRight = new Node{9};

  // traverse binary tree:
  Node* node = Node::traverse(root, Node::right, Node::left, Node::right);
  std::cout << node->getValue() << '\n';
  node = root ->* Node::right ->* Node::left ->* Node::right;
  std::cout << node->getValue() << '\n';
  node = root -> subRight -> subLeft -> subRight;
  std::cout << node->getValue() << '\n';
}

