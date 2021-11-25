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
    fout << "9 14\n0 1 4\n0 7 8\n1 2 8\n1 7 11\n2 3 7\n2 5 4\n2 8 2\n3 4 9\n3 5 14\n4 5 10\n5 6 2\n6 7 1\n6 8 6\n7 8 7\n0 8";

    fout.close();
    return 0;
}