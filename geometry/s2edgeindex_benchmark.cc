// MICROBENCHMARKS (and related structures)
#include "s2edgeindex.h"

#include <benchmark/benchmark.h>

#include "s2testing.h"
#include "s2loop.h"
#include "s2cap.h"

// @TODO: Eliminate code duplication. This typdef is also used in test.
typedef pair<S2Point, S2Point> S2Edge;

// @TODO: Eliminate code duplication. This const is also used in test.
static const double kEarthRadiusMeters = 6371000;

// Generates a random edge whose center is in the given cap.
// @TODO: Eliminate code duplication. This function is also used in test.
static S2Edge RandomEdgeCrossingCap(double max_length_meters,
                                    const S2Cap& cap) {
    // Pick the edge center at random.
    S2Point edge_center = S2Testing::SamplePoint(cap);
    // Pick two random points in a suitably sized cap about the edge center.
    S2Cap edge_cap = S2Cap::FromAxisAngle(
        edge_center,
        S1Angle::Radians(max_length_meters / kEarthRadiusMeters / 2));
    S2Point p1 = S2Testing::SamplePoint(edge_cap);
    S2Point p2 = S2Testing::SamplePoint(edge_cap);
    return S2Edge(p1, p2);
}

// Generates "num_edges" random edges, of length at most
// "edge_length_meters_max" and each of whose center is in a randomly located
// cap with radius "cap_span_meters", and puts results into "edges".
// @TODO: Eliminate code duplication. This function is also used in test.
static void GenerateRandomEarthEdges(double edge_length_meters_max,
                                     double cap_span_meters,
                                     int num_edges,
                                     vector<S2Edge>* edges) {
    S2Cap cap = S2Cap::FromAxisAngle(
        S2Testing::RandomPoint(),
        S1Angle::Radians(cap_span_meters / kEarthRadiusMeters));
    for (int i = 0; i < num_edges; ++i) {
        edges->push_back(RandomEdgeCrossingCap(edge_length_meters_max, cap));
    }
}

// @TODO: Eliminate code duplication. This class is also used in test.
class EdgeVectorIndex: public S2EdgeIndex {
public:
  explicit EdgeVectorIndex(vector<S2Edge> const* edges):
      edges_(edges) {}

  virtual int num_edges() const { return edges_->size(); }
  virtual S2Point const* edge_from(int index) const {
      return &((*edges_)[index].first);
  }
  virtual S2Point const* edge_to(int index) const {
      return &((*edges_)[index].second);
  }
private:
  vector<S2Edge> const* edges_;
};

// Generates a bunch of random edges and tests each against all others for
// crossings. This is just for benchmarking; there's no correctness testing in
// this function. Set "cutoff_level" negative to apply brute force checking.
static void ComputeCrossings(benchmark::State &state,
                             double edge_length_max,
                             double cap_span_meters) {
    state.PauseTiming();
    vector<S2Edge> all_edges;
    GenerateRandomEarthEdges(edge_length_max, cap_span_meters, state.range_x(),
                             &all_edges);
    state.ResumeTiming();
    if (state.range_y()) {
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

//static void BM_TestCrossingsSparse(int iters, int num_edges, int brute_force) {
static void BM_TestCrossingsSparse(benchmark::State &state) {
    while (state.KeepRunning()) {
        ComputeCrossings(state, 30,  5000);
        ComputeCrossings(state, 100, 5000);
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
static void BM_QuadTreeInsertionCost(benchmark::State &state) {
    const int kNumVertices = 1000;
    S2Point loop_center = S2Testing::MakePoint("42:107");
    S2Loop* loop = S2Testing::MakeRegularLoop(loop_center, kNumVertices,
                                              7e-3);  // = 5km/6400km
    while (state.KeepRunning()) {
        S2LoopIndex index(loop);
        index.ComputeIndex();
    }
    delete loop;
}
BENCHMARK(BM_QuadTreeInsertionCost);

// To compute kQuadTreeFindCost
static void BM_QuadTreeFindCost(benchmark::State &state) {
    S2Point loop_center = S2Testing::MakePoint("42:107");
    S2Loop* loop = S2Testing::MakeRegularLoop(loop_center, state.range_x(),
                                              7e-3);  // = 5km/6400km
    S2Point p(S2Testing::MakePoint("42:106.99"));
    S2Point q(S2Testing::MakePoint("42:107.01"));
    S2LoopIndex index(loop);
    index.ComputeIndex();
    EdgeVectorIndex::Iterator can_it(&index);

    while (state.KeepRunning()) {
        can_it.GetCandidates(p, q);
    }
    delete loop;
}
BENCHMARK(BM_QuadTreeFindCost)
->Arg(10)
->Arg(100)
->Arg(1000)
->Arg(10000);

BENCHMARK_MAIN()