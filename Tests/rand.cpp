#include <iostream>
#include <ctime>
#include <fstream>

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));

    std::ofstream fout;
    fout.open("io/random.txt");
    int start, end;
    start = 1 + rand() % 10000;
    end = 1 + rand() % 10000;
    fout << start << " " << end;
    for(int i = 0; i < 9; ++i){  
      fout << "\n";
      start = 1 + rand() % 10000;
      end = 1 + rand() % 10000;
      fout << start << " " << end;
    }
    fout.close();
    return 0;
}


/*
71 31
5 7
57 169
111 27
691 194
390 216
854 686
935 832
312 654
73 4
*/