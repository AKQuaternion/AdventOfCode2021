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

void print(map<Position, int> grid) {
    for (int row = -10; row < 115; ++row) {
        for (int col = -10; col < 115; ++col)
            if (grid[{col, row}])
                cout << '#';
            else
                cout << '.';
        cout << endl;
    }
}

void day20() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day20.txt");
    string line;
    string enhance;
    getline(ifile, enhance);
    assert(enhance.size() == 512);
    getline(ifile, line);
    int row = 0;
    map<Position, int> grid;
    int minx = 0;
    int maxx = 0;
    while (getline(ifile, line)) {
        maxx = line.size();
        for (int col = 0; col < line.size(); ++col)
            if (line[col] == '#')
                grid[{col, row}]++;
            else if (line[col] == '.')
                grid[{col, row}] = 0;
            else throw 1;
        ++row;
    }
    for (int gen = 0; gen < 51; ++gen) {
        --minx;
        ++maxx;
        map<Position, int> newGrid;
        //iterate grid touch all newGrid

        for (int i = minx - 1; i < maxx + 1; ++i) {
            grid[{minx, i}] = gen % 2;
            grid[{maxx - 1, i}] = gen % 2;
            grid[{i, maxx - 1}] = gen % 2;
            grid[{i, minx}] = gen % 2;

            grid[{minx - 1, i}] = gen % 2;
            grid[{maxx, i}] = gen % 2;
            grid[{i, maxx}] = gen % 2;
            grid[{i, minx - 1}] = gen % 2;
        }
//        const int grow = 0;
//        for (auto[pos, v]: grid)
//            for (int dx = -grow; dx <= grow; ++dx)
//                for (int dy = -grow; dy <= grow; ++dy) {
//                    auto[x, y] = pos;
//                    newGrid[{x + dx, y + dy}] = 0;
//                }

//        print(grid);

        //iterate newGrid look up bits in grid, use binary value to put 1 or 0

        for (int x = minx; x < maxx; ++x)
            for (int y = minx; y < maxx; ++y) {
                uint64_t bits = 0;
                if (grid[{x - 1, y - 1}])
                    ++bits;
                bits *= 2;
                if (grid[{x, y - 1}])
                    ++bits;
                bits *= 2;
                if (grid[{x + 1, y - 1}])
                    ++bits;
                bits *= 2;
                if (grid[{x - 1, y}])
                    ++bits;
                bits *= 2;
                if (grid[{x, y}])
                    ++bits;
                bits *= 2;
                if (grid[{x + 1, y}])
                    ++bits;
                bits *= 2;
                if (grid[{x - 1, y + 1}])
                    ++bits;
                bits *= 2;
                if (grid[{x, y + 1}])
                    ++bits;
                bits *= 2;
                if (grid[{x + 1, y + 1}])
                    ++bits;
                assert(bits < 512);
                if (enhance[bits] == '#')
                    newGrid[{x, y}] = 1;
            }
        grid = newGrid;
//        cout << "After " << gen+1 << " generations " << endl;
//        cout << "Size is " << grid.size() << endl;
//        cout << "count is " << count << endl;
        if (gen + 1 == 2 || gen + 1 == 50) {
            int count=0;
            for (auto[pos, v]: grid) {
                auto[x, y] = pos;
                if (x < minx || x >= maxx || y < minx || y >= maxx)
                    continue;
                assert(v == 0 || v == 1);
                count += v;
            }
            if (gen + 1 == 2)
                star1 = count;
            else
                star2 = count;
        }
//        print(grid);

    }
    cout << "Day 20 star 1 = " << star1 << "\n";
    cout << "Day 20 star 2 = " << star2 << "\n";
}
// 5565 too low
// 7879 too high