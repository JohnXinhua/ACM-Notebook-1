#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1e-6;

struct point {
  double x, y;
  point() {}
  point(double x_, double y_): x(x_), y(y_) {}
  point(const point& p): x(p.x), y(p.y) {}

  point operator+(const point& p) const { return point(x + p.x, y + p.y); }
  point operator-(const point& p) const { return point(x - p.x, y - p.y); }
  point operator*(double c) const { return point(x * c, y * c); }
  point operator/(double c) const { return point(x / c, y / c); }
};
ostream &operator<<(ostream &os, const point& p) {
  os << "(" << p.x << "," << p.y << ")";
}

double dot(point p, point q) { return p.x * q.x + p.y * q.y; }
double dist2(point p, point q) { return dot(p - q, p - q); }
double dist(point p, point q) { return sqrt(dist2(p, q)); }
double cross(point p, point q) { return p.x * q.y - p.y * q.x; }

// test if point c is Left | On | Right of line through a, b
// returns > 0 if left, = 0 if on, < 0 if right
double is_left(point a, point b, point c) {
  return cross(b - a, c - a);
}

point rotate_cw_90(point p) { return point(p.y, -p.x); }
point rotate_ccw_90(point p) { return point(-p.y, p.x); }
// rotate point counter-clockwise around origin
point rotate(point p, double a) {
  return point(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
}

// project c on line through a and b (a != b)
point project_point_line(point a, point b, point c) {
  return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}
// project point c onto line segment through a and b
point project_point_segment(point a, point b, point c) {
  double d = dot(b - a, b - a);
  if (abs(d) < EPS) return a;
  d = dot(c - a, b - a) / d;
  if (d < 0) return a;
  if (d > 1) return b;
  return a + (b - a) * d;
}

// compute distance from c to segment between a and b
double distance_point_segment(point a, point b, point c) {
  return sqrt(dist2(c, project_point_segment(a, b, c)));
}
// compute distance between point (x, y, z) and plane ax + by + cz = d
double distance_point_plane(double x, double y, double z,
    double a, double b, double c, double d) {
  return abs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

// determine if lines a - b and c - d are parallel or collinear
bool lines_parallel(point a, point b, point c, point d) {
  return abs(cross(b - a, c - d)) < EPS;
}
bool lines_collinear(point a, point b, point c, point d) {
  return lines_parallel(a, b, c, d) &&
    abs(cross(a - b, a - c)) < EPS &&
    abs(cross(c - d, c - a)) < EPS;
}

// check if line segment a - b intersects line segment c - d
bool segments_intersect(point a, point b, point c, point d) {
  if (lines_collinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
        dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 &&
        dot(c - b, d - b) > 0) return false;
    return true;
  }
  if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
  if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
  return true;
}
point compute_line_intersection(point a, point b, point c, point d) {
  b = b - a; d = c - d; c = c - a;
  return a + b * cross(c, d) / cross(b, d);
}

// compute center of circle given three points
point compute_circle_center(point a, point b, point c) {
  b = (a + b) / 2;
  c = (a + c) / 2;
  return compute_line_intersection(b, b + rotate_cw_90(a - b),
      c, c + rotate_cw_90(a - c));
}

// test if point p is in polygon (use winding number test)
bool point_in_poly(point p, const vector<point>& v) {
  int wn = 0;
  int n = static_cast<int>(v.size());
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    if (v[i].y <= p.y) {
      if (v[j].y > p.y && is_left(v[i], v[j], p) > 0)
        ++wn;
    } else {
      if (v[j].y <= p.y && is_left(v[i], v[j], p) < 0)
        --wn;
    }
  }

  return wn != 0;
}
bool point_on_polygon(point p, const vector<point>& v) {
  int n = static_cast<int>(v.size());
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    if (dist2(project_point_segment(v[i], v[j], p), p) < EPS)
      return true;
  }
  return false;
}

// compute signed area of polygon
double signed_area(const vector<point>& v) {
  int n = static_cast<int>(v.size());
  double area = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    area += v[i].x * v[j].y - v[j].x * v[i].y;
  }
  return area / 2.0;
}
double area(const vector<point>& v) {
  return abs(signed_area(v));
}

