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
			io_refData.p_bzUnprocessedData = nullptr;
			io_refData.p_bzInputDataT1 = nullptr;
			io_refData.p_bzInputDataT2 = nullptr;
			io_refData.p_bzInputDataT3 = nullptr;
			io_refData.p_bzInputDataT4 = nullptr;
			io_refData.p_bzInterpretedBj = nullptr;
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzUnprocessedData = new blitz::Array<ns_dt::octet, 1>(4080000);
			io_refData.p_bzInputDataT1 = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzInputDataT2 = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.p_bzInputDataT3 = new blitz::Array<ns_dt::octet, 1>(1000000);
			io_refData.p_bzInputDataT4 = new blitz::Array<ns_dt::octet, 1>(1000000);
			io_refData.p_bzInterpretedBj = new blitz::Array<ns_dt::octet, 1>(20000);
			io_refData.t_testT1 = { 0, 0, {9654, 10346}, ns_consts::EnmPassFailResults::NotDetermined, {0} };
			io_refData.t_testT2 = { 0, 1.03, 57.4, ns_consts::EnmPassFailResults::NotDetermined, {0} };
			io_refData.t_testT3 = { 0 };
			io_refData.t_testT3.t_common.pass_fail_result = ns_consts::EnmPassFailResults::NotDetermined;
			io_refData.t_testT3.D = 16;	// as per NIST SP 800-90B
			io_refData.t_testT3.maxEntries = 100000;	// as per NIST SP 800-90B
			io_refData.t_testT3.threshold = 0.95;	// as per AIS2031An_24
			io_refData.t_testT4 = { 0 };
			io_refData.t_testT4.t_common.pass_fail_result = ns_consts::EnmPassFailResults::NotDetermined;
			io_refData.t_testT4.B = 16;	// as per NIST SP 800-90B
			io_refData.t_testT4.maxDictionarySize = 65536;	// as per NIST SP 800-90B
			io_refData.t_testT4.threshold = 0.95;	// as per AIS2031An_24
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