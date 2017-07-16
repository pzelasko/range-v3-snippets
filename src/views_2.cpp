#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/all.hpp>

using namespace std;

int  square(int i) { return i * i; }
bool odd(int i)    { return i % 2; }

int main() {
    namespace view = ranges::view;

    // Views can be infinite, e.g. ints beginning at 0.
    auto naturals = view::ints(0);

    // Views can be piped together in a single expression.
    auto numbers = naturals
        | view::transform(square)
        | view::filter(odd)
        | view::drop(3)
        //| view::stride(3)  // TODO: report bug?
        | view::take(5);

    // Or used as a function calls, which can be awkward.
    auto numbers_alt = 
        view::take(
            view::drop(
                view::filter(
                    view::transform(naturals, 
                        square),
                    odd),
                3),
            5);

    // Display first range ascending and second descending
    for (int n : numbers) { cout << n << " "; } cout << '\n';
    for (int n : view::reverse(numbers_alt)) { cout << n << " "; } cout << '\n';

}
