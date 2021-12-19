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
using Position = pair<int, int>;

set<Position> foldOnX(const set<Position> &dots, int foldx) {
    set<Position> newDots;
    for (auto[x, y]: dots)
        newDots.insert({x < foldx ? x : foldx - (x - foldx), y});
    return newDots;
}

set<Position> foldOnY(const set<Position> &dots, int foldy) {
    set<Position> newDots;
    for (auto[x, y]: dots)
        newDots.insert({x, y < foldy ? y : foldy - (y - foldy)});
    return newDots;
}

void day13() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day13.txt");
//    istringstream ifile("6,10\n"
//                        "0,14\n"
//                        "9,10\n"
//                        "0,3\n"
//                        "10,4\n"
//                        "4,11\n"
//                        "6,0\n"
//                        "6,12\n"
//                        "4,1\n"
//                        "0,13\n"
//                        "10,12\n"
//                        "3,4\n"
//                        "3,0\n"
//                        "8,4\n"
//                        "1,10\n"
//                        "2,14\n"
//                        "8,10\n"
//                        "9,0\n"
//                        "\n"
//                        "fold along y=7\n"
//                        "fold along x=5");
    string line;
    set<Position> dots;
    while (getline(ifile, line)) {
        if (line.empty())
            break;
        int x;
        int y;
        char c;
        istringstream iline(line);
        iline >> x >> c >> y;
        dots.insert({x, y});
    }
    while (getline(ifile, line)) {
        string s;
        int num;
        char c;
        char comma;
        istringstream iline(line);
        iline >> s >> s >> c >> comma >> num;
        if (c=='x')
            dots = foldOnX(dots,num);
        else if (c=='y')
            dots = foldOnY(dots,num);
        else throw "huh?";
        if(star1 == 0)
            star1 = dots.size();
    }
    int minx = dots.begin()->first;
    int miny = dots.begin()->second;
    int maxx = dots.begin()->first;
    int maxy = dots.begin()->second;
    for(auto [x,y]:dots) {
        minx = min(x,minx);
        miny = min(y,miny);
        maxx = max(x,maxx);
        maxy = max(y,maxy);
    }
    for(int y=miny;y<=maxy;++y) {
        for (int x = minx; x <= maxx; ++x)
            if(dots.contains({x,y}))
                cout << "##";
            else
                cout << "  ";
        cout << endl;
    }
    cout << "Day 13 star 1 = " << star1 << "\n";
    cout << "Day 13 star 2 = " << star2 << "\n";
}
// 1:05
// 1:22
// 1:26