#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <unordered_set>
#include <range/v3/all.hpp>


using namespace std;
using namespace std::literals;
using namespace ranges;

auto lines_to_words() {
    return view::for_each([](const auto &line) {
        return line | view::split(' ') | view::for_each([](auto r) {
            return yield(string{r});
        });
    });
}

template <typename Range>
unordered_set<string> unique_words(Range &&lines) {
    return lines | lines_to_words();
}

bool odd(int i) { return i % 2; }
bool even(int i) { return !odd; }

int main() {
    const vector<string> sents = { "Tom killed Bob", "Bob killed Tom", "Alice is unhappy" };
    cout << view::all(sents) << '\n';

    const auto vocab = unique_words(sents);
    cout << view::all(vocab) << '\n';


    const vector<string> names = { "Tom", "Bob", "Alice" };
    auto results = view::for_each(names, [&](const auto &name) {
        return view::for_each(sents, [&](const auto &sent) {
            return yield_if(sent.find(name) != string::npos, 
                    name + " was found in sentence \"" + sent + "\"");
        });
    });
    for (auto result: results) { cout << result << '\n'; }

    return 0;
}
