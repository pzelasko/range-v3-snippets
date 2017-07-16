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
    return view::transform([](const auto &line){ 
        return line 
        | view::split(" "s) 
        | view::transform([](auto r){ return std::string{r}; });
    }) | view::join;
}

template <typename Range>
unordered_set<string> unique_words(Range &&lines) {
    return lines | lines_to_words();
}

int main() {
    const vector<string> sents = { "Tom killed Bob", "Bob killed Tom", "Alice is unhappy" };
    cout << view::all(sents) << '\n';

    const auto vocab = unique_words(sents);
    cout << view::all(vocab) << '\n';

    return 0;
}
