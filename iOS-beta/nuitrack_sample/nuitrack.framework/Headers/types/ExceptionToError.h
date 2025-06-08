// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/Error.h"

namespace tdv { namespace nuitrack {

inline nuitrack_error* exceptionToNuitrackError(const Exception &e)
{
	const auto message = e.what();

	switch(e.type())
	{
	case ExceptionType::EXCEPTION:
		return new nuitrack_error(new Exception(message));
	case ExceptionType::TERMINATE_EXCEPTION:
		return new nuitrack_error(new TerminateException(message));
	case ExceptionType::BAD_CONFIG_VALUE_EXCEPTION:
		return new nuitrack_error(new BadConfigValueException(message));
	case ExceptionType::CONFIG_NOT_FOUND_EXCEPTION:
		return new nuitrack_error(new ConfigNotFoundException(message));
	case ExceptionType::MODUDLE_NOT_FOUND_EXCEPTION:
		return new nuitrack_error(new ModuleNotFoundException(message));
	case ExceptionType::LICENSE_NOT_ACQUIRED_EXCEPTION:
		return new nuitrack_error(new LicenseNotAcquiredException(message));
	case ExceptionType::MODULE_NOT_INITIALIZED_EXCEPTION:
		return new nuitrack_error(new ModuleNotInitializedException(message));
	case ExceptionType::MODULE_NOT_STARTED_EXCEPTION:
		return new nuitrack_error(new ModuleNotStartedException(message));
	case ExceptionType::NETWORK_EXCEPTION:
		return new nuitrack_error(new NetworkException(message));
	case ExceptionType::NETWORK_UNAVAILABLE_EXCEPTION:
		return new nuitrack_error(new NetworkUnavailableException(message));
	default:
		return new nuitrack_error(new Exception(message));
	}
}

}}
