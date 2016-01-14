#include "s2latlng.h"

#include <benchmark/benchmark.h>

static void BM_ToPoint(benchmark::State& state) {
  S2LatLng ll(S1Angle::E7(0x150bc888), S1Angle::E7(0x5099d63f));
  while (state.KeepRunning())
    ll.ToPoint();
}
BENCHMARK(BM_ToPoint);

BENCHMARK_MAIN();