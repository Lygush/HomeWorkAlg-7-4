#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

bool serch(std::vector<std::pair<int, int>>& vector, int numb) {
    for (int i{}; i < vector.size(); ++i) {
        if (vector[i].first == numb) {
            return true;
        }
    }
    return false;
}

void dfs(int** matrix, int i, int size, std::vector<std::pair<int, int>>& result, int& connect_comp) {
    for (int j{}; j < size; ++j) {
        if (matrix[i][j] != 0) {
            if (!serch(result, j)) {
                result.push_back(std::make_pair(j, connect_comp));
            }
            matrix[i][j] = 0;
            dfs(matrix, j, size, result, connect_comp);
        }
    }
}

int main() {
    std::fstream f_in("input.txt");
    int size{};
    if (f_in.is_open()) {
        f_in >> size;
        int** matrix = new int*[size];
        for (int i{}; i < size; ++i) {
            matrix[i] = new int[size];
        }
        for (int i{}; i < size; ++i) {
            for (int j{}; j < size; ++j) {
                f_in >> matrix[i][j];
            }
        }
        std::vector<std::pair<int, int>> result{std::make_pair(0,0)};
        int connect_comp{};
        for (int i{}; i < size; ++i) {
            for (int j{}; j < size; ++j) {
               if (matrix[i][j] != 0) {
                dfs(matrix, i, size, result, connect_comp);
                connect_comp++;
               }
            }
        }
        std::sort(result.begin(), result.end());
        std::cout << "Affiliation of connectivity components:\n";
        for (auto i: result) {
             std::cout << i.first + 1 << " - " << i.second + 1 << "\n";
        }
        std::cout << "Counts of connectivity components: " << connect_comp;
        for (int i{}; i < size; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    f_in.close();
}