#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::string;
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
    std::ifstream ifile("../day3.txt");
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

    star1 = stoi(gamma,0,2) * stoi(epsilon,0,2);

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

    star2 = stoi(Olines.front(),0,2) * stoi(CO2lines.front(),0,2);
    std::cout << "Day 3 star 1 = " << star1 << "\n";
    std::cout << "Day 3 star 2 = " << star2 << "\n";
}
