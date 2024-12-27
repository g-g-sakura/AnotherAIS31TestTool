////////////////////////////////////////////////////////////////////////////////
// TestData.h
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_TEST_DATA_H
#define AIS_31_LIB_TEST_DATA_H

#include <cstdint>
#include <blitz/array.h>
#include "constants.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>

namespace ais_31_lib
{
	namespace data_types
	{

		namespace aisconsts = ais_31_lib::constants;

		typedef unsigned char	octet;

		template<typename T>	struct NullableT
		{
			bool	bIsValueNull;
			T		value;
		};

		typedef struct _TDataCommon
		{
			// -------------------------------------------------------------------------- //
			// variables originally introduced by AIS 20/31
			// -------------------------------------------------------------------------- //
			double	test_value;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;

			// -------------------------------------------------------------------------- //
			// variables taken from NIST SP 800-90B
			// -------------------------------------------------------------------------- //
			double	min_entropy;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			double	min_entropy_lower_bound;
			double	min_entropy_upper_bound;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			double	number_of_significant_digits;
		} t_data_common;

		typedef struct _TThresholdData
		{
			uint32_t	lower_bound;
			uint32_t	upper_bound;
		} threshold;

		typedef struct _TDataForPerformanceInfo
		{
			tm		startTime;
			int64_t		start_delta_microseconds;
			tm		endTime;
			tm		duration;
		} t_data_for_performance_info;

		typedef struct _TDataForMonobitTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c1;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double		test_value_T1;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			threshold	th;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_monobit_test;

		typedef struct _TDataForPokerTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double		test_value_T2;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// lower bound of threshold, non-inclusive
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double	threshold_lower_bound;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// upper bound of threshold, non-inclusive
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double	threshold_upper_bound;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_poker_test;

		typedef struct _TDataForMultiMMCPredictionEstimate
		{
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_common					t_common;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double		test_value_T3;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			double	p_local;
			double	p_prime_global;
			double	p_global;

			int		r;
			int		occurrences_at_longest_run;

			int		D;
			int		N;
			int		C;
			int		maxEntries;
			// -------------------------------------------------------------------------- //
			// constant introduced by AIS 20/31
			// -------------------------------------------------------------------------- //
			double	threshold;
		} t_data_for_multi_mmc_prediction_estimate;

		typedef struct _TDataForLZ78YPredictionEstimate
		{
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_common					t_common;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double		test_value_T4;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			double	p_local;
			double	p_prime_global;
			double	p_global;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			int		r;
			int		occurrences_at_longest_run;

			int		B;
			int		N;
			int		C;
			int		maxDictionarySize;
			// -------------------------------------------------------------------------- //
			// constant introduced by AIS 20/31
			// -------------------------------------------------------------------------- //
			double	threshold;
		} t_data_for_lz78_y_prediction_estimate;

		typedef struct _TDataForTestResultSummary
		{
			// -------------------------------------------------------------------------- //
			// overall test result
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	overall_test_result;
			// -------------------------------------------------------------------------- //
			// max 2 trials, 4 tests (Test T1 - T4)
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_results[2][4];
		} t_data_for_test_result_summary;

		typedef struct _TDataForTestSuitesV3
		{
			unsigned int			k;	// size of alphabet
			unsigned int			L;	// size of input
			unsigned int			bits_per_sample;	//
			blitz::Array<octet, 1>* p_bzUnprocessedData;
			blitz::Array<octet, 1> *p_bzInputDataT1;
			blitz::Array<octet, 1> *p_bzInputDataT2;
			blitz::Array<octet, 1> *p_bzInputDataT3;
			blitz::Array<octet, 1> *p_bzInputDataT4;
			blitz::Array<octet, 1> *p_bzInterpretedBj;		// $b_{j}$
			bool					bIsMSbFirstByteBitConversion;
			// -------------------------------------------------------------------------- //
			// for Test T1
			// -------------------------------------------------------------------------- //
			t_data_for_monobit_test						t_testT1;
			// -------------------------------------------------------------------------- //
			// for Test T2
			// -------------------------------------------------------------------------- //
			t_data_for_poker_test						t_testT2;
			// -------------------------------------------------------------------------- //
			// for Test T3
			// -------------------------------------------------------------------------- //
			t_data_for_multi_mmc_prediction_estimate	t_testT3;
			// -------------------------------------------------------------------------- //
			// for Test T4
			// -------------------------------------------------------------------------- //
			t_data_for_lz78_y_prediction_estimate		t_testT4;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			bool		areT1ThroughT4Selected;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			bool		isGeneratingReportInLaTeXformatRequested;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			int			verbose_level;	//
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			unsigned int			current_number_of_round_in_trials;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_test_result_summary	test_result_summary;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragment;
			// -------------------------------------------------------------------------- //
			// for Test T1
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentTestT1Header;
			std::wstringstream* p_ssLaTeXFragmentTestT1Body;
			// -------------------------------------------------------------------------- //
			// for Test T2
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentTestT2Header;
			std::wstringstream* p_ssLaTeXFragmentTestT2Body;
			// -------------------------------------------------------------------------- //
			// for Test T3
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentTestT3Header;
			std::wstringstream* p_ssLaTeXFragmentTestT3Body;
			// -------------------------------------------------------------------------- //
			// for Test T4
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentTestT4Header;
			std::wstringstream* p_ssLaTeXFragmentTestT4Body;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
		} t_data_for_v3;

	}
}

#endif