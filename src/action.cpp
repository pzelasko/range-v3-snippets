#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <map>

#include <range/v3/all.hpp>

using namespace std;

int  square(int i) { return i * i; }
bool odd(int i)    { return i % 2; }
int  add_5(int i)  { return i + 5; }

int main() {
    namespace view = ranges::view;
    namespace action = ranges::action;

    auto numbers = view::ints(0)
        | view::transform(square)
        | view::filter(odd)
        | view::drop(3)
        | view::take(5);

    // Range views are convertible to std:: containers.
    vector<int> vec_        = numbers;
    unordered_set<int> set_ = numbers;
    // (49: 0), (81: 1), (121: 2), (169: 3), (225: 4)
    map<int, int> map_      = view::zip(numbers, view::ints(0));

    for (const pair<int, int> p : map_) { cout << '(' << p.first << ": " << p.second << "), "; } cout << '\n';

    // But not to an array.
    // int arr[5] = numbers;
    // array<int, 5> arr = numbers;  

    // Range views can be subject to actions and algorithms,
    // which produce either a single element result,
    // or an Iterable (container) which owns its elements.
    // Actions are evaluated instantly (i.e. not lazily).

    // "Reduce" action performed on a range.
    auto sum = ranges::accumulate(numbers, 0);


	// Actions performed on elements of a vector,
	// which do not modify the source (elements are copied).
	// note: ranges::move is analogous, but (obviously) modifies the source.
	auto cpy = vec_ | ranges::copy
	    | action::sort
	    | action::stride(2)
	    | action::transform(add_5);
	
	static_assert(is_same_v<decltype(cpy), vector<int>>);
    cout << view::all(cpy) << '\n';

    // Actions performed on a vector in-place.
    action::sort(vec_);       // vec_ contains: [49, 81, 121, 169, 225]
    cout << view::all(vec_) << '\n';

    action::stride(vec_, 2);  // vec_ contains: [49, 121, 225]
    cout << view::all(vec_) << '\n';

    action::transform(vec_, add_5); // vec_ contains: [54, 126, 230]
    cout << view::all(vec_) << '\n';

    // Alternative syntax:
    vec_ = numbers;
    vec_ |= action::sort
        | action::stride(2)
        | action::transform(add_5);
    cout << view::all(vec_) << '\n';


    // Compile time error:
    //
    //     // auto sorted = action::sort(numbers);
    //
    // Compiler message:
    // 
    //     // error: static assertion failed: The iterator type 
    //     // of the range passed to action::sort 
    //     // must allow its elements to be permuted; that is, 
    //     // the values must be movable and the iterator must be mutable.
    //
    
}
