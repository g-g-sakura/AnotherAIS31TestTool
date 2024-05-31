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
	/// <params="io_refData">
	/// </params>
	/// <params="i_refFullPath">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus loadSamples(ns_dt::t_data_for_v2& io_refData,
		const IDInfoForReport& i_refInfoReport,
		const bs_fs::path& i_refFullPath,
		ns_consts::EnmAIS20AIS31V2Track i_enmTrack)
	{
		ns_consts::EnmReturnStatus	sts = ns_consts::EnmReturnStatus::ErrorUnexpected;

		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		switch (i_enmTrack)
		{
		case ns_consts::EnmAIS20AIS31V2Track::TestT0:
			if (io_refData.p_bzInputDataT0 == nullptr)
			{
				return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
			}
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT1:
		case ns_consts::EnmAIS20AIS31V2Track::TestT2:
		case ns_consts::EnmAIS20AIS31V2Track::TestT3:
		case ns_consts::EnmAIS20AIS31V2Track::TestT4:
		case ns_consts::EnmAIS20AIS31V2Track::TestT5:
			if (io_refData.p_bzInputDataT1 == nullptr)
			{
				return	sts = ns_consts::EnmReturnStatus::ErrorNullPointer;
			}
			break;
		default:
			break;
		}
		boost::uintmax_t size = bs_fs::file_size(i_refFullPath);
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		switch (i_enmTrack)
		{
		case ns_consts::EnmAIS20AIS31V2Track::TestT0:
			io_refData.p_bzInputDataT0->resize(size);
			(*io_refData.p_bzInputDataT0) = 0;
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT1:
		case ns_consts::EnmAIS20AIS31V2Track::TestT2:
		case ns_consts::EnmAIS20AIS31V2Track::TestT3:
		case ns_consts::EnmAIS20AIS31V2Track::TestT4:
		case ns_consts::EnmAIS20AIS31V2Track::TestT5:
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			if (20000 < size * io_refData.bits_per_sample)
			{
				if (1 == io_refData.bits_per_sample)
				{
					size = 20000;
				}
				else if (1 < io_refData.bits_per_sample)
				{
					size = (20000 + io_refData.bits_per_sample - 1) / io_refData.bits_per_sample;
				}
			}
			// -------------------------------------------------------------------------- //
			//
			// -------------------------------------------------------------------------- //
			io_refData.p_bzInputDataT1->resize(257, size);
			(*io_refData.p_bzInputDataT1) = 0;
			break;
		default:
			break;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		std::ifstream	file(i_refFullPath.wstring(), std::ios::in | std::ios::binary);
		if (!file)
		{
			return sts = ns_consts::EnmReturnStatus::ErrorFileIO;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		switch (i_enmTrack)
		{
		case ns_consts::EnmAIS20AIS31V2Track::TestT0:
			file.read((char*)io_refData.p_bzInputDataT0->data(), size);
			io_refData.p_bzInputDataT0->resizeAndPreserve(size);
			break;
		case ns_consts::EnmAIS20AIS31V2Track::TestT1:
		case ns_consts::EnmAIS20AIS31V2Track::TestT2:
		case ns_consts::EnmAIS20AIS31V2Track::TestT3:
		case ns_consts::EnmAIS20AIS31V2Track::TestT4:
		case ns_consts::EnmAIS20AIS31V2Track::TestT5:
		{
			int i = 0;
			bs_fs::path	path_next_index = bs_fs::path(i_refFullPath);
			int	next_index = 0;
			ns_consts::EnmReturnStatus	stsSynth = ns_consts::EnmReturnStatus::Success;
			do
			{
				blitz::Array<ns_dt::octet, 2> bz_slice = (*io_refData.p_bzInputDataT1)(blitz::Range(i, i), blitz::Range::all());
				file.read((char*)bz_slice.data(), size);
				file.close();
				//io_refData.p_bzInputDataT1->resizeAndPreserve(257, size);
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				next_index = 1 + i;
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				if (i < 256)
				{
					stsSynth = synthesizeFilename(path_next_index, next_index, i_refFullPath);
					if (ns_consts::EnmReturnStatus::Success != stsSynth)
					{
						sts = stsSynth;
						std::cout << "# [ERROR]: Failed to synthesize the filename for " << next_index << "-th input data in 257 sets.\n";
						return sts;
					}
					// -------------------------------------------------------------------------- //
					//
					// -------------------------------------------------------------------------- //
					file.open(path_next_index.wstring(), std::ios::in | std::ios::binary);
					if (!file)
					{
						sts = stsSynth = ns_consts::EnmReturnStatus::ErrorFileIO;
						std::wcout << L"# [ERROR]: Failed to open the file: " << path_next_index.wstring() << L".\n";
						return sts;
					}
					// -------------------------------------------------------------------------- //
					//
					// -------------------------------------------------------------------------- //
					size = bs_fs::file_size(path_next_index);
					if (20000 < size * io_refData.bits_per_sample)
					{
						if (1 == io_refData.bits_per_sample)
						{
							size = 20000;
						}
						else if (1 < io_refData.bits_per_sample)
						{
							size = (20000 + io_refData.bits_per_sample - 1) / io_refData.bits_per_sample;
						}
					}
					// -------------------------------------------------------------------------- //
					//
					// -------------------------------------------------------------------------- //
					i_refInfoReport.info_source.p_info_input_data_items_testT1->emplace_back(InfoInputDataItem{ nullptr, 0 });
					i_refInfoReport.info_source.p_info_input_data_items_testT1->at(i + 1).p_path_to_input_data = new bs_fs::path(path_next_index);
					i_refInfoReport.info_source.p_info_input_data_items_testT1->at(i + 1).tm_last_write_time = bs_fs::last_write_time(path_next_index);
				}
				// -------------------------------------------------------------------------- //
				//
				// -------------------------------------------------------------------------- //
				++i;
			} while ((ns_consts::EnmReturnStatus::Success == stsSynth) && (i < 257));
		}
		break;
		default:
			break;
		}
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		io_refData.L = size;
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
	/// <params="io_refData">
	/// </params>
	/// <returns>
	/// </returns>
	/// <precondition>
	/// </precondition>
	/// <postcondition>
	/// </postcondition>
	// -------------------------------------------------------------------------- //
	ns_consts::EnmReturnStatus performProjection(ns_dt::t_data_for_v2& io_refData, int indexWithZeroOffset)
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
		const boost::uintmax_t size = io_refData.p_bzInputDataT1->length(blitz::secondDim);
		// -------------------------------------------------------------------------- //
		//
		// -------------------------------------------------------------------------- //
		if (1 == io_refData.bits_per_sample)
		{
			io_refData.p_bzInterpretedBj->resize(io_refData.p_bzInputDataT1->length(blitz::secondDim));
			for (int j = 0; j < io_refData.p_bzInputDataT1->length(blitz::secondDim); ++j)
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