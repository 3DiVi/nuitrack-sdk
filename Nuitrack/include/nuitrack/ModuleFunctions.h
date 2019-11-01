#ifndef MODULEFUNCTIONS_H_
#define MODULEFUNCTIONS_H_

#include <stdio.h>
#include <memory>
#include "nuitrack/types/Export.h"
#include "nuitrack/modules/NuitrackModule.h"

namespace tdv {
namespace nuitrack {

class ModuleFunctions
{
public:
	static bool GetNuitrackModuleCanUpdate(NuitrackModule* module);

	static uint64_t GetNuitrackModuleTimestamp(NuitrackModule* module);
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* MODULEFUNCTIONS_H_ */
