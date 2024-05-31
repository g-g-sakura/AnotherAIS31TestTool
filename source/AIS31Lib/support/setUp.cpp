////////////////////////////////////////////////////////////////////////////////
// setUp.cpp
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "setUp.h"
#include <boost/filesystem.hpp>

namespace ais_31_lib
{
	namespace support
	{
		namespace ns_consts = ais_31_lib::constants;
		namespace ns_dt = ais_31_lib::data_types;
		namespace bs_fs = boost::filesystem;

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <params="io_refData">
		/// </params>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus setUp(ns_dt::t_data_for_v2& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzInputDataT0 = nullptr;
			io_refData.p_bzInputDataT1 = nullptr;
			io_refData.p_bzInterpretedBj = nullptr;
			io_refData.p_bzSampleSpaceA = nullptr;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzInputDataT0 = new blitz::Array<ns_dt::octet, 1>(65536);
			io_refData.p_bzInputDataT1 = new blitz::Array<ns_dt::octet, 2>(257, 20000);
			io_refData.p_bzInterpretedBj = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzSampleSpaceA = new blitz::Array<ns_dt::octet, 1>(256);
			io_refData.t_testT0 = { 0 };
			io_refData.t_testT1 = { 0, 0, {9654, 10346}, 0, ns_consts::EnmPassFailResults::NotDetermined, {0} };
			io_refData.t_testT2 = { 0, 0, 1.03, 57.4, 0, ns_consts::EnmPassFailResults::NotDetermined, {0} };
			io_refData.t_testT3 = { 0 };
			io_refData.t_testT4 = { 0, nullptr, 0, 0, ns_consts::EnmPassFailResults::NotDetermined };
			io_refData.t_testT5 = { 0 };
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.t_testT5.th = {2326, 2674};
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.t_testT3.p_bzTestValue = new blitz::Array<uint32_t, 2>(6, 2);
			(*io_refData.t_testT3.p_bzTestValue) = 0;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.t_testT4.p_bzTestValue = new blitz::Array<uint32_t, 2>(20000, 2);
			(*io_refData.t_testT4.p_bzTestValue) = 0;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.t_testT5.p_bzZTau = new blitz::Array<uint32_t, 1>(5000);
			(*io_refData.t_testT5.p_bzZTau) = 0;
			io_refData.t_testT5.pHistogram = new ns_dt::TestValueHistogram();
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.t_testT5.p_bzTestValue = new blitz::Array<uint32_t, 1>(257);
			(*io_refData.t_testT5.p_bzTestValue) = 0;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			for (int lambdaMinusOne = 0; lambdaMinusOne < 6; ++lambdaMinusOne)
			{
				switch (lambdaMinusOne)
				{
				case 0:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 2267;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 2733;
					break;
				case 1:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 1079;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 1421;
					break;
				case 2:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 502;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 748;
					break;
				case 3:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 223;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 402;
					break;
				case 4:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 90;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 223;
					break;
				case 5:
					io_refData.t_testT3.th[lambdaMinusOne].lower_bound = 90;
					io_refData.t_testT3.th[lambdaMinusOne].upper_bound = 223;
					break;
				}
			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.verbose_level = 1;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			return sts = ns_consts::EnmReturnStatus::Success;
		}

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <params="io_refData">
		/// </params>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus tearDown(ns_dt::t_data_for_v2& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			if (nullptr != io_refData.t_testT5.p_bzTestValue)
			{
				delete io_refData.t_testT5.p_bzTestValue;
				io_refData.t_testT5.p_bzTestValue = nullptr;
			}
			if (nullptr != io_refData.t_testT5.p_bzZTau)
			{
				delete io_refData.t_testT5.p_bzZTau;
				io_refData.t_testT5.p_bzZTau = nullptr;
			}
			if (nullptr != io_refData.t_testT4.p_bzTestValue)
			{
				delete io_refData.t_testT4.p_bzTestValue;
				io_refData.t_testT4.p_bzTestValue = nullptr;
			}
			if (nullptr != io_refData.t_testT3.p_bzTestValue)
			{
				delete io_refData.t_testT3.p_bzTestValue;
				io_refData.t_testT3.p_bzTestValue = nullptr;
			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			if (nullptr != io_refData.p_bzSampleSpaceA)
			{
				delete io_refData.p_bzSampleSpaceA;
				io_refData.p_bzSampleSpaceA = nullptr;
			}
			if (nullptr != io_refData.p_bzInterpretedBj)
			{
				delete io_refData.p_bzInterpretedBj;
				io_refData.p_bzInterpretedBj = nullptr;
			}
			if (nullptr != io_refData.p_bzInputDataT1)
			{
				delete io_refData.p_bzInputDataT1;
				io_refData.p_bzInputDataT1 = nullptr;
			}
			if (nullptr != io_refData.p_bzInputDataT0)
			{
				delete io_refData.p_bzInputDataT0;
				io_refData.p_bzInputDataT0 = nullptr;
			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			return sts = ns_consts::EnmReturnStatus::Success;
		}


	}
}