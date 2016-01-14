#include "s2polygon.h"

#include <benchmark/benchmark.h>


static void BM_S2Decoding(int iters, int num_vertices_per_loop_for_bm) {
  StopBenchmarkTiming();
  string encoded = GenerateInputForBenchmark(num_vertices_per_loop_for_bm);
  StartBenchmarkTiming();
  for (int i = 0; i < iters; ++i) {
    Decoder decoder(encoded.data(), encoded.size());
    S2Polygon decoded_polygon;
    decoded_polygon.Decode(&decoder);
  }
}
BENCHMARK_RANGE(BM_S2Decoding, 8, 131072);

static void BM_S2DecodingWithinScope(int iters,
                                     int num_vertices_per_loop_for_bm) {
  StopBenchmarkTiming();
  string encoded = GenerateInputForBenchmark(num_vertices_per_loop_for_bm);
  StartBenchmarkTiming();
  for (int i = 0; i < iters; ++i) {
    Decoder decoder(encoded.data(), encoded.size());
    S2Polygon decoded_polygon;
    decoded_polygon.DecodeWithinScope(&decoder);
  }
}
BENCHMARK_RANGE(BM_S2DecodingWithinScope, 8, 131072);


void ConcentricLoops(S2Point center,
                     int num_loops,
                     int num_vertices_per_loop,
                     S2Polygon* poly) {
  Matrix3x3_d m;
  S2::GetFrame(center, &m);
  vector<S2Loop*> loops;
  for (int li = 0; li < num_loops; ++li) {
    vector<S2Point> vertices;
    double radius = 0.005 * (li + 1) / num_loops;
    double radian_step = 2 * M_PI / num_vertices_per_loop;
    for (int vi = 0; vi < num_vertices_per_loop; ++vi) {
      double angle = vi * radian_step;
      S2Point p(radius * cos(angle), radius * sin(angle), 1);
      vertices.push_back(S2::FromFrame(m, p.Normalize()));
    }
    loops.push_back(new S2Loop(vertices));
  }
  poly->Init(&loops);
}

static void UnionOfPolygons(int iters,
                            int num_vertices_per_loop,
                            double second_polygon_offset) {
  for (int i = 0; i < iters; ++i) {
    StopBenchmarkTiming();
    S2Polygon p1, p2;
    S2Point center = S2Testing::RandomPoint();
    ConcentricLoops(center,
                    FLAGS_num_loops_per_polygon_for_bm,
                    num_vertices_per_loop,
                    &p1);
    ConcentricLoops(
        (center + S2Point(second_polygon_offset,
                          second_polygon_offset,
                          second_polygon_offset)).Normalize(),
        FLAGS_num_loops_per_polygon_for_bm,
        num_vertices_per_loop,
        &p2);
    StartBenchmarkTiming();
    S2Polygon p_result;
    p_result.InitToUnion(&p1, &p2);
  }
}

static void BM_DeepPolygonUnion(int iters, int num_vertices_per_loop) {
  UnionOfPolygons(iters, num_vertices_per_loop, 0.000001);
}
BENCHMARK(BM_DeepPolygonUnion)
->Arg(8)
->Arg(64)
->Arg(128)
->Arg(256)
->Arg(512)
->Arg(1024)
->Arg(4096)
->Arg(8192);

static void BM_ShallowPolygonUnion(int iters, int num_vertices_per_loop) {
  UnionOfPolygons(iters, num_vertices_per_loop, 0.004);
}
BENCHMARK(BM_ShallowPolygonUnion)
->Arg(8)
->Arg(64)
->Arg(128)
->Arg(256)
->Arg(512)
->Arg(1024)
->Arg(4096)
->Arg(8192);

static void BM_DisjointPolygonUnion(int iters, int num_vertices_per_loop) {
  UnionOfPolygons(iters, num_vertices_per_loop, 0.3);
}
BENCHMARK(BM_DisjointPolygonUnion)
->Arg(8)
->Arg(64)
->Arg(128)
->Arg(256)
->Arg(512)
->Arg(1024)
->Arg(4096)
->Arg(8192);