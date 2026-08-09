// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include <functional>

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/GestureData.h"

namespace tdv { namespace nuitrack { namespace cpp {

/**
 * @brief Represent access to hand gesture recognition.
 * @ingroup GestureRecognizer_group
 */
class GestureRecognizer: public Module
{
public:
	using Ptr = std::shared_ptr<GestureRecognizer>;

	/*
	 * GestureRecognizer new gestures event.
	 */
	using OnNewGestures = std::function<void (GestureData::Ptr)>;

	/*
	 * On users state changes event
	 */
	using OnUserStateChange = std::function<void (UserStateData::Ptr)>;

	/*
	 * On update event
	 */
	using OnUpdate = std::function<void (UserGesturesStateData::Ptr)>;

	/**
	 * @brief Create GestureRecognizer.
	 *
	 * @return new instance GestureRecognizer.
	 */
	NUITRACK_API static GestureRecognizer::Ptr create();

	/**
	 * @brief Register OnNewGestures event callback.
	 *
	 * @param callback OnNewGestures callback
	 *
	 * @return callback handler
	 */
	virtual uint64_t connectOnNewGestures(const OnNewGestures& callback) = 0;

	/**
	 * @brief Unregister OnNewGestures event callback.
	 *
	 * @param callback handler
	 */
	virtual void disconnectOnNewGestures(uint64_t handler) = 0;

	/**
	 * @brief Register OnUsersStateChanges event callback.
	 *
	 * @param callback OnUsersStateChanges callback
	 *
	 * @return callback handler
	 */
	virtual uint64_t connectOnUserStateChange(const OnUserStateChange& callback) = 0;

	/**
	 * @brief Unregister OnUserStateChange event callback.
	 *
	 * @param callback handler
	 */
	virtual void disconnectOnUserStateChange(uint64_t handler) = 0;

	/**
	 * @brief Register OnUpdate event callback.
	 *
	 * @param OnUpdate callback
	 *
	 * @return callback handler
	 */
	virtual uint64_t connectOnUpdate(const OnUpdate& callback) = 0;

	/**
	 * @brief Unregister OnUpdate event callback.
	 *
	 * @param callback handler
	 */
	virtual void disconnectOnUpdate(uint64_t handler) = 0;

	/**
	 * @brief Get current processing time
	 *
	 * @return milliseconds
	 */
	virtual float getProcessingTime() const = 0;

	/**
	 * @brief Turn on/off control gestures (swipes/push)
	 *
	 * @param status (true - on, false - off)
	 */
	virtual void setControlGesturesStatus(bool status) = 0;
};

}}}
