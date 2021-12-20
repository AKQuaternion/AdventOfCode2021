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
using std::priority_queue;

using Location = pair<int,int>;
using QEntry = pair<int, Location>;
bool operator<(const QEntry &x, const QEntry &y) {
    return x.first < y.first;
}

void day15() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day15.txt");
    string line;
    vector<string> lines;
    while (getline(ifile, line)) {
        lines.push_back(line);
    }
    cout << lines.size() << " " << lines.front().size() << endl;
    auto size = lines.size();
    priority_queue<QEntry,vector<QEntry>,std::greater<>> q;
    q.push({0,{0,0}});
    set<Location > visited;
    while(true) {
        auto next = q.top();
        if (next.second == Location{size-1,size-1}) {
            star1 = next.first;
        }
        if (next.second == Location{5*size-1,5*size-1}) {
            star2 = next.first;
            break;
        }
        q.pop();
        if(visited.contains(next.second))
            continue;
        visited.insert(next.second);
        auto [x,y] = next.second;
        cout << "Cost " << next.first << " at " << x << "," << y << endl;
             auto vx=x;
        auto vy=y;
        if(x>1)
            q.push({next.first + ((lines[y%size][(x-1)%size]-'0'+y/size +(x-1)/size)-1)%9+1,{x-1,y}});
        if(x<5*size-1)
            q.push({next.first + ((lines[(y)%size][(x+1)%size]-'0'+y/size +(x+1)/size)-1)%9+1,{x+1,y}});
        if(y>1)
            q.push({next.first + ((lines[(y-1)%size][(x)%size]-'0'+(y-1)/size +x/size)-1)%9+1,{x,y-1}});
        if(y<5*size-1)
            q.push({next.first + ((lines[(y+1)%size][(x)%size]-'0'+(y+1)/size +x/size)-1)%9+1,{x,y+1}});
    }
    cout << "Day 15 star 1 = " << star1 << "\n";
    cout << "Day 15 star 2 = " << star2 << "\n";
}
