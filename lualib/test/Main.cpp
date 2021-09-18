
#include <iostream>
#include <set>
#include "Carp/carp_number_set.hpp"

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
	std::set<std::string> number_set;
	for (int i = 0; i < 1000; ++i)
	{
		number_set.insert(std::to_string(i));
	}

	CarpNumberSet set;
	for (auto& number : number_set)
		set.Insert(number);


	for (auto& number : number_set)
		auto v = set.Find(number);

	for (auto& number : number_set)
		auto v = set.Erase(number);

	return 0;
}
