// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <stdexcept>
#include <string>
#include "nuitrack/cpp/Export.h"

namespace tdv { namespace nuitrack {

enum class ExceptionType // Types ?
{
	OK,									///< No exception
	EXCEPTION,							///< tdv::nuitrack::Exception
	TERMINATE_EXCEPTION,				///< tdv::nuitrack::TerminateException
	BAD_CONFIG_VALUE_EXCEPTION,			///< tdv::nuitrack::BadConfigValueException
	CONFIG_NOT_FOUND_EXCEPTION,			///< tdv::nuitrack::ConfigNotFoundException
	MODULE_NOT_FOUND_EXCEPTION,			///< tdv::nuitrack::ModuleNotFoundException
	LICENSE_NOT_ACQUIRED_EXCEPTION,		///< tdv::nuitrack::LicenseNotAcquiredException
	MODULE_NOT_INITIALIZED_EXCEPTION,	///< tdv::nuitrack::ModuleNotInitializedException
	MODULE_NOT_STARTED_EXCEPTION,		///< tdv::nuitrack::ModuleNotStartedException
	NETWORK_EXCEPTION,					///< tdv::nuitrack::NetworkException
	NETWORK_UNAVAILABLE_EXCEPTION,		///< tdv::nuitrack::NetworkUnavailableException
	SENSOR_DISCONNECTED_EXCEPTION		///< tdv::nuitrack::SensorDisconnectedException
};

inline std::string ExceptionTypeToString(ExceptionType type)
{
	switch (type)
	{
		case ExceptionType::EXCEPTION: return "Unknown Exception";
		case ExceptionType::TERMINATE_EXCEPTION: return "TerminateException";
		case ExceptionType::BAD_CONFIG_VALUE_EXCEPTION: return "BadConfigValueException";
		case ExceptionType::CONFIG_NOT_FOUND_EXCEPTION: return "ConfigNotFoundException";
		case ExceptionType::MODULE_NOT_FOUND_EXCEPTION: return "ModuleNotFoundException";
		case ExceptionType::LICENSE_NOT_ACQUIRED_EXCEPTION: return "LicenseNotAcquiredException";
		case ExceptionType::MODULE_NOT_INITIALIZED_EXCEPTION: return "ModuleNotInitializedException";
		case ExceptionType::MODULE_NOT_STARTED_EXCEPTION: return "ModuleNotStartedException";
		case ExceptionType::NETWORK_EXCEPTION: return "NetworkException";
		case ExceptionType::NETWORK_UNAVAILABLE_EXCEPTION: return "NetworkUnavailableException";
		case ExceptionType::SENSOR_DISCONNECTED_EXCEPTION: return "SensorDisconnectedException";
		default: return "";
	}
};

class Exception : public std::runtime_error
{
	mutable std::string _result;

public:
	std::string _message;
	ExceptionType _type {ExceptionType::EXCEPTION};

	explicit Exception(const std::string& _ = "") : std::runtime_error(_), _message(_) {}

	ExceptionType type() const { return _type; }
	const char* msg() const { return _message.c_str(); }
	const char* what() const noexcept { _result = "NuitrackException (" + ExceptionTypeToString(_type) + ")" + (_message.empty() ? "" : ": " + _message); return _result.c_str(); }
};

class TerminateException : public Exception
{
public:
	explicit TerminateException(const std::string& _ = "") : Exception(_) { _type = ExceptionType::TERMINATE_EXCEPTION; }
};

class NetworkException : public TerminateException
{
public:
	explicit NetworkException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::NETWORK_EXCEPTION; }
};

class NetworkUnavailableException : public TerminateException
{
public:
	explicit NetworkUnavailableException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::NETWORK_UNAVAILABLE_EXCEPTION; }
};

class BadConfigValueException : public Exception
{
public:
	explicit BadConfigValueException(const std::string& _ = "") : Exception(_) { _type = ExceptionType::BAD_CONFIG_VALUE_EXCEPTION; }
};

class ConfigNotFoundException : public TerminateException
{
public:
	explicit ConfigNotFoundException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::CONFIG_NOT_FOUND_EXCEPTION; }
};

class ModuleNotFoundException : public TerminateException
{
public:
	explicit ModuleNotFoundException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::MODULE_NOT_FOUND_EXCEPTION; }
};

class LicenseNotAcquiredException : public TerminateException
{
public:
	explicit LicenseNotAcquiredException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::LICENSE_NOT_ACQUIRED_EXCEPTION; }
};

class ModuleNotInitializedException : public TerminateException
{
public:
	explicit ModuleNotInitializedException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::MODULE_NOT_INITIALIZED_EXCEPTION; }
};

class ModuleNotStartedException : public TerminateException
{
public:
	explicit ModuleNotStartedException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::MODULE_NOT_STARTED_EXCEPTION; }
};

class SensorDisconnectedException : public TerminateException
{
public:
	explicit SensorDisconnectedException(const std::string& _ = "") : TerminateException(_) { _type = ExceptionType::SENSOR_DISCONNECTED_EXCEPTION; }
};

struct nuitrack_error
{
	ExceptionType _type;
	std::string _msg;
	explicit nuitrack_error(ExceptionType type, std::string msg) : _type(type), _msg(msg) {}
};

struct ExceptionTranslator
{
	static void generateExceptionByErrorCode(ExceptionType errorCode, std::string errorMessage)
	{
		generateExceptionByErrorCode(errorCode, errorMessage.c_str());
	}

	static void generateExceptionByErrorCode(ExceptionType errorCode, const char* errorMessage = nullptr)
	{
		#if defined(NUITRACK_NO_EXCEPTIONS)
			if (errorCode != ExceptionType::OK) std::terminate();
		#else
			std::string message = errorMessage == nullptr ? "" : errorMessage;
			switch(errorCode)
			{
				case ExceptionType::EXCEPTION:
					throw Exception(message);
				case ExceptionType::TERMINATE_EXCEPTION:
					throw TerminateException(message);
				case ExceptionType::NETWORK_EXCEPTION:
					throw NetworkException(message);
				case ExceptionType::NETWORK_UNAVAILABLE_EXCEPTION:
					throw NetworkUnavailableException(message);
				case ExceptionType::BAD_CONFIG_VALUE_EXCEPTION:
					throw BadConfigValueException(message);
				case ExceptionType::CONFIG_NOT_FOUND_EXCEPTION:
					throw ConfigNotFoundException(message);
				case ExceptionType::MODULE_NOT_FOUND_EXCEPTION:
					throw ModuleNotFoundException(message);
				case ExceptionType::LICENSE_NOT_ACQUIRED_EXCEPTION:
					throw LicenseNotAcquiredException(message);
				case ExceptionType::MODULE_NOT_INITIALIZED_EXCEPTION:
					throw ModuleNotInitializedException(message);
				case ExceptionType::MODULE_NOT_STARTED_EXCEPTION:
					throw ModuleNotStartedException(message);
				case ExceptionType::SENSOR_DISCONNECTED_EXCEPTION:
					throw SensorDisconnectedException(message);
				case ExceptionType::OK:
					break;
			}
		#endif
	}
};

}}
