#include <bits/stdc++.h>
using namespace std;

struct Node {
  int key, height;
  Node *left;
  Node *right;
  Node *parent;

  Node(int k)
      : key(k), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

class AVLTree {
  Node *root;

  int height(Node *n) { return n ? n->height : 0; }

  int getBalance(Node *n) { return n ? height(n->left) - height(n->right) : 0; }

  void updateHeight(Node *n) {
    if (n)
      n->height = 1 + max(height(n->left), height(n->right));
  }

  Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2)
      T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2)
      T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  Node *rebalance(Node *node) {
    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
      return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) {
      node->left = leftRotate(node->left);
      node->left->parent = node;
      return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
      return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) {
      node->right = rightRotate(node->right);
      node->right->parent = node;
      return leftRotate(node);
    }
    return node;
  }

  Node *insert(Node *node, int key, Node *parent) {
    if (!node) {
      Node *n = new Node(key);
      n->parent = parent;
      return n;
    }
    
    if (key < node->key)
      node->left = insert(node->left, key, node);
    else if (key > node->key)
      node->right = insert(node->right, key, node);
    else
      return node; // no duplicates

    return rebalance(node);
  }

  Node *minValueNode(Node *node) const {
    while (node->left)
      node = node->left;
    return node;
  }

  Node *maxValueNode(Node *node) const {
    while (node->right)
      node = node->right;
    return node;
  }

  Node *deleteNode(Node *root, int key) {
    if (!root)
      return root;

    if (key < root->key)
      root->left = deleteNode(root->left, key);
    else if (key > root->key)
      root->right = deleteNode(root->right, key);
    else {
      if (!root->left || !root->right) {
        Node *temp = root->left ? root->left : root->right;
        if (!temp) {
          temp = root;
          root = nullptr;
        } else {
          *root = *temp;
        }
        delete temp;
      } else {
        Node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
      }
    }

    if (!root)
      return root;

    return rebalance(root);
  }

  Node *search(Node *node, int key) const {
    if (!node || node->key == key)
      return node;
    if (key < node->key)
      return search(node->left, key);
    return search(node->right, key);
  }

  Node *successor(Node *node) const {
    if (!node)
      return nullptr;
    if (node->right)
      return minValueNode(node->right);

    Node *p = node->parent;
    while (p && node == p->right) {
      node = p;
      p = p->parent;
    }
    return p;
  }

  Node *predecessor(Node *node) const {
    if (!node)
      return nullptr;
    if (node->left)
      return maxValueNode(node->left);

    Node *p = node->parent;
    while (p && node == p->left) {
      node = p;
      p = p->parent;
    }
    return p;
  }

public:
  AVLTree() : root(nullptr) {}

  void insert(int key) { root = insert(root, key, nullptr); }

  void deleteNode(int key) { root = deleteNode(root, key); }

  Node *search(int key) const { return search(root, key); }

  int minimum() { return minValueNode(root)->key; }

  int maximum() { return maxValueNode(root)->key; }

  Node *successor(int key) const { return successor(search(root, key)); }

  Node *predecessor(int key) const { return predecessor(search(root, key)); }
};