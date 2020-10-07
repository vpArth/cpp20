#include <cstdio>
#include <vector>
using std::vector;

vector<int> range(int start, int stop, int step = 1) {
    vector<int> numbers;

    for (auto i = start; i < stop; i += step) {
        numbers.push_back(i);
    }

    return numbers;
}
vector<int> range(int stop) {return range(0, stop, 1); }

int main() {
    const auto numbers = range(-10, 11);
    for (auto n : numbers) {
    	printf("%3d ", n);
    }
	printf("\n\n");
 
    for (auto n : range(100)) {
    	printf("%3d ", n);
    	if ((n+1) % 20 == 0) printf("\n");
    }
	printf("\n");
}
