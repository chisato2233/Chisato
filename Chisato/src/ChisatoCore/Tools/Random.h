#pragma once

#include <numeric>
#include <random>
#include <type_traits>

namespace cst {
    struct random {
        template<typename  T>
			requires(std::integral<T> || std::floating_point<T>)
        static T range(T min = 0.0, T max = 1.0) {
        	thread_local std::mt19937 generator(std::random_device{}());

            if constexpr (std::is_integral<T>::value) {
                std::uniform_int_distribution<T> distribution(min, max);
                return distribution(generator);
            }
            else {
                std::uniform_real_distribution<T> distribution(min, max);
                return static_cast<float>(distribution(generator));
            }
        }

        static auto probability (double prob) {
        	thread_local std::mt19937 generator(std::random_device{}());
            std::uniform_real_distribution<double> distribution(0.0, 1.0);

            const double roll = distribution(generator);
            return roll <= prob;
        }


        static auto unique_indices(int min,int max, int count) -> std::vector<int> {
	        const int range = max - min;
            std::vector<int> indices(range);


            
            std::iota(indices.begin(), indices.end(), 0);  // Fill with 0, 1, 2, ..., range-1
            std::ranges::shuffle(indices, std::mt19937(std::random_device{}()));
            if (count <= range) indices.resize(count);  // Keep only the first 'count' elements
            return indices;
        }

    };
}
