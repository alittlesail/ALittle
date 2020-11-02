
#include "CTCLossNode.h"

#include "include/ctc.h"
#include "dynet/expr.h"
#include "dynet/tensor-eigen.h"

CTCLossNode::~CTCLossNode()
{
	free(m_grad.v);
}

dynet::Dim CTCLossNode::dim_forward(const std::vector<dynet::Dim>& xs) const
{
	DYNET_ASSERT(xs.size() == 1, "must be 1 input");
	DYNET_ASSERT(xs[0]->bd == 1, "must be single batch");

	return dynet::Dim({1});
}

void CTCLossNode::forward_impl(const std::vector<const dynet::Tensor*>& xs, dynet::Tensor& fx) const
{
	m_grad.d = xs[0]->d;
	free(m_grad.v);
	m_grad.v = (float*)malloc(xs[0]->d[0] * sizeof(float));
	m_grad.device = xs[0]->device;
	dynet::TensorTools::zero(m_grad);

	int sizes = (int)xs[0]->d[0] / m_tag_size;
	int* labels_ptr = (int*)&(m_seq[0]);
	int label_sizes_ptr = (int)m_seq.size();

	int minibatch_size = 1;
	float costs = 0;

	ctcOptions options;
	memset(&options, 0, sizeof(options));
	options.loc = CTC_CPU;
	options.blank_label = m_blank_tag;
	options.num_threads = 0; // will use default number of threads

#if defined(CTC_DISABLE_OMP) || defined(APPLE)
	// have to use at least one
	options.num_threads = std::max(options.num_threads, (unsigned int) 1);
#endif

	size_t cpu_size_bytes;
	get_workspace_size(&label_sizes_ptr, &sizes,
		m_tag_size, minibatch_size,
		options, &cpu_size_bytes);

	std::vector<float> cpu_workspace(cpu_size_bytes);

	ctcStatus_t result = compute_ctc_loss(xs[0]->v, m_grad.v,
		labels_ptr, &label_sizes_ptr,
		&sizes, m_tag_size,
		minibatch_size, &costs,
		cpu_workspace.data(), options);
	printf("status %d\n", (int)result);
	fx.v[0] = costs;
}

void CTCLossNode::backward_impl(const std::vector<const dynet::Tensor*>& xs, const dynet::Tensor& fx,
	const dynet::Tensor& dEdf, unsigned i, dynet::Tensor& dEdxi) const
{
	dynet::tvec(dEdxi) += dynet::tvec(m_grad);
}

dynet::Expression ctc_loss(const dynet::Expression& x, int tag_size, const std::vector<int>& seq, int blank_tag)
{
	std::vector<int> args;
	args.push_back(x.i);
	return dynet::Expression(x.pg, x.pg->add_function<CTCLossNode>(args, tag_size, seq, blank_tag));
}