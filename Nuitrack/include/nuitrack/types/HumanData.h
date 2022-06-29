#ifndef NUITRACK_HUMANDATA_LEGACY_H_
#define NUITRACK_HUMANDATA_LEGACY_H_

#include "nuitrack/types/Human.h"
#include "nuitrack/types/ObjectData.h"

namespace tdv
{
namespace nuitrack
{

class HumanData: public ObjectData<HumanData>
{
public:
	virtual ~HumanData() { }

	virtual const std::vector<Human>& getHumans() const = 0;
};

}
}

#endif //NUITRACK_HUMANDATA_LEGACY_H_
