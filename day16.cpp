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

namespace {
    uint64_t binaryToInt(const string &s) {
        uint64_t ret = 0;
        for (auto c: s)
            ret = ret * 2 + (c == '1' ? 1 : 0);
        return ret;
    }
}

string hexToBin(const string &in) {
    string out;
    for (auto c: in) {
        switch (c) {
            case '0':
                out += "0000";
                break;
            case '1':
                out += "0001";
                break;
            case '2':
                out += "0010";
                break;
            case '3':
                out += "0011";
                break;
            case '4':
                out += "0100";
                break;
            case '5':
                out += "0101";
                break;
            case '6':
                out += "0110";
                break;
            case '7':
                out += "0111";
                break;
            case '8':
                out += "1000";
                break;
            case '9':
                out += "1001";
                break;
            case 'A':
                out += "1010";
                break;
            case 'B':
                out += "1011";
                break;
            case 'C':
                out += "1100";
                break;
            case 'D':
                out += "1101";
                break;
            case 'E':
                out += "1110";
                break;
            case 'F':
                out += "1111";
                break;
        }
    }
    return out;
}

struct Info {
    const string &s;
    uint64_t pos;

    string eat(uint64_t n) {
        auto out = s.substr(pos, n);
        pos += n;
        return out;
    }

    bool empty() {
        return pos >= s.size();
    }
};

uint64_t readVersion(Info &i) {
    uint64_t out = binaryToInt(i.eat(3));
    return out;
}

uint64_t readPacketID(Info &i) {
    uint64_t out = binaryToInt(i.eat(3));
    return out;
}

uint64_t processLiteral(Info &i) {
    string val;
    while (true) {
        auto group = i.eat(5);
        val += group.substr(1, 4);
        if (group[0] == '0')
            break;
    }
    auto out  = binaryToInt(val);
    cout << out << endl;
    return out;
}

uint64_t star1 = 0;

//vector<uint64_t> eatPacketsByNum(Info &i, uint64_t num) {
//
//}
//
//vector<uint64_t> eatPacketsBylength(Info &i, uint64_t length) {
//
//}
void indent(int depth) {
    cout << string(depth*3,' ');
}
uint64_t processPacket(Info &info, int depth) {
//    cout << "version " << readVersion(info) << endl;
    star1 += readVersion(info);
    auto packetID = readPacketID(info);
    if (packetID == 4) {
        indent(depth);
        return processLiteral(info);
    } else {
        indent(depth);
        switch (packetID) {
            case 0: // sum
                cout << "sum(" << endl; break;
            case 1: // product
                cout << "product(" << endl; break;
            case 2: // min
                cout << "min(" << endl; break;
            case 3: // max
                cout << "max(" << endl; break;
            case 5: // greater
                cout << "greater(" << endl; break;
            case 6: // less
                cout << "less(" << endl; break;
            case 7: // equal to
                cout << "equal(" << endl; break;
            default:
                throw "1";
        }
        vector<uint64_t> packetValues;
        auto lengthType = info.eat(1);
        if (lengthType == "0") {// next 15 bits is length of sub-packets
            auto numBits = binaryToInt(info.eat(15));
            auto chunk = info.eat(numBits);
            Info chunkInfo{chunk, 0};
            while (!chunkInfo.empty())
                packetValues.push_back(processPacket(chunkInfo,depth+1));
        } else { // next 11 bits is number of sub-packets
            auto numPackets = binaryToInt(info.eat(11));
            for (auto i = 0; i < numPackets; ++i)
                packetValues.push_back(processPacket(info,depth+1));
        }
        indent(depth); cout << ")" << endl;
        switch (packetID) {
            case 0: // sum
                return std::accumulate(packetValues.begin(), packetValues.end(), uint64_t {0});
            case 1: // product
                return std::accumulate(packetValues.begin(), packetValues.end(), uint64_t {1}, std::multiplies<>());
            case 2: // min
                return *std::min_element(packetValues.begin(), packetValues.end());
            case 3: // max
                return *std::max_element(packetValues.begin(), packetValues.end());
            case 5: // greater
                return packetValues.front() > packetValues.back();
            case 6: // less
                return packetValues.front() < packetValues.back();
            case 7: // equal to
                return packetValues.front() == packetValues.back();
            default:
                throw "1";
        }
    }
}

void day16() {
    ifstream ifile("../day16.txt");
    string line;
    ifile >> line;
//    line = "D2FE28";
//    line = "38006F45291200";
//    line = "9C0141080250320F1802104A08";
    auto bits = hexToBin(line);
    cout << bits << endl;

    Info i{bits, 0};
    auto star2 = processPacket(i,0);
    cout << "Day 16 star 1 = " << star1 << "\n";
    cout << "Day 16 star 2 = " << star2 << "\n";
}
// not 18446744071625764457, too high
// not 18446744072695278448, too high