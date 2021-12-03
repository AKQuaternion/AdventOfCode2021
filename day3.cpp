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

void day3() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day3.txt");
    string line;
    vector<int> onesCount;
    auto totalCount = 0;
    while (getline(ifile, line)) {
        string s;
        int i;
        int x;
        int y;
        char c;
        double d;
        istringstream iline(line);
        iline >> s;
        if(onesCount.empty())
            onesCount.resize(s.size());
        else
            if(onesCount.size() != s.size())
                throw 1;
        for(auto i=0;i<s.size();++i)
            if(s[i]=='1')
                ++onesCount[i];
        ++totalCount;
    }
    auto gamma = 0;
    auto epsilon = 0;
    for(auto i:onesCount) {
        auto gammaBit = i>totalCount-i;
        gamma = gamma*2 + gammaBit;
        epsilon = epsilon*2 + (1-gammaBit);
    }
    star1 = gamma*epsilon;

    cout << "Day 3 star 1 = " << star1 << "\n";
    cout << "Day 3 star 2 = " << star2 << "\n";
}
