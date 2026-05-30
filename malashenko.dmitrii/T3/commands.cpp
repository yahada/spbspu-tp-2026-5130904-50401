#include "commands.hpp"


void malashenko::area(std::istream& in, std::ostream& out, const Figures& figures)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  try
  {
    size_t amountOfVertexes = std::stoull(param);
    out << figures.getAreaByAmountOfVertexes(amountOfVertexes);
    return;
  }
  catch(...)
  {}

  double res = 0;
  if (param == "EVEN")
  {
    res = figures.getAreaByParity(true);
  }
  else if (param == "ODD")
  {
    res = figures.getAreaByParity(false);
  }
  else if (param == "MEAN")
  {
    res = figures.getAverageArea();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res;
}


void malashenko::max(std::istream& in, std::ostream& out, const Figures& figures)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  double res = 0;
  if (param == "AREA")
  {
    res = figures.getMaxArea();
  }
  else if (param == "VERTEXES")
  {
    res = figures.getMaxAmoutOfVertexes();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res;
}

void malashenko::min(std::istream& in, std::ostream& out, const Figures& figures)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  double res = 0;
  if (param == "AREA")
  {
    res = figures.getMinArea();
  }
  else if (param == "VERTEXES")
  {
    res = figures.getMinAmoutOfVertexes();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res;
}


void malashenko::count(std::istream& in, std::ostream& out, const Figures& figures)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  try
  {
    size_t amountOfVertexes = std::stoull(param);
    out << figures.getAmountOfFiguresByAmountOfVertexes(amountOfVertexes);
    return;
  }
  catch(...)
  {}

  double res = 0;
  if (param == "EVEN")
  {
    res = figures.getAmountOfFiguresByParity(true);
  }
  else if (param == "ODD")
  {
    res = figures.getAmountOfFiguresByParity(false);
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res;
}


