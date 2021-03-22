#ifndef NUITRACK_EXCEPTION_TO_NUITRACK_ERROR_H_
#define NUITRACK_EXCEPTION_TO_NUITRACK_ERROR_H_

#include "nuitrack/types/Error.h"

namespace tdv
{
namespace nuitrack
{

inline nuitrack_error* exceptionToNuitrackError(const Exception &e)
{
	const auto message = e.what();

	switch(e.type())
	{
	case EXCEPTION:
		return new nuitrack_error(new Exception(message));
	case TERMINATE_EXCEPTION:
		return new nuitrack_error(new TerminateException(message));
	case BAD_CONFIG_VALUE_EXCEPTION:
		return new nuitrack_error(new BadConfigValueException(message));
	case CONFIG_NOT_FOUND_EXCEPTION:
		return new nuitrack_error(new ConfigNotFoundException(message));
	case MODUDLE_NOT_FOUND_EXCEPTION:
		return new nuitrack_error(new ModuleNotFoundException(message));
	case LICENSE_NOT_ACQUIRED_EXCEPTION:
		return new nuitrack_error(new LicenseNotAcquiredException(message));
	case MODULE_NOT_INITIALIZED_EXCEPTION:
		return new nuitrack_error(new ModuleNotInitializedException(message));
	case MODULE_NOT_STARTED_EXCEPTION:
		return new nuitrack_error(new ModuleNotStartedException(message));
	}
}

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_EXCEPTION_TO_NUITRACK_ERROR_H_ */
