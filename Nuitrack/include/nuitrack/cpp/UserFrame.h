// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <vector>

#include "nuitrack/cpp/Types.h"

namespace tdv { namespace nuitrack {

class UserFrame: public Frame
{
public:
	using Ptr      = std::shared_ptr<UserFrame>;
	using DataType = uint16_t;
	virtual const DataType* getData() const = 0;

	/**
	 * @brief Get current Users.
	 * @return Users.
	 */
	virtual std::vector<User> getUsers() const = 0;
	virtual std::vector<bool> getOutOfWindow() const { return {}; };


	// to be reworked
	virtual Vector3 getFloor() const = 0;
	virtual Vector3 getFloorNormal() const = 0;
};

}}
