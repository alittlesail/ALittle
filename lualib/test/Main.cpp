
#include <eigen/Eigen/Eigen>
#include <eigen/unsupported/Eigen/CXX11/Tensor>
#include <eigen_third_party/eigen_spatial_convolutions.h>
#include <eigen_third_party/eigen_backward_spatial_convolutions.h>
#include <eigen_third_party/eigen_pooling.h>

#include <iostream>

int main(int argc, char* argv[])
{
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
	return 0;
}
