// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <functional>
#include <mutex>
#include <vector>

namespace tdv { namespace nuitrack {

template <typename ParamType>
class CallbackStruct
{
	using CallbackType = std::function<void (ParamType)>;
	using Lock = std::lock_guard<std::mutex>;
public:

	CallbackStruct() { _maxHandle = 0; }

	uint64_t addCallback(const CallbackType& callback)
	{
		Lock l(_mutex);

		_maxHandle++;
		Callback c;
		c.function = callback;
		c.handle = _maxHandle;
		_cbs.push_back(c);
		return _maxHandle;
	}

	void deleteCallback(uint64_t handle)
	{
		Lock l(_mutex);

		for(uint64_t i = 0; i < _cbs.size(); i++)
			if (_cbs[i].handle == handle)
			{
				_cbs.erase(_cbs.begin() + i);
				return;
			}
	}

	void executeAllCallbacks(ParamType param)
	{
		Lock l(_mutex);

		for (auto& cb : _cbs)
			cb.function(param);
	}

	uint64_t getCallbacksCount()
	{
		Lock l(_mutex);
		return _cbs.size();
	}

private:
	struct Callback { CallbackType function; uint64_t handle; };
	std::vector<Callback> _cbs;
	uint64_t _maxHandle;
	std::mutex _mutex;
};

template <typename ParamType1, typename ParamType2>
class CallbackStruct2p
{
	using CallbackType = std::function<void (ParamType1, ParamType2)>;
public:

	CallbackStruct2p() { _maxHandle = 0; }

	uint64_t addCallback(const CallbackType& callback)
	{
		std::lock_guard<std::mutex> l(_mutex);

		_maxHandle++;
		_callbacks.push_back(callback);
		_handles.push_back(_maxHandle);
		return _maxHandle;
	}

	void deleteCallback(uint64_t handle)
	{
		std::lock_guard<std::mutex> l(_mutex);

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
		std::lock_guard<std::mutex> l(_mutex);

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
