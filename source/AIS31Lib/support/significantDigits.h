////////////////////////////////////////////////////////////////////////////////
// significantDigits.h
//
//
// Copyright (c) 2021-2024 Gen'ya SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_SIGNIFICANT_DIGITS_H
#define AIS_31_LIB_SIGNIFICANT_DIGITS_H

#include "../constants.h"

namespace ais_31_lib
{
	namespace predictors
	{
		namespace support
		{

			namespace ns_consts = ais_31_lib::constants;

			ns_consts::EnmReturnStatus evaluateSignificantDigitsSP800_90B_6_3_2(
				double& o_ref_min_entropy_lower_bound,
				double& o_ref_min_entropy_upper_bound,
				double& o_ref_number_of_significant_digits,
				const double& i_ref_X_bar_prime,
				const int& i_ref_nu);

			ns_consts::EnmReturnStatus evaluateSignificantDigitsOfMinEntropyByPglobalSP800_90B_6_3_7_6_3_10(
				double& o_ref_min_entropy_lower_bound,
				double& o_ref_min_entropy_upper_bound,
				double& o_ref_number_of_significant_digits,
				const int& i_ref_C,
				const int& i_ref_N);

			ns_consts::EnmReturnStatus evaluateSignificantDigitsOfMinEntropyByPlocalSP800_90B_6_3_7_6_3_10(
				double& o_ref_min_entropy_lower_bound,
				double& o_ref_min_entropy_upper_bound,
				double& o_ref_number_of_significant_digits,
				const int& i_ref_r,
				const int& i_ref_N,
				const unsigned int & i_ref_k);

		}
	}
}
#endif