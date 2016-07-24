/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * Source: My head
 * Description: Basic matrix operations.
 * Usage: Matrix<int> A(3,3);
 *  A.d = {1,2,3,4,5,6,7,8,9};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

template <class T> struct Matrix {
	typedef Matrix M;
	typedef const M& R;
	int r, c;
	vector<T> d;
	Matrix(int _r, int _c) : r(_r), c(_c), d(r*c) {}
	Matrix() : r(0), c(0) {}
	Matrix(int _r, int _c, T val) : r(_r), c(_c), d(r*c, val) {}
	T& operator()(int row, int col) { return d[row*c + col]; }
	M operator*(R m) const {
		assert(c == m.r);
		M a(r, m.c);
		rep(i,0,r) rep(j,0,m.c) {
			rep(k,0,c) a(i,j) += operator()(i,k)*m(k,j);
		}
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		M a((int)vec.size(), 1); a.d = vec;
		return (*this * a).d;
	}
	M operator^(ll p) const {
		M a(r, c), b(*this);
		rep(i,0,r) a(i,i) = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};
