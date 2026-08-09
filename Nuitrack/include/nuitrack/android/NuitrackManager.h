// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <nuitrack/cpp/Export.h>

namespace tdv { namespace nuitrack { namespace middleware { namespace android {

/**
 * Native wrapper for INudroidManager interface
 */
class NUITRACK_API NuitrackManager
{
public:
	NuitrackManager();
	virtual ~NuitrackManager();

	/**
	 * Get version Nuitrack Manager
	 */
	std::string getVersion();

	/**
	 * Get path to Nuitrack data
	 */
	std::string getDataPath();

	/**
	 * Get path to libraries Nuitrack modules
	 */
	std::string getLibraryPath();

private:
	/**
	 * Call Nuitrack Manager Handler methods
	 */
	void callMethod(const std::string& method, std::string& result);
};

}}}}