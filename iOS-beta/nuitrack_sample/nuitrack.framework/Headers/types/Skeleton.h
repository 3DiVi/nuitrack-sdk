#ifndef NUITRACK_SKELETON_H_
#define NUITRACK_SKELETON_H_

#include <vector>

#include "nuitrack/types/Vector3.h"
#include "nuitrack/types/Orientation.h"

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup SkeletonTracker_group
 * @brief Joint index meaning (please note that <i>JOINT_LEFT_FINGERTIP, JOINT_RIGHT_FINGERTIP, JOINT_LEFT_FOOT, JOINT_RIGHT_FOOT</i> are not used in the current version).
 */
enum JointType
{
	JOINT_NONE				= 0, ///< Reserved joint (unused).

	JOINT_HEAD				= 1, ///< Head
	JOINT_NECK				= 2, ///< Neck
	JOINT_TORSO				= 3, ///< Torso
	JOINT_WAIST				= 4, ///< Waist

	JOINT_LEFT_COLLAR		= 5, ///< Left collar
	JOINT_LEFT_SHOULDER		= 6, ///< Left shoulder
	JOINT_LEFT_ELBOW		= 7, ///< Left elbow
	JOINT_LEFT_WRIST		= 8, ///< Left wrist
	JOINT_LEFT_HAND			= 9, ///< Left hand
	JOINT_LEFT_FINGERTIP	= 10, ///< Left fingertip (<b>not used in the current version</b>).

	JOINT_RIGHT_COLLAR		= 11, ///< Right collar
	JOINT_RIGHT_SHOULDER	= 12, ///< Right shoulder
	JOINT_RIGHT_ELBOW		= 13, ///< Right elbow
	JOINT_RIGHT_WRIST		= 14, ///< Right wrist
	JOINT_RIGHT_HAND		= 15, ///< Right hand
	JOINT_RIGHT_FINGERTIP	= 16, ///< Right fingertip (<b>not used in the current version</b>).

	JOINT_LEFT_HIP			= 17, ///< Left hip
	JOINT_LEFT_KNEE			= 18, ///< Left knee
	JOINT_LEFT_ANKLE		= 19, ///< Left ankle
	JOINT_LEFT_FOOT			= 20, ///< Left foot (<b>not used in the current version</b>).

	JOINT_RIGHT_HIP			= 21, ///< Right hip
	JOINT_RIGHT_KNEE		= 22, ///< Right knee
	JOINT_RIGHT_ANKLE		= 23, ///< Right ankle
	JOINT_RIGHT_FOOT		= 24 ///< Right foot (<b>not used in the current version</b>).
};

/**
 * @ingroup SkeletonTracker_group
 * @brief Stores the joint data.
 */
struct Joint
{
	/**
	 * @brief %Joint type.
	 */
	JointType type;

	/**
	 * @brief %Joint confidence from 0.0 to 1.0. Larger value means more confident joint.
	 */
	float confidence;

	/**
	 * @brief %Joint position in real world coordinates.
	 */
	Vector3 real;

	/**
	 * @brief %Joint position in normalized projective coordinates
	 * (x, y from 0.0 to 1.0, z is real).
	 */
	Vector3 proj;

	/**
	 * @brief %Joint orientation.
	 */
	Orientation orient;
};

/**
 * @ingroup SkeletonTracker_group
 * @brief Stores the data of the skeleton.
 * 
 * @details The skeleton is represented as a set of joints, each of which has its
 * position and orientation. If pairs of adjacent joints are connected by
 * imaginary "bones", you can get a simplified model of a real human skeleton.
 * Then the orientation of the joint will be consistent with the orientation of
 * the outgoing "bone".
 * 
 * The skeleton scheme is shown in the picture below.
 * 
 * @image html images/skeleton_scheme.jpg "Skeleton scheme"
 * @image latex images/skeleton_scheme.jpg "Skeleton scheme"
 * 
 * %Joint orientation is represented in the form of rotation matrix.
 * In T-pose rotation matrices for all joints are equal to identity matrix (see picture below).
 * Rotations for wrists, feet and head are always identity.
 * 
 * @image html images/t_pose.jpg "T-pose"
 * @image latex images/t_pose.jpg "T-pose"
 * 
 */
struct Skeleton
{
	/**
	* @brief User Id. The same as other(@ref UserTracker, @ref HandTracker, @ref GestureRecognizer) modules uses.
	*/
	int id;

	/**
	* @brief Array of joints. Where each index is ::JointType.
	*/
	std::vector<Joint> joints;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_SKELETON_H_ */
