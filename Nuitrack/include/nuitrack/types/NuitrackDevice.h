#ifndef NUITRACK_NUITRAKDEVICE_H_
#define NUITRACK_NUITRAKDEVICE_H_
#include <vector>

#include "nuitrack/capi/NuitrackDevice_CAPI.h"
#include "nuitrack/utils/ExceptionTranslator.h"

namespace tdv
{
namespace nuitrack
{
namespace device
{

/**
 * @ingroup CommonElements_group
 * @brief Contains information and settings for a device.
 */
class NuitrackDevice
{
public:
	typedef std::shared_ptr<NuitrackDevice> Ptr;

	/**
	 * @brief For internal use only.
	 */
	NuitrackDevice(NuitrackDeviceData* pimpl)
	{
		_pimpl = pimpl;
	}

	~NuitrackDevice()
	{
		nuitrack_deleteNuitrackDeviceImpl(_pimpl);
	}

	/**
	 * @brief Provides device info by type.
	 *
	 * @param [in] info_type Type of device info.
	 * @return Info about a device.
	 */
	std::string getInfo(DeviceInfoType info_type)
	{
		int string_buffer_size = 0;
		nuitrack_nuitrackDevice_getStringBufferSizeConst(string_buffer_size);
		std::string result;
		result.resize(string_buffer_size);

		nuitrack_nuitrackDevice_getInfo(_pimpl, info_type, (char *)result.c_str());
		result.resize(strlen(result.c_str()));

		return result;
	}

	/**
	 * @brief Provides all available video modes for a current StreamType.
	 *
	 * @param [in] stream_type Stream type of VideoMode.
	 * @return Vector of available video modes.
	 */
	std::vector<VideoMode> getAvailableVideoModes(StreamType stream_type)
	{
		std::vector<VideoMode> res;

		int buf_size = 0;
		nuitrack_nuitrackDevice_getVideoModeListSize(_pimpl, stream_type, buf_size);

		for(int i = 0; i < buf_size; i++)
		{
			VideoMode tmp;
			nuitrack_nuitrackDevice_getVideoModeList(_pimpl, stream_type, i, tmp);
			res.push_back(tmp);
		}

		return res;
	}

	/**
	 * @brief Provides selected video mode for a current StreamType.
	 *
	 * @param [in] stream_type Stream type of VideoMode.
	 * @return Selected VideoMode.
	 */
	VideoMode getSelectedVideoMode(StreamType stream_type)
	{
		VideoMode tmp;
		nuitrack_nuitrackDevice_getSelectedVideoMode(_pimpl, stream_type, tmp);
		return tmp;
	}

	/**
	 * @brief Sets video mode for a current StreamType.
	 *
	 * @param [in] stream_type Stream type of VideoMode.
	 * @param [in] video_mode Video mode.
	 */
	void setVideoMode(StreamType stream_type, VideoMode video_mode)
	{
		nuitrack_nuitrackDevice_setVideoMode(_pimpl, stream_type, video_mode);
	}

	/**
	 * @brief Get license activation status.
	 *
	 * @return License activation status.
	 */
	ActivationStatus getActivationStatus()
	{
		int res = ActivationStatus::NONE;
		nuitrack_nuitrackDevice_getActivationStatus(_pimpl, res);
		return (ActivationStatus)res;
	}

	/**
	 * @brief Activate the current device.
	 *
	 * @param [in] activation_key License key for Nuitrack.
	 * @throw tdv::nuitrack::Exception
	 */
	void activate(std::string activation_key)
	{
		nuitrack_error* e = nullptr;
		nuitrack_nuitrackDevice_activate(_pimpl, activation_key.c_str(), &e);
		tdv::nuitrack::ExceptionTranslator::handle(e);
	}

private:
	friend class tdv::nuitrack::Nuitrack;

	NuitrackDeviceData* _pimpl;
};

}
}
}

#endif /* NUITRACK_USERFRAME_H_ */
