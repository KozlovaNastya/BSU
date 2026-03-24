#include "pch.h"
#include "CppUnitTest.h"
#include "logic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
	TEST_CLASS(LogicTests)
	{
	public:
		TEST_METHOD(TestAverageValue)
		{
			std::vector<int> v = { 10, 20, 30 };
			double res = calculate_average(v);
			Assert::AreEqual(20.0, res);
		}

		TEST_METHOD(TestMinIndex)
		{
			std::vector<int> v = { 5, 1, 10 };
			int min_i, max_i;
			find_min_max(v, min_i, max_i);
			Assert::AreEqual(1, min_i);
		}
	};
}
