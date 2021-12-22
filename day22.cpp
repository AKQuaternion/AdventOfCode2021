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

//on x=10..12,y=10..12,z=10..12
//on x=11..13,y=11..13,z=11..13
//off x=9..11,y=9..11,z=9..11
//on x=10..10,y=10..10,z=10..10
void part2(bool cubies[1000][1000][1000]) {

}

void day22() {
    uint64_t star1 = 0;
    uint64_t star2 = 0;
    string fname = "../day22.txt";
    ifstream ifile(fname);
    string line;
    map<tuple<int, int, int>, bool> cubes;
    vector<int64_t> xC, yC, zC;
    while (getline(ifile, line)) {
        char c;
        string onOff;
        int xMin, xMax, yMin, yMax, zMin, zMax;
        istringstream iline(line);
        iline >> onOff >> c >> c >> xMin >> c >> c >> xMax >> c >> c >> c >> yMin >> c >> c >> yMax >> c >> c >> c
              >> zMin >> c >> c >> zMax;
        for (int x = max(-50, xMin); x <= min(50, xMax); ++x)
            for (int y = max(-50, yMin); y <= min(50, yMax); ++y)
                for (int z = max(-50, zMin); z <= min(50, zMax); ++z) {

                    cubes[{x, y, z}] = (onOff == "on");

                }
        xC.push_back(xMin);
        xC.push_back(xMax + 1);
        yC.push_back(yMin);
        yC.push_back(yMax + 1);
        zC.push_back(zMin);
        zC.push_back(zMax + 1);
    }

    star1 = count_if(cubes.begin(), cubes.end(), [](auto x) { return x.second; });
    sort(xC.begin(), xC.end());
    sort(yC.begin(), yC.end());
    sort(zC.begin(), zC.end());

    xC.erase(unique(xC.begin(), xC.end()), xC.end());
    yC.erase(unique(yC.begin(), yC.end()), yC.end());
    zC.erase(unique(zC.begin(), zC.end()), zC.end());
    cout << xC.size() << " " << yC.size() << ' ' << zC.size() << endl;
    vector<vector<std::vector<bool>>> cubies(xC.size(), vector<std::vector<bool>>(yC.size(), std::vector<bool>(zC.size())));
//    bool * base = new bool [1'000'000'000];
//    bool (*cubies)[1000][1000] = reinterpret_cast<bool (*)[1000][1000]>(base);





    ifstream ifile2(fname);

    while (getline(ifile2, line)) {
        char c;
        string onOff;
        int xMin, xMax, yMin, yMax, zMin, zMax;
        istringstream iline(line);
        iline >> onOff >> c >> c >> xMin >> c >> c >> xMax >> c >> c >> c >> yMin >> c >> c >> yMax >> c >> c >> c
              >> zMin >> c >> c >> zMax;

        auto xcl = std::lower_bound(xC.begin(), xC.end(), xMin) - xC.begin();
        auto xcr = std::lower_bound(xC.begin(), xC.end(), xMax + 1) - xC.begin();
        auto ycl = std::lower_bound(yC.begin(), yC.end(), yMin) - yC.begin();
        auto ycr = std::lower_bound(yC.begin(), yC.end(), yMax + 1) - yC.begin();
        auto zcl = std::lower_bound(zC.begin(), zC.end(), zMin) - zC.begin();
        auto zcr = std::lower_bound(zC.begin(), zC.end(), zMax + 1) - zC.begin();

        for (int x = xcl; x < xcr; ++x)
            for (int y = ycl; y < ycr; ++y)
                for (int z = zcl; z < zcr; ++z)
                    cubies[x][y][z] = (onOff == "on");
    }
    for (int x = 0; x < xC.size() - 1; ++x)
        for (int y = 0; y < yC.size() - 1; ++y)
            for (int z = 0; z < zC.size() - 1; ++z)
                if (cubies[x][y][z])
                    star2 += (xC[x + 1] - xC[x]) * (yC[y + 1] - yC[y]) * (zC[z + 1] - zC[z]);


    cout << "Day 22 star 1 = " << star1 << "\n";
    cout << "Day 22 star 2 = " << star2 << "\n";
}
//not 1217868038141411
// 1047690211377206
// 2758514936282235