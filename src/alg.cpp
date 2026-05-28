// Copyright 2022 NNTU-CS
#include <vector>
#include <cstddef>
#include "tree.h"

std::size_t factorial(std::size_t m) {
  std::size_t f = 1;
  for (std::size_t i = 2; i <= m; ++i) f *= i;
  return f;
}

std::vector<std::vector<char>> getAllPerms(const Tree& tree) {
  std::vector<std::vector<char>> result;
  if (tree.getRoot() == nullptr) return result;
  std::vector<char> current;
  tree.collectPerms(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(const Tree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || static_cast<std::size_t>(num) > all.size()) {
    return {};
  }
  return all[num - 1];
}

std::vector<char> getPerm2(const Tree& tree, int num) {
  std::size_t n = tree.size();
  if (num < 1 || static_cast<std::size_t>(num) > factorial(n)) {
    return {};
  }
  std::vector<char> result;
  const TreeNode* cur = tree.getRoot();
  int k = num - 1;
  for (std::size_t rem = n; rem > 0; --rem) {
    std::size_t fact = factorial(rem - 1);
    std::size_t idx = static_cast<std::size_t>(k) / fact;
    if (idx >= cur->children.size()) return {};
    const TreeNode* next = cur->children[idx];
    result.push_back(next->value);
    k = static_cast<int>(static_cast<std::size_t>(k) % fact);
    cur = next;
  }
  return result;
}
