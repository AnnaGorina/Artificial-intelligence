// Lab1(II).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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

    std::vector<int> Result; //вектор для итогового результата

    int vertex; 

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (A[i][j] == 1) {
                Queue.push(i);
                //Result.push_back(i);
                /*vertex = Queue.front();
                Queue.pop();
                for (int z = 0; z < N; z++) {
                    if (A[vertex][z] == 1 && z != vertex) {
                        Queue.push(z);
                        Aa[i][z] = true;
                }*/
                while (!Queue.empty()) {
                    vertex = Queue.front();
                    Result.push_back(vertex);

                    for (int d = 0; d < N; d++) {
                        if (A[d][vertex] == 1 && d != vertex) Aa[d][vertex] = true;
                    }

                    Queue.pop();

                    for (int z = 0; z < N; z++) {
                        if (Aa[vertex][z] != true && A[vertex][z] == 1 && z != vertex) {
                            Queue.push(z);
                            Aa[vertex][z] = true;
                        }
                    }
                }
                if (A[vertex][i] == 1) continue;
                else {
                    Result.clear();
                    for (int t = 0; t < N; t++) {
                        for (int s = 0; s < N; s++) {
                            Aa[t][s] = false;
                        }
                    }
                }
                for (int z = 0; z < N; z++) {
                    for (int x = 0; x < N; x++) {
                        if (A[z][x] == 1 && z != x && Aa[z][x] == true) continue;
                        else {
                            Result.clear();
                            for (int t = 0; t < N; t++) {
                                for (int s = 0; s < N; s++) {
                                    Aa[t][s] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!Result.empty()) break;
    }

    std::cout << "Итоговый результат: " << std::endl;
    for (int i = 0; i < Result.size(); i++) {
        std::cout << Result[i] << " ";
    }
    std::cout << std::endl;

    //освобождение памяти
    for (int i = 0; i < N; i++) delete[] A[i];

    delete[] A;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
