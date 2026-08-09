// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <memory>
#include <functional>

#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/Error.h"
#include "nuitrack/cpp/NuitrackDevice.h"

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/ColorSensor.h"
#include "nuitrack/cpp/DepthSensor.h"
#include "nuitrack/cpp/UserTracker.h"
#include "nuitrack/cpp/SkeletonTracker.h"
#include "nuitrack/cpp/GestureRecognizer.h"
#include "nuitrack/cpp/HandTracker.h"
#include "nuitrack/cpp/IssuesData.h"

namespace tdv { namespace nuitrack { namespace cpp {

class NUITRACK_API Nuitrack
{
public:
	/**
	 * @brief Initialize Nuitrack.
	 * NOTE: For Android OS config file get from Nuitrack Manager.
	 *
	 * @param config Config file for Nuitrack initialization.//
	 */
	static void init(const std::string& config = "");

	/**
	 * @brief Run Nuitrack.
	 * NOTE: Start all Nuitrack modules.
	 */
	static void run();

	/**
	 * @brief Update Nuitrack, call all new events.
	 * NOTE: Non block update Nuitrack, call all new events.
	 */
	static void update();

	/**
	 * @brief Update Nuitrack, call all new events.
	 * NOTE: Non block update Nuitrack, synchronize all events by module.
	 *
	 * @param _ Nuitrack module.
	 */
	static void update(const Module::Ptr& _);

	/**
	 * @brief Wait and update Nuitrack, call all new events.
	 * NOTE: Block update Nuitrack, synchronize all events by module.
	 *
	 * @param _ Nuitrack module.
	 */
	static void waitUpdate(const Module::Ptr& _);

	/**
	 * @brief Release Nuitrack
	 * NOTE: Release and destroy all Nuitrack modules.
	 */
	static void release();

	/**
	 * @brief Configure Nuitrack
	 *
	 * @param key - key in config file
	 * @param value - value by key in config file
	 */
	static void setConfigValue(const std::string& key, const std::string& value);

	/**
	 * @brief Get config value
	 *
	 * @param key - key in config file
	 */
	static std::string getConfigValue(const std::string& key);

	// TODO refactor/doxygen
	using OnIssueUpdate = std::function<void (IssuesData::Ptr)>;

	static uint64_t connectOnIssuesUpdate(const OnIssueUpdate& callback);
	static void     disconnectOnIssuesUpdate(uint64_t handler);

	static std::string getLicense();

	static std::string getInstancesJson();
	static std::string getMulticamInstancesJson();
	static std::string getInternalParamsJson();

	static void* getCopyFromDataStream(DataStreamType type, int streamId = 0);
	static void  freeDataStreamItem(void* item);

    /**
     * @brief Get the data type from the data stream
     * @tparam T A data type that supported by data stream (exist in DataStreamType enumeration)
     * @param id Sequential number of the created camera that the data corresponds to (use `0` also for data that is not linked to a specific camera)
     * @return A pointer to the data type or nullptr if data type not exist
     */
	template<class T>
	static std::shared_ptr<T> get(int id = 0)
	{
		auto ptr = getCopyFromDataStream(T::type(), id);
		if (!ptr) return nullptr;
		return std::shared_ptr<T>((T*)ptr, freeDataStreamItem);
	}

	static int getVersion();

	/**
	 * @brief Get list of available devices.
	 *
	 * @return List of available devices.
	 * @see NuitrackDeviceImpl
	 */
	static std::vector<tdv::nuitrack::device::cpp::NuitrackDevice::Ptr> getDeviceList();

	/**
	 * @brief Setting the default device.
	 *
	 * @param _ Device.
	 * @see NuitrackDeviceImpl
	 */
	static void setDevice(const tdv::nuitrack::device::cpp::NuitrackDevice::Ptr& _);

	static bool runDumpSaving();
	static bool isDumpSavingInProgress();
};

}}}