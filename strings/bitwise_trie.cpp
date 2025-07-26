#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
  TrieNode *bit[2]; // 0 and 1
  int count;        // How many numbers pass through this node

  TrieNode() {
    bit[0] = nullptr;
    bit[1] = nullptr;
    count = 0;
  }
};

class BitwiseTrie {
  TrieNode *root;
  const int MAX_BITS = 31; // for 32-bit integers

public:
  BitwiseTrie() { root = new TrieNode(); }

  void insert(int num) {
    TrieNode *node = root;
    for (int i = MAX_BITS; i >= 0; i--) {
      int curBit = (num >> i) & 1;
      if (!node->bit[curBit])
        node->bit[curBit] = new TrieNode();
      node = node->bit[curBit];
      node->count++;
    }
  }

  bool search(int num) {
    TrieNode *node = root;
    for (int i = MAX_BITS; i >= 0; i--) {
      int curBit = (num >> i) & 1;
      if (!node->bit[curBit] || node->bit[curBit]->count == 0)
        return false;
      node = node->bit[curBit];
    }
    return true;
  }

  void erase(int num) {
    if (!search(num))
      return; // number not present

    TrieNode *node = root;
    for (int i = MAX_BITS; i >= 0; i--) {
      int curBit = (num >> i) & 1;
      TrieNode *next = node->bit[curBit];
      next->count--;
      if (next->count == 0) { // safe to delete the subtree
        deleteSubtree(next);
        node->bit[curBit] = nullptr;
        return; // No need to go deeper
      }
      node = next;
    }
  }

  int getMaxXor(int num) {
    TrieNode *node = root;
    int maxXor = 0;
    for (int i = MAX_BITS; i >= 0; i--) {
      int curBit = (num >> i) & 1;
      int oppositeBit = 1 - curBit;
      if (node->bit[oppositeBit] && node->bit[oppositeBit]->count > 0) {
        maxXor |= (1 << i);
        node = node->bit[oppositeBit];
      } else if (node->bit[curBit] && node->bit[curBit]->count > 0) {
        node = node->bit[curBit];
      } else {
        break; // No further path
      }
    }
    return maxXor;
  }

private:
  void deleteSubtree(TrieNode *node) {
    if (!node)
      return;
    deleteSubtree(node->bit[0]);
    deleteSubtree(node->bit[1]);
    delete node;
  }
};

int main() {
  BitwiseTrie trie;
  vector<int> nums = {3, 10, 5, 25, 2, 8};

  for (int n : nums)
    trie.insert(n);

  cout << trie.search(10) << "\n"; // 1 (true)
  trie.erase(10);
  cout << trie.search(10) << "\n"; // 0 (false)

  cout << trie.getMaxXor(5) << "\n"; // Max XOR with 5
  return 0;
}