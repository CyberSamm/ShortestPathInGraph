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

    std::cout << "Enter source and destination" << std::endl;
    int source, destination;
    std::cin >> source >> destination;

    if((source > 10000 || source < 1) || 
        (destination > 10000 || destination < 1)){
            std::cout << "Invalid input value.\nSource and destination must be from [1, 10000]\n";
            exit(1);
    }

    fout << source << " " <<  destination; 
    fout.close();
    
    return 0;
}