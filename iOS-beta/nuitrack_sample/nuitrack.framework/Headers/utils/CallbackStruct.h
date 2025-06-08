// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <functional>
#include <mutex>
#include <vector>

namespace tdv { namespace nuitrack {

template <typename ParamType>
class CallbackStruct
{
	typedef std::function<void (ParamType)> CallbackType;
public:

	CallbackStruct() { _maxHandle = 0; }

	uint64_t addCallback(const CallbackType& callback)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_maxHandle++;
		_callbacks.push_back(callback);
		_handles.push_back(_maxHandle);
		return _maxHandle;
	}

	void deleteCallback(uint64_t handle)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		for(uint64_t i = 0; i < _handles.size(); i++)
			if (_handles[i] == handle)
			{
				_callbacks.erase(_callbacks.begin() + i);
				_handles.erase(_handles.begin() + i);
				return;
			}
	}

	void executeAllCallbacks(ParamType param)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		for (auto callback : _callbacks)
			callback(param);
	}

	uint64_t getCallbacksCount()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _callbacks.size();
	}

private:
	std::vector<CallbackType> _callbacks;
	std::vector<uint64_t> _handles;
	uint64_t _maxHandle;
	std::mutex _mutex;
};

template <typename ParamType1, typename ParamType2>
class CallbackStruct2p
{
	typedef std::function<void (ParamType1, ParamType2)> CallbackType;

public:

	CallbackStruct2p() { _maxHandle = 0; }

	uint64_t addCallback(const CallbackType& callback)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_maxHandle++;
		_callbacks.push_back(callback);
		_handles.push_back(_maxHandle);
		return _maxHandle;
	}

	void deleteCallback(uint64_t handle)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		for (uint64_t i = 0; i < _handles.size(); i++)
			if (_handles[i] == handle)
			{
				_callbacks.erase(_callbacks.begin() + i);
				_handles.erase(_handles.begin() + i);
				return;
			}
	}

	void executeAllCallbacks(ParamType1 param1, ParamType2 param2)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		for (auto callback : _callbacks)
			callback(param1, param2);
	}

	uint64_t getCallbacksCount() { return _callbacks.size(); }

private:
	std::vector<CallbackType> _callbacks;
	std::vector<uint64_t> _handles;
	uint64_t _maxHandle;
	std::mutex _mutex;
};

}}
