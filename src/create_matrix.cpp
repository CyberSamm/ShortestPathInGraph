#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    /*
    std::cout << "Enter source and destination" << std::endl;
    int source, destination;
    std::cin >> source >> destination;
    if((source > 10000 || source < 1) ||
        (destination > 10000 || destination < 1)){
            std::cout << "Invalid input value.\nSource and destination must be from [1, 10000]\n";
            exit(1);
    }*/

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
      //fout << "\n";
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
      //fout << "\n";
      ++count;
    }
    /*
    count = 1;
    std::vector<std::vector<int>> matrix(100);
    for(int i = 0 ; i < matrix.size(); ++i){
      for(int j = 0; j < 100; ++j){
        matrix[i].push_back(count);
        ++count;
      }
    } 
    
    for(int i = 0 ; i < matrix.size(); ++i){
      for(int j = 0; j < matrix[i].size(); ++j){
        fout << matrix[i][j] << " ";
      }
      fout << "\n";
    }
    */

    //fout << source << " " <<  destination; 
    fout.close();
 
    return 0;
}