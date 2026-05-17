#include "reloads.hpp"
#include <algorithm>
#include <cstring>

namespace malashenko
{
  std::istream& operator>>(std::istream& in, DBLLIT& dl)
  {
    double num = 0.0;
    if (!(in >> num))
    {
      return in;
    }

    char c = 0;
    if (!(in >> c) || (c != 'd' && c != 'D'))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    dl.num_ = num;
    return in;
  }

  std::istream& operator>>(std::istream& in, Delimiter&& del)
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

  std::istream& operator>>(std::istream& in, RATLSP& rl)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    long long n = 0;
    unsigned long long d = 0;
    using d_t = Delimiter;

    in >> d_t{'('} >> d_t{':'} >> d_t{'N'} >> n >> d_t{':'} >> d_t{'D'} >> d >> d_t{':'} >> d_t{')'};

    if (!in || d == 0)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    rl.num_.first = n;
    rl.num_.second = d;
    return in;
  }

  bool operator<(const RATLSP& lhs, const RATLSP& rhs)
  {
    return lhs.num_.first * rhs.num_.second < rhs.num_.first * lhs.num_.second;
  }

  bool operator==(const RATLSP& lhs, const RATLSP& rhs)
  {
    return lhs.num_.first * rhs.num_.second == rhs.num_.first * lhs.num_.second;

  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> Delimiter{'"'}, dest.ref_, '"');
  }


  std::istream& operator>>(std::istream& in, DataStruct& ds)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    DBLLIT k1{};
    RATLSP k2{};
    std::string k3{};

    bool got1 = false, got2 = false, got3 = false;

    in >> Delimiter{'('} >> Delimiter{':'};

    while (in && in.peek() != ')')
    {
      std::string key;
      in >> key;

      if (!in)
      {
        return in;
      }

      if (key == "key1")
      {
        in >> k1;
        got1 = true;
      }
      else if (key == "key2")
      {
        in >> k2;
        got2 = true;
      }
      else if (key == "key3")
      {
        in >> StringIO{k3};
        got3 = true;
      }
      else
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      in >> Delimiter{':'};
    }

    in >> Delimiter{')'};

    if (!in || !got1 || !got2 || !got3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    ds.key1_ = k1;
    ds.key2_ = k2;
    ds.key3_ = k3;

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
  {
    IOguard guard(out);
    out << "(:key1 " << ds.key1_.num_;
    if (static_cast<long long>(ds.key1_.num_) == ds.key1_.num_)
    {
      out << ".0";
    }
    out << "d:key2 (:N " << ds.key2_.num_.first << ":D " << ds.key2_.num_.second;
    out << ":):key3 " << '"' << ds.key3_ << '"' << ":)";
    return out;
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1_.num_ != rhs.key1_.num_)
    {
      return lhs.key1_.num_ < rhs.key1_.num_;
    }

    if (!(lhs.key2_ == rhs.key2_))
    {
      return lhs.key2_ < rhs.key2_;
    }

    return lhs.key3_.size() < rhs.key3_.size();
  }


  IOguard::IOguard(std::basic_ios< char >& s):
    s_(s),
    width_(s.width()),
    precision_(s.precision()),
    fmt_(s.flags()),
    fill_(s.fill())
  {}

  IOguard::~IOguard()
  {
    s_.precision(precision_);
    s_.width(width_);
    s_.flags(fmt_);
    s_.fill(fill_);
  }
}
