////////////////////////////////////////////////////////////////////////////////
// parse.cpp
//
//
//
// Copyright (c) 2023-2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <boost/program_options.hpp>
#include "AIS31Lib/support/setUp.h"
#include "parse.h"
#include "synthesizeFilename.h"
#include "loadInputData.h"
#include <locale> 
#include <Windows.h>

namespace bs_po = boost::program_options;

namespace ais_31_tool
{
    ns_consts::EnmReturnStatus parse(ns_dt::t_data_for_v3& io_refData,
        IDInfoForReport& i_refInfoReport,
        int ac, wchar_t* av[], wchar_t* envp[])
    {
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        constexpr  boost::uintmax_t file_size_limit = 32 * 1024 * 1024;
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        constexpr   uintmax_t   minimum_data_size = 2040000;
        constexpr   uintmax_t   sufficient_data_size = 2 * minimum_data_size;

        setlocale(LC_ALL, "");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        try {
            int     bits_per_sample = 8;
            int     vl = 1;
            bs_po::options_description desc("Allowed options");
            desc.add_options()
                ("help,h", "Usage is : AIS31TestTool --input <file_name> [-w] [-x] [-v]")
                ("input", bs_po::wvalue<std::wstring>(), "Must be relative path to a binary file for input data for tests T1 through T4.")
                ("bits_per_sample,w", bs_po::value<int>(&bits_per_sample)->default_value(8), "Must be between 1-8, inclusive. By default this value is 8.")
                ("MSb", "    Byte to bitstring conversion is performed by assuming Most Significant bit (MSb) first (default).")
                ("LSb", "    Byte to bitstring conversion is performed by assuming Least Significant bit (LSb) first.")
                ("LaTeX,x", "    Generate a report in LaTeX format.")
                ("verbose_level,v", bs_po::value<int>(&vl)->default_value(1), "Must be between 0-3, inclusive.")
                ;

            bs_po::variables_map po_vm;
            bs_po::store(bs_po::wcommand_line_parser(ac, av).options(desc).run(), po_vm);
            bs_po::notify(po_vm);

            // -------------------------------------------------------------------------- //
            // 
            // 
            // -------------------------------------------------------------------------- //
            if (po_vm.count("help")) {
                std::cout << desc << "\n";
                return  sts = ns_consts::EnmReturnStatus::ErrorNoTask;
            }
            // -------------------------------------------------------------------------- //
            // 
            // 
            // -------------------------------------------------------------------------- //
            if (po_vm.count("bits_per_sample")) {
                if ((bits_per_sample < 1) || (8 < bits_per_sample)) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: Invalid bits per symbol." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    return  sts;
                }
            }
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            memset(&io_refData, 0, sizeof(io_refData));
            const ns_consts::EnmReturnStatus	stsSetUp = ais_31_lib::support::setUp(io_refData);
            if (ns_consts::EnmReturnStatus::Success != stsSetUp)
            {
                return  sts = stsSetUp;
            }
            // -------------------------------------------------------------------------- //
            // 
            // 
            // -------------------------------------------------------------------------- //
            if (po_vm.count("input") == 0) {
                std::cout << "# [INFO]: No file is specified to process." << "\n";
                std::cout << "# [INFO]: Terminates conformance test..." << "\n";
                ais_31_lib::support::tearDown(io_refData);
                return  sts = ns_consts::EnmReturnStatus::ErrorNoTask;
            }
            // -------------------------------------------------------------------------- //
            // load initial input data file for T1 through T4
            // -------------------------------------------------------------------------- //
            if (po_vm.count("input")) {
                const bs_fs::path file_path_testT1 = po_vm["input"].as<std::wstring>(); // <<<
                std::wcout << L"# [INFO]: Opening file:\t";
                std::wcout << file_path_testT1 << L"\n";

                boost::system::error_code error;
                const bool result = bs_fs::exists(file_path_testT1, error);
                if (!result || error) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: Specified file was not found." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    ais_31_lib::support::tearDown(io_refData);
                    return  sts;
                }
                else {
                    std::cout << "# [INFO]: Specified file was found." << "\n";
                }
                // -------------------------------------------------------------------------- //
                // full path
                // -------------------------------------------------------------------------- //
                const bs_fs::path full_path_testT1 = bs_fs::system_complete(file_path_testT1);
                // -------------------------------------------------------------------------- //
                // get path for future use
                // -------------------------------------------------------------------------- //
                if (nullptr != i_refInfoReport.info_source.p_path_to_input_data) {
                    *i_refInfoReport.info_source.p_path_to_input_data = full_path_testT1;
                }
                i_refInfoReport.info_source.tm_last_write_time = bs_fs::last_write_time(full_path_testT1);
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                const boost::uintmax_t size = bs_fs::file_size(file_path_testT1);

                std::cout << "# [INFO]: Its file size: " << size << "-byte" << "\n";
                if (file_size_limit < size)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: Huge file is specified, so the estimation is stopped." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    ais_31_lib::support::tearDown(io_refData);
                    return  sts;
                }
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                io_refData.bits_per_sample = bits_per_sample;
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                sts = ais_31_tool::loadSamples(io_refData, i_refInfoReport, full_path_testT1);
                if (ns_consts::EnmReturnStatus::Success != sts)
                {
                    ais_31_lib::support::tearDown(io_refData);
                    return  sts;
                }
                // -------------------------------------------------------------------------- //
                // 
                // check pre-conditions for L
                // -------------------------------------------------------------------------- //
                if (io_refData.p_bzUnprocessedData->size() < minimum_data_size)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: The input data contains less than " << minimum_data_size << " bits." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    ais_31_lib::support::tearDown(io_refData);
                    return  sts = ns_consts::EnmReturnStatus::ErrorPreconditions;
                }
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                if (io_refData.p_bzUnprocessedData->size() < sufficient_data_size)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                    std::cout << "# [WARNING]: The input data contains less than " << sufficient_data_size << " bits." << "\n";
                    std::cout << "# [WARNING]: If any individual test is failed, then Tirn black box test suite is failed due to insufficient data." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }
            // -------------------------------------------------------------------------- //
            // 
            // 
            // -------------------------------------------------------------------------- //
            if (po_vm.count("LaTeX")) {
                std::cout << "# [INFO]: Generating a report in LaTeX format is requested." << "\n";
                std::cout << "# [INFO]: The report in LaTeX format will be output in the same folder as the input file." << "\n";
                io_refData.isGeneratingReportInLaTeXformatRequested = true;
            }
            // -------------------------------------------------------------------------- //
            // 
            // 
            // -------------------------------------------------------------------------- //
            if (po_vm.count("verbose_level")) {
                if ((vl < 0) || (3 < vl)) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: Invalid verbose level." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    ais_31_lib::support::tearDown(io_refData);
                    return  sts;
                }
                io_refData.verbose_level = vl;
            }
            else
            {

            }
        }
        catch (std::exception& e) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
            std::cerr << "# [ERROR]: error: " << e.what() << "\n";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return sts;
        }
        catch (...) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
            std::cerr << "# [ERROR]: Exception of unknown type!" << "\n";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return	sts;
        }
        return  sts = ns_consts::EnmReturnStatus::Success;
    }
}