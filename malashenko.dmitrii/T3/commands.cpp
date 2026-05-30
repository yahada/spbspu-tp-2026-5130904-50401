#include "commands.hpp"
#include <assert.h>


malashenko::Figures* malashenko::Commands::figures = nullptr;

void malashenko::Commands::area(std::istream& in, std::ostream& out)
{
  assert(figures != nullptr);
  std::cout << figures << '\n';
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  try
  {
    size_t amountOfVertexes = std::stoull(param);
    out << figures->getAreaByAmountOfVertexes(amountOfVertexes) << '\n';
    return;
  }
  catch(...)
  {}

  double res = 0;
  if (param == "EVEN")
  {
    res = figures->getAreaByParity(true);
  }
  else if (param == "ODD")
  {
    res = figures->getAreaByParity(false);
  }
  else if (param == "MEAN")
  {
    res = figures->getAverageArea();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res << '\n';
}


void malashenko::Commands::max(std::istream& in, std::ostream& out)
{
  assert(figures != nullptr);
  std::cout << figures << '\n';

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  double res = 0;
  if (param == "AREA")
  {
    res = figures->getMaxArea();
  }
  else if (param == "VERTEXES")
  {
    res = figures->getMaxAmoutOfVertexes();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res << '\n';
}

void malashenko::Commands::min(std::istream& in, std::ostream& out)
{
  assert(figures != nullptr);
  std::cout << figures << '\n';

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  double res = 0;
  if (param == "AREA")
  {
    res = figures->getMinArea();
  }
  else if (param == "VERTEXES")
  {
    res = figures->getMinAmoutOfVertexes();
  }
  else
  {
    throw std::invalid_argument("UNKNOWN PARAMETR");
  }
  out << res << '\n';
}


void malashenko::Commands::count(std::istream& in, std::ostream& out)
{
  assert(figures != nullptr);
  std::cout << figures << '\n';

  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("INPUT PROBLEMS");
  }

  try
  {
    size_t amountOfVertexes = std::stoull(param);
    out << figures->getAmountOfFiguresByAmountOfVertexes(amountOfVertexes);
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


std::istream& malashenko::operator>>(std::istream& in, Commands& cmds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string cmd;
  if (!(in >> cmd))
  {
    return in;
  }




  using cmd_t = void (Commands::*)(std::istream&, std::ostream&);
  static std::map< std::string, cmd_t > commands
  {
    {"AREA", &Commands::area},
    {"MAX", &Commands::max},
    {"MIN", &Commands::min},
    {"COUNT", &Commands::count}
  };


  try
  {
    (cmds.*commands.at(cmd))(in, std::cout);
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>" << '\n';
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return in;
}