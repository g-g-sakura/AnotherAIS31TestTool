////////////////////////////////////////////////////////////////////////////////
// showTestSummary.h
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS_31_LIB_SHOW_TEST_SUMMARY_H__
#define __AIS_31_LIB_SHOW_TEST_SUMMARY_H__

#include "../TestData.h"
#include "../constants.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace ais_31_lib
{
	namespace support
	{
		namespace ns_consts = ais_31_lib::constants;
		namespace ns_dt = ais_31_lib::data_types;

		ns_consts::EnmReturnStatus showTestSpecificHeader(std::stringstream & o_refStream, 
			const ns_consts::EnmAIS20AIS31V2Track& i_enmTest,
			ns_dt::t_data_for_v2& io_refData);

		ns_consts::EnmReturnStatus showTestSpecificFooter(std::stringstream& o_refStream, 
			const ns_consts::EnmAIS20AIS31V2Track& i_enmTest,
			ns_dt::t_data_for_v2& io_refData);

		ns_consts::EnmReturnStatus showTestSpecificResult(std::stringstream& o_refStream,
			ns_consts::EnmAIS20AIS31V2Track& i_enmTest,
			ns_dt::t_data_for_v2& io_refData);
	}
}
#endif