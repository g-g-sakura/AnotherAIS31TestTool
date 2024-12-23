////////////////////////////////////////////////////////////////////////////////
// checkArgs.cpp
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "checkArgs.h"

namespace ais_31_lib
{
	namespace support
	{
		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="i_refData">
		///  Specifies the reference to data structure for conformance test.
		/// </param>
		/// <returns>
		///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNullPointer</c>: when one of the following conditions is met:
		///    <ul>
		///     <li><c>i_refData.p_bzInputDataT1</c> is <c>nullptr</c>.</li>
		///    </ul>
		///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorInvalidData</c>: when one of the following conditions is met: 
		///    <ul>
		///     <li><c>i_refData.L</c> &gt; INT_MAX.</li>
		///     <li><c>i_refData.L</c> is not equal to <c>i_refData.p_bzInputDataT1-&gt;length(blitz::firstDim)</c>.</li>
		///     <li><c>i_refData.bits_per_sample</c> &lt; 1</li>
		///     <li><c>i_refData.bits_per_sample</c> &gt; 8</li>
		///    </ul>
		///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus perform_common_args_for_tests(const ns_dt::t_data_for_v3& i_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			if (nullptr == i_refData.p_bzInputDataT1)
			{
				sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				return sts;
			}
			if (nullptr == i_refData.p_bzInputDataT2)
			{
				sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				return sts;
			}
			if (i_refData.p_bzInputDataT1->length(blitz::firstDim) < 20000)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (i_refData.p_bzInputDataT2->length(blitz::firstDim) < 20000)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (i_refData.p_bzInputDataT3->length(blitz::firstDim) < 1000000)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (i_refData.p_bzInputDataT4->length(blitz::firstDim) < 1000000)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (INT_MAX < i_refData.L)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (i_refData.bits_per_sample < 1)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}
			if (8 < i_refData.bits_per_sample)
			{
				sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				return sts;
			}

			return sts = ns_consts::EnmReturnStatus::Success;
		}

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="i_refData">
		///  Specifies the reference to data structure for entropy estimation.
		/// </param>
		/// <returns>
		///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNullPointer</c>: when one of the following conditions is met:
		///    <ul>
		///     <li><c>i_refData.p_bzInputDataT3</c> is <c>nullptr</c>.</li>
		///     <li><c>i_refData.p_bzInputDataT4</c> is <c>nullptr</c>.</li>
		///    </ul>
		///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorInvalidData</c>: when one of the following conditions is met: 
		///    <ul>
		///     <li><c>i_refData.L</c> &gt; INT_MAX.</li>
		///     <li><c>i_refData.bits_per_sample</c> &lt; 1</li>
		///     <li><c>i_refData.bits_per_sample</c> &gt; 8</li>
		///    </ul>
		///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus perform_common_args_for_estimate(const ns_dt::t_data_for_v3& i_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
			if (nullptr == i_refData.p_bzInputDataT3)
			{
				sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				return sts;
			}
			if (nullptr == i_refData.p_bzInputDataT4)
			{
				sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
				return sts;
			}
			if (i_refData.p_bzInputDataT3->length(blitz::firstDim) < 1000000)
			{
				return sts;
			}
			if (i_refData.p_bzInputDataT4->length(blitz::firstDim) < 1000000)
			{
				return sts;
			}
			if (INT_MAX < i_refData.L)
			{
				return sts;
			}
			if (i_refData.bits_per_sample < 1)
			{
				return sts;
			}
			if (8 < i_refData.bits_per_sample)
			{
				return sts;
			}

			return sts = ns_consts::EnmReturnStatus::Success;
		}
	}
}