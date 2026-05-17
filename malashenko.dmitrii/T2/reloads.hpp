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

  struct Delimiter
  {
    char exp_;
  };

  struct StringIO
  {
    std::string& ref_;
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

  std::istream& operator>>(std::istream& in, DBLLIT& dl);
  std::istream& operator>>(std::istream& in, RATLSP& rl);
  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::istream& operator>>(std::istream& in, Delimiter&& del);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

  bool operator<(const RATLSP& lhs, const RATLSP& rhs);
  bool operator==(const RATLSP& lhs, const RATLSP& rhs);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
