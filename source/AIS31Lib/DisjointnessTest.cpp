////////////////////////////////////////////////////////////////////////////////
// DisjointnessTest.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "DisjointnessTest.h"

namespace ais_31_lib
{
	namespace v2
	{
		namespace disjointness_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;


			ns_consts::EnmReturnStatus performTest(ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT0.c1 = (48 + (io_refData.bits_per_sample - 1)) / io_refData.bits_per_sample;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.p_bzInputDataT0->size() < 65536 * io_refData.t_testT0.c1)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorInsufficientData;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT0.pass_fail_result = ns_consts::EnmPassFailResults::NotDetermined;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_dt::octet	octMask = 0xff;
				if (io_refData.bits_per_sample < 8)
				{
					octMask = 0xff >> (8 - io_refData.bits_per_sample);
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				int	shiftWidthAtLast = 48 % io_refData.bits_per_sample;
				if (0 == shiftWidthAtLast)
				{
					shiftWidthAtLast = io_refData.bits_per_sample;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_dt::octet	octMaskAtLast = 0xff;
				if (0 == 48 % io_refData.bits_per_sample)
				{
					octMaskAtLast = octMask;
				}
				else {
					octMaskAtLast = 0xff >> (8 - shiftWidthAtLast);
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				int	max_count = 1;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ElementHistogram	hist;
				for (int i = 0; i < 65536; ++i)
				{
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					uint64_t	w = 0;
					for (uint64_t j = 0; j < io_refData.t_testT0.c1; ++j)
					{
						if (j < (io_refData.t_testT0.c1 - 1))
						{
							w <<= io_refData.bits_per_sample;
							w |= (*io_refData.p_bzInputDataT0)(io_refData.t_testT0.c1 * i + j) & octMask;
						}
						else
						{
							w <<= shiftWidthAtLast;
							w |= (*io_refData.p_bzInputDataT0)(io_refData.t_testT0.c1 * i + j) & octMaskAtLast;

						}
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					tpl_elw_map& x_map_hg = hist.get<elem_w>();

					const tpl_elw_map::iterator it = x_map_hg.find(w);

					if (it != x_map_hg.cend())
					{
						const int new_count = 1 + (it->ex_cnt);
						x_map_hg.replace(it, t_element_count(w, new_count));
						if (max_count < new_count)
						{
							max_count = new_count;
						}
					}
					else
					{
						hist.insert(t_element_count(w, 1));
					}
				}
				// -------------------------------------------------------------------------- //
				// apply Evaluation rule
				// -------------------------------------------------------------------------- //
				if (2 <= max_count)
				{
					io_refData.t_testT0.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
				}
				else
				{
					io_refData.t_testT0.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}


		}
	}
}