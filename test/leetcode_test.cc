#include "leetcode.h"

#include <cstdio>

int main() {
    // auto start = chrono::system_clock::now();
    leetcode::Solution* solution = new leetcode::Solution();

    int64_t out = solution->intPartition();
    printf("%lld\n", out);

    // auto end = chrono::system_clock::now();
    // auto duration = chrono::duration<double>(end - start);
    // printf("%lf\n", duration.count());
}