#include "reloads.hpp"
#include <iterator>
#include <limits>
#include <map>


malashenko::IOguard::IOguard(std::basic_ios< char >& s):
  s_(s),
  width_(s.width()),
  precision_(s.precision()),
  fmt_(s.flags()),
  fill_(s.fill())
{}

malashenko::IOguard::~IOguard()
{
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(fmt_);
  s_.fill(fill_);
}


std::istream& malashenko::operator>>(std::istream& in, Delimiter&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  IOguard guard(in);
  char c = 0;
  in >> c;
  if (in && c != del.exp_)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& malashenko::operator>>(std::istream& in, Point& pt)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  IOguard guard(in);

  int x = 0, y = 0;
  using d_t = Delimiter;
  in >> d_t{'('} >> x >> d_t{';'} >> y >> d_t{')'};
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  pt.x = x;
  pt.y = y;
  return in;
}

std::istream& malashenko::operator>>(std::istream& in, Polygon& pol)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  IOguard guard(in);

  size_t n = 0;
  in >> n;

  if (!in || n < 3)
  {
    in.setstate(std::ios::failbit);
    pol.points.clear();
    return in;
  }

  std::vector< Point > tmp;
  tmp.reserve(n);

  using it_t = std::istream_iterator<Point>;
  std::copy_n(it_t{in}, n, std::back_inserter(tmp));

  if (in && tmp.size() == n)
  {
    pol.points = std::move(tmp);
  }
  else
  {
    in.setstate(std::ios::failbit);
    pol.points.clear();
  }

  return in;
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
    {"COUNT", &Commands::count},
    {"RIGHTSHAPES", &Commands::rightshapes},
    {"INTERSECTIONS", &Commands::intersections}

  };

  try
  {
    (cmds.*commands.at(cmd))(in, std::cout);
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>" << '\n';
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return in;
}
