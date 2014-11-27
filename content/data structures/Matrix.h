/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * Source: My head
 * Description: Basic matrix operations.
 * Usage: Matrix<int> A(3,3,2), b(3,1,3);
 *  A(1,2) = 5;
 *  b(2,0) = 0;
 *  cout << b/2 + A*A*b*3 + (A^3)*b - A->*A*b + 5;
 * Status: tested
 */
#pragma once
#include <cmath>
#include <iostream>

template <class T> struct Matrix {
	typedef Matrix M;
	typedef const M& R;
	int r, c;
	T* d;
	Matrix(int _r, int _c) : r(_r), c(_c) {
		d = new T[r*c];
	}
	Matrix() : r(0), c(0), d(0) {}
	Matrix(int _r, int _c, T value)
		: r(_r), c(_c) {
		d = new T[r*c];
		rep(i,0,r) rep(j,0,c)
			operator()(i,j) = value;
	}
	Matrix(R m) : r(m.r), c(m.c) {
		d = new T[r*c];
		rep(i,0,r) rep(j,0,c)
			operator()(i,j) = m(i,j);
	}
	~Matrix() { delete[] d; }
	T& operator()(int row, int col) const { return d[row*c+col]; }
	bool operator==(R m) const {
		rep(i,0,r) rep(j,0,c)
			if (!(operator()(i,j)==m(i,j))) return false;
		return true;
	}
	void operator=(R m) {
		delete[] d;
		r = m.r;
		c = m.c;
		d = new T[r*c];
		rep(i,0,r) rep(j,0,c)
			operator()(i,j) = m(i,j);
	}
	M operator+(R m) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)+m(i,j);
		return a;
	}
	M operator-(R m) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)-m(i,j);
		return a;
	}
	M operator->*(R m) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)*m(i,j);
		return a;
	}
	M operator/(R m) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)/m(i,j);
		return a;
	}
	M operator*(R m) const {
		M a(r, m.c);
		rep(i,0,r) rep(j,0,m.c) {
			a(i,j) = 0;
			rep(k,0,c) a(i,j) += operator()(i,k)*m(k,j);
		}
		return a;
	}
	M operator+(T v) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)+v;
		return a;
	}
	M operator-(T v) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)-v;
		return a;
	}
	M operator*(T v) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)*v;
		return a;
	}
	M operator/(T v) const {
		M a(r, c);
		rep(i,0,r) rep(j,0,c)
			a(i,j) = operator()(i,j)/v;
		return a;
	}
	M operator^(int p) {
		M a(r, c, 0), b(*this);
		rep(i,0,r) a(i,i) = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
	void set(T v) {
		rep(i,0,r) rep(j,0,c)
			operator()(i,j) = v;
	}
};
