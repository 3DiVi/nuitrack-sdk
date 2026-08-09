#pragma once

#include <cstring>
#include <functional>
#include <memory>
#include <string>

// Nuitrack C API symbols
#include <nuitrack/capi/Nuitrack_CAPI.h>

// Nuitrack Native C++ API
#include <nuitrack/cpp/Nuitrack.h>

#include "CallbackStruct.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/NuitrackModule.h"


namespace tdv { namespace nuitrack {

using device::VideoMode;
using device::StreamType;
using device::ActivationStatus;


class NuitrackPIMPL;

template<typename TFramePIMPL, typename TFrameType>
class FramePIMPL : public TFrameType
{
public:
    uint64_t        getID()                                const override { return nuitrack_GetFrameID(_pimpl); }
    uint64_t        getTimestamp()                         const override { return nuitrack_GetFrameTimestamp(_pimpl); }
    int             getRows()                              const override { return nuitrack_GetFrameRows(_pimpl); }
    int             getCols()                              const override { return nuitrack_GetFrameCols(_pimpl); }

    Frame::Ptr updateSize(Size newSize) const override
    {
        auto* data = nuitrack_UpdateFrameSize(_pimpl, newSize);
        return std::make_shared<TFramePIMPL>(data);
    }

protected:
    FrameHolder* _pimpl;
};

/**
* @brief Stores a frame depth map.
* @ingroup DepthSensor_group
*/
class DepthFramePIMPL : public FramePIMPL<DepthFramePIMPL, DepthFrame>
{
public:
    explicit DepthFramePIMPL(FrameHolder* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddDepthSensorDataRef(pimpl);
    }

    const DataType* getData() const override { return nuitrack_GetDepthFrameData(_pimpl); }
    void writePointCloudTextureRGBA(float* outBuf, size_t size, PointCloud::Format format) const override { nuitrack_WriteDepthFramePointCloudTextureRGBA(_pimpl, outBuf, size, format); }
    ~DepthFramePIMPL() override { nuitrack_DestroyDepthSensorData(_pimpl); }
};


/**
* @brief Stores a frame color map.
* @ingroup ColorSensor_group
*/
class RGBFramePIMPL : public FramePIMPL<RGBFramePIMPL, RGBFrame>
{
public:
    /** @warning For internal use only. */
    explicit RGBFramePIMPL(FrameHolder* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddColorSensorDataRef(pimpl);
    }

    const DataType* getData() const override { return nuitrack_GetColorFrameData(_pimpl); }
    void writeTextureBGRA(uint8_t* outBuf, size_t size) const override { nuitrack_WriteColorFrameTextureBGRA(_pimpl, outBuf, size); }
    ~RGBFramePIMPL() override { nuitrack_DestroyColorSensorData(_pimpl); }
};


/**
 * @ingroup CommonElements_group
 * @brief Stores results of issue detection.
 */
class IssuesDataPIMPL
{
public:
    using Ptr = std::shared_ptr<IssuesDataPIMPL>;

    /** @warning For internal use only. */
    explicit IssuesDataPIMPL(IssueTrackerData* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddIssueTrackerDataRef(pimpl);
    }
    virtual ~IssuesDataPIMPL() { nuitrack_DestroyIssueTrackerData(_pimpl); }

    /**
     * @brief Returns information about sensor related issue detected.
     * @tparam T A data type that stores information about the requested issue.
     */
    template<typename T> std::shared_ptr<T> NUITRACK_LOCAL getIssue() const
    {
        if (T::getType() == "SensorIssue")
        {
            std::string buffer;
            buffer.resize(50);
            if (nuitrack_GetSensorIssue(_pimpl, (char *) buffer.c_str(), buffer.size()))
            {
                buffer.resize(strlen(buffer.c_str()));
                return std::make_shared<SensorIssue>(IssueId::SENSOR_ISSUE, buffer);
            }
        }
        return nullptr;
    }

    /**
     * @brief Returns information about user related issue detected.
     * @tparam T A data type that stores information about the requested issue.
     * @param userId ID of the user of interest.
     */
    template<typename T> std::shared_ptr<T> NUITRACK_LOCAL getUserIssue(int userId) const
    {
        if (T::getType() == "OcclusionIssue")
            if (nuitrack_GetOcclusionIssue(_pimpl, userId))
                return std::dynamic_pointer_cast<T>(std::make_shared<OcclusionIssue>());

        if (T::getType() == "FrameBorderIssue")
        {
            bool left = false, right = false, top = false;
            nuitrack_GetFrameBorderIssue(_pimpl, userId, &left, &right, &top);
            if (left || right || top)
                return std::dynamic_pointer_cast<T>(std::make_shared<FrameBorderIssue>(left, right, top));
        }
        return {};
    }

protected:
    IssueTrackerData* _pimpl;
};


inline void ExceptionHandle(nuitrack_error* e)
{
    if (e == nullptr) return;

    auto errorCode = nuitrack_GetErrorType(e);
    std::string msg = nuitrack_GetErrorMessage(e);
    nuitrack_DestroyError(e);

    ExceptionTranslator::generateExceptionByErrorCode(errorCode, msg);
}


class NuitrackDevicePIMPL
{
public:
    using Ptr = std::shared_ptr<NuitrackDevicePIMPL>;

    explicit NuitrackDevicePIMPL(NuitrackDeviceHolder* pimpl) { _pimpl = pimpl; }
    ~NuitrackDevicePIMPL() { nuitrack_deleteNuitrackDeviceImpl(_pimpl); }

    /**
     * @brief  Provides device info by type.
     * @param  [in] info_type Type of device info.
     * @return Info about a device.
     */
    std::string getInfo(device::DeviceInfoType info_type)
    {
        int string_buffer_size = 0;
        nuitrack_nuitrackDevice_getStringBufferSizeConst(string_buffer_size);
        std::string result;
        result.resize(string_buffer_size);

        nuitrack_nuitrackDevice_getInfo(_pimpl, info_type, (char *) result.c_str());
        result.resize(strlen(result.c_str()));

        return result;
    }

    /**
     * @brief  Provides all available video modes for a current StreamType.
     * @param  [in] stream_type Stream type of VideoMode.
     * @return Vector of available video modes.
     */
    std::vector<VideoMode> getAvailableVideoModes(StreamType stream_type)
    {
        std::vector<VideoMode> res;

        int buf_size = 0;
        nuitrack_nuitrackDevice_getVideoModeListSize(_pimpl, stream_type, buf_size);

        for (int i = 0; i < buf_size; i++)
        {
            VideoMode mode{};
            nuitrack_nuitrackDevice_getVideoModeList(_pimpl, stream_type, i, mode);
            res.push_back(mode);
        }
        return res;
    }

    /**
     * @brief Provides selected video mode for a current StreamType.
     * @param [in] stream_type Stream type of VideoMode.
     * @return Selected VideoMode.
     */
    VideoMode getSelectedVideoMode(StreamType stream_type)
    {
        VideoMode mode{};
        nuitrack_nuitrackDevice_getSelectedVideoMode(_pimpl, stream_type, mode);
        return mode;
    }

    /**
     * @brief Sets video mode for a current StreamType.
     * @param [in] stream_type Stream type of VideoMode.
     * @param [in] video_mode Video mode.
     */
    void setVideoMode(StreamType stream_type, VideoMode video_mode)
    {
        nuitrack_nuitrackDevice_setVideoMode(_pimpl, stream_type, video_mode);
    }

    /**
     * @brief Get license activation status.
     * @return License activation status.
     */
    ActivationStatus getActivationStatus()
    {
        auto res = ActivationStatus::NONE;
        nuitrack_nuitrackDevice_getActivationStatus(_pimpl, res);
        return res;
    }

