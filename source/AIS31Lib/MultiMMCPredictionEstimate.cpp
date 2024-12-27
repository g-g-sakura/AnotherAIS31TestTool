////////////////////////////////////////////////////////////////////////////////
// MultiMMCPredictionEstimate.cpp
//
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "MultiMMCPredictionEstimate.h"
#include "./support/checkArgs.h"
#include "./support/significantDigits.h"
#include "./support/MarkovModelHistogram.h"
#include "./support/conversion.h"
#include "./math/SpecialFunctions.h"
#include "./math/Equations.h"
#include <boost/math/tools/roots.hpp>
#include <vector>
#include <map>
#include "./support/LaTeX.h"

namespace ais_31_lib
{
	namespace predictors
	{
		namespace multimmc_prediction
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;
			namespace ns_math = ais_31_lib::predictors::math;
			namespace ns_spt = ais_31_lib::support;
			namespace ns_es = ais_31_lib::predictors::support;

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output LaTeX header for Multi MMC Prediction Estimate
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNullPointer</c>:  when the following condition is met:
			///    <ul>
			///     <li><c>io_refData.p_ssLaTeXFragmentTestT3Header</c> == nullptr</li>
			///     <li><c>io_refData.p_ssLaTeXFragmentTestT3Body</c> == nullptr</li>
			///    </ul>
			///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXHeader(ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentTestT3Header)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (nullptr == io_refData.p_ssLaTeXFragmentTestT3Body)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (1 == io_refData.current_number_of_round_in_trials)
				{
					// -------------------------------------------------------------------------- //
					//
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentTestT3Header) << L"\\clearpage" << L"\n";
					// -------------------------------------------------------------------------- //
					// prepend subsection 
					// -------------------------------------------------------------------------- //
					std::wstring	strSubsection639 = std::wstring();
					std::wstring	strSubsectionTitle639 = std::wstring(L"The MultiMMC Prediction Estimate (Test T3)");
					std::wstring	strLabel = std::wstring(L"sec:Binary639");
					ns_spt::getLaTeXSubsection(strSubsection639, strSubsectionTitle639, strLabel);
					// -------------------------------------------------------------------------- //
					//
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentTestT3Header) << strSubsection639;
					(*io_refData.p_ssLaTeXFragmentTestT3Header) << L"\n";
				}
				// -------------------------------------------------------------------------- //
				// prepend subsubsection 
				// -------------------------------------------------------------------------- //
				std::wstring	strSubsubsection639 = std::wstring();
				std::wstring	strSubsubsectionTitle639 = std::wstring(L"Distribution of $correct$");
				std::wstring	strSubsubLabel = std::wstring(L"sec:Binary639-distribution");
				std::wstring	strTrailer = std::wstring();
				switch (io_refData.current_number_of_round_in_trials)
				{
				case 1:
					strSubsubLabel += std::wstring(L"-1stTrial");
					strTrailer += std::wstring(L" for the 1st trial");
					break;
				case 2:
					strSubsubLabel += std::wstring(L"-2ndTrial");
					strTrailer += std::wstring(L" for the 2nd trial");
					break;
				default:
					break;
				}
				strSubsubsectionTitle639 += strTrailer;
				ns_spt::getLaTeXSubsubsection(strSubsubsection639, strSubsubsectionTitle639, strSubsubLabel);
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << strSubsubsection639;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{figure}[htbp]" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\centering" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{tikzpicture}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{axis}[" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	ybar," << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	xmin=0," << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	ymin=0," << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	width=20cm," << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	xlabel=length of run of ones in $correct$," << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"	ylabel=occurrences" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"]" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\addplot+[ybar] coordinates {" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output LaTeX Footer for Multi MMC Prediction Estimate
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNullPointer</c>:  when the following condition is met:
			///    <ul>
			///     <li><c>io_refData.p_ssLaTeXFragmentTestT3Body</c> == nullptr</li>
			///    </ul>
			///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXFooter(ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentTestT3Body)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"};" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"coordinates {(" << io_refData.t_testT3.r - 1 << L", " << io_refData.t_testT3.occurrences_at_longest_run << L") "; 
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"(" << io_refData.t_testT3.r - 1 << L", " << std::dec << io_refData.t_testT3.occurrences_at_longest_run << L") }" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"node[above left] at (axis cs:" << io_refData.t_testT3.r - 1 << L", ";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << io_refData.t_testT3.occurrences_at_longest_run << L") ";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"{\\shortstack{$r - 1$ = ";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << io_refData.t_testT3.r - 1 << L" " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\($\\rightarrow$ min-entropy = " << io_refData.t_testT3.t_common.min_entropy;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L" [bit / " << io_refData.bits_per_sample << L"-bit])}};" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{axis}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{tikzpicture}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\caption{Distribution of $correct$}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{figure}" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output supplemental information in LaTeX format
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNullPointer</c>:  when the following condition is met:
			///    <ul>
			///     <li><c>io_refData.p_ssLaTeXFragmentTestT3Body</c> == nullptr</li>
			///    </ul>
			///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputSupplementalInfoLaTeX(ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentTestT3Body)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				std::wstring	strSubsubsectionTraceability = std::wstring();
				std::wstring	strLabel = std::wstring(L"sec:Binary639-traceability");
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				std::wstring	strTrailer = std::wstring();
				switch (io_refData.current_number_of_round_in_trials)
				{
				case 1:
					strLabel += std::wstring(L"-1stTrial");
					strTrailer += std::wstring(L" for the 1st trial");
					break;
				case 2:
					strLabel += std::wstring(L"-2ndTrial");
					strTrailer += std::wstring(L" for the 2nd trial");
					break;
				default:
					break;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				ns_spt::getLaTeXSubsubsectionTraceability(strSubsubsectionTraceability, strTrailer, strLabel);
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << strSubsubsectionTraceability;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\renewcommand{\\arraystretch}{1.8}" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{table}[h]" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\caption{Supplemental information for traceability (NIST SP 800-90B Section 6.3.9)";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				switch (io_refData.current_number_of_round_in_trials)
				{
				case 1:
					(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"for the 1-st trial";
					break;
				case 2:
					(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"for the 2-nd trial";
					break;
				default:
					break;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{center}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\begin{tabular}{|l|c|}" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\rowcolor{anotherlightblue} %%" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"Symbol				& Value ";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$N$				& " << io_refData.t_testT3.N;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$C$				& " << io_refData.t_testT3.C;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$P_{\\textrm{global}}$				& " << std::setw(8) << io_refData.t_testT3.p_global;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$P'_{\\textrm{global}}$			& " << std::setw(8) << io_refData.t_testT3.p_prime_global;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$r$				& " << io_refData.t_testT3.r;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline " << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"$P_{\\textrm{local}}$ 			& " << std::setw(8) << io_refData.t_testT3.p_local;
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\\\ \\hline" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{tabular}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{center}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\end{table}" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\renewcommand{\\arraystretch}{1.4}" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentTestT3Body) << L"\\clearpage" << L"\n";
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 1 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_ref_bz_subpredict">
			/// </param>
			/// <param name="o_ref_bz_correct">
			/// </param>
			/// <param name="o_ref_bz_entries">
			/// </param>
			/// <param name="i_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step1(blitz::Array<ns_dt::NullableT<ns_dt::octet>, 1>& o_ref_bz_subpredict,
				blitz::Array<ns_dt::octet, 1>& o_ref_bz_correct,
				blitz::Array<int, 1>& o_ref_bz_entries,
				const ns_dt::t_data_for_v3& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorInvalidData;

				const int		def_D = 16;
				if (i_refData.t_testT3.D != def_D)
				{
					return	sts;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				constexpr  ns_dt::NullableT<ns_dt::octet>	nv = { true, 0 };
				o_ref_bz_subpredict.resize(i_refData.t_testT3.D);
				o_ref_bz_subpredict = nv;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				const int		N = i_refData.p_bzInputDataT3->length(blitz::firstDim) - 2;
				o_ref_bz_correct.resize(N);
				o_ref_bz_correct = 0;

				o_ref_bz_entries.resize(i_refData.t_testT3.D);
				o_ref_bz_entries = 0;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}


			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 2 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_refM">
			/// </param>
			/// <param name="i_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step2(std::vector<ns_es::MarkovModelHistogram*> & o_refM,
				const ns_dt::t_data_for_v3& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorInvalidData;

				const int	def_D = 16;
				if (i_refData.t_testT3.D != def_D)
				{
					return	sts;
				}
				for (int d = 1; d <= i_refData.t_testT3.D; ++d)
				{
					o_refM.push_back(new ns_es::MarkovModelHistogram());
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}
			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 4 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_refM">
			/// </param>
			/// <param name="o_ref_bz_subpredict">
			/// </param>
			/// <param name="io_ref_bz_correct">
			/// </param>
			/// <param name="io_ref_bz_scoreboard">
			/// </param>
			/// <param name="io_ref_winner">
			/// </param>
			/// <param name="o_ref_bz_entries">
			/// </param>
			/// <param name="i_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step4(std::vector<ns_es::MarkovModelHistogram*>& o_refM,
				blitz::Array<ns_dt::NullableT<ns_dt::octet>, 1>& o_ref_bz_subpredict,
				blitz::Array<ns_dt::octet, 1>& io_ref_bz_correct,
				blitz::Array<int, 1>& io_ref_bz_scoreboard,
				int& io_ref_winner,
				blitz::Array<int, 1>& o_ref_bz_entries,
				const ns_dt::t_data_for_v3& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				// -------------------------------------------------------------------------- //
				// 3. For i = 3 to L:
				// -------------------------------------------------------------------------- //
				for (int i = 3; i <= i_refData.p_bzInputDataT3->length(blitz::firstDim); ++i)
				{
					// -------------------------------------------------------------------------- //
					// a. For d = 1 to D
					// -------------------------------------------------------------------------- //
					for (int d = 1; d <= i_refData.t_testT3.D; ++d)
					{
						if (d < (i - 1))
						{
							// -------------------------------------------------------------------------- //
							// i. If (d < i - 1), 
							// -------------------------------------------------------------------------- //
							const blitz::Range	rg(i - d - 2, i - 3);
							blitz::Array<ns_dt::octet, 1>	bz_x = (*(i_refData.p_bzInputDataT3))(rg);

							boost::dynamic_bitset<>		xExp(d * i_refData.bits_per_sample, 0);
							const ns_consts::EnmReturnStatus	stsCnv = ns_spt::convertSeqSamplesToBitSet(xExp, bz_x);
							if (ns_consts::EnmReturnStatus::Success != stsCnv)
							{
								return sts = stsCnv;
							}
							const ns_dt::octet	oct_y = (*(i_refData.p_bzInputDataT3))(i - 2);

							// -------------------------------------------------------------------------- //
							//   1. If [(s_{i - d - 1}, \ldots, s_{i - 2}), s_{i - 1}] is in M_{d}, 
							//      increment M_{d}[(s_{i - d - 1}, \ldots, s_{i - 2}), s_{i - 1}] by 1.
							// -------------------------------------------------------------------------- //
							ns_consts::EnmReturnStatus	stsUpdate = ns_es::incrementXY(xExp, oct_y, *(o_refM.at(d - 1)));
							switch (stsUpdate)
							{
							case ns_consts::EnmReturnStatus::Success:
								break;
							case ns_consts::EnmReturnStatus::ErrorFirstIndexNotFound:
							case ns_consts::EnmReturnStatus::ErrorFirstIndexFoundButSecondIndexNotFound:
								// -------------------------------------------------------------------------- //
								//   2. Else if entries_{d} < maxEntries, add a counter for [(s_{i - d - 1}, \ldots, s_{i - 2}), s_{i - 1}] to the set,
								//      let M_{d}[(s_{i - d - 1}, \ldots, s_{i - 2}), s_{i - 1}] = 1
								//      and increment entries_{d} by 1.
								// -------------------------------------------------------------------------- //
								o_refM.at(d - 1)->insert(ns_es::t_xy_bin(xExp, oct_y, 1));
								break;
							default:
								return sts = stsUpdate;
							}
						}
					}
					// -------------------------------------------------------------------------- //
					// b. For d = 1 to D
					// -------------------------------------------------------------------------- //
					for (int d = 1; d <= i_refData.t_testT3.D; ++d)
					{
						if (d < i)
						{
							// -------------------------------------------------------------------------- //
							// i. If (d < i), find the y value that corresponds to the highest M_{d}[(s_{i-d}, \ldots, s_{i-1}), y] value,
							//    and denote that y as ymax.
							//    If there is a tie, let ymax be the greatest y in the tie.
							//    Let subpredict_{d} = ymax.
							//    If all possible values of M_{d}[(s_{i-d}, \ldots, s_{i-1}), y] are 0, then let subpredict_{d} = Null.
							// -------------------------------------------------------------------------- //
							const blitz::Range	rg(i - d - 1, i - 2);
							blitz::Array<ns_dt::octet, 1>	bz_x = (*(i_refData.p_bzInputDataT3))(rg);

							boost::dynamic_bitset<>		xExp(d * i_refData.bits_per_sample, 0);
							const ns_consts::EnmReturnStatus	stsCnv = ns_spt::convertSeqSamplesToBitSet(xExp, bz_x);
							if (ns_consts::EnmReturnStatus::Success != stsCnv)
							{
								return sts = stsCnv;
							}

							//ns_es::t_xy_bin	t_highest_value = { 0, 0, 0 };
							boost::dynamic_bitset<>		bitset_iv(d * i_refData.bits_per_sample, 0);
							ns_es::t_xy_bin	t_highest_value = { bitset_iv, 0, 0 };
							const ns_consts::EnmReturnStatus	stsFreq = ns_es::getFrequent(t_highest_value, xExp, *(o_refM.at(d - 1)));
							if (ns_consts::EnmReturnStatus::Success == stsFreq)
							{
								o_ref_bz_subpredict(d - 1) = { false, t_highest_value.ex_y };
							}
							else if (ns_consts::EnmReturnStatus::ErrorNotFound == stsFreq)
							{
								o_ref_bz_subpredict(d - 1) = { true, 0 };
							}
						}
					}
					// -------------------------------------------------------------------------- //
					// c. Let prediction = subpredict_winner.
					// -------------------------------------------------------------------------- //
					const ns_dt::NullableT<ns_dt::octet>	prediction = o_ref_bz_subpredict(io_ref_winner - 1);
					// -------------------------------------------------------------------------- //
					// d. If (prediction = s_{i}), let correct_{i - 2} = 1.
					// -------------------------------------------------------------------------- //
					if (false == prediction.bIsValueNull)
					{
						if (prediction.value == (*(i_refData.p_bzInputDataT3))(i - 1))
						{
							io_ref_bz_correct(i - 3) = 1;
						}
					}
					// -------------------------------------------------------------------------- //
					// e. Update the scoreboard. 
					//  For d = 1 to D,
					// -------------------------------------------------------------------------- //
					for (int d = 1; d <= i_refData.t_testT3.D; ++d)
					{
						// -------------------------------------------------------------------------- //
						// i. If (subpredict_{d} = s_{i})
						// -------------------------------------------------------------------------- //
						if (false == o_ref_bz_subpredict(d - 1).bIsValueNull)
						{
							if (o_ref_bz_subpredict(d - 1).value == (*(i_refData.p_bzInputDataT3))(i - 1))
							{
								// -------------------------------------------------------------------------- //
								// 1. Let scoreboard_{d} = scoreboard_{d} + 1
								// -------------------------------------------------------------------------- //
								io_ref_bz_scoreboard(d - 1) = io_ref_bz_scoreboard(d - 1) + 1;
								// -------------------------------------------------------------------------- //
								// 2. If scoreboard_{d} >= scoreboard_{winner}, let winner = d
								// -------------------------------------------------------------------------- //
								if (io_ref_bz_scoreboard(io_ref_winner - 1) <= io_ref_bz_scoreboard(d - 1))
								{
									io_ref_winner = d;
								}
							}
						}
					}
				}

				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 5 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_refC">
			/// </param>
			/// <param name="o_ref_bz_correct">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step5(int& o_refC, const blitz::Array<ns_dt::octet, 1>& io_ref_bz_correct)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				o_refC = blitz::count(io_ref_bz_correct == static_cast<ns_dt::octet>(1));

				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 6 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_ref_p_prime_global">
			/// </param>
			/// <param name="o_ref_p_global">
			/// </param>
			/// <param name="i_refC">
			/// </param>
			/// <param name="i_refN">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step6(double& o_ref_p_prime_global,
				double& o_ref_p_global,
				const int& i_refC, const int& i_refN)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

				o_ref_p_global = static_cast<double>(i_refC) / static_cast<double>(i_refN);
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (0 == i_refC)
				{
					o_ref_p_prime_global = 1.0 - pow(0.01, 1.0 / static_cast<double>(i_refN));
				}
				else
				{
					const double z_alpha = calc_Z_alpha(0.995);
					o_ref_p_prime_global = o_ref_p_global + z_alpha * sqrt(o_ref_p_global * (1.0 - o_ref_p_global) / static_cast<double>(i_refN - 1));
					if (1.0 < o_ref_p_prime_global)
					{
						o_ref_p_prime_global = 1.0;
					}
				}
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements step 7 of 6.3.9 of NIST SP 800-90B.
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="o_ref_r">
			/// </param>
			/// <param name="o_ref_p_local">
			/// </param>
			/// <param name="i_ref_bz_correct">
			/// </param>
			/// <param name="i_refN">
			/// </param>
			/// <param name="o_ref_occurrences_at_longest_run">
			/// </param>
			/// <param name="o_refSSFragmentForLaTeX">
			/// </param>
			/// <param name="i_bIsGeneratingReportInLaTeXformatRequested">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus step7(int& o_ref_r,
				double& o_ref_p_local,
				const blitz::Array<ns_dt::octet, 1>& i_ref_bz_correct,
				const int& i_refN,
				int& o_ref_occurrences_at_longest_run,
				std::wstringstream& o_refSSFragmentForLaTeX,
				bool i_bIsGeneratingReportInLaTeXformatRequested)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				int	r_current = 0;
				int	r_prev = 0;
				// -------------------------------------------------------------------------- //
				// map for LaTeX output
				// -------------------------------------------------------------------------- //
				std::map<int, int>	mp_correct;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				for (int m = 0; m < i_ref_bz_correct.length(blitz::firstDim); ++m)
				{
					if (i_ref_bz_correct(m) == 0)
					{
						if (r_prev < r_current)
						{
							r_prev = r_current;
							r_current = 0;
							// -------------------------------------------------------------------------- //
							// 
							// -------------------------------------------------------------------------- //
							auto	mit = mp_correct.find(r_prev);
							if (mit == mp_correct.cend())
							{
								mp_correct.insert(std::make_pair(r_prev, 1));
							}
							else
							{
								const int count = mit->second;
								mit->second = (count + 1);
							}
						}
					}
					else
					{
						if (0 == m)
						{
							r_current = 1;
						}
						else if (i_ref_bz_correct(m - 1) == 0)
						{
							r_current = 1;
						}
						else if (i_ref_bz_correct(m - 1) == 1)
						{
							++r_current;
						}
					}
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (r_prev < r_current)
				{
					o_ref_r = r_current;
				}
				else
				{
					o_ref_r = r_prev;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				const auto	mit = mp_correct.find(r_current);
				if (mit == mp_correct.cend())
				{
					mp_correct.insert(std::make_pair(r_current, 1));
				}
				else
				{
					const int count = mit->second;
					mit->second = (count + 1);
				}
				// -------------------------------------------------------------------------- //
				// output LaTeX
				// -------------------------------------------------------------------------- //
				if (i_bIsGeneratingReportInLaTeXformatRequested)
				{
					for (const auto& e : mp_correct)
					{
						o_refSSFragmentForLaTeX << L"(";
						o_refSSFragmentForLaTeX << std::setw(8) << e.first << L"," << std::setw(8) << e.second;
						o_refSSFragmentForLaTeX << L")" << L"\n";

						if (e.first == o_ref_r)
						{
							o_ref_occurrences_at_longest_run = e.second;
						}
					}
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				++o_ref_r;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_math::RhsMinusLhs	fnc(o_ref_r, i_refN, 0.99);
				double	lowerbound = pow(0.5, 20.0);
				double	upperbound = 1.0 - pow(0.5, 20.0);
				const boost::math::tools::eps_tolerance<double> tol(std::numeric_limits<double>::digits - 4);
				boost::uintmax_t it = 32;
				const std::pair<double, double>	rg = boost::math::tools::toms748_solve(fnc, lowerbound, upperbound, tol, it);
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				o_ref_p_local = rg.first;

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
			ns_consts::EnmReturnStatus check_args_for_estimate(const ns_dt::t_data_for_v3& i_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				const ns_consts::EnmReturnStatus	stsCommon = ns_spt::perform_common_args_for_estimate(i_refData);
				if (ns_consts::EnmReturnStatus::Success != stsCommon)
				{
					return sts = stsCommon;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				const int	def_D = 16;
				if (i_refData.t_testT3.D != def_D)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements The MultiMMC Prediction Estimate (see 6.3.9 of NIST SP 800-90B).
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
			ns_consts::EnmReturnStatus estimate(ns_dt::t_data_for_v3& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				sts = check_args_for_estimate(io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				int		N = io_refData.p_bzInputDataT3->length(blitz::firstDim) - 2;
				blitz::Array<ns_dt::octet, 1>	bz_correct(N);
				bz_correct = 0;

				ns_dt::NullableT<ns_dt::octet>	nv = { true, 0 };
				blitz::Array<ns_dt::NullableT<ns_dt::octet>, 1>	bz_subpredict(io_refData.t_testT3.D);
				bz_subpredict = nv;

				blitz::Array<int, 1>	bz_entries(io_refData.t_testT3.D);
				// -------------------------------------------------------------------------- //
				// Step 1.
				//  Let D = 16, and N = L - 2. 
				//  Let subpredict be a list of D values, each initialized to Null.
				//  Let correct be an array of N values, each initialized to 0.
				//  Let entries be an array of D values, each initialized to 0,
				//  and let maxEntries = 100 000.
				// -------------------------------------------------------------------------- //
				sts = step1(bz_subpredict, bz_correct, bz_entries, io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Step 2.
				//  For d = 1 to D, let M_{d} be a set of counters, 
				//  where M_{d}[x, y] denotes the number of observed transitions from output x to output y for the d th-order MMC.
				// -------------------------------------------------------------------------- //
				std::vector<ns_es::MarkovModelHistogram*>	setM = std::vector<ns_es::MarkovModelHistogram*>();
				sts = step2(setM, io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Step 3.
				//  Let scoreboard be a list of D counters, each initialized to 0. 
				//  Let winner = 1.
				// -------------------------------------------------------------------------- //
				blitz::Array<int, 1>	bz_scoreboard(io_refData.t_testT3.D);
				bz_scoreboard = 0;

				int		winner = 1;
				// -------------------------------------------------------------------------- //
				// Step 4.
				//  For i = 3 to L:
				//    a. For d = 1 to D:
				//       i. If d < i - 1:
				//          1. 
				// -------------------------------------------------------------------------- //
				sts = step4(setM, bz_subpredict, bz_correct, bz_scoreboard, winner, bz_entries, io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Step 5.
				//  Let C be the number of ones in correct.
				// -------------------------------------------------------------------------- //
				io_refData.t_testT3.C = 0;
				sts = step5(io_refData.t_testT3.C, bz_correct);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Step 6.
				//  Calculate the predictor' s global performance as P_{global} = C / N.
				//  The upper bound of the 99% confidence interval on P_{global}, denoted P'_{global} is calculated as:
				// -------------------------------------------------------------------------- //
				io_refData.t_testT3.p_global = 0;
				io_refData.t_testT3.p_prime_global = 0.0;
				sts = step6(io_refData.t_testT3.p_prime_global, io_refData.t_testT3.p_global, io_refData.t_testT3.C, N);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::wstringstream	ssFragmentForLaTeX;
				// -------------------------------------------------------------------------- //
				// Step 7.
				//  Calculate the predictor's local performance, based on the longest run of correct predictions. 
				//  Let r be one greater than the length of the longest run of ones in correct. 
				//  Use a binary search to solve the following for P_{local}:
				// -------------------------------------------------------------------------- //
				io_refData.t_testT3.p_local = 0.0;
				io_refData.t_testT3.r = 0;
				io_refData.t_testT3.occurrences_at_longest_run = 0;
				sts = step7(io_refData.t_testT3.r, io_refData.t_testT3.p_local, bz_correct, N,
					io_refData.t_testT3.occurrences_at_longest_run, 
					ssFragmentForLaTeX, io_refData.isGeneratingReportInLaTeXformatRequested);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Step 8.
				//  The min-entropy is the negative logarithm of the greater performance metric
				// -------------------------------------------------------------------------- //
				double	one_over_k = 1.0 / static_cast<double>(io_refData.k);
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				double	min_entropy_lower_bound = 0.0;
				double	min_entropy_upper_bound = 0.0;
				double	number_of_significant_digits = 1.0;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.t_testT3.p_prime_global < io_refData.t_testT3.p_local)
				{
					if (io_refData.t_testT3.p_local < one_over_k)
					{
						io_refData.t_testT3.t_common.min_entropy = -log2(one_over_k);
					}
					else
					{
						// -------------------------------------------------------------------------- //
						// 
						// -------------------------------------------------------------------------- //
						io_refData.t_testT3.t_common.min_entropy = -log2(io_refData.t_testT3.p_local);
						// -------------------------------------------------------------------------- //
						// evaluate number of significant digits based on p_local
						// -------------------------------------------------------------------------- //
						ns_consts::EnmReturnStatus	stsNumSignificantDigits = ns_es::evaluateSignificantDigitsOfMinEntropyByPlocalSP800_90B_6_3_7_6_3_10(
							min_entropy_lower_bound, min_entropy_upper_bound,
							number_of_significant_digits, io_refData.t_testT3.r, N, io_refData.k);
						if (ns_consts::EnmReturnStatus::Success == stsNumSignificantDigits)
						{
							io_refData.t_testT3.t_common.number_of_significant_digits = number_of_significant_digits;
							io_refData.t_testT3.t_common.min_entropy_lower_bound = min_entropy_lower_bound;
							io_refData.t_testT3.t_common.min_entropy_upper_bound = min_entropy_upper_bound;
						}
					}
				}
				else
				{
					if (io_refData.t_testT3.p_prime_global < one_over_k)
					{
						io_refData.t_testT3.t_common.min_entropy = -log2(one_over_k);
					}
					else
					{
						// -------------------------------------------------------------------------- //
						// 
						// -------------------------------------------------------------------------- //
						io_refData.t_testT3.t_common.min_entropy = -log2(io_refData.t_testT3.p_prime_global);
						// -------------------------------------------------------------------------- //
						// evaluate number of significant digits based on p_prime_global
						// -------------------------------------------------------------------------- //
						ns_consts::EnmReturnStatus	stsNumSignificantDigits = ns_es::evaluateSignificantDigitsOfMinEntropyByPglobalSP800_90B_6_3_7_6_3_10(
							min_entropy_lower_bound, min_entropy_upper_bound,
							number_of_significant_digits, io_refData.t_testT3.C, N);
						if (ns_consts::EnmReturnStatus::Success == stsNumSignificantDigits)
						{
							io_refData.t_testT3.t_common.number_of_significant_digits = number_of_significant_digits;
							io_refData.t_testT3.t_common.min_entropy_lower_bound = min_entropy_lower_bound;
							io_refData.t_testT3.t_common.min_entropy_upper_bound = min_entropy_upper_bound;
						}
					}
				}
				// -------------------------------------------------------------------------- //
				// as per decision rule by AIS2031An_24
				// -------------------------------------------------------------------------- //
				if (io_refData.t_testT3.t_common.min_entropy < io_refData.t_testT3.threshold) {
					io_refData.t_testT3.t_common.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
				}
				else
				{
					io_refData.t_testT3.t_common.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				io_refData.t_testT3.N = N;
				// -------------------------------------------------------------------------- //
				// output LaTeX
				// -------------------------------------------------------------------------- //
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					outputLaTeXHeader(io_refData);
					if (nullptr != io_refData.p_ssLaTeXFragmentTestT3Body)
					{
						(*io_refData.p_ssLaTeXFragmentTestT3Body) << ssFragmentForLaTeX.rdbuf();
					}
					outputLaTeXFooter(io_refData);
					// -------------------------------------------------------------------------- //
					// supplemental information for traceability
					// -------------------------------------------------------------------------- //
					outputSupplementalInfoLaTeX(io_refData);
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}
		}
	}
}