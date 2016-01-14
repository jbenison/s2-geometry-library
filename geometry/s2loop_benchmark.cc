#include "s2loop.h"

#include <benchmark/benchmark.h>

static void BM_ContainsOrCrosses(int iters, int num_vertices) {
  StopBenchmarkTiming();
  S2Loop* p1 = S2Testing::MakeRegularLoop(S2::Origin(), num_vertices, 0.005);
  S2Loop* p2 = S2Testing::MakeRegularLoop(
      (S2::Origin() + S2Point(0, 0, 0.003)).Normalize(),
      num_vertices,
      0.005);
  StartBenchmarkTiming();
  for (int i = 0; i < iters; ++i) {
    p1->ContainsOrCrosses(p2);
  }
  StopBenchmarkTiming();
  delete p1;
  delete p2;
}
BENCHMARK_RANGE(BM_ContainsOrCrosses, 8, 8192);

static void BM_IsValid(int iters, int num_vertices) {
  StopBenchmarkTiming();
  S2Loop* l = S2Testing::MakeRegularLoop(S2::Origin(), num_vertices, 0.001);
  StartBenchmarkTiming();
  int r = 0;
  for (int i = 0; i < iters; ++i) {
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

static void BM_ContainsQuery(int iters, int num_vertices) {
  StopBenchmarkTiming();
  S2Point loop_center = S2Testing::MakePoint("42:10");
  S2Loop* loop = S2Testing::MakeRegularLoop(loop_center,
                                            num_vertices,
                                            7e-3);  // = 5km/6400km
  StartBenchmarkTiming();
  int count = 0;
  for (int i = 0; i < iters; ++i) {
    count += 1 + loop->Contains(loop_center);
  }
  CHECK_LE(0, count);
  delete loop;
}
BENCHMARK_RANGE(BM_ContainsQuery, 4, 1 << 16);