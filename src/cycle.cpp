#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

int main(int argc, char** argv) {

    std::ofstream fout;
    fout.open("io/input.txt");

    if (!fout.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    //  G = {v, e}
    // |v| = 10000
    // |e| = 10000
    fout << 10000 << " " << 10000 << "\n";
    for (int i = 1; i <= 10000; ++i) {
        if (i == 10000) {
        fout << i << " " << 1 << " " << 1 << "\n";
        break;
        }
        fout << i << " " << i + 1 << " " << 1 << "\n";
    }
    fout.close();
    
    return 0;
}