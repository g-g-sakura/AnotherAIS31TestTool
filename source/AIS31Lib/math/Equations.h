////////////////////////////////////////////////////////////////////////////////
// Equations.h
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef AIS_31_LIB_EQUATIONS_H
#define AIS_31_LIB_EQUATIONS_H

namespace ais_31_lib
{
	namespace predictors
	{
		namespace math
		{
			class RhsMinusLhs
			{
			private:
				int r;
				int N;
				double	lhs;
			public:
				RhsMinusLhs(int i_r, int i_N, double i_lhs)
					: r(i_r), N(i_N), lhs(i_lhs) {}

				double	evaluate_x(double i_p) const
				{
					double	x = 1.0;
					for (int j = 0; j < 10; ++j)
					{
						const double	x_new = 1.0 + (1.0 - i_p) * pow(i_p * x, this->r) * x;
						x = x_new;
					}
					return	x;
				}

				double operator()(double i_p) const
				{
					const double	q = (1.0 - i_p);
					const double	x = this->evaluate_x(i_p);
					const double	rhs = (1.0 - i_p * x) / (q * (static_cast<double>(this->r + 1) - x * (static_cast<double>(this->r))) * pow(x, N + 1));
					return	rhs - lhs;
				}
			};
		}
	}
}
#endif