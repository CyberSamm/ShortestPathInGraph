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
    
    return result.s;
}


std::pair<int, int> find_rows_and_columns(int source, int destination) {
    std::pair<int, int> s_coordinates, d_coordinates;

    s_coordinates.first = (source - 1) % 100;
    d_coordinates.first = (destination - 1) % 100;
    (source == 10000) ? s_coordinates.second = 99 : s_coordinates.second = (source / 100) % 100;
    (destination == 10000) ? d_coordinates.second = 99 : d_coordinates.second = (destination / 100) % 100;

    if (d_coordinates.first == 99 && destination != 10000) {
        --d_coordinates.second;
    }
    if (s_coordinates.first == 99 && source != 10000) {
        --s_coordinates.second;
    }

    int rows = std::abs(s_coordinates.first - d_coordinates.first);
    int columns = std::abs(s_coordinates.second - d_coordinates.second);
    return { rows, columns };
}

void print(const std::vector<int>& v, std::ofstream& fout) {
    for (int elem : v) {
        fout << elem << " ";
    }
    fout << "\n";
}

void samples_of_size_k(int start, int end, int k, std::vector<int>& cur_comb, std::ofstream& fout) {

    if (cur_comb.size() == k) {
        print(cur_comb, fout);
        return;
    }
    int a = cur_comb.empty() ? start : cur_comb.back() + 1;
    for (int next_num = a; next_num < end; ++next_num) { // <=end
        cur_comb.push_back(next_num);
        samples_of_size_k(start, end, k, cur_comb, fout);
        cur_comb.pop_back();
    }
}
void find_paths(int rows, int columns, std::vector<std::vector<int>>& vv) {
    std::string file_name = "comb.txt";
    std::ofstream fout;
    fout.open(file_name);
    if (!fout.is_open()) {
        std::cout << "Unable to open " << file_name << std::endl;
        exit(1);
    }
    std::vector<int> comb;
    samples_of_size_k(0, rows + columns, rows, comb, fout);
    comb.clear();
    fout.close();
    std::vector<std::vector<int>> combinations;
    std::ifstream fin;
    fin.open(file_name);
    if (!fin.is_open()) {
        std::cout << "Unable to open " << file_name << std::endl;
        exit(1);
    }
    std::string data;
    while (!fin.eof()) {
        std::getline(fin, data);
        if (data.empty()) {
            break;
        }
        data.pop_back();
        std::stringstream ss(data);
        std::vector<int> temp;
        while (!ss.eof()) {
            int num;
            ss >> num;
            temp.push_back(num);
        }
        combinations.push_back(temp);
    }
    fin.close();
    
    for (int i = 0; i < combinations.size(); ++i) {
        std::vector<int> temp(rows + columns, 100);
        for (int j = 0; j < combinations[i].size(); ++j) {
            temp[combinations[i][j]] = 1;
        }
        vv.push_back(temp);
    }
}

void make_path(int source, int dest, int dir1, int dir2, std::vector<std::string>& paths, const std::vector<std::vector<int>>& vv) {
    if (dir1 == 1 && dir2 == 1) {
        for (int i = 0; i < vv.size(); ++i) {
            std::string temp = std::to_string(source);
            temp.push_back(' ');
            int elem = source;
            for (int j = 0; j < vv[i].size(); ++j) {
                elem += vv[i][j];
                temp += std::to_string(elem);
                temp.push_back(' ');
            }
            paths.push_back(temp);
        }
    }
    else if (dir1 == -1 && dir2 == -1) {
        for (int i = 0; i < vv.size(); ++i) {
            std::string temp = std::to_string(source);
            temp.push_back(' ');
            int elem = source;
            for (int j = 0; j < vv[i].size(); ++j) {
                elem -= vv[i][j];
                temp += std::to_string(elem);
                temp.push_back(' ');
            }
            paths.push_back(temp);
        }
    }
    else if (dir1 == 1 && dir2 == -1) {
        for (int i = 0; i < vv.size(); ++i) {
            std::string temp = std::to_string(source);
            temp.push_back(' ');
            int elem = source;
            for (int j = 0; j < vv[i].size(); ++j) {
                if (vv[i][j] == 1) {
                    elem += vv[i][j];
                    temp += std::to_string(elem);
                }
                else{
                    elem -= vv[i][j];
                    temp += std::to_string(elem);
                }
                temp.push_back(' ');
            }
            paths.push_back(temp);
        }
    }
    else if (dir1 == -1 && dir2 == 1) {
        for (int i = 0; i < vv.size(); ++i) {
            std::string temp = std::to_string(source);
            temp.push_back(' ');
            int elem = source;
            for (int j = 0; j < vv[i].size(); ++j) {
                if (vv[i][j] == 1) {
                    elem -= vv[i][j];
                    temp += std::to_string(elem);
                }
                else {
                    elem += vv[i][j];
                    temp += std::to_string(elem);
                }
                temp.push_back(' ');
            }
            paths.push_back(temp);
        }
    }
}

