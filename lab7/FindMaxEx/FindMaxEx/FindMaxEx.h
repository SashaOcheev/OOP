#pragma once
#include <vector>
#include <functional>

template <typename T, typename Less = std::less<T> >
bool FindMax(const std::vector<T> &arr, T& maxValue, const Less &less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto max = arr.begin();
	for (auto it = arr.begin() + 1; it != arr.end(); it++)
	{
		if (less(*max, *it))
		{
			max = it;
		}
	}
	maxValue = *max;
	return true;
};
