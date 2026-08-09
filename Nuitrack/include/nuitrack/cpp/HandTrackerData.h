// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/cpp/ObjectData.h"
#include "nuitrack/cpp/Types.h"
#include <vector>

namespace tdv { namespace nuitrack {

class HandTrackerData: public ObjectData<HandTrackerData> //legacy
{
public:
	~HandTrackerData() override = default;

    /**
     * @brief Get current number of users tracked by hand tracker
     * @return Number of users
     */
    virtual int getNumUsers() const = 0;

    /**
     * @brief Get user hands
     * @return User hands
     */
    virtual std::vector<UserHands> getUsersHands() const = 0;
};

}}
