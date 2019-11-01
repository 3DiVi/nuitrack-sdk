#ifndef NUITRACK_BOUNDING_BOX_H_
#define NUITRACK_BOUNDING_BOX_H_

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup UserTracker_group
 * @brief Stores a bounding box properties.
 */
struct BoundingBox
{
	BoundingBox(float top = 0.0, float bottom = 1.0,
				float left = 0.0, float right = 1.0) :
					top(top), bottom(bottom), left(left), right(right) {}

	float top; ///< Position of the top face of the bounding box
	float bottom; ///< Position of the bottom face of the bounding box
	float left; ///< Position of the left face of the bounding box
	float right; ///< Position of the right face of the bounding box
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_BOUNDING_BOX_H_ */
