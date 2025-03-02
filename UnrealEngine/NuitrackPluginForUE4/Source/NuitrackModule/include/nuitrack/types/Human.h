// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <map>

#include "nuitrack/types/Skeleton.h"

namespace tdv
{
namespace nuitrack
{

struct Human
{
	std::size_t id;
	std::string uuid;
	Skeleton skeletonReal;
	std::map<std::string, Skeleton> views;

};

}
}
