#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class BigInt {
public:

    BigInt() = default;

    BigInt(int n) {
        s = std::to_string(n);
    }

    BigInt(const std::string& s) {
        this->s = s;
    }

    BigInt operator+(const BigInt& other) {
        bool sign = false;

        std::string s2 = other.s;
        std::reverse(s2.begin(), s2.end());

        std::string s1 = s;
        std::reverse(s1.begin(), s1.end());

        std::string res;
        for (int i = 0; i < std::max(s1.size(), s2.size()); ++i) {

            int sum = 0;

            if (i < s1.size()) {
                sum += s1[i] - '0';
            }

            if (i < s2.size()) {
                sum += s2[i] - '0';
            }

            if (sign) {
                ++sum;
            }

            sign = sum >= 10;

            sum = sum % 10;

            res.push_back(sum + '0');
        }

        if (sign) {
            res.push_back('1');
        }

        std::reverse(res.begin(), res.end());

        return BigInt(res);
    }

    bool operator<(const BigInt& other) {
        if (this->s.size() < other.s.size()) {
            return true;
        }
        if (this->s.size() < other.s.size()) {
            return false;
        }
        return s < other.s;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& b) {
        out << b.s;
        return out;
    }
   
    std::string s;
};

std::string findWaysCount(int rows, int columns) {
    if (rows < 1 || columns < 1) {
        return "-1";
    }
    
    if (rows == 1 && columns == 1) {
        return "0";
    }

    if (rows == 1 || columns == 1) {
        return "1";
    }

    std::vector<std::vector<BigInt>> ways(rows, std::vector<BigInt>(columns));

    for (int i = 0; i < rows; i = i + 1) {
        for (int j = 0; j < columns; j++) {
            if (j == 0 || i == 0) {
                ways[i][j] = 1;
            }
            else {
                ways[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            ways[i][j] = ways[i - 1][j] + ways[i][j - 1];
        }
    }

    BigInt result = ways[rows - 1][columns - 1];
/*
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << ways[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    return result.s;
}


std::pair<int, int> find_rows_and_columns(int source, int destination) {
    std::pair<int, int> s_coordinates, d_coordinates;
    
    s_coordinates.first = (source - 1)%100;
    d_coordinates.first = (destination - 1)%100;
    s_coordinates.second = (source/100)%100;
    d_coordinates.second = (destination/100)%100;
    

    int rows = std::abs(s_coordinates.first - d_coordinates.first);
    int columns = std::abs(s_coordinates.second - d_coordinates.second); 
    return { rows, columns };
}

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

    std::pair<int,int> temp = find_rows_and_columns(source, destination);
    int rows = temp.first;
    int columns = temp.second;
    
    std::string dist = std::to_string(rows + columns);

    std::string count = findWaysCount(rows + 1, columns + 1);

    if (count  == "-1") {
        std::cout << "Invalid source and destination\n";
    }

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

    if(dist == dist_from_dij && count_from_dij == count) {
        std::cout << "Success!" << std::endl;
    }
    else {
        std::cout << "Fail." << std::endl;
    }
    return 0;
}