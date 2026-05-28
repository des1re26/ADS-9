// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

struct TreeNode {
  char value;
  std::vector<TreeNode*> children;

  explicit TreeNode(char v) : value(v) {}
};

std::size_t factorial(std::size_t m);

class PMTree {
 private:
  TreeNode* root;
  std::size_t n;

  void buildTree(TreeNode* parent, const std::vector<char>& available) {
    for (char c : available) {
      auto* child = new TreeNode(c);
      parent->children.push_back(child);
      std::vector<char> nextAvail;
      for (char x : available) {
        if (x != c) nextAvail.push_back(x);
      }
      buildTree(child, nextAvail);
    }
  }

  void deleteTree(TreeNode* node) {
    if (!node) return;
    for (auto* child : node->children) {
      deleteTree(child);
    }
    delete node;
  }

 public:
  explicit PMTree(const std::vector<char>& input)
      : root(new TreeNode('\0')), n(input.size()) {
    if (!input.empty()) {
      std::vector<char> sorted = input;
      std::sort(sorted.begin(), sorted.end());
      buildTree(root, sorted);
    }
  }

  ~PMTree() { deleteTree(root); }

  TreeNode* getRoot() const { return root; }
  std::size_t size() const { return n; }

  void collectPerms(const TreeNode* node,
                    std::vector<char>& current,
                    std::vector<std::vector<char>>& result) const {
    if (node->children.empty()) {
      result.push_back(current);
      return;
    }
    for (const auto* child : node->children) {
      current.push_back(child->value);
      collectPerms(child, current, result);
      current.pop_back();
    }
  }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
