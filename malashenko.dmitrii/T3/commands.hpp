#ifndef COMMANDS
#define COMMANDS
#include <string>
#include <map>
#include <limits>
#include "figures.hpp"
#include "reloads.hpp"


namespace malashenko
{
  class Figures;

  struct Commands {
    static Figures* figures;

    Commands() = default;
    void area(std::istream&, std::ostream&);
    void max(std::istream&, std::ostream&);
    void min(std::istream&, std::ostream&);
    void count(std::istream&, std::ostream&);
    void rightshapes(std::istream&, std::ostream&);
    void intersections(std::istream&, std::ostream&);
  };
}


#endif
