////////////////////////////////////////////////////////////////////////////////
// performTests.h
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif


#ifndef __AIS31_TEST_TOOL_PERFORM_TESTS_H__
#define __AIS31_TEST_TOOL_PERFORM_TESTS_H__

#include "AIS31Lib/constants.h"
#include "AIS31Lib/TestData.h"

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;
	namespace ns_dt = ais_31_lib::data_types;

	ns_consts::EnmReturnStatus performTests(ns_dt::t_data_for_v2& io_refDataOriginal);
}
#endif