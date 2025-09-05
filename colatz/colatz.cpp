#include <iostream>
#include <cstdint>
#include <device_launch_parameters.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

constexpr static uint64_t PRINT_VALUE = (1ULL << 31) - 1;



constexpr static uint64_t K = 14; // set this up depending on your cpu cache size (prob depending on L1 and L2 cache)
constexpr static uint64_t SIZE = 1 << K;

static std::array<uint8_t, SIZE> c_table;
static std::array<uint64_t, SIZE> d_table;

static std::array<uint64_t, K> power_three;

void init_tables() {
    for (int b = 0; b < SIZE; b++) {
        uint8_t c = 0;
        uint64_t x = b;
        for (uint16_t step = 0; step < K; step++) {
            if (x & 1) {
                x = (3 * x + 1) >> 1;
                c++;
            }
            else {
                x >>= 1;
            }
        }
        c_table[b] = c;
        d_table[b] = x;
    }
    uint64_t p = 1;
    for (int i = 0; i < 64; ++i) {
        power_three[i] = p;
        p *= 3;
    }
}

void collatzSequence(uint64_t start_val) {
    uint64_t i = start_val;
    while (i >= start_val) {
        uint64_t a = i >> K;
        int b = static_cast<int>(i & (SIZE - 1));

        i = a * power_three[c_table[b]] + d_table[b];
    }
}

int main() {
    uint64_t start = 3;
    init_tables();
    while (true) {
        collatzSequence(start);
        start += 4;
        if ((start & PRINT_VALUE) == 3) std::cout << start << std::endl;
    }
    return 0;
}

// latest 61499636711427
// YO LETS GO billion throughput in a second











/*

old code, eh it was good one, bye bye bro

static std::array<cpp_int, 64> power_three;
static std::array<cpp_int, 64> sum_three;

void init_tables() {
    cpp_int p = 1;
    cpp_int s = 0;
    for (int i = 0; i < 64; ++i) {
        power_three[i] = p;
        sum_three[i] = p >> 1;
        p *= 3;
    }
}

void collatzSequence(uint64_t start_val) {
    cpp_int i = start_val;
	while (i >= start_val) {
        uint64_t low = static_cast<uint64_t>(i);
        uint64_t n = std::countr_one(low);
		i >>= n + 1;
        i = i * power_three[n] + sum_three[n];
        low = static_cast<uint64_t>(i);
        i >>= std::countr_zero(low);
    }
}

int main() {
    uint64_t start = 3;
	init_tables();
    while (true) {
        collatzSequence(start);
        start += 4;
        if ((start & PRINT_VALUE) == 3) std::cout << start << std::endl;
    }
    return 0;
}
// latest 8329015328771
// latest 9687298736129
// latest 10475962105857
*/