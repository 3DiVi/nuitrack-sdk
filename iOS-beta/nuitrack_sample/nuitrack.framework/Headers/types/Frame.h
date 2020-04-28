#ifndef NUITRACK_FRAME_H_
#define NUITRACK_FRAME_H_

#include "nuitrack/types/ObjectData.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Represents a generalized frame.
 */
template<typename TImpl, typename TData>
class Frame: public ObjectData<TImpl>
{
public:
	typedef TData DataType;

	virtual ~Frame() {}

	/**
	 * @brief Returns the number of rows in the frame.
	 */
	virtual int getRows() const = 0;

	/**
	 * @brief Returns the number of columns in the frame.
	 */
	virtual int getCols() const = 0;

	/**
	 * @brief Returns the frame ID.
	 */
	virtual uint64_t getID() const = 0;

	/**
	 * @brief Returns the frame data.
	 */
	virtual const DataType* getData() const = 0;
};

}
}

#endif /* NUITRACK_IMAGE_H_ */
