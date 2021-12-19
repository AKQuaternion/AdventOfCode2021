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

int flood(int i, int j, vector<string> &data) {
    int filled = 1;
    const auto &here = data[i][j];
    if(here=='9')
        return 0;
    if (i > 0 && data[i - 1][j] > here)
        filled += flood(i - 1, j, data);
    if (i < data.size() - 1 && data[i + 1][j] > here)
        filled += flood(i + 1, j, data);
    if (j > 0 && data[i][j - 1] > here)
        filled += flood(i , j-1, data);
    if (j < data.front().size() - 1 && data[i][j + 1] > here)
        filled += flood(i , j+1, data);

    data[i][j] = 0;
    return filled;
}

void day9() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day9.txt");
    string line;
    vector<string> data;
    while (getline(ifile, line)) {
        data.push_back(line);
    }

    auto isLow = [&data](int i, int j) {
        bool result = true;
        auto &here = data[i][j];
        if (i > 0 && data[i - 1][j] <= here)
            result = false;
        if (i < data.size() - 1 && data[i + 1][j] <= here)
            result = false;
        if (j > 0 && data[i][j - 1] <= here)
            result = false;
        if (j < data.front().size() - 1 && data[i][j + 1] <= here)
            result = false;
        return result;
    };

    vector<pair<int, int>> lowPoints;
    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data.front().size(); ++j) {
            if (isLow(i, j)) {
                star1 += data[i][j] - '0' + 1;
                lowPoints.push_back({i, j});
            }
        }

    vector<int> sizes;

    for (auto[i, j]: lowPoints)
        sizes.push_back(flood(i, j, data));

    sort(sizes.begin(),sizes.end(),std::greater());
    star2 = sizes[0]*sizes[1]*sizes[2];

    cout << "Day 9 star 1 = " << star1 << "\n";
    cout << "Day 9 star 2 = " << star2 << "\n";
}
