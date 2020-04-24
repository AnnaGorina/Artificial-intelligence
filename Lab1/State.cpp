#include "pch.h"
#include "State.h"

State::State(int N)
{
	isVisited.resize(N, false);
}

bool State::isEnd(int** A, int N)
{
	if (SequenceWidth.size() == N)
		return A[SequenceWidth.front()][SequenceWidth.back()] && A[SequenceWidth.back()][SequenceWidth.front()];
	else return false;
}

bool State::isSequence(int i) const {
	return isVisited[i];
}

void State::set_number(int i) {
	isVisited[i] = true;
	SequenceWidth.push_back(i);
}

int State::get_last_number() const {
	return SequenceWidth.back();
}

int State::get_first_number() const {
	return SequenceWidth.front();
}

std::vector<int> State::get_vector() const {
	return SequenceWidth;
}

void State::pop_back() {
	isVisited[SequenceWidth.back()] = false;
	SequenceWidth.pop_back();
}
