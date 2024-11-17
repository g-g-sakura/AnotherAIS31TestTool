// AIS31TestTool.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "parse.h"
#include "performTests.h"
#include "hostinfo.h"
#include "reporter.h"
#include "toolinfo.h"

namespace bs_fs = boost::filesystem;

namespace ns_consts = ais_31_lib::constants;
namespace ns_dt = ais_31_lib::data_types;
namespace ns_tool = ais_31_tool;

typedef ns_consts::EnmReturnStatus(*PF_EE)(ns_dt::t_data_for_v3&);

int wmain(int ac, wchar_t* av[], wchar_t* envp[])
{
    ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    ns_dt::t_data_for_v3     data;
    memset(&data, 0, sizeof(data));
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    ns_tool::IDInfoForReport the_info_report;
    memset(&the_info_report, 0, sizeof(the_info_report));
    // -------------------------------------------------------------------------- //
    // obtain tool information, for traceability
    // -------------------------------------------------------------------------- //
    std::wstring strToolName;
    std::wstring strToolVersioning;
    the_info_report.info_analysis_tool.p_analyzer_name = &strToolName;
    the_info_report.info_analysis_tool.p_analyzer_versioning = &strToolVersioning;
    sts = ns_tool::getToolInfo(the_info_report.info_analysis_tool);
    if (ns_consts::EnmReturnStatus::Success == sts)
    {
        std::wcout << L"# \t\t" << strToolName << L"\n";
        std::wcout << L"# \t\tVersion info:\t" << strToolVersioning << L"\n";
    }
    // -------------------------------------------------------------------------- //
    // show host name and username, for traceability
    // -------------------------------------------------------------------------- //
    std::wstring strHostName;
    std::wstring strCPUInfo;
    std::wstring strPhysicalMemory;
    std::wstring strOSName;
    std::wstring strOSVersion;
    std::wstring strSystemType;
    std::wstring strUserName;
    the_info_report.info_env.p_hostname = &strHostName;
    the_info_report.info_env.p_cpuinfo = &strCPUInfo;
    the_info_report.info_env.p_physicalmemory = &strPhysicalMemory;
    the_info_report.info_env.p_osname = &strOSName;
    the_info_report.info_env.p_osversion = &strOSVersion;
    the_info_report.info_env.p_system_type = &strSystemType;
    the_info_report.info_env.p_username = &strUserName;
    sts = ns_tool::getEnvInfo(the_info_report.info_env);
    if (ns_consts::EnmReturnStatus::Success == sts)
    {
        std::wcout << std::wstring(L"# Host name:\t") << strHostName << L"\n";
        std::wcout << std::wstring(L"# CPU id:\t") << strCPUInfo << L"\n";
        std::wcout << std::wstring(L"# Amount of Physical Memory:\t") << strPhysicalMemory << L"\n";
        std::wcout << std::wstring(L"# OS name:\t") << strOSName << L"\n";
        std::wcout << std::wstring(L"# OS version:\t") << strOSVersion << L"\n";
        std::wcout << std::wstring(L"# System type:\t") << strSystemType << L"\n";
        std::wcout << std::wstring(L"# User name:\t") << strUserName << L"\n";
    }
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    bs_fs::path     the_report_path;
    bs_fs::path     the_path_input_data_testT0;
    bs_fs::path     the_path_input_data_testT1;
    // -------------------------------------------------------------------------- //
    // parse command line parameters
    // -------------------------------------------------------------------------- //
    sts = ns_tool::parse(data, the_info_report, ac, av, envp);
    if (ns_consts::EnmReturnStatus::Success != sts)
    {
        return  static_cast<int>(sts);
    }
    // -------------------------------------------------------------------------- //
    // show some samples from the head of file, for confirmation
    // -------------------------------------------------------------------------- //
    ns_tool::showHeadSamplesTest(data);
    // -------------------------------------------------------------------------- //
    // show some samples from the tail of file, for confirmation
    // -------------------------------------------------------------------------- //
    ns_tool::showTailSamplesTest(data);
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    std::wstringstream ssLaTeXFragmentBody = std::wstringstream();
    data.p_ssLaTeXFragment = &ssLaTeXFragmentBody;
    // -------------------------------------------------------------------------- //
    // perform tests
    // -------------------------------------------------------------------------- //
    sts = ns_tool::performTests(data, the_info_report);
    if (ns_consts::EnmReturnStatus::Success != sts)
    {
        return  static_cast<int>(sts);
    }
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    sts = ns_tool::reportXML(the_info_report, data);
    if (ns_consts::EnmReturnStatus::Success != sts)
    {
        return  static_cast<int>(sts);
    }
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    if (data.isGeneratingReportInLaTeXformatRequested)
    {
        // -------------------------------------------------------------------------- //
        // 
        // -------------------------------------------------------------------------- //
        sts = ns_tool::reportLaTeX(the_info_report, data);
        if (ns_consts::EnmReturnStatus::Success != sts)
        {
            return  static_cast<int>(sts);
        }
    }
    // -------------------------------------------------------------------------- //
    // 
    // -------------------------------------------------------------------------- //
    return  (int)sts;
}