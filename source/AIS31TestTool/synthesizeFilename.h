////////////////////////////////////////////////////////////////////////////////
// synthesizeFilename.h
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS31_TEST_TOOL_SYNTHESIZE_FILENAME_H__
#define __AIS31_TEST_TOOL_SYNTHESIZE_FILENAME_H__

#include "AIS31Lib/constants.h"
#include "AIS31Lib/TestData.h"
#include "reporter.h"
#include <boost/filesystem.hpp>

namespace ais_31_tool
{
	namespace ns_consts = ais_31_lib::constants;

	namespace bs_fs = boost::filesystem;

	ns_consts::EnmReturnStatus getFirstIndex(unsigned long& io_refOffset,
		size_t& io_refNumberOfDigitsOfIndex,
		const bs_fs::path& i_refInitialFilePath);

	ns_consts::EnmReturnStatus synthesizeFilename(bs_fs::path& io_refPathForIndex,
		unsigned long indexOfInputDataFiles,
		const bs_fs::path& i_refInitialFilePath);
}
#endif