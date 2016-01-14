#include "s2edgeutil.h"
#include "s2testing.h"

#include <benchmark/benchmark.h>

typedef bool CrossingFunction(S2Point const &, S2Point const &,
                              S2Point const &, S2Point const &);

// Reusable function for passing crossing functions to benchmark.
void BenchmarkCrossing(CrossingFunction crossing, benchmark::State &state) {
  // We want to avoid cache effects, so kNumPoints should be small enough so
  // that the points can be in L1 cache.  sizeof(S2Point) == 24, so 400 will
  // only take ~9KiB of 64KiB L1 cache.
  static const int kNumPoints = 400;
  vector<S2Point> p(kNumPoints);
  for (int i = 0; i < kNumPoints; ++i)
    p[i] = S2Testing::RandomPoint();

  int num_crossings = 0;
  while (state.KeepRunning()) {
    state.PauseTiming();
    const S2Point &a = p[(state.iterations() + 0) % kNumPoints];
    const S2Point &b = p[(state.iterations() + 1) % kNumPoints];
    const S2Point &c = p[(state.iterations() + 2) % kNumPoints];
    const S2Point &d = p[(state.iterations() + 3) % kNumPoints];

    state.ResumeTiming();
    if (crossing(a, b, c, d))
      ++num_crossings;
  }
  VLOG(5) << "Fraction crossing = " << 1.0 * num_crossings / state.iterations();
  VLOG(5) << "iters: " << state.iterations();
}

void BM_EdgeOrVertexCrossing(benchmark::State &state) {
  BenchmarkCrossing(&S2EdgeUtil::EdgeOrVertexCrossing, state);
}
BENCHMARK(BM_EdgeOrVertexCrossing);

bool RobustCrossingBool(S2Point const &a, S2Point const &b,
                        S2Point const &c, S2Point const &d) {
  return S2EdgeUtil::RobustCrossing(a, b, c, d) > 0;
}

void BM_RobustCrossing(benchmark::State &state) {
  BenchmarkCrossing(&RobustCrossingBool, state);
}
BENCHMARK(BM_RobustCrossing);

// Copied from BenchmarkCrossing() above.
static void BM_RobustCrosserEdgesCross(benchmark::State &state) {
  static const int kNumPoints = 400;
  vector<S2Point> p(kNumPoints);
  for (int i = 0; i < kNumPoints; ++i) p[i] = S2Testing::RandomPoint();
  // 1/4th of the points will cross ab.
  const S2Point &a = S2Testing::RandomPoint();
  const S2Point &b = (-a + S2Point(0.1, 0.1, 0.1)).Normalize();

  S2EdgeUtil::EdgeCrosser crosser(&a, &b, &p[0]);
  int num_crossings = 0;
  while (state.KeepRunning()) {
    state.PauseTiming();
    const S2Point &d = p[state.iterations() % kNumPoints];
    state.ResumeTiming();
    if (crosser.RobustCrossing(&d) > 0)
      ++num_crossings;
  }
  VLOG(5) << "Fraction crossing = " << 1.0 * num_crossings / state.iterations();
  VLOG(5) << "num_crossings = " << num_crossings;
}
BENCHMARK(BM_RobustCrosserEdgesCross);

BENCHMARK_MAIN()