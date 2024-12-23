////////////////////////////////////////////////////////////////////////////////
// pokerTest.h
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_POKER_TEST_H
#define AIS_31_LIB_POKER_TEST_H

#include "TestData.h"

namespace ais_31_lib
{
	namespace v3
	{
		namespace poker_test
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;

			ns_consts::EnmReturnStatus performTest(ns_dt::t_data_for_v3& io_refData);

		}
	}
}
#endif