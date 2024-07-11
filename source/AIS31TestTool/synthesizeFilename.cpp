////////////////////////////////////////////////////////////////////////////////
// synthesizeFilename.cpp
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "synthesizeFilename.h"
#include <regex>
#include <sstream>
#include <iomanip>

namespace ais_31_tool
{
    // -------------------------------------------------------------------------- //
/// <summary>
///  Get the first index (or offset) of input data file either from basefilename or extesion.
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="io_refOffset">
///  [Output] specifies the reference to the first index (or offset) to be stored.
/// </param>
/// <param name="io_refNumberOfDigitsOfIndex">
///  [Output] specifies the reference to the digits of the first index (or offset) in the filename.
/// </param>
/// <param name="i_refInitialFilePath">
///  [Input] specifies the file path of initial file.
/// </param>
/// <returns>
///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNotFound</c>:  the file referenced by <c>i_refInitialFilePath</c> is not found.
///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorFirstIndexNotFound</c>:  an appropriate offset cannot be found either from basefilename or extesion:
///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
/// </returns>
/// <precondition>
/// </precondition>
/// <postcondition>
/// </postcondition>
// -------------------------------------------------------------------------- //
    ns_consts::EnmReturnStatus getFirstIndex(unsigned long& io_refOffset,
        size_t& io_refNumberOfDigitsOfIndex,
        const bs_fs::path& i_refInitialFilePath)
    {
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        std::wregex e1(L"([0-9]{3,})$", std::regex::extended);

        boost::system::error_code error;
        const bool result = bs_fs::exists(i_refInitialFilePath, error);
        if (!result || error) {
            return  sts = ns_consts::EnmReturnStatus::ErrorNotFound;
        }
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        std::wstring    wstrBaseFilename = i_refInitialFilePath.stem().c_str();
        std::wstring    wstrExtension = i_refInitialFilePath.extension().c_str();
        std::wsmatch  whatBase;
        std::wsmatch  whatExt;
        bool    bBase = std::regex_search(wstrBaseFilename.cbegin(), wstrBaseFilename.cend(), whatBase, e1);
        bool    bExt = std::regex_search(wstrExtension.cbegin(), wstrExtension.cend(), whatExt, e1);

        if ((true == bBase) && (false == bExt))
        {
            std::wstring    wstrIndex = std::wstring(whatBase[1].first, whatBase[1].second);
            io_refOffset = std::stoul(wstrIndex);
            io_refNumberOfDigitsOfIndex = wstrIndex.length();
            sts = ns_consts::EnmReturnStatus::Success;
        }
        else if (true == bExt)
        {
            std::wstring    wstrIndex = std::wstring(whatExt[1].first, whatExt[1].second);
            io_refOffset = std::stoul(wstrIndex);
            io_refNumberOfDigitsOfIndex = wstrIndex.length();
            sts = ns_consts::EnmReturnStatus::Success;
        }
        else
        {
            return  sts = ns_consts::EnmReturnStatus::ErrorFirstIndexNotFound;
        }
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        return sts;
    }


    // -------------------------------------------------------------------------- //
    /// <summary>
    ///  Synthesize the path of input data file of the specified index <c>indexOfInputDataFiles</c>.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="io_refPathForIndex">
    ///  [Output] specifies the reference to the path of input data file of the specified index <c>indexOfInputDataFiles</c>
    /// </param>
    /// <param name="io_refNumberOfDigitsOfIndex">
    ///  [Input] specifies the index of file to be synthesized.
    /// </param>
    /// <param name="i_refInitialFilePath">
    ///  [Input] specifies the file path of initial file.
    /// </param>
    /// <returns>
    ///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorNotFound</c>:  the file referenced by <c>i_refInitialFilePath</c> is not found.
    ///  <c>ais_31_lib::constants::EnmReturnStatus::ErrorFirstIndexNotFound</c>:  an appropriate offset cannot be found either from basefilename or extesion:
    ///  <c>ais_31_lib::constants::EnmReturnStatus::Success</c>:  otherwise.
    /// </returns>
    /// <precondition>
    /// </precondition>
    /// <postcondition>
    /// </postcondition>
    // -------------------------------------------------------------------------- //
    ns_consts::EnmReturnStatus synthesizeFilename(bs_fs::path& io_refPathForIndex,
        unsigned long indexOfInputDataFiles,
        const bs_fs::path& i_refInitialFilePath)
    {
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        std::wregex e1(L"([0-9]{3,})$", std::regex::extended);

        boost::system::error_code error;
        const bool result = bs_fs::exists(i_refInitialFilePath, error);
        if (!result || error) {
            return  sts = ns_consts::EnmReturnStatus::ErrorNotFound;
        }
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        std::wstring    wstrBaseFilename = i_refInitialFilePath.stem().c_str();
        std::wstring    wstrExtension = i_refInitialFilePath.extension().c_str();
        std::wsmatch  whatBase;
        std::wsmatch  whatExt;
        bool    bBase = std::regex_search(wstrBaseFilename.cbegin(), wstrBaseFilename.cend(), whatBase, e1);
        bool    bExt = std::regex_search(wstrExtension.cbegin(), wstrExtension.cend(), whatExt, e1);

        std::wstringstream  ssFilename = std::wstringstream();
        std::wstringstream  ssIndex = std::wstringstream();
        unsigned long       initialIndex = 0;
        unsigned long       newIndex;
        size_t              digits = 0;
        std::wstring        fmt;

        if ((true == bBase) && (false == bExt))
        {
            std::wstring    wstrIndex = std::wstring(whatBase[1].first, whatBase[1].second);
            initialIndex = std::stoul(wstrIndex);
            newIndex = initialIndex + indexOfInputDataFiles;
            digits = wstrIndex.length();
            ssIndex << std::setfill(L'0') << std::right << std::setw(digits) << newIndex;
            fmt = ssIndex.str();
            ssFilename << std::regex_replace(wstrBaseFilename, e1, fmt);
            ssFilename << wstrExtension;
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            io_refPathForIndex = i_refInitialFilePath.parent_path();
            io_refPathForIndex /= ssFilename.str();
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            sts = ns_consts::EnmReturnStatus::Success;
        }
        else if (true == bExt)
        {
            std::wstring    wstrIndex = std::wstring(whatExt[1].first, whatExt[1].second);
            initialIndex = std::stoul(wstrIndex);
            newIndex = initialIndex + indexOfInputDataFiles;
            digits = wstrIndex.length();
            if ((double)digits < log10((double)newIndex))
            {
                ++digits;
            }
            ssIndex << std::setfill(L'0') << std::right << std::setw(digits) << newIndex;
            fmt = ssIndex.str();
            ssFilename << wstrBaseFilename;
            ssFilename << std::regex_replace(wstrExtension, e1, fmt);
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            io_refPathForIndex = i_refInitialFilePath.parent_path();
            io_refPathForIndex /= ssFilename.str();
            // -------------------------------------------------------------------------- //
            // 
            // -------------------------------------------------------------------------- //
            sts = ns_consts::EnmReturnStatus::Success;
        }
        else
        {
            return  sts = ns_consts::EnmReturnStatus::ErrorNotFound;
        }
        // -------------------------------------------------------------------------- //
        //
        // -------------------------------------------------------------------------- //
        return sts;
    }
}