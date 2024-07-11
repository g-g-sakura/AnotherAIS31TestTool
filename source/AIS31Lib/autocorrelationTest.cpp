////////////////////////////////////////////////////////////////////////////////
// autocorrelationTest.cpp
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#define _USE_MATH_DEFINES
#include <cmath>
#include "support/checkArgs.h"
#include <boost/format.hpp>    // only needed for printing
#include <boost/histogram.hpp>
#include "support/LaTeX.h"

#ifdef _OPENMP
#include <omp.h>
#endif

namespace ais_31_lib
{
	namespace v2
	{
		namespace autocorrelation_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;
			namespace ns_spt = ais_31_lib::support;

			// -------------------------------------------------------------------------- //
			/// <summary>
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
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::wstring	strTitle = std::wstring(L"Test T5 (autocorrelation test)");
				std::wstring	strLabel = std::wstring(L"sec:TestT5");
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
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXSummarySubsubsectionHeader(const ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentWork53)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork53) << L"\\subsubsection{Test values $T_{5}(\\tau_{0})$ for given sets of input data}\\label{sec:TestT5Summary}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork53) << L"\n\n";
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
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus outputLaTeXDetailInfoSubsubsectionHeader(const ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentWork54)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork54) << L"\\subsubsection{Intermediate values $Z_{\\tau}$ for given sets}\\label{sec:TestT5Detail}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork54) << L"\n";
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
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus flushFiguresInLaTeX(const ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragmentWork52)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork52) << L"\\clearpage" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork52) << L"\n\n";
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
			/// <param name="io_refData">
			/// </param>
			/// <param name="i_test_value">
			/// </param>
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
				if (nullptr == io_refData.p_ssLaTeXFragmentWork53)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (257 < io_refData.t_testT5.current_index_in_sets)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorDomain;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (1 == io_refData.t_testT5.current_index_in_sets)
				{
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					outputLaTeXSummarySubsubsectionHeader(io_refData);
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\\begin{figure}[htbp]" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\centering" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\begin{tikzpicture}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\begin{axis}[" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" 	xmin=2200," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	xmax=2800," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	ymin=0," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	xtick distance=50," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	width=24cm," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	xlabel=$T_{5}({\\tau_0})$," << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"	ylabel=\\# of given sets" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" ]" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\addplot[mark size=0.4, draw=blue] coordinates {" << L"\n";
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork53) << L" (";
				(*io_refData.p_ssLaTeXFragmentWork53) << std::right << std::setw(6) << i_test_value;
				(*io_refData.p_ssLaTeXFragmentWork53) << L", ";
				(*io_refData.p_ssLaTeXFragmentWork53) << std::right << std::setw(6) << io_refData.t_testT5.current_index_in_sets;
				(*io_refData.p_ssLaTeXFragmentWork53) << L")" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (257 <= io_refData.t_testT5.current_index_in_sets)
				{
					(*io_refData.p_ssLaTeXFragmentWork53) << L" };" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"coordinates {( 2326, 260) ( 2326, 0)}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"node[above right] at (axis cs: 2326,260) {2326};" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\\addplot+[Nigelle,no marks,sharp plot,update limits=false] " << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"coordinates {( 2674, 260) ( 2674, 0)}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"node[above left] at (axis cs: 2674, 260) {2674};" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\end{axis}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\end{tikzpicture}" << L"\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork53) << L" \\caption{Test values $T_{5}(\\tau_0)$ of given sets}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\\end{figure}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\n\n";
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\\clearpage" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork53) << L"\n\n";
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Output distribution of intermediate $Z_{\tau}$ in LaTeX
			/// </summary>
			/// <remarks>
			/// </remarks>
			/// <param name="io_refData">
			/// </param>
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
			ns_consts::EnmReturnStatus outputEachFigureInLaTeX(const ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.p_ssLaTeXFragment)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (nullptr == io_refData.p_ssLaTeXFragmentWork51)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (nullptr == io_refData.p_ssLaTeXFragmentWork52)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				if (nullptr == io_refData.p_ssLaTeXFragmentWork54)
				{
					return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (1 == io_refData.t_testT5.current_index_in_sets)
				{
					outputLaTeXSubsectionHeader(io_refData);
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				auto	hg = boost::histogram::make_histogram(boost::histogram::axis::regular<>(50, 2200, 2800));

				ns_dt::tpl_tau_map& tau_map = io_refData.t_testT5.pHistogram->get<ns_dt::elem_tau>();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (ns_dt::tpl_tau_map::iterator it = tau_map.begin(); it != tau_map.end(); ++it)
				{
					hg(it->ex_test_value);
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (257 == io_refData.t_testT5.current_index_in_sets)
				{
					(*io_refData.p_ssLaTeXFragmentWork51) << L"\\begin{figure}[h]" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork51) << L"\\begin{tabular}{c}" << L"\n";
				}
				else if (0 == ((io_refData.t_testT5.current_index_in_sets - 1) % 2))
				{
					(*io_refData.p_ssLaTeXFragmentWork51) << L"\\begin{figure}[h]" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork51) << L"\\begin{tabular}{cc}" << L"\n";
				}
				else if (1 == ((io_refData.t_testT5.current_index_in_sets - 1) % 2))
				{
					(*io_refData.p_ssLaTeXFragmentWork51) << L" & " << L"\n";
				}
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\begin{minipage}[t]{0.45\\hsize}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\centering" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"\\tikzset{" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"		every pin/.style={fill=yellow!50!white,rectangle,rounded corners=3pt,font=\\tiny}," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"		small dot/.style={fill=black,circle,scale=0.05}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\begin{tikzpicture}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\begin{axis}[" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" 	ybar," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" 	xmin=2200," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	xmax=2800," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	ymin=0," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	bar width=0.175cm," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	width=10.5cm," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	xlabel=$Z_{\\tau}$," << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"	ylabel=Number" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" ]" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\addplot+[ybar] coordinates {" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t	max_z_tau = 0;
				uint32_t	y_position_for_tau_0 = 0;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (auto&& x : boost::histogram::indexed(hg, boost::histogram::coverage::all))
				{
					if (-std::numeric_limits<double>::infinity() == x.bin().lower())
					{
						continue;
					}
					if (std::numeric_limits<double>::infinity() == x.bin().upper())
					{
						continue;
					}
					(*io_refData.p_ssLaTeXFragmentWork51) << L" (";
					(*io_refData.p_ssLaTeXFragmentWork51) << std::right << std::setw(6) << 0.5 * (x.bin().lower() + x.bin().upper());
					(*io_refData.p_ssLaTeXFragmentWork51) << L", "; 
					(*io_refData.p_ssLaTeXFragmentWork51) << std::right << std::setw(6) << *x;
					(*io_refData.p_ssLaTeXFragmentWork51) << L")" << L"\n";
					if (max_z_tau < *x)
					{
						max_z_tau = *x;
					}

					if ((x.bin().lower() < io_refData.t_testT5.z_resulting_tau_0) && (io_refData.t_testT5.z_resulting_tau_0 < x.bin().upper()))
					{
						y_position_for_tau_0 = *x;
					}
				}
				(*io_refData.p_ssLaTeXFragmentWork51) << L" };" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork51) << L"\\addplot+[Nigelle,sharp plot,update limits=false] " << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"coordinates {";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"(" << io_refData.t_testT5.z_resulting_tau_0 << L", " << floor(0.5 * max_z_tau) << L")";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"(" << io_refData.t_testT5.z_resulting_tau_0 << L", " << y_position_for_tau_0 << L")";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"node[above, yshift=35mm]      at (axis cs:";
				(*io_refData.p_ssLaTeXFragmentWork51) << io_refData.t_testT5.z_resulting_tau_0 << L", " << y_position_for_tau_0 << L")";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"{selected $\\tau_{0} = " << io_refData.t_testT5.tau_0 << L"$};";
				(*io_refData.p_ssLaTeXFragmentWork51) << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\end{axis}" << L"\n";
				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\end{tikzpicture}" << L"\n";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::wstringstream	ssWork1 = std::wstringstream();
				ssWork1 << L"Histogram of $Z_{\\tau}$ for the ";
				ssWork1 << io_refData.t_testT5.current_index_in_sets;
				switch (io_refData.t_testT5.current_index_in_sets)
				{
				case 1:
					ssWork1 << L"-st set. ";
					break;
				case 2:
					ssWork1 << L"-nd set. ";
					break;
				case 3:
					ssWork1 << L"-rd set. ";
					break;
				default:
					ssWork1 << L"-th set. ";
					break;
				}

				(*io_refData.p_ssLaTeXFragmentWork51) << L" \\caption[";
				(*io_refData.p_ssLaTeXFragmentWork51) << ssWork1.str();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork51) << L"]{";	//
				(*io_refData.p_ssLaTeXFragmentWork51) << ssWork1.str();
				ssWork1.clear();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				(*io_refData.p_ssLaTeXFragmentWork52) << L"} \n";	//
				(*io_refData.p_ssLaTeXFragmentWork52) << L" \\end{minipage}";
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if ((1 == ((io_refData.t_testT5.current_index_in_sets - 1) % 2))
					|| (257 <= io_refData.t_testT5.current_index_in_sets))
				{
					(*io_refData.p_ssLaTeXFragmentWork52) << L" \\end{tabular}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork52) << L"\\end{figure}" << L"\n";
					(*io_refData.p_ssLaTeXFragmentWork52) << L"\n\n";
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if ((0 != io_refData.t_testT5.current_index_in_sets - 1) && (0 == io_refData.t_testT5.current_index_in_sets % 6))
				{
					flushFiguresInLaTeX(io_refData);
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
				// as per paragraph 199 of AIS 20/31 - Version 2.0
				// -------------------------------------------------------------------------- //
				size_t	input_data_size = i_refData.p_bzInterpretedBj->size();
				if (input_data_size < 20000)
				{
					sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (nullptr == i_refData.t_testT5.pHistogram)
				{
					sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
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
			/// <param name="io_refData">
			/// </param>
			/// <param name="o_ref_test_value">
			/// </param>
			/// <param name="i_tau">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus computeTestValueForSpecificTau(const ns_dt::t_data_for_v2& io_refData, 
				uint32_t &o_ref_test_value, uint32_t i_tau)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t T_5_tau = 0;
				int		pos;
				uint32_t	rhs;

				#pragma omp parallel for reduction(+:T_5_tau) private(pos, rhs)
				for (int j = 0; j < 5000; ++j)
				{
					pos = j + io_refData.t_testT5.offset_for_tau;
					rhs = 0x01 & ((*io_refData.p_bzInterpretedBj)(pos) ^ (*io_refData.p_bzInterpretedBj)(pos + i_tau));
					T_5_tau += rhs;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_ref_test_value = T_5_tau;
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
			/// <param name="io_refData">
			/// </param>
			/// <returns>
			/// </returns>
			/// <precondition>
			/// </precondition>
			/// <postcondition>
			/// </postcondition>
			// -------------------------------------------------------------------------- //
			ns_consts::EnmReturnStatus computeTestValues(ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.t_testT5.pHistogram)
				{
					return sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				for (unsigned int tau = 1; tau <= 5000; ++tau)
				{
					uint32_t T_5_tau = 0;
					sts = computeTestValueForSpecificTau(io_refData, T_5_tau, tau);
					if (ns_consts::EnmReturnStatus::Success != sts)
					{
						return sts;
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.t_testT5.p_bzZTau)(tau - 1) = T_5_tau;
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					io_refData.t_testT5.pHistogram->insert(ns_dt::t_element_test_value(tau, T_5_tau));
				}

				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
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
			ns_consts::EnmReturnStatus determineTau0(ns_dt::t_data_for_v2& io_refData)
			{
				ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (nullptr == io_refData.t_testT5.pHistogram)
				{
					return sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t	max_delta_candidates[2] = { 0, 0 };
				uint32_t	test_values[2] = {0, 0};
				ns_dt::tpl_test_value_map& test_value_map = io_refData.t_testT5.pHistogram->get<ns_dt::elem_test_value>();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_dt::tpl_test_value_map::reverse_iterator	rit_tv_max = test_value_map.rbegin();
				test_values[1] = rit_tv_max->ex_test_value;
				if (2500 <= test_values[1])
				{
					max_delta_candidates[1] = test_values[1] - 2500;
				}
				else
				{
					max_delta_candidates[1] = 2500 - test_values[1];
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_dt::tpl_test_value_map::iterator	it_tv_min = test_value_map.begin();
				test_values[0] = it_tv_min->ex_test_value;
				if (2500 <= test_values[0])
				{
					max_delta_candidates[0] = test_values[0] - 2500;
				}
				else
				{
					max_delta_candidates[0] = 2500 - test_values[0];
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t* p_test_value = nullptr;
				if (max_delta_candidates[0] < max_delta_candidates[1])
				{
					p_test_value = &test_values[1];
				}
				else
				{
					p_test_value = &test_values[0];
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (1 <= io_refData.verbose_level)
				{
					if (test_values[0] <= io_refData.t_testT5.th.lower_bound)
					{
						std::wcout << L"# [INFO]: At " << io_refData.t_testT5.current_index_in_sets << L"-th set, ";
						std::wcout << L"# [INFO]: non-zero test value was found at $\\tau$ = " << test_values[0] << L", ";
						std::wcout << L"# [INFO]: which is less than or equal to 2326. "  << L"\n";
					}
					if (io_refData.t_testT5.th.upper_bound <= test_values[1])
					{
						std::wcout << L"# [INFO]: At " << io_refData.t_testT5.current_index_in_sets << L"-th set, " << L"\n";
						std::wcout << L"# [INFO]: non-zero test value was found at $\\tau$ = " << test_values[1] << L", " << L"\n";
						std::wcout << L"# [INFO]: which is greater than or equal to 2674. " << L"\n";
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				std::pair<ns_dt::tpl_test_value_map::iterator, ns_dt::tpl_test_value_map::iterator> rg_x = test_value_map.equal_range(*p_test_value);

				if (rg_x.first != rg_x.second)
				{
					// -------------------------------------------------------------------------- //
					// determine multiplicity of candidates
					// -------------------------------------------------------------------------- //
					unsigned long long	multiplicity = 0;
					for (ns_dt::tpl_test_value_map::iterator it = rg_x.first; it != rg_x.second; ++it)
					{
						++multiplicity;
					}
					// -------------------------------------------------------------------------- //
					// generate random number
					// -------------------------------------------------------------------------- //
					unsigned long long      ullRandom = 1;
					int     rv = 0;
					do
					{
						rv = _rdrand64_step(&ullRandom);
					} while (0 == rv);
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					const unsigned long long		pos = ullRandom % (unsigned long long)multiplicity;
					// -------------------------------------------------------------------------- //
					// randomly select $\tau_0$ in case of several candidates
					// -------------------------------------------------------------------------- //
					unsigned long long j = 0;
					for (ns_dt::tpl_test_value_map::iterator it = rg_x.first; it != rg_x.second; ++it)
					{
						if (pos == j)
						{
							io_refData.t_testT5.tau_0 = it->ex_tau;
							io_refData.t_testT5.z_resulting_tau_0 = it->ex_test_value;
						}
						++j;
					}
				}
				else
				{
					// only one candidate
					io_refData.t_testT5.tau_0 = rg_x.first->ex_tau;
					io_refData.t_testT5.z_resulting_tau_0 = rg_x.first->ex_test_value;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

			// -------------------------------------------------------------------------- //
			/// <summary>
			///  Implements autocorrelation test as specified in AIS 20/31 - Version 2.0
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
				ns_consts::EnmReturnStatus	stsReport = ns_consts::EnmReturnStatus::ErrorUnexpected;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				sts = checkArgsForPerformTest(io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT5.offset_for_tau = 0;
				// -------------------------------------------------------------------------- //
				// Compute the test values as per (46) in AIS 20/31 Version 2.0
				// -------------------------------------------------------------------------- //
				sts = computeTestValues(io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// Determine $\tau_0$
				// -------------------------------------------------------------------------- //
				sts = determineTau0(io_refData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					io_refData.p_ssLaTeXFragmentWork51->clear();
					io_refData.p_ssLaTeXFragmentWork52->clear();
					stsReport = outputEachFigureInLaTeX(io_refData);
					if (ns_consts::EnmReturnStatus::Success != stsReport)
					{
						return sts = stsReport;
					}
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT5.offset_for_tau = 10000;
				io_refData.t_testT5.pHistogram->clear();
				(*io_refData.t_testT5.p_bzZTau) = 0;
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				uint32_t	test_value = 0;
				sts = computeTestValueForSpecificTau(io_refData, test_value, io_refData.t_testT5.tau_0);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return sts;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					stsReport = outputEachTestValueForSummaryFigureInLaTeX(io_refData, test_value);
					if (ns_consts::EnmReturnStatus::Success != stsReport)
					{
						return sts = stsReport;
					}
				}
				// -------------------------------------------------------------------------- //
				// apply Evaluation rule
				// -------------------------------------------------------------------------- //
				if ((test_value <= io_refData.t_testT5.th.lower_bound) || (io_refData.t_testT5.th.upper_bound <= test_value))
				{
					io_refData.t_testT5.pass_fail_result = ns_consts::EnmPassFailResults::Fail;
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					if (1 <= io_refData.verbose_level)
					{
						std::wcout << L"# [INFO]: At " << io_refData.t_testT5.current_index_in_sets << L"-th set, " << L"\n";
						std::wcout << L"# [INFO]: this test failed at shift $\\tau_{0}$ = " << io_refData.t_testT5.tau_0 << L", " << L"\n";
						std::wcout << L"# [INFO]: and the test value was " << test_value << L". \n";
					}
				}
				else
				{
					io_refData.t_testT5.pass_fail_result = ns_consts::EnmPassFailResults::Pass;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (io_refData.isGeneratingReportInLaTeXformatRequested)
				{
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					std::wstringstream	ssWork = std::wstringstream();

					if (ns_consts::EnmPassFailResults::Fail == io_refData.t_testT5.pass_fail_result)
					{
						ssWork << L"Test result was \\textcolor{red}{Fail}, and $T_{5}(\\tau_{0} = ";
						ssWork << io_refData.t_testT5.tau_0 << L")$ = ";
						ssWork << test_value << L", which is ";
						if (test_value <= 2326)
						{
							ssWork << L"less than or equal to 2326. ";
						}
						else if (2674 <= test_value)
						{
							ssWork << L"greater than or equal to 2674. ";
						}
					}
					else if (ns_consts::EnmPassFailResults::Pass == io_refData.t_testT5.pass_fail_result)
					{
						ssWork << L"Test result was Pass, and $T_{5}(\\tau_{0} = ";
						ssWork << io_refData.t_testT5.tau_0 << L")$ = ";
						ssWork << test_value << L", which is in range [2327, 2673]. ";
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					if (1 == io_refData.t_testT5.current_index_in_sets)
					{
						stsReport = outputLaTeXDetailInfoSubsubsectionHeader(io_refData);
						if (ns_consts::EnmReturnStatus::Success != stsReport)
						{
							return sts = stsReport;
						}
					}
					// -------------------------------------------------------------------------- //
					// 
					// -------------------------------------------------------------------------- //
					(*io_refData.p_ssLaTeXFragmentWork54) << io_refData.p_ssLaTeXFragmentWork51->rdbuf();
					(*io_refData.p_ssLaTeXFragmentWork54) << ssWork.rdbuf();
					(*io_refData.p_ssLaTeXFragmentWork54) << io_refData.p_ssLaTeXFragmentWork52->rdbuf();
					io_refData.p_ssLaTeXFragmentWork51->clear();
					io_refData.p_ssLaTeXFragmentWork52->clear();
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				io_refData.t_testT5.pHistogram->clear();
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				return sts = ns_consts::EnmReturnStatus::Success;
			}

		}
	}
}