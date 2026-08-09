// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include <mutex>
#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Error.h"

class ExceptionHolder
{
public:
	using Ptr = std::shared_ptr<ExceptionHolder>;

	explicit ExceptionHolder(tdv::nuitrack::ExceptionType type = tdv::nuitrack::ExceptionType::OK, std::string message = "") : 
		_type(type), _message(message) {}

	virtual tdv::nuitrack::ExceptionType getType() const	{ return _type; }
	virtual void setType(tdv::nuitrack::ExceptionType type) { _type = type; }
	virtual std::string getMessage() const					{ return _message; }
	virtual void setMessage(std::string message)			{ _message = message; }

	virtual ~ExceptionHolder() = default;

protected:
	tdv::nuitrack::ExceptionType _type;
	std::string _message;
};

class AtomicExceptionHolder : public ExceptionHolder
{
public:
	using Lock = std::lock_guard<std::mutex>;

	tdv::nuitrack::ExceptionType getType() const override	 { Lock lock(_mutex); return _type; }
	void setType(tdv::nuitrack::ExceptionType type) override { Lock lock(_mutex); _type = type; }
	std::string getMessage() const override					 { Lock lock(_mutex); return _message; }
	void setMessage(std::string message) override			 { Lock lock(_mutex); _message = message; }

	~AtomicExceptionHolder() override = default;
private:
	mutable std::mutex _mutex;
};

// Plain struct as a Module::Ptr holder
struct NuitrackModule
{
	tdv::nuitrack::Module::Ptr impl;
	ExceptionHolder::Ptr	   exceptionInfo;
};
