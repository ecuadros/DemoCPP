#include <utility>
#include <iostream>
#include "util.h"

std::string repeat(size_t n, const std::string& str) {
    if (n == 0 || str.empty()) return {};
    if (n == 1) return str;
    const auto period = str.size();
    if (period == 1) return std::string(n, str.front());

    std::string ret(str);
    ret.reserve(period * n);
    std::size_t m {2};
    for (; m < n; m *= 2) ret += ret;
    ret.append(ret.c_str(), (n - (m / 2)) * period);
    return ret;
}

std::string operator*(std::string str, std::size_t n)
{
    return repeat(n, std::move(str));
}