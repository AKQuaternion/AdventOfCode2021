#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using std::abs;
using std::ceil;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::pair;
using std::set;
using std::queue;
using std::sqrt;
using std::string;
using std::forward_as_tuple;
using std::tie;
using std::tuple;
using std::swap;
using std::vector;

void day16() {
   auto star1 = 0;
   auto star2 = 0;
   ifstream ifile("../day16.txt");
   string line;
   while (getline(ifile, line)) {
      string s;
      int i;
      int x;
      int y;
      char c;
      double d;
      istringstream iline(line);
      iline >> s;
   }

   cout << "Day 16 star 1 = " << star1 << "\n";
   cout << "Day 16 star 2 = " << star2 << "\n";
}
