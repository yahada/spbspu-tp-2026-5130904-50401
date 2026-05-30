#include "polygon.hpp"

using p_t = malashenko::Point;
using pol_t = malashenko::Polygon;


malashenko::Triangle::Triangle(const p_t& a, const p_t& b, const p_t& c, const pol_t& pol):
  t1(a),
  t2(b),
  t3(c),
  parentPolygon(pol)
{}

malashenko::Triangle malashenko::makeTriangle(const pol_t& pol, const p_t& p1, const p_t& p2)
{
  Triangle tri(pol.points[0], p1, p2, pol);
  return tri;
}

double malashenko::countTriangleArea(const Triangle& tri)
{
  Point p1 = tri.t1;
  Point p2 = tri.t2;
  Point p3 = tri.t3;
  int tmp = std::abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
  return static_cast< double >(tmp) / 2;
}


std::vector< malashenko::Triangle > malashenko::convertToTriangles(const pol_t& pol)
{
  using namespace std::placeholders;
  std::vector< Triangle > res(pol.points.size() - 2);
  std::transform(++pol.points.cbegin(),
                  pol.points.cend(),
                  (pol.points.cbegin() + 2),
                  res.begin(),
                  std::bind(makeTriangle, pol, _1, _2));
  return res;
}

std::vector< double > malashenko::convertToAreas(const std::vector< Triangle >& triVec)
{
  std::vector< double > res(triVec.size());
  std::transform(triVec.cbegin(), triVec.cend(), res.begin(), countTriangleArea);
  return res;
}

double malashenko::sumArea(const std::vector< double >& areas)
{
  return std::accumulate(areas.cbegin(), areas.cend(), 0);
}




