#include "figures.hpp"
#include <iterator>

std::vector< double > malashenko::Figures::getPolygonsAreas(const std::vector< Polygon >& polygons) const
{
  std::vector< std::vector< Triangle > > triangles(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), triangles.begin(), convertToTriangles);
  std::vector< std::vector< double > > areas(polygons.size());
  std::transform(triangles.cbegin(), triangles.cend(), areas.begin(), convertToAreas);

  std::vector< double > res(polygons.size());
  std::transform(areas.cbegin(), areas.cend(), res.begin(), sumArea);
  return res;
}

std::vector< size_t > malashenko::Figures::getAmountsOfVertexes(const std::vector< Polygon >& polygons) const
{
  std::vector< size_t > res;
  std::transform(polygons.cbegin(), polygons.cend(), res.begin(), vertexes);
  return res;
}

size_t malashenko::vertexes(const Polygon& pol)
{
  return pol.points.size();
}


bool malashenko::isEvenCheck(const Polygon& pol, bool isEven)
{
  bool check = pol.points.size() % 2 == 0;
  return isEven ? check : !check;
}


bool malashenko::isEqualCheck(const Polygon& pol, size_t amount)
{
  return pol.points.size() == amount;
}


std::vector< malashenko::Polygon > malashenko::Figures::filterByParityOfVertexes(bool isEven) const
{
  using namespace std::placeholders;

  std::vector< malashenko::Polygon > res;
  std::copy_if(polygons_.cbegin(), polygons_.cend(), res.begin(), std::bind(isEvenCheck, _1, isEven));
  return res;
}

std::vector< malashenko::Polygon > malashenko::Figures::filterByAmountOfVertexes(size_t amount) const
{
  using namespace std::placeholders;
  std::vector< malashenko::Polygon > res;
  std::copy_if(polygons_.cbegin(), polygons_.cend(), res.begin(), std::bind(isEqualCheck, _1, amount));
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
  std::vector< Polygon > polygons;

  std::copy(std::istream_iterator< Polygon >(in),
            std::istream_iterator< Polygon >(),
            std::back_inserter(polygons));
  polygons_ = polygons;
}
