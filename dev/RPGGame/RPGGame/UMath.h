#pragma once
#include <random>
#include <stdexcept>

namespace UMath
{

	// Clamps the inputed value between the min and max
	template <typename T>
	inline T Clamp(T value, T min, T max) 
	{
		if (min > max)
		{
			throw std::invalid_argument("Clamp: min is greater than max"); // Throws an exception if the min is greater than the max
		}

		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	// Generates a int number between the min and max
	inline int RandRange(int min, int max)
	{
		if (min > max)
		{
			throw std::invalid_argument("RandRange: min is greater than max"); // Throws an exception if the min is greater than the max
		}

		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int> distrib(min, max);
		return distrib(gen);
	}

	// Generates a float-pointing number between the min and max
	inline float FRandRange(float min, float max)
	{
		if (min > max)
		{
			throw std::invalid_argument("FRandRange: min is greater than max"); // Throws an exception if the min is greater than the max
		}
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<float> distrib(min, max);
		return distrib(gen);
	}

	// Generates a double floating-pointing number between the min and max
	inline double FRandRange(double min, double max)
	{
		if (min > max)
		{
			throw std::invalid_argument("FRandRange: min is greater than max"); // Throws an exception if the min is greater than the max
		}
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<double> distrib(min, max);
		return distrib(gen);
	}
}