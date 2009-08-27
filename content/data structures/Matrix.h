/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * Source: My head
 * Description: Class for handling matrices with the +, *, -, / and $\hat{ }$ operators and functions for accessing individual elements and reading and writing a matrix to a stream. Most of the functions are not always neccescary so not all of them need to be implemented.
 * Usage: Matrix<int> A(3,3,2), b(3,1,3);
 *  A(1,2) = 5;
 *  b(2,0) = 0;
 *  cout << b/2 + A*A*b*3 + (A^3)*b - A->*A*b + 5;
 * Status: tested
 */
#pragma once
#include <cmath>
#include <iostream>

template <class T>
struct Matrix {
	typedef T elemType;
	typedef Matrix M;
	typedef const M & R;
	int rows, cols; //The number of rows and columns
	T* data;
	//number of rows and columns
	Matrix(int _rows, int _cols) : rows(_rows), cols(_cols) {
		data = new T[rows*cols];
	}
	Matrix() : rows(0), cols(0), data(0) {}
	Matrix(int _rows, int _cols, T value)
		: rows(_rows), cols(_cols) {
		data = new T[rows*cols];
		rep(i,0,rows) rep(j,0,cols)
			operator()(i,j) = value;
	}
	Matrix(R m) : rows(m.rows), cols(m.cols) {
		data = new T[rows*cols];
		rep(i,0,rows) rep(j,0,cols)
			operator()(i,j) = m(i,j);
	}
	~Matrix() { delete[] data; }
	T& operator()(int row, int col) const { return data[row*cols+col]; }
	bool operator==(R m) const {
		rep(i,0,rows) rep(j,0,cols)
			if (!(operator()(i,j)==m(i,j))) return false;
		return true;
	}
	void operator=(R m) {
		delete[] data;
		rows = m.rows;
		cols = m.cols;
		data = new T[rows*cols];
		rep(i,0,rows) rep(j,0,cols)
			operator()(i,j) = m(i,j);
	}
	//implement the functions needed out of those bellow
	M operator+(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)+m(i,j);
		return a;
	}
	M operator-(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)-m(i,j);
		return a;
	}
	M operator->*(R m) const { //element-wise multiplication
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)*m(i,j);
		return a;
	}
	M operator/(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)/m(i,j);
		return a;
	}
	M operator*(R m) const { //matrix multiplication
		M a(rows, m.cols);
		rep(i,0,rows) rep(j,0,m.cols) {
			a(i,j) = 0;
			rep(k,0,cols) a(i,j) += operator()(i,k)*m(k,j);
		}
		return a;
	}
	M operator+(T v) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)+v;
		return a;
	}
	M operator-(T v) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)-v;
		return a;
	}
	M operator*(T v) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)*v;
		return a;
	}
	M operator/(T v) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)/v;
		return a;
	}
	M operator^(int p) {
		M a(rows, cols, 0), b(*this);
		rep(i,0,rows) a(i,i) = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
	void set(T v) {
		rep(i,0,rows) rep(j,0,cols)
			operator()(i,j) = v;
	}
};
template <class T>
ostream & operator<<(ostream & os, const Matrix<T> & m) {
	os << m.rows << " " << m.cols << endl;
	rep(i,0,m.rows) {
		rep(j,0,m.cols) os << m(i,j) << " ";
		os << endl;
	}
	return os;
}
template <class T>
istream & operator>>(istream & is, Matrix<T> & m) {
	is >> m.rows >> m.cols;
	delete[] m.data;
	m.data = new T[m.rows*m.cols];
	rep(i,0,m.rows) rep(j,0,m.cols)
		is >> m(i,j);
	return is;
}
