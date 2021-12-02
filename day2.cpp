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

void day2() {
    auto star1 = 0;
    auto star2 = 0;
    std::ifstream ifile("../day2.txt");

    auto hpos=0;
    auto depth=0;
    string line;
    while (getline(ifile, line)) {
        string s;
        int i;
        istringstream iline(line);
        iline >> s >> i;
        cout << s << i << endl;
        if(s=="up")
            depth -= i;
        else if (s=="down")
            depth += i;
        else if (s == "forward")
            hpos += i;
        else throw 1;
    }
    star1 = hpos*depth;

    std::cout << "Day 2 star 1 = " << star1 << "\n";
    std::cout << "Day 2 star 2 = " << star2 << "\n";
}
