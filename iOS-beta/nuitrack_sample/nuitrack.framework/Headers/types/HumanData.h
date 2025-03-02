// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/Human.h"
#include "nuitrack/types/ObjectData.h"

namespace tdv
{
namespace nuitrack
{

class HumanData: public ObjectData<HumanData>
{
public:
	virtual ~HumanData() { }

	virtual const std::vector<Human>& getHumans() const = 0;
};

}
}
