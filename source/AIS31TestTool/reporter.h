////////////////////////////////////////////////////////////////////////////////
// reporter.h
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS31_TEST_TOOL_REPORTER_H__
#define __AIS31_TEST_TOOL_REPORTER_H__

#include "AIS31Lib/constants.h"
#include "AIS31Lib/TestData.h"
#include "reportItems.h"

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;
	namespace ns_dt = ais_31_lib::data_types;
	namespace bs_fs = boost::filesystem;

	void showHeadSamplesTestT0(const ns_dt::t_data_for_v2& i_refData);
	void showHeadSamplesTestT1(const ns_dt::t_data_for_v2& i_refData);
	void showTailSamplesTestT0(const ns_dt::t_data_for_v2& i_refData);
	void showTailSamplesTestT1(const ns_dt::t_data_for_v2& i_refData);

	ns_consts::EnmReturnStatus reportXML(const IDInfoForReport& i_refInfoReport,
		const ns_dt::t_data_for_v2& io_refDataOriginal);

	ns_consts::EnmReturnStatus reportLaTeX(IDInfoForReport& i_refInfoReport,
		ns_dt::t_data_for_v2& io_refDataOriginal);

	ns_consts::EnmReturnStatus synthesizeReportPath(bs_fs::path& o_report_complete_path,
		const bs_fs::path& i_path_input_data);

	ns_consts::EnmReturnStatus synthesizeReportPathTex(bs_fs::path& o_report_complete_path,
		const bs_fs::path& i_path_input_data);

	ns_consts::EnmReturnStatus loadLaTeXPreamble(std::stringstream&);
}

#endif