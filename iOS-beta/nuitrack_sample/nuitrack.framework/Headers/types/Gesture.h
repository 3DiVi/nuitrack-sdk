#ifndef NUITRACK_GESTURE_H_
#define NUITRACK_GESTURE_H_

#include <memory>
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
	/*
	 * ID of the user
	 */
	int userId;

	/*
	 * Type of the gesture
	 */
	GestureType type;
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a state of a particular user.
 */
struct UserState
{
	/*
	 * ID of the user
	 */
	int userId;

	/*
	 * State of the user
	 */
	UserStateType state;
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the state of a gesture.
 */
struct GestureState
{
	/*
	 * Type of the gesture
	 */
	GestureType type;

	/*
	 * Execution progress (in percents)
	 */
	int progress;
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the user's state, supplemented
 * by information about the actions currently being performed.
 */
struct UserGesturesState : public UserState
{
	/*
	 * Gesture information
	 */
	std::vector<GestureState> gestures;
};

} // namespace nuitrack
} // namespace tdv

#endif /* NUITRACK_GESTURE_H_ */
