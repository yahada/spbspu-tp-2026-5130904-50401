#ifndef RELOADS
#define RELOADS
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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
    std::vector< char > exp_;
  };

  struct StringIO
  {
    std::string ref_;
  };

  struct Lable
  {
    std::string exp_;
    bool isBeen_[3];
  };

  struct DataStruct
  {
    DBLLIT key1_;
    RATLSP key2_;
    StringIO key3_;
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
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
  std::istream& operator>>(std::istream& in, const Delimiter& del);
  std::istream& operator>>(std::istream& in, StringIO&& str);
  std::istream& operator>>(std::istream& in, Lable&& str);

  bool operator<(const RATLSP& lhs, const RATLSP& rhs);
  bool operator==(const DBLLIT& lhs, const DBLLIT& rhs);

  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  void checkChar(std::istream& in, const std::vector< char >& expected);
  void checkStr(std::istream& in, Lable& lbl);
}

#endif