#include <cassert>    // assert
#include <cmath>      // sqrt
#include <functional> // function
#include <iostream>   // cout, endl, ostream
#include <vector>     // vector

using ::std::cout;
using ::std::endl;
using ::std::function;
using ::std::ostream;
using ::std::vector;
using mapper = function<int(int,int)>;

vector<int> createInitial(unsigned size) {
	vector<int> v;
	v.reserve(size);
	for (unsigned i = 0; i < size; i++) {
		v.push_back(i);
	}
	return v;
}

// 0123456789ABCDEF
// ECA86420FDB97531
int standardShuffle(int index, int size) {
	if (index % 2 == 0) {
		int mid = (size - 1) / 2;
		return mid - index / 2;
	} else {
		int end = size - 1;
		return end - index / 2;
	}
}

// 0123456789ABCDEF
// C840D951EA62FB73
int sqrtShuffle(int index, int size) {
	int partitions = static_cast<int>(sqrt(size));
	double ratio = ((index % partitions) + 1) / static_cast<double>(partitions);
	int split = (size - 1) * ratio;
	return split - index / partitions;
}

// 0123456789ABCDEF
// E9520D841C73B6AF
int triangleShuffle(int index, int size) {
	assert("Not implemented" == 0);
	return 0;
}

vector<int> shuffle(const vector<int>& v, mapper fn) {
	vector<int> result(v.size());
	for (unsigned i = 0; i < v.size(); i++) {
		result[fn(i, v.size())] = v[i];
	}
	return result;
}

ostream& operator<<(ostream& out, const vector<int>& v) {
	out << "[";
	for (int i : v) {
		out << i << ",";
	}
	out << "\b]";
	return out;
}

// WARNING: Potential infinite loop if mapper misbehaves.
int findCycleLength(int size, mapper fn) {
	const vector<int> initial = createInitial(size);
	int iterations = 0;
	vector<int> next = initial;
	do {
		next = shuffle(next, fn);
		iterations++;
#if DEBUG
		cout << next << endl;
#endif
	} while (next != initial);
	return iterations;
}

int main() {
	constexpr int deckSize = 16;
	cout << "standardShuffle repeats after "
	     << findCycleLength(deckSize, standardShuffle)
	     << " iterations.\n";
	cout << "sqrtShuffle repeats after "
	     << findCycleLength(deckSize, sqrtShuffle)
	     << " iterations.\n";
	cout << "triangleShuffle repeats after "
	     << findCycleLength(deckSize, triangleShuffle)
	     << " iterations.\n";
	return 0;
}