    /**
     * @brief Activate the current device.
     *
     * @param [in] activation_key License key for Nuitrack.
     * @throw tdv::nuitrack::Exception
     */
    void activate(const std::string& activation_key) const
    {
        nuitrack_error* e = nullptr;
        nuitrack_nuitrackDevice_activate(_pimpl, activation_key.c_str(), &e);
        ExceptionHandle(e);
    }

private:
    NuitrackDeviceHolder* _pimpl;
    friend class NuitrackPIMPL;
};


/**
 * @ingroup CommonElements_group
 * @brief Central class for common %Nuitrack operations.
 *
 * This class is an access point for common %Nuitrack operations.
 * This class does not require instance creation, all member functions are static.
 *
 * Some issues that may occur when using sensor (user occluded by objects / stays
 * close to sensor FOV borders) can be handled with the Nuitrack::OnIssueUpdate callback.
 * Use Nuitrack::connectOnIssuesUpdate to receive information about issues happening.
 *
 * Callbacks for updating data from %Nuitrack modules and the Nuitrack central class are
 * not automatically called. You should request new data with Nuitrack::update or
 * Nuitrack::waitUpdate methods.
 */
class NUITRACK_LOCAL NuitrackPIMPL
{
public:
    /**
     * @brief Initialize %Nuitrack.
     *
     * This should be called before using any other %Nuitrack API functions.
     *
     * @note For Android OS: config file is located in the folder with unpacked assets after the installation of Nuitrack.apk
     * @param config Config file for %Nuitrack initialization.
     * @warning <b>Do not</b> specify the <i>config</i> value as it's set <b>automatically</b>. Specify the path to <i>nuitrack.config</i> <b>only</b> if the default location of <i>nuitrack.config</i> (defined after the installation of %Nuitrack runtime) was changed.
     * @throw tdv::nuitrack::Exception
     */
    static void init(const std::string& config = "")
    {
        nuitrack_error* e = nullptr;
        nuitrack_InitializeFromConfig_E(config.c_str(), &e);
        ExceptionHandle(e);
    }

    /**
     * @brief Start processing the data provided by the sensor.
     *
     * The stages of data processing are determined
     * by the existing module objects. The data is processed asynchronously.
     *
     * @throw tdv::nuitrack::Exception
     */
    static void run() { ExceptionTranslator::generateExceptionByErrorCode(nuitrack_Run()); }

    /**
     * @brief Initiate %Nuitrack update.
     *
     * Request new data from all created %Nuitrack modules. All module callbacks will be called.
     * No data synchronization is performed.
     *
     * @note Non-blocking operation.
     * @throw tdv::nuitrack::Exception
     */
    static void update()
    {
        nuitrack_error* e = nullptr;
        nuitrack_Update(&e);
        ExceptionHandle(e);
    }

    /**
     * @brief Initiate %Nuitrack module data update.
     *
     * Request new data from %Nuitrack module. When data becomes available, corresponding callbacks
     * will be called for given module and all the modules, that are required for it.
     * The data sent to these callbacks will be synchronized, so callback calls will be consistent.
     * Callback call order is defined by module dependency chain: from independent to dependent.
     * The call order of callbacks belonging to a particular module is defined by internal organization
     * of this module.
     *
     * @note Non-blocking operation.
     * @param module %Nuitrack module's Ptr.
     * @throw tdv::nuitrack::Exception
     */
    template<typename T>
    static void update(const std::shared_ptr<T>& module)
    {
        nuitrack_error* e = nullptr;
        nuitrack_SyncUpdate(module.get()->_pimpl, &e);
        ExceptionHandle(e);
    }

    /**
     * @brief Initiate %Nuitrack module update and wait for it.
     *
     * Similar to Nuitrack::update(std::shared_ptr<Module> module), but waits until all the required callbacks are called.
     *
     * @note Blocking operation.
     * @param module %Nuitrack module's Ptr.
     * @throw tdv::nuitrack::Exception
     */
    template<typename T>
    static void waitUpdate(const std::shared_ptr<T>& module)
    {
        nuitrack_error* e = nullptr;
        nuitrack_WaitSyncUpdate(module.get()->_pimpl, &e);
        ExceptionHandle(e);
    }

    /**
     * @brief Stop data processing and destroy all existing %Nuitrack modules.
     *
     * @note To restart Nuitrack after release you should call Nuitrack::init and create all required modules again.
     * @throw tdv::nuitrack::Exception
     */

    using issues_cbs_type = CallbackStruct<IssuesDataPIMPL::Ptr>;

    static void release()
    {
        auto* callbackStruct  = (issues_cbs_type*)nuitrack_getIssuesCallbackStruct();
        if (callbackStruct != nullptr)
        {
            nuitrack_setIssuesCallbackStruct(nullptr);
            delete callbackStruct;
        }
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_Release());
    }

    /**
     * @brief Set the value of a %Nuitrack configuration parameter.
     *
     * @param key Parameter key
     * @param value Parameter value
     * @throw tdv::nuitrack::Exception
     */
    static void setConfigValue(const std::string& key, const std::string& value)
    {
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_SetConfigValue(key.c_str(), value.c_str()));
    }

    /**
     * @brief Get the value of a %Nuitrack configuration parameter.
     *
     * @param key Parameter key
     * @return Parameter value
     * @throw tdv::nuitrack::Exception
     */
    static std::string getConfigValue(const std::string& key)
    {
        std::string result;
        result.resize(5000);
        auto ec = nuitrack_GetConfigValue(key.c_str(), (char *) result.c_str(), (int)result.size());
        ExceptionTranslator::generateExceptionByErrorCode(ec);

        result.resize(strlen(result.c_str()));
        return result;
    }

    /**
     * @brief Get the JSON string of Nuitrack instance-based API.
     *
     * @return JSON string
     * @throw tdv::nuitrack::Exception
     */
    static std::string getInstancesJson()
    {
        nuitrack_error* e = nullptr;
        auto* resultPtr   = nuitrack_GetInstancesJsonDataAlloc(&e);
        std::string result(resultPtr);
        ExceptionHandle(e);
        nuitrack_GetInstancesJsonDataClear(resultPtr);

        return result;
    }

    /**
     * @brief Get the JSON string with internal Nuitrack parameters (for internal use only).
     * @return JSON string
     * @throw tdv::nuitrack::Exception
     */
    static std::string getInternalParamsJson()
    {
        nuitrack_error* e = nullptr;
        auto* resultPtr   = nuitrack_GetInternalParamsJsonAlloc(&e);
        std::string result(resultPtr);
        ExceptionHandle(e);
        nuitrack_GetInternalParamsJsonClear(resultPtr);

        return result;
    }

    /**
     * @brief Get the data type from the data stream
     * @tparam T A data type that supported by data stream (exist in DataStreamType enumeration)
     * @param id Sequential number of the created camera that the data corresponds to (use `0` also for data that is not linked to a specific camera)
     * @return A pointer to the data type or nullptr if data type not exist
     */
    template<class T> static std::shared_ptr<T> get(int id = 0) { return cpp::Nuitrack::get<T>(id); }

    /**
     * @brief Get Nuitrack version.
     * The version is calculated by the formula: major * 10000 + minor * 100 + revision
     *
     * @return An integer value of Nuitrack version.
     * @throw tdv::nuitrack::Exception
     */
    static int getVersion()
    {
        int version;
        auto e = nuitrack_GetVersion(&version);
        ExceptionTranslator::generateExceptionByErrorCode(e);

        return version;
    }

    /**
     * @brief Callback type of the issue update request.
     *
     * @see tdv::nuitrack::IssuesData
     * @see tdv::nuitrack::Issue
     * @see connectOnIssuesUpdate
     */
    using OnIssueUpdate = std::function<void (IssuesDataPIMPL::Ptr)>;

    /**
     * @brief Add a callback for the issue update request.
     *
     * @param [in] callback Callback to be invoked at the issue update request.
     * @return Registered callback ID. You can use it to remove the callback.
     * @see disconnectOnIssuesUpdate
     */
    static uint64_t connectOnIssuesUpdate(const OnIssueUpdate& callback)
    {
        IssueTracker* issueTracker = nullptr;
        nuitrack_getIssueTracker(&issueTracker);
        if (issueTracker == nullptr) return 0;

        if (nuitrack_getIssuesCallbackStruct() == nullptr)
        {
            auto* ptr = new issues_cbs_type();
            nuitrack_setIssuesCallbackStruct(ptr);

            auto* callbackWrapper = new IssueTrackerCallbackWrapper();
            callbackWrapper->setIssueTracker(issueTracker);
            callbackWrapper->setFunctionAddress(&onIssuesUpdateCallback);
            nuitrack_registerIssuesTrackerCallback(callbackWrapper);
        }

        // rework
        auto cbs = (issues_cbs_type*)(nuitrack_getIssuesCallbackStruct());
        return cbs->addCallback(callback);
    }

