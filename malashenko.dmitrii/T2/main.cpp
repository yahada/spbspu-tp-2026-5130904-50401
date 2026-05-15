#include <iostream>
#include "reloads.hpp"
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
  using data_t = malashenko::DataStruct;
  std::vector< data_t > data;
  using iit_t = std::istream_iterator< data_t >;
  std::copy(iit_t {std::cin}, iit_t {}, std::back_inserter(data));

  std::sort(data.begin(), data.end());

  using oit_t = std::ostream_iterator< data_t >;
  std::copy(std::begin(data), std::end(data), oit_t{std::cout, "\n"});
}

