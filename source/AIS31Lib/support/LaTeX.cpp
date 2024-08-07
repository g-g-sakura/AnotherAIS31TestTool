////////////////////////////////////////////////////////////////////////////////
// LaTeX.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "LaTeX.h"
namespace ais_31_lib
{
	namespace support
	{
		namespace ns_consts = ais_31_lib::constants;

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="o_refLaTeXFragment">
		/// </param>
		/// <param name="i_refComment">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus getLaTeXCommentBlock(std::wstring& o_refLaTeXFragment, const std::wstring& i_refComment)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstringstream	ss = std::wstringstream();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			ss << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
			ss << L"%%%%%%" << L"\n";
			ss << L"%%%%%%";
			if (false == i_refComment.empty())
			{
				ss << L" " << i_refComment;
			}
			ss << L"\n";
			ss << L"%%%%%%" << L"\n";
			ss << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			o_refLaTeXFragment = ss.str();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			return  sts = ns_consts::EnmReturnStatus::Success;
		}

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="o_refSubsection">
		/// </param>
		/// <param name="i_refSubsectionTitle">
		/// </param>
		/// <param name="i_refLabel">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus getLaTeXSubsection(std::wstring& o_refSubsection, 
			const std::wstring& i_refSubsectionTitle,
			const std::wstring& i_refLabel)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstringstream	ssSubsection = std::wstringstream();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstring	strComment = std::wstring();
			sts = getLaTeXCommentBlock(strComment, i_refSubsectionTitle);
			if (ns_consts::EnmReturnStatus::Success != sts)
			{
				return  sts;
			}
			ssSubsection << strComment;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			ssSubsection << L"\\subsection{";
			if (false == i_refSubsectionTitle.empty())
			{
				ssSubsection << i_refSubsectionTitle;
			}
			ssSubsection << L"}";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			if (false == i_refLabel.empty())
			{
				ssSubsection << L"\\label{" << i_refLabel << L"}" << L"\n";
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			o_refSubsection = ssSubsection.str();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			return  sts = ns_consts::EnmReturnStatus::Success;
		}

		// -------------------------------------------------------------------------- //
		/// <summary>
		/// </summary>
		/// <remarks>
		/// </remarks>
		/// <param name="o_refSubsubsection">
		/// </param>
		/// <param name="i_refSubsubsectionTitle">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus getLaTeXSubsubsection(std::wstring& o_refSubsubsection, const std::wstring& i_refSubsubsectionTitle)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstringstream	ssSubsubsection = std::wstringstream();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::wstring	strComment = std::wstring();
			sts = getLaTeXCommentBlock(strComment, i_refSubsubsectionTitle);
			if (ns_consts::EnmReturnStatus::Success != sts)
			{
				return  sts;
			}
			ssSubsubsection << strComment;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			ssSubsubsection << L"\\subsubsection{";
			if (false == i_refSubsubsectionTitle.empty())
			{
				ssSubsubsection << i_refSubsubsectionTitle;
			}
			ssSubsubsection << L"}\n";

			o_refSubsubsection = ssSubsubsection.str();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			return  sts = ns_consts::EnmReturnStatus::Success;
		}


	}
}
