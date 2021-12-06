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
    std::ifstream fin;
    fin.open("io/random.txt");
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    std::vector<std::pair<int, int>> v;
    while (!fin.eof()) {
        int a, b;
        fin >> a >> b;
        v.push_back({ a, b });
    }

    fin.close();

   
    fin.open("io/output.txt");
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    std::string count_from_dij, dist_from_dij;
    std::vector<std::string> path_from_dij;
    std::string data;
    int index = 0;
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
            }/*
            std::cout << dist << std::endl;
            for (int i = 0; i < paths.size(); ++i) {
                std::cout << paths[i] << std::endl;
            }*/
            std::string num_of_paths = std::to_string(paths.size());
            std::getline(fin, data); // line: Paths
            while (!fin.eof()) {
                std::getline(fin, data);
                if (data == "end") {
                    break;
                }
                path_from_dij.push_back(data);
            }
            
            if (dist == dist_from_dij && count_from_dij == num_of_paths) {
                if (paths.size() != path_from_dij.size()) {
                    std::cout << "Test " << index + 1 << " failed. (cycle)\n";
                }
                else {
                    bool success = true;
                    for (int i = 0; i < paths.size(); ++i) {
                        if (paths[i] != path_from_dij[i]) {
                            std::cout << "Test " << index + 1 << " failed. (cycle)\n";
                            success = false;
                        }
                    }
                    if (success) {
                        std::cout << "Test " << index + 1 << " passed successfully. (cycle)\n";
                    }
                }
            }
            else {
                std::cout << "Test " << index + 1 << " failed. (cycle)\n";
            }
                
            path_from_dij.clear();
            paths.clear();
            ++index;
        }
    }
    fin.close();
    return 0;
}