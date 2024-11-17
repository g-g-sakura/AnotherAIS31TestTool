////////////////////////////////////////////////////////////////////////////////
// pokerTest.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "pokerTest.h"
#include "support/checkArgs.h"
#include "support/LaTeX.h"

namespace ais_31_lib
{
	namespace v3
	{
		namespace poker_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;
			namespace ns_spt = ais_31_lib::support;

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output subsection header for mononbit test
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXSubsectionHeader(const ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragment)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::wstringstream	ssSep = std::wstringstream();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::wstring	strTitle = std::wstring(L"Test T2 (poker test)");
				std::wstring	strLabel = std::wstring(L"sec:TestT2");
				std::wstring	strBlock = std::wstring();
				sts = ns_spt::getLaTeXSubsection(strBlock, strTitle, strLabel);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return  sts;
				}
				ssSep << strBlock;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragment) << ssSep.rdbuf();
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragment) << L"\n\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="i_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus checkArgsForPerformTest(const ns_dt::t_data_for_v3& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				ns_consts::EnmReturnStatus	stsCommon = ns_spt::perform_common_args_for_tests(i_refData);
				if (ns_consts::EnmReturnStatus::Success != stsCommon)
				{
					return sts = stsCommon;
				}

				// -------------------------------------------------------------------------- //
				// as per paragraph 772 of AIS 20/31 - Version 3
				// -------------------------------------------------------------------------- //
				unsigned int	input_data_size = i_refData.p_bzInterpretedBj->length(blitz::firstDim);
				if (input_data_size < 20000)
				{
					sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //

				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_ref_f_j">
			/// </param>
			/// <param name="i_refData">
			/// </param>
			/// <param name="j">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus getfj(ns_dt::octet& o_ref_f_j,
				const ns_dt::t_data_for_v3& i_refData,
				unsigned int j)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (i_refData.p_bzInterpretedBj->extent(blitz::firstDim) < (int)(4 * (j + 1)))
				{
					return sts = ns_consts::EnmReturnStatus::ErrorOutOfBound;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				const blitz::Range	rg(4 * j, 4 * j + 3);
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				blitz::Array<ns_dt::octet, 1>	bz_x = (*(i_refData.p_bzInterpretedBj))(rg);
				const ns_dt::octet	f_j = 8 * bz_x(0) + 4 * bz_x(1) + 2 * bz_x(2) + bz_x(3);
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_ref_f_j = f_j;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return	sts = ns_consts::EnmReturnStatus::Success;
			}
			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements Test T1: monobit test as specified in AIS 20/31 Version 2.35
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus performTest(ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				sts = checkArgsForPerformTest(io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				// -------------------------------------------------------------------------- //
				// create histogram_f_i
				// -------------------------------------------------------------------------- //
				unsigned int	histogram_f_i[16] = { 0 };
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (int j = 0; j < 5000; ++j)
				{
					ns_dt::octet	f_j = 0;
					ns_consts::EnmReturnStatus	stsGetFj = getfj(f_j, io_refData, j);
					if (ns_consts::EnmReturnStatus::Success != sts)
					{
						return sts = stsGetFj;
					}
					const int iwj = static_cast<int>(f_j);
					if ((0 <= iwj) && (iwj <= 15))
					{
						histogram_f_i[iwj] += 1;
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				double	test_value = 0.0;
				constexpr  double	denominator = 0.5 * 625;
				for (const auto fi : histogram_f_i)
				{
					const double x = static_cast<double>(fi) - denominator;
					test_value += std::pow(x, 2.0);
				}
				test_value /= denominator;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT2.test_value_T2 = test_value;
				if (   (io_refData.t_testT2.threshold_lower_bound < test_value)
					&& (test_value < io_refData.t_testT2.threshold_upper_bound))
				{
					io_refData.t_testT2.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				else
				{
					io_refData.t_testT2.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}



		}
	}
}