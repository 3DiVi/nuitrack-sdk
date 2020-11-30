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
		: _type(type), _message(message)
	{
	}

	virtual ~ExceptionHolder() {}

	virtual tdv::nuitrack::ExceptionType getType() const { return _type; }
	virtual void setType(tdv::nuitrack::ExceptionType type) { _type = type; }
	virtual std::string getMessage() const { return _message; }
	virtual void setMessage(std::string message) { _message = message; }

protected:
	tdv::nuitrack::ExceptionType _type;
	std::string _message;
};

class AtomicExceptionHolder : public ExceptionHolder {
public:
	tdv::nuitrack::ExceptionType getType() const override {
		std::lock_guard<std::mutex> lock(_mutex);
		return _type;
	}
	void setType(tdv::nuitrack::ExceptionType type) override {
		std::lock_guard<std::mutex> lock(_mutex);
		_type = type;
	}
	std::string getMessage() const override {
		std::lock_guard<std::mutex> lock(_mutex);
		return _message;
	}
	void setMessage(std::string message) override {
		std::lock_guard<std::mutex> lock(_mutex);
		_message = message;
	}

	virtual ~AtomicExceptionHolder() {}
private:
	mutable std::mutex _mutex;
};

struct NuitrackModule
{
	std::shared_ptr<tdv::nuitrack::Module> impl;
	std::shared_ptr<ExceptionHolder> exceptionInfo;
};

#endif /* NUITRACKMODULE_H_ */