int main() {
    std::string file_name = "../io/random.txt";
    std::ifstream fin;
    fin.open(file_name);
    if (!fin.is_open()) {
        std::cout << "Unable to open " << file_name << std::endl;
        exit(1);
    }
    std::vector<std::pair<int, int>> v;
    while (!fin.eof()) {
        int a, b;
        fin >> a >> b;
        v.push_back({ a, b });
    }

    fin.close();
    file_name = "../io/output.txt";
    fin.open(file_name);
    if (!fin.is_open()) {
        std::cout << "Unable to open " << file_name << std::endl;
        exit(1);
    }

    std::string count_from_dij, dist_from_dij;
    std::vector<std::string> path_from_dij;
    std::string data;
    int index = 0;
    std::cout << "Running tests for matrix.\n"; 
    while (!fin.eof()) {
        std::getline(fin, data);
        if (data[0] == 'N') {
            count_from_dij = data.substr(28);
            std::getline(fin, data);
            dist_from_dij = data.substr(15);
            std::pair<int, int> temp = find_rows_and_columns(v[index].first, v[index].second);
            int rows = temp.first;
            int columns = temp.second;
            std::string dist = std::to_string(rows + columns);
            std::string num_of_paths;
            if (rows == 0 && columns == 0) {
                num_of_paths = "1";
            }
            else {
                num_of_paths = findWaysCount(rows + 1, columns + 1);
                if (num_of_paths == "-1") {
                    std::cout << "Invalid source and destination\n";
                }
            }

            // FIND PATHS
            /*
            std::vector<std::vector<int>> vv;
            find_paths(rows, columns, vv);
            std::vector<std::string> paths;
            int row_s = (v[index].first - 1) % 100;
            int row_d = (v[index].second - 1) % 100;
            int column_s = (v[index].first / 100) % 100;
            int column_d = (v[index].second / 100) % 100;

            if (row_s < row_d) {
                if (column_s < column_d) {
                    make_path(v[index].first, v[index].second, 1, 1, paths, vv);
                }
                else {
                    make_path(v[index].first, v[index].second, 1, -1, paths, vv);
                }
            }
            else {
                if (column_s < column_d) {
                    make_path(v[index].first, v[index].second, -1, 1, paths, vv);
                }
                else {
                    make_path(v[index].first, v[index].second, -1, -1, paths, vv);
                }
            }
            for (auto elem : paths) {
                std::cout << elem << "\n";
            }
            //std::string num_of_paths = std::to_string(paths.size());
            */
            // ----------

            std::getline(fin, data); // line: Paths
            while (!fin.eof()) {
                std::getline(fin, data);
                if (data == "end") {
                    break;
                }
                path_from_dij.push_back(data);
            }
            std::cout << "Test " << index + 1 << ": source - " <<  v[index].first << " destination - " << v[index].second << "\n"; 
            if (dist == dist_from_dij && count_from_dij == num_of_paths) {
                std::cout << "Passed successfully.\n";
            }
            else {
                std::cout << "Failed.\n";
                std::cout << dist << " dijkstra: " << dist_from_dij << "\n" << num_of_paths << " dijkstra: " << count_from_dij << "\n";
            }

            path_from_dij.clear();
            //paths.clear();
            ++index;
        }
    }


    fin.close();
    return 0;
}