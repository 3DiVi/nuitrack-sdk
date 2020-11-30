#ifndef NUITRACK_MODULE_H_
#define NUITRACK_MODULE_H_

#include <stdint.h>

namespace tdv
{
namespace nuitrack
{

class Nuitrack;
class ModuleFunctions;

class Module
{
public:
	virtual ~Module() {}

private:

	virtual bool canUpdate() const = 0;
	virtual uint64_t getTimestamp() = 0;

	friend class Nuitrack;
	friend class ModuleFunctions;

};

}
}

#endif /* NUITRACK_MODULE_H_ */
