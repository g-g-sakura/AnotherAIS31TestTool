////////////////////////////////////////////////////////////////////////////////
// runsTest.cpp
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
		namespace runs_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;
			namespace ns_spt = ais_31_lib::support;

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output subsection header for runs test
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
				(*io_refData.p_ssLaTeXFragment) << L"\\subsection{Test T3 (runs test) }\\label{sec:TestT3}" << L"\n";
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
			ns_consts::EnmReturnStatus outputEachTestValueForSummaryFigureInLaTeX(ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragment)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (257 < io_refData.t_testT3.current_index_in_sets)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorDomain;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (1 == io_refData.t_testT3.current_index_in_sets)
				{
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					outputLaTeXSubsectionHeader(io_refData);
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					std::wstringstream	ssWorkHeader1 = std::wstringstream();
					std::wstringstream	ssWorkHeader2 = std::wstringstream();
					ssWorkHeader1 << L"\\begin{minipage}[t]{0.45\\hsize}" << L"\n";
					ssWorkHeader1 << L" \\centering" << L"\n";
					ssWorkHeader1 << L"\n";
					ssWorkHeader1 << L" \\begin{tikzpicture}" << L"\n";
					ssWorkHeader1 << L" \\begin{axis}[" << L"\n";
					ssWorkHeader1 << L" 	xmin=0," << L"\n";
					ssWorkHeader1 << L"	xmax=290," << L"\n";
					ssWorkHeader1 << L"	ymin=0," << L"\n";
					ssWorkHeader1 << L"	bar width=0.025cm," << L"\n";
					ssWorkHeader1 << L"	xtick distance=20," << L"\n";
					ssWorkHeader1 << L"	width=10.5cm," << L"\n";
					ssWorkHeader1 << L"	xlabel=\\# of given sets," << L"\n";
					ssWorkHeader1 << L"	ylabel={$T_{3}(\\lambda ";
					ssWorkHeader2 << L")$}" << L"\n";
					ssWorkHeader2 << L" ]" << L"\n";
					ssWorkHeader2 << L" \\addplot[mark size=0.4, draw=blue] coordinates {" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					for (int i = 0; i < 6; ++i)
					{
						for (int j = 0; j < 2; ++j)
						{
							if (0 == j)
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L"\\begin{figure}[ht]" << L"\n";
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L"\\begin{tabular}{cc}" << L"\n";
							}
							else if (1 == j)
							{

							}
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkHeader1.str();
							if (i < 5)
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L"= ";
							}
							else
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L"\\ge ";
							}
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << (i + 1) << L", p = " << j;
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkHeader2.str();
						}
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (int i = 0; i < 6; ++i)
				{
					for (int j = 0; j < 2; ++j)
					{
						*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L" (";
						*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << std::right << std::setw(6) << io_refData.t_testT3.current_index_in_sets;
						*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L", ";
						*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << std::right << std::setw(7) << (*io_refData.t_testT3.p_bzTestValue)(i,j);
						*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L")" << L"\n";
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (257 <= io_refData.t_testT3.current_index_in_sets)
				{
					std::wstringstream	ssWorkFooterLambda[6];
					std::wstringstream	ssWorkFooter11 = std::wstringstream();
					std::wstringstream	ssWorkFooter12 = std::wstringstream();
					std::wstringstream	ssWorkFooter13 = std::wstringstream();
					std::wstringstream	ssWorkFooter14 = std::wstringstream();
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					for (int i = 0; i < 6; ++i)
					{

						ssWorkFooterLambda[i] << L" };" << L"\n";
						ssWorkFooterLambda[i] << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
						ssWorkFooterLambda[i] << L"coordinates {( 0, ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].lower_bound;
						ssWorkFooterLambda[i] << L") ( 260, ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].lower_bound;
						ssWorkFooterLambda[i] << L")}" << L"\n";
						ssWorkFooterLambda[i] << L"node[below right] at (axis cs: 260,";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].lower_bound;
						ssWorkFooterLambda[i] << L") {\\footnotesize ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].lower_bound;
						ssWorkFooterLambda[i] << L"};" << L"\n";
						ssWorkFooterLambda[i] << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
						ssWorkFooterLambda[i] << L"coordinates {( 0, ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].upper_bound;
						ssWorkFooterLambda[i] << L") ( 260, ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].upper_bound;
						ssWorkFooterLambda[i] << L")}" << L"\n";
						ssWorkFooterLambda[i] << L"node[below right] at (axis cs: 260,";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].upper_bound;
						ssWorkFooterLambda[i] << L") {\\footnotesize ";
						ssWorkFooterLambda[i] << io_refData.t_testT3.th[i].upper_bound;
						ssWorkFooterLambda[i] << L"};" << L"\n";
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					ssWorkFooter11 << L" \\end{axis}" << L"\n";
					ssWorkFooter11 << L" \\end{tikzpicture}" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					ssWorkFooter11 << L" \\caption{Test values $T_{3}(\\lambda";
					ssWorkFooter12 << L", p = ";
					ssWorkFooter13 << L")$ of given sets}" << L"\n";
					ssWorkFooter13 << L" \\end{minipage}";
					ssWorkFooter14 << L"\\end{tabular}" << L"\n";
					ssWorkFooter14 << L"\\end{figure}" << L"\n";
					ssWorkFooter14 << L"\n\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					for (int i = 0; i < 6; ++i)
					{
						for (int j = 0; j < 2; ++j)
						{
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkFooterLambda[i].str();
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkFooter11.str();
							if (i < 5)
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L" = ";
							}
							else
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L" \\ge ";
							}
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << (i + 1);
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkFooter12.str();
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << j;
							*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkFooter13.str();
							if (0 == j)
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L" & \n";
							}
							else if (1 == j)
							{
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << L"\n";
								*(io_refData.p_ssLaTeXFragmentWork3[i][j]) << ssWorkFooter14.str();
							}
						}
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					for (int i = 0; i < 6; ++i)
					{
						for (int j = 0; j < 2; ++j)
						{
							(*io_refData.p_ssLaTeXFragment) << io_refData.p_ssLaTeXFragmentWork3[i][j]->rdbuf();
						}
					}
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
				(*io_refData.t_testT3.p_bzTestValue) = 0;
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
							int pos = runLength - 1;
							if (6 <= runLength)
							{
								pos = 5;
							}
							(*io_refData.t_testT3.p_bzTestValue)(pos, (int)octCurrentBit) += 1;
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
						int pos = runLength - 1;
						if (6 <= runLength)
						{
							pos = 5;
						}
						(*io_refData.t_testT3.p_bzTestValue)(pos, (int)octCurrentBit) += 1;
					}
					else
					{
						if ((0x01 & octCurrentBit) != (*io_refData.p_bzInterpretedBj)(i))
						{
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							int pos = runLength - 1;
							if (6 <= runLength)
							{
								pos = 5;
							}
							(*io_refData.t_testT3.p_bzTestValue)(pos, (int)octCurrentBit) += 1;
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
				io_refData.t_testT3.pass_fail_result = ns_consts::EnmPassFailResults::NotDetermined;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (int p = 0; p < 2; ++p)
				{
					// -------------------------------------------------------------------------- //
					// $\lambda = 1, 2, ..., 6$
					// -------------------------------------------------------------------------- //
					for (int lambdaMinusOne = 0; lambdaMinusOne < 6; ++lambdaMinusOne)
					{
						uint32_t	test_value = (*io_refData.t_testT3.p_bzTestValue)(lambdaMinusOne, p);
						if ((io_refData.t_testT3.th[lambdaMinusOne].lower_bound <= test_value) 
							&& (test_value <= io_refData.t_testT3.th[lambdaMinusOne].upper_bound))
						{
							//io_refData.t_testT3.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
						}
						else
						{
							io_refData.t_testT3.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
						}
					}
				}
				if (ns_consts::EnmPassFailResults::NotDetermined == io_refData.t_testT3.pass_fail_result)
				{
					io_refData.t_testT3.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					ns_consts::EnmReturnStatus	stsReport = outputEachTestValueForSummaryFigureInLaTeX(io_refData);
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