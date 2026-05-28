// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <cstddef>

struct TreeNode {
  char value;
  std::vector<TreeNode*> children;

  explicit TreeNode(char v) : value(v) {}
};

class Tree {
 private:
  TreeNode* root;
  std::size_t n;  // исходное количество символов

  void deleteTree(TreeNode* node);
  void buildTree(TreeNode* parent, std::vector<char> available);
  void collectPerms(const TreeNode* node, std::vector<char>& current,
                    std::vector<std::vector<char>>& result) const;

 public:
  explicit Tree(const std::vector<char>& input);
  ~Tree();

  TreeNode* getRoot() const { return root; }
  std::size_t size() const { return n; }
};

// Функции для работы с деревом
std::vector<std::vector<char>> getAllPerms(const Tree& tree);
std::vector<char> getPerm1(const Tree& tree, int num);
std::vector<char> getPerm2(const Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
