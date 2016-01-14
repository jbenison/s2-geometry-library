#include "s2latlng.h"

#include <benchmark/benchmark.h>

static void BM_ToPoint(int iters) {
  S2LatLng ll(S1Angle::E7(0x150bc888), S1Angle::E7(0x5099d63f));
  for (int i = 0; i < iters; i++) {
    ll.ToPoint();
  }
}
BENCHMARK(BM_ToPoint);