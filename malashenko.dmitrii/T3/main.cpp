#include <iostream>
#include <iterator>
#include <fstream>
#include "reloads.hpp"
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Argumets problem\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "Can't open the file\n";
    return 1;
  }

  using namespace malashenko;

  Figures figures{};
  figures.getData(input);


  Commands::figures = &figures;

  std::vector< Commands > v;
  using iit_t = std::istream_iterator<Commands>;
  std::copy(
      iit_t{std::cin},
      iit_t{},
      std::back_inserter(v)
  );

  return 0;

}
