#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


using Position = std::array<int, 3>;
using ScannerData = std::vector<Position>;
using Distance = std::array<int, 3>;

//
//ostream &operator<<(ostream &os, const array<int, 3> &a) {
//    return os << a[0] << "," << a[1] << "," << a[2] << " ";
//}

int norm(const Distance &d) {
    return abs(d[0]) + abs(d[1]) + abs(d[2]);
}

bool lessByNorm(const Distance &d1, const Distance &d2) {
    return norm(d1) < norm(d2);
}

std::array<int, 3> operator-(const std::array<int, 3> &lhs, const std::array<int, 3> &rhs) {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]};
}

void transformIt(Position &a, int t) {
    assert(t >= 0 & t < 24);

    switch (t) {
        case 0:
            a = {a[0], a[1], a[2]}; break; //even
        case 1:
            a = {a[0], a[2], -a[1]}; break; //odd
        case 2:
            a = {a[1], a[0], -a[2]}; break; //odd
        case 3:
            a = {a[1], a[2], a[0]}; break; //even
        case 4:
            a = {a[2], a[0], a[1]}; break; //even
        case 5:
            a = {a[2], a[1], -a[0]}; break;  //odd

        case 6:
            a = {-a[0], a[1], -a[2]}; break; //even
        case 7:
            a = {-a[0], a[2], a[1]}; break; //odd
        case 8:
            a = {-a[1], a[0], a[2]}; break; //odd
        case 9:
            a = {-a[1], a[2], -a[0]}; break; //even
        case 10:
            a = {-a[2], a[0], -a[1]}; break; //even
        case 11:
            a = {-a[2], a[1], a[0]}; break;  //odd

        case 12:
            a = {a[0], -a[1], -a[2]}; break; //even
        case 13:
            a = {a[0], -a[2], a[1]}; break; //odd
        case 14:
            a = {a[1], -a[0], a[2]}; break; //odd
        case 15:
            a = {a[1], -a[2], -a[0]}; break; //even
        case 16:
            a = {a[2], -a[0], -a[1]}; break; //even
        case 17:
            a = {a[2], -a[1], a[0]}; break;  //odd

        case 18:
            a = {-a[0], -a[1], a[2]}; break; //even
        case 19:
            a = {-a[0], -a[2], -a[1]}; break; //odd
        case 20:
            a = {-a[1], -a[0], -a[2]}; break; //odd
        case 21:
            a = {-a[1], -a[2], a[0]}; break; //even
        case 22:
            a = {-a[2], -a[0], a[1]}; break; //even
        case 23:
            a = {-a[2], -a[1], -a[0]}; break;  //odd
        default:
            throw 1;
    };
}

Distance distance(const Position &p1, const Position &p2) {
    return (p1 - p2);
}

std::vector<Distance> distances(const std::vector<Position> &scanner) {
    std::vector<Distance> scannerDistances;
    scannerDistances.reserve(scanner.size() * (scanner.size() + 1) / 2);
    for (int i = 0; i < scanner.size(); ++i)
        for (int j = i + 1; j < scanner.size(); ++j)
            scannerDistances.push_back(distance(scanner[i], scanner[j]));
    return scannerDistances;
}

std::vector<Distance> common(std::vector<Distance> &a, std::vector<Distance> &b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    std::vector<Distance> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
    return result;
}

void transformThem(std::vector<Position> &a, int t) {
    for (auto &p: a)
        transformIt(p, t);
    sort(a.begin(), a.end());
}

std::vector <Position> translate(const std::vector <Position> &a, Distance t) {
    std::vector <std::array<int, 3>> out;
    for (const auto &x: a)
        out.push_back({x[0] + t[0], x[1] + t[1], x[2] + t[2]});
    return out;
}

int findOriginPoint(const std::vector <Position> &points, const Distance &d) {
    for (int i = 0; i < points.size(); ++i)
        for (int j = i + 1; j < points.size(); ++j)
            if (points[i] - points[j] == d)
                return i;
    throw 1;
}

std::vector <Position> scannerPositions;

bool alignSecond(const std::vector <Position> &base, std::vector <Position> &mod) {
    for (int t = 0; t < 24; ++t) {
        auto potential = mod;
        transformThem(potential, t);
        auto baseDistances = distances(base);
        auto potentialDistances = distances(potential);
        auto commonPoints = common(baseDistances, potentialDistances);
        if (commonPoints.size() >= 66) { //2 works!!!
            auto bi = findOriginPoint(base, commonPoints.front());
            auto pi = findOriginPoint(potential, commonPoints.front());
//            cout << "Translate by " << base[bi] - potential[pi] << endl;
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
    std::ifstream ifile("../day19.txt");
    std::string line;
    std::vector <ScannerData> data;
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
            std::istringstream iline(line);
            iline >> x >> c >> y >> c >> z;
            data.back().push_back({x, y, z});
        }
        sort(data.back().begin(), data.back().end());
//        cout << "Scanner " << data.size() << " has this many beacons: " << data.back().size() << endl;
    }

    scannerPositions.push_back({0, 0, 0});
    std::vector<bool> processed(data.size(), false);
    std::queue<int> indexToProcess;
    indexToProcess.push(0);



    while (!indexToProcess.empty()) {
        auto i = indexToProcess.front();
        indexToProcess.pop();
        if (processed[i])
            continue;
        processed[i] = true;
        for (int j = 0; j < data.size(); ++j) {
            if (!processed[j] && alignSecond(data[i], data[j])) {
                indexToProcess.push(j);
//                cout << i << " to " << j << endl;
            }
        }
    }
    std::set <Position> beacons;
    for (const auto &scanner: data)
        for (const auto &b: scanner)
            beacons.insert(b);
    star1 = beacons.size();

//    cout << scannerPositions.size() << endl;

    Distance max = {0, 0, 0};
    for (int i = 0; i < scannerPositions.size(); ++i)
        for (int j = 0; j < scannerPositions.size(); ++j) {
            if (lessByNorm(max, distance(scannerPositions[i], scannerPositions[j])))
                max = distance(scannerPositions[i], scannerPositions[j]);
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


    std::cout << "Day 19 star 1 = " << star1 << "\n";
    std::cout << "Day 19 star 2 = " << star2 << "\n";
}
