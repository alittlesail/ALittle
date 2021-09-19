
#include <iostream>
#include <set>
#include <unordered_set>
#include <assert.h>
#include "Carp/carp_string_set.hpp"
#include "Carp/carp_time.hpp"

int main(int argc, char* argv[])
{
	/*
	std::vector<float> m_value(4 * 3 * 2);
	m_value = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100
	, -0, -100, -200, -300, -400, -500, -600, -700, -800, -900, -1000, -1100 };
	Eigen::TensorMap<Eigen::Tensor<float, 3>> a(m_value.data(), 4, 3, 2);

	Eigen::array<int, 1> red_axis; red_axis[0] = 0;
	Eigen::array<int, 2> red_axis2 = { 1, 0};

	std::cout << "a" << std::endl << a << std::endl;
	std::cout << "b" << std::endl << a.chip<2>(0).chip(0, 1) << std::endl;
	std::cout << "c" << std::endl << a.maximum(red_axis) << std::endl;
	std::cout << "c" << std::endl << a.sum(red_axis) << std::endl;
	std::cout << "c" << std::endl << a.sum(red_axis2) << std::endl;
	*/
	auto si = sizeof CarpStringSet::CarpCharNode;

	std::unordered_set<std::string> number_set;
	for (size_t i = 10000000000; i < 10002000000; ++i)
	{
		number_set.insert(std::to_string(i));
	}

	/*
	bool value = false;
	auto t1 = CarpTime::GetCurMSTime();
	for (auto& number : number_set)
	{
		auto it = number_set.find(number);
		value = it != number_set.end();
	}
	auto t2 = CarpTime::GetCurMSTime();
	printf("set %lld value:%d\n", t2 - t1, (int)value);
	*/
	CarpStringSet set;
	for (auto& number : number_set)
		set.Insert(number);
	printf("set %zu\n", set.Size());
	/*
	bool value = false;
	auto t1 = CarpTime::GetCurMSTime();
	for (auto& number : number_set)
	{
		value = set.Find(number);
	}
	auto t2 = CarpTime::GetCurMSTime();
	printf("set %lld value:%d\n", t2 - t1, (int)value);
	*/
	for (auto& number : number_set)
	{
		auto v = set.Find(number);
		if (!v)
		printf("find %s %s\n", number.c_str(), v ? "true" : "false");
	}
	for (auto& number : number_set)
	{
		auto v = set.Erase(number);
		if (!v)
			printf("erase %s %s\n", number.c_str(), v ? "true" : "false");
	}
	system("pause");
	return 0;
}
