#pragma once

#include "Processor.h"

namespace DiffProcessor
{
	Processor::Processor(long limit) {}

	Processor::~Processor()
	{
	}

	double abs(const double& a) {
		return a > 0 ? a : -a;
	}

	const double eps = 1e-9;
	bool eq(const double& a, const double& b) {
		return abs(a - b) < eps;
	}

	void Processor::do_process(SortedLimitedList<double> &must_be_equal_to, const SortedLimitedList<double> &expected_output)
	{
		SortedLimitedList<double>::iterator it1 = must_be_equal_to.first();
		SortedLimitedList<double>::const_iterator it2 = expected_output.first();

		while (it1 != must_be_equal_to.end())
			// erase bad elements
		{
			if (it2 != expected_output.end() && eq(*it1, *it2))
			{
				it1++;
				it2++;
				continue;
			}
			if (it2 == expected_output.end() || *it1 <  *it2)
			{
				SortedLimitedList<double>::iterator to_delete = it1;
				it1++;
				must_be_equal_to.remove(to_delete);
			} else
			{
				it2++;
			}
		}

		it1 = must_be_equal_to.first();
		it2 = expected_output.first();

		while (it2 != expected_output.end())
			// add missing ones
		{
			if (it1 != must_be_equal_to.end() && eq(*it1, *it2))
			{
				it1++;
				it2++;
				continue;
			}
			if (it1 == must_be_equal_to.end())
				must_be_equal_to.add_last(*it2);
			else
				must_be_equal_to.add_before(it1, *it2);
			it2++;
		}
	}
};
