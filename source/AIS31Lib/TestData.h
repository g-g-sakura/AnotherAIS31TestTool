////////////////////////////////////////////////////////////////////////////////
// TestData.h
//
//
//
// Copyright (c) 2023 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS_31_LIB_TEST_DATA_H__
#define __AIS_31_LIB_TEST_DATA_H__

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

		typedef struct _TDataCommon
		{
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			double	test_value;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
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

		typedef struct _TDataForDisjointnessTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c1;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			blitz::Array<uint64_t, 1>* p_bzProjectedData;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_disjointness_test;

		typedef struct _TDataForMonobitTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c2;
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
			uint32_t	current_index_in_sets;
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
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c2;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			double		test_value_T2;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			//blitz::Array<octet, 1>* p_bzInterpretedBj;
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
			uint32_t	current_index_in_sets;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_poker_test;


		typedef struct _TDataForRunsTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c2;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			blitz::Array<uint32_t, 2>* p_bzTestValue;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			threshold	th[7];
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			uint32_t	current_index_in_sets;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_runs_test;

		typedef struct _TDataForLongRunTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c2;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			blitz::Array<uint32_t, 2>* p_bzTestValue;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			octet			p_of_longest_run;
			uint32_t		longest_run;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_long_run_test;


		namespace bmi = boost::multi_index;
		using boost::multi_index_container;

		struct t_element_test_value
		{
			uint32_t		ex_tau;		// shift $\tau$
			uint32_t		ex_test_value;		// test value

			t_element_test_value(const uint32_t& i_tau, uint32_t i_test_value) : ex_tau(i_tau), ex_test_value(i_test_value) {}

			bool operator <(t_element_test_value const& i_refRight) const
			{
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (ex_test_value != i_refRight.ex_test_value)
				{
					return	ex_test_value < i_refRight.ex_test_value;
				}
				else
				{
					return	ex_tau < i_refRight.ex_tau;
				}
			}
		};

		struct elem_tau {};
		struct elem_test_value {};

		typedef bmi::multi_index_container<
			t_element_test_value,
			bmi::indexed_by<
			bmi::ordered_unique<bmi::identity<t_element_test_value> >, //
			bmi::ordered_unique<bmi::tag<elem_tau>, bmi::member<t_element_test_value, uint32_t, &t_element_test_value::ex_tau> >,
			bmi::ordered_non_unique<bmi::tag<elem_test_value>, bmi::member<t_element_test_value, uint32_t, &t_element_test_value::ex_test_value> >
			>
		> TestValueHistogram;

		typedef TestValueHistogram::index<elem_tau>::type tpl_tau_map;
		typedef TestValueHistogram::index<elem_test_value>::type tpl_test_value_map;


		typedef struct _TDataForAutocorrelationTest
		{
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// 
			/// </summary>
			/// -------------------------------------------------------------------------- //
			uint64_t	c2;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// lower bound of threshold, non-inclusive
			/// </summary>
			/// -------------------------------------------------------------------------- //
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// upper bound of threshold, non-inclusive
			/// </summary>
			/// -------------------------------------------------------------------------- //
			threshold	th;
			/// -------------------------------------------------------------------------- //
			/// <summary>
			/// test value
			/// </summary>
			/// -------------------------------------------------------------------------- //
			blitz::Array<uint32_t, 1>* p_bzZTau;
			blitz::Array<uint32_t, 1>* p_bzTestValue;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			uint32_t	offset_for_tau;
			uint32_t	tau_0;
			uint32_t	z_resulting_tau_0;
			TestValueHistogram*		pHistogram;
			uint32_t	current_index_in_sets;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			aisconsts::EnmPassFailResults	pass_fail_result;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_performance_info		t_performance;
		} t_data_for_autocorrelation_test;

		typedef struct _TDataForTestSuitesV2
		{
			unsigned int			k;	// size of alphabet
			unsigned int			L;	// size of input
			unsigned int			bits_per_sample;	//
			blitz::Array<octet, 1>* p_bzSampleSpaceA;
			blitz::Array<octet, 1>* p_bzInputDataT0;
			blitz::Array<octet, 2>* p_bzInputDataT1;
			blitz::Array<octet, 1>* p_bzInterpretedBj;		// $b_{j}$
			bool					bIsMSbFirstByteBitConversion;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			unsigned long			offsetOfInputDataFilesIndex;
			size_t					numberOfDigitsOfOffset;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			t_data_for_disjointness_test	t_testT0;
			t_data_for_monobit_test			t_testT1;
			t_data_for_poker_test			t_testT2;
			t_data_for_runs_test			t_testT3;
			t_data_for_long_run_test		t_testT4;
			t_data_for_autocorrelation_test	t_testT5;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			bool		isT0Selected;
			bool		areT1ThroughT5Selected;
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
			std::wstringstream* p_ssLaTeXFragment;
			// -------------------------------------------------------------------------- //
			// for Test T3
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentWork3[6][2];
			// -------------------------------------------------------------------------- //
			// for Test T5
			// -------------------------------------------------------------------------- //
			std::wstringstream* p_ssLaTeXFragmentWork51;
			std::wstringstream* p_ssLaTeXFragmentWork52;
			std::wstringstream* p_ssLaTeXFragmentWork53;
			std::wstringstream* p_ssLaTeXFragmentWork54;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
		} t_data_for_v2;

	}
}

#endif