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

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="io_refData">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus setUp(ns_dt::t_data_for_v3& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzInputDataT1 = nullptr;
			io_refData.p_bzInputDataT2 = nullptr;
			io_refData.p_bzInputDataT3 = nullptr;
			io_refData.p_bzInputDataT4 = nullptr;
			io_refData.p_bzInterpretedBj = nullptr;
			io_refData.p_bzSampleSpaceA = nullptr;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzInputDataT1 = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzInputDataT2 = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzInputDataT3 = new blitz::Array<ns_dt::octet, 1>(1000000);
			io_refData.p_bzInputDataT4 = new blitz::Array<ns_dt::octet, 1>(1000000);
			io_refData.p_bzInterpretedBj = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzSampleSpaceA = new blitz::Array<ns_dt::octet, 1>(256);
			io_refData.t_testT1 = { 0, 0, {9654, 10346}, 0, ns_consts::EnmPassFailResults::NotDetermined, {0} };
			io_refData.t_testT2 = { 0, 1.03, 57.4, 0, ns_consts::EnmPassFailResults::NotDetermined, {0} };
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
		/// <param name="io_refData">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus tearDown(ns_dt::t_data_for_v3& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
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
			if (nullptr != io_refData.p_bzInputDataT4)
			{
				delete io_refData.p_bzInputDataT4;
				io_refData.p_bzInputDataT4 = nullptr;
			}
			if (nullptr != io_refData.p_bzInputDataT3)
			{
				delete io_refData.p_bzInputDataT3;
				io_refData.p_bzInputDataT3 = nullptr;
			}
			if (nullptr != io_refData.p_bzInputDataT2)
			{
				delete io_refData.p_bzInputDataT2;
				io_refData.p_bzInputDataT2 = nullptr;
			}
			if (nullptr != io_refData.p_bzInputDataT1)
			{
				delete io_refData.p_bzInputDataT1;
				io_refData.p_bzInputDataT1 = nullptr;
			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			return sts = ns_consts::EnmReturnStatus::Success;
		}


	}
}