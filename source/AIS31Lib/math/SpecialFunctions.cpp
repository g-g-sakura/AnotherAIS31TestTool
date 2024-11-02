////////////////////////////////////////////////////////////////////////////////
// SpecialFunctions.cpp
//
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "SpecialFunctions.h"
#include <boost/math/special_functions/erf.hpp>

namespace ais_31_lib
{
	double calc_Z_alpha(double alpha)
	{
		const double x = 2.0 * (1.0 - alpha);
		const double val = boost::math::erfc_inv<double>(x);
		return M_SQRT2 * val;
	}

}