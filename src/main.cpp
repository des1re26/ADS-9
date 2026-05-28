// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <string>

#include "tree.h"

int main() {
    // Размеры алфавита для тестирования (можно менять)
    std::vector<std::size_t> sizes = {1, 2, 3, 4, 5, 6, 7, 8};
    std::ofstream csv("experiment.csv");
    csv << "n,getAllPerms,getPerm1,getPerm2\n";

    for (auto n : sizes) {
        std::vector<char> alphabet;
        for (std::size_t i = 0; i < n; ++i) {
            alphabet.push_back(static_cast<char>('a' + i));
        }
        Tree tree(alphabet);
        int total = static_cast<int>(factorial(n));

        // 1. getAllPerms
        auto start = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double tAll = std::chrono::duration<double, std::milli>(end - start).count();

        // 2. getPerm1 (медленный)
        int num = 1 + rand() % total;
        start = std::chrono::high_resolution_clock::now();
        auto p1 = getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t1 = std::chrono::duration<double, std::milli>(end - start).count();

        // 3. getPerm2 (быстрый)
        start = std::chrono::high_resolution_clock::now();
        auto p2 = getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t2 = std::chrono::duration<double, std::milli>(end - start).count();

        csv << n << "," << tAll << "," << t1 << "," << t2 << "\n";
    }

    csv.close();
    std::cout << "Data saved to experiment.csv\n";
    return 0;
}
