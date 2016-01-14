#include "s2regioncoverer.h"
#include "s2loop.h"
#include "s2testing.h"

#include <benchmark/benchmark.h>

// Two concentric loops don't cross so there is no 'fast exit'
static void BM_Covering(benchmark::State &state) {
  S2RegionCoverer coverer;
  coverer.set_max_cells(state.range_x());

  while (state.KeepRunning()) {
    state.PauseTiming();
    S2Point center = S2Testing::RandomPoint();
    S2Loop* loop = S2Testing::MakeRegularLoop(center, state.range_y(), 0.005);

    state.ResumeTiming();
    vector<S2CellId> covering;
    coverer.GetCovering(*loop, &covering);

    delete loop;
  }
}
BENCHMARK(BM_Covering)->RangePair(8, 1024, 8, 1 << 17);

BENCHMARK_MAIN()