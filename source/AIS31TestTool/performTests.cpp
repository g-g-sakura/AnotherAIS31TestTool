////////////////////////////////////////////////////////////////////////////////
// runTests.cpp
//
//
//
// Copyright (c) 2021-2023 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "performTests.h"
#include "parse.h"
#include "synthesizeFilename.h"
#include "reportItems.h"
#include "loadInputData.h"
#include <AIS31Lib/support/setUp.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <AIS31Lib/DisjointnessTest.h>  // T0
#include <AIS31Lib/MonobitTests.h>      // T1
#include <AIS31Lib/pokerTest.h>         // T2
#include <AIS31Lib/runsTest.h>          // T3
#include <AIS31Lib/longRunTest.h>       // T4
#include <AIS31Lib/autocorrelationTest.h>   // T5
#include <AIS31Lib/support/showTestSummary.h>


namespace ais_31_tool
{
    typedef ns_consts::EnmReturnStatus(*PF_EE)(ns_dt::t_data_for_v2&);

    ns_consts::EnmReturnStatus performTests(ns_dt::t_data_for_v2& io_refData)
    {
        PF_EE	func_tests[7] = {
                            ais_31_lib::v2::disjointness_test::performTest,
                            ais_31_lib::v2::monobit_test::performTest,
                            ais_31_lib::v2::poker_test::performTest,
                            ais_31_lib::v2::runs_test::performTest,
                            ais_31_lib::v2::long_run_test::performTest,
                            ais_31_lib::v2::autocorrelation_test::performTest,
                            nullptr
        };

        ns_consts::EnmAIS20AIS31V2Track   enm_test[] = {
                ns_consts::EnmAIS20AIS31V2Track::TestT0,
                ns_consts::EnmAIS20AIS31V2Track::TestT1,
                ns_consts::EnmAIS20AIS31V2Track::TestT2,
                ns_consts::EnmAIS20AIS31V2Track::TestT3,
                ns_consts::EnmAIS20AIS31V2Track::TestT4,
                ns_consts::EnmAIS20AIS31V2Track::TestT5,
                ns_consts::EnmAIS20AIS31V2Track::TestT6,
                ns_consts::EnmAIS20AIS31V2Track::TestT7,
                ns_consts::EnmAIS20AIS31V2Track::TestT8
        };

        ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
        // -------------------------------------------------------------------------- //
        // 
        // -------------------------------------------------------------------------- //
        std::stringstream ss = std::stringstream();
        // -------------------------------------------------------------------------- //
        // 
        // -------------------------------------------------------------------------- //
        ns_dt::t_data_for_v2* pData = &io_refData;
        if (io_refData.isT0Selected)
        {
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            for (int j = 0; j < 1; ++j)
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
                // show case specific header
                // -------------------------------------------------------------------------- //
                ns_consts::EnmReturnStatus stsShowInfo = ais_31_lib::support::showTestSpecificHeader(ss, enm_test[j],
                    *pData);
                if (ns_consts::EnmReturnStatus::Success != stsShowInfo)
                {
                    return  sts = stsShowInfo;
                }
                // -------------------------------------------------------------------------- //
                // perform test
                // -------------------------------------------------------------------------- //
                sts = (*func_tests[j])(*pData);
                if (ns_consts::EnmReturnStatus::Success != sts)
                {
                    std::cout << "The test was terminated..." << std::endl;
                    return  sts;
                }
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
            }
        }
        if (io_refData.areT1ThroughT5Selected)
        {
            for (int j = 1; j < 6; ++j)
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
                case 1:
                    p_current_pass_fail = &(pData->t_testT1.pass_fail_result);
                    break;
                case 2:
                    p_current_pass_fail = &(pData->t_testT2.pass_fail_result);
                    break;
                case 3:
                    p_current_pass_fail = &(pData->t_testT3.pass_fail_result);
                    break;
                case 4:
                    p_current_pass_fail = &(pData->t_testT4.pass_fail_result);
                    break;
                case 5:
                    p_current_pass_fail = &(pData->t_testT5.pass_fail_result);
                    break;
                default:
                    break;
                }
                // -------------------------------------------------------------------------- //
                // perform tests
                // -------------------------------------------------------------------------- //
                ns_consts::EnmPassFailResults	pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::NotDetermined;
                for (int s = 0; s < 257; ++s)
                {
                    // -------------------------------------------------------------------------- //
                    // autocorrelation test specific setting
                    // -------------------------------------------------------------------------- //
                    switch (j)
                    {
                    case 1:
                        pData->t_testT1.current_index_in_sets = s + 1;
                        break;
                    case 2:
                        pData->t_testT2.current_index_in_sets = s + 1;
                        break;
                    case 3:
                        pData->t_testT3.current_index_in_sets = s + 1;
                        break;
                    case 5:
                        pData->t_testT5.current_index_in_sets = s + 1;
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
                        std::cout << "The test was terminated..." << std::endl;
                        return  sts;
                    }
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
                    // merge LaTeX output for autocorrelation test
                    // -------------------------------------------------------------------------- //
                    if (5 == j)
                    {
                        if (pData->isGeneratingReportInLaTeXformatRequested)
                        {
                            if (256 == s)
                            {
                                (*(pData->p_ssLaTeXFragment)) << pData->p_ssLaTeXFragmentWork53->rdbuf();
                                (*(pData->p_ssLaTeXFragment)) << pData->p_ssLaTeXFragmentWork54->rdbuf();
                                pData->p_ssLaTeXFragmentWork53->clear();
                                pData->p_ssLaTeXFragmentWork54->clear();
                            }
                        }
                    }
                    // -------------------------------------------------------------------------- //
                    // prepare projected $b_{j}$ for next set
                    // -------------------------------------------------------------------------- //
                    if (s < 256)
                    {
                        sts = ais_31_tool::performProjection(*pData, s + 1);
                        if (ns_consts::EnmReturnStatus::Success != sts)
                        {
                            std::cout << "The test was terminated due to an error in constructing $b_{j}$." << std::endl;
                            return  sts;
                        }
                    }
                }
                // -------------------------------------------------------------------------- //
                // 
                // -------------------------------------------------------------------------- //
                if (ns_consts::EnmPassFailResults::NotDetermined == pass_fail_result_over_multiple_sets)
                {
                    pass_fail_result_over_multiple_sets = ns_consts::EnmPassFailResults::Pass;
                }
                // -------------------------------------------------------------------------- //
                // write back
                // -------------------------------------------------------------------------- //
                *p_current_pass_fail = pass_fail_result_over_multiple_sets;
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
            }
        }
        // -------------------------------------------------------------------------- //
        // 
        // -------------------------------------------------------------------------- //
        return  sts;
    }
}