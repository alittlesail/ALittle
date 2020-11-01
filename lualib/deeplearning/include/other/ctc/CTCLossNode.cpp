
#include "CTCLossNode.h"

#include "include/ctc.h"

void CTCLossNode::ForwardImpl( const std::vector<const dynet::Tensor*>& xs, dynet::Tensor& fx ) const
{
	m_grads.SetDim(xs[0]->d);
	TensorTool::Zero(m_grads);

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

	float* cpu_workspace = (float*)g_MemoryPoolGroup.Create(cpu_size_bytes);

	compute_ctc_loss(xs[0]->v, m_grads.v,
		labels_ptr, &label_sizes_ptr,
		&sizes, m_tag_size,
		minibatch_size, &costs,
		cpu_workspace, options);

	g_MemoryPoolGroup.Release(cpu_workspace);

	fx.v[0] = costs;
}

void CTCLossNode::BackwardImpl( const std::vector<const Tensor*>& xs, const Tensor& fx, const Tensor& dEdf, unsigned int xs_i, Tensor& dEdxi ) const
{
	dEdxi.tvec() += m_grads.tvec();
}

void CTCLossNode::DimForward( const std::vector<Dim*>& xs )
{
	ALITTLE_ROBOT_ASSERT(xs.size() == 1, STRING_2_UTF8("必须是两个输入"));
	ALITTLE_ROBOT_ASSERT(xs[0]->bd == 1, STRING_2_UTF8("必须是单批次"));

	m_dim_forward = Dim(1);
}

dynet::Expression ctc_loss(const dynet::Expression& x, int tag_size, const std::vector<int>& seq, int blank_tag)
{
	std::vector<int> args;
	args.push_back(x.i);
	return dynet::Expression(x.pg, x.pg->AddNode(new CTCLossNode(args, tag_size, seq, blank_tag)));
}