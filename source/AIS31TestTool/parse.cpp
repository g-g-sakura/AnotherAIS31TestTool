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

        setlocale(LC_ALL, "");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        try {
            int     bits_per_sample = 8;
            int     vl = 1;
            bs_po::options_description desc("Allowed options");
            desc.add_options()
                ("help,h", "Usage is : ea_non_iid [-i|-c][-a|-t][-v][-l <index>, <samples>] -f <file_name>[-w] [-x]")
                ("inputT0", bs_po::wvalue<std::wstring>(), "Must be relative path to a binary file for input data for test T0.")
                ("inputT1", bs_po::wvalue<std::wstring>(), "Must be relative path to a binary file for input data for test T1 through T5.")
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
            if ((po_vm.count("inputT0") == 0) && (po_vm.count("inputT1") == 0)) {
                std::cout << "# [INFO]: No file is specified to process." << "\n";
                std::cout << "# [INFO]: Terminates conformance test..." << "\n";
                ais_31_lib::support::tearDown(io_refData);
                return  sts = ns_consts::EnmReturnStatus::ErrorNoTask;
            }
            // -------------------------------------------------------------------------- //
            // load initial input data file for T1 through T4
            // -------------------------------------------------------------------------- //
            if (po_vm.count("inputT1")) {
                const bs_fs::path file_path_testT1 = po_vm["inputT1"].as<std::wstring>(); // <<<
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
                if ((nullptr != i_refInfoReport.info_source.p_info_input_data_items_testT1)
                    && (false == i_refInfoReport.info_source.p_info_input_data_items_testT1->empty())) {
                    i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).p_path_to_input_data = new bs_fs::path(full_path_testT1);
                }
                i_refInfoReport.info_source.p_info_input_data_items_testT1->at(0).tm_last_write_time = bs_fs::last_write_time(full_path_testT1);
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
                // obtain offset in input data files index
                // -------------------------------------------------------------------------- //
                unsigned long       offset;
                size_t              digitsOfOffset = 3;
                ns_consts::EnmReturnStatus	stsGetFirstIndex = getFirstIndex(offset, digitsOfOffset, file_path_testT1);
                if (ns_consts::EnmReturnStatus::Success != stsGetFirstIndex)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: More than or equal to 3-digit number is not appended at the file name of the input data file." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    ais_31_lib::support::tearDown(io_refData);
                    return  sts = stsGetFirstIndex;
                }
                else
                {
                    io_refData.offsetOfInputDataFilesIndex = offset;
                    io_refData.numberOfDigitsOfOffset = digitsOfOffset;
                }
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                sts = ais_31_tool::loadSamples(io_refData, i_refInfoReport, full_path_testT1, ns_consts::EnmAIS20AIS31V3Track::TestT1);
                if (ns_consts::EnmReturnStatus::Success != sts)
                {
                    ais_31_lib::support::tearDown(io_refData);
                    return  sts;
                }
                // -------------------------------------------------------------------------- //
                //
                // -------------------------------------------------------------------------- //
                sts = ais_31_tool::performProjection(io_refData, 0);
                if (ns_consts::EnmReturnStatus::Success != sts)
                {
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
                if (io_refData.p_bzInputDataT1->size() < 20000 / 8)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                    std::cout << "# [WARNING]: data contains less than 20,000 samples." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                // -------------------------------------------------------------------------- //
                // 
                // check pre-conditions for L
                // -------------------------------------------------------------------------- //
                if ((io_refData.p_bzInputDataT1->size() * bits_per_sample) < 20000)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                    std::cout << "# [ERROR]: The number of samples does not meet one of pre-conditions for Test T1." << "\n";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    ais_31_lib::support::tearDown(io_refData);
                    return  sts = ns_consts::EnmReturnStatus::ErrorPreconditions;
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