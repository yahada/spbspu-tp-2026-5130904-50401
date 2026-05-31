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
struct PointExtractor
{
  std::istream &in;
  malashenko::Point operator()()
  {
    malashenko::Point p;
    in >> p; // Используем твой существующий operator>>
    if (!in)
    {
      throw std::runtime_error("Parse error");
    }
    return p;
  }
};


malashenko::Point checkNextEnter(std::istream& in, const malashenko::Point& point)
{
  char c = in.peek();
  if (c == '\n')
  {
    in.setstate(std::ios::eofbit);
  }
  return point;
}

std::istream& malashenko::operator>>(std::istream& in, Polygon& polygon)
{
  using namespace std::placeholders;

  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t cnt_points;
  in >> cnt_points;
  if (!in || cnt_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tested;
  auto begin = std::istream_iterator< Point >(in), end = std::istream_iterator< Point >();
  std::transform(begin, end, std::back_inserter(tested), std::bind(checkNextEnter, std::ref(in), _1));

  if (tested.size() == cnt_points && in.eof())
  {
    in.clear();
    polygon.points = std::move(tested);
  }
  else
  {
    in.clear();
    in.setstate(std::ios::failbit);
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
