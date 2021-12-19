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

int doOctopus(int i, int j, vector<string> &lines, vector<vector<bool>> &hasFlashed) {
    if (i < 0 || i >= lines.size() || j < 0 || j >= lines.front().size())
        return 0;
    if (hasFlashed[i][j])
        return 0;
    ++lines[i][j];
    int flashes = 0;
    if (lines[i][j] > '9') {
        ++flashes;
        hasFlashed[i][j] = true;
        for (int di = -1; di <= 1; ++di)
            for (int dj = -1; dj <= 1; ++dj)
                flashes += doOctopus(i + di, j + dj, lines, hasFlashed);
    }
    return flashes;
}

int doStep(vector<string> &lines) {
    vector<vector<bool>> hasFlashed(lines.size(), vector<bool>(lines.front().size(), false));

    int flashes = 0;
    for (int i = 0; i < lines.size(); ++i)
        for (int j = 0; j < lines.front().size(); ++j)
            flashes += doOctopus(i, j, lines, hasFlashed);

    for(auto &l:lines)
        for(auto &c:l)
            if (c > '9')
                c = '0';

    return flashes;
}

void day11() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day11.txt");
    vector<string> lines;
    string line;
    while (getline(ifile, line)) {
        lines.push_back(line);
    }

    for (int steps = 0; true; ++steps) {
        cout << steps << ":" << endl;
        star1 += doStep(lines);
        if(all_of(lines.begin(),lines.end(),[](const string &line){return line == string(line.size(),'0');})) {
            star2 = steps+1;
            break;
        }

    }

    cout << "Day 11 star 1 = " << star1 << "\n";
    cout << "Day 11 star 2 = " << star2 << "\n";
}