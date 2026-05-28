// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

#include "tree.h"

int main() {
  std::vector<std::size_t> sizes = {1, 2, 3, 4, 5, 6, 7, 8};
  std::ofstream csv("experiment.csv");
  csv << "n,getAllPerms,getPerm1,getPerm2\n";

  std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

  for (auto n : sizes) {
    std::vector<char> alphabet;
    for (std::size_t i = 0; i < n; ++i) {
      alphabet.push_back(static_cast<char>('a' + i));
    }
    PMTree tree(alphabet);
    int total = static_cast<int>(factorial(n));

    auto start = std::chrono::high_resolution_clock::now();
    auto all = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double tAll =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::uniform_int_distribution<int> dist(1, total);
    int num = dist(rng);

    start = std::chrono::high_resolution_clock::now();
    auto p1 = getPerm1(tree, num);
    end = std::chrono::high_resolution_clock::now();
    double t1 =
        std::chrono::duration<double, std::milli>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto p2 = getPerm2(tree, num);
    end = std::chrono::high_resolution_clock::now();
    double t2 =
        std::chrono::duration<double, std::milli>(end - start).count();

    csv << n << "," << tAll << "," << t1 << "," << t2 << "\n";
  }

  csv.close();
  std::cout << "Data saved to experiment.csv\n";
  return 0;
}
