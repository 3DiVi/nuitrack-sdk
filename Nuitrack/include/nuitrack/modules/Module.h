// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include <cstdint>

namespace tdv
{
namespace nuitrack
{

class Nuitrack;
class ModuleFunctions;

class Module
{
public:
	virtual ~Module() = default;

private:

	virtual bool canUpdate() const = 0;
	virtual uint64_t getTimestamp() = 0;

	friend class Nuitrack;
	friend class ModuleFunctions;

};

}
}
