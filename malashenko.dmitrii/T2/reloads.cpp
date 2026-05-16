#include "reloads.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>

namespace malashenko
{
  std::istream& operator>>(std::istream& in, DBLLIT& dl)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);
    double num = 0.0;
    in >> num >> Delimiter{{'d', 'D'}};
    dl.num_ = num;
    return in;
  }

  std::istream& operator>>(std::istream& in, RATLSP& rl)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);
    long long n = 0;
    unsigned long long d = 0;
    using d_t = Delimiter;
    in >> d_t{ {'('}} >> d_t{ {':'}} >> d_t{ {'N'}} >> n >> d_t{ {':'}} >> d_t{ {'D'}} >> d >> d_t{ {':'}} >> d_t{ {')'}};
    rl.num_.first = n;
    rl.num_.second = d;
    return in;
  }

  bool operator<(const RATLSP& lhs, const RATLSP& rhs)
  {
    double num1 = static_cast< double >(lhs.num_.first) / lhs.num_.second;
    double num2 = static_cast< double >(rhs.num_.first) / rhs.num_.second;
    return num1 < num2;
  }

  bool operator==(const RATLSP& lhs, const RATLSP& rhs)
  {
    double num1 = static_cast< double >(lhs.num_.first) / lhs.num_.second;
    double num2 = static_cast< double >(rhs.num_.first) / rhs.num_.second;
    return num1 == num2;
  }

  std::istream& operator>>(std::istream& in, StringIO& str)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);
    return in >> str.ref_;
  }


  std::istream& operator>>(std::istream& in, const Delimiter& del)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);

    checkChar(in, del.exp_);
    return in;
  }

  std::istream& operator>>(std::istream& in, Lable& lbl)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);

    checkStr(in, lbl);

    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& ds)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    IOguard guard(in);

    DataStruct data;
    using d_t = Delimiter;
    using l_t = Lable;
    DBLLIT dl;
    RATLSP rl;
    StringIO str;
    in >> d_t{{'('}} >> d_t{{':'}} >> l_t{"key1"} >> dl >> d_t{{':'}} >> l_t{"key2"} >> rl >> d_t{{':'}} >> l_t{"key3"} >> str >> d_t{{':'}} >> d_t{{')'}};
    if (in)
    {
      data.key1_ = dl;
      data.key2_ = rl;
      data.key3_ = str;
      ds = data;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
  {
    out << "(:key1 " << ds.key1_.num_ << ":key2 (:N " << ds.key2_.num_.first << ":D " << ds.key2_.num_.second << ":):key3 " << '"' << ds.key3_.ref_ << '"' << ":)";
    return out;
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1_.num_ < rhs.key1_.num_)
    {
      return true;
    }
    else if (lhs.key1_.num_ > rhs.key1_.num_)
    {
      return false;
    }
    else
    {
      if (lhs.key2_ < rhs.key2_)
      {
        return true;
      }
      else if (rhs.key2_ < lhs.key2_)
      {
        return false;
      }
      else
      {
        if (lhs.key3_.ref_.length() < rhs.key3_.ref_.length())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    }

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

  void checkChar(std::istream& in, const std::vector< char >& expected)
  {
    char c = 0;
    if (in >> c && std::find(expected.begin(), expected.end(), c) != expected.end())
    {
      in.setstate(std::ios::failbit);
    }
  }

  void checkStr(std::istream& in, Lable& lbl)
  {
    std::string str = "";
    StringIO io{ str };
    if (in >> io && lbl.exp_ != str)
    {
      in.setstate(std::ios::failbit);
    }
    if (io.ref_ == "key1")
    {
      lbl.isBeen_[0] = true;
    }
    else if (io.ref_ == "key2")
    {
    }
  }
}