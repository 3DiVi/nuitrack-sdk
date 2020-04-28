#ifndef NUITRACKMODULE_H_
#define NUITRACKMODULE_H_

#include <memory>
#include "Module.h"
#include "nuitrack/types/Error.h"

struct ExceptionHolder
{
	ExceptionHolder(tdv::nuitrack::ExceptionType type = tdv::nuitrack::OK, std::string message = "")
	    : type(type), message(message)
	{
	}

	tdv::nuitrack::ExceptionType type;
	std::string message;
};

struct NuitrackModule
{
	std::shared_ptr<tdv::nuitrack::Module> impl;
	std::shared_ptr<ExceptionHolder> exceptionInfo;
};

#endif /* NUITRACKMODULE_H_ */
