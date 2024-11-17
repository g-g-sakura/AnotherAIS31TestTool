////////////////////////////////////////////////////////////////////////////////
// MonobitTests.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "MonobitTests.h"
#include "support/countBits.h"
#include "support/LaTeX.h"

namespace ais_31_lib
{
	namespace v3
	{
		namespace monobit_test
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
				std::wstring	strTitle = std::wstring(L"Test T1 (monobit test)");
				std::wstring	strLabel = std::wstring(L"sec:TestT1");
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
			///  Implements monobit test test as specified in AIS 20/31 - Version 2.0
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
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT1.c1 = 20000;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.p_bzInterpretedBj->length(blitz::firstDim) < (int64_t)io_refData.t_testT1.c1)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorInsufficientData;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT1.pass_fail_result = ns_consts::EnmPassFailResults::NotDetermined;
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
				int	remainder = 20000 % io_refData.bits_per_sample;
				if (0 == remainder)
				{
					octMaskAtLast = octMask;
				}
				else {
					if (true == io_refData.bIsMSbFirstByteBitConversion)
					{
						unsigned int	tempMask = ((0x00000001 << remainder) - 1);
						tempMask <<= (io_refData.bits_per_sample - remainder);
						octMaskAtLast = octMask & (0xff & tempMask);

					}
					else
					{
						octMaskAtLast = octMask & (0xff & ((0x00000001 << remainder) - 1));
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t	test_value = 0;
				for (int64_t i = 0; i < (int64_t)io_refData.t_testT1.c1; ++i)
				{
					if (i != (io_refData.t_testT1.c1 - 1))
					{
						const uint32_t	word_bit_count = countBits((ns_dt::octet)(*io_refData.p_bzInterpretedBj)((int)i));
						test_value += word_bit_count;
					}
					else
					{
						ns_dt::octet	octMaskedLastData = (*io_refData.p_bzInterpretedBj)((int)i);
						octMaskedLastData &= octMaskAtLast;
						const uint32_t	word_bit_count = countBits((ns_dt::octet)octMaskedLastData);
						test_value += word_bit_count;
					}
				}
				// -------------------------------------------------------------------------- //
				// apply Evaluation rule
				// -------------------------------------------------------------------------- //
				io_refData.t_testT1.test_value_T1 = test_value;
				if ((io_refData.t_testT1.th.lower_bound < test_value) && (test_value < io_refData.t_testT1.th.upper_bound))
				{
					io_refData.t_testT1.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				else
				{
					io_refData.t_testT1.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

		}
	}
}