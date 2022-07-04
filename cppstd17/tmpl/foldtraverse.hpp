
// define binary tree structure and traverse helpers:
struct Node
{
  int value;
  Node* subLeft{nullptr};
  Node* subRight{nullptr};
  Node(int i = 0) : value{i} {}
  int getValue() const {  return value;  }

  // traverse helpers:
  static constexpr auto left  = &Node::subLeft;
  static constexpr auto right = &Node::subRight;

  // traverse tree, using fold expression:
  template<typename T, typename... TP>
  static Node* traverse (T np, TP... paths)
  {
    return (np ->* ... ->* paths);      // np ->* paths1 ->* paths2 ...
  }
};

