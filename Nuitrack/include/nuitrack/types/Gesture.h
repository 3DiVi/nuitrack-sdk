// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <vector>

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a gesture type.
 */
enum GestureType
{
	GESTURE_WAVING          = 0,
	GESTURE_SWIPE_LEFT      = 1,
	GESTURE_SWIPE_RIGHT     = 2,
	GESTURE_SWIPE_UP        = 3,
	GESTURE_SWIPE_DOWN      = 4,
	GESTURE_PUSH            = 5,
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a user state.
 */
enum UserStateType
{
	USER_IS_ABSENT			= 0,
	USER_IN_SCENE			= 1,
	USER_ACTIVE				= 2
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a gesture with a binding to a user.
 */
struct Gesture
{
	int userId; /* ID of the user */
	GestureType type; /* Type of the gesture */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a state of a particular user.
 */
struct UserState
{
	int userId; /* ID of the user */
	UserStateType state; /* State of the user */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the state of a gesture.
 */
struct GestureState
{
	GestureType type; /* Type of the gesture */
	int progress; /* Execution progress (in percents) */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the user's state, supplemented
 * by information about the actions currently being performed.
 */
struct UserGesturesState : public UserState
{
	std::vector<GestureState> gestures; /* Gesture information */
};

} // namespace nuitrack
} // namespace tdv
