////////////////////////////////////////////////////////////////////////////////
// loadInputData.h
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS31_TEST_TOOL_LOAD_INPUT_DATA_H
#define AIS31_TEST_TOOL_LOAD_INPUT_DATA_H

#include "AIS31Lib//TestData.h"
#include "AIS31Lib/constants.h"
#include "reportItems.h"
#include <boost/filesystem.hpp>

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;
	namespace ns_dt = ais_31_lib::data_types;
	namespace bs_fs = boost::filesystem;

	ns_consts::EnmReturnStatus loadSamples(ns_dt::t_data_for_v3& io_refData,
		const IDInfoForReport& i_refInfoReport,
		const bs_fs::path& i_refFullPath);

	ns_consts::EnmReturnStatus loadSamplesForTest(ns_dt::t_data_for_v3& io_refData,
		const IDInfoForReport& i_refInfoReport,
		ns_consts::EnmAIS20AIS31V3Track i_enmTrack);

	ns_consts::EnmReturnStatus performProjection(ns_dt::t_data_for_v3& io_refData, int indexWithZeroOffset);

}
#endif