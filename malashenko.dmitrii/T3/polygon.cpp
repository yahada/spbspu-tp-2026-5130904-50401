#include "polygon.hpp"

using p_t = malashenko::Point;

malashenko::detail::Triangle::Triangle(p_t a, p_t b, p_t c, Polygon& pol):
  t1(a),
  t2(b),
  t3(c),
  polRef(pol)
{}

malashenko::detail::Triangle malashenko::detail::makeTriangle(Polygon& pol)
{
  static size_t pointPos = 0;
  return {pol.points[0], pol.points[++pointPos], pol.points[++pointPos], pol};
}

int malashenko::detail::countTriangleSquare(const std::vector< Triangle >& triangles)
{
  static size_t triPos = 0;
  Triangle tri = triangles[triPos];
  Point p1 = tri.t1;
  Point p2 = tri.t2;
  Point p3 = tri.t3;
  ++triPos;
  return std::abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2;
}


std::vector< malashenko::detail::Triangle > malashenko::detail::convertToTriangle(const Polygon& pol)
{
  std::vector< Triangle > res(pol.points.size() - 2);
  std::generate(res.begin(), res.end(), makeTriangle(pol));
  return res;
}

std::vector< int > malashenko::detail::convertToSquares(const std::vector< Triangle >& triangles)
{
  std::vector< int > res(triangles.size());
  std::generate(res.begin(), res.end(), countTriangleSquare(triangles));
}

int malashenko::detail::calcPolygonSquare(const std::vector< int >& squares)
{
  return std::accumulate(squares.begin(), squares.end(), 0);
}




