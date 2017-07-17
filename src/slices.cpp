#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/all.hpp>

//using namespace std;
using std::cout;
using namespace ranges;

int  square(int i) { return i * i; }
bool odd(int i)    { return i % 2; }

int main() {

    // Views can be infinite, e.g. ints beginning at 0.
    auto naturals = view::ints(0);

    // Views can be piped together in a single expression.
    auto numbers = naturals
        | view::transform(square)
        | view::filter(odd);

    // [49 81 121 169 225 289 361 441 529 625 729 841 961 1089 1225 1369 1521]
    auto sliced = numbers | view::slice(3, 20);

    // [49 121 225 361 529 729 961 1225 1521]
    auto every_second = view::stride(numbers, 2);

    // "Python-like" syntax
    for (int n : sliced[{5, end}]) { 
        cout << n << " "; 
    }

    // Other variants:
    sliced[{7, end}];
    sliced[{end - 5, end - 1}];

    // And a very nice compile error:
    //
    // numbers[{end - 2, end}];
    // 
    // error: static assertion failed: Can't index from the end of an infinite range!

    return 0;
}
