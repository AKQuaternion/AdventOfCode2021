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

void day5() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day5.txt");
    string line;
    map<pair<int,int>,int> vents;
    while (getline(ifile, line)) {
        char c;
        int x1,x2,y1,y2;
        istringstream iline(line);
        iline >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2;
//        cout << x1 << y1 << x2 << y2 << endl;
        if(x1==x2) {
            int yStart = min(y1,y2);
            int yEnd = max(y1,y2);
            for(int i=yStart; i<=yEnd;++i)
                ++vents[{x1,i}];
        }
        if(y1==y2) {
            int xStart = min(x1,x2);
            int xEnd = max(x1,x2);
            for(int i=xStart; i<=xEnd;++i)
                ++vents[{i,y1}];
        }
    }
    star1 = std::count_if(vents.begin(),vents.end(),[](const auto v){return v.second>1;});

    cout << "Day 5 star 1 = " << star1 << "\n";
    cout << "Day 5 star 2 = " << star2 << "\n";
}
