// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/cpp/ObjectData.h"

namespace tdv { namespace nuitrack {

struct Human
{
	std::size_t id;
	std::string uuid;
	Skeleton skeletonReal;
	std::map<std::string, Skeleton> views;

};

class HumanData: public ObjectData<HumanData>
{
public:
	virtual const std::vector<Human>& getHumans() const = 0;
	~HumanData() override = default;
};

}}
