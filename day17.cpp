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

struct Shot {
    long x;
    long y;
    long dx;
    long dy;

    void update() {
        x += dx;
        y += dy;
        if (dx) dx -= abs(dx) / dx;
        --dy;
    }
};

pair<bool, long> hits(Shot s, long leftx, long rightx, long boty, long topy) {
    auto maxy = s.y;
    while (s.y >= boty) {
        if (s.x >= leftx && s.x <= rightx && s.y >= boty && s.y <= topy)
            return {true, maxy};
        s.update();
        maxy = max(maxy, s.y);
    }
    return {false, -1};
}

pair<long, long> findXrange(long leftx, long rightx, long boty, long topy) {
    long dx = 0;
    while (dx * dx + dx < 2 * leftx)
        ++dx;
    return {dx, rightx};
}

void doit(long leftx, long rightx, long boty, long topy) {
    long maxy = boty;
    uint64_t star2 = 0;
    auto[minx, maxx] = findXrange(leftx, rightx, boty, topy);
    for (long x = minx; x <= maxx; ++x) {
        for (long y = boty; y <= 1000; ++y) {
            if (auto[yes, newMaxy] = hits(Shot{0, 0, x, y}, leftx, rightx, boty, topy); yes) {
                maxy = max(maxy, newMaxy);
                ++star2;
            }
        }
    }
    cout << "Day 17 star 1 = " << maxy << "\n";
    cout << "Day 17 star 2 = " << star2 << "\n";
}

//target area: x=56..76, y=-162..-134
void day17() {
    auto star1 = 0;
    auto star2 = 0;

//    hits({0, 0, 7, 2}, 20, 30, -10, -5);
//   doit(20, 30, -10, -5);
    doit(56, 76, -162, -134);
}
// 13041 yes
// star 2 73896 too high