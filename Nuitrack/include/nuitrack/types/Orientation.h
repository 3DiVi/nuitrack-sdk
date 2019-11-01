#ifndef NUITRACK_ORIENTATION_H_
#define NUITRACK_ORIENTATION_H_

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Stores the spatial orientation as a 3x3 rotation matrix.
 */
struct Orientation
{
	/**
	 * @brief Constructs an orientation with the zero matrix
	 */
	Orientation()
	{
		matrix[0] = 0;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 0;
		matrix[4] = 0;
		matrix[5] = 0;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 0;
	}

	/**
	 * @brief Flattened 3x3 rotation matrix.
	 */
	float matrix[9];
};

}
}

#endif /* NUITRACK_ORIENTATION_H_ */
