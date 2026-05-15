#ifndef RELOADS
#define RELOADS
#include <iostream>
#include <iomanip>
#include <string>

namespace malashenko
{
  struct DBLLIT
  {
    double num_;
  };

  struct RATLSP
  {
    std::pair< long long, unsigned long long > num_;
  };

  struct DelimiterIO
  {
    std::string expected;
    char& last;
  };

  struct StringIO
  {
    std::string& ref_;
  };

    struct LableIO
  {
    std::string exp_;
  };


  struct DataStruct
  {
    DBLLIT key1_;
    RATLSP key2_;
    std::string key3_;
  };

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

  std::istream& operator>>(std::istream& is, DBLLIT& dl);
  std::istream& operator>>(std::istream& is, RATLSP& rl);
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::istream& operator>>(std::istream& is, DelimiterIO& del);
  std::istream& operator>>(std::istream& is, StringIO& str);
  char check(std::istream& is, const std::string& expected);
}

#endif