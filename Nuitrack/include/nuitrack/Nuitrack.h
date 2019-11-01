#ifndef NUITRACK_HEADER_ONLY_API_H_
#define NUITRACK_HEADER_ONLY_API_H_

#include <string>
#include <memory>
#include <functional>

#include <stdio.h>

#include "nuitrack/types/Export.h"
#include "nuitrack/types/Error.h"

#include "nuitrack/modules/NuitrackModule.h"
#include "nuitrack/modules/DepthSensor.h"
#include "nuitrack/modules/ColorSensor.h"
#include "nuitrack/modules/UserTracker.h"
#include "nuitrack/modules/SkeletonTracker.h"
#include "nuitrack/modules/GestureRecognizer.h"
#include "nuitrack/modules/HandTracker.h"
#include "nuitrack/types/IssuesData.h"

#include "nuitrack/capi/Public_Nuitrack_CAPI.h"
#include "nuitrack/capi/IssueTracker_CAPI.h"

namespace tdv
{
namespace nuitrack
{

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
class NUITRACK_LOCAL Nuitrack
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
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_InitializeFromConfig(config.c_str()));
	}

	/**
	 * @brief Start processing the data provided by the sensor.
	 * 
	 * The stages of data processing are determined
	 * by the existing module objects. The data is processed asynchronously.
	 * 
	 * @throw tdv::nuitrack::Exception
	 */
	static void run()
	{
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_Run());
	}

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
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_Update());
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
	static void update(std::shared_ptr<HeaderOnlyAPI_Module> module)
	{
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_SyncUpdatePublic(module.get()));
	}

	/**
	 * @brief Initiate %Nuitrack module update and wait for it.
	 * 
	 * Similar to Nuitrack::update(std::shared_ptr<HeaderOnlyAPI_Module> module), but waits until all the required callbacks are called.
	 * 
	 * @note Blocking operation.
	 * @param module %Nuitrack module's Ptr.
	 * @throw tdv::nuitrack::Exception
	 */
	static void waitUpdate(std::shared_ptr<HeaderOnlyAPI_Module> module)
	{
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_WaitSyncUpdatePublic(module.get()));
	}

	/**
	 * @brief Stop data processing and destroy all existing %Nuitrack modules.
	 *
	 * @note To restart Nuitrack after release you should call Nuitrack::init and create all required modules again.
	 * @throw tdv::nuitrack::Exception
	 */
	static void release()
	{
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
		int bufferSize = 5000;
		char* buffer = new char[bufferSize];
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_GetConfigValue(key.c_str(), buffer, bufferSize));

		std::string result = std::string(buffer);
		delete[] buffer;

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
		int bufferSize = (6000 * 6);
		char* buffer = new char[bufferSize];
		ExceptionTranslator::generateExceptionByErrorCode(nuitrack_GetInstancesJson(buffer, bufferSize));

		std::string result = std::string(buffer);
		delete[] buffer;

		return result;
	}

	/**
	 * @brief Callback type of the issue update request.
	 * 
	 * @see tdv::nuitrack::IssuesData
	 * @see tdv::nuitrack::Issue
	 * @see connectOnIssuesUpdate
	 */
	typedef std::function<void (IssuesData::Ptr)> OnIssueUpdate;

	/**
	 * @brief Add a callback for the issue update request.
	 * 
	 * @param [in] callback Callback to be invoked at the issue update request.
	 * @return Registered callback ID. You can use it to remove the callback.
	 * @see disconnectOnIssuesUpdate
	 */
	static uint64_t connectOnIssuesUpdate(const OnIssueUpdate& callback)
	{
		IssueTracker* issueTracker = NULL;
		nuitrack_getIssueTracker(&issueTracker);
		if(issueTracker == NULL)
			return 0;

		if(nuitrack_getIssuesCallbackStruct() == NULL)
		{
			CallbackStruct<IssuesData::Ptr>* ptr = new CallbackStruct<IssuesData::Ptr>();
			nuitrack_setIssuesCallbackStruct(ptr);

			IssueTrackerCallbackWrapper* callbackWrapper = new IssueTrackerCallbackWrapper();
			callbackWrapper->setIssueTracker(issueTracker);
			callbackWrapper->setFunctionAddress(&onIssuesUpdateCallback);
			nuitrack_registerIssuesTrackerCallback(callbackWrapper);
		}

		return ((CallbackStruct<IssuesData::Ptr>*)(nuitrack_getIssuesCallbackStruct()))->addCallback(callback);
	}

	/** @warning For internal use only. */
	static void onIssuesUpdateCallback(IssueTrackerData* data)
	{
		IssuesData::Ptr newData = IssuesData::Ptr(new IssuesData(data));
		CallbackStruct<IssuesData::Ptr>* callbackStruct =
				(CallbackStruct<IssuesData::Ptr>*)nuitrack_getIssuesCallbackStruct();
		if(callbackStruct == NULL)
			return;
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
		CallbackStruct<IssuesData::Ptr>* callbackStruct =
				(CallbackStruct<IssuesData::Ptr>*)nuitrack_getIssuesCallbackStruct();
		if(callbackStruct == NULL)
			return;
		callbackStruct->deleteCallback(handler);
	}
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_HEADER_ONLY_API_H_ */
