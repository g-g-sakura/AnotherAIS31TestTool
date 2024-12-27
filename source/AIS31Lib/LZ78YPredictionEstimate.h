////////////////////////////////////////////////////////////////////////////////
// LZ78YPredictionEstimate.h
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_LZ78Y_PREDICTION_ESTIMATE_H
#define AIS_31_LIB_LZ78Y_PREDICTION_ESTIMATE_H

#include "TestData.h"
#include "constants.h"

namespace ais_31_lib
{
	namespace predictors
	{
		namespace lz78y_prediction
		{
			namespace ns_consts = ais_31_lib::constants;
			namespace ns_dt = ais_31_lib::data_types;

			ns_consts::EnmReturnStatus estimate(ns_dt::t_data_for_v3& io_refData);

		}
	}
}
#endif