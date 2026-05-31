#include "polygon.hpp"

using p_t = malashenko::Point;
using pol_t = malashenko::Polygon;

malashenko::Triangle malashenko::makeTriangle(const pol_t& pol, const p_t& p1, const p_t& p2)
{
  return {pol.points[0], p1, p2};
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
  if (pol.points.size() == 3)
  {
    return {{pol.points[0], pol.points[1], pol.points[2]}};
  }

  using namespace std::placeholders;
  std::vector< Triangle > res;
  std::transform(
      pol.points.cbegin() + 1,
      pol.points.cend() - 1,
      pol.points.cbegin() + 2,
      std::back_inserter(res),
      std::bind(makeTriangle, pol, _1, _2)
  );

  return res;
}



std::vector< double > malashenko::convertToAreas(const std::vector< Triangle >& triVec)
{
  std::vector< double > res;

  std::transform(
      triVec.cbegin(),
      triVec.cend(),
      std::back_inserter(res),
      countTriangleArea
  );

  return res;
}

double malashenko::sumArea(const std::vector< double >& areas)
{
  return std::accumulate(areas.begin(), areas.end(), 0.0f);
}

bool malashenko::hasRightAngle(const pol_t& pol, size_t i)
{
  std::vector< p_t > pts = pol.points;
  size_t n = pts.size();

  size_t prev = (i + n - 1) % n;
  size_t next = (i + 1) % n;

  Point v1{pts[prev].x - pts[i].x, pts[prev].y - pts[i].y};
  Point v2{pts[next].x - pts[i].x, pts[next].y - pts[i].y};

  return v1.x * v2.x + v1.y * v2.y == 0;
}


bool malashenko::hasRightAngleInPolygon(const pol_t& pol)
{
  std::vector< size_t > indices(pol.points.size());
  std::iota(indices.begin(), indices.end(), 0);

  using namespace std::placeholders;
  auto it = std::find_if(
    indices.cbegin(),
    indices.cend(),
    std::bind(hasRightAngle, std::cref(pol), _1)
  );

  return it != indices.cend();
}


std::vector< malashenko::Segment > malashenko::getSegments(const pol_t& pol)
{
  std::vector< Segment > res;

  std::transform(
      pol.points.cbegin(),
      pol.points.cend() - 1,
      pol.points.cbegin() + 1,
      std::back_inserter(res),
      makeSegment
  );

  res.push_back({pol.points.back(), pol.points.front()});

  return res;
}

malashenko::Segment malashenko::makeSegment(const Point& p1, const Point& p2)
{
  return {p1, p2};
}

int malashenko::orient(const Point& a, const Point& b, const Point& c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool malashenko::onSegment(const Point& a, const Point& b, const Point& p)
{
  bool res = orient(a, b, p) == 0 && std::min(a.x, b.x) <= p.x;
  res = res && p.x <= std::max(a.x, b.x) && std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
  return res;
}

bool malashenko::segmentsIntersect(const Segment& s1, const Segment& s2)
{
  auto o1 = orient(s1.p1, s1.p2, s2.p1);
  auto o2 = orient(s1.p1, s1.p2, s2.p2);
  auto o3 = orient(s2.p1, s2.p2, s1.p1);
  auto o4 = orient(s2.p1, s2.p2, s1.p2);

  bool res = (o1 == 0 && onSegment(s1.p1, s1.p2, s2.p1)) || (o2 == 0 && onSegment(s1.p1, s1.p2, s2.p2));
  res = res || (o3 == 0 && onSegment(s2.p1, s2.p2, s1.p1)) || (o4 == 0 && onSegment(s2.p1, s2.p2, s1.p2));
  if (res)
  {
    return true;
  }

  return (o1 * o2 < 0) && (o3 * o4 < 0);
}

bool malashenko::intersectsWithAny(const Segment& seg, const std::vector< Segment >& segments)
{
  using namespace std::placeholders;

  return std::any_of(
      segments.cbegin(),
      segments.cend(),
      std::bind(segmentsIntersect, seg, _1)
  );
}

bool malashenko::polygonsIntersect(const Polygon& lhs, const Polygon& rhs)
{
    auto segs1 = getSegments(lhs);
    auto segs2 = getSegments(rhs);

    using namespace std::placeholders;

    if (std::any_of(segs1.cbegin(), segs1.cend(), std::bind(intersectsWithAny, _1, std::cref(segs2))))
    {
        return true;
    }


    if (isPointInPolygon(lhs.points.front(), rhs))
    {
        return true;
    }

    if (isPointInPolygon(rhs.points.front(), lhs))
    {
        return true;
    }

    return false;
}

bool malashenko::rayIntersectsSegment(const Point& p, const Segment& s)
{
    double py = static_cast<double>(p.y);
    double y1 = static_cast<double>(s.p1.y);
    double y2 = static_cast<double>(s.p2.y);

    if (py < std::min(y1, y2) || py >= std::max(y1, y2))
    {
        return false;
    }

    if (y1 == y2)
    {
        return false;
    }

    double x1 = static_cast<double>(s.p1.x);
    double x2 = static_cast<double>(s.p2.x);

    double x_intersect = x1 + (py - y1) * (x2 - x1) / (y2 - y1);

    return x_intersect > p.x;
}

bool malashenko::isPointInPolygon(const Point& p, const Polygon& pol)
{
    if (pol.points.empty())
    {
        return false;
    }

    auto segs = getSegments(pol);


    using namespace std::placeholders;

    int intersections = std::count_if(
        segs.begin(),
        segs.end(),
        std::bind(rayIntersectsSegment, p, _1)
    );

    return (intersections % 2) != 0;
}