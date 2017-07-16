#include <vector>
#include <iostream>

#include <range/v3/all.hpp>

using namespace std;
using namespace ranges;

int  square(int i) { return i * i; }
bool odd(int i)    { return i % 2; }

int main() {
	vector<int> numbers = view::ints(0)
		| view::transform(square)
		| view::filter(odd)
		| view::drop(3)
		| view::take(5); 

    for (int i: numbers) {
        cout << i << ", ";
    }

	return 0;
}
