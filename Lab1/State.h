#pragma once
#include<vector>

class State {
	std::vector<int> SequenceWidth;
	std::vector<bool> isVisited;

public:
	explicit State(int N);

	bool isEnd(int** A, int N);

	bool isSequence(int i) const;

	void set_number(int i);

	int get_last_number() const;

	int get_first_number() const;

	std::vector<int> get_vector() const;

	void pop_back();
};
