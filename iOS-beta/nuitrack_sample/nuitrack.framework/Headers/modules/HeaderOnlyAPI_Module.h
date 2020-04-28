#ifndef HEADER_ONLY_API_MODULE_H_
#define HEADER_ONLY_API_MODULE_H_

#include <stdint.h>

namespace tdv
{
namespace nuitrack
{

class HeaderOnlyAPI_Module
{
public:
	virtual bool canUpdate() const = 0;
	virtual uint64_t getTimestamp() = 0;
};

} // namespace nuitrack
} // namespace tdv

#endif /* NUITRACK_MODULE_H_ */
