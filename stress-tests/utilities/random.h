#pragma once
#include <cstdint>
#include <cassert>

// returns random int in [0, hi), like Python's random.randrange
int randRange(int hi) {
    return rand() % hi;
}

bool randBool() {
	return !!(rand() & 128);
}

// returns random int in [lo, hi), like Python's random.randrange
int randRange(int lo, int hi) {
    return lo + randRange(hi - lo);
}

// returns random int in [0, 2^64)
uint64_t randU64() {
    uint64_t a = rand() & 0xffffff;
    uint64_t b = rand() & 0xffffff;
    uint64_t c = rand() & 0xffff;
    return a << 40 | b << 16 | c;
}

uint64_t randRange(uint64_t hi) {
    return randU64() % hi;
}

uint64_t randRange(uint64_t lo, uint64_t hi) {
    return lo + randRange(hi - lo);
}

int64_t randRange(int64_t hi) {
    assert(hi > 0);
    return (int64_t) randRange((uint64_t) hi);
}

int64_t randRange(int64_t lo, int64_t hi) {
    return lo + randRange(hi - lo);
}

// returns random int in [0, hi], like Python's random.randint
int randIncl(int hi) {
    return randRange(hi + 1);
}

// returns random int in [lo, hi], like Python's random.randint
int randIncl(int lo, int hi) {
    return randRange(lo, hi + 1);
}

int64_t randIncl(int64_t hi) {
    return randRange(hi + 1);
}

int64_t randIncl(int64_t lo, int64_t hi) {
    return randRange(lo, hi + 1);
}

// returns uniformly random double in [lo, hi)
double randDouble(double lo, double hi) {
    static mt19937_64 rng(time(0));
    std::uniform_real_distribution<> dis(lo, hi);
    return dis(rng);
}

// int -> double based on IEEE 754 bitpattern
double bitPatternToDouble(uint64_t x) {
    union {
        double d;
        uint64_t i;
    } u;
    u.i = x;
    return u.d;
}

// double -> int based on IEEE 754 bitpattern
uint64_t doubleToBitPattern(double x) {
    union {
        double d;
        uint64_t i;
    } u;
    u.d = x;
    return u.i;
}

// random double
double randDoubleUniformBitPattern() {
    return bitPatternToDouble(randU64());
}

// random double in [lo, hi), with any bit pattern being equally likely
double randDoubleUniformBitPattern(double lo, double hi) {
    return bitPatternToDouble(randRange(doubleToBitPattern(lo), doubleToBitPattern(hi)));
}

// add ~y ulps (units of last precision) to x, similar to calling next_after y times
double addUlps(double x, int64_t y) {
    if (x == 0 && y < 0) {
        return -addUlps(-x, -y);
    }
    return bitPatternToDouble(doubleToBitPattern(x) + y);
}

// random int in [-lim, lim], perturbed by a few ulps
double randNearIntUlps(int lim, int64_t ulps = 5) {
    return addUlps(randIncl(-lim, lim), randIncl(-ulps, ulps));
}

// random int in [-lim, lim], perturbed by a random double in [-eps, eps]
double randNearIntEps(int lim, double eps) {
    return randIncl(-lim, lim) + randDouble(-eps, eps);
}

// like random_shuffle but uses rand() as RNG source
template<class T>
void shuffle_vec(T& vec) {
    random_shuffle(begin(vec), end(vec), [](int lim) { return rand() % lim; });
}
