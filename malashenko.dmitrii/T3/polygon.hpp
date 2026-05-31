#ifndef POLYGON
#define POLYGON
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

namespace malashenko
{
  struct Point
  {
    int x, y;
  };

  struct Segment
  {
    Point p1;
    Point p2;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  struct Triangle {
    Triangle() = default;
    Point t1, t2, t3;
  };


  Triangle makeTriangle(const Polygon&, const Point&, const Point&);
  std::vector< Triangle > convertToTriangles(const Polygon&);


  double countTriangleArea(const Triangle&);
  std::vector< double > convertToAreas(const std::vector< Triangle >&);

  bool hasRightAngleInPolygon(const Polygon& pol);
  bool hasRightAngle(const Polygon& pol, size_t i);


  double sumArea(const std::vector< double >&);
  Segment makeSegment(const Point& p1, const Point& p2);
  std::vector< Segment > getSegments(const Polygon& pol);
  int orient(const Point& a, const Point& b, const Point& c);
  bool onSegment(const Point& a, const Point& b, const Point& p);
  bool segmentsIntersect(const Segment& s1, const Segment& s2);
  bool intersectsWithAny(const Segment& seg, const std::vector< Segment >& segments);
  bool polygonsIntersect(const Polygon& lhs, const Polygon& rhs);
}


#endif
