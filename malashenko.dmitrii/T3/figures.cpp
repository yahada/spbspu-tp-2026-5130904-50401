#include "figures.hpp"
#include <iterator>

std::vector< double > malashenko::Figures::getPolygonsAreas(const std::vector< Polygon >& polygons) const
{
  std::vector< std::vector< Triangle > > triangles;
  std::transform(
      polygons.cbegin(),
      polygons.cend(),
      std::back_inserter(triangles),
      convertToTriangles
  );

  std::vector< std::vector< double > > areas;
  std::transform(
    triangles.cbegin(),
    triangles.cend(),
    std::back_inserter(areas),
    convertToAreas
  );

  std::vector< double > res;
  std::transform(
    areas.cbegin(),
    areas.cend(),
    std::back_inserter(res),
    sumArea
  );

  return res;
}

std::vector< size_t > malashenko::Figures::getAmountsOfVertexes(const std::vector< Polygon >& polygons) const
{
  std::vector< size_t > res;
  std::transform(
      polygons.cbegin(),
      polygons.cend(),
      std::back_inserter(res),
      detail::vertexes
  );
  return res;
}

size_t malashenko::detail::vertexes(const Polygon& pol)
{
  return pol.points.size();
}


bool malashenko::detail::isEvenCheck(const Polygon& pol, bool isEven)
{
  bool check = pol.points.size() % 2 == 0;
  return isEven ? check : !check;
}


bool malashenko::detail::isEqualCheck(const Polygon& pol, size_t amount)
{
  return pol.points.size() == amount;
}


std::vector< malashenko::Polygon > malashenko::Figures::filterByParityOfVertexes(bool isEven) const
{
  using namespace std::placeholders;

  std::vector< malashenko::Polygon > res;
  std::copy_if(
      polygons_.cbegin(),
      polygons_.cend(),
      std::back_inserter(res), std::bind(detail::isEvenCheck, _1, isEven)
    );
  return res;
}

std::vector< malashenko::Polygon > malashenko::Figures::filterByAmountOfVertexes(size_t amount) const
{
  using namespace std::placeholders;
  std::vector< malashenko::Polygon > res;
  std::copy_if(
      polygons_.cbegin(),
      polygons_.cend(),
      std::back_inserter(res),
      std::bind(detail::isEqualCheck, _1, amount)
  );
  return res;
}


double malashenko::Figures::getAreaByParity(bool isEven) const
{
  std::vector< Polygon > filteredPolygons = filterByParityOfVertexes(isEven);

  std::vector< double > polygonsAreas = getPolygonsAreas(filteredPolygons);

  return sumArea(polygonsAreas);
}

double malashenko::Figures::getAreaByAmountOfVertexes(size_t amount) const
{
  std::vector< Polygon > filteredPolygons = filterByAmountOfVertexes(amount);

  std::vector< double > polygonsAreas = getPolygonsAreas(filteredPolygons);

  return sumArea(polygonsAreas);
}

double malashenko::Figures::getAverageArea() const
{
  std::vector< double > polygonsAres = getPolygonsAreas(polygons_);

  return sumArea(polygonsAres) / polygonsAres.size();
}

double malashenko::Figures::getMaxArea() const
{
  std::vector< double > polygonsAreas = getPolygonsAreas(polygons_);

  return *std::max_element(polygonsAreas.cbegin(), polygonsAreas.cend());
}


double malashenko::Figures::getMinArea() const
{
  std::vector< double > polygonsAreas = getPolygonsAreas(polygons_);

  return *std::min_element(polygonsAreas.cbegin(), polygonsAreas.cend());
}


size_t malashenko::Figures::getMaxAmoutOfVertexes() const
{
  std::vector< size_t > amountsOfVertexes =  getAmountsOfVertexes(polygons_);

  return *std::max_element(amountsOfVertexes.cbegin(), amountsOfVertexes.cend());
}

size_t malashenko::Figures::getMinAmoutOfVertexes() const
{
  std::vector< size_t > amountsOfVertexes =  getAmountsOfVertexes(polygons_);

  return *std::min_element(amountsOfVertexes.cbegin(), amountsOfVertexes.cend());
}

size_t malashenko::Figures::getAmountOfFiguresByParity(bool isEven) const
{
  std::vector< Polygon > filteredPolygons = filterByParityOfVertexes(isEven);

  return filteredPolygons.size();
}

size_t malashenko::Figures::getAmountOfFiguresByAmountOfVertexes(size_t amount) const
{
  std::vector< Polygon > filteredPolygons = filterByAmountOfVertexes(amount);

  return filteredPolygons.size();
}

void malashenko::Figures::getData(std::istream& in)
{
  Polygon p;

  in >> p;

  if (in.eof() && p.points.empty())
  {
    return;
  }

  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  else if (!p.points.empty())
  {
    polygons_.push_back(std::move(p));
  }

  if (!in.eof())
  {
    getData(in);
  }
}

size_t malashenko::Figures::getAmoutntOfRightShapes() const
{
  std::vector< bool > flags;

  std::transform(
    polygons_.cbegin(),
    polygons_.cend(),
    std::back_inserter(flags),
    hasRightAngleInPolygon
  );

  return std::count(flags.cbegin(), flags.cend(), true);
}

size_t malashenko::Figures::getIntersections(const Polygon& target) const
{
  using namespace std::placeholders;
  return std::count_if(
      polygons_.cbegin(),
      polygons_.cend(),
      std::bind(polygonsIntersect, target, _1)
  );
}


bool malashenko::Figures::isEmpty() const
{
  return polygons_.empty();
}

