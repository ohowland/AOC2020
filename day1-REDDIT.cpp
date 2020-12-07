#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <vector>
#include <chrono>

std::optional<long long>
find (std::ranges::contiguous_range auto nums, int level, int target = 2020, long long prod = 1ll) {
  if (level == 0 && target == 0) {
    return {prod};
  }
  if (target < 0) {
    return std::nullopt;
  }
  auto iter = std::ranges::begin (nums);
  auto const end = std::ranges::end (nums);
  for (auto x : nums) {
    if (auto r = find (std::ranges::subrange (++iter, end), level - 1, target - x, prod * x); r) {
      return r;
    }
  }
  return std::nullopt;
}

int main (int argc, char* argv[]) {
  std::ifstream ifs{argv[1]};
  std::vector<int> nums{std::istream_iterator<int>{ifs}, {}};
  auto part1 = *find (nums, 2);
  auto start = std::chrono::high_resolution_clock::now();
  auto part2 = *find(nums, 3);
  auto stop = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
  std::cout << "Day 01 (in " << duration.count() << " us)" << '\n'
            << "  Part 1: " << part1 << '\n';
            << "  Part 2: " << part2 << '\n';
}