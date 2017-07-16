#include <iostream>
#include <vector>
using namespace std;

int  square(int i) { return i * i; }
bool odd(int i)    { return i % 2; }
 
int main() {
	 int to_drop = 3;
	 int to_take = 5;
	 vector<int> numbers;
	 for (int i = 0; ; ++i) {
		 int number = square(i);
		 if (odd(number)) {
			 if (to_drop > 0) {
				 --to_drop;
				 continue;
			 } else if (to_take-- > 0) {
				 numbers.push_back(number);
			 } else {
				 break;
			 }
		 }
	 }

    for (int i: numbers) {
        cout << i << ", ";
    }

	return 0;
}
