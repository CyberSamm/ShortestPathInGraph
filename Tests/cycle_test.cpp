#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::ifstream fin;
    fin.open("io/input.txt");
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    std::string data;
    while (!fin.eof()) {
        std::getline(fin, data);
    }
    fin.close();

    std::stringstream ss(data);
    int source, destination;
    ss >> source >> destination;

    std::string dist = std::to_string(std::min(std::abs(source - destination),
                    10000 - std::abs(source - destination)));

    fin.open("io/output.txt");
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    std::getline(fin, data);
    std::string count_from_dij = data.substr(28);
    std::getline(fin, data);
    std::string dist_from_dij = data.substr(15);

    fin.close();

    if(dist == dist_from_dij && count_from_dij == "1") {
        std::cout << "Success!" << std::endl;
    }
    else {
        std::cout << "Fail." << std::endl;
    }
    return 0;
}