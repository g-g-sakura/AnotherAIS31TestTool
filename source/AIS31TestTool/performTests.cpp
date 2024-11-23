////////////////////////////////////////////////////////////////////////////////
// performTests.cpp
//
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "performTests.h"
#include "parse.h"
#include "synthesizeFilename.h"
#include "loadInputData.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <AIS31Lib/MonobitTests.h>      // T1
#include <AIS31Lib/pokerTest.h>         // T2
#include <AIS31Lib/MultiMMCPredictionEstimate.h>	// T3
#include <AIS31Lib/LZ78YPredictionEstimate.h> // T4
#include <AIS31Lib/support/showTestSummary.h>
#include <locale>
#include <Windows.h>


namespace ais_31_tool
{
	typedef ns_consts::EnmReturnStatus(*PF_EE)(ns_dt::t_data_for_v3&);

	ns_consts::EnmReturnStatus performTests(ns_dt::t_data_for_v3& io_refData,
		IDInfoForReport& i_refInfoReport)
	{
		PF_EE	func_tests[5] = {
							ais_31_lib::v3::monobit_test::performTest,
							ais_31_lib::v3::poker_test::performTest,
							ais_31_lib::predictors::multimmc_prediction::estimate,
							ais_31_lib::predictors::lz78y_prediction::estimate,
							nullptr
		};

		ns_consts::EnmAIS20AIS31V3Track   enm_test[] = {
				ns_consts::EnmAIS20AIS31V3Track::TestT1,
				ns_consts::EnmAIS20AIS31V3Track::TestT2,
				ns_consts::EnmAIS20AIS31V3Track::TestT3,
				ns_consts::EnmAIS20AIS31V3Track::TestT4
		};

		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::stringstream ss = std::stringstream();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ns_dt::t_data_for_v3* pData = &io_refData;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ns_consts::EnmPassFailResults	pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::NotDetermined;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		constexpr uintmax_t	cui_required_number_of_bits_lowerbound = 2040000;
		const uintmax_t max_iterations = (io_refData.L + cui_required_number_of_bits_lowerbound - 1) / cui_required_number_of_bits_lowerbound;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		setlocale(LC_ALL, "");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		// -------------------------------------------------------------------------- //
		// perform tests
		// -------------------------------------------------------------------------- //
		uintmax_t s = 0;
		do {
			if (0 < s)
			{
				ss << "\n" << "\n";
				ss << "# -------------------------------------------------------------------------- " << "\n";
				ss << "# [INFO]: The first trial of Tirn blackbox test suite has failed." << "\n";
				ss << "# [INFO]: The second trial of Tirn blackbox test suite is applied." << "\n";
				ss << "\n";
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			pData->current_number_of_round_in_trials = s + 1;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::NotDetermined;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			for (int j = 0; j < 4; ++j)
			{
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (nullptr == pData)
				{
					// should not reach here
					return sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_consts::EnmReturnStatus stsLoadSamples;
				// -------------------------------------------------------------------------- //
				// show case specific header
				// -------------------------------------------------------------------------- //
				ns_consts::EnmReturnStatus stsShowInfo = ais_31_lib::support::showTestSpecificHeader(ss, enm_test[j],
					*pData);
				if (ns_consts::EnmReturnStatus::Success != stsShowInfo)
				{
					return  sts = stsShowInfo;
				}
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				ns_consts::EnmPassFailResults* p_current_pass_fail = nullptr;
				switch (j)
				{
				case 0:
					p_current_pass_fail = &(pData->t_testT1.pass_fail_result);
					break;
				case 1:
					p_current_pass_fail = &(pData->t_testT2.pass_fail_result);
					break;
				case 2:
					p_current_pass_fail = &(pData->t_testT3.t_common.pass_fail_result);
					break;
				case 3:
					p_current_pass_fail = &(pData->t_testT4.t_common.pass_fail_result);
					break;
				default:
					break;
				}
				// -------------------------------------------------------------------------- //
				// purposely overwrite bits per sample for Tests T3 and T4
				// -------------------------------------------------------------------------- //
				int	bits_per_sample_restore = pData->bits_per_sample;
				switch (j)
				{
				case 2:
				case 3:
					pData->bits_per_sample = 1;
					break;
				default:
					break;
				}
				// -------------------------------------------------------------------------- //
				// perform test
				// -------------------------------------------------------------------------- //
				sts = (*func_tests[j])(*pData);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
					std::cout << "# [ERROR]: The test was terminated..." << std::endl;
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					return  sts;
				}
				// -------------------------------------------------------------------------- //
				// restoring bits per sample
				// -------------------------------------------------------------------------- //
				pData->bits_per_sample = bits_per_sample_restore;
				// -------------------------------------------------------------------------- //
				// detecting fail for each set
				// -------------------------------------------------------------------------- //
				if (nullptr != p_current_pass_fail)
				{
					if (ns_consts::EnmPassFailResults::Fail == *p_current_pass_fail)
					{
						pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::Fail;
					}
				}
				// -------------------------------------------------------------------------- //
				// record pass/fail to test result summary
				// -------------------------------------------------------------------------- //
				pData->test_result_summary.pass_fail_results[s][j] = *p_current_pass_fail;
				// -------------------------------------------------------------------------- //
				// show case specific footer
				// -------------------------------------------------------------------------- //
				stsShowInfo = ais_31_lib::support::showTestSpecificFooter(ss, enm_test[j],
					*pData);
				if (ns_consts::EnmReturnStatus::Success != stsShowInfo)
				{
					return  sts = stsShowInfo;
				}
				// -------------------------------------------------------------------------- //
				// show test result
				// -------------------------------------------------------------------------- //
				stsShowInfo = ais_31_lib::support::showTestSpecificResult(ss, enm_test[j],
					*pData);
				if (ns_consts::EnmReturnStatus::Success != stsShowInfo)
				{
					return  sts = stsShowInfo;
				}
				// -------------------------------------------------------------------------- //
				// load input data from unprocessed data
				// -------------------------------------------------------------------------- //
				ns_consts::EnmAIS20AIS31V3Track   next_test = ns_consts::EnmAIS20AIS31V3Track::TestT1;
				if (j < 3)
				{
					next_test = enm_test[j + 1];
				}
				else
				{
					next_test = ns_consts::EnmAIS20AIS31V3Track::TestT1;
				}
				if (!((max_iterations == s) && (3 == j)))
				{
					stsLoadSamples = loadSamplesForTest(*pData, i_refInfoReport, next_test);
					if (ns_consts::EnmReturnStatus::Success != stsLoadSamples)
					{
						return  sts = stsLoadSamples;
					}
				}
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			++s;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
		} while ((ns_consts::EnmPassFailResults::Fail == pass_fail_result_over_multiple_sets) && (s < max_iterations));
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (ns_consts::EnmPassFailResults::NotDetermined == pass_fail_result_over_multiple_sets)
		{
			pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::Pass;
		}
		io_refData.test_result_summary.overall_test_result = pass_fail_result_over_multiple_sets;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		return  sts;
	}
}