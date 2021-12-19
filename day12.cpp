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

map<string, set<string>> edges;

//int dfs(const string &v, map<string,int> &visited) {
//    if (v == "end") {
//        for(auto s:path)
//            cout << s << " ";
//        cout << endl;
//        return 1;
//    }
//    int paths = 0;
//    if (std::islower(v[0]))
//        ++visited[v];
//    path.push_back(v);
//    for (auto x: edges[v])
//        if(visited[x]<2)
//            paths += dfs(x, visited);
//    if (std::islower(v[0]))
//        --visited[v];
//    path.pop_back();
//    return paths;
//}

vector<string> path;

int dfs(const string &v, set<string> &visited, string &sawTwice) {
    if (v == "end"){
//        for(auto s:path)
//            cout << s << " ";
//        cout << endl;
        return 1;
    }
    int paths = 0;
    if (std::islower(v[0])) {
        if (visited.contains(v)) {
            assert(sawTwice.empty());
            sawTwice = v;
        } else
            visited.insert(v);
    }
    path.push_back(v);

    for (auto x: edges[v])
        if (x != "start" && (!visited.contains(x) || sawTwice.empty()))
            paths += dfs(x, visited, sawTwice);
    if(sawTwice == v)
        sawTwice.clear();
    else
        visited.erase(v);
    path.pop_back();
    return paths;
}

void day12() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day12.txt");
    string line;
    while (getline(ifile, line)) {
        istringstream iline(line);
        string from;
        string to;
        getline(iline, from, '-');
        getline(iline, to);
        edges[from].insert(to);
        edges[to].insert(from);
    }

    set<string> visited;
    string sawTwice;
    star1 = dfs("start", visited,sawTwice);
    cout << "Day 12 star 1 = " << star1 << "\n";
    cout << "Day 12 star 2 = " << star2 << "\n";
}
