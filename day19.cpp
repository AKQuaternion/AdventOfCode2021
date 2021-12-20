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
using std::ostream;
using std::pair;
using std::set;
using std::queue;
using std::sqrt;
using std::string;
using std::forward_as_tuple;
using std::tie;
using std::tuple;
using std::sort;
using std::swap;
using std::vector;

using Position = array<int, 3>;
using ScannerData = vector<Position>;
using Distance = array<int, 3>;


ostream &operator<<(ostream &os, const array<int, 3> &a) {
    return os << a[0] << "," << a[1] << "," << a[2] << " ";
}

int norm(const Distance &d) {
    return abs(d[0]) + abs(d[1]) + abs(d[2]);
}

bool lessByNorm(const Distance &d1, const Distance &d2) {
    return norm(d1) < norm(d2);
}

array<int, 3> operator-(const array<int, 3> &lhs, const array<int, 3> &rhs) {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]};
}

vector<array<int, 3>> permutations = {
        {0, 1, 2}, //even
        {0, 2, 1}, //odd
        {1, 0, 2}, //odd
        {1, 2, 0}, //even
        {2, 0, 1}, //even
        {2, 1, 0}  //odd
};

array<int, 3> transformIt(const array<int, 3> &a, int t) {
    assert(t >= 0 & t < 24);

    auto x = a[0];
    auto y = a[1];
    auto z = a[2];

    vector<array<int, 3>> transformations{
            {x,  y,  z}, //even
            {x,  z,  -y}, //odd
            {y,  x,  -z}, //odd
            {y,  z,  x}, //even
            {z,  x,  y}, //even
            {z,  y,  -x},  //odd

            {-x, y,  -z}, //even
            {-x, z,  y}, //odd
            {-y, x,  z}, //odd
            {-y, z,  -x}, //even
            {-z, x,  -y}, //even
            {-z, y,  x},  //odd

            {x,  -y, -z}, //even
            {x,  -z, y}, //odd
            {y,  -x, z}, //odd
            {y,  -z, -x}, //even
            {z,  -x, -y}, //even
            {z,  -y, x},  //odd

            {-x, -y, z}, //even
            {-x, -z, -y}, //odd
            {-y, -x, -z}, //odd
            {-y, -z, x}, //even
            {-z, -x, y}, //even
            {-z, -y, -x}  //odd
    };
    return transformations[t];
}

Distance distance(const Position &p1, const Position &p2) {
    return (p1 - p2);
}

vector<Distance> distances(vector<Position> scanner) {
    vector<Distance> scannerDistances;
    for (int i = 0; i < scanner.size(); ++i) {
        for (int j = i + 1; j < scanner.size(); ++j) {
            scannerDistances.push_back(distance(scanner[i], scanner[j]));
        }
    }
//    sort(scannerDistances.begin(), scannerDistances.end(), lessByNorm);

    return scannerDistances;
}

vector<array<int, 3>> common(vector<array<int, 3>> a, vector<array<int, 3>> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<array<int, 3>> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
    return result;
}

vector<array<int, 3>> transformThem(const vector<array<int, 3>> &a, int t) {
    vector<array<int, 3>> out;
    for (auto p: a)
        out.push_back(transformIt(p, t));
    sort(out.begin(), out.end());
    return out;
}

vector<array<int, 3>> translate(const vector<array<int, 3>> &a, array<int, 3> t) {
    vector<array<int, 3>> out;
    for (const auto &x: a)
        out.push_back({x[0] + t[0], x[1] + t[1], x[2] + t[2]});
    return out;
}

int findOriginPoint(const vector<Position> &points, const Distance &d) {
    for (int i = 0; i < points.size(); ++i)
        for (int j = i + 1; j < points.size(); ++j)
            if (points[i] - points[j] == d)
                return i;
    throw 1;
}

vector<Position > scannerPositions;

bool alignSecond(const vector<Position> &base, vector<Position> &mod) {
    for (int t = 0; t < 24; ++t) {
        auto potential = transformThem(mod, t);
        auto baseDistances = distances(base);
        auto potentialDistances = distances(potential);
        auto commonPoints = common(baseDistances, potentialDistances);
        if (commonPoints.size() >= 66) {
            auto bi = findOriginPoint(base, commonPoints.front());
            auto pi = findOriginPoint(potential, commonPoints.front());
            cout << "Translate by " << base[bi] - potential[pi] << endl;
            scannerPositions.push_back(base[bi] - potential[pi]);
            mod = translate(potential, base[bi] - potential[pi]);

            return true;
        }
    }
    return false;
}

void day19() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day19.txt");
    string line;
    vector<ScannerData> data;
    while (getline(ifile, line)) {//scanner ID line
        data.emplace_back();
        while (true) {
            getline(ifile, line);
            if (line.empty())
                break;
            int x;
            int y;
            int z;
            char c;
            istringstream iline(line);
            iline >> x >> c >> y >> c >> z;
            data.back().push_back({x, y, z});
        }
        sort(data.back().begin(), data.back().end());
        cout << "Scanner " << data.size() << " has this many beacons: " << data.back().size() << endl;
    }

//    for (const auto &scanner: data) {
//        auto scannerDistances = distances(scanner);
//        for (int i = 0; i < 5; ++i)
//            cout << scannerDistances[i] << endl;
//        cout << endl;
//    }

//    alignSecond(data[0], data[1]);
//    alignSecond(data[1], data[4]);
//    alignSecond(data[4], data[2]);
//    alignSecond(data[1], data[3]);

    scannerPositions.push_back({0,0,0});
    vector<bool> processed(data.size(), false);
    queue<int> indexToProcess;
    indexToProcess.push(0);

    while (!indexToProcess.empty()) {
        auto i = indexToProcess.front();
        indexToProcess.pop();
        if(processed[i])
            continue;
        processed[i] = true;
        for(int j=0;j<data.size();++j) {
            if(!processed[j] && alignSecond(data[i],data[j])) {
                indexToProcess.push(j);
                cout << i << " to " << j << endl;
            }
        }
    }
    set<Position> beacons;
    for (const auto &scanner: data)
        for (const auto &b: scanner)
            beacons.insert(b);
    star1 = beacons.size();

    cout << scannerPositions.size() << endl;

    Distance max = {0,0,0};
    for(int i=0;i<scannerPositions.size();++i)
        for(int j=0;j<scannerPositions.size();++j) {
            if(lessByNorm(max,distance(scannerPositions[i],scannerPositions[j])))
                max = distance(scannerPositions[i],scannerPositions[j]);
        }
    star2 = norm(max);
//    alignSecond(data[1], data[4]);
//    auto d1 = transformThem(data[1], 6);
//
//    auto dd1 = distances(d1);
//    auto dd0 = distances(data[0]);
//    auto count = common(dd1,dd0);
//
//
//    auto td1 = translate(d1, {68, -1246, -43});
//    auto dtd1 = distances(td1);
////    auto count2 = common(dtd1,dd0);
//    sort(data[0].begin(),data[0].end());
//    sort(td1.begin(),td1.end());
//    auto count2 = common(distances(data[0]),distances(td1));
//    auto commonPoints = common(data[0],td1);
////    sort(tdata1.begin(), tdata1.end());
////    sort(data[0].begin(), data[0].end());
////    for (int i = 0; i < tdata1.size(); ++i)
////        cout << tdata1[i] << "   " << data[0][i] << endl;


    cout << "Day 19 star 1 = " << star1 << "\n";
    cout << "Day 19 star 2 = " << star2 << "\n";
}
