#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> results;
vector<int> sequence;
bool* isVisited;

void process(int** matrix, unsigned N, int i)
{
    sequence.push_back(i + 1);
    isVisited[i] = true;

    if (sequence.size() == N)
    {
        int k = sequence[0] - 1;
        int j = sequence[sequence.size() - 1] - 1;
        
        if (matrix[k][j] == 1 && matrix[j][k] == 1)
        {
            results.push_back(sequence);
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (matrix[i][j] == 1 && !isVisited[j])
        {
            process(matrix, N, j);
            isVisited[j] = false;
            sequence.pop_back();
        }
    }
}

int main()
{
    unsigned N;

    cout << "N: ";
    cin >> N;

    int** matrix = new int* [N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
        }
    }

    isVisited = new bool[N] {};

    process(matrix, N, 0);

    cout << "************************************************************" << endl;

    for (int i = 0; i < results.size(); i++)
    {
        for (int j = 0; j < results[i].size(); j++)
        {
            cout << results[i][j] << " ";
        }
        cout << endl;
    }

    exit(0);
}
