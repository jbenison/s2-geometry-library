#include "s2regioncoverer.h"
#include "s2testing.h"

#include <benchmark/benchmark.h>

// Two concentric loops don't cross so there is no 'fast exit'
static void BM_Covering(int iters, int max_cells, int num_vertices) {
    S2RegionCoverer coverer;
    coverer.set_max_cells(max_cells);

    for (int i = 0; i < iters; ++i) {
        S2Point center = S2Testing::RandomPoint();
        S2Loop* loop = S2Testing::MakeRegularLoop(center, num_vertices, 0.005);

        StartBenchmarkTiming();
        vector<S2CellId> covering;
        coverer.GetCovering(*loop, &covering);
        StopBenchmarkTiming();

        delete loop;
    }
}
BENCHMARK(BM_Covering)->RangePair(8, 1024, 8, 1<<17);