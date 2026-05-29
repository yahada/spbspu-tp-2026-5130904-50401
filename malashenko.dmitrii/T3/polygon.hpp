#ifndef POLYGON
#define POLYGON
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

namespace malashenko
{
  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  namespace detail
  {
    struct Triangle {
      Triangle(Point, Point, Point, Polygon&);
      Point t1, t2, t3;
      Polygon& polRef;
    };

    std::vector< Triangle > convertToTriangle(const Polygon& pol);
    std::vector< int > convertToSquares(const std::vector< Triangle >& triangles);
    int calcPolygonSquare(const std::vector< int >& squares);
    Triangle makeTriangle(const Polygon& pol);
    int countTriangleSquare(const std::vector< Triangle >& triangles);
  }


}


#endif
