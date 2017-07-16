#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include <range/v3/all.hpp>


using namespace ranges;
using namespace std::literals;


short bytes2short(unsigned char b1, unsigned char b2){
    return (static_cast<short>(b1) << 8) + static_cast<short>(b2);
}

int main() {
    constexpr auto window_size = 80;
    constexpr auto amplitude = 80;
    constexpr auto zero_signal = 40;
    constexpr auto amplify_factor = 240;
    constexpr auto delay = 100ms;

    std::ifstream wavestream{"example.wav", std::ios::binary};
    auto samples = ranges::istream<unsigned char>(wavestream)[{44, end}]
        | view::chunk(2) 
        | view::for_each([](auto bytes) { return yield(accumulate(bytes, 0, &bytes2short)); })
        | view::transform([](short s){ return float(s) / std::numeric_limits<short>::max(); }) 
        | view::chunk(window_size)
        | view::transform([](auto chnk){ return accumulate(chnk, 0.f) / window_size; })
        | view::transform([](float f){ return std::string(std::min(amplitude, std::max(0, zero_signal + int(amplify_factor * f))), '#'); })
        | view::transform([](auto sample){ const auto sz = amplitude - sample.size(); return std::move(sample) + std::string(sz, '.'); })
        | view::transform([](auto item){ std::this_thread::sleep_for(delay); return std::move(item); });


    for (const auto &s : samples) {
        std::cout << s << '\n';
    }

    return 0;
}
