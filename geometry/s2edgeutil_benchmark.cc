#include "s2edgeutil.h"

#include <benchmark/benchmark.h>

typedef bool CrossingFunction(S2Point const&, S2Point const&,
                              S2Point const&, S2Point const&);
void BenchmarkCrossing(CrossingFunction crossing, int iters) {
  StopBenchmarkTiming();
  // We want to avoid cache effects, so kNumPoints should be small enough so
  // that the points can be in L1 cache.  sizeof(S2Point) == 24, so 400 will
  // only take ~9KiB of 64KiB L1 cache.
  static const int kNumPoints = 400;
  vector<S2Point> p(kNumPoints);
  for (int i = 0; i < kNumPoints; ++i)
    p[i] = S2Testing::RandomPoint();
  StartBenchmarkTiming();

  int num_crossings = 0;
  for (int i = 0; i < iters; ++i) {
    const S2Point& a = p[(i + 0) % kNumPoints];
    const S2Point& b = p[(i + 1) % kNumPoints];
    const S2Point& c = p[(i + 2) % kNumPoints];
    const S2Point& d = p[(i + 3) % kNumPoints];

    if (crossing(a, b, c, d))
      ++num_crossings;
  }
  VLOG(5) << "Fraction crossing = " << 1.0 * num_crossings / iters;
  VLOG(5) << "iters: " << iters;
}

void BM_EdgeOrVertexCrossing(int iters) {
  BenchmarkCrossing(&S2EdgeUtil::EdgeOrVertexCrossing, iters);
}
BENCHMARK(BM_EdgeOrVertexCrossing);

bool RobustCrossingBool(S2Point const& a, S2Point const& b,
                        S2Point const& c, S2Point const& d) {
  return S2EdgeUtil::RobustCrossing(a, b, c, d) > 0;
}
void BM_RobustCrossing(int iters) {
  BenchmarkCrossing(&RobustCrossingBool, iters);
}
BENCHMARK(BM_RobustCrossing);

static void BM_RobustCrosserEdgesCross(int iters) {
  // Copied from BenchmarkCrossing() above.
  StopBenchmarkTiming();
  static const int kNumPoints = 400;
  vector<S2Point> p(kNumPoints);
  for (int i = 0; i < kNumPoints; ++i) p[i] = S2Testing::RandomPoint();
  // 1/4th of the points will cross ab.
  const S2Point& a = S2Testing::RandomPoint();
  const S2Point& b = (-a + S2Point(0.1, 0.1, 0.1)).Normalize();
  StartBenchmarkTiming();

  S2EdgeUtil::EdgeCrosser crosser(&a, &b, &p[0]);
  int num_crossings = 0;
  for (int i = 0; i < iters; ++i) {
    const S2Point& d = p[i % kNumPoints];

    if (crosser.RobustCrossing(&d) > 0)
      ++num_crossings;
  }
  VLOG(5) << "Fraction crossing = " << 1.0 * num_crossings / iters;
  VLOG(5) << "num_crossings = " << num_crossings;
}
BENCHMARK(BM_RobustCrosserEdgesCross);