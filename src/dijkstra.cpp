#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

void find_paths(std::vector<std::vector<int>>& paths, std::vector<int>& path, 
                const std::vector<std::vector<int>>& answer, int to) {
    if (to == -1) {
        paths.push_back(path);
        return;
    }

    for (int p = 0; p < answer[to].size(); ++p) {
        path.push_back(to);
        find_paths(paths, path, answer, answer[to][p]);
        path.pop_back();
    }
}

void find_paths2(std::vector<std::vector<int>>& paths, std::vector<int>& path, 
                const std::vector<std::vector<int>>& answer, int from, int to) {

    std::stack<int> s_path;
    std::stack<int> s_index;
    s_path.push(from);
    s_index.push(0);

    while (!s_path.empty()) {
        int vertex = s_path.top();
        int ind = s_index.top();
        path.push_back(vertex);

        if (vertex == to) {
            paths.push_back(path);
        }

        if (ind < answer[vertex].size() &&
            answer[vertex][ind] != -1) {

            int tmp = answer[vertex][ind];
            s_path.push(tmp);
            s_index.push(0);
        }
        else {
            s_path.pop();
            s_index.pop();
            path.pop_back();
            if (s_path.empty()) {
                break;
            }

            vertex = s_path.top();
            ind = s_index.top();
            ++ind; 
            
            s_path.pop();
            s_index.pop();
            path.pop_back();

            s_path.push(vertex);
            s_index.push(ind);
        }
    }
}

int dijkstra(std::vector<std::vector<std::pair<int, int>>>& graph, std::vector<std::vector<int>>& answer, int from, int end) {
    int n = graph.size();

    std::vector<int> distance(n, std::numeric_limits<int>::max());

    distance[from] = 0;
    std::vector<char> used(n, false);
    answer[from] = { -1 };
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || distance[j] < distance[v])) {
                v = j;
            }
        }
        if (distance[v] == std::numeric_limits<int>::max()) {
            break;
        }
        used[v] = true;
        for (size_t j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j].first;
            int length = graph[v][j].second;

            if (distance[to] > distance[v] + length) {
                distance[to] = distance[v] + length;
                answer[to].clear();
                answer[to].push_back(v);
            }
            else if (distance[to] == distance[v] + length) {
                answer[to].push_back(v);
            }
        }
    }
    return distance[end];
}

void print_paths(std::vector<std::vector<std::pair<int, int>>>& graph, int from, int to, std::ostream& fout) {
    int n = graph.size();

    std::vector<std::vector<int>> paths;
    std::vector<int> path;
    std::vector<std::vector<int>> answer(n);

    int dist = dijkstra(graph, answer, from, to);

    find_paths2(paths, path, answer, to, from);
    
    fout << "Number of shortest paths is " << paths.size() << "\n";
    fout << "Path length is " << dist << "\n";
    fout << "Paths:" << "\n";
    for (auto v : paths) {
        std::reverse(v.begin(), v.end());

        for (int u : v) {
            fout << u << " ";
        }
        fout << "\n";
    } 
    fout << "end" << "\n";
}

int main(int argc, char* argv[]) {
    std::ifstream fin;
    std::string file_name = "io/input.txt";

    fin.open(file_name);
    if (!fin.is_open()) {
        std::cout << "Unable to open the " << file_name << " file" << std::endl;
        exit(1);
    }

    std::vector<std::vector<std::pair<int, int>>> graph;
    while (!fin.eof()) {
        int n;
        fin >> n;
        graph.resize(n + 1);

        int m;
        fin >> m;
        for (int i = 0; i < m; ++i) {
            int x, y, length;
            fin >> x >> y >> length;
            graph[x].push_back(std::make_pair(y, length));
            graph[y].push_back(std::make_pair(x, length));
        }
    }
    fin.close();

    fin.open("io/random.txt");
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    std::vector<std::pair<int, int>> vertices;
    while (!fin.eof()) {
        int a,b;
        fin >> a >> b;
        vertices.push_back({a, b});
    }

    fin.close();

    file_name = "io/output.txt";
    std::ofstream fout;
    fout.open(file_name);
    if (!fout.is_open()) {
        std::cout << "Unable to open the " << file_name << " file" << std::endl;
        exit(1);
    }

    for(auto elem : vertices){
        print_paths(graph, elem.first, elem.second, fout);
    }
    
    fout.close();  
    return 0;
}