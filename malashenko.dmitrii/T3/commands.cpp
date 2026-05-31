#include "commands.hpp"
#include <assert.h>
#include <iomanip>

malashenko::Figures* malashenko::Commands::figures = nullptr;

void malashenko::Commands::area(std::istream& in, std::ostream& out)
{

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  double res = -1;
  try
  {
    size_t amountOfVertexes = std::stoull(param);
    res = figures->getAreaByAmountOfVertexes(amountOfVertexes);
  }
  catch(...)
  {}

  if (res == -1)
  {
    if (param == "EVEN" && res )
    {
      res = figures->getAreaByParity(true);
    }
    else if (param == "ODD")
    {
      res = figures->getAreaByParity(false);
    }
    else if (param == "MEAN")
    {
      if (figures->isEmpty())
      {
        throw std::invalid_argument("THERE'RE NO FIGURES");
      }
      res = figures->getAverageArea();
    }
    else
    {
      throw std::invalid_argument("UNKNOWN PARAMETR");
    }
  }
  out << std::fixed << std::setprecision(1);
  out << res << '\n';
}


void malashenko::Commands::max(std::istream& in, std::ostream& out)
{
  if (figures->isEmpty())
  {
    throw std::invalid_argument("THERE'RE NO FIGURES");
  }

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  if (param == "AREA")
  {
    double res = figures->getMaxArea();
    out << std::fixed << std::setprecision(1);
    out << res << '\n';

  }
  else if (param == "VERTEXES")
  {
    out << figures->getMaxAmoutOfVertexes() << '\n';
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }

}

void malashenko::Commands::min(std::istream& in, std::ostream& out)
{
  if (figures->isEmpty())
  {
    throw std::invalid_argument("THERE'RE NO FIGURES");
  }

  assert(figures != nullptr);

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  if (param == "AREA")
  {
    double res = figures->getMinArea();
    out << std::fixed << std::setprecision(1);
    out << res << '\n';
  }
  else if (param == "VERTEXES")
  {
    out << figures->getMinAmoutOfVertexes() << '\n';
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
}


void malashenko::Commands::count(std::istream& in, std::ostream& out)
{

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  try
  {
    size_t amountOfVertexes = std::stoull(param);
    out << figures->getAmountOfFiguresByAmountOfVertexes(amountOfVertexes) << '\n';
    return;
  }
  catch(...)
  {}

  double res = 0;
  if (param == "EVEN")
  {
    res = figures->getAmountOfFiguresByParity(true);
  }
  else if (param == "ODD")
  {
    res = figures->getAmountOfFiguresByParity(false);
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res << '\n';
}



void malashenko::Commands::rightshapes(std::istream&, std::ostream& out)
{
  if (figures->isEmpty())
  {
    throw std::invalid_argument("THERE'RE NO FIGURES");
  }
  out << figures->getAmoutntOfRightShapes() << '\n';
}

void malashenko::Commands::intersections(std::istream& in, std::ostream& out)
{
  if (figures->isEmpty())
  {
    throw std::invalid_argument("THERE'RE NO FIGURES");
  }
  Polygon pol;
  if (!(in >> pol))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }
  out << figures->getIntersections(pol) << '\n';
}
