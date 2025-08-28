#include <iostream>
#include <cstdint>
#include <device_launch_parameters.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

const static uint64_t PRINT_VALUE = (1ULL << 25) - 1;

static std::array<cpp_int, 64> power_three;
static std::array<cpp_int, 64> sum_three;

void init_tables() {
    cpp_int p = 1;
    cpp_int s = 0;
    for (int i = 0; i < 64; ++i) {
        power_three[i] = p;
        sum_three[i] = s;
        p *= 3;
        s = (p - 1) / 2;
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