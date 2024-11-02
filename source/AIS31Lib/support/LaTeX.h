////////////////////////////////////////////////////////////////////////////////
// LaTeX.h
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef ENTROPY_ESTIMATOR_LIB_LATEX_H
#define ENTROPY_ESTIMATOR_LIB_LATEX_H

#include "../constants.h"
#include <sstream>

namespace ais_31_lib
{
	namespace support
	{
		namespace ns_consts = ais_31_lib::constants;

		ns_consts::EnmReturnStatus getLaTeXCommentBlock(std::wstring& o_refLaTeXFragment, const std::wstring& i_refComment);
		ns_consts::EnmReturnStatus getLaTeXSubsection(std::wstring& o_refSubsection, 
			const std::wstring& i_refSubsectionTitle,
			const std::wstring& i_refLabel);
		ns_consts::EnmReturnStatus getLaTeXSubsubsection(std::wstring& o_refSubsubsection,
			const std::wstring& i_refSubsubsectionTitle,
			const std::wstring& i_refLabel);
		ns_consts::EnmReturnStatus getLaTeXSubsubsectionTraceability(std::wstring& o_refSubsubsection,
			const std::wstring& i_refLabel);
	}
}
#endif