    /** @warning For internal use only. */
    static void onIssuesUpdateCallback(IssueTrackerData* data)
    {
        auto newData         = std::make_shared<IssuesDataPIMPL>(data);
        auto* callbackStruct = (issues_cbs_type*) nuitrack_getIssuesCallbackStruct();
        if (callbackStruct == nullptr) return;
        callbackStruct->executeAllCallbacks(newData);
    }

    /**
     * @brief Remove a callback of the issue update request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnIssuesUpdate
     */
    static void disconnectOnIssuesUpdate(uint64_t handler)
    {
        auto* callbackStruct = (issues_cbs_type*) nuitrack_getIssuesCallbackStruct();
        if (callbackStruct == nullptr) return;

        callbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Get a list of available devices.
     * @return List of available devices.
     * @throw tdv::nuitrack::Exception
     */
    static std::vector<NuitrackDevicePIMPL::Ptr> getDeviceList()
    {
        int device_limit = 0;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_nuitrackDevice_getDeviceListLimitConst(device_limit));
        std::vector<NuitrackDeviceHolder *> bufferOfDevices(device_limit);
        auto e = nuitrack_GetDeviceList(bufferOfDevices.data(), device_limit);
        ExceptionTranslator::generateExceptionByErrorCode(e);

        std::vector<NuitrackDevicePIMPL::Ptr> result;
        for (int i = 0; i < device_limit; i++)
        {
            if (bufferOfDevices[i] == nullptr) break;
            result.emplace_back(new NuitrackDevicePIMPL(bufferOfDevices[i]));
        }

        return result;
    }

    /**
     * @brief Setting a device to run.
     *
     * @param dev A configured device that you want to use.
     * @throw tdv::nuitrack::Exception
     */
    static void setDevice(const NuitrackDevicePIMPL::Ptr& dev)
    {
        auto ret = nuitrack_SetDevice(dev->_pimpl);
        ExceptionTranslator::generateExceptionByErrorCode(ret);
    }

    /**
     * @brief Get current device license.
     *
     * @return JSON string.
     * @throw tdv::nuitrack::Exception
     */
    static std::string getLicense()
    {
        std::string result;
        result.resize(5000);
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_GetLicense((char *) result.c_str(), result.size()));

        result.resize(std::strlen(result.c_str()));
        return result;
    }

    static bool runDumpSaving() { return nuitrack_runDumpSaving(); }
};

/**
 * @ingroup ColorSensor_group
 * @brief Represents the interface to the capabilities of the
 * @ref ColorSensor_group "Nuitrack Color Sensor" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor ColorSensor::create.
 * This instance is called %ColorSensor module object.
 * To receive the new color frames, add an ColorSensor::OnNewFrame callback
 * to the module object with ColorSensor::connectOnNewFrame method.
 */
class ColorSensorPIMPL : public cpp::ColorSensor
{
public:
    using Ptr      = std::shared_ptr<ColorSensorPIMPL>;
    using FramePtr = std::shared_ptr<RGBFrame>;

    /**
     * @brief The callback type of the new color frame request.
     * @see tdv::nuitrack::RGBFrame
     * @see connectOnNewFrame
     */
    using OnNewFrame = std::function<void (FramePtr)>;

    /**
     * @brief Create the ColorSensor module object.
     *
     * @return Smart pointer to a new ColorSensor instance.
     * @note Do not call this method twice. Instead, use the previously
     * received ColorSensor::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_CreateColorSensor(&pimpl));
        return std::make_shared<ColorSensorPIMPL>(pimpl);
    }

    /** @warning For internal use only. */
    explicit ColorSensorPIMPL(NuitrackModule* pimpl)
    {
        _pimpl = pimpl;

        _callbackStruct = new CallbackStruct<RGBFrame::Ptr>();
        _callbackWrapper.setColorSensor(this);
        _callbackWrapper.setFunctionAddress(&onNewFrameCallback);
        nuitrack_registerColorSensorCallback(_pimpl, &_callbackWrapper);
    }

    ~ColorSensorPIMPL() override
    {
        nuitrack_DestroyColorSensor(_pimpl);
        delete _callbackStruct;
    }

    CameraModel getOutputMode() const override
    {
        CameraModel mode{};
        nuitrack_GetColorSensorOutputMode(_pimpl, &mode);
        return mode;
    }