// compute centroid of polygon
point centroid(const vector<point>& v) {
  int n = static_cast<int>(v.size());
  point c(0, 0);
  double scale = 6.0 * signed_area(v);
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    c = c + (v[i] + v[j]) * (v[i].x * v[j].y - v[j].x * v[i].y);
  }
  return c / scale;
}

bool is_simple(const vector<point>& v) {
  int n = static_cast<int>(v.size());
  for (int i = 0; i < n; ++i) {
    for (int k = i + 1; k < n; ++k) {
      int j = (i + 1) % n;
      int l = (k + 1) % n;
      if (i == l || j == k) continue;
      if (segments_intersect(v[i], v[j], v[k], v[l]))
        return false;
    }
  }
  return true;
}

int main()
{
  // expected: (-5,2)
  cerr << rotate_ccw_90(point(2,5)) << endl;

  // expected: (5,-2)
  cerr << rotate_cw_90(point(2,5)) << endl;

  // expected: (-5,2)
  cerr << rotate(point(2,5),M_PI/2) << endl;

  // expected: (5,2)
  cerr << project_point_line(point(-5,-2), point(10,4), point(3,7)) << endl;

  // expected: (5,2) (7.5,3) (2.5,1)
  cerr << project_point_segment(point(-5,-2), point(10,4), point(3,7)) << " "
    << project_point_segment(point(7.5,3), point(10,4), point(3,7)) << " "
    << project_point_segment(point(-5,-2), point(2.5,1), point(3,7)) << endl;

  // expected: 6.78903
  cerr << distance_point_plane(4,-4,3,2,-2,5,-8) << endl;

  // expected: 1 0 1
  cerr << lines_parallel(point(1,1), point(3,5), point(2,1), point(4,5)) << " "
    << lines_parallel(point(1,1), point(3,5), point(2,0), point(4,5)) << " "
    << lines_parallel(point(1,1), point(3,5), point(5,9), point(7,13)) << endl;

  // expected: 0 0 1
  cerr << lines_collinear(point(1,1), point(3,5), point(2,1), point(4,5)) << " "
    << lines_collinear(point(1,1), point(3,5), point(2,0), point(4,5)) << " "
    << lines_collinear(point(1,1), point(3,5), point(5,9), point(7,13)) << endl;

  // expected: 1 1 1 0
  cerr << segments_intersect(point(0,0), point(2,4), point(3,1), point(-1,3)) << " "
    << segments_intersect(point(0,0), point(2,4), point(4,3), point(0,5)) << " "
    << segments_intersect(point(0,0), point(2,4), point(2,-1), point(-2,1)) << " "
    << segments_intersect(point(0,0), point(2,4), point(5,5), point(1,7)) << endl;

  // expected: (1,2)
  cerr << compute_line_intersection(point(0,0), point(2,4), point(3,1), point(-1,3)) << endl;

  // expected: (1,1)
  cerr << compute_circle_center(point(-3,4), point(6,1), point(4,5)) << endl;

  vector<point> v;
  v.push_back(point(0,0));
  v.push_back(point(5,0));
  v.push_back(point(5,5));
  v.push_back(point(0,5));

  // expected: 1 1 1 0 0
  cerr << point_in_poly(point(2,2), v) << " "
    << point_in_poly(point(2,0), v) << " "
    << point_in_poly(point(0,2), v) << " "
    << point_in_poly(point(5,2), v) << " "
    << point_in_poly(point(2,5), v) << endl;

  // expected: 0 1 1 1 1
  cerr << point_on_polygon(point(2,2), v) << " "
    << point_on_polygon(point(2,0), v) << " "
    << point_on_polygon(point(0,2), v) << " "
    << point_on_polygon(point(5,2), v) << " "
    << point_on_polygon(point(2,5), v) << endl;

  // area should be 5.0
  // centroid should be (1.1666666, 1.166666)
  point pa[] = { point(0,0), point(5,0), point(1,1), point(0,5) };
  vector<point> p(pa, pa+4);
  point c = centroid(p);
  cerr << "Area: " << area(p) << endl;
  cerr << "Centroid: " << c << endl;

  return 0;
}
