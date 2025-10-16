#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>

static void BM_SortVector(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v(state.range(0));
        std::generate(v.begin(), v.end(), std::rand);
        std::sort(v.begin(), v.end());
    }
}

// Register benchmark with input size 1<<10 (1024)
BENCHMARK(BM_SortVector)->Arg(1 << 10);

// Run benchmarks
BENCHMARK_MAIN();
