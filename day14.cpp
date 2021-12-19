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

void day14() {
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day14.txt");
    string line;
    string current;
    getline(ifile,current);
    getline(ifile,line);
    map<pair<char,char>,char> rules;
    while (getline(ifile, line)) {
        string s;
        char p1,p2,c;
        istringstream iline(line);
        iline >> p1 >> p2 >> s >> c;
        rules[{p1,p2}]=c;
//        cout << p1 << p2 << c << endl;
    }
    for(int gen=0;gen<40;++gen) {
        string next;
        for(int i=0;i<current.size()-1;++i) {
            next.push_back(current[i]);
            if(rules.contains({current[i],current[i+1]}))
                next.push_back(rules[{current[i],current[i+1]}]);
        }
        next.push_back(current.back());
        current = next;
        cout << gen << " " << next.size() << endl;
    }

    map<char,u_int64_t > frequencies;
    for(auto c:current)
        ++frequencies[c];
    vector<pair<uint64_t ,char>> counts;
    for(auto [c,f] : frequencies)
        counts.push_back({f,c});
    sort(counts.begin(),counts.end());
    star1 = counts.back().first-counts.front().first;
    cout << "Day 14 star 1 = " << star1 << "\n";
    cout << "Day 14 star 2 = " << star2 << "\n";
}
