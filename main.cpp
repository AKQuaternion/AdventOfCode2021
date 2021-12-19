#include <chrono>
#include <iostream>

void day1();
void day2();
void day3();
void day4();
void day5();
void day6();
void day7();
void day8();
void day9();
void day10();
void day10b();
void day11();
void day12();
void day13();
void day14();
void day15();
void day16();
void day17();
void day18();
void day19();
void day20();
void day21();
void day22();
void day23();
void day24();
void day25();

// day 1
// day 2
// day 3
// day 4
// day 5
// day 6
// day 7
// day 8
// day 9
// day 10
// day 11
// day 12
// day 13
// day 14
// day 15
// day 16
// day 17
// day 18
// day 19
// day 20
// day 21
// day 22
// day 23
// day 24
// day 25


double timesec() {
   auto nanos = static_cast<std::chrono::nanoseconds>(
         std::chrono::high_resolution_clock::now().time_since_epoch());
   return static_cast<double>(nanos.count()) / 1.e9;
}

int main() {
   auto time1 = timesec();// End time (sec)

//   day1();
//   day2();
//   day3();
//   day4();
//   day5();
//   day6();
//   day7();
//   day8();
//   day9();
//   day10();
//       day11();
//       day12();
//       day13();
       day14();
//       day15();
//     day16();
//     day17();
//     day18();
//     day19();
//     day20();
   //  day21();
   //  day22();
   //  day23();
   //  day24();
   //  day25();
   auto time2 = timesec();          // End time (sec)
   auto elapsedtime = time2 - time1;// Elapsed (sec)
   std::cout << "Time required: " << elapsedtime << " seconds" << std::endl;
}
