#ifndef COMMANDS
#define COMMANDS
#include <string>
#include "figures.hpp"

namespace malashenko
{
  void area(std::istream&, std::ostream&, const Figures&);
  void max(std::istream&, std::ostream&, const Figures&);
  void min(std::istream&, std::ostream&, const Figures&);
  void count(std::istream&, std::ostream&, const Figures&);
}


#endif