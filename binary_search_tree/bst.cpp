#include <iostream>
using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
  Node *parent;

  Node(int val) : key(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
private:
  Node *root;

  Node *search(Node *node, int key) {
    if (node == nullptr || node->key == key)
      return node;
    if (key < node->key)
      return search(node->left, key);
    return search(node->right, key);
  }

  Node *findMin(Node *node) {
    while (node && node->left)
      node = node->left;
    return node;
  }

  Node *findMax(Node *node) {
    while (node && node->right)
      node = node->right;
    return node;
  }

  Node *deleteNode(Node *node, int key) {
    if (!node)
      return node;

    if (key < node->key)
      node->left = deleteNode(node->left, key);
    else if (key > node->key)
      node->right = deleteNode(node->right, key);
    else {
      if (!node->left || !node->right) {
        Node *child = node->left ? node->left : node->right;
        if (child)
          child->parent = node->parent;
        delete node;
        return child;
      }

      Node *temp = findMin(node->right);
      node->key = temp->key;
      node->right = deleteNode(node->right, temp->key);
    }
    return node;
  }

  void inorder(Node *node) {
    if (node) {
      inorder(node->left);
      cout << node->key << " ";
      inorder(node->right);
    }
  }

public:
  BST() : root(nullptr) {}

  void insert(int key) {
    Node *newNode = new Node(key);
    if (!root) {
      root = newNode;
      return;
    }

    Node *parent = nullptr;
    Node *current = root;

    while (current) {
      parent = current;
      if (key < current->key)
        current = current->left;
      else if (key > current->key)
        current = current->right;
      else
        return; // no duplicates in this BST
    }

    newNode->parent = parent;
    if (key < parent->key)
      parent->left = newNode;
    else
      parent->right = newNode;
  }

  bool search(int key) { return search(root, key) != nullptr; }
  void deleteKey(int key) { root = deleteNode(root, key); }
  void inorder() {
    inorder(root);
    cout << "\n";
  }

  Node *successor(int key) {
    Node *current = search(root, key);
    if (!current)
      return nullptr;

    if (current->right)
      return findMin(current->right);

    Node *p = current->parent;
    while (p && current == p->right) {
      current = p;
      p = p->parent;
    }
    return p;
  }

  Node *predecessor(int key) {
    Node *current = search(root, key);
    if (!current)
      return nullptr;

    if (current->left)
      return findMax(current->left);

    Node *p = current->parent;
    while (p && current == p->left) {
      current = p;
      p = p->parent;
    }
    return p;
  }
};

int main() {
  BST tree;
  tree.insert(20);
  tree.insert(8);
  tree.insert(22);
  tree.insert(4);
  tree.insert(12);
  tree.insert(10);
  tree.insert(14);

  cout << "Inorder traversal: ";
  tree.inorder();

  Node *succ = tree.successor(10);
  if (succ)
    cout << "Successor of 10: " << succ->key << "\n";
  else
    cout << "No successor for 10\n";

  Node *pred = tree.predecessor(10);
  if (pred)
    cout << "Predecessor of 10: " << pred->key << "\n";
  else
    cout << "No predecessor for 10\n";

  return 0;
}