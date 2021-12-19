//
// Created by Chris Hartman on 12/6/21.
//

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

int calcFuel(const vector<int> &v, int location) {
    vector<int> output(v.size());
    std::transform(v.begin(),v.end(),output.begin(),[location](auto x){
        auto n = abs(x-location);
        return n*(n+1)/2;});
    return std::accumulate(output.begin(),output.end(),0);
}

void day7() {
    double star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day7.txt");
    int i;
    char c;
    auto num=0;
    vector<int> numbers;
    while (ifile >> i) {
        numbers.push_back(i);
        ifile >> c;
    }
    sort(numbers.begin(),numbers.end());
    star1 = numbers[numbers.size()/2+1];

    auto min=0;

    for(int ii=0;ii<numbers.size();++ii) {
        cout << ii << " " << calcFuel(numbers,ii) << endl;
    }
    cout << "Day 7 star 1 = " << star1 << "\n";
    cout << "Day 7 star 2 = " << star2 << "\n";
}
// not 504 or 505