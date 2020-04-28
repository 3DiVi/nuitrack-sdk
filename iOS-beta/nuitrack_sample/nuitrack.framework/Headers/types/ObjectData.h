#ifndef NUITRACK_OBJECTDATA_H_
#define NUITRACK_OBJECTDATA_H_

#include <memory>
#include <cstdint>

#include <chrono>
#include <vector>
#include <string>

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup CommonElements_group
 * @brief Generalized class for data with a timestamp
 */
class BaseObjectData
{
public:
	typedef std::shared_ptr<BaseObjectData> Ptr;

	/**
	 * @brief Returns the data timestamp in microseconds.
	 * 
	 * The timestamp characterizes the time point to which the data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp() const = 0;
};

/**
 * @ingroup CommonElements_group
 * @brief Generalized template for data with a timestamp
 */
template<typename TImpl>
class ObjectData : public virtual BaseObjectData
{
public:
	typedef std::shared_ptr<TImpl> Ptr;

	virtual ~ObjectData() {}

};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_OBJECTDATA_H_ */
