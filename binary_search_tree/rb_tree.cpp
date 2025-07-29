// created on 29th July 2025
#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node {
  int key;
  Color color;
  Node *left, *right, *parent;

  Node(int key) : key(key) {
    color = RED;
    left = right = parent = nullptr;
  }
};

class RedBlackTree {
  Node *root;
  Node *NIL;

  // CLRS Pg. 301
  void leftRotate(Node *x) {
    // will have right child
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NIL)
      y->left->parent = x;
    y->parent = x->parent;

    // update parent for y
    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node *y) {
    // will have left child
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NIL)
      x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == nullptr)
      root = x;
    else if (y == y->parent->right)
      y->parent->right = x;
    else
      y->parent->left = x;

    x->right = y;
    y->parent = x;
  }

  /* Information about the fixup algorithm
    Fixing Property Violation that can occur
    1. Root being black
    2. Red Node should have only Black children

    The way we are fixing is by looking closely at the different cases.

    Invariants of the loop are
    1. Node z is red
    2. if p[z] is root, then p[z] is black
    3. if there is a violation of the red-black properites, there is at most one
       violation, it is of either property 2 or property 4
  */
  void insertFixup(Node *z) {
    while (z->parent->color == RED) {
      // p[z] is the left child of p[p[z]]
      if (z->parent == z->parent->parent->left) {
        Node *y = z->parent->parent->right; // uncle of z
        if (y->color == RED) {
          z->parent->color = BLACK;       // Case (1)
          y->color = BLACK;               // Case (1)
          z->parent->parent->color = RED; // Case (1)
          z = z->parent->parent;          // Case (1)
        } else {
          if (z == z->parent->right) { // Case (2)
            z = z->parent;             // Case (2)
            leftRotate(z);             // Case (2)
          }
          z->parent->color = BLACK;       // Case (3)
          z->parent->parent->color = RED; // Case (3)
          rightRotate(z->parent->parent); // Case (3)
        }
      }
      // p[z] is the right child of p[p[z]] - symmetric to previous case
      else {
        Node *y = z->parent->parent->left;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }

    // fixes property 1
    root->color = BLACK;
  }

  // move node v to node u place by updating the u's parent
  void transplant(Node *u, Node *v) {
    if (u->parent == nullptr)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    v->parent = u->parent;
  }

  /* Information about the fixup algorithm
    Fixing Property Violation that can occur
    1. Root being black y could be root itself
    2. Red Node should have only blank, when x and p[y] both are red
    3. Number of black nodes is same on all paths from any node to leaf, black
    is deleted some ancestor can get violated

    The way we are fixing is by looking closely at the different cases.

    We will look how property (5) is brought back through the various cases and
    transformations
  */
  void deleteFixup(Node *x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        Node *w = x->parent->right; // w is sibling and w cannot be NIL
        if (w->color == RED) {
          w->color = BLACK;       // Case (1)
          x->parent->color = RED; // Case (1)
          leftRotate(x->parent);  // Case (1)
          w = x->parent->right;   // Case (1) -> Case (2)
        }

        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED; // Case (2)
          x = x->parent;  // Case (2) - looked as pushing extra black up
        } else {
          if (w->right->color == BLACK) {
            w->left->color = BLACK; // Case (3)
            w->color = RED;         // Case (3)
            rightRotate(w);         // Case (3)
            w = x->parent->right;   // Case (3)
          }
          w->color = x->parent->color; // Case (4) - Termination
          x->parent->color = BLACK;    // Case (4)
          w->right->color = BLACK;     // Case (4)
          leftRotate(x->parent);       // Case (4)
          x = root;                    // Case (4)
        }
      } else {
        Node *w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rightRotate(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }

  Node *minimum(Node *x) const {
    while (x->left != NIL)
      x = x->left;
    return x;
  }

  Node *maximum(Node *x) const {
    while (x->right != NIL)
      x = x->right;
    return x;
  }

  Node *search(Node *node, int key) const {
    if (node == NIL || key == node->key)
      return node;
    if (key < node->key)
      return search(node->left, key);
    return search(node->right, key);
  }

public:
  RedBlackTree() {
    NIL = new Node(0);
    NIL->color = BLACK;
    root = NIL;
  }

  void insert(int key) {
    // z color is RED
    Node *z = new Node(key);
    z->left = z->right = NIL;

    // standard bst insert
    Node *y = nullptr;
    Node *x = root;
    while (x != NIL) {
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;

    // fix the properties
    insertFixup(z);
  }

  void deleteNode(int key) {
    Node *z = search(root, key);
    if (z == NIL)
      return;

    Node *y = z;
    Color yOriginalColor = y->color;
    Node *x;

    // standard bst deletion
    if (z->left == NIL) {
      x = z->right;
      transplant(z, z->right);
    } else if (z->right == NIL) {
      x = z->left;
      transplant(z, z->left);
    } else {
      y = minimum(z->right);
      yOriginalColor = y->color;
      x = y->right;
      if (y->parent == z)
        x->parent = y;
      else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }

    // no properties are violated if y's color is RED
    if (yOriginalColor == BLACK)
      deleteFixup(x);

    delete z;
  }

  Node *search(int key) const { return search(root, key); }

  int minimum() const { return minimum(root)->key; }

  int maximum() const { return maximum(root)->key; }

  Node *successor(int key) const {
    Node *x = search(root, key);
    if (x == NIL)
      return NIL;
    if (x->right != NIL)
      return minimum(x->right);
    Node *y = x->parent;
    while (y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  Node *predecessor(int key) const {
    Node *x = search(root, key);
    if (x == NIL)
      return NIL;
    if (x->left != NIL)
      return maximum(x->left);
    Node *y = x->parent;
    while (y != nullptr && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }
};