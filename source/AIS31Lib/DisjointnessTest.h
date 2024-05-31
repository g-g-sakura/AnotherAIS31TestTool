////////////////////////////////////////////////////////////////////////////////
// DisjointnessTest.h
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_DISJOINTNESS_TEST_H
#define AIS_31_LIB_DISJOINTNESS_TEST_H

#include "TestData.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

namespace ais_31_lib
{
	namespace v2
	{
		namespace ns_consts = ais_31_lib::constants;
		namespace ns_dt = ais_31_lib::data_types;
		namespace bmi = boost::multi_index;
		using boost::multi_index_container;

		struct t_element_count
		{
			uint64_t		ex_w;		// w
			int				ex_cnt;		// count = number of occurrence of index value within a certain window

			t_element_count(const uint64_t& i_x, int i_count) : ex_w(i_x), ex_cnt(i_count) {}

			bool operator <(t_element_count const& i_refRight) const
			{
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				if (ex_cnt != i_refRight.ex_cnt)
				{
					return	ex_cnt < i_refRight.ex_cnt;
				}
				else
				{
					return	ex_w < i_refRight.ex_w;
				}
			}
		};

		struct elem_w {};
		struct elem_cnt {};

		typedef bmi::multi_index_container<
			t_element_count,
			bmi::indexed_by<
			bmi::ordered_unique<bmi::identity<t_element_count> >, //
			bmi::ordered_unique<bmi::tag<elem_w>, bmi::member<t_element_count, uint64_t, &t_element_count::ex_w> >,
			bmi::ordered_non_unique<bmi::tag<elem_cnt>, bmi::member<t_element_count, int, &t_element_count::ex_cnt> >
			>
		> ElementHistogram;

		typedef ElementHistogram::index<elem_w>::type tpl_elw_map;
		typedef ElementHistogram::index<elem_cnt>::type tpl_elcnt_map;

		namespace disjointness_test
		{
			ns_consts::EnmReturnStatus performTest(ns_dt::t_data_for_v2& io_refData);
		}
	}
}
#endif