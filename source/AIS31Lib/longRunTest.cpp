////////////////////////////////////////////////////////////////////////////////
// longRunTest.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "support/checkArgs.h"

namespace ais_31_lib
{
	namespace v2
	{
		namespace long_run_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;
			namespace ns_spt = ais_31_lib::support;

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
			ns_consts::EnmReturnStatus checkArgsForPerformTest(const ns_dt::t_data_for_v2& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				ns_consts::EnmReturnStatus	stsCommon = ns_spt::perform_common_args_for_tests(i_refData);
				if (ns_consts::EnmReturnStatus::Success != stsCommon)
				{
					return sts = stsCommon;
				}

				// -------------------------------------------------------------------------- //
				// as per paragraph 772 of AIS 20/31 - Version 2.35
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
			ns_consts::EnmReturnStatus performTest(ns_dt::t_data_for_v2& io_refData)
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
				ns_dt::octet	octCurrentBit = 0;
				uint32_t		runLength = 1;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_dt::octet	octBitOfLongestRun = 0;
				uint32_t		longestRunLength = 1;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (int i = 0; i < 20000; ++i)
				{
					if (0 == i)
					{
						octCurrentBit = (*io_refData.p_bzInterpretedBj)(i);
						runLength = 1;
					}
					else if ((20000 - 1) == i)
					{
						if ((0x01 & octCurrentBit) != (*io_refData.p_bzInterpretedBj)(i))
						{
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							if (longestRunLength < runLength)
							{
								longestRunLength = runLength;
								octBitOfLongestRun = octCurrentBit;

								if (34 <= runLength)
								{
									io_refData.t_testT4.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
								}
							}
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							octCurrentBit = (*io_refData.p_bzInterpretedBj)(i);
							runLength = 1;
						}
						else
						{
							++runLength;
						}
						// -------------------------------------------------------------------------- //
						// 
						// -------------------------------------------------------------------------- //
						if (longestRunLength < runLength)
						{
							longestRunLength = runLength;
							octBitOfLongestRun = octCurrentBit;

							if (34 <= runLength)
							{
								io_refData.t_testT4.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
							}
						}
					}
					else
					{
						if ((0x01 & octCurrentBit) != (*io_refData.p_bzInterpretedBj)(i))
						{
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							if (longestRunLength < runLength)
							{
								longestRunLength = runLength;
								octBitOfLongestRun = octCurrentBit;

								if (34 <= runLength)
								{
									io_refData.t_testT4.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
								}
							}
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							octCurrentBit = (*io_refData.p_bzInterpretedBj)(i);
							runLength = 1;
						}
						else
						{
							++runLength;
						}
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT4.longest_run = longestRunLength;
				io_refData.t_testT4.p_of_longest_run = octBitOfLongestRun;

				if (ns_consts::EnmPassFailResults::NotDetermined == io_refData.t_testT4.pass_fail_result)
				{
					io_refData.t_testT4.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}



		}
	}
}