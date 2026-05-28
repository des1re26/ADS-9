// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

// Структура узла дерева
struct TreeNode {
  char value;
  std::vector<TreeNode*> children;

  explicit TreeNode(char v) : value(v) {}
};

// Класс дерева вариантов
class Tree {
 private:
  TreeNode* root;
  std::size_t n;  // количество исходных символов

  // Рекурсивное построение поддерева
  void buildTree(TreeNode* parent, const std::vector<char>& available) {
    for (char c : available) {
      auto* child = new TreeNode(c);
      parent->children.push_back(child);
      // оставшиеся символы (кроме текущего)
      std::vector<char> nextAvail;
      for (char x : available) {
        if (x != c) nextAvail.push_back(x);
      }
      buildTree(child, nextAvail);
    }
  }

  // Рекурсивное удаление
  void deleteTree(TreeNode* node) {
    if (!node) return;
    for (auto* child : node->children) {
      deleteTree(child);
    }
    delete node;
  }

 public:
  explicit Tree(const std::vector<char>& input) : root(new TreeNode('\0')), n(input.size()) {
    if (!input.empty()) {
      std::vector<char> sorted = input;
      std::sort(sorted.begin(), sorted.end());
      buildTree(root, sorted);
    }
  }

  ~Tree() {
    deleteTree(root);
  }

  TreeNode* getRoot() const { return root; }
  std::size_t size() const { return n; }

  // Вспомогательная функция для сбора всех перестановок
  void collectPerms(const TreeNode* node, std::vector<char>& current,
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

// Функции для работы с деревом
std::vector<std::vector<char>> getAllPerms(const Tree& tree);
std::vector<char> getPerm1(const Tree& tree, int num);
std::vector<char> getPerm2(const Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
