////////////////////////////////////////////////////////////////////////////////
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB__CONSTANTS_H
#define AIS_31_LIB__CONSTANTS_H

namespace ais_31_lib
{
	namespace  constants
	{
		enum class EnmPassFailResults
		{
			Fail = -8192,
			NotDetermined = 0,
			Pass = 8192,
		};

		enum class EnmReturnStatus
		{
			Success = 0,
			ErrorNotFound = -8,
			ErrorFirstIndexNotFound = -9,
			ErrorFirstIndexFoundButSecondIndexNotFound = -10,
			ErrorNoTask = -16,
			ErrorInvalidData = -120,
			ErrorDomain = -121,
			ErrorOutOfBound = -122,
			ErrorMemoryAllocation = -126,
			ErrorNullPointer = -127,
			ErrorFileIO = -250,
			ErrorPreconditions = -251,
			ErrorInsufficientData = -252,
			ErrorChildProcess = -480,
			ErrorUnexpected = -8192,
		};

		enum class EnmAIS20AIS31V3Track
		{
			TestT1 = 1,
			TestT2,
			TestT3,
			TestT4,
		};

	}
}

#endif