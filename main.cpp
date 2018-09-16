#include <iostream>
#include <array>
#include <functional>
#include <string_view>
#include "random.hpp"

constexpr auto rows = 6, cols = 6;

	template<int rows, int cols, template<int,int> class Gen>
constexpr auto generate_permutations()
{
	Gen<rows, cols> rnd;
	std::uint64_t used_length = 0;
	std::array<std::array<std::uint64_t, cols>, rows> out = {};
	std::array<std::uint64_t, rows*cols> used_values = {};
	for (auto&& val : used_values) val = rnd.next();
	for (auto row = 0; row < rows; row++) {
		for (auto element = 0; element < cols; element++) {
			std::uint64_t tmp = rnd.next();
			bool is_valid = false;
			while(is_valid)
			{
				for (auto &i : used_values) {
					if (tmp == i ) {
						is_valid = true;
						break;
					}
					tmp = rnd.next();
				}
			}
			out[row][element] = tmp;
			used_values[used_length++] = tmp;
		}
	}
	return out;
}

int main()
{
	constexpr auto permutations = generate_permutations<rows, cols, ConstexprRandom>();
	for (auto row = 0; row < rows; row++) {
		for (auto element = 0; element < cols; element++) {
			std::cout << permutations[row][element] << ' ';
		}
		std::cout << std::endl;
	}
	return 0;
}
