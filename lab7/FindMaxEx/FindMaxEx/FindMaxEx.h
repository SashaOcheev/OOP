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

struct ConstCharComparator
{
	bool operator()(const char *s1, const char *s2) const
	{
		return strcmp(s1, s2) > 0;
	}
};

template <typename Less = ConstCharComparator>
bool FindMax<const char *, Less>
	(std::vector<const char*> const& arr, const char * maxValue, const Less &less = Less())
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
