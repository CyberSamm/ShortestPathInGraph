#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string find_path(int s, int d, int dir) {
    std::string result;
    int i = s;
    while (true) {
        if (i == d) {
            result += std::to_string(i);
            break;
        }
        if (i < 1) {
            i = 10000;
        }
        if (i > 10000) {
            i = 1;
        }


        result += std::to_string(i);
        result.push_back(' ');
        i += dir;
    }
    result.push_back(' ');
    return result;
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

    std::cout << "Running tests for cycle.\n"; 
    while (!fin.eof()) {
        std::getline(fin, data);
        if (data[0] == 'N') {
            count_from_dij = data.substr(28);
            std::getline(fin, data);
            dist_from_dij = data.substr(15);
            std::string dist;
            std::vector<std::string> paths;
            if (std::abs(v[index].first - v[index].second) > 10000 - std::abs(v[index].first - v[index].second)) {
                if (v[index].first < v[index].second) {
                    paths.push_back(find_path(v[index].first, v[index].second, 1));
                }
                else
                {
                    paths.push_back(find_path(v[index].first, v[index].second, -1));
                }
                dist = std::to_string(10000 - std::abs(v[index].first - v[index].second));
            }
            else if (std::abs(v[index].first - v[index].second) < 10000 - std::abs(v[index].first - v[index].second)) {
                if (v[index].first > v[index].second) {
                    paths.push_back(find_path(v[index].first, v[index].second, -1));
                }
                else
                {
                    paths.push_back(find_path(v[index].first, v[index].second, 1));
                }
                dist = std::to_string(std::abs(v[index].first - v[index].second));
            }
            else {
                paths.push_back(find_path(v[index].first, v[index].second, 1));
                paths.push_back(find_path(v[index].first, v[index].second, -1));
                dist = std::to_string(std::abs(v[index].first - v[index].second));
            }
            std::string num_of_paths = std::to_string(paths.size());
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
                if (paths.size() != path_from_dij.size()) {
                    std::cout << "Failed.\n";
                }
                else {
                    bool success = true;
                    for (int i = 0; i < paths.size(); ++i) {
                        if (paths[i] != path_from_dij[i]) {
                            std::cout << "Failed.\n";
                            success = false;
                        }
                    }
                    if (success) {
                        std::cout << "Passed successfully.\n";
                    }
                }
            }
            else {
                std::cout << "Failed.\n";
            }
                
            path_from_dij.clear();
            paths.clear();
            ++index;
        }
    }
    fin.close();
    return 0;
}