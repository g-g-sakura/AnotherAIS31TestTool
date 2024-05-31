////////////////////////////////////////////////////////////////////////////////
// hostinfo.h
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS31_TEST_TOOL_HOST_INFO_H
#define AIS31_TEST_TOOL_HOST_INFO_H

#include "AIS31Lib/constants.h"
#include "reportItems.h"

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;

	ns_consts::EnmReturnStatus getEnvInfo(const InfoEnv&);

}
#endif