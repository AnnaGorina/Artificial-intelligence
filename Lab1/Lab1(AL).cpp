#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include <stack>
#include <queue>
#include <chrono>
#include "State.h"

//для обхода в глубину
std::vector<std::vector<int>> ResultDepth;
std::vector<int> SequenceDepth;
bool* isVisitedDepth;
int countVertexDepth = 0;

//для обхода в ширину
std::vector<std::vector<int>> ResultWidth;
int countVertexWidth = 0;

//обход в глубину
void depth(int** A, int N, int vertex) {
	SequenceDepth.push_back(vertex + 1);
	countVertexDepth++;
	isVisitedDepth[vertex] = true;

	if (SequenceDepth.size() == N) {
		int k = SequenceDepth[0] - 1;
		int j = SequenceDepth[SequenceDepth.size() - 1] - 1;

		if (A[k][j] == 1 && A[j][k] == 1) {
			ResultDepth.push_back(SequenceDepth);
			return;
		}
	}

	for (int j = 0; j < N; j++) {
		if (A[vertex][j] == 1 && !isVisitedDepth[j]) {
			depth(A, N, j);
			isVisitedDepth[j] = false;
			SequenceDepth.pop_back();
		}
	}
}

void width(int** A, int N, int vertex)
{
	std::queue<State> myQueue;
	State startvertex(N); 
	startvertex.set_number(vertex);
	myQueue.push(startvertex);

	while (!myQueue.empty()) {
		State state = myQueue.front();
		myQueue.pop();

		if (state.isEnd(A, N)) {
			ResultWidth.push_back(state.get_vector());
			continue;
		}

		for (int j = 0; j < N; j++) {
			if (A[state.get_last_number()][j] && !state.isSequence(j)) {
				state.set_number(j);
				myQueue.push(state);
				countVertexWidth++;
				state.pop_back();
			}
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
	A = new int*[N];
	for (int i = 0; i < N; i++) {
		A[i] = new int[N];
	}

	isVisitedDepth = new bool[N] {};

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
	std::cout << "МАТРИЦА ЗНАКОМСТВ" << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "**************************************************" << std::endl;

	//обход в глубину
	std::chrono::time_point<std::chrono::system_clock> startDepth, endDepth;
	startDepth = std::chrono::system_clock::now();
	depth(A, N, 0); //вызов функции обхода в ширину
	endDepth = std::chrono::system_clock::now();

	std::cout << "ОБХОД В ГЛУБИНУ" << std::endl;
	if (ResultDepth.empty()) {
		std::cout << "Невозможно рассадить " << N << " человек!" << std::endl;
	}
	for (int i = 0; i < ResultDepth.size(); i++) {
		for (int j = 0; j < ResultDepth[i].size(); j++) {
			std::cout << ResultDepth[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "**************************************************" << std::endl;

	//обход в ширину
	std::chrono::time_point<std::chrono::system_clock> startWidth, endWidth;
	startWidth = std::chrono::system_clock::now();
	width(A, N, 0); //вызов функции обхода в глубину
	endWidth = std::chrono::system_clock::now();

	std::cout << "ОБХОД В ШИРИНУ" << std::endl;
	if (ResultWidth.empty()) {
		std::cout << "Невозможно рассадить " << N << " человек!" << std::endl;
	}
	for (int i = 0; i < ResultWidth.size(); i++) {
		for (int j = 0; j < ResultWidth[i].size(); j++) {
			std::cout << ResultWidth[i][j] + 1 << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//Оценки
	double Depth = static_cast<double>(N) / static_cast<double>(countVertexDepth - 1); //критерий целенаправленности для обхода в глубину

	std::cout << "Обход в глубину: " << Depth << std::endl;
	std::cout << "Время обхода в глубину: " <<  std::chrono::duration_cast<std::chrono::microseconds>(endDepth - startDepth).count() << std::endl;

	double Width = static_cast<double>(N) / static_cast<double>(countVertexWidth); //критерий целенаправленности для обхода в ширину
	
	std::cout << "Обход в ширину: " << Width << std::endl;
	std::cout << "Время обхода в ширину: " << std::chrono::duration_cast<std::chrono::microseconds>(endWidth - startWidth).count() << std::endl;

	//освобождение памяти
	delete[] isVisitedDepth;

	for (int i = 0; i < N; i++) {
		delete[] A[i];
	}
	delete[] A;

	system("Pause");
}
