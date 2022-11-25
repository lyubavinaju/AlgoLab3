#include "Sort.h"
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

static constexpr auto lower_int_comp = [](int a, int b) {return a < b; };
static constexpr auto greater_int_comp = [](int a, int b) {return a > b; };
static constexpr auto greater_string_comp = [](std::string a, std::string b) {return a > b; };

TEST(QuickSort, Sorted) {
	constexpr int n = 100;
	int a[n];
	for (int i = 0; i < n; i++) {
		a[i] = i;
	}
	sort(a, a + n, lower_int_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!lower_int_comp(a[i + 1], a[i]));
	}
}

TEST(QuickSort, DescendingOrder) {
	constexpr int n = 100;
	int a[n];
	for (int i = 0; i < n; i++) {
		a[i] = n - i;
	}
	sort(a, a + n, lower_int_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!lower_int_comp(a[i + 1], a[i]));
	}
}

TEST(QuickSort, EqualElements) {
	constexpr int n = 100;
	int a[n];
	for (int i = 0; i < n; i++) {
		a[i] = n - i;
	}
	for (int i = 0; i < n; i += 5) {
		a[i] = -100;
	}
	sort(a, a + n, lower_int_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!lower_int_comp(a[i + 1], a[i]));
	}
}

TEST(QuickSort, RandomTest) {
	std::mt19937 g;
	std::vector<int> a;
	constexpr int n = 1000000;
	for (int i = 0; i < n; i++) {
		a.push_back(g());
	}
	sort(&a[0], &a[0] + n, lower_int_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!lower_int_comp(a[i + 1], a[i]));
	}
}

TEST(QuickSort, InversedComparator) {
	std::mt19937 g;
	std::vector<int> a;
	constexpr int n = 1000000;
	for (int i = 0; i < n; i++) {
		a.push_back(g());
	}
	sort(&a[0], &a[0] + n, greater_int_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!greater_int_comp(a[i + 1], a[i]));
	}
}


TEST(QuickSort, Strings) {
	std::mt19937 g;
	std::vector<std::string> a;
	constexpr int n = 10000;
	constexpr int maxL = 35;
	constexpr int minL = 0;
	for (int i = 0; i < n; i++) {
		int length = g() % (maxL - minL + 1) + minL;
		std::string s;
		for (int j = 0; j < length; j++) {
			char c = char('A' + g() % 26);
			s += c;
		}
		a.push_back(s);
	}
	sort(&a[0], &a[0] + n, greater_string_comp);
	for (int i = 0; i < n - 1; i++) {
		ASSERT_TRUE(!greater_string_comp(a[i + 1], a[i]));
	}
}

TEST(Time, InsertionSort) {
	std::ofstream f;
	f.open("insertionSortTime.txt");
	constexpr int maxN = 50;
	constexpr int runs = 50000;
	for (int i = 1; i <= maxN; i++) {
		std::vector<std::vector<int>> a(runs, std::vector<int>(i));
		for (std::vector<int>& ai : a) {
			for (int j = 0; j < i; j++) {
				ai[j] = i - j;
			}
		}
		auto start = std::chrono::high_resolution_clock::now();
		for (int k = 0; k < runs; k++) {
			insertionSort(&a[k][0], &a[k][0] + i - 1, lower_int_comp);
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		f << d.count() << "\n";
	}
	f.close();
}

TEST(Time, QuickSort) {
	std::ofstream f;
	f.open("quickSortTime.txt");
	std::mt19937 g;
	constexpr int maxN = 50;
	constexpr int runs = 50000;
	for (int i = 1; i <= maxN; i++) {
		std::vector<std::vector<int>> a(runs, std::vector<int>(i));
		for (std::vector<int>& ai : a) {
			for (int j = 0; j < i; j++) {
				ai[j] = g();
			}
		}
		auto start = std::chrono::high_resolution_clock::now();
		for (int k = 0; k < runs; k++) {
			sort(&a[k][0], &a[k][0] + i, lower_int_comp);
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		f << d.count() << "\n";
	}
	f.close();
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}