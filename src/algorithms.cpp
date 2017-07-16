#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/all.hpp>

using namespace std;

template<typename Range>
void display(Range &&r) {
    cout << ranges::view::all(r) << '\n';
}

int main() {

    // Just like std:: algorithms from <algorithm>,
    // but instead of begin() - end() iterators,
    // provide a range.

    vector<int> numbers {10, 5, 7, 2, 9, 8, 1};
    ranges::sort(numbers);  // sorts in-place
    
    display(numbers);  // [1,2,5,7,8,9,10]

    vector<int> numbers2 = {3, 4, 5};
    vector<int> output;
    ranges::set_intersection(numbers, numbers2, ranges::back_inserter(output));

    display(output); // [5]
}
