#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(
    const std::deque<T>& left,
    const std::deque<T>& right,
    const Comp& comp
    ) {
    std::deque<T> result;

    auto it_l = left.begin();
    auto it_r = right.begin();

    while (it_l != left.end() && it_r != right.end()) {
        if (comp(*it_l, *it_r)) {
            result.push_back(*it_l);
            ++it_l;
        } else {
            result.push_back(*it_r);
            ++it_r;
        }
    }

    result.insert(result.end(), it_l, left.end());
    result.insert(result.end(), it_r, right.end());

    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comp) {
    if (src.size() <= 1) {
        return src;
    }

    auto mid = src.begin() + src.size() / 2;

    std::deque<T> left(src.begin(), mid);
    std::deque<T> right(mid, src.end());

    left = MergeSort(left, comp);
    right = MergeSort(right, comp);

    return Merge(left, right, comp);
}

