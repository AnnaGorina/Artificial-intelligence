#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include <stack>

//для обхода в ширину
std::vector<std::vector<int>> ResultWidth;
std::vector<int> SequenceWidth;
bool* isVisitedWidth;

//для обхода в глубину
std::vector<std::vector<int>> ResultDepth;
std::vector<int> SecuenceDepth;
bool** isVisitedDepth;
std::vector<int> deleteStack;

//обход в ширину
void width(int** A, int N, int i) {
    SequenceWidth.push_back(i + 1);
    isVisitedWidth[i] = true;

    if (SequenceWidth.size() == N) {
        int k = SequenceWidth[0] - 1;
        int j = SequenceWidth[SequenceWidth.size() - 1] - 1;

        if (A[k][j] == 1 && A[j][k] == 1) {
            ResultWidth.push_back(SequenceWidth);
        }
    }

    for (int j = 0; j < N; j++) {
        if (A[i][j] == 1 && !isVisitedWidth[j]) {
            width(A, N, j);
            isVisitedWidth[j] = false;
            SequenceWidth.pop_back();
        }
    }
}

void depth(int** A, int N, int i) {
    std::stack<int> Stack;
    //std::vector<int> Copy;

    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            isVisitedDepth[j][k] = false;
        }
    }

    Stack.push(i);
    SecuenceDepth.push_back(i);
    //isVisitedDepth[i][0] = true;
    //Copy.push_back(i);

    while (!Stack.empty()) {
        for (int j = 0; j < N; j++) {
            if (A[Stack.top()][j] == 1 /*&& isVisitedDepth[j][Stack.top()] == false*/ && isVisitedDepth[Stack.top()][j] == false) {
                 for (int k = 0; k < SecuenceDepth.size(); k++) {
                      if (SecuenceDepth[k] == j) break;
                      if (k == SecuenceDepth.size() - 1) {
                          //isVisitedDepth[j][Stack.top()] = true;
                          isVisitedDepth[Stack.top()][j] = true;
                          Stack.push(j);
                          SecuenceDepth.push_back(j);
                          break;
                      }
                 }
                 if (j == N - 1 && Stack.size() <= N) {
                     if (Stack.size() == N) continue;
                     else
                     {
                         break;
                     }
                 }
            }
            if (j == N - 1 && Stack.size() < N) {
                //isVisitedDepth[Stack.top()][Stack.size() - 1] = true;
                deleteStack.push_back(Stack.top());
                Stack.pop();
                SecuenceDepth.pop_back();
            }
            if (Stack.size() == N) {
                if (A[Stack.top()][i] == 1) {
                    ResultDepth.push_back(SecuenceDepth);
                    SecuenceDepth.pop_back();
                    //deleteStack.push_back(Stack.top());
                    Stack.pop();
                    break;
                }
                else {
                    //isVisitedDepth[Stack.top()][Stack.size() - 1] = true;
                    //deleteStack.push_back(Stack.top());
                    Stack.pop();
                    SecuenceDepth.pop_back();
                    break;
                }
            }
            /*if (Stack.size() < 2) {
                for (int k = 0; k < deleteStack.size(); k++) {
                    if (k == 0) continue;
                    if (k == deleteStack.size() - 1) break;
                    isVisitedDepth[k - 1][k] = false;
                    isVisitedDepth[k][k - 1] = false;
                }
            }*/
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int N; //количество человек за столом

    std::cout << "Введите количество человек за столом: ";
    std::cin >> N;

    int** A; //матрица знакомств
    
    //выделение памяти
    A = new int* [N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
    }

    isVisitedWidth = new bool[N] {};

    isVisitedDepth = new bool*[N];
    for (int i = 0; i < N; i++) {
        isVisitedDepth[i] = new bool[N];
    }

    //заполнение матрицы знакомств
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 0;
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

    //вывод матрицы знакомств
    std::cout << "МАТРИЦА ЗНАКОМТСВ" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "**************************************************" << std::endl;

    //обход в ширину
    width(A, N, 0); //вызов функции обхода в ширину

    std::cout << "ОБХОД В ШИРИНУ" << std::endl;
    if (ResultWidth.empty()) {
        std::cout << "Невозможно рассадить " << N << " человек!" << std::endl;
    }
    for (int i = 0; i < ResultWidth.size(); i++) {
        for (int j = 0; j < ResultWidth[i].size(); j++) {
            std::cout << ResultWidth[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "**************************************************" << std::endl;

    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            isVisitedDepth[i][j] = true;
        }
    }*/

    //обход в глубину
    depth(A, N, 0); //вызов функции обхода в глубину

    std::cout << "ОБХОД В ГЛУБИНУ" << std::endl;
    if (ResultDepth.empty()) {
        std::cout << "Невозможно рассадить " << N << " человек!" << std::endl;
    }
    for (int i = 0; i < ResultDepth.size(); i++) {
        for (int j = 0; j < ResultDepth[i].size(); j++) {
            std::cout << ResultDepth[i][j] + 1 << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
 
    //освобождение памяти
    delete[] isVisitedWidth;
    
    for (int i = 0; i < N; i++) {
        delete[] isVisitedDepth[i];
    }
    delete[] isVisitedDepth;

    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;

    system("Pause");
}
