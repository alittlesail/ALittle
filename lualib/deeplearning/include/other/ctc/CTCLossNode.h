
#ifndef _ALITTLE_ROBOT_CTCLOSSNODE_H_
#define _ALITTLE_ROBOT_CTCLOSSNODE_H_

#include "dynet/dynet.h"

class CTCLossNode : public dynet::Node
{
public:
	CTCLossNode(const std::vector<int>& a, int tag_size, const std::vector<int>& seq, int blank_tag) : Node(a), m_tag_size(tag_size), m_seq(seq), m_blank_tag(blank_tag) {}
	~CTCLossNode() {}

public:
	void DimForward(const std::vector<dynet::Dim*>& xs);

protected:
	void ForwardImpl(const std::vector<const dynet::Tensor*>& xs, dynet::Tensor& fx) const;
	void BackwardImpl(const std::vector<const dynet::Tensor*>& xs,
						const dynet::Tensor& fx,
						const dynet::Tensor& dEdf,
						unsigned int xs_i,
						dynet::Tensor& dEdxi) const;

private:
	std::vector<int> m_seq;
	int m_tag_size;
	int m_blank_tag;

	mutable dynet::Tensor m_grads;
};

dynet::Expression ctc_loss(const dynet::Expression& x, int tag_size, const std::vector<int>& seq, int blank_tag);

#endif // _ALITTLE_ROBOT_CTCLOSSNODE_H_
