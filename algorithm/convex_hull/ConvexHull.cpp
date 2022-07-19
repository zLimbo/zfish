#include "zLimboConvexHull.h"
#include <stack>
#include <map>

namespace zLimbo {

	using std::cout;
	using std::endl;
	using std::map;
	using std::vector;
	using std::stack;
	using cv::Point2f;

	int lowestThenLeftmost(vector<Point2f> &points) {

		int ltl = 0;
		size_t sz = points.size();

		for (size_t i = 1; i < sz; ++i)
			if (points[i].y < points[ltl].y || points[i].y == points[ltl].y && points[i].x < points[ltl].x)
				ltl = i;
		return ltl;
	}


	bool onLeft(Point2f &p, Point2f &q, Point2f &s) {
		int helenArea = p.x * q.y - p.y * q.x
			+ q.x * s.y - s.x * q.y
			+ s.x * p.y - p.x * s.y;
		return helenArea > 0;
	}


	void myConvexHull(vector<Point2f> &points, vector<int> &hull) {
		int ltl = lowestThenLeftmost(points);
		int p = ltl;
		size_t sz = points.size();
		do {
			hull.push_back(p);
			int q = -1;
			for (size_t k = 0; k < sz; ++k) {
				if (k != p && k != q && (q == -1 || !onLeft(points[p], points[q], points[k])))
					q = k;
			}
			p = q;
		} while (p != ltl);
		
	}

	void myConvexHull2(vector<Point2f> &points, vector<int> &hull) {

		int ltl = lowestThenLeftmost(points);

		size_t sz = points.size();
		int p = ltl, q = -1;
		for (size_t k = 0; k < sz; ++k) {
			if (k != p && k != q && (q == -1 || !onLeft(points[p], points[q], points[k])))
				q = k;
		}

		hull.push_back(p);
		hull.push_back(q);

		map<double, int> auxMap;

		double xq = points[q].x - points[p].x, yq = points[q].y - points[p].y;
		double qLen = sqrt(xq * xq + yq * yq);
		for (size_t k = 0; k < sz; ++k) {
			if (k != p && k != q) {
				double xk = points[k].x - points[p].x, yk = points[k].y - points[p].y;
				double kLen = sqrt(xk * xk + yk * yk);
				double cosine = -(xq * xk + yq * yk) / (qLen * kLen);
				
				auxMap.emplace(cosine, k);
			}
		}
		for (auto it = auxMap.begin(); it != auxMap.end(); ++it) {
			if (onLeft(points[hull[hull.size() - 2]], points[hull[hull.size() - 1]], points[it->second]))
				hull.push_back(it->second);
			else {
				hull.pop_back();
				--it;
			}
		}
	}
}