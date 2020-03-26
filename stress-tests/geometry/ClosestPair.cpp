#include "../utilities/template.h"

#include "../../content/geometry/ClosestPair.h"

namespace old {
template<class It>
bool it_less(const It& i, const It& j) { return *i < *j; }
template<class It>
bool y_it_less(const It& i,const It& j) {return i->y < j->y;}

template<class It, class IIt> /* IIt = vector<It>::iterator */
double cp_sub(IIt ya, IIt yaend, IIt xa, It &i1, It &i2) {
	typedef typename iterator_traits<It>::value_type P;
	int n = yaend-ya, split = n/2;
	if(n <= 3) { // base case
		double a = (*xa[1]-*xa[0]).dist(), b = 1e50, c = 1e50;
		if(n==3) b=(*xa[2]-*xa[0]).dist(), c=(*xa[2]-*xa[1]).dist();
		if(a <= b) { i1 = xa[1];
			if(a <= c) return i2 = xa[0], a;
			else return i2 = xa[2], c;
		} else { i1 = xa[2];
			if(b <= c) return i2 = xa[0], b;
			else return i2 = xa[1], c;
	}	}
	vector<It> ly, ry, stripy;
	P splitp = *xa[split];
	double splitx = splitp.x;
	for(IIt i = ya; i != yaend; ++i) { // Divide
		if(*i != xa[split] && (**i-splitp).dist2() < 1e-12)
			return i1 = *i, i2 = xa[split], 0;// nasty special case!
		if (**i < splitp) ly.push_back(*i);
		else ry.push_back(*i);
	} // assert((signed)lefty.size() == split)
	It j1, j2; // Conquer
	double a = cp_sub(ly.begin(), ly.end(), xa, i1, i2);
	double b = cp_sub(ry.begin(), ry.end(), xa+split, j1, j2);
	if(b < a) a = b, i1 = j1, i2 = j2;
	double a2 = a*a;
	for(IIt i = ya; i != yaend; ++i) { // Create strip (y-sorted)
		double x = (*i)->x;
		if(x >= splitx-a && x <= splitx+a) stripy.push_back(*i);
	}
	for(IIt i = stripy.begin(); i != stripy.end(); ++i) {
		const P &p1 = **i;
		for(IIt j = i+1; j != stripy.end(); ++j) {
			const P &p2 = **j;
			if(p2.y-p1.y > a) break;
			double d2 = (p2-p1).dist2();
			if(d2 < a2) i1 = *i, i2 = *j, a2 = d2;
	}	}
	return sqrt(a2);
}

template<class It> // It is random access iterators of point<T>
double closestpair(It begin, It end, It &i1, It &i2 ) {
	vector<It> xa, ya;
	assert(end-begin >= 2);
	for (It i = begin; i != end; ++i)
		xa.push_back(i), ya.push_back(i);
	sort(xa.begin(), xa.end(), it_less<It>);
	sort(ya.begin(), ya.end(), y_it_less<It>);
	return cp_sub(ya.begin(), ya.end(), xa.begin(), i1, i2);
}
}

int main() {
	// Compare against the old code
	ll sum = 0;
	int mode = 1;
	if (mode != 0) rep(it,0,100) {
		// clog << it << ' ';
		int n = 100000;
		int maxx = rand() % 1000000 + 1;
		int maxy = rand() % 1000000 + 1;
		int biasx = -100;
		int biasy = -100;
		vector<P> ps;
		rep(i,0,n) {
			int x = rand() % maxx + biasx;
			int y = rand() % maxy + biasy;
			ps.emplace_back(x, y);
		}
		ll foundDist = -1, oldDist = -1, theDist = -1;
		if (mode == 1 || mode == 3) {
			auto pa = closest(ps);
			theDist = foundDist = (pa.first - pa.second).dist2();
		}
		if (mode == 2 || mode == 3) {
			vector<P>::iterator i1, i2;
			old::closestpair(all(ps), i1, i2);
			theDist = oldDist = (*i1 - *i2).dist2();
		}
		sum += theDist;
		// cerr << theDist << endl;
		if (mode == 3 && oldDist != foundDist) {
			cerr << "failed at " << it << endl;
			return 1;
		}
	}
	// cout << sum << endl;

	// Compare against bruteforce
	rep(it,0,1'000'000) {
		int n = rand() % 15 + 2;
		int maxx = rand() % 20 + 1;
		int maxy = rand() % 20 + 1;
		int biasx = rand() % 20 - 10;
		int biasy = rand() % 20 - 10;
		vector<P> ps;
		rep(i,0,n) {
			int x = rand() % maxx + biasx;
			int y = rand() % maxy + biasy;
			ps.emplace_back(x, y);
		}
		ll minDist = LLONG_MAX;
		rep(i,0,n) rep(j,i+1,n) {
			minDist = min(minDist, (ps[i] - ps[j]).dist2());
		}
		auto pa = closest(ps);
		ll foundDist = (pa.first - pa.second).dist2();
		if (minDist != foundDist) {
			cerr << "failed at " << it << endl;
			return 1;
		}
	}
	cout<<"Tests passed!"<<endl;
}
