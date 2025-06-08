// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/Error.h"
#include "nuitrack/capi/Nuitrack_CAPI.h"

namespace tdv { namespace nuitrack {

class ExceptionTranslator
{
public:
	static void generateExceptionByErrorCode(ExceptionType errorCode, const char * errorMessage = nullptr)
	{
        #ifndef NUITRACK_NO_EXCEPTIONS
		std::string message = (errorMessage == nullptr ? "" : errorMessage);
		switch(errorCode)
		{
			case ExceptionType::EXCEPTION:
				throw Exception("NuitrackException: " + message);
			case ExceptionType::TERMINATE_EXCEPTION:
				throw TerminateException("NuitrackException (TerminateException): " + message);
			case ExceptionType::BAD_CONFIG_VALUE_EXCEPTION:
				throw BadConfigValueException("NuitrackException (BadConfigValueException): " + message);
			case ExceptionType::CONFIG_NOT_FOUND_EXCEPTION:
				throw ConfigNotFoundException("NuitrackException (ConfigNotFoundException): " + message);
			case ExceptionType::MODUDLE_NOT_FOUND_EXCEPTION:
				throw ModuleNotFoundException("NuitrackException (ModuleNotFoundException): " + message);
			case ExceptionType::LICENSE_NOT_ACQUIRED_EXCEPTION:
				throw LicenseNotAcquiredException("NuitrackException (LicenseNotAcquiredException): " + message);
			case ExceptionType::MODULE_NOT_INITIALIZED_EXCEPTION:
				throw ModuleNotInitializedException("NuitrackException (ModuleNotInitializedException): " + message);
			case ExceptionType::MODULE_NOT_STARTED_EXCEPTION:
				throw ModuleNotStartedException("NuitrackException (ModuleNotStartedException): " + message);
			case ExceptionType::NETWORK_EXCEPTION:
				throw NetworkException("NuitrackException (NetworkException): " + message);
			case ExceptionType::NETWORK_UNAVAILABLE_EXCEPTION:
				throw NetworkUnavailableException("NuitrackException (NetworkUnavailableException): " + message);
			case ExceptionType::SENSOR_DISCONNECTED_EXCEPTION:
				throw SensorDisconnectedException("NuitrackException (SensorDisconnectedException): " + message);
			case ExceptionType::OK:
				break;
		}
        #else
		if (errorCode != ExceptionType::OK) std::terminate();
        #endif
	}
	static void handle(nuitrack_error* e)
	{
		if (e == nullptr) return;

        auto errorCode = nuitrack_GetErrorType(e);

		const char* msg = nuitrack_GetErrorMessage(e);
		std::string errorMessage = (msg == nullptr ? "" : msg);

		nuitrack_DestroyError(e);

		if (errorMessage.empty())
			ExceptionTranslator::generateExceptionByErrorCode(errorCode);
		else
			ExceptionTranslator::generateExceptionByErrorCode(errorCode, errorMessage.c_str());
	}
};

}}
