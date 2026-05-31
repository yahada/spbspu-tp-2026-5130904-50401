#ifndef RELOAD_INPUT
#define RELOAD_INPUT
#include <iostream>
#include <iomanip>
#include "polygon.hpp"
#include "commands.hpp"
#include "figures.hpp"


namespace malashenko
{
  struct Delimiter
  {
    char exp_;
  };

  struct Commands;

  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios< char >& s);
    ~IOguard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
    char fill_;
  };

  std::istream& operator>>(std::istream& in, Point& pt);
  std::istream& operator>>(std::istream& in, Polygon& pol);
  std::istream& operator>>(std::istream& in, Delimiter&& del);
  std::istream& operator>>(std::istream& in, Commands& cmds);

}

#endif
