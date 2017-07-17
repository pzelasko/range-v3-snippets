#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/all.hpp>

using namespace std;
using namespace ranges;


struct Person {
    string name;
    int age = 0;

    int GetAge() const { return age; }
    string GetName() const { return name; }
};

ostream &operator<<(ostream &os, const Person &p) {
    os << "Person{name: " << p.GetName() << ", age: " << p.GetAge() << "}";
    return os;
}

bool IsNameValid(const string &n) {
    // Some kind of real validation would be here
    return n.size() > 3;
}

int main() {

    // Ranges TS brings a new term to STL algorithms: projection.
    // Projection is a callable which "preprocesses" the item
    // before the main algorithm is applied.

    vector<Person> people { {"Ann", 57}, {"Jake", 23}, {"John", 53} };

    // Equivalent calls
    ranges::sort(people, [](const Person &left, const Person &right) { return left.GetAge() < right.GetAge(); });
    cout << view::all(people) << '\n';
    
    ranges::sort(people, std::less<int>{}, [](const Person &p) { return p.GetAge(); });
    cout << view::all(people) << '\n';
    
    ranges::sort(people, std::less<int>{}, &Person::GetAge);
    cout << view::all(people) << '\n';


    // Equivalent calls
    int count  = ranges::count_if(people, [](const Person &p) { return IsNameValid(p.GetName()); });
    cout << "Count: " << count << '\n';

    int count_ = ranges::count_if(people, IsNameValid, &Person::GetName);
    cout << "Count: " << count << '\n';


    return 0;
}
