////////////////////////////////////////////////////////////////////////////////
// reporter.cpp
//
//
//
// Copyright (c) 2021-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "reporter.h"
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/filesystem/fstream.hpp>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <boost/version.hpp>
#include "calcMessageDigest.h"

namespace ais_31_tool
{
	namespace bs_fs = boost::filesystem;

	namespace ns_consts = ais_31_lib::constants;
	namespace ns_dt = ais_31_lib::data_types;

	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	void showHeadSamplesTestT0(const ns_dt::t_data_for_v2& i_refData)
	{
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (i_refData.isT0Selected)
		{
			const int total_length = i_refData.p_bzInputDataT0->length(blitz::firstDim);
			int num_bytes = 64;
			if (total_length < 64)
			{
				num_bytes = total_length;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << "\n";
			std::cout << "The following are the first " << num_bytes << "-byte samples, in hexadecimal, of the specified file for Test T0 for confirmation:" << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout.setf(std::ios::hex, std::ios::basefield);
			const char chFillSaved = std::cout.fill('0');
			for (int j = 0; j < num_bytes; ++j)
			{
				std::cout << std::setw(2) << static_cast<int>((*i_refData.p_bzInputDataT0)(j)) << ", ";
				if ((j != 0) && (15 == j % 16))
				{
					std::cout << "\n";
				}
			}
			std::cout.fill(chFillSaved);
			std::cout.setf(std::ios::dec, std::ios::basefield);
		}
	}
	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	void showHeadSamplesTestT1(const ns_dt::t_data_for_v2& i_refData)
	{
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (i_refData.areT1ThroughT5Selected)
		{
			const int total_length = i_refData.p_bzInputDataT1->length(blitz::firstDim);
			int num_bytes = 64;
			if (total_length < 64)
			{
				num_bytes = total_length;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << "\n";
			std::cout << "The following are the first " << num_bytes << "-byte samples, in hexadecimal, of the specified file for Tests T1 through T5 for confirmation:" << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout.setf(std::ios::hex, std::ios::basefield);
			const char chFillSaved = std::cout.fill('0');
			for (int j = 0; j < num_bytes; ++j)
			{
				std::cout << std::setw(2) << static_cast<int>((*i_refData.p_bzInputDataT1)(j)) << ", ";
				if ((j != 0) && (15 == j % 16))
				{
					std::cout << "\n";
				}
			}
			std::cout.fill(chFillSaved);
			std::cout.setf(std::ios::dec, std::ios::basefield);

		}
	}
	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	void showTailSamplesTestT0(const ns_dt::t_data_for_v2& i_refData)
	{
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (i_refData.isT0Selected)
		{
			const int total_length = i_refData.p_bzInputDataT0->length(blitz::firstDim);
			int offset = total_length;
			int num_bytes = 64;
			if (64 <= total_length)
			{
				offset = total_length - 64;
			}
			else
			{
				offset = 0;
				num_bytes = total_length;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << "\n";
			std::cout << "The following are the last " << num_bytes << "-byte samples, in hexadecimal, of the specified file for Test T0 for confirmation:" << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout.setf(std::ios::hex, std::ios::basefield);
			const char chFillSaved = std::cout.fill('0');
			for (int j = 0; j < num_bytes; ++j)
			{
				std::cout << std::setw(2) << static_cast<int>((*i_refData.p_bzInputDataT0)(offset + j)) << ", ";
				if ((j != 0) && (15 == j % 16))
				{
					std::cout << "\n";
				}
			}
			std::cout.fill(chFillSaved);
			std::cout.setf(std::ios::dec, std::ios::basefield);
		}
	}
	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	void showTailSamplesTestT1(const ns_dt::t_data_for_v2& i_refData)
	{
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (i_refData.areT1ThroughT5Selected)
		{
			const int total_length = i_refData.p_bzInputDataT1->length(blitz::firstDim);
			int offset = total_length;
			int num_bytes = 64;
			if (64 <= total_length)
			{
				offset = total_length - 64;
			}
			else
			{
				offset = 0;
				num_bytes = total_length;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << "\n";
			std::cout << "The following are the last " << num_bytes << "-byte samples, in hexadecimal, of the specified file for Tests T1 through T5 for confirmation:" << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout.setf(std::ios::hex, std::ios::basefield);
			const char chFillSaved = std::cout.fill('0');
			for (int j = 0; j < num_bytes; ++j)
			{
				std::cout << std::setw(2) << static_cast<int>((*i_refData.p_bzInputDataT1)(offset + j)) << ", ";
				if ((j != 0) && (15 == j % 16))
				{
					std::cout << "\n";
				}
			}
			std::cout.fill(chFillSaved);
			std::cout.setf(std::ios::dec, std::ios::basefield);
		}
	}


	struct TestResult
	{
		double  test_value;

		ns_consts::EnmAIS20AIS31V2Track   test_info;
		bool    bIsTestValueScalar;
		ns_consts::EnmPassFailResults	pass_fail_result;

		TestResult() : test_value(0.0), test_info(ns_consts::EnmAIS20AIS31V2Track::TestT0), bIsTestValueScalar(true), pass_fail_result(ns_consts::EnmPassFailResults::NotDetermined) {}

		TestResult(double val, ns_consts::EnmAIS20AIS31V2Track i_test, ns_consts::EnmPassFailResults i_pass_fail)
			: test_value(val), test_info(i_test), bIsTestValueScalar(true), pass_fail_result(i_pass_fail)
		{
			switch (i_test)
			{
			case ns_consts::EnmAIS20AIS31V2Track::TestT0:
				test_value = 0;
				bIsTestValueScalar = false;
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT1:
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT2:
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT3:
				test_value = 0;
				bIsTestValueScalar = false;
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT4:
				test_value = 0;
				bIsTestValueScalar = false;
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT5:
				test_value = 0;
				bIsTestValueScalar = false;
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT6:
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT7:
				break;
			case ns_consts::EnmAIS20AIS31V2Track::TestT8:
				break;
			default:
				break;
			}
		}

	};

	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_est">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	std::wstring getTestInfo(ns_consts::EnmAIS20AIS31V2Track i_test)
	{
		std::wstring str_ret;
		switch (i_test)
		{
		case ns_consts::EnmAIS20AIS31V2Track::TestT0:
			str_ret = std::wstring(L"Test T0 (disjointness test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT1:
			str_ret = std::wstring(L"Test T1 (monobit test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT2:
			str_ret = std::wstring(L"Test T2 (poker test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT3:
			str_ret = std::wstring(L"Test T3 (runs test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT4:
			str_ret = std::wstring(L"Test T4 (long run test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT5:
			str_ret = std::wstring(L"Test T5 (autocorrelation test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT6:
			str_ret = std::wstring(L"Test T6 (uniform distribution test)");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT7:
			str_ret = std::wstring(L"Test T7 (comparative test for multinomial distributions aka `test for homogeneity')");
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT8:
			str_ret = std::wstring(L"Test T8 (entropy estimation)");
			break;
		default:
			break;
		}
		return  str_ret;
	}

	std::wstring getPassFail(ns_consts::EnmPassFailResults i_enmPassFail)
	{
		std::wstring     str_ret;
		switch (i_enmPassFail)
		{
		case ns_consts::EnmPassFailResults::Pass:
			str_ret = std::wstring(L"Pass");
			break;
		case ns_consts::EnmPassFailResults::Fail:
			str_ret = std::wstring(L"Fail");
			break;
		default:
			str_ret = std::wstring(L"Not determined");
			break;
		}
		return  str_ret;
	}
	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <params="i_refInfoReport">
	/// </params>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportXML(const IDInfoForReport& i_refInfoReport,
		const ns_dt::t_data_for_v2& i_refData)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		constexpr  ns_consts::EnmAIS20AIS31V2Track   enm_test_method[] = {
				ns_consts::EnmAIS20AIS31V2Track::TestT0,
				ns_consts::EnmAIS20AIS31V2Track::TestT1,
				ns_consts::EnmAIS20AIS31V2Track::TestT2,
				ns_consts::EnmAIS20AIS31V2Track::TestT3,
				ns_consts::EnmAIS20AIS31V2Track::TestT4,
				ns_consts::EnmAIS20AIS31V2Track::TestT5,
				ns_consts::EnmAIS20AIS31V2Track::TestT6,
				ns_consts::EnmAIS20AIS31V2Track::TestT7,
				ns_consts::EnmAIS20AIS31V2Track::TestT8
		};
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1)
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (true == i_refInfoReport.info_source.p_info_input_data_items_testT1->empty())
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if ((nullptr == i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
			&& (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data))
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		bs_fs::path the_report_path;
		if (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data)
		{
			sts = synthesizeReportPath(the_report_path, (*i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data));
		}
		else if (nullptr == i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
		{
			sts = synthesizeReportPath(the_report_path, *(i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data));
		}
		else
		{
			sts = synthesizeReportPath(the_report_path, (*i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data));
		}
		if (ns_consts::EnmReturnStatus::Success != sts)
		{
			return  sts;
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		boost::property_tree::wptree the_tree;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::vector<TestResult> vec_tr;
		vec_tr.reserve(8);
		ns_consts::EnmPassFailResults   global_pass_fail = ns_consts::EnmPassFailResults::NotDetermined;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		for (int i = 0; i < 6; ++i)
		{
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			const ns_consts::EnmPassFailResults* p_pass_fail_result = nullptr;
			double  failsafe_test_value = 0;
			switch (i)
			{
			case 0:
				p_pass_fail_result = &(i_refData.t_testT0.pass_fail_result);
				break;
			case 1:
				p_pass_fail_result = &(i_refData.t_testT1.pass_fail_result);
				failsafe_test_value = i_refData.t_testT1.test_value_T1;
				break;
			case 2:
				p_pass_fail_result = &(i_refData.t_testT2.pass_fail_result);
				failsafe_test_value = i_refData.t_testT2.test_value_T2;
				break;
			case 3:
				p_pass_fail_result = &(i_refData.t_testT3.pass_fail_result);
				break;
			case 4:
				p_pass_fail_result = &(i_refData.t_testT4.pass_fail_result);
				break;
			case 5:
				p_pass_fail_result = &(i_refData.t_testT5.pass_fail_result);
				break;
			default:
				return  sts;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			if (nullptr != p_pass_fail_result)
			{
				if (ns_consts::EnmPassFailResults::Fail == *p_pass_fail_result)
				{
					global_pass_fail = ns_consts::EnmPassFailResults::Fail;
				}
			}
			vec_tr.emplace_back(TestResult(failsafe_test_value, enm_test_method[i], *p_pass_fail_result));
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (ns_consts::EnmPassFailResults::NotDetermined == global_pass_fail)
		{
			global_pass_fail = ns_consts::EnmPassFailResults::Pass;
		}
		// -------------------------------------------------------------------------- //
		// <identification><sources>
		// -------------------------------------------------------------------------- //
		{
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			if (nullptr != i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
			{
				the_tree.add(L"conformance_report.identification.sources.source.path", i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data->wstring());

				struct tm newtime;

				errno_t err = localtime_s(&newtime, &(i_refInfoReport.info_source.info_input_data_testT0.tm_last_write_time));
				if (err)
				{
					return  sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
				}

				the_tree.add(L"conformance_report.identification.sources.source.last_write_time", std::put_time(&newtime, L"%Y-%b-%d %H:%M:%S"));
				the_tree.add(L"conformance_report.identification.sources.source.bits_per_sample", std::to_wstring(i_refData.bits_per_sample));
				the_tree.add(L"conformance_report.identification.sources.source.description", std::wstring(L" "));
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			if ((nullptr != i_refInfoReport.info_source.p_info_input_data_items_testT1)
				&& (false == i_refInfoReport.info_source.p_info_input_data_items_testT1->empty()))
			{

				BOOST_FOREACH(const InfoInputDataItem & input_item, *i_refInfoReport.info_source.p_info_input_data_items_testT1) {
					if (nullptr != input_item.p_path_to_input_data)
					{
						the_tree.add(L"conformance_report.identification.sources.source.path", input_item.p_path_to_input_data->wstring());

						struct tm newtime;

						errno_t err = localtime_s(&newtime, &(input_item.tm_last_write_time));
						if (err)
						{
							return  sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
						}

						the_tree.add(L"conformance_report.identification.sources.source.last_write_time", std::put_time(&newtime, L"%Y-%b-%d %H:%M:%S"));
						the_tree.add(L"conformance_report.identification.sources.source.bits_per_sample", std::to_wstring(i_refData.bits_per_sample));
						the_tree.add(L"conformance_report.identification.sources.source.description", std::wstring(L" "));
					}
				}
			}
		}
		// -------------------------------------------------------------------------- //
		// <identification><analysis_tool>
		// -------------------------------------------------------------------------- //
		if (nullptr != i_refInfoReport.info_analysis_tool.p_analyzer_name)
		{
			the_tree.add(L"conformance_report.identification.analysis_tool.name", *i_refInfoReport.info_analysis_tool.p_analyzer_name);
		}
		if (nullptr != i_refInfoReport.info_analysis_tool.p_analyzer_versioning)
		{
			the_tree.add(L"conformance_report.identification.analysis_tool.version", *i_refInfoReport.info_analysis_tool.p_analyzer_versioning);
		}
		// -------------------------------------------------------------------------- //
		// <identification><environment>
		// -------------------------------------------------------------------------- //
		if (nullptr != i_refInfoReport.info_env.p_hostname)
		{
			the_tree.add(L"conformance_report.identification.environment.hostname", *i_refInfoReport.info_env.p_hostname);
		}
		if (nullptr != i_refInfoReport.info_env.p_cpuinfo)
		{
			the_tree.add(L"conformance_report.identification.environment.cpuinfo", *i_refInfoReport.info_env.p_cpuinfo);
		}
		if (nullptr != i_refInfoReport.info_env.p_physicalmemory)
		{
			the_tree.add(L"conformance_report.identification.environment.physicalmemory", *i_refInfoReport.info_env.p_physicalmemory);
		}
		if (nullptr != i_refInfoReport.info_env.p_username)
		{
			the_tree.add(L"conformance_report.identification.environment.username", *i_refInfoReport.info_env.p_username);
		}
		// -------------------------------------------------------------------------- //
		// <summary>
		// -------------------------------------------------------------------------- //
		{
			the_tree.add(L"conformance_report.summary.result", getPassFail(global_pass_fail));
		}
		// -------------------------------------------------------------------------- //
		// <results>
		// -------------------------------------------------------------------------- //
		BOOST_FOREACH(const TestResult & tr_entry, vec_tr) {
			boost::property_tree::wptree& child = the_tree.add(L"conformance_report.results.test", getPassFail(tr_entry.pass_fail_result));
			child.put(L"<xmlattr>.test_method", getTestInfo(tr_entry.test_info));
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		constexpr  int indent = 4;
		boost::property_tree::xml_parser::write_xml(the_report_path.string(), the_tree, std::locale(),
			boost::property_tree::xml_parser::xml_writer_make_settings<std::wstring>(L' ', indent));
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
	/// <params="o_report_complete_path">
	/// </params>
	/// <params="i_path_input_data">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus synthesizeReportPath(bs_fs::path& o_report_complete_path,
		const bs_fs::path& i_path_input_data)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		const std::string strBaseFileName("test_report_");
		const std::string strExtension(".xml");

		const auto pt =
			boost::posix_time::ptime(
				boost::posix_time::microsec_clock::local_time());

		const std::string strTimeInfo(boost::posix_time::to_iso_string(pt));
		std::string strFileName(strBaseFileName);
		strFileName += i_path_input_data.stem().string();
		strFileName += "_";
		strFileName += strTimeInfo.substr(0, 15);
		strFileName += strExtension;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_report_complete_path = i_path_input_data.parent_path();
		o_report_complete_path /= strFileName;
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
	/// <params="o_report_complete_path">
	/// </params>
	/// <params="i_path_input_data">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus synthesizeReportPathTex(bs_fs::path& o_report_complete_path,
		const bs_fs::path& i_path_input_data)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		const std::string strBaseFileName("test_report_");
		const std::string strExtension(".tex");

		const auto pt =
			boost::posix_time::ptime(
				boost::posix_time::microsec_clock::local_time());

		const std::string strTimeInfo(boost::posix_time::to_iso_string(pt));
		std::string strFileName(strBaseFileName);
		strFileName += i_path_input_data.stem().string();
		strFileName += "_";
		strFileName += strTimeInfo.substr(0, 15);
		strFileName += strExtension;
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_report_complete_path = i_path_input_data.parent_path();
		o_report_complete_path /= strFileName;
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
	/// <params="o_ssLaTeX">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus loadLaTeXPreamble(std::wstringstream& o_ssLaTeX)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream	ssSep = std::wstringstream();
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_ssLaTeX << L"\\documentclass[a3paper,xelatex,english]{bxjsarticle}" << L"\n";
		o_ssLaTeX << L"\\usepackage{pgfplots,pgfplotstable}" << L"\n";
		o_ssLaTeX << L"\\pgfplotsset{ compat = newest }" << L"\n";
		o_ssLaTeX << L"\\usepackage{tikz}" << L"\n";
		o_ssLaTeX << L"\\usetikzlibrary{arrows.meta,bending,calc,shapes,positioning}" << L"\n";
		o_ssLaTeX << L"\\usepackage{ascmac}" << L"\n";
		o_ssLaTeX << L"\\usepackage{fancybox}" << L"\n";
		o_ssLaTeX << L"\\usepackage{amsmath,amssymb}" << L"\n";
		o_ssLaTeX << L"\\usepackage{algorithm}" << L"\n";
		o_ssLaTeX << L"\\usepackage[edges]{forest}" << L"\n";
		o_ssLaTeX << L"\\usepackage{array}" << L"\n";
		o_ssLaTeX << L"\\usepackage{algpseudocode}" << L"\n";
		o_ssLaTeX << L"\\usepackage{paralist}" << L"\n";
		o_ssLaTeX << L"\\usepackage{cases}" << L"\n";
		o_ssLaTeX << L"\\usepackage{fvextra}" << L"\n";
		o_ssLaTeX << L"\\usepackage{longtable}" << L"\n";
		o_ssLaTeX << L"\\usepackage{colortbl}" << L"\n";
		o_ssLaTeX << L"\\usepackage{xcolor}" << L"\n";
		o_ssLaTeX << L"\\usepackage{fancyhdr}" << L"\n";
		o_ssLaTeX << L"\\usepackage[explicit]{titlesec}" << L"\n";
		o_ssLaTeX << L"\\usepackage{xspace}" << L"\n";
		o_ssLaTeX << L"\\usepackage[many]{tcolorbox}" << L"\n";
		o_ssLaTeX << L"\\usepackage{lastpage}" << L"\n";
		o_ssLaTeX << L"\\usepackage{verbatim}" << L"\n";
		o_ssLaTeX << L"\\usepackage{multirow}" << L"\n";
		o_ssLaTeX << L"\\usepackage{fancyvrb}" << L"\n";
		o_ssLaTeX << L"\\usepackage{censor}" << L"\n";
		o_ssLaTeX << L"\\usepackage[unicode,pdftitle={Test report of based on BSI AIS 20 / AIS 31},setpagesize=false]{hyperref}" << L"\n";
		o_ssLaTeX << L"\\usepackage[open,openlevel=4]{bookmark}" << L"\n";
		o_ssLaTeX << L"\\newcommand\\mib[1]{\\boldsymbol{#1}}" << L"\n";
		o_ssLaTeX << L"\\usepgfplotslibrary{patchplots}" << L"\n";
		o_ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%% customize page numbering" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		o_ssLaTeX << L"\\fancypagestyle{mypagestylewithtotalpagenumbers}{" << L"\n"; //
		o_ssLaTeX << L"\\lhead{}" << L"\n"; // 
		o_ssLaTeX << L"\\rhead{}" << L"\n"; //
		o_ssLaTeX << L"\\cfoot{\\thepage/\\pageref{LastPage}}" << L"\n"; // 
		o_ssLaTeX << L"\\renewcommand{\\headrulewidth}{0.0pt}" << L"\n"; // 
		o_ssLaTeX << L"}" << L"\n";
		o_ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%% output up to 4-th level" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		o_ssLaTeX << L"\\setcounter{secnumdepth}{4}" << L"\n";
		o_ssLaTeX << L"\\setcounter{tocdepth}{4}" << L"\n";
		o_ssLaTeX << L"\\setlength{\\topmargin}{-1cm}" << L"\n";
		o_ssLaTeX << L"\\setlength{\\textheight}{37cm}" << L"\n";
		o_ssLaTeX << L"\\setlength{\\textwidth}{25cm}" << L"\n";
		o_ssLaTeX << L"\\setlength{\\oddsidemargin}{-5mm}" << L"\n";
		o_ssLaTeX << L"\\setlength{\\evensidemargin}{-5mm}" << L"\n";
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"%%%\\renewcommand{ \\figurename }{Figure }" << L"\n";
		o_ssLaTeX << L"%%%\\renewcommand{ \\tablename }{Table }" << L"\n";
		o_ssLaTeX << L"%%%\\renewcommand{ \\refname }{References}" << L"\n";
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"\\definecolor{rowcolorlightblue}{RGB}{191,233,251}" << L"\n";
		o_ssLaTeX << L"\\definecolor{bordercolordarkblue}{RGB}{0,163,243}" << L"\n";
		o_ssLaTeX << L"\\definecolor{BleuDur}{RGB}{27,61,176}" << L"\n";
		o_ssLaTeX << L"\\definecolor{Nigelle}{RGB}{0,133,201}" << L"\n";
		o_ssLaTeX << L"\\definecolor{BleuFaience}{RGB}{105,171,219}" << L"\n";
		o_ssLaTeX << L"\\definecolor{anotherlightblue}{RGB}{61,143,244}" << L"\n";
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"\\def\\chpcolor{BleuDur}" << L"\n";
		o_ssLaTeX << L"\\def\\chpcolortxt{BleuDur}" << L"\n";
		o_ssLaTeX << L"\\def\\sectionfont{\\sffamily\\LARGE}" << L"\n";
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"\\makeatletter" << L"\n";
		o_ssLaTeX << L"%Section:" << L"\n";
		o_ssLaTeX << L"\\def\\@sectionstrut{\\vrule\\@width\\z@\\@height12.5\\p@}" << L"\n";
		o_ssLaTeX << L"\\def\\@makesectionhead#1{%" << L"\n";
		o_ssLaTeX << L"  {\\par\\vspace{20pt}%" << L"\n";
		o_ssLaTeX << L"   \\parindent 0pt\\raggedleft\\sectionfont" << L"\n";
		o_ssLaTeX << L"   \\colorbox{\\chpcolor}{%" << L"\n";
		o_ssLaTeX << L"     \\parbox[t]{90pt}{\\color{white}\\@sectionstrut\\@depth4.5\\p@\\hfill" << L"\n";
		o_ssLaTeX << L"       \\ifnum\\c@secnumdepth>\\z@\\thesection\\fi}%" << L"\n";
		o_ssLaTeX << L"   }%" << L"\n";
		o_ssLaTeX << L"   \\begin{minipage}[t]{\\dimexpr\\textwidth-90pt-2\\fboxsep\\relax}" << L"\n";
		o_ssLaTeX << L"   \\color{\\chpcolortxt}\\@sectionstrut\\hspace{5pt}#1" << L"\n";
		o_ssLaTeX << L"   \\end{minipage}\\par" << L"\n";
		o_ssLaTeX << L"   \\vspace{10pt}%" << L"\n";
		o_ssLaTeX << L"  }" << L"\n";
		o_ssLaTeX << L"}" << L"\n";
		o_ssLaTeX << L"\\def\\section{\\@afterindentfalse\\secdef\\@section\\@ssection}" << L"\n";
		o_ssLaTeX << L"\\def\\@section[#1]#2{%" << L"\n";
		o_ssLaTeX << L"  \\ifnum\\c@secnumdepth>\\m@ne" << L"\n";
		o_ssLaTeX << L"    \\refstepcounter{section}%" << L"\n";
		o_ssLaTeX << L"    \\addcontentsline{toc}{section}{\\protect\\numberline{\\thesection}#1}%" << L"\n";
		o_ssLaTeX << L"  \\else" << L"\n";
		o_ssLaTeX << L"    \\phantomsection" << L"\n";
		o_ssLaTeX << L"    \\addcontentsline{toc}{section}{#1}%" << L"\n";
		o_ssLaTeX << L"  \\fi" << L"\n";
		o_ssLaTeX << L"  \\sectionmark{#1}%" << L"\n";
		o_ssLaTeX << L"  \\if@twocolumn" << L"\n";
		o_ssLaTeX << L"    \\@topnewpage[\\@makesectionhead{#2}]%" << L"\n";
		o_ssLaTeX << L"  \\else" << L"\n";
		o_ssLaTeX << L"    \\@makesectionhead{#2}\\@afterheading" << L"\n";
		o_ssLaTeX << L"  \\fi" << L"\n";
		o_ssLaTeX << L"}" << L"\n";
		o_ssLaTeX << L"\\def\\@ssection#1{%" << L"\n";
		o_ssLaTeX << L"  \\if@twocolumn" << L"\n";
		o_ssLaTeX << L"    \\@topnewpage[\\@makesectionhead{#1}]%" << L"\n";
		o_ssLaTeX << L"  \\else" << L"\n";
		o_ssLaTeX << L"    \\@makesectionhead{#1}\\@afterheading" << L"\n";
		o_ssLaTeX << L"  \\fi" << L"\n";
		o_ssLaTeX << L"}" << L"\n";
		o_ssLaTeX << L"\\makeatother" << L"\n";
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"\\setlength{ \\topmargin }{-1.5cm}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_ssLaTeX << ssSep.str();
		o_ssLaTeX << L"\\pagestyle{mypagestylewithtotalpagenumbers}" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"%%%%%%" << L"\n";
		o_ssLaTeX << L"\\title{Test report of based on BSI AIS 20 / AIS 31}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		const auto pt =
			boost::posix_time::ptime(
				boost::posix_time::microsec_clock::local_time());

		const std::string strTimeInfo(boost::posix_time::to_simple_string(pt));

		const int size_needed = MultiByteToWideChar(CP_UTF8, 0, strTimeInfo.data(), static_cast<int>(strTimeInfo.size()), nullptr, 0);
		std::wstring    wstrTimeInfo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, strTimeInfo.data(), static_cast<int>(strTimeInfo.size()), wstrTimeInfo.data(), size_needed);

		o_ssLaTeX << L"\\date{" << wstrTimeInfo << L"}" << L"\n";
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
	/// <params="o_ssLaTeX">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus loadLaTeXBibliography(std::wstringstream& o_ssLaTeX)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream	ssSep = std::wstringstream();
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%  Bibliography" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_ssLaTeX << ssSep.rdbuf();
		o_ssLaTeX << L"\\normalsize" << L"\n";
		o_ssLaTeX << L"\\addcontentsline{toc}{chapter}{\\refname}" << L"\n";
		o_ssLaTeX << L"\\begin{thebibliography}{99}" << L"\n";
		o_ssLaTeX << L"% 1" << L"\n";
		o_ssLaTeX << L"\\bibitem{AIS2031An_11}" << L"\n";
		o_ssLaTeX << L"W. Killmann and W. Schindler." << L"\n";
		o_ssLaTeX << L"\\textit{A proposal for: Functionality classes for random number generators}," << L"\n";
		o_ssLaTeX << L"Version 2.0 (18.09.2011), " << L"\n";
		o_ssLaTeX << L"\\url{https://www.bsi.bund.de/dok/ais-20-31-appx-2011}" << L"\n";
		o_ssLaTeX << L"\\end{thebibliography}" << L"\n\n";
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
	/// <params="o_refLaTeXSupportingInfo">
	/// </params>
	/// <params="i_refInfoReport">
	/// </params>
	/// <params="i_refTestSpecificString">
	/// </params>
	/// <params="io_refInfoInputDataItem">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportLaTeXSupportingInfoInputDataItem(std::wstringstream& o_refLaTeXSupportingInfo,
		const IDInfoForReport& i_refInfoReport,
		const ais_31_tool::constants::EnmHashAlgorithm i_enmHashAlgorithmId,
		const std::wstring& i_refTestSpecificString,
		const InfoInputDataItem& io_refInfoInputDataItem,
		const int i_NoOfInputDataItem)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// calculate hash value of the acquisition data in advance
		// -------------------------------------------------------------------------- //
		std::string strHashOfAcquisitionData = std::string();

		const ns_consts::EnmReturnStatus  stsCalcHash = ais_31_tool::calcMessageDigest(strHashOfAcquisitionData,
			*io_refInfoInputDataItem.p_path_to_input_data,
			i_enmHashAlgorithmId);

		if (ns_consts::EnmReturnStatus::Success != stsCalcHash)
		{
			return  sts = stsCalcHash;
		}    
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\cellcolor{anotherlightblue} & ";
		o_refLaTeXSupportingInfo << L"Path to the input data " << i_refTestSpecificString << L" & \\verb|";
		o_refLaTeXSupportingInfo << (*io_refInfoInputDataItem.p_path_to_input_data) << L"| \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";

		o_refLaTeXSupportingInfo << L"\\multirow{-2}{*}{\\cellcolor{anotherlightblue} " << i_NoOfInputDataItem << L" } & ";
		switch (i_enmHashAlgorithmId)
		{
		case ais_31_tool::constants::EnmHashAlgorithm::ESHA_256:
			o_refLaTeXSupportingInfo << L"SHA-256";
			break;
		case ais_31_tool::constants::EnmHashAlgorithm::ESHA_384:
			o_refLaTeXSupportingInfo << L"SHA-384";
			break;
		case ais_31_tool::constants::EnmHashAlgorithm::ESHA_512:
			o_refLaTeXSupportingInfo << L"SHA-512";
			break;
		default:
			return  sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
		}
		o_refLaTeXSupportingInfo << L" hash value of the input data " << i_refTestSpecificString << L"[hex] & " << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{BVerbatim}" << L"\n";

		const int size_needed = MultiByteToWideChar(CP_UTF8, 0, strHashOfAcquisitionData.data(), static_cast<int>(strHashOfAcquisitionData.size()), nullptr, 0);
		std::wstring    wstrHashOfAcquisitionData(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, strHashOfAcquisitionData.data(), static_cast<int>(strHashOfAcquisitionData.size()), wstrHashOfAcquisitionData.data(), size_needed);

		o_refLaTeXSupportingInfo << wstrHashOfAcquisitionData << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{BVerbatim} " << L"\n";
		o_refLaTeXSupportingInfo << L"\\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";

		struct tm newtime;

		errno_t err = localtime_s(&newtime, &(io_refInfoInputDataItem.tm_last_write_time));
		if (err)
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorInvalidData;
		}

		o_refLaTeXSupportingInfo << L"\\cellcolor{anotherlightblue} & ";
		o_refLaTeXSupportingInfo << L"Last write time & " << std::put_time(&newtime, L"%Y-%b-%d %H:%M:%S") << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
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
	/// <params="o_refLaTeXSupportingInfo">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportLaTeXSupportingCompilerInfo(std::wstringstream& o_refLaTeXSupportingInfo)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// compiler information
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & built by & ";
		{
#if defined(_MSC_VER) && !defined(__INTEL_LLVM_COMPILER) && !defined(__INTEL_COMPILER)
#if _MSC_VER >= 1940
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.10";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1939
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.9";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1938
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.8";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1937
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.7";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1936
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.6";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1935
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.5";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1934
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.4";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1933
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.3";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1932
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.2";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1931
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 version 17.1";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1930
			o_refLaTeXSupportingInfo << L" Visual Studio 2022 RTW (17.0)";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1929
			o_refLaTeXSupportingInfo << L" Visual Studio 2019 version ";
#if _MSC_FULL_VER >= 192930100 
			o_refLaTeXSupportingInfo << L"16.11";
#else
			o_refLaTeXSupportingInfo << L"16.10";
#endif
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1928
			o_refLaTeXSupportingInfo << L" Visual Studio 2019 version ";
#if _MSC_FULL_VER >= 192829500 
			o_refLaTeXSupportingInfo << L"16.9";
#else
			o_refLaTeXSupportingInfo << L"16.8";
#endif
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#elif _MSC_VER >= 1927
			o_refLaTeXSupportingInfo << L" Visual Studio 2019 version 16.7";
			o_refLaTeXSupportingInfo << L" (\\verb|_MSC_FULL_VER|: " << _MSC_FULL_VER << L" )";
#endif
#elif defined(_MSC_VER) && defined(__INTEL_LLVM_COMPILER)
			o_refLaTeXSupportingInfo << L" Intel C++ Compiler";
			o_refLaTeXSupportingInfo << L" (";
			o_refLaTeXSupportingInfo << L" \\verb|__INTEL_LLVM_COMPILER|: " << __INTEL_LLVM_COMPILER;
			o_refLaTeXSupportingInfo << L" )";
#elif defined(_MSC_VER) && defined(__INTEL_COMPILER)
			o_refLaTeXSupportingInfo << L" Intel C++ Compiler Classic";
			o_refLaTeXSupportingInfo << L" (";
			o_refLaTeXSupportingInfo << L" \\verb|__INTEL_COMPILER|: " << __INTEL_COMPILER;
			o_refLaTeXSupportingInfo << L" )";
#endif
		}
		o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
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
	/// <params="o_refLaTeXSupportingInfo">
	/// </params>
	/// <params="i_refInfoReport">
	/// </params>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportLaTeXSupportingInfo(std::wstringstream& o_refLaTeXSupportingInfo,
		const IDInfoForReport& i_refInfoReport,
		const ns_dt::t_data_for_v2& i_refData)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\section{Identification information}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\subsection{Identification information of input data}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\begin{itemize}" << L"\n";
		o_refLaTeXSupportingInfo << L"		\\item Filename(s) of input data : See Annex \\ref{sec:AnnexIdentification}." << L"\n";
		o_refLaTeXSupportingInfo << L"		\\item Name of the submitter of the input data : " << L"\n";
		o_refLaTeXSupportingInfo << L"		    \\begin{Form}" << L"\n";
		o_refLaTeXSupportingInfo << L"		    \\noindent" << L"\n";
		o_refLaTeXSupportingInfo << L"		    \\TextField[name=NameOfSubmitter, multiline=false, bordercolor=bordercolordarkblue,width=17cm,height=1cm]{}" << L"\n";
		o_refLaTeXSupportingInfo << L"		    \\end{Form}" << L"\n";
		o_refLaTeXSupportingInfo << L"\t	\\item Brief explanation of the input data : \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\t	    \\begin{Form}" << L"\n";
		o_refLaTeXSupportingInfo << L"\t	    \\noindent" << L"\n";
		o_refLaTeXSupportingInfo << L"\t	    \\TextField[name=ExplanationOfInputData, multiline=true, bordercolor=bordercolordarkblue,width=\\linewidth,height=2.5in]{}" << L"\n";
		o_refLaTeXSupportingInfo << L"\t	    \\end{Form}" << L"\n";
		o_refLaTeXSupportingInfo << L"\t\\end{itemize} " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\subsection{Identification of analysis environment}" << L"\n";

		o_refLaTeXSupportingInfo << L"\\renewcommand{\\arraystretch}{1.8}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{table}[h]" << L"\n";
		o_refLaTeXSupportingInfo << L"\\caption{Identification information of analysis environment}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{center}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{tabular}{|>{\\columncolor{anotherlightblue}}l|>{\\columncolor{anotherlightblue}}l|p{12cm}|}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"Analysis tool & Name & " << (*i_refInfoReport.info_analysis_tool.p_analyzer_name) << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & Versioning information & " << (*i_refInfoReport.info_analysis_tool.p_analyzer_versioning) << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & built as & ";
		{
#if defined(_WIN64)
			o_refLaTeXSupportingInfo << L" 64-bit application";
#elif defined(_WIN32)
			o_refLaTeXSupportingInfo << L" 32-bit application";
#else
#endif
		}
		o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// compiler information
		// -------------------------------------------------------------------------- //
		const ns_consts::EnmReturnStatus  stsCompiler = reportLaTeXSupportingCompilerInfo(o_refLaTeXSupportingInfo);
		if (ns_consts::EnmReturnStatus::Success != stsCompiler)
		{
			return  sts = stsCompiler;
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & linked libraries & ";
		{
			o_refLaTeXSupportingInfo << L" Boost C++ ";
			o_refLaTeXSupportingInfo << BOOST_VERSION / 100000 << L"." << ((BOOST_VERSION / 100) % 1000) << L"." << BOOST_VERSION % 100;
			o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
		}
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & with & ";
		{
#if defined(_OPENMP)
			o_refLaTeXSupportingInfo << L"OpenMP enabled \\\\" << L"\n";
#else
			o_refLaTeXSupportingInfo << L"OpenMP disabled \\\\" << L"\n";
#endif
		}
		o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"Analysis environment & Hostname & ";
		o_refLaTeXSupportingInfo << L"\\censor{";   // censor/redact
		o_refLaTeXSupportingInfo << (*i_refInfoReport.info_env.p_hostname);
		o_refLaTeXSupportingInfo << L"}";           // censor/redact
		o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, & CPU information & " << (*i_refInfoReport.info_env.p_cpuinfo) << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, &  Physical memory size & " << (*i_refInfoReport.info_env.p_physicalmemory) << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, &  OS information & " << (*i_refInfoReport.info_env.p_osinfo) << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\cline{2-3}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\, &  Username & ";
		o_refLaTeXSupportingInfo << L"\\censor{";   // censor/redact
		o_refLaTeXSupportingInfo << (*i_refInfoReport.info_env.p_username);
		o_refLaTeXSupportingInfo << L"}";           // censor/redact
		o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{tabular}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{center}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{table}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\renewcommand{\\arraystretch}{1.4}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\subsection{Identification of analysis conditions}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\renewcommand{\\arraystretch}{1.8}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{table}[h]" << L"\n";
		o_refLaTeXSupportingInfo << L"\\caption{Identification information of analysis conditions}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{center}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\begin{tabular}{|>{\\columncolor{anotherlightblue}}l|p{8cm}|}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\hline " << L"\n";
		if (i_refData.isT0Selected)
		{
			o_refLaTeXSupportingInfo << L"Number of samples for Test T0 & " << i_refData.p_bzInputDataT0->extent(blitz::firstDim) << L" \\\\" << L"\n";
			o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		}
		if (i_refData.areT1ThroughT5Selected)
		{
			o_refLaTeXSupportingInfo << L"Number of samples in each set for Tests T1 through T5 & " << i_refData.p_bzInputDataT1->extent(blitz::secondDim) << L" \\\\" << L"\n";
			o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		}
		o_refLaTeXSupportingInfo << L"Bits per sample & " << i_refData.bits_per_sample << L" \\\\" << L"\n";
		o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		if (1 < i_refData.bits_per_sample)
		{
			o_refLaTeXSupportingInfo << L"Byte to bit conversion & " << L"\n";
			if (i_refData.bIsMSbFirstByteBitConversion)
			{
				o_refLaTeXSupportingInfo << L"Most Significant bit (MSb) first" << L"\n";
			}
			else
			{
				o_refLaTeXSupportingInfo << L"Least Significant bit (LSb) first" << L"\n";
			}
			o_refLaTeXSupportingInfo << L" \\\\" << L"\n";
			o_refLaTeXSupportingInfo << L"\\hline" << L"\n";
		}
		o_refLaTeXSupportingInfo << L"\\end{tabular}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{center}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\end{table}" << L"\n";
		o_refLaTeXSupportingInfo << L"\\renewcommand{\\arraystretch}{1.4}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXSupportingInfo << L"\\subsection{Identification of analysis method}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if ((i_refData.isT0Selected) && (i_refData.areT1ThroughT5Selected))
		{
			o_refLaTeXSupportingInfo << L"Test Procedure A of BSI AIS 20 / AIS 31 \\cite{AIS2031An_11} is applied." << L"\n";
		}
		else if (i_refData.isT0Selected)
		{
			o_refLaTeXSupportingInfo << L"Test T0 of BSI AIS 20 / AIS 31\\cite{AIS2031An_11} is applied." << L"\n";
		}
		else if (i_refData.areT1ThroughT5Selected)
		{
			o_refLaTeXSupportingInfo << L"Tests T1 - T5 of BSI AIS 20 / AIS 31\\cite{AIS2031An_11} are applied." << L"\n";
		}
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
	/// <params="o_refLaTeXAppendix">
	/// </params>
	/// <params="i_refInfoReport">
	/// </params>
	/// <params="i_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportLaTeXAppendix(std::wstringstream& o_refLaTeXAppendix,
		const IDInfoForReport& i_refInfoReport,
		const ns_dt::t_data_for_v2& i_refData)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXAppendix << L"\\section{Identification information} " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXAppendix << L"\\subsection{Identification of input data} \\label{sec:AnnexIdentification}" << L"\n";
		o_refLaTeXAppendix << L"\\scriptsize" << L"\n";
		o_refLaTeXAppendix << L"\\renewcommand{\\arraystretch}{1.8}" << L"\n";
		o_refLaTeXAppendix << L"\\begin{longtable}{|>{\\cellcolor{anotherlightblue}}p{0.7cm}|>{\\columncolor{anotherlightblue}}p{7cm}|p{16cm}|}" << L"\n";
		o_refLaTeXAppendix << L"\\caption{Identification information of input data} \\\\" << L"\n";
		o_refLaTeXAppendix << L"\\hline {\\cellcolor{anotherlightblue}No} & Item & Value \\\\ \\hline \\hline " << L"\n";
		o_refLaTeXAppendix << L"\\endfirsthead " << L"\n";
		o_refLaTeXAppendix << L"\\hline No & Item & Value \\\\ \\hline " << L"\n";
		o_refLaTeXAppendix << L"\\endhead " << L"\n";
		o_refLaTeXAppendix << L"\\hline  \\multicolumn{3}{|r|}{continued...} " << L"\n";
		o_refLaTeXAppendix << L"\\endfoot " << L"\n";
		o_refLaTeXAppendix << L"\\hline  \\multicolumn{3}{|r|}{end of the table} " << L"\n";
		o_refLaTeXAppendix << L"\\endlastfoot " << L"\n";

		// -------------------------------------------------------------------------- //
		// calculate hash value of the acquisition data
		// -------------------------------------------------------------------------- //
		int	number_of_entry = 1;
		// -------------------------------------------------------------------------- //
		// calculate hash value of the acquisition data
		// -------------------------------------------------------------------------- //
		constexpr ais_31_tool::constants::EnmHashAlgorithm  enmDefaultHashId = ais_31_tool::constants::EnmHashAlgorithm::ESHA_256;
		std::string strHashOfAcquisitionData = std::string();

		if (nullptr != i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
		{
			const InfoInputDataItem* pInfoInputDataItem = &i_refInfoReport.info_source.info_input_data_testT0;

			const ns_consts::EnmReturnStatus  stsCalcHash = ais_31_tool::calcMessageDigest(strHashOfAcquisitionData,
				*(pInfoInputDataItem->p_path_to_input_data),
				enmDefaultHashId);

			if (ns_consts::EnmReturnStatus::Success != stsCalcHash)
			{
				return  sts = stsCalcHash;
			}

			std::wstring    wstrTestSpecific = std::wstring(L"for Test T0");

			sts = reportLaTeXSupportingInfoInputDataItem(o_refLaTeXAppendix, i_refInfoReport, enmDefaultHashId, wstrTestSpecific, *pInfoInputDataItem, number_of_entry);
			if (ns_consts::EnmReturnStatus::Success != sts)
			{
				return  sts;
			}
			++number_of_entry;
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if ((nullptr != i_refInfoReport.info_source.p_info_input_data_items_testT1)
			&& (false == i_refInfoReport.info_source.p_info_input_data_items_testT1->empty()))
		{
			BOOST_FOREACH(const InfoInputDataItem & info_item, *(i_refInfoReport.info_source.p_info_input_data_items_testT1)) {
				const ns_consts::EnmReturnStatus  stsCalcHash = ais_31_tool::calcMessageDigest(strHashOfAcquisitionData,
					*info_item.p_path_to_input_data,
					enmDefaultHashId);

				if (ns_consts::EnmReturnStatus::Success != stsCalcHash)
				{
					return  sts = stsCalcHash;
				}

				std::wstring    wstrTestSpecific = std::wstring(L"for Test T1");

				sts = reportLaTeXSupportingInfoInputDataItem(o_refLaTeXAppendix, i_refInfoReport, enmDefaultHashId, wstrTestSpecific, info_item, number_of_entry);
				if (ns_consts::EnmReturnStatus::Success != sts)
				{
					return  sts;
				}
				++number_of_entry;
			}
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		o_refLaTeXAppendix << L"\\end{longtable}" << L"\n";
		o_refLaTeXAppendix << L"\\renewcommand{\\arraystretch}{1.8}" << L"\n";
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
	/// <params="i_refReportPath">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus showLaTeXCompilationHint(const bs_fs::path& i_refReportPath)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// Output supplementary information to compile XeLateX source file
		// -------------------------------------------------------------------------- //
		setlocale(LC_ALL, "");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::wcout << L"\n";
		std::wcout << L"# [INFO] In order to compile the generated XeLaTeX source file of test report, " << L"\n";
		std::wcout << L"# [INFO] you need to type the following command and press Enter key." << L"\n";
		std::wcout << L"# [INFO] ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L" xelatex " << i_refReportPath.wstring() << L"\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L"\n";
		std::wcout << L"# [INFO] In a case where you get an error message like ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		std::wcout << L"\"TeX capacity exceeded, sorry [main memory size=...]\"," << L"\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L"# [INFO] first you need to update the \"texmf.cnf\" file so as to modify the memory size like as follows:" << L"\n";
		std::wcout << L"# [INFO] ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L" main_memory = 12400000" << L"\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L"# [INFO] Next you need to run command prompt with Administrator privilege and type as follows:" << L"\n";
		std::wcout << L"# [INFO] ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L" fmtutil-sys --all" << L"\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::wcout << L"# [INFO] and press \"Enter\" key";
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
	/// <params="i_refInfoReport">
	/// </params>
	/// <params="io_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus reportLaTeX(IDInfoForReport& i_refInfoReport,
		ns_dt::t_data_for_v2& io_refData)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		if (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1)
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (true == i_refInfoReport.info_source.p_info_input_data_items_testT1->empty())
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if ((nullptr == i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
			&& (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data))
		{
			return  sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		bs_fs::path the_report_path_LaTeX;
		if (nullptr == i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data)
		{
			sts = synthesizeReportPathTex(the_report_path_LaTeX, *i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data);
		}
		else if (nullptr == i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data)
		{
			sts = synthesizeReportPathTex(the_report_path_LaTeX, *(i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data));
		}
		else
		{
			sts = synthesizeReportPathTex(the_report_path_LaTeX, *i_refInfoReport.info_source.info_input_data_testT0.p_path_to_input_data);
		}
		if (ns_consts::EnmReturnStatus::Success != sts)
		{
			return  sts;
		}
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream ssLaTeXSummary = std::wstringstream();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"\\begin{table}[h]" << L"\n";
		ssLaTeXSummary << L"\\caption{Test results}" << L"\n";
		ssLaTeXSummary << L"\\begin{center}" << L"\n";
		ssLaTeXSummary << L"\\begin{tabular}{|l|c|c|}" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		ssLaTeXSummary << L"\\rowcolor{anotherlightblue} %%" << L"\n";
		ssLaTeXSummary << L"Tests							& Pass / Fail & Notes 	\\\\ " << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T0 (disjointness test)		& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT0.pass_fail_result);
		ssLaTeXSummary << L" & ---         \\\\" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T1 (monobit test)			& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT1.pass_fail_result);
		ssLaTeXSummary << L" & see \\ref{sec:TestT1}         \\\\" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T2 (poker test)			& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT2.pass_fail_result);
		ssLaTeXSummary << L" & see \\ref{sec:TestT2}         \\\\" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T3 (runs test)				& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT3.pass_fail_result);
		ssLaTeXSummary << L" & see \\ref{sec:TestT3}         \\\\" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T4 (long runs test)		& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT4.pass_fail_result);
		ssLaTeXSummary << L" & ---         \\\\" << L"\n";
		ssLaTeXSummary << L"\\hline " << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"Test T5 (autocorrelation test)	& ";
		ssLaTeXSummary << getPassFail(io_refData.t_testT5.pass_fail_result);
		ssLaTeXSummary << L" & see \\ref{sec:TestT5}         \\\\" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeXSummary << L"\\hline " << L"\n";
		ssLaTeXSummary << L"\\end{tabular}" << L"\n";
		ssLaTeXSummary << L"\\end{center}" << L"\n";
		ssLaTeXSummary << L"\\end{table}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream ssLaTeXSupportingInfo = std::wstringstream();
		reportLaTeXSupportingInfo(ssLaTeXSupportingInfo, i_refInfoReport, io_refData);
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream ssLaTeX = std::wstringstream();
		loadLaTeXPreamble(ssLaTeX);
		ssLaTeX << L"\\begin{document}" << L"\n";
		ssLaTeX << L"\\StopCensoring" << L"\n";
		ssLaTeX << L"\\maketitle" << L"\n";
		ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssLaTeX << L"%%%%%%" << L"\n";
		ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssLaTeX << L"\\thispagestyle{mypagestylewithtotalpagenumbers}" << L"\n";
		ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssLaTeX << L"%%%%%%" << L"\n";
		ssLaTeX << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << ssLaTeXSupportingInfo.rdbuf();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << L"\\clearpage" << L"\n";
		ssLaTeX << L"\\section{Executive summary}" << L"\n";
		ssLaTeX << L"\\subsection{Test results based on BSI AIS 20 / AIS 31}" << L"\n";
		ssLaTeX << ssLaTeXSummary.rdbuf();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << L"\\clearpage" << L"\n";
		ssLaTeX << L"\\section{Detailed information of tests for given input data}" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << io_refData.p_ssLaTeXFragment->rdbuf();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		std::wstringstream	ssSep = std::wstringstream();
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%  Appendix" << L"\n";
		ssSep << L"%%%%%%" << L"\n";
		ssSep << L"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << L"\n";
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << ssSep.rdbuf();
		ssLaTeX << L"\\appendix" << L"\n";
		std::wstringstream ssAppendix = std::wstringstream();
		reportLaTeXAppendix(ssAppendix, i_refInfoReport, io_refData);
		ssLaTeX << ssAppendix.rdbuf();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << L"\\clearpage" << L"\n";
		std::wstringstream ssBiblio = std::wstringstream();
		loadLaTeXBibliography(ssBiblio);
		ssLaTeX << ssBiblio.rdbuf();
		// -------------------------------------------------------------------------- //
		// 
		// -------------------------------------------------------------------------- //
		ssLaTeX << L"\\end{document}" << L"\n";
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		boost::filesystem::wofstream	file(the_report_path_LaTeX);
		if (!file)
		{
			return sts = ns_consts::EnmReturnStatus::ErrorFileIO;
		}
		file << ssLaTeX.rdbuf();
		file.close();
		// -------------------------------------------------------------------------- //
		// Output supplementary information to compile XeLateX source file
		// -------------------------------------------------------------------------- //
		return  sts = showLaTeXCompilationHint(the_report_path_LaTeX);
	}

}