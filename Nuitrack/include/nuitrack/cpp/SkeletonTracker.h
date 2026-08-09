// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <functional>

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/SkeletonData.h"

namespace tdv { namespace nuitrack { namespace cpp {

/**
 * @brief Represent access to user skeleton tracking.
 * @ingroup SkeletonTracker_group
 */
class SkeletonTracker: public Module
{
public:
	using Ptr = std::shared_ptr<SkeletonTracker>;

	using OnUpdate   = std::function<void (SkeletonData::Ptr)>;
	using OnNewUser  = std::function<void (SkeletonTracker::Ptr, int)>;
	using OnLostUser = std::function<void (SkeletonTracker::Ptr, int)>;

	NUITRACK_API static SkeletonTracker::Ptr create();

	virtual uint64_t connectOnUpdate(const OnUpdate&) = 0;
	virtual void     disconnectOnUpdate(uint64_t) = 0;

	virtual uint64_t connectOnNewUser(const OnNewUser&) { throw TerminateException{}; }; // TODO re-align
	virtual void     disconnectOnNewUser(uint64_t) = 0;


	virtual uint64_t connectOnLostUser(const OnLostUser&) { throw TerminateException{}; }; // TODO re-align
	virtual void     disconnectOnLostUser(uint64_t) = 0;

	/**
	 * @brief Set maximum number of users for tracking.
	 * @param[in] numUsers Maximum users number.
	 */
	virtual void setNumActiveUsers(int numUsers) = 0;

	/**
	 * @brief Get users skeleton auto tracking status.
	 * @return Is auto tracking enabled status.
	 */
	virtual bool isAutoTracking() const = 0;

	/**
	 * @brief Set users skeleton auto tracking.
	 * @param[in] tracking Enable or disable auto tracking.
	 */
	virtual void setAutoTracking(bool tracking) = 0;

	/**
	 * @brief Start tracking user by ID.
	 * @param[in] userID Id of user which tracking should be started.
	 */
	virtual void startTracking(int userID) = 0;

	/**
	 * @brief Stop tracking user by ID.
	 * @param[in] userID Id of user which tracking should be stopped.
	 */
	virtual void stopTracking(int userID) = 0;

	/**
	 * @brief Check tracking status of user by ID.
	 * @return Tracking status of user.
	 */
	virtual bool isTracking(int userID) = 0;

	/**
	 * @brief Get smart pointer to last available UserSkeletons.
	 * @return Smart pointer to last available UserSkeletons.
	 */
	virtual SkeletonData::Ptr getSkeletons() = 0;

	/**
	 * @brief Get current processing time.
	 *
	 * @return Frame processing time in milliseconds.
	 */
	virtual float getProcessingTime() const = 0;
};

}}}
