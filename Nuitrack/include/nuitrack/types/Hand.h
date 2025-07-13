// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <memory>

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup HandTracker_group
 * @brief Stores information about the user's hand.
 */
struct Hand
{
	typedef std::shared_ptr<Hand> Ptr;

    float x; ///< The normalized projective x coordinate of the hand (in range [0, 1]).
    float y; ///< The normalized projective y coordinate of the hand (in range [0, 1]).
	bool click; ///< True if the hand makes a click, false otherwise.
	int pressure; ///< Rate of hand clenching.

    float xReal; ///< The x coordinate of the hand in the world system.
    float yReal; ///< The y coordinate of the hand in the world system.
    float zReal; ///< The z coordinate of the hand in the world system.
};

/**
 * @ingroup HandTracker_group
 * @brief Stores information about the user's hand.
 */
struct UserHands
{
    int userId;
    Hand::Ptr leftHand, rightHand;
};

}}
