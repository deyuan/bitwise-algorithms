/**
 * @file kogge_stone_sub.cpp
 * @brief Implementation of the Kogge-Stone adder algorithm.
 * 
 * This file contains the implementation of the Kogge-Stone adder,
 * a parallel prefix adder used for fast binary addition.
 * 
 * @author Deyuan Guo, Yingming Ma
 * @date 09/03/2025
 */

#include <random>
#include <cstdio>
#include <ctime>

int
kogge_stone_sub(int a, int b)
{
    int nb = ~b; // for sub

    int G0 = a & nb; // Generate bits
    int P0 = a ^ nb; // Propagate bits

    G0 |= (P0 & 1);

    int G1 = G0 | (P0 & (G0 << 1));
    int P1 = P0 & (P0 << 1);

    int G2 = G1 | (P1 & (G1 << 2));
    int P2 = P1 & (P1 << 2);

    int G3 = G2 | (P2 & (G2 << 4));
    int P3 = P2 & (P2 << 4);

    int G4 = G3 | (P3 & (G3 << 8));
    int P4 = P3 & (P3 << 8);

    int G5 = G4 | (P4 & (G4 << 16));

    int sum = P0 ^ (G5 << 1) ^ 1;
    return sum;
}

int main()
{
    int seed = std::time(nullptr);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    int numElements = 32;
    for (int i = 0; i < numElements; ++i) {
        int a = dist(gen);
        int b = dist(gen);
        int result = kogge_stone_sub(a, b);
        int expected = a - b;
        std::printf("a: 0x%08x, b: 0x%08x, result: 0x%08x, expected: 0x%08x, %s\n",
            a, b, result, expected, (result == expected) ? "PASS" : "FAIL");
    }
    return 0;
}

