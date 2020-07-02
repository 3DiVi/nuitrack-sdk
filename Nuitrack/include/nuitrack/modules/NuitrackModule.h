#ifndef NUITRACKMODULE_H_
#define NUITRACKMODULE_H_

#include <memory>
#include <mutex>
#include "Module.h"
#include "nuitrack/types/Error.h"

class ExceptionHolder
{
public:
	ExceptionHolder(tdv::nuitrack::ExceptionType type = tdv::nuitrack::OK, std::string message = "")
	    : type(type), message(message)
	{
	}

	virtual tdv::nuitrack::ExceptionType getType() const { return type; }
	virtual void setType(tdv::nuitrack::ExceptionType type) { this->type = type; }
	virtual std::string getMessage() const { return message; }
	virtual void setMessage(std::string message) { this->message = message; }

protected:
	tdv::nuitrack::ExceptionType type;
	std::string message;
};

class AtomicExceptionHolder : public ExceptionHolder {
public:
	tdv::nuitrack::ExceptionType getType() const override {
		std::lock_guard<std::mutex> lock(_mutex);
		return type;
	}
	void setType(tdv::nuitrack::ExceptionType type) override {
		std::lock_guard<std::mutex> lock(_mutex);
		this->type = type;
	}
	std::string getMessage() const override {
		std::lock_guard<std::mutex> lock(_mutex);
		return message;
	}
	void setMessage(std::string message) override {
		std::lock_guard<std::mutex> lock(_mutex);
		this->message = message;
	}
private:
	mutable std::mutex _mutex;
};

struct NuitrackModule
{
	std::shared_ptr<tdv::nuitrack::Module> impl;
	std::shared_ptr<ExceptionHolder> exceptionInfo;
};

#endif /* NUITRACKMODULE_H_ */
