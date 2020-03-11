#include <iostream>
#include <clocale>
#include <queue>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество человек: ";

    int N;
    std::cin >> N;

    int** A; //матрица знакомств
    bool** Aa; //для хранения пройденных вершин

    //выделение памяти
    A = new int* [N];

    for (int i = 0; i < N; i++) A[i] = new int[N];

    Aa = new bool* [N];

    for (int i = 0; i < N; i++) Aa[i] = new bool[N];

    //заполнение матрицы знакомств
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 1;
                continue;
            }
            if (A[j][i] == 0 || A[j][i] == 1) {
                A[i][j] = A[j][i];
                continue;
            }
            std::cout << "A[" << i << "][" << j << "] = ";
            std::cin >> A[i][j];
        }
    }
    std::cout << std::endl;

    //заполнение массива пройденных вершин значениями false
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Aa[i][j] = false;
        }
    }

    //вывод матрицы знакомств
    std::cout << "Матрица знакомств: " << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //обход графа в ширину
    std::queue<int> Queue; //создание очереди для обхода в ширину

    std::vector<int> ResultX; //вектор для итогового результата
    std::vector<int> ResultY;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (A[i][j] == 1) {
                Queue.push(A[i][j]);
                Aa[i][j] = true;
                ResultX.push_back(i);
                ResultY.push_back(j);
            }
        }
    }

    std::cout << "Итоговый результат: " << std::endl;
    for (int i = 0; i < ResultX.size(); i++) {
        std::cout << ResultX[i] << " " << ResultY[i] << std::endl;
    }
    std::cout << std::endl;

    //освобождение памяти
    for (int i = 0; i < N; i++) delete[] A[i];

    delete[] A;
}
