#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

int main() {
  List<int> list;

  for (int i = 1; i <= 8; i++)
      list.insertBack(i);

  list.tripleRotate();
  list.tripleRotate();
  list.reverse();
  std::cout << "sdf" << std::endl;
  stringstream s;

  list.print(s);
  std::cout << s.str() << std::endl;
  return 0;
}
