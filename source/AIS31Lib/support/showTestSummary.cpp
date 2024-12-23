////////////////////////////////////////////////////////////////////////////////
// showTestSummary.cpp
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "showTestSummary.h"
#include "boost/date_time/posix_time/posix_time.hpp"

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
		/// <param name="o_refStream">
		/// </param>
		/// <param name="i_enmTest">
		/// </param>
		/// <param name="io_refData">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus showTestSpecificHeader(std::stringstream& o_refStream,
			const ns_consts::EnmAIS20AIS31V3Track& i_enmTest,
			ns_dt::t_data_for_v3& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			o_refStream.str("");
			o_refStream << "\n" << "\n";
			o_refStream << "# -------------------------------------------------------------------------- " << "\n";
			o_refStream << "# " << "\n";
			o_refStream << "# Running ";
			switch (i_enmTest)
			{
			case ns_consts::EnmAIS20AIS31V3Track::TestT1:
				o_refStream << "Test T1 (monobit test) ";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT2:
				o_refStream << "Test T2 (poker test) ";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT3:
				o_refStream << "Test T3 (MultiMMC Prediction Estimate) ";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT4:
				o_refStream << "Test T4 (LZ78Y Prediction Estimate) ";
				break;
			default:
				break;
			}
			o_refStream << "\n";
			o_refStream << "# " << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			const auto pt_s =
				boost::posix_time::ptime(
					boost::posix_time::microsec_clock::local_time());

			o_refStream << "#\tThis test was initiated at \t" << pt_s << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << o_refStream.str();
			std::cout.flush();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			ns_dt::t_data_for_performance_info* p_perf = nullptr;
			switch (i_enmTest)
			{
			case ns_consts::EnmAIS20AIS31V3Track::TestT1:
				p_perf = &io_refData.t_testT1.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT2:
				p_perf = &io_refData.t_testT2.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT3:
				p_perf = &io_refData.t_testT3.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT4:
				p_perf = &io_refData.t_testT4.t_performance;
				break;
			default:
				break;
			}
			if (nullptr != p_perf)
			{
				p_perf->startTime = boost::posix_time::to_tm(pt_s);

				const boost::posix_time::ptime	pt_round = boost::posix_time::ptime_from_tm(p_perf->startTime);
				boost::posix_time::time_duration	tdelta = pt_s - pt_round;
				p_perf->start_delta_microseconds = tdelta.total_microseconds();
			}
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
		/// <param name="o_refStream">
		/// </param>
		/// <param name="i_enmTest">
		/// </param>
		/// <param name="io_refData">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus showTestSpecificFooter(std::stringstream& o_refStream,
			const ns_consts::EnmAIS20AIS31V3Track& i_enmTest,
			ns_dt::t_data_for_v3& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			const auto pt_e =
				boost::posix_time::ptime(
					boost::posix_time::microsec_clock::local_time());

			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			o_refStream.str("");
			o_refStream << "# " << "\n";
			o_refStream << "#\tThis test was finished at \t" << pt_e << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			ns_dt::t_data_for_performance_info* p_perf = nullptr;
			switch (i_enmTest)
			{
			case ns_consts::EnmAIS20AIS31V3Track::TestT1:
				p_perf = &io_refData.t_testT1.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT2:
				p_perf = &io_refData.t_testT2.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT3:
				p_perf = &io_refData.t_testT3.t_performance;
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT4:
				p_perf = &io_refData.t_testT4.t_performance;
				break;
			default:
				break;
			}
			if (nullptr != p_perf)
			{
				p_perf->endTime = boost::posix_time::to_tm(pt_e);

				const boost::posix_time::ptime    pt_s = boost::posix_time::ptime_from_tm(p_perf->startTime);
				boost::posix_time::time_duration    tdelta = boost::posix_time::microseconds(p_perf->start_delta_microseconds);
				const boost::posix_time::time_duration    td = pt_e - pt_s - tdelta;
				p_perf->duration = boost::posix_time::to_tm(td);

				o_refStream << "#\tThe time duration for this test :\t" << boost::posix_time::to_simple_string(td) << "\n";
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << o_refStream.str();
			std::cout.flush();
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
		/// <param name="o_refStream">
		/// </param>
		/// <param name="i_enmTest">
		/// </param>
		/// <param name="io_refData">
		/// </param>
		/// <returns>
		/// </returns>
		/// <precondition>
		/// </precondition>
		/// <postcondition>
		/// </postcondition>
		// -------------------------------------------------------------------------- //
		ns_consts::EnmReturnStatus showTestSpecificResult(std::stringstream& o_refStream,
			ns_consts::EnmAIS20AIS31V3Track& i_enmTest,
			ns_dt::t_data_for_v3& io_refData)
		{
			ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::stringstream	ssSampleInterp;
			std::stringstream	ssTrail;
			std::stringstream	ssUnitInfo;
			std::stringstream	ssSeparator = std::stringstream("#\n# --------------------------------------------------------------------------\n");
			std::stringstream	ssSeparatorSimple = std::stringstream("# --------------------------------------------------------------------------\n");
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			o_refStream.str("");
			o_refStream << "# Finalizing ..." << "\n";
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			switch (i_enmTest)
			{
			case ns_consts::EnmAIS20AIS31V3Track::TestT1:
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_refStream << "# " << "Test T1:\t" << "\n";
				o_refStream << "#\tTest result = ";
				switch (io_refData.t_testT1.pass_fail_result)
				{
				case ns_consts::EnmPassFailResults::NotDetermined:
					o_refStream << "Not determined";
					break;
				case ns_consts::EnmPassFailResults::Fail:
					o_refStream << "Fail";
					break;
				case ns_consts::EnmPassFailResults::Pass:
					o_refStream << "Pass";
					break;
				}
				o_refStream << "\n";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT2:
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_refStream << "# " << "Test T2:\t" << "\n";
				o_refStream << "#\tTest result = ";
				switch (io_refData.t_testT2.pass_fail_result)
				{
				case ns_consts::EnmPassFailResults::NotDetermined:
					o_refStream << "Not determined";
					break;
				case ns_consts::EnmPassFailResults::Fail:
					o_refStream << "Fail";
					break;
				case ns_consts::EnmPassFailResults::Pass:
					o_refStream << "Pass";
					break;
				}
				o_refStream << "\n";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT3:
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_refStream << "# " << "Test T3:\t" << "\n";
				o_refStream << "#\tTest result = ";
				switch (io_refData.t_testT3.t_common.pass_fail_result)
				{
				case ns_consts::EnmPassFailResults::NotDetermined:
					o_refStream << "Not determined";
					break;
				case ns_consts::EnmPassFailResults::Fail:
					o_refStream << "Fail";
					break;
				case ns_consts::EnmPassFailResults::Pass:
					o_refStream << "Pass";
					break;
				}
				o_refStream << "\n";
				break;
			case ns_consts::EnmAIS20AIS31V3Track::TestT4:
				// -------------------------------------------------------------------------- //
				// 
				// -------------------------------------------------------------------------- //
				o_refStream << "# " << "Test T4:\t" << "\n";
				o_refStream << "#\tTest result = ";
				switch (io_refData.t_testT4.t_common.pass_fail_result)
				{
				case ns_consts::EnmPassFailResults::NotDetermined:
					o_refStream << "Not determined";
					break;
				case ns_consts::EnmPassFailResults::Fail:
					o_refStream << "Fail";
					break;
				case ns_consts::EnmPassFailResults::Pass:
					o_refStream << "Pass";
					break;
				}
				o_refStream << "\n";
				break;
			default:
				break;
			}
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			std::cout << o_refStream.str() << "\n";
			std::cout.flush();
			// -------------------------------------------------------------------------- //
			// 
			// -------------------------------------------------------------------------- //
			return sts = ns_consts::EnmReturnStatus::Success;
		}
	}
}