// This program reads "example.wav" WAVE file from disk
// in a streaming manner and performs on-the-fly audio samples averaging. 
// The results are displayed in real-time as a 90-degrees-rotated 
// pseudo-waveform on the console.
//
// It's a simple demonstration of the power of the range-v3 library: 
// all the computation is done lazily (i.e. "on demand").
//
// Piotr Żelasko 2017
// <petezor +at+ gmail +dot+ com>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include <range/v3/all.hpp>


using namespace ranges;
using namespace std::literals;


constexpr short bytes2short(unsigned char b1, unsigned char b2){
    return (static_cast<short>(b1) << 8) + static_cast<short>(b2);
}

static_assert(bytes2short(0x0, 0x0) == 0x0);
static_assert(bytes2short(0x0, 0x1) == 0x1);
static_assert(bytes2short(0x1, 0x0) == 0x100);
static_assert(bytes2short(0x1, 0x2) == 0x102);

auto make_bar(int zero_signal) {
    return view::transform([=](int amp){ 
            return std::string{ view::concat(
                    view::repeat('.') | view::take(min(zero_signal, zero_signal + amp)),
                    view::repeat('#') | view::take(abs(min(0, amp))),
                    view::single('|'),
                    view::repeat('#') | view::take(max(0, amp)),
                    view::repeat('.') | view::take(min(zero_signal, zero_signal - amp))
                    )};  
            });
}

int main() {
    constexpr auto window_size = 40;
    constexpr auto amplitude = 60.f;
    constexpr auto zero_signal = int(amplitude);
    constexpr auto amplify_factor = 160;
    constexpr auto delay = 100ms;

    std::ifstream wavestream{"example.wav", std::ios::binary};
    auto samples = ranges::istream<unsigned char>(wavestream)[{44, end}]
        | view::chunk(2) 
        | view::for_each([](auto bytes) { return yield(accumulate(bytes, 0, &bytes2short)); })
        | view::transform([](short s){ return float(s) / std::numeric_limits<short>::max(); }) 
        | view::chunk(window_size)
        | view::transform([](auto chnk){ return accumulate(chnk, 0.f) / window_size; })
        | view::transform([](float f){ return std::min(amplitude, std::max(-amplitude, amplify_factor * f)); })
        | make_bar(zero_signal)
        | view::transform([](auto item){ std::this_thread::sleep_for(delay); return std::move(item); });


    for (const auto &s : samples) {
        std::cout << s << '\n';
    }

    return 0;
}
