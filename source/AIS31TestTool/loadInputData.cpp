////////////////////////////////////////////////////////////////////////////////
// loadInputData.cpp
//
//
//
// Copyright (c) 2024 G. G. SAKURAI <g.garland823@gmail.com>
//
////////////////////////////////////////////////////////////////////////////////
#include "loadInputData.h"
#include "synthesizeFilename.h"
#include <fstream>

namespace ais_31_tool
{
	// -------------------------------------------------------------------------- //
	/// <summary>
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <param name="io_refData">
	/// </param>
	/// <param name="i_refInfoReport">
	/// </param>
	/// <param name="i_refFullPath">
	/// </param>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus loadSamples(ns_dt::t_data_for_v3& io_refData,
		const IDInfoForReport& i_refInfoReport,
		const bs_fs::path& i_refFullPath)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		const unsigned int	cui_number_of_bits_lowerbound = 2040000;
		const unsigned int	cui_number_of_bits_upperbound = 4080000;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (io_refData.p_bzUnprocessedData == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT1 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT2 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT3 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT4 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		boost::uintmax_t size = bs_fs::file_size(i_refFullPath);
		boost::uintmax_t size_to_read = size;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (cui_number_of_bits_upperbound <= size * io_refData.bits_per_sample)
		{
			if (1 == io_refData.bits_per_sample)
			{
				size_to_read = cui_number_of_bits_upperbound;
			}
			else if (1 < io_refData.bits_per_sample)
			{
				size_to_read = (cui_number_of_bits_upperbound + io_refData.bits_per_sample - 1) / io_refData.bits_per_sample;
			}
		}
		else if (cui_number_of_bits_lowerbound <= size * io_refData.bits_per_sample) {
			if (1 == io_refData.bits_per_sample)
			{
				size_to_read = size;
			}
			else if (1 < io_refData.bits_per_sample)
			{
				size_to_read = (size + io_refData.bits_per_sample - 1) / io_refData.bits_per_sample;
			}
		}
		else {
			return	sts = ns_consts::EnmReturnStatus::ErrorInsufficientData;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		blitz::Array<ns_dt::octet, 1>	bz_original(size_to_read);
		bz_original = 0;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		std::ifstream	file(i_refFullPath.wstring(), std::ios::in | std::ios::binary);
		if (!file)
		{
			return sts = ns_consts::EnmReturnStatus::ErrorFileIO;
		}
		file.read((char*)bz_original.data(), size_to_read);
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		io_refData.p_bzUnprocessedData->resize(size_to_read * (io_refData.bits_per_sample));
		*(io_refData.p_bzUnprocessedData) = 0;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (1 == io_refData.bits_per_sample)
		{
			memcpy(io_refData.p_bzUnprocessedData->data(), bz_original.data(), size_to_read);
		}
		else
		{
			// -------------------------------------------------------------------------- //
			/// fill <c>io_refData.p_bzUnprocessedData</c> by converting <c>io_refData.bits_per_sample</c>-bit vectors to an array of bit
			// -------------------------------------------------------------------------- //
			if (io_refData.bIsMSbFirstByteBitConversion == true)
			{
				// -------------------------------------------------------------------------- //
				// MSb first
				// -------------------------------------------------------------------------- //
				for (uintmax_t i = 0; i < size_to_read; ++i)
				{
					for (unsigned int j = 0; j < io_refData.bits_per_sample; ++j)
					{
						// -------------------------------------------------------------------------- //
						// assuming MSb first
						// -------------------------------------------------------------------------- //
						const int shift_width = (static_cast<int>(io_refData.bits_per_sample) - 1) - static_cast<int>(j);
						if (shift_width < 0)
						{
							return	sts;
						}
						// -------------------------------------------------------------------------- //
						/// here, <c>shift_witdth</c> is greater than or equal to 0
						// -------------------------------------------------------------------------- //
						(*(io_refData.p_bzUnprocessedData))(io_refData.bits_per_sample * i + j) = (bz_original(i) >> shift_width) & 0x01;
					}
				}
			}
			else
			{
				// -------------------------------------------------------------------------- //
				// LSb first
				// -------------------------------------------------------------------------- //
				for (uintmax_t i = 0; i < size_to_read; ++i)
				{
					for (unsigned int j = 0; j < io_refData.bits_per_sample; ++j)
					{
						// -------------------------------------------------------------------------- //
						// assuming LSb first
						// -------------------------------------------------------------------------- //
						const unsigned int shift_width = j;
						// -------------------------------------------------------------------------- //
						/// here, <c>shift_witdth</c> is greater than or equal to 0
						// -------------------------------------------------------------------------- //
						(*(io_refData.p_bzUnprocessedData))(io_refData.bits_per_sample * i + j) = (bz_original(i) >> shift_width) & 0x01;
					}
				}
			}
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		bz_original.resize(0);
		io_refData.L = size_to_read * io_refData.bits_per_sample;
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
	/// <param name="io_refData">
	/// </param>
	/// <param name="i_refInfoReport">
	/// </param>
	/// <param name="i_enmTrack">
	/// </param>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus loadSamplesForTest(ns_dt::t_data_for_v3& io_refData,
		const IDInfoForReport& i_refInfoReport,
		ns_consts::EnmAIS20AIS31V3Track i_enmTrack)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		const unsigned int	cui_number_of_bits_lowerbound = 2040000;
		const unsigned int	cui_number_of_bits_upperbound = 4080000;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (io_refData.p_bzUnprocessedData == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT1 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT2 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT3 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInputDataT4 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		uintmax_t	ui_requied_number_of_bits_for_test = 20000;
		blitz::Array<ns_dt::octet, 1>** dpInputData = nullptr;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		switch (i_enmTrack)
		{
		case ns_consts::EnmAIS20AIS31V3Track::TestT1:
			ui_requied_number_of_bits_for_test = 20000;
			dpInputData = &(io_refData.p_bzInputDataT1);
			break;
		case ns_consts::EnmAIS20AIS31V3Track::TestT2:
			ui_requied_number_of_bits_for_test = 20000;
			dpInputData = &(io_refData.p_bzInputDataT2);
			break;
		case ns_consts::EnmAIS20AIS31V3Track::TestT3:
			ui_requied_number_of_bits_for_test = 1000000;
			dpInputData = &(io_refData.p_bzInputDataT3);
			break;
		case ns_consts::EnmAIS20AIS31V3Track::TestT4:
			ui_requied_number_of_bits_for_test = 1000000;
			dpInputData = &(io_refData.p_bzInputDataT4);
			break;
		default:
			break;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (io_refData.p_bzUnprocessedData->size() < ui_requied_number_of_bits_for_test) {
			return	sts = ns_consts::EnmReturnStatus::ErrorInsufficientData;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		memcpy((*dpInputData)->data(), io_refData.p_bzUnprocessedData->data(), ui_requied_number_of_bits_for_test);
		// -------------------------------------------------------------------------- //
		// copy unprocessed data to temporary variable
		// -------------------------------------------------------------------------- //
		uintmax_t	ui_size_remaining = io_refData.p_bzUnprocessedData->size() - ui_requied_number_of_bits_for_test;
		blitz::Array<ns_dt::octet, 1>	bz_remaining(ui_size_remaining);
		memcpy(bz_remaining.data(), io_refData.p_bzUnprocessedData->data() + ui_requied_number_of_bits_for_test, ui_size_remaining);
		// -------------------------------------------------------------------------- //
		// set unprocessed data
		// -------------------------------------------------------------------------- //
		io_refData.p_bzUnprocessedData->resize((int)ui_size_remaining);
		memcpy(io_refData.p_bzUnprocessedData->data(), bz_remaining.data(), ui_size_remaining);
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		bz_remaining = 0;
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		bz_remaining.resize(0);
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
	/// <param name="io_refData">
	/// </param>
	/// <param name="indexWithZeroOffset">
	/// </param>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus performProjection(ns_dt::t_data_for_v3& io_refData, int indexWithZeroOffset)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (io_refData.p_bzInputDataT1 == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		if (io_refData.p_bzInterpretedBj == nullptr)
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if ((io_refData.bits_per_sample < 1) || (8 < io_refData.bits_per_sample))
		{
			return	sts = ns_consts::EnmReturnStatus::ErrorDomain;
		}
		const boost::uintmax_t size = io_refData.p_bzInputDataT1->length(blitz::firstDim);
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (1 == io_refData.bits_per_sample)
		{
			io_refData.p_bzInterpretedBj->resize(io_refData.p_bzInputDataT1->length(blitz::firstDim));
			for (int j = 0; j < io_refData.p_bzInputDataT1->length(blitz::firstDim); ++j)
			{
				(*io_refData.p_bzInterpretedBj)(j) = (*io_refData.p_bzInputDataT1)(indexWithZeroOffset, j);
			}
		}
		else
		{
			constexpr	uintmax_t number_of_bits_to_be_loaded = 20000;

			// -------------------------------------------------------------------------- //
			// 1 < io_refData.bits_per_sample
			// -------------------------------------------------------------------------- //
			uintmax_t size_to_read = (number_of_bits_to_be_loaded + io_refData.bits_per_sample - 1) / io_refData.bits_per_sample;
			if (size < size_to_read)
			{
				// -------------------------------------------------------------------------- //
				// warning, i.e. all bits in the bitstring is tested
				// -------------------------------------------------------------------------- //
				size_to_read = size;
			}
			else
			{
				// -------------------------------------------------------------------------- //
				// truncate
				// -------------------------------------------------------------------------- //

			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			if (io_refData.bIsMSbFirstByteBitConversion == true)
			{
				// -------------------------------------------------------------------------- //
				// MSb first
				// -------------------------------------------------------------------------- //
				for (uintmax_t i = 0; i < size_to_read; ++i)
				{
					for (unsigned int j = 0; j < io_refData.bits_per_sample; ++j)
					{
						// -------------------------------------------------------------------------- //
						// assuming MSb first
						// -------------------------------------------------------------------------- //
						const int shift_width = (static_cast<int>(io_refData.bits_per_sample) - 1) - static_cast<int>(j);
						if (shift_width < 0)
						{
							return	sts;
						}
						// -------------------------------------------------------------------------- //
						/// here, <c>shift_witdth</c> is greater than or equal to 0
						// -------------------------------------------------------------------------- //
						(*io_refData.p_bzInterpretedBj)((int)(io_refData.bits_per_sample * i + j)) = ((*io_refData.p_bzInputDataT1)(indexWithZeroOffset, (int)i) >> shift_width) & 0x01;
					}
				}
			}
			else
			{
				// -------------------------------------------------------------------------- //
				// LSb first
				// -------------------------------------------------------------------------- //
				for (uintmax_t i = 0; i < size_to_read; ++i)
				{
					for (unsigned int j = 0; j < io_refData.bits_per_sample; ++j)
					{
						// -------------------------------------------------------------------------- //
						// assuming LSb first
						// -------------------------------------------------------------------------- //
						const unsigned int shift_width = j;
						// -------------------------------------------------------------------------- //
						/// here, <c>shift_witdth</c> is greater than or equal to 0
						// -------------------------------------------------------------------------- //
						(*io_refData.p_bzInterpretedBj)((int)(io_refData.bits_per_sample * i + j)) = ((*io_refData.p_bzInputDataT1)(indexWithZeroOffset, (int)i) >> shift_width) & 0x01;
					}
				}
			}
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		return sts = ns_consts::EnmReturnStatus::Success;
	}

}