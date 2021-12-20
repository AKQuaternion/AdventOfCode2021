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
using std::shared_ptr;
using std::make_shared;

using Integer = int;

class Number {
public:
    virtual pair<int,int> explode(int depth) {

    }
    virtual ~Number() {}
};

class RegularNumber : public Number {
public:
    RegularNumber(Integer x):_number(x){}
private:
    Integer _number;
};

class PairNumber : public Number {
public:
    PairNumber(std::shared_ptr<Number> left, std::shared_ptr<Number> right):_left(left),_right(right) {}
private:
    std::shared_ptr<Number> _left;
    std::shared_ptr<Number> _right;
};

shared_ptr<Number> parse(istream& is) {
    if(isdigit(is.peek())) {
        int i;
        is >> i;
        return make_shared<RegularNumber>(i);
    }
    else if(is.peek()=='[') {
        char c;
        is >> c; // read '['
        auto left = parse(is);
        is >> c; // read ','
        auto right = parse(is);
        is >> c; // read ']'
        return make_shared<PairNumber>(left,right);
    }
    else throw 1;
}

void day18() {
    auto star1 = 0;
    auto star2 = 0;


    ifstream ifile("../day18.txt");
    string line;
    while (getline(ifile, line)) {
        string s;
        int i;
        int x;
        int y;
        char c;
        double d;
        istringstream iline(line);
        iline >> s;
    }

    cout << "Day 18 star 1 = " << star1 << "\n";
    cout << "Day 18 star 2 = " << star2 << "\n";
}
