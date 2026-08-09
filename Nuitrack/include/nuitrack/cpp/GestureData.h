// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/cpp/ObjectData.h"
#include "nuitrack/cpp/Types.h"

namespace tdv
{
namespace nuitrack
{

class GestureData: public ObjectData<GestureData> // legacy
{
public:
	~GestureData() override = default;

	/**
	 * @brief Get current number of gestures.
	 * @return Number of gestures.
	 */
	virtual int getNumGestures() const = 0;

	/**
	 * @brief Get current user gestures.
	 * @return Gestures.
	 */
	virtual std::vector<Gesture> getGestures() const = 0;
};

class UserStateData: public ObjectData<UserStateData>
{
public:
	~UserStateData() override = default;

	/**
	 * @brief Get current number of gestures.
	 * @return Number of gestures.
	 */
	virtual int getNumUserStates() const = 0;

	/**
	 * @brief Get user state changes
	 * @return State changes.
	 */
	virtual std::vector<UserState> getUserStates() const = 0;
};

class UserGesturesStateData: public ObjectData<UserGesturesStateData>
{
public:
	~UserGesturesStateData() override = default;

	/**
	 * @brief Get number of users.
	 * @return Number of users.
	 */
	virtual int getNumUsers() const = 0;

	/**
	 * @brief Get users and gestures state
	 * @return User and gesture state for each user.
	 */
	virtual std::vector<UserGesturesState> getUserGesturesStates() const = 0;
};

}
}
