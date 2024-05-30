////////////////////////////////////////////////////////////////////////////////
//
//
//
// Copyright (c) 2023 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AIS_31_LIB__CONSTANTS_H__
#define __AIS_31_LIB__CONSTANTS_H__

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
			ErrorUnexpected = -8192,
		};

		enum class EnmAIS20AIS31V2Track
		{
			TestT0 = 0,
			TestT1,
			TestT2,
			TestT3,
			TestT4,
			TestT5,
			TestT6,
			TestT7,
			TestT8,
		};

	}
}

#endif