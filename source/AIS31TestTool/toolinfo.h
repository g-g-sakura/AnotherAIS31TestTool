////////////////////////////////////////////////////////////////////////////////
// toolinfo.h
//
//
// Copyright (c) 2021-2023 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS31_TEST_TOOL_TOOL_INFO_H__
#define __AIS31_TEST_TOOL_TOOL_INFO_H__

#include "AIS31Lib/constants.h"
#include "reportItems.h"

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;

	ns_consts::EnmReturnStatus getToolInfo(const InfoAnalysisTool& i_refAnalysisTool);
}
#endif