    /**
     * @brief Add a callback for the new color frame request.
     *
     * @param[in] callback Callback to be invoked at the new color frame request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnNewFrame
     */
    uint64_t connectOnNewFrame(const OnNewFrame& callback) override
    {
        return _callbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the new color frame request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnNewFrame
     */
    void disconnectOnNewFrame(uint64_t handler) override
    {
        _callbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Returns smart pointer to the last available RGBFrame.
     */
    FramePtr getColorFrame() override
    {
        auto* data = nuitrack_GetColorSensorData(_pimpl);
        return std::make_shared<RGBFramePIMPL>(data);
    }

private:
    static void onNewFrameCallback(FrameHolder* colorFrameImpl, ColorSensorPIMPL* sensor)
    {
        sensor->_callbackStruct->executeAllCallbacks(std::make_shared<RGBFramePIMPL>(colorFrameImpl));
    }

    NuitrackModule*                _pimpl;
    ColorSensorCallbackWrapper     _callbackWrapper;
    CallbackStruct<RGBFrame::Ptr>* _callbackStruct;

    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};


/**
 * @ingroup DepthSensor_group
 * @brief Represents the interface to the capabilities of the
 * @ref DepthSensor_group "Nuitrack Depth Sensor" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor DepthSensor::create.
 * This instance is called %DepthSensor module object.
 * To receive the new depth frames, add an DepthSensor::OnNewFrame callback
 * to the module object with DepthSensor::connectOnNewFrame method.
 * Use DepthSensor::convertProjToRealCoords
 * to convert coordinates from the projective system to the world and
 * DepthSensor::convertProjToRealCoords for reverse conversion.
 */
class DepthSensorPIMPL : public cpp::DepthSensor
{
public:
    /**
    * @brief Smart pointer to access the DepthSensor instance.
    * @see create
    */
    using Ptr = std::shared_ptr<DepthSensorPIMPL>;

    /**
     * @brief The callback type of the new depth frame request.
     * @see tdv::nuitrack::DepthFrame
     * @see connectOnNewFrame
     */
    using OnNewFrame = std::function<void (DepthFrame::Ptr)>;

    /**
     * @brief Create the DepthSensor module object.
     *
     * @return Smart pointer to a new DepthSensor instance.
     * @note Do not call this method twice. Instead, use the previously
     * received DepthSensor::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        auto exception_code   = nuitrack_CreateDepthSensor(&pimpl);
        char exception_message[1024];
        nuitrack_GetExceptionMessage(pimpl, exception_message, 1024);
        ExceptionTranslator::generateExceptionByErrorCode(exception_code, exception_message);
        return std::make_shared<DepthSensorPIMPL>(pimpl);
    }

    /** @warning For internal use only. */
    explicit DepthSensorPIMPL(NuitrackModule* pimpl)
    {
        _pimpl = pimpl;

        _callbackStruct = new CallbackStruct<DepthFrame::Ptr>();
        _callbackWrapper.setDepthSensor(this);
        _callbackWrapper.setFunctionAddress(&onNewFrameCallback);
        nuitrack_registerDepthSensorCallback(_pimpl, &_callbackWrapper);
    }

    ~DepthSensorPIMPL() override
    {
        nuitrack_DestroyDepthSensor(_pimpl);
        delete _callbackStruct;
    }

    /**
     * @brief Returns output mode of depth sensor.
     */
    CameraModel getOutputMode() const override
    {
        CameraModel mode{};
        nuitrack_GetDepthSensorOutputMode(_pimpl, &mode);
        return mode;
    }

    /**
     * @brief Returns true if mirror mode is enabled, false otherwise.
     * @see setMirror
     */
    bool isMirror() const override
    {
        return nuitrack_IsDepthSensorMirror(_pimpl);
    }

    /**
     * @brief Set mirror mode state.
     *
     * Call setMirror(true) to enable mirror mode.
     * Call setMirror(false) to disable mirror mode.
     *
     * If the mirror mode is on, the depth map from the sensor will be
     * reflected horizontally before consequent processing.
     *
     * @param[in] mirror Mirror mode state to be set.
     * @see isMirror
     */
    void setMirror(bool mirror) override
    {
        nuitrack_SetDepthSensorMirror(_pimpl, mirror);
    }

    /**
     * @brief Add a callback for the new depth frame request.
     *
     * @param[in] callback Callback to be invoked at the new depth frame request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnNewFrame
     */
    uint64_t connectOnNewFrame(const OnNewFrame& callback) override
    {
        return _callbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the new depth frame request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnNewFrame
     */
    void disconnectOnNewFrame(uint64_t handler) override
    {
        _callbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Returns smart pointer to the last available DepthFrame.
     */

    DepthFrame::Ptr getDepthFrame() override
    {
        auto data = nuitrack_GetDepthSensorData(_pimpl);
        return std::make_shared<DepthFramePIMPL>(data);
    }

    /**
     * @brief Convert projective coordinates to real world coordinates from Vector3 point.
     * @param[in] p Projective point coordinates.
     * @return Converted real world point.
     */
    Vector3 convertProjToRealCoords(const Vector3& p) const override
    {
        CVector3 c_vec{p.x, p.y, p.z};
        return {nuitrack_ctypes_ConvertProjToRealCoordsVector3(_pimpl, c_vec)};
    }

    /**
    * @brief Convert projective coordinates to real world coordinates from x, y and depth map.
    * @param[in] x,y Projective point coordinates.
    * @param[in] depth Depth map.
    * @return Converted real world point.
    */
    Vector3 convertProjToRealCoords(int x, int y, DepthFrame::DataType depth) const override { return {nuitrack_ctypes_ConvertProjToRealCoordsXYZ(_pimpl, x, y, depth)}; }

    /**
     * @brief Convert real world coordinates to projective coordinates from Vector3 point.
     * @param[in] p Real world point coordinates.
     * @return Converted projective point.
     */
    Vector3 convertRealToProjCoords(const Vector3& p) const override
    {
        CVector3 c_vec{p.x, p.y, p.z};
        return {nuitrack_ctypes_ConvertRealToProjCoordsVector3(_pimpl, c_vec)};
    }

    /**
    * @brief Convert real world coordinates to projective coordinates from x, y, z.
    * @param[in] x,y,z Real world point coordinates.
    * @return Converted projective point.
    */
    Vector3 convertRealToProjCoords(float x, float y, float z) const override
    {
        return {nuitrack_ctypes_ConvertRealToProjCoordsXYZ(_pimpl, x, y, z)};
    }

private:
    static void onNewFrameCallback(FrameHolder* depthFrameImpl, DepthSensorPIMPL* sensor)
    {
        auto frame = std::make_shared<DepthFramePIMPL>(depthFrameImpl);
        sensor->_callbackStruct->executeAllCallbacks(frame);
    }

    NuitrackModule* _pimpl;

    DepthSensorCallbackWrapper _callbackWrapper;

    CallbackStruct<DepthFrame::Ptr>* _callbackStruct;

    friend class NuitrackPIMPL;

    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};

/**
 * @ingroup UserTracker_group
 * @brief Represents a user map with information about the floor.
 *
 * Each UserFrame element stores the ID of a user to which corresponding frame pixel belongs.
 *
 * Additional information about detected users can be accessed trough UserFrame::getUsers.
 *
 * The floor is represented in the form of a plane: as the point and the normal vector.
 * This properties can be accessed via UserFrame::getFloor and
 * UserFrame::getFloorNormal respectively.
 */
class UserFramePIMPL : public FramePIMPL<UserFramePIMPL, UserFrame>
{
public:
    explicit UserFramePIMPL(FrameHolder* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddUserTrackerDataRef(pimpl);
    }

    ~UserFramePIMPL() override { nuitrack_DestroyUserTrackerData(_pimpl); }
    const DataType* getData() const override { return nuitrack_GetUserFrameData(_pimpl); }

    /**
     * @brief Returns additional information about detected users.
     *
     * @return Detected user properties in the form of array of the User structures.
     */
    std::vector<User> getUsers() const override
    {
        std::vector<User> usersVector;

        auto numUsers = nuitrack_GetUserFrameNumUsers(_pimpl);

        for (int i = 0; i < numUsers; i++)
        {
            User user;
            nuitrack_GetUserFrameUser(_pimpl, i, &user);
            usersVector.push_back(user);
        }

        return usersVector;
    }

    Vector3 getFloor() const override
    {
        Vector3 floor;
        nuitrack_GetUserFrameFloor(_pimpl, &floor);
        return floor;
    }

    Vector3 getFloorNormal() const override
    {
        Vector3 floorNormal;
        nuitrack_GetUserFrameFloorNormal(_pimpl, &floorNormal);
        return floorNormal;
    }
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of gesture estimation.
 */
class GestureDataPIMPL : public GestureData
{
public:
    /** @warning For internal use only. */
    explicit GestureDataPIMPL(GestureRecognizerData* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddGestureRecognizerDataRef(pimpl);
    }

    ~GestureDataPIMPL() override { nuitrack_DestroyGestureRecognizerData(_pimpl); }

    /**
     * @brief Returns the data timestamp in microseconds.
     *
     * The timestamp characterizes the time point to which the gesture
     * data corresponds.
     * @note The exact meaning of this value depends on the depth provider.
     */
    uint64_t getTimestamp() const override { return nuitrack_GetUserGesturesTimestamp(_pimpl); }

    /**
     * @brief Returns the number of gestures detected.
     */
    int getNumGestures() const override { return nuitrack_GetUserGesturesNumGestures(_pimpl); }

    /**
     * @brief Returns descriptions of detected gestures.
     * @return Gesture information in the form of array of the Gesture structures.
     */
    std::vector<Gesture> getGestures() const override
    {
        auto numUsers = nuitrack_GetUserGesturesNumGestures(_pimpl);

        std::vector<Gesture> gesturesVector;
        for (int i = 0; i < numUsers; i++)
        {
            Gesture g{};
            nuitrack_GetUserGesture(_pimpl, i, &g);
            gesturesVector.push_back(g);
        }

        return gesturesVector;
    }

private:
    GestureRecognizerData* _pimpl;
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of user state estimation.
 */
class UserStateDataPIMPL : public UserStateData
{
public:
    /** @warning For internal use only. */
    explicit UserStateDataPIMPL(UsersStateChanges* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddUsersStateChangesRef(pimpl);
    }

    ~UserStateDataPIMPL() override { nuitrack_DestroyUsersStateChanges(_pimpl); }

    /**
     * @brief Returns the number of user states detected.
     */
    int getNumUserStates() const override { return nuitrack_GetNumUsersStateChanges(_pimpl); }

    /**
     * @brief Returns the data timestamp in microseconds.
     *
     * The timestamp characterizes the time point to which the user state
     * data corresponds.
     * @note The exact meaning of this value depends on the depth provider.
     */
    uint64_t getTimestamp() const override { return nuitrack_GetUsersStateChangesTimestamp(_pimpl); }

    /**
     * @brief Returns descriptions of detected states of users.
     *
     * @return User state information in the form of array of the UserState structures.
     */
    std::vector<UserState> getUserStates() const override
    {
        std::vector<UserState> usersVector;

        auto numUsers = nuitrack_GetNumUsersStateChanges(_pimpl);

        for (int i = 0; i < numUsers; i++)
        {
            UserState g{};
            nuitrack_GetUserStateChange(_pimpl, i, &g);
            usersVector.push_back(g);
        }

        return usersVector;
    }

private:
    UsersStateChanges* _pimpl;
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of estimation of the state of gestures
 * for every tracked user.
 */
class UserGesturesStateDataPIMPL : public UserGesturesStateData
{
public:
    /** @warning For internal use only. */
    explicit UserGesturesStateDataPIMPL(GestureRecognizerUserGesturesStateData* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddUsersStateDataRef(pimpl);
    }

    ~UserGesturesStateDataPIMPL() override { nuitrack_DestroyUsersStateData(_pimpl); }

    /**
     * @brief Returns the number of tracked users.
     */
    int getNumUsers() const override { return nuitrack_GetNumUsersGestures(_pimpl); }

    /**
     * @brief Returns the data timestamp in microseconds.
     *
     * The timestamp characterizes the time point to which the gesture state
     * data corresponds.
     * @note The exact meaning of this value depends on the depth provider.
     */
    uint64_t getTimestamp() const override { return nuitrack_GetUsersGesturesStateTimestamp(_pimpl); }

    /**
     * @brief Returns information about the gestures of the tracked users.
     *
     * @return User gesture information in the form of array of the UserGesturesState structures.
     */
    std::vector<UserGesturesState> getUserGesturesStates() const override
    {
        std::vector<UserGesturesState> usersVector;

        GestureRecognizerUserGesturesStateData* dataHolder = _pimpl;

        int numUsers = nuitrack_GetNumUsersGestures(dataHolder);

        for (int i = 0; i < numUsers; i++)
        {
            UserGesturesState ugs;
            UserGesturesState ugsTemp;

            nuitrack_GetUserStateData(dataHolder, i, &ugsTemp);
            ugs.userId = ugsTemp.userId;
            ugs.state  = ugsTemp.state;

            int numGestures = nuitrack_GetNumUserGestureState(dataHolder, i);
            for (int j = 0; j < numGestures; j++)
            {
                GestureState gs{};
                nuitrack_GetUserGestureState(dataHolder, i, j, &gs);
                ugs.gestures.push_back(gs);
            }

            usersVector.push_back(ugs);
        }

        return usersVector;
    }

private:
    GestureRecognizerUserGesturesStateData* _pimpl;
};

/**
* @ingroup SkeletonTracker_group
* @brief Stores the data of all available skeletons at a certain point in time.
*/
class SkeletonDataPIMPL : public SkeletonData
{
public:
    explicit SkeletonDataPIMPL(SkeletonTrackerData* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddSkeletonTrackerDataRef(pimpl);
    }

    ~SkeletonDataPIMPL() override { nuitrack_DestroySkeletonTrackerData(_pimpl); }

    /**
     * @brief Get current number of skeletons.
     * @return Number of skeletons.
     */
    int getNumSkeletons() const override { return nuitrack_GetNumUsers(_pimpl); }

    /**
     * @brief Get current user skeletons.
     * @return Skeletons.
     */
    std::vector<Skeleton> getSkeletons() const override
    {
        std::vector<Skeleton> usersVector;

        const int maxJoints = 25;
        int numUsers  = nuitrack_GetNumUsers(_pimpl);

        for (int i = 0; i < numUsers; i++)
        {
            Skeleton skeleton;
            int id      = nuitrack_GetSkeletonID(_pimpl, i);
            skeleton.id = id;

            for (int j = 0; j < maxJoints; j++)
            {
                Joint joint;
                nuitrack_GetSkeletonJoint(_pimpl, i, (JointType) j, &joint);
                skeleton.joints.push_back(joint);
            }

            usersVector.push_back(skeleton);
        }

        return usersVector;
    }

    /**
     * @brief Returns the data timestamp in microseconds.
     * The timestamp characterizes the time point to which the skeleton
     * data corresponds.
     * @note The exact meaning of this value depends on the depth provider.
     */
    uint64_t getTimestamp() const override { return nuitrack_GetSkeletonTrackerTimestamp(_pimpl); }

private:
    SkeletonTrackerData* _pimpl;
};

/**
 * @ingroup HandTracker_group
 * @brief Stores hand tracking results related to a specific point in time.
 */
class HandTrackerDataPIMPL : public HandTrackerData
{
public:
    /** @warning For internal use only. */
    explicit HandTrackerDataPIMPL(HandTrackerDataInner* pimpl)
    {
        _pimpl = pimpl;
        nuitrack_AddHandTrackerDataRef(_pimpl);
    }

    ~HandTrackerDataPIMPL() override { nuitrack_DestroyHandTrackerData(_pimpl); }

    /**
     * @brief Returns the data timestamp in microseconds.
     *
     * The timestamp characterizes the time point to which the hand
     * tracking data corresponds.
     * @note The exact meaning of this value depends on the depth provider.
     */
    uint64_t getTimestamp() const override { return nuitrack_GetHandTrackerDataTimestamp(_pimpl); }

    /**
     * @brief Returns the number of users handled by the hand tracker.
     */
    int getNumUsers() const override { return nuitrack_HandTrackerGetNumUsers(_pimpl); }

    /**
     * @brief Returns information about the hands of the tracked users.
     * @return User hand information in the form of array of the UserHands structures.
     */
    std::vector<UserHands> getUsersHands() const override
    {
        int numUsers = nuitrack_HandTrackerGetNumUsers(_pimpl);

        int userId = 0;
        std::vector<UserHands> userHands;
        for (int i = 0; i < numUsers; i++)
        {
            Hand leftHand{}, rightHand{};
            nuitrack_HandTrackerGetUserHands(_pimpl, i, &userId, &leftHand, &rightHand);
            UserHands newHand;
            newHand.userId    = userId;
            newHand.leftHand  = std::make_shared<Hand>(leftHand);
            newHand.rightHand = std::make_shared<Hand>(rightHand);
            userHands.push_back(newHand);
        }

        return userHands;
    }

private:
    HandTrackerDataInner* _pimpl;
};

/**
 * @ingroup UserTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref UserTracker_group "Nuitrack User Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor UserTracker::create.
 * This instance is called %UserTracker module object.
 * To receive the user tracking data, add an UserTracker::OnUpdate callback
 * to the module object with UserTracker::connectOnUpdate method.
 * To handle events of appearance and disappearance of the user, add UserTracker::OnNewUser
 * and UserTracker::OnLostUser callbacks with UserTracker::connectOnNewUser and
 * UserTracker::connectOnLostUser methods respectively.
 */
class UserTrackerPIMPL : public cpp::UserTracker
{
public:
    using Ptr = std::shared_ptr<UserTrackerPIMPL>;

    /**
     * @brief The callback type of the user frame update request.
     * @see tdv::nuitrack::UserFrame
     * @see tdv::nuitrack::User
     * @see connectOnUpdate
     */
    using OnUpdate               = std::function<void (UserFrame::Ptr)>;
    using OnUpdateRawFunctionPtr = void(*)(UserFrame*, UserTracker*);

    /**
     * @brief The callback type of the new user apearance event.
     * This callback will be called if a new user appears in the frame.
     * This callback receive the ID of the new user.
     * @see connectOnNewUser
     */
    using OnNewUser               = std::function<void (int)>;
    using OnNewUserRawFunctionPtr = void(*)(int, UserTracker*);

    /**
     * @brief The callback type of the user disapearance event.
     *
     * This callback will be called if a user disapears from the frame.
     * This callback receive the ID of the lost user.
     * @see connectOnLostUser
     */
    using OnLostUser               = std::function<void (int)>;
    using OnLostUserRawFunctionPtr = void(*)(int, UserTracker*);

    /**
     * @brief Create the UserTracker module object.
     *
     * @return Smart pointer to a new UserTracker instance.
     * @note Do not call this method twice. Instead, use the previously
     * received UserTracker::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_CreateUserTracker(&pimpl));;
        return std::make_shared<UserTrackerPIMPL>(pimpl);
    }

    explicit UserTrackerPIMPL(NuitrackModule* pimpl)
    {
        _pimpl = pimpl;

        _onUpdateCallbackStruct   = new CallbackStruct<UserFrame::Ptr>();
        _onNewUserCallbackStruct  = new CallbackStruct<int>();
        _onLostUserCallbackStruct = new CallbackStruct<int>();

        _callbackWrapper.setUserTracker(this);
        _callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
        _callbackWrapper.setOnNewUserAddress(&onNewUserCallback);
        _callbackWrapper.setOnLostUserAddress(&onLostUserCallback);

        nuitrack_registerUserTrackerCallback(_pimpl, &_callbackWrapper);
    }

    ~UserTrackerPIMPL() override
    {
        nuitrack_DestroyUserTracker(_pimpl);
        destroyUserTracker();
    }

    /**
     * @brief Add a callback for the user frame update request.
     *
     * @param [in] callback Callback to be invoked after the user frame update request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnUpdate
     */
    uint64_t connectOnUpdate(const OnUpdate& callback) override
    {
        return _onUpdateCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the user frame update request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnUpdate
     */
    void disconnectOnUpdate(uint64_t handler) override
    {
        _onUpdateCallbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Add a callback for the new user appearance event.
     *
     * @param [in] callback Callback to be invoked after the user frame update request,
     * if a new user is detected.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnNewUser
     */
    uint64_t connectOnNewUser(const OnNewUser& callback) override
    {
        return _onNewUserCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the new user appearance event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnNewUser
     */
    void disconnectOnNewUser(uint64_t handler) override { _onNewUserCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Add a callback for the user disappearance event.
     *
     * @param [in] callback Callback to be invoked after the user frame update request,
     * if a user is found to be missing.
     * @return Registered callback ID. You can use it to remove the callback.
     * @see disconnectOnLostUser
     */
    uint64_t connectOnLostUser(const OnLostUser& callback) override
    {
        return _onLostUserCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the user disappearance event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnLostUser
     */
    void disconnectOnLostUser(uint64_t handler) override { _onLostUserCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Returns smart pointer to the last available UserFrame.
     */
    UserFrame::Ptr getUserFrame() override
    {
        auto data = nuitrack_GetUserTrackerData(_pimpl);
        return std::make_shared<UserFramePIMPL>(data);
    }

    /**
     * @brief Returns last frame processing time in milliseconds.
     */
    float getProcessingTime() const override
    {
        return nuitrack_GetUserTrackerProcessingTime(_pimpl);
    }

private:
    static void onUpdateCallback(FrameHolder* userFrameImpl, UserTrackerPIMPL* tracker)
    {
        auto frame = std::make_shared<UserFramePIMPL>(userFrameImpl);
        tracker->_onUpdateCallbackStruct->executeAllCallbacks(frame);
    }

    static void onNewUserCallback(int usedID, UserTrackerPIMPL* tracker)
    {
        tracker->_onNewUserCallbackStruct->executeAllCallbacks(usedID);
    }
    static void onLostUserCallback(int usedID, UserTrackerPIMPL* tracker)
    {
        tracker->_onLostUserCallbackStruct->executeAllCallbacks(usedID);
    }

    void destroyUserTracker()
    {
        delete _onUpdateCallbackStruct;
        delete _onNewUserCallbackStruct;
        delete _onLostUserCallbackStruct;
    }

    NuitrackModule* _pimpl;

    UserTrackerCallbackWrapper _callbackWrapper;

    CallbackStruct<UserFrame::Ptr>* _onUpdateCallbackStruct;
    CallbackStruct<int>*            _onNewUserCallbackStruct;
    CallbackStruct<int>*            _onLostUserCallbackStruct;

    friend class NuitrackPIMPL;

    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};

/**
 * @ingroup SkeletonTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref SkeletonTracker_group "Nuitrack Skeleton Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor SkeletonTracker::create.
 * This instance is called %SkeletonTracker module object.
 * To receive the skeleton tracking data, add an SkeletonTracker::OnUpdate callback
 * to the module object with SkeletonTracker::connectOnUpdate method.
 * To handle events of appearance and disappearance of an active user,
 * add SkeletonTracker::OnNewUser and SkeletonTracker::OnLostUser callbacks
 * with SkeletonTracker::connectOnNewUser and SkeletonTracker::connectOnLostUser
 * methods respectively.
 */
class SkeletonTrackerPIMPL : public cpp::SkeletonTracker
{
public:
    /**
     * @brief Smart pointer to access the SkeletonTracker instance.
     * @see create
     */
    using Ptr     = std::shared_ptr<SkeletonTrackerPIMPL>;
    using BasePtr = std::shared_ptr<SkeletonTracker>;

    /**
     * @brief The callback type of the skeleton data update request.
     *
     * This callback receive a smart pointer to SkeletonData, which contains @ref Skeleton array.
     * @see tdv::nuitrack::SkeletonData
     * @see tdv::nuitrack::Skeleton
     * @see connectOnUpdate
     */
    using OnUpdate               = std::function<void (SkeletonData::Ptr)>;
    using OnUpdateRawFunctionPtr = void(*)(SkeletonData*, SkeletonTracker*);

    /**
     * @brief The callback type of the new active user appearance event.
     *
     * This callback will be called if a new active user appears.
     * This callback receive the ID of the new active user.
     * @see connectOnNewUser
     */
    using OnNewUser               = std::function<void (Ptr, int)>;
    using OnNewUserRawFunctionPtr = void(*)(SkeletonTracker*, int);

    /**
     * @brief The callback type of the active user disappearance event.
     *
     * This callback will be called if an active user disappears.
     * This callback receive the ID of the lost active user.
     * @see connectOnLostUser
     */
    using OnLostUser               = std::function<void (Ptr, int)>;
    using OnLostUserRawFunctionPtr = void(*)(SkeletonTracker*, int);

    /**
     * @brief Create the SkeletonTracker module object.
     *
     * @return Smart pointer to a new SkeletonTracker instance.
     * @note Do not call this method twice. Instead, use the previously
     * received SkeletonTracker::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_CreateSkeletonTracker(&pimpl));
        return std::make_shared<SkeletonTrackerPIMPL>(pimpl);
    }

    explicit SkeletonTrackerPIMPL(NuitrackModule* pimpl)
    {
        _pimpl  = pimpl;
        _isCopy = 0;

        _onUpdateCallbackStruct   = new CallbackStruct<SkeletonData::Ptr>();
        _onNewUserCallbackStruct  = new CallbackStruct2p<Ptr, int>();
        _onLostUserCallbackStruct = new CallbackStruct2p<Ptr, int>();

        _callbackWrapper.setSkeletonTracker(this);
        _callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
        _callbackWrapper.setOnNewUserAddress(&onNewUserCallback);
        _callbackWrapper.setOnLostUserAddress(&onLostUserCallback);
        nuitrack_registerSkeletonTrackerCallback(_pimpl, &_callbackWrapper);
    }

    /** @warning For internal use only. */
    SkeletonTrackerPIMPL(NuitrackModule*                    pimpl,
                         CallbackStruct<SkeletonData::Ptr>* onUpdateCallbackStruct,
                         CallbackStruct2p<Ptr, int>*        onNewUserCallbackStruct,
                         CallbackStruct2p<Ptr, int>*        onLostUserCallbackStruct)
    {
        _pimpl  = pimpl;
        _isCopy = 1;

        _onUpdateCallbackStruct   = onUpdateCallbackStruct;
        _onNewUserCallbackStruct  = onNewUserCallbackStruct;
        _onLostUserCallbackStruct = onLostUserCallbackStruct;
    }

    ~SkeletonTrackerPIMPL() override
    {
        if (_isCopy == 0)
        {
            nuitrack_DestroySkeletonTracker(_pimpl);
            destroySkeletonTracker();
        }
    }

    /**
     * @brief Add a callback for the skeleton data update request.
     *
     * @param [in] callback Callback to be invoked after the skeleton data update request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnUpdate
     */
    uint64_t connectOnUpdate(const OnUpdate& callback) override
    {
        return _onUpdateCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the skeleton data update request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnUpdate
     */
    void disconnectOnUpdate(uint64_t handler) override { _onUpdateCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Add a callback for the new active user appearance event.
     *
     * @param [in] callback Callback to be invoked after the skeleton data update request,
     * if a new active user is appeared.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnNewUser
     */
    uint64_t connectOnNewUser(const OnNewUser& callback) { return _onNewUserCallbackStruct->addCallback(callback); }

    /**
     * @brief Remove a callback of the new active user appearance event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnNewUser
     */
    void disconnectOnNewUser(uint64_t handler) override { _onNewUserCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Add a callback for the active user disappearance event.
     *
     * @param [in] callback Callback to be invoked after the skeleton data update request,
     * if an active user is found to be missing.
     * @return Registered callback ID. You can use it to remove the callback.
     * @see disconnectOnLostUser
     */
    uint64_t connectOnLostUser(const OnLostUser& callback) { return _onLostUserCallbackStruct->addCallback(callback); }

    /**
     * @brief Remove a callback of the active user disappearance event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnLostUser
     */
    void disconnectOnLostUser(uint64_t handler) override { _onLostUserCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Set maximum number of users for tracking.
     *
     * @note The function supports tracking from 0 to 6 users.
     * By default, the skeleton of 2 users is tracked.
     * Tracking of more than 2 users may lead to performance loss.
     * @param [in] numUsers Maximum active user number to be set.
     */
    void setNumActiveUsers(int numUsers) override { nuitrack_SetNumActiveUsers(_pimpl, numUsers); }

    /**
     * @brief Returns true if auto tracking is enabled, false otherwise.
     * @note The default value is determined by the %Nuitrack config file.
     * @see setAutoTracking
     */
    bool isAutoTracking() const override { return nuitrack_IsAutoTracking(_pimpl); }

    /**
     * @brief Set user skeleton auto tracking state.
     *
     * Call setAutoTracking(true) to enable auto tracking.
     * Call setAutoTracking(false) to disable auto tracking.
     *
     * When auto tracking is enabled, tracking of the skeleton of a user begins
     * immediately when the user appears in the frame. Otherwise, you must manually
     * start tracking of the user's skeleton.
     *
     * @param [in] tracking Auto tracking state to be set.
     * @see startTracking
     * @see connectOnNewUser
     * @see isAutoTracking
     */
    void setAutoTracking(bool tracking) override { nuitrack_SetAutoTracking(_pimpl, tracking); }

    /**
     * @brief Start tracking of a user.
     *
     * @param [in] userID ID of user which tracking should be started.
     * @see stopTracking
     * @see isTracking
     */
    void startTracking(int userID) override { nuitrack_StartTracking(_pimpl, userID); }
    void stopTracking (int userID) override { nuitrack_StopTracking (_pimpl, userID); }

    /**
     * @brief Get user tracking state.
     *
     * @return True if user is being tracked, false otherwise.
     * @see startTracking
     * @see stopTracking
     */
    bool isTracking(int userID) override { return nuitrack_IsTracking(_pimpl, userID); }

    /**
     * @brief Returns smart pointer to the last avilable SkeletonData.
     */
    SkeletonData::Ptr getSkeletons() override
    {
        auto data = nuitrack_GetSkeletonTrackerData(_pimpl);
        return std::make_shared<SkeletonDataPIMPL>(data);
    }

    /**
     * @brief Returns last skeleton data processing time in milliseconds.
     */
    float getProcessingTime() const override { return nuitrack_GetSkeletonTrackerProcessingTime(_pimpl); }

protected:
    /** @warning For internal use only. */
    static void onUpdateCallback(SkeletonTrackerData* frame, SkeletonTrackerPIMPL* tracker)
    {
        tracker->_onUpdateCallbackStruct->executeAllCallbacks(std::make_shared<SkeletonDataPIMPL>(frame));
    }

    /** @warning For internal use only. */
    static void onNewUserCallback(SkeletonTrackerPIMPL* tracker, int usedID)
    {
        auto ptr = std::make_shared<SkeletonTrackerPIMPL>(tracker->_pimpl,
                                                     tracker->_onUpdateCallbackStruct,
                                                     tracker->_onNewUserCallbackStruct,
                                                     tracker->_onLostUserCallbackStruct);
        tracker->_onNewUserCallbackStruct->executeAllCallbacks(ptr, usedID);
    }

    /** @warning For internal use only. */
    static void onLostUserCallback(SkeletonTrackerPIMPL* tracker, int usedID)
    {
        auto ptr = std::make_shared<SkeletonTrackerPIMPL>(tracker->_pimpl,
                                                     tracker->_onUpdateCallbackStruct,
                                                     tracker->_onNewUserCallbackStruct,
                                                     tracker->_onLostUserCallbackStruct);
        tracker->_onLostUserCallbackStruct->executeAllCallbacks(ptr, usedID);
    }

    void destroySkeletonTracker() const
    {
        delete _onUpdateCallbackStruct;
        delete _onNewUserCallbackStruct;
        delete _onLostUserCallbackStruct;
    }

    ///< @warning For internal use only.
    NuitrackModule* _pimpl;
    int8_t _isCopy;

    CallbackStruct<SkeletonData::Ptr>* _onUpdateCallbackStruct;
    CallbackStruct2p<Ptr, int>*        _onNewUserCallbackStruct;
    CallbackStruct2p<Ptr, int>*        _onLostUserCallbackStruct;

    SkeletonTrackerCallbackWrapper _callbackWrapper;

    friend class NuitrackPIMPL;

private:
    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};


/**
 * @ingroup HandTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref HandTracker_group "Nuitrack Hand Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor HandTracker::create.
 * This instance is called %HandTracker module object.
 * To receive the hand tracking data, add an HandTracker::OnUpdate callback
 * to the module object with HandTracker::connectOnUpdate method.
 */
class HandTrackerPIMPL : public cpp::HandTracker
{
public:
    /**
     * @brief Smart pointer to access the SkeletonTracker instance.
     * @see create
     */
    using Ptr = std::shared_ptr<HandTrackerPIMPL>;

    /**
     * @brief The callback type of the hand data update request.
     *
     * This callback receive a smart pointer to SkeletonData, which contains @ref Skeleton array.
     *
     * @see tdv::nuitrack::HandTrackerData
     * @see tdv::nuitrack::Hand
     * @see connectOnUpdate
     */
    using OnUpdate               = std::function<void (HandTrackerData::Ptr)>;
    using OnUpdateRawFunctionPtr = void(*)(HandTrackerData*, HandTracker*);

    /**
     * @brief Create the HandTracker module object.
     *
     * @return Smart pointer to a new HandTracker instance.
     * @note Do not call this method twice. Instead, use the previously
     * received HandTracker::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_CreateHandTracker(&pimpl));
        return std::make_shared<HandTrackerPIMPL>(pimpl);
    }

    ~HandTrackerPIMPL() override
    {
        destroyHandTracker();
        nuitrack_DestroyHandTracker(_pimpl);
    }

    /** @warning For internal use only. */
    explicit HandTrackerPIMPL(NuitrackModule* pimpl)
    {
        _pimpl = pimpl;

        _callbackStruct = new CallbackStruct<HandTrackerData::Ptr>();

        _callbackWrapper.setHandTracker(this);
        _callbackWrapper.setFunctionAddress(&onUpdateCallback);
        nuitrack_registerHandTrackerCallback(_pimpl, &_callbackWrapper);
    }

    /**
     * @brief Add a callback for the hand data update request.
     *
     * @param [in] callback Callback to be invoked after the hand data update request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnUpdate
     */
    uint64_t connectOnUpdate(const OnUpdate& callback) override
    {
        return _callbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the hand data update request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnUpdate
     */
    void disconnectOnUpdate(uint64_t handler) override
    {
        _callbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Returns smart pointer to the last available HandTrackerData.
     */
    HandTrackerData::Ptr getData() override
    {
        HandTrackerDataInner* data = nullptr;
        nuitrack_ReceiveInnerHandTrackerData(_pimpl, &data);
        return std::make_shared<HandTrackerDataPIMPL>(data);
    }

    /**
     * @brief Returns last hand data processing time in milliseconds.
     */
    float getProcessingTime() const override { return nuitrack_GetHandTrackerProcessingTime(_pimpl); }

protected:
    /** @warning For internal use only. */
    static void onUpdateCallback(HandTrackerDataInner* data, HandTrackerPIMPL* tracker)
    {
        auto frame = std::make_shared<HandTrackerDataPIMPL>(data);
        tracker->_callbackStruct->executeAllCallbacks(frame);
    }

    void destroyHandTracker() const { delete _callbackStruct; }

    NuitrackModule*                       _pimpl;
    HandTrackerCallbackWrapper            _callbackWrapper;
    CallbackStruct<HandTrackerData::Ptr>* _callbackStruct;

    friend class NuitrackPIMPL;

private:
    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Represents the interface to the capabilities of the
 * @ref GestureRecognizer_group "Nuitrack Gesture Recognizer" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor GestureRecognizer::create.
 * This instance is called %GestureRecognizer module object.
 * To receive the gesture progress estimation data, add an GestureRecognizer::OnUpdate callback
 * to the module object with GestureRecognizer::connectOnUpdate method.
 * To handle event of user state change, add GestureRecognizer::OnUserStateChange callback
 * with SkeletonTracker::connectOnUserStateChange method.
 * To handle event of new gesture detection, add GestureRecognizer::OnNewGestures callback
 * with SkeletonTracker::connectOnNewGestures method.
 */
class GestureRecognizerPIMPL : public cpp::GestureRecognizer
{
public:
    using Ptr = std::shared_ptr<GestureRecognizerPIMPL>;

    /**
     * @brief The callback type of the new gesture detection event.
     *
     * This callback is called when it is detected that the user is
     * performing a new gesture.
     * This callback receive a smart pointer to GestureData.
     * @see connectOnNewGestures
     */
    using OnNewGestures               = std::function<void (GestureData::Ptr)>;
    using OnNewGesturesRawFunctionPtr = void(*)(GestureData*, GestureRecognizer*);

    /**
     * @brief The callback type of the user state change event.
     *
     * This callback will be called when it is detected that the
     * user state has changed.
     * This callback receive a smart pointer to UserStateData.
     * @see connectOnUserStateChange
     */
    using OnUserStateChange               = std::function<void (UserStateData::Ptr)>;
    using OnUserStateChangeRawFunctionPtr = void(*)(UserStateData*, GestureRecognizer*);

    /**
     * @brief The callback type of the user gesture data update request.
     *
     * This callback receive a smart pointer to UserGesturesStateData.
     * @see tdv::nuitrack::UserGesturesStateData
     * @see tdv::nuitrack::UserGesturesState
     * @see connectOnUpdate
     */
    using OnUpdate               = std::function<void (UserGesturesStateData::Ptr)>;
    using OnUpdateRawFunctionPtr = void(*)(UserGesturesStateData*, GestureRecognizer*);

    /**
     * @brief Create the GestureRecognizer module object.
     * @return Smart pointer to a new GestureRecognizer instance.
     * @note Do not call this method twice. Instead, use the previously
     * received GestureRecognizer::Ptr.
     */
    static Ptr create()
    {
        NuitrackModule* pimpl = nullptr;
        ExceptionTranslator::generateExceptionByErrorCode(nuitrack_CreateGestureRecognizer(&pimpl));
        return std::make_shared<GestureRecognizerPIMPL>(pimpl);
    }

    /** @warning For internal use only. */
    explicit GestureRecognizerPIMPL(NuitrackModule* pimpl)
    {
        _pimpl = pimpl;

        _onNewGesturesCallbackStruct     = new CallbackStruct<GestureData::Ptr>();
        _onUserStateChangeCallbackStruct = new CallbackStruct<UserStateData::Ptr>();
        _onUpdateCallbackStruct          = new CallbackStruct<UserGesturesStateData::Ptr>();

        _callbackWrapper.setGestureRecognizer(this);
        _callbackWrapper.setOnNewGestureAddress(&onNewGesturesCallback);
        _callbackWrapper.setOnUserStateChangeAddress(&onUserStateChangeCallback);
        _callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
        nuitrack_registerGestureRecognizerCallback(_pimpl, &_callbackWrapper);
    }

    ~GestureRecognizerPIMPL() override
    {
        nuitrack_DestroyGestureRecognizer(_pimpl);
        destroyGestureRecognizer();
    }

    /**
     * @brief Add a callback for the new gesture detection event.
     *
     * @param [in] callback Callback to be invoked after the gesture data update request,
     * if it is detected that the user is performing a new gesture.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnNewGestures
     */
    uint64_t connectOnNewGestures(const OnNewGestures& callback) override
    {
        return _onNewGesturesCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the new gesture detection event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnNewGestures
     */
    void disconnectOnNewGestures(uint64_t handler) override { _onNewGesturesCallbackStruct->deleteCallback(handler); }

    /**
     * @brief Add a callback for the user state change event.
     *
     * @param [in] callback Callback to be invoked after the skeleton data update request,
     * if it is detected that the user state has changed.
     * @return Registered callback ID. You can use it to remove the callback.
     * @see disconnectOnUserStateChange
     */
    uint64_t connectOnUserStateChange(const OnUserStateChange& callback) override
    {
        return _onUserStateChangeCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the user state change event.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnUserStateChange
     */
    void disconnectOnUserStateChange(uint64_t handler) override
    {
        _onUserStateChangeCallbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Add a callback for the gesture state data update request.
     *
     * @param [in] callback Callback to be invoked after the gesture state
     * data update request.
     * @return Callback ID. You can use it to remove the callback.
     * @see disconnectOnUpdate
     */
    uint64_t connectOnUpdate(const OnUpdate& callback) override
    {
        return _onUpdateCallbackStruct->addCallback(callback);
    }

    /**
     * @brief Remove a callback of the gesture state data update request.
     *
     * @param [in] handler ID of the previously added callback.
     * @see connectOnUpdate
     */
    void disconnectOnUpdate(uint64_t handler) override
    {
        _onUpdateCallbackStruct->deleteCallback(handler);
    }

    /**
     * @brief Returns last gesture recognition time in milliseconds.
     */
    float getProcessingTime() const override
    {
        return nuitrack_GetGestureRecognizerProcessingTime(_pimpl);
    }

    /**
     * @brief Set control gesture recognition state.
     *
     * Call setControlGesturesStatus(true) to enable control gestures.
     * Call setControlGesturesStatus(false) to disable control gestures.
     *
     * @param [in] status Control gesture recognition state to be set.
     */
    void setControlGesturesStatus(bool status) override
    {
        nuitrack_UserGesturesSetControlStatus(_pimpl, status);
    }

    /** @warning For internal use only. */
    void destroyGestureRecognizer()
    {
        delete _onNewGesturesCallbackStruct;
        delete _onUserStateChangeCallbackStruct;
        delete _onUpdateCallbackStruct;
    }

protected:
    static void onNewGesturesCallback(GestureRecognizerData* data, GestureRecognizerPIMPL* tracker)
    {
        tracker->_onNewGesturesCallbackStruct->executeAllCallbacks(std::make_shared<GestureDataPIMPL>(data));
    }
    static void onUserStateChangeCallback(UsersStateChanges* data, GestureRecognizerPIMPL* tracker)
    {
        tracker->_onUserStateChangeCallbackStruct->executeAllCallbacks(std::make_shared<UserStateDataPIMPL>(data));
    }
    static void onUpdateCallback(GestureRecognizerUserGesturesStateData* data, GestureRecognizerPIMPL* tracker)
    {
        tracker->_onUpdateCallbackStruct->executeAllCallbacks(std::make_shared<UserGesturesStateDataPIMPL>(data));
    }

    /** @warning For internal use only. */
    NuitrackModule*                             _pimpl;
    GestureRecognizerCallbackWrapper            _callbackWrapper;
    CallbackStruct<GestureData::Ptr>*           _onNewGesturesCallbackStruct;
    CallbackStruct<UserStateData::Ptr>*         _onUserStateChangeCallbackStruct;
    CallbackStruct<UserGesturesStateData::Ptr>* _onUpdateCallbackStruct;

    friend class NuitrackPIMPL;

private:
    bool canUpdate() const override { throw Exception("not implemented"); }
    uint64_t getTimestamp() override { throw Exception("not implemented"); }
};

}}
