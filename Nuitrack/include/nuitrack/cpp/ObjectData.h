// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace tdv { namespace nuitrack {

struct Event
{
	std::string name;
	uint64_t timestamp;
};

/**
 * @ingroup CommonElements_group
 * @brief Generalized class for data with a timestamp
 */
class BaseObjectData // ->Timestamped (from hpp)
{
public:
	/**
	 * @brief Get timestamp for current data.
	 * @return Timestamp data.
	 */
	virtual uint64_t getTimestamp() const = 0;

	using Ptr = std::shared_ptr<BaseObjectData>;
	virtual ~BaseObjectData() = default;
};


class Traceable : public BaseObjectData
{
public:
	using Ptr = std::shared_ptr<Traceable>;
	std::vector<Event> events, inconsistEvents;

	void addEvent(const std::string& name)
	{
		using namespace std::chrono;
		const uint64_t ts = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		events.push_back({name, ts});
	}

	void addEvent(const std::string& name, const uint64_t& timestamp) { inconsistEvents.push_back({name, timestamp}); }
	void copyEventsFrom(const Traceable::Ptr& object) { copyEventsFrom(*object); }

	void copyEventsFrom(const Traceable& object)
	{
		events.insert(events.end(), object.events.begin(), object.events.end());
		inconsistEvents.insert(inconsistEvents.end(), object.inconsistEvents.begin(), object.inconsistEvents.end());
	}
};


/**
 * @ingroup CommonElements_group
 * @brief Generalized template for data with a timestamp
 */
// TODO: a dummy class for only one `using` -> for refactoring
template<typename TImpl>
class ObjectData : public virtual Traceable // ? virtual
{
public:
	using Ptr = std::shared_ptr<TImpl>; // ?
	~ObjectData() override = default;
};

}}
