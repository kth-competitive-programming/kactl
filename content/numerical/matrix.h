/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * Source: My head
 * Description: 
 * Usage:
 * Status: Not done
 */
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

template <class T>
struct Matrix {
	typedef T elemType;
	typedef Matrix M;
	typedef const M & R;
	int rows, cols; //The number of rows and columns
	T* data;
	//number of rows, number of columns and initial values
	Matrix(int _rows, int _cols)
		: rows(_rows), cols(_cols) {
		data = new T[rows*cols];
	}
	~Matrix() { delete data[]; }

...............................................................
	T operator()(int row, int col) { return data[row*cols+col]; }
	bool operator==(R m) const {
		rep(i,0,rows) rep(j,0,cols)
			if (!(operator()(i,j)==m(i,j))) return false;
		return true;
	}
	P operator+(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)+m(i,j);
		return a;
	}
	P operator-(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)-m(i,j);
		return a;
	}
	P operator->*R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)->*m(i,j);
		return a;
	}
	P operator/(R m) const {
		M a(rows, cols);
		rep(i,0,rows) rep(j,0,cols)
			a(i,j) = operator()(i,j)/m(i,j);
		return a;
	}
	P operator*(R m) const {
		M a(rows, m.cols);
		rep(i,0,rows) rep(j,0,m.cols) {
			a(i,j) = 0;
			rep(k,0,cols) a(i,j) += operator()(i,k)*m(k,j);
		}
		return a;
	}
  //TODO: ones, zeros, ^, <<, >>
};
template <class T>
ostream & operator<<(ostream & os, const Point<T> & p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
template <class T>
istream & operator>>(istream & is, Point<T> & p) {
	is >> p.x >> p.y;
	return is;
}
