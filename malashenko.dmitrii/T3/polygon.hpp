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

  struct Polygon {
    std::vector< Point > points;
  };

  struct Triangle {
    Triangle() = default;
    Triangle(const Point&, const Point&, const Point&, const Polygon& pol);

    Point t1, t2, t3;
    Polygon parentPolygon;
  };


  Triangle makeTriangle(const Polygon&, const Point&, const Point&);
  std::vector< Triangle > convertToTriangles(const Polygon&);


  double countTriangleArea(const Triangle&);
  std::vector< double > convertToAreas(const std::vector< Triangle >&);

  double sumArea(const std::vector< double >&);

}


#endif
