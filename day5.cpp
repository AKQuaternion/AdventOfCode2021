#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void day5() {
    auto star1 = 0;
    auto star2 = 0;
    std::ifstream ifile("../day5.txt");
    std::string line;
    std::map<std::pair<int,int>,int> vents1;
    std::map<std::pair<int,int>,int> vents2;
    while (getline(ifile, line)) {
        char c;
        int x1,x2,y1,y2;
        std::istringstream iline(line);
        iline >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2;
        if(x1==x2) {
            int yStart = std::min(y1,y2);
            int yEnd = std::max(y1,y2);
            for(int i=yStart; i<=yEnd;++i) {
                ++vents1[{x1, i}];
                ++vents2[{x1, i}];
            }
        }
        else if(y1==y2) {
            int xStart = std::min(x1,x2);
            int xEnd = std::max(x1,x2);
            for(int i=xStart; i<=xEnd;++i) {
                ++vents1[{i, y1}];
                ++vents2[{i, y1}];
            }
        }
        else if(abs(x2-x1) == abs(y2-y1)) {
            int dx = (x2-x1)/abs(x2-x1);
            int dy = (y2-y1)/abs(y2-y1);
            for(int i=0;i<=abs(x2-x1);++i)
                ++vents2[{x1+i*dx,y1+i*dy}];
        }
    }
    star1 = std::count_if(vents1.begin(),vents1.end(),[](const auto v){return v.second>1;});
    star2 = std::count_if(vents2.begin(),vents2.end(),[](const auto v){return v.second>1;});

    std::cout << "Day 5 star 1 = " << star1 << "\n";
    std::cout << "Day 5 star 2 = " << star2 << "\n";
}