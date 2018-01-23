#include <iostream>   // cout
#include <vector>     // vector
#include <functional> // function
#include <algorithm>  // next_permutation
#include <random>     // default_random_engine

using namespace std;

// Return the number of calls to generator before it returns result.
template <typename T>
int count_while(function<T()> generator, T result) {
	int i = 1;
	while (generator() != result) {
		i++;
	}
	return i;
}

int count_permutations(vector<int> v) {
	return count_while<vector<int>>([&v]() {
		next_permutation(v.begin(), v.end());
		return v;
	}, v);
}

int count_shuffles(vector<int> v) {
	std::random_device rd;
	std::mt19937 mt(rd());
	return count_while<vector<int>>([&v, &mt]() {
		shuffle(v.begin(), v.end(), mt);
		return v;
	}, v);
	return 0;
}

double count_average_shuffles(vector<int> v, int iterations) {
	double count = 0;
	for (int i = 0; i < iterations; i++) {
		count += count_shuffles(v);
	}
	return count / iterations;
}

int main() {
	vector<int> v = {0, 1, 2, 3, 4, 5, 6};
	cout << "Permutations: " << count_permutations(v) << endl;
	cout << "Shuffles: " << count_average_shuffles(v, 1000) << endl;
	return 0;
}
