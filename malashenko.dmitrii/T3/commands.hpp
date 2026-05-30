#ifndef COMMANDS
#define COMMANDS
#include <string>
#include "figures.hpp"

namespace malashenko
{


  void area(std::istream&, std::ostream&, const Figures& figures);
  void max(std::istream&, std::ostream&, const Figures& figures);
  void min(std::istream&, std::ostream&, const Figures& figures);
  void count(std::istream&, std::ostream&, const Figures& figures);
}


#endif