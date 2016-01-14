#include "s2loop.h"
#include "s2testing.h"

#include <benchmark/benchmark.h>

static void BM_ContainsOrCrosses(benchmark::State& state) {
  S2Loop* p1 = S2Testing::MakeRegularLoop(S2::Origin(), state.range_x(), 0.005);
  S2Loop* p2 = S2Testing::MakeRegularLoop(
      (S2::Origin() + S2Point(0, 0, 0.003)).Normalize(),
      state.range_x(),
      0.005);
  while (state.KeepRunning()) {
    p1->ContainsOrCrosses(p2);
  }
  delete p1;
  delete p2;
}
BENCHMARK_RANGE(BM_ContainsOrCrosses, 8, 8192);

static void BM_IsValid(benchmark::State& state) {
  S2Loop* l = S2Testing::MakeRegularLoop(S2::Origin(), state.range_x(), 0.001);
  int r = 0;
  while (state.KeepRunning()) {
    r += l->IsValid();
  }
  CHECK(r != INT_MAX);
  delete l;
}
BENCHMARK(BM_IsValid)
->Arg(32)
->Arg(64)
->Arg(128)
->Arg(256)
->Arg(512)
->Arg(4096)
->Arg(32768);

static void BM_ContainsQuery(benchmark::State& state) {
  S2Point loop_center = S2Testing::MakePoint("42:10");
  S2Loop* loop = S2Testing::MakeRegularLoop(loop_center,
                                            state.range_x(),
                                            7e-3);  // = 5km/6400km
  int count = 0;
  while (state.KeepRunning()) {
    count += 1 + loop->Contains(loop_center);
  }
  CHECK_LE(0, count);
  delete loop;
}
BENCHMARK_RANGE(BM_ContainsQuery, 4, 1 << 16);

BENCHMARK_MAIN()