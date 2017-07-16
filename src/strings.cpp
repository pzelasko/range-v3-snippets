#include <vector>
#include <string>
#include <iostream>
#include <range/v3/all.hpp>

using namespace std;
using namespace std::literals;
using namespace ranges;


int main() {

    string str {"tom killed bob"};

    // [[t,o,m],[k,i,l,l,e,d],[b,o,b]]
    auto rng = str | view::split(' ');
    cout << rng << '\n';

    // [t,o,m,k,i,l,l,e,d,b,o,b]
    auto rng2 = rng | view::join;
    cout << rng2 << '\n';

    // tomkilledbob
    string rng3 = view::join(rng);
    cout << rng3 << '\n';

    // tom killed bob
    string rng3a = view::join(rng, " ");
    cout << rng3a << '\n';

    // [tom,killed,bob]
    auto rng4 = rng | view::for_each([](auto r){ return yield(std::string{r}); });
    cout << rng4 << '\n';

    // [tom,killed,bob]
    auto rng5 = rng | view::transform([](auto r){ return std::string{r}; });
    cout << rng5 << '\n';

    // [[t,o,m, ,k,i,l,l,e,d, ,b,o,b]]
    auto rng6 = str | view::split(" ");  // Problems with c string '\0' char
    cout << rng6 << '\n';

    // [[t,o,m, ,k,i],[e,d, ,b,o,b]]
    auto rng7 = str | view::split(view::c_str("ll"));
    cout << rng7 << '\n';

    // [[t,o,m],[k,i,l,l,e,d],[b,o,b]]
    auto rng8 = str | view::split(view::c_str(" "));
    cout << rng8 << '\n';

    // [[t,o,m],[k,i,l,l,e,d],[b,o,b]]
    auto rng9 = str | view::split(" "s);
    cout << rng9 << '\n';




    auto rng3b = action::join(rng);
    static_assert(is_same_v<decltype(rng3b), vector<char>>);


    return 0;
}
