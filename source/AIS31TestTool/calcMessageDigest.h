////////////////////////////////////////////////////////////////////////////////
// calcMessageDigest.h
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS31_TEST_TOOL_CALC_MESSAGE_DIGEST_H
#define AIS31_TEST_TOOL_CALC_MESSAGE_DIGEST_H

#include <string>
#include <boost/filesystem.hpp>
#include "AIS31Lib/constants.h"

namespace ais_31_tool
{
	namespace constants
	{
		enum class EnmHashAlgorithm
		{
			ESHA_256 = 0x03040201,
			ESHA_384 = 0x03040202,
			ESHA_512 = 0x03040203,
			//ESHA3_256 = 0x03040208,
			//ESHA3_384 = 0x03040209,
			//ESHA3_512 = 0x0304020a,
		};
	}

	namespace ns_consts = ais_31_lib::constants;
	namespace bs_fs = boost::filesystem;

	ns_consts::EnmReturnStatus calcMessageDigest(std::string& o_refMessageDigestInHex,
		unsigned char* i_pInputMessage,
		unsigned int i_cuiInputMessageLengthInOctets,
		constants::EnmHashAlgorithm i_enmHashAlgorithm);

	ns_consts::EnmReturnStatus calcMessageDigest(std::string& o_refMessageDigestInHex,
		const bs_fs::path& i_refFullPath,
		constants::EnmHashAlgorithm i_enmHashAlgorithm);
}

#endif