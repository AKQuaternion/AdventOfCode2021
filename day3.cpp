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

vector<int> countOnes(const vector<string> &lines) {
    vector<int> onesCount(lines[0].size());
    for (auto s: lines) {
        for (auto i = 0; i < s.size(); ++i)
            if (s[i] == '1')
                ++onesCount[i];
    }
    return onesCount;
}

int binaryToInt(const string &s) {
    int ret = 0;
    for (auto c: s)
        ret = ret * 2 + (c == '1'?1:0);
    return ret;
}

void day3() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day3.txt");
    string line;
    vector<string> lines;
    while (getline(ifile, line)) {
        lines.push_back(line);
    }
    auto onesCount = countOnes(lines);
    string gamma;
    string epsilon;

    transform(onesCount.begin(),onesCount.end(),back_inserter(gamma),
              [totalCount=lines.size()](int oneCount){return oneCount > totalCount - oneCount ? '1':'0';});
    transform(onesCount.begin(),onesCount.end(),back_inserter(epsilon),
              [totalCount=lines.size()](int oneCount){return oneCount > totalCount - oneCount ? '0':'1';});

    star1 = binaryToInt(gamma) * binaryToInt(epsilon);

    auto Olines = lines;
    auto CO2lines = lines;
    const auto numBits = lines[0].size();
    for (auto bit = 0; bit<numBits; ++bit) {
        auto OonesCount = countOnes(Olines);
        auto mostBit = (OonesCount[bit] >= Olines.size() - OonesCount[bit] ? '1' : '0');
        std::erase_if(Olines, [mostBit, bit](const auto &line) { return line[bit] != mostBit; });

        auto CO2onesCount = countOnes(CO2lines);
        auto leastBit = (CO2onesCount[bit] >= CO2lines.size() - CO2onesCount[bit] ? '0' : '1');
        std::erase_if(CO2lines, [leastBit, bit](const auto &line) { return line[bit] != leastBit; });
    }

    star2 = binaryToInt(Olines.front()) * binaryToInt(CO2lines.front());
    cout << "Day 3 star 1 = " << star1 << "\n";
    cout << "Day 3 star 2 = " << star2 << "\n";
}
