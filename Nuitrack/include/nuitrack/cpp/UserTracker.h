// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include <functional>

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/UserFrame.h"

namespace tdv { namespace nuitrack { namespace cpp {

class UserTracker: public Module
{
public:
	using Ptr = std::shared_ptr<UserTracker>;

	using OnUpdate   = std::function<void (UserFrame::Ptr)>;
	using OnNewUser  = std::function<void (int)>;
	using OnLostUser = std::function<void (int)>;

	NUITRACK_API static UserTracker::Ptr create();

	virtual uint64_t connectOnUpdate(const OnUpdate& callback) = 0;
	virtual void	 disconnectOnUpdate(uint64_t handler) = 0;

	virtual uint64_t connectOnNewUser(const OnNewUser& callback) = 0;
	virtual void	 disconnectOnNewUser(uint64_t handler) = 0;

	virtual uint64_t connectOnLostUser(const OnLostUser& callback) = 0;
	virtual void	 disconnectOnLostUser(uint64_t handler) = 0;

	virtual UserFrame::Ptr getUserFrame() = 0;

	virtual float getProcessingTime() const = 0;
};

}}}
