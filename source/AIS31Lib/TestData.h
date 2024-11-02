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

		typedef struct _TDataForTestSuitesV3
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
			t_data_for_monobit_test			t_testT1;
			t_data_for_poker_test			t_testT2;
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
			std::wstringstream* p_ssLaTeXFragment;
			// -------------------------------------------------------------------------- //
			// for Test T3
			// -------------------------------------------------------------------------- //
			// -------------------------------------------------------------------------- //
			// for Test T4
			// -------------------------------------------------------------------------- //
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
		} t_data_for_v3;

	}
}

#endif