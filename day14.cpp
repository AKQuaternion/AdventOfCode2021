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
    uint64_t star1 = 0;
    uint64_t star2 = 0;
    ifstream ifile("../day14.txt");
    string line;
    string current;
    getline(ifile, current);
    getline(ifile, line);
    using cp = pair<char, char>;
    map<cp, vector<cp>> rules;
    map<pair<char,char>,char> oldRules;

    while (getline(ifile, line)) {
        string s;
        char p1, p2, c;
        istringstream iline(line);
        iline >> p1 >> p2 >> s >> c;
        oldRules[{p1,p2}]=c;
        rules[{p1, p2}].push_back({p1, c});
        rules[{p1, p2}].push_back({c, p2});
    }

    map<cp,uint64_t> frequencies;
    for (uint64_t i = 0; i < current.size() - 1; ++i) {
        ++frequencies[{current[i],current[i+1]}];
    }
    for (uint64_t gen = 0; gen < 40; ++gen) {
//        cout << gen << " " << current.size() << " " << current << endl;

//        for(auto [p,count]:frequencies) {
//            cout << p.first << p.second << ":" << count << " ";
//        }
//        cout << endl;

//        string next;
//        for(uint64_t i=0;i<current.size()-1;++i) {
//            next.push_back(current[i]);
//            if(oldRules.contains({current[i],current[i+1]}))
//                next.push_back(oldRules[{current[i],current[i+1]}]);
//        }
//        next.push_back(current.back());
//        current = next;

        map<cp,uint64_t> nextFrequencies;
        for(auto [p,count]:frequencies)
            for(auto newP:rules[p])
                nextFrequencies[newP] += count;

        frequencies = nextFrequencies;

    }

    map<char, u_int64_t> joe;
    for (auto [cp,count]: frequencies) {
        joe[cp.first] += count;
        joe[cp.second] += count;
    }
    ++joe[current.front()];
    ++joe[current.back()];
    vector<pair<uint64_t, char>> counts;
    for (auto[c, f]: joe)
        counts.push_back({f, c});
    sort(counts.begin(), counts.end());
    star1 = counts.back().first - counts.front().first;
    star1 /= 2;
    cout << "Day 14 star 1 = " << star1 << "\n";
    cout << "Day 14 star 2 = " << star2 << "\n";
}
// not 9223372033857011098 is too high
