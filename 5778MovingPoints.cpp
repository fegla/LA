#include <iterator>
#include <cstring>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <sstream>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <complex>
#include <list>
#include <valarray>
using namespace std;
#define SZ(v)                   (int)v.size()
#define all(v)					v.begin(), v.end()
#define rall(v)					v.rbegin(), v.rend()
typedef long long ll;
const int OO = 1 << 28;

#ifndef M_PI
const double M_PI=acos(-1.0);
#endif
typedef complex<double> point;
#define sz(a) ((int)(a).size())
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define length(v) ((double)hypot((v).Y,(v).X))
#define dot(a,b) ((conj(a)*(b)).real())

double mysp;
/*
 *
 *       get Time is used to find the time taken for me to reach the point p that is moving in direction d with speed s
 *       given that i am currently at point my and i am traveling at speed mysp
 *
 *        meeting point
 *              /\
 *             /  \
 *            /    \
 *  mysp*t=a /      \ b=s*t
 *          /      +-\
 *         /       |th\
 *        /________|___\
 *       my     c        p
 *
 *
 *      looking at the triangle above using cosine rule
 *
 *      cosTh = (b * b + c *c - a * a) / ( 2 * b * c)
 *      cosTh = (s * t * s * t + c * c - mysp * t * mysp * t) / ( 2 * s * t * c)
 *      ( 2 * s * t * c) * cosTh = s^2 t^2 + c^2 - mysp ^ 2 t ^2
 *      t^2 ( s^2-mysp^2) - t ( 2sc cosTh) + c^2 =0
 *
 *      then if A=( s^2-mysp^2) and B=( 2sc cosTh) and C= c^2
 *      then the equation will be At^2+ Bt + C=0
 *		which has the solution t1,t2 = (-B (+or-) sqrt(B * B - 4 * A * C)) / (2 * A);
 *		which means that i can meet it in times t1 and t2 and since i need the earliest of both then i will take t2
 *
 */

double getTime(const point &my, const point &p, const point &d,
		const double &s) {
	double c = length(vec(p,my));
	if (c < EPS)
		return 0;
	double cosTh = dot(vec(p,my)/c,d);
	double A = s * s - mysp * mysp;
	double B = -2 * s * c * cosTh;
	double C = c * c;
	//double t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
	double t2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);

	return t2;
}

point init[15], dir[15];
double sp[15];

int n;
#define deg2rad(x) ((x)*M_PI/180)
struct state {
	int vis, lst;
	double t;
	bool operator <(const state& s) const {
		return t > s.t;
	}
};

point getPos(int i, double ct) {
	return init[i] + ct * sp[i] * dir[i];
}

double best[1 << 15][15];
double dijkstra() {
	double res;
	priority_queue<state> q;
	fill((double*) (best), (double*) (best) + (1 << 15) * 15, 1e10);
	for (int i = 0; i < n; i++) {
		double t = getTime(point(0, 0), init[i], dir[i], sp[i]);
		state s = { 1 << i, i, t };
		best[1 << i][i] = t;
		q.push(s);
	}
	while (q.size()) {
		state s = q.top();
		q.pop();
		if (s.t != best[s.vis][s.lst])
			continue;

		if (s.vis == ((1 << n) - 1)) {
			res = s.t;
			break;
		}
		point my = getPos(s.lst, s.t);
		for (int i = 0; i < n; i++) {
			if ((s.vis >> i) & 1)
				continue;

			double t = getTime(my, getPos(i, s.t), dir[i], sp[i]);
			state ns = { s.vis | (1 << i), i, s.t + t };
			if (ns.t < best[ns.vis][ns.lst]) {
				best[ns.vis][ns.lst] = ns.t;
				q.push(ns);
			}
		}

	}
	return res;
}

int main() {

	while (cin >> n >> mysp && (n || mysp)) {
		for (int i = 0; i < n; ++i) {
			int x, y, a, s;
			cin >> x >> y >> a >> s;
			init[i] = point(x, y);
			dir[i] = polar(1.0,deg2rad(a));
			sp[i] = s;
		}
		printf("%.2lf\n", dijkstra());
	}
	return 0;
}

