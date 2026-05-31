#ifndef FIGURES
#define FIGURES
#include "polygon.hpp"
#include "reloads.hpp"

namespace malashenko
{
  class Figures {
  public:
    void getData(std::istream& in);

    double getAreaByParity(bool isEven) const;
    double getAreaByAmountOfVertexes(size_t amount) const;
    double getAverageArea() const;
    double getMaxArea() const;
    double getMinArea() const;
    size_t getMaxAmoutOfVertexes() const;
    size_t getMinAmoutOfVertexes() const;
    size_t getAmountOfFiguresByParity(bool isEven) const;
    size_t getAmountOfFiguresByAmountOfVertexes(size_t amount) const;
    size_t getAmoutntOfRightShapes() const;
    size_t getIntersections(const Polygon& target) const;
    bool isEmpty() const;

  // private:
    std::vector< Polygon > polygons_;
    std::vector< double > getPolygonsAreas(const std::vector< Polygon >& polygons) const;
    std::vector< size_t > getAmountsOfVertexes(const std::vector< Polygon >& polygons) const;
    std::vector< Polygon > filterByParityOfVertexes(bool parity) const;
    std::vector< Polygon > filterByAmountOfVertexes(size_t amount) const;
  };


  namespace detail
  {
    bool isEvenCheck(const Polygon& pol, bool isEven);
    bool isEqualCheck(const Polygon& pol, size_t amount);
    size_t vertexes(const Polygon& pol);
  }

}

#endif
