//
// Created by Chris Hartman on 12/22/21.
//
#include <algorithm>
#include <array>
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
#include <limits>

using std::abs;
using std::array;
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

struct OctNode {
    int x1;
    int x2;
    int y1;
    int y2;
    int z1;
    int z2;
    bool on;
    array<std::unique_ptr<OctNode>,2> children;
    void reboot(int cx1, int cx2, int cy1, int cy2, int cz1, int cz2, bool con) {
//        if(cx1>=x2 || cx2 <= x1 || cy1 >= y2 || cy2 <= y1 || cz1 >= z2 || cz2 <= z1)
//            return;
        if(cx1 > x1 && cx1 < x2) {
            children[0] = std::make_unique<OctNode>(OctNode{x1,cx1,y1,y2,z1,z2,on});
            children[0] = std::make_unique<OctNode>(OctNode{cx1,x2,y1,y2,z1,z2,on});
        }
    }
};


void day22alt() {
    auto iMin = std::numeric_limits<int>::min();
    auto iMax = std::numeric_limits<int>::max();
    OctNode root = {iMin,iMax,iMin,iMax,iMin,iMax,false};

}