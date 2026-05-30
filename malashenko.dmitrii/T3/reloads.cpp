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

  size_t n = 0;
  in >> n;
  if (!in || n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  pol.points.resize(n);

  std::copy_n(std::istream_iterator< Point >(in), n, pol.points.begin());

  return in;
}




