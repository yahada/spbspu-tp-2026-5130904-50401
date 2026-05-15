#include "reloads.hpp"
#include <iostream>


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
    in >> num >> Delimiter{'d'};
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
    in >> Lable{ "(:N" } >> n >> Lable{ ":D" } >> d >> Lable{ ":)" };
    rl.num_.first = n;
    rl.num_.second = d;
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO& str)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> str.ref_;
  }


  std::istream& operator>>(std::istream& in, const Delimiter& del)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    checkChar(in, del.exp_);
    return in;
  }

  std::istream& operator>>(std::istream& in, const Lable& lbl)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    checkStr(in, lbl.exp_);
    return in;
  }

  void checkChar(std::istream& in, const char& expected)
  {
    char c = 0;
    if (in >> c && expected != std::towlower(c))
    {
      in.setstate(std::ios::failbit);
    }
  }

  void checkStr(std::istream& in, const std::string& expected)
  {
    std::string str = "";
    StringIO io{ str };
    if (in >> io && expected != str)
    {
      in.setstate(std::ios::failbit);
    }
  }
}