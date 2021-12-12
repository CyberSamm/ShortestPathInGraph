#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

int main(int argc, char** argv) {

    std::ofstream fout;
    fout.open("io/input.txt");
    if (!fout.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    //  G = {v, e}
    // |v| = 10000
    // |e| = 2*99*100 = 19800
    fout << 10000 << " " << 19800 << "\n";
    int count = 1;
    int i = 1;
    while(true){
      if (count > 100){
        break;
      }
      for (i = 1 + 100 * (count - 1); i < 100*count; ++i) {
        fout << i << " " << i + 1 << " " << 1 << "\n";
      }
      ++count;
    }
    count = 1;
    while(true){
      if (count > 100){
        break;
      }
      for (i = count; i < 10000 - 100 + count; i += 100) {
        fout << i << " " << i + 100 << " " << 1 << "\n";
      }
      ++count;
    }
    fout.close();
 
    return 0;
}