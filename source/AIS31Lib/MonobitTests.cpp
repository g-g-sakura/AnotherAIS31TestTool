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

namespace ais_31_lib
{
	namespace v2
	{
		namespace monobit_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;


			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output subsection header for mononbit test
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <params="io_refData">
			/// </params>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXSubsectionHeader(const ns_dt::t_data_for_v2& io_refData)
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
				ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
				ssSep << L"%%%%%%" << L"\n";
				ssSep << L"%%%%%%  Test T1 (monobit test)" << L"\n";
				ssSep << L"%%%%%%" << L"\n";
				ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragment) << ssSep.rdbuf();
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragment) << L"\\subsection{Test T1 (monobit test) }\\label{sec:TestT1}" << L"\n";
				(*io_refData.p_ssLaTeXFragment) << L"\n\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output test values in LaTeX
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <params="io_refData">
			/// </params>
			/// <params="i_test_value">
			/// </params>
			/// <returns>
			///  <c>entropy_estimator_lib::constants::EnmReturnStatus::ErrorNullPointer</c>:  when the following condition is met:
			///    <ul>
			///     <li><c>io_refData.p_ssLaTeXFragment</c> == nullptr</li>
			///    </ul>
			///  <c>entropy_estimator_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputEachTestValueForSummaryFigureInLaTeX(const ns_dt::t_data_for_v2& io_refData, uint32_t i_test_value)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragment)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (257 < io_refData.t_testT1.current_index_in_sets)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorDomain;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (1 == io_refData.t_testT1.current_index_in_sets)
				{
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					outputLaTeXSubsectionHeader(io_refData);
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragment) << L"\\begin{figure}[htbp]" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" \\centering" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" \\begin{tikzpicture}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" \\begin{axis}[" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" 	xmin=0," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	xmax=280," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	ymin=8000," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	ymax=12000," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	xtick distance=20," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	width=24cm," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	xlabel=\\# of given sets," << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"	ylabel=$T_{1}$" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" ]" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" \\addplot[mark size=0.4, draw=blue] coordinates {" << L"\n";
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragment) << L" (";
				(*io_refData.p_ssLaTeXFragment) << std::right << std::setw(6) << io_refData.t_testT1.current_index_in_sets;
				(*io_refData.p_ssLaTeXFragment) << L", ";
				(*io_refData.p_ssLaTeXFragment) << std::right << std::setw(7) << i_test_value;
				(*io_refData.p_ssLaTeXFragment) << L")" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (257 <= io_refData.t_testT1.current_index_in_sets)
				{
					(*io_refData.p_ssLaTeXFragment) << L" };" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragment) << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"coordinates {( 0, 9654) ( 260, 9654)}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"node[above right] at (axis cs: 260,9654) {9654};" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"coordinates {( 0, 10346) ( 260, 10346)}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"node[above right] at (axis cs: 260, 10346) {10346};" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragment) << L" \\end{axis}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L" \\end{tikzpicture}" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragment) << L" \\caption{Test values $T_{1}$ of given sets}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"\\end{figure}" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"\n\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragment) << L"\\clearpage" << L"\n";
					(*io_refData.p_ssLaTeXFragment) << L"\n\n";
				}
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
			/// <params="io_refData">
			/// </params>
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
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT1.c2 = 20000;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.p_bzInterpretedBj->length(blitz::firstDim) < (int64_t)io_refData.t_testT1.c2)
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
				for (int64_t i = 0; i < (int64_t)io_refData.t_testT1.c2; ++i)
				{
					if (i != (io_refData.t_testT1.c2 - 1))
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
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					ns_consts::EnmReturnStatus	stsReport = outputEachTestValueForSummaryFigureInLaTeX(io_refData, test_value);
					if (ns_consts::EnmReturnStatus::Success != stsReport)
					{
						return sts = stsReport;
					}
				}				
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

		}
	}
}