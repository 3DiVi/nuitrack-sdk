#ifndef EXCEPTIONTRANSLATOR_H_
#define EXCEPTIONTRANSLATOR_H_

#include "nuitrack/types/Error.h"
#include "nuitrack/capi/Nuitrack_CAPI.h"

namespace tdv
{
namespace nuitrack
{

class ExceptionTranslator
{
public:
	static void generateExceptionByErrorCode(ExceptionType errorCode)
	{
#ifndef NUITRACK_NO_EXCEPTIONS
		switch(errorCode)
		{
		case EXCEPTION:
			throw tdv::nuitrack::Exception();
		case TERMINATE_EXCEPTION:
			throw tdv::nuitrack::TerminateException();
		case BAD_CONFIG_VALUE_EXCEPTION:
			throw tdv::nuitrack::BadConfigValueException();
		case CONFIG_NOT_FOUND_EXCEPTION:
			throw tdv::nuitrack::ConfigNotFoundException();
		case MODUDLE_NOT_FOUND_EXCEPTION:
			throw tdv::nuitrack::ModuleNotFoundException();
		case LICENSE_NOT_ACQUIRED_EXCEPTION:
			throw tdv::nuitrack::LicenseNotAcquiredException();
		case MODULE_NOT_INITIALIZED_EXCEPTION:
			throw tdv::nuitrack::ModuleNotInitializedException();
		case MODULE_NOT_STARTED_EXCEPTION:
			throw tdv::nuitrack::ModuleNotStartedException();
		}
#else
		if (errorCode != ExceptionType::OK)
			std::terminate();
#endif
	}

	static void generateExceptionByErrorCode(ExceptionType errorCode, const char * errorMessage)
	{
#ifndef NUITRACK_NO_EXCEPTIONS
		std::string message = (errorMessage == NULL ? "" : errorMessage);
		switch(errorCode)
		{
		case EXCEPTION:
			throw tdv::nuitrack::Exception("NuitrackException: " + message);
		case TERMINATE_EXCEPTION:
			throw tdv::nuitrack::TerminateException("NuitrackException (TerminateException): " + message);
		case BAD_CONFIG_VALUE_EXCEPTION:
			throw tdv::nuitrack::BadConfigValueException("NuitrackException (BadConfigValueException): " + message);
		case CONFIG_NOT_FOUND_EXCEPTION:
			throw tdv::nuitrack::ConfigNotFoundException("NuitrackException (ConfigNotFoundException): " + message);
		case MODUDLE_NOT_FOUND_EXCEPTION:
			throw tdv::nuitrack::ModuleNotFoundException("NuitrackException (ModuleNotFoundException): " + message);
		case LICENSE_NOT_ACQUIRED_EXCEPTION:
			throw tdv::nuitrack::LicenseNotAcquiredException("NuitrackException (LicenseNotAcquiredException): " + message);
		case MODULE_NOT_INITIALIZED_EXCEPTION:
			throw tdv::nuitrack::ModuleNotInitializedException("NuitrackException (ModuleNotInitializedException): " + message);
		case MODULE_NOT_STARTED_EXCEPTION:
			throw tdv::nuitrack::ModuleNotStartedException("NuitrackException (ModuleNotStartedException): " + message);
		}
#else
		if (errorCode != ExceptionType::OK)
			std::terminate();
#endif
	}
	static void handle(nuitrack_error* e)
	{
		if (e == nullptr)
			return;

		ExceptionType errorCode = nuitrack_GetErrorType(e);

		const char* msg = nuitrack_GetErrorMessage(e);
		std::string errorMessage = (msg == nullptr ? "" : msg);

		nuitrack_DestroyError(e);

		if (errorMessage.empty())
			ExceptionTranslator::generateExceptionByErrorCode(errorCode);
		else
			ExceptionTranslator::generateExceptionByErrorCode(errorCode, errorMessage.c_str());
	}
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* EXCEPTIONTRANSLATOR_H_ */
