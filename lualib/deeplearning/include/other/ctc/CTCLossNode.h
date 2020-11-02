
#ifndef _ALITTLE_ROBOT_CTCLOSSNODE_H_
#define _ALITTLE_ROBOT_CTCLOSSNODE_H_

#include "dynet/dynet.h"

class CTCLossNode : public dynet::Node
{
public:
	CTCLossNode(const std::vector<int>& a, int tag_size, const std::vector<int>& seq, int blank_tag) : Node(a), m_tag_size(tag_size), m_seq(seq), m_blank_tag(blank_tag) {}
	~CTCLossNode();

public:
	dynet::Dim dim_forward(const std::vector<dynet::Dim>& xs) const override;
	std::string as_string(const std::vector<std::string>& args) const override { return "ctc"; }

protected:
	void forward_impl(const std::vector<const dynet::Tensor*>& xs, dynet::Tensor& fx) const override;
	void backward_impl(const std::vector<const dynet::Tensor*>& xs,
		const dynet::Tensor& fx, const dynet::Tensor& dEdf, unsigned i,
		dynet::Tensor& dEdxi) const override;

private:
	std::vector<int> m_seq;
	int m_tag_size;
	int m_blank_tag;

	mutable dynet::Tensor m_grad;
};

dynet::Expression ctc_loss(const dynet::Expression& x, int tag_size, const std::vector<int>& seq, int blank_tag);

#endif // _ALITTLE_ROBOT_CTCLOSSNODE_H_
