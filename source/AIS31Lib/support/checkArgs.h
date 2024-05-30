////////////////////////////////////////////////////////////////////////////////
// checkArgs.h
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS_31_LIB_CHECK_ARGS_H__
#define __AIS_31_LIB_CHECK_ARGS_H__

#include "../TestData.h"

namespace ais_31_lib
{
	namespace support
	{
		namespace ns_consts = ais_31_lib::constants;
		namespace ns_dt = ais_31_lib::data_types;

		ns_consts::EnmReturnStatus perform_common_args_for_tests(const ns_dt::t_data_for_v2& i_refData);

	}
}
#endif