#ifndef FIGURES
#define FIGURES
#include "polygon.hpp"

namespace malashenko
{
  class Figures {
  public:
    double getAreaByParity(bool isEven);
  private:
    std::vector< Polygon > polygons_;
  };

}

#endif