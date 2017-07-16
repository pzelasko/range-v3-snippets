#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/all.hpp>

using namespace std;

int main() {
    namespace view = ranges::view;

    // Unlike std:: algorithms, views are lazily evaluated.
    // They operate on ranges and return lightweight range objects,
    // which can be copied/moved and composed together.
    // This is possible due to "smart iterators", e.g. transform_iterator, filter_iterator

    // Lazily-evaluated range of ints [0, 100)
    auto numbers = view::ints(0, 100);

    // Range composition (also a lazily-evaluated range)
    auto squares = numbers | view::transform([](int i) { return i * i; });

    // Another range composition
    auto odds = numbers | view::filter([](int i) { return i % 2; });

    // Lazy range set_intersection algorithm
    auto common = view::set_intersection(squares, odds);

    // Limit range evaluation to first five elements
    auto first_five = view::take(common, 5);

    // All computation is done in here [before C++17 use RANGES_FOR macro]
    for (int num : first_five) {
        cout << num << ", ";
    }
}
