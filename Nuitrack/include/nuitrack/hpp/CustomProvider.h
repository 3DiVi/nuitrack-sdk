// Copyright 3DiVi 2025, Inc. All Rights Reserved.
#pragma once

#include "nuitrack/capi/Nuitrack_CAPI.h"

namespace tdv { namespace nuitrack {

class CustomProvider
{
 public:
	enum DataType: uint8_t
	{
		DEPTH = 0,
		IMAGE
	};

	enum PixelType: uint8_t
	{
		PIXEL_16UC1 = 0,
		PIXEL_8UC3
	};

	static void sendData(DataType dataType, uint32_t width, uint32_t height, uint8_t* data, PixelType pixelType,
	                     uint64_t timestamp = -1, uint32_t id = -1)
	{
		nuitrack_sendData((uint8_t)dataType, width, height, data, (uint8_t)pixelType, timestamp, id);
	}
};

}}
