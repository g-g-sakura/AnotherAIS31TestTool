////////////////////////////////////////////////////////////////////////////////
// reportItems.h
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS31_TEST_TOOL_REPORT_ITEMS_H
#define AIS31_TEST_TOOL_REPORT_ITEMS_H

#include <boost/filesystem.hpp>
#include <vector>

namespace ais_31_tool
{
	namespace bs_fs = boost::filesystem;

	struct InfoInputDataItem
	{
		bs_fs::path* p_path_to_input_data;
		std::time_t		tm_last_write_time;
	};

	struct InfoAnalysisTool
	{
		std::wstring* p_analyzer_name;
		std::wstring* p_analyzer_versioning;
	};

	struct InfoEnv
	{
		std::wstring* p_hostname;
		std::wstring* p_cpuinfo;
		std::wstring* p_physicalmemory;
		std::wstring* p_osname;
		std::wstring* p_osversion;
		std::wstring* p_system_type;
		std::wstring* p_username;
	};

	struct IDInfoForReport
	{
		InfoInputDataItem	info_source;
		InfoAnalysisTool	info_analysis_tool;
		InfoEnv				info_env;
	};
}
#endif