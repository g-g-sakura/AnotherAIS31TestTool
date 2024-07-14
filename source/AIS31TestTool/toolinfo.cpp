////////////////////////////////////////////////////////////////////////////////
// toolinfo.cpp
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "toolinfo.h"

namespace ais_31_tool
{
    ns_consts::EnmReturnStatus getToolInfo(const InfoAnalysisTool& i_refAnalysisTool)
    {
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
        if (nullptr == i_refAnalysisTool.p_analyzer_name)
        {
            return  sts;
        }
        if (nullptr == i_refAnalysisTool.p_analyzer_versioning)
        {
            return  sts;
        }
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        *i_refAnalysisTool.p_analyzer_name = std::wstring(L"Another AIS 20/AIS 31 test tool");
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        *i_refAnalysisTool.p_analyzer_versioning = std::wstring(L"1.0.3");
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        return  sts = ns_consts::EnmReturnStatus::Success;
    }
}