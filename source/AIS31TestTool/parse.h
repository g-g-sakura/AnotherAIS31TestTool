////////////////////////////////////////////////////////////////////////////////
// parse.h
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS31_TEST_TOOL_PARSE_H
#define AIS31_TEST_TOOL_PARSE_H

#include "AIS31Lib/constants.h"
#include "AIS31Lib/TestData.h"
#include "reporter.h"

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;
	namespace ns_dt = ais_31_lib::data_types;

	namespace bs_fs = boost::filesystem;

	ns_consts::EnmReturnStatus parse(ns_dt::t_data_for_v3& io_refData,
		IDInfoForReport& i_refInfoReport,
		int ac, wchar_t* av[], wchar_t* envp[]);
}
#endif