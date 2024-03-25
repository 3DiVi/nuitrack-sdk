#ifndef NUITRACK_ERROR_H_
#define NUITRACK_ERROR_H_

#include <stdexcept>

#include "nuitrack/types/Export.h"

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup CommonElements_group
 * @brief Possible error codes for Nuitrack internal functions.
 * 
 * Each member of the enumeration corresponds to the Nuitrack exception,
 * except for the OK member, to which there is no exception.
 */
enum ExceptionType
{
	OK, ///< No exception
	EXCEPTION, ///< tdv::nuitrack::Exception
	TERMINATE_EXCEPTION, ///< tdv::nuitrack::TerminateException
	BAD_CONFIG_VALUE_EXCEPTION, ///< tdv::nuitrack::BadConfigValueException
	CONFIG_NOT_FOUND_EXCEPTION, ///< tdv::nuitrack::ConfigNotFoundException
	MODUDLE_NOT_FOUND_EXCEPTION, ///< tdv::nuitrack::ModuleNotFoundException
	LICENSE_NOT_ACQUIRED_EXCEPTION, ///< tdv::nuitrack::LicenseNotAcquiredException
	MODULE_NOT_INITIALIZED_EXCEPTION, ///< tdv::nuitrack::ModuleNotInitializedException
	MODULE_NOT_STARTED_EXCEPTION, ///< tdv::nuitrack::ModuleNotStartedException
	NETWORK_EXCEPTION, ///< tdv::nuitrack::NetworkException
	NETWORK_UNAVAILABLE_EXCEPTION, ///< tdv::nuitrack::NetworkUnavailableException
	SENSOR_DISCONNECTED_EXCEPTION ///< tdv::nuitrack::SensorDisconnectedException
};

/**
 * @ingroup CommonElements_group
 * @brief Common %Nuitrack exception class.
 */
class Exception : public std::runtime_error
{
public:
	Exception(const std::string& msg = "")
		: std::runtime_error(msg)
	{
	}

	/**
	 * @brief Exception type as enum value.
	 * @see ExceptionType
	 */
	virtual ExceptionType type() const
	{
		return EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class TerminateException : public Exception
{
public:
	TerminateException(const std::string& msg = "")
		: Exception(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return TERMINATE_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class BadConfigValueException : public Exception
{
public:
	BadConfigValueException(const std::string& msg = "")
		: Exception(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return BAD_CONFIG_VALUE_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class ConfigNotFoundException : public TerminateException
{
public:
	ConfigNotFoundException(const std::string& msg = "")
		: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return CONFIG_NOT_FOUND_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class ModuleNotFoundException : public TerminateException
{
public:
	ModuleNotFoundException(const std::string& msg = "")
		: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return MODUDLE_NOT_FOUND_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class LicenseNotAcquiredException : public TerminateException
{
public:
	LicenseNotAcquiredException(const std::string& msg = "")
		: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return LICENSE_NOT_ACQUIRED_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class ModuleNotInitializedException : public TerminateException
{
public:
	ModuleNotInitializedException(const std::string& msg = "")
		: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return MODULE_NOT_INITIALIZED_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class ModuleNotStartedException : public TerminateException
{
public:
	ModuleNotStartedException(const std::string& msg = "")
		: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return MODULE_NOT_STARTED_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class NetworkException : public TerminateException
{
public:
	NetworkException(const std::string& msg = "")
			: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return NETWORK_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class NetworkUnavailableException : public TerminateException
{
public:
	NetworkUnavailableException(const std::string& msg = "")
			: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return NETWORK_UNAVAILABLE_EXCEPTION;
	}
};

/**
 * @ingroup CommonElements_group
 */
class SensorDisconnectedException : public TerminateException
{
public:
	SensorDisconnectedException(const std::string& msg = "")
			: TerminateException(msg)
	{
	}

	virtual ExceptionType type() const
	{
		return SENSOR_DISCONNECTED_EXCEPTION;
	}
};

struct nuitrack_error
{
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_ERROR_H_ */
