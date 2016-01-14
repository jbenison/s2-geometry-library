// MICROBENCHMARKS (and related structures)
#include "s2edgeindex.h"

#include <benchmark/benchmark.h>

// Generates a bunch of random edges and tests each against all others for
// crossings. This is just for benchmarking; there's no correctness testing in
// this function. Set "cutoff_level" negative to apply brute force checking.
static void ComputeCrossings(int num_edges,
                             double edge_length_max,
                             double cap_span_meters,
                             int brute_force) {
    StopBenchmarkTiming();
    vector<S2Edge> all_edges;
    GenerateRandomEarthEdges(edge_length_max, cap_span_meters, num_edges,
                             &all_edges);
    StartBenchmarkTiming();
    if (brute_force) {
        for (vector<S2Edge>::const_iterator it = all_edges.begin();
             it != all_edges.end(); ++it) {
            for (vector<S2Edge>::const_iterator it2 = all_edges.begin();
                 it2 != all_edges.end(); ++it2) {
                S2EdgeUtil::RobustCrossing(it->first, it->second,
                                           it2->first, it2->second);
            }
        }
    } else {
        EdgeVectorIndex index(&all_edges);
        index.ComputeIndex();
        EdgeVectorIndex::Iterator can_it(&index);
        for (vector<S2Edge>::const_iterator it = all_edges.begin();
             it != all_edges.end(); ++it) {
            for (can_it.GetCandidates(it->first, it->second);
                 !can_it.Done(); can_it.Next()) {
                int in = can_it.Index();
                S2EdgeUtil::RobustCrossing(all_edges[in].first, all_edges[in].second,
                                           it->first,
                                           it->second);
            }
        }
    }
}

// "Sparse" tests are those where we expect relatively few segment crossings.
// In general the segment lengths are short (< 300m) and the random segments
// are distributed over caps of radius 5-50km.

static void BM_TestCrossingsSparse(int iters, int num_edges, int brute_force) {
    for (int i = 0; i < iters; ++i) {
        ComputeCrossings(num_edges, 30,  5000,  brute_force);
        ComputeCrossings(num_edges, 100, 5000,  brute_force);
    }
}
BENCHMARK(BM_TestCrossingsSparse)
->ArgPair(10, true)
->ArgPair(10, false)
->ArgPair(50, true)
->ArgPair(50, false)
->ArgPair(100, true)
->ArgPair(100, false)
->ArgPair(300, true)
->ArgPair(300, false)
->ArgPair(600, true)
->ArgPair(600, false)
->ArgPair(1000, true)
->ArgPair(1000, false)
->ArgPair(2000, false)
->ArgPair(5000, false)
->ArgPair(10000, false)
->ArgPair(20000, false)
->ArgPair(50000, false)
->ArgPair(100000, false);

// These benchmarks are used to find the right trade-off between brute force
// and quad tree.

// To compute kQuadTreeInsertionCost
static void BM_QuadTreeInsertionCost(int iters) {
    const int kNumVertices = 1000;
    StopBenchmarkTiming();
    S2Point loop_center = S2Testing::MakePoint("42:107");
    S2Loop* loop = S2Testing::MakeRegularLoop(loop_center, kNumVertices,
                                              7e-3);  // = 5km/6400km
    StartBenchmarkTiming();

    for (int i = 0; i < iters; ++i) {
        S2LoopIndex index(loop);
        index.ComputeIndex();
    }
    delete loop;
}
BENCHMARK(BM_QuadTreeInsertionCost);

// To compute kQuadTreeFindCost
static void BM_QuadTreeFindCost(int iters, int num_vertices) {
    StopBenchmarkTiming();
    S2Point loop_center = S2Testing::MakePoint("42:107");
    S2Loop* loop = S2Testing::MakeRegularLoop(loop_center, num_vertices,
                                              7e-3);  // = 5km/6400km
    S2Point p(S2Testing::MakePoint("42:106.99"));
    S2Point q(S2Testing::MakePoint("42:107.01"));
    S2LoopIndex index(loop);
    index.ComputeIndex();
    EdgeVectorIndex::Iterator can_it(&index);
    StartBenchmarkTiming();

    for (int i = 0; i < iters; ++i) {
        can_it.GetCandidates(p, q);
    }
    delete loop;
}
BENCHMARK(BM_QuadTreeFindCost)
->Arg(10)
->Arg(100)
->Arg(1000)
->Arg(10000);