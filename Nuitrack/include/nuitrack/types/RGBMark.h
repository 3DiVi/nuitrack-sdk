#ifndef NUITRACK_RGBMARKDATA_H_
#define NUITRACK_RGBMARKDATA_H_

#include "nuitrack/types/ObjectData.h"

namespace tdv
{
namespace nuitrack
{

class RGBMark : public ObjectData<RGBMark>
{
public:
    /**
     * @brief Get orientation of marker
     *
     * @return true for succesful  
     */	
	virtual bool getRotationMat(float *mat, int id) const = 0;
	virtual bool getTranslationMat(float *mat, int id) const = 0;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_RGBMARKDATA_H_ */
