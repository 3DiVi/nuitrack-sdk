// Copyright 3DiVi 2025, Inc. All Rights Reserved.

// WARNING: Related files (the number, order, and types of fields in the corresponding structures must match): nuitrack.net/Types.cs

#pragma once

#include <memory>
#include <ostream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <cmath>

#include "nuitrack/cpp/ObjectData.h"

namespace tdv { namespace nuitrack {

/// --- Common Types

extern "C" {

struct CVector3 { float x, y, z; };

struct Color3   { uint8_t blue, green, red; };

}

struct Vector3
{
	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
	Vector3(CVector3 c_vec) : x(c_vec.x), y(c_vec.y), z(c_vec.z) {}

	float x, y, z;
};

template<typename TOut, typename TIn> TOut type2type(const TIn& in);


struct Size
{
	Size(int width = 0, int height = 0) : width(width), height(height) {}

	bool empty() const                   { return width == 0 && height == 0; }
	int  area() const                    { return width * height; }
	Size operator/ (Size& _) const       { return Size(width / _.width, height / _.height); }
	template<typename T> T to() const    { return type2type<T>(*this); }

	int width, height;
};

template<typename TOut, typename TIn>
TOut type2type(const TIn& in)
{
	static_assert(sizeof(TOut) == sizeof(TIn), "Error: types sizes aren't equal");
	TOut out;
	memcpy(&out, &in, sizeof(TOut));
	return out;
}

inline std::ostream& operator<< (std::ostream& s, const nuitrack::Size& size)
{
	s << size.width << "x" << size.height;
	return s;
}

/**
 * @ingroup CommonElements_group
 * @brief Stores the spatial orientation as a 3x3 rotation matrix.
 */
struct Orientation
{
	float matrix[9] = {}; /** @brief Flattened 3x3 rotation matrix. */
};


/**
 * @ingroup CommonElements_group
 * @brief Contains parameters for a stream.
 */
namespace device {
struct VideoMode
{
	int width, height;
	int fps;
};
}


/**
 * @ingroup DataStream_group
 * @brief Enumeration of data types supported by the data stream.
 */
enum class DataStreamType
{
	AccelFrame,
	GyroFrame,
	Count
};

/**
 * @ingroup DataStream_group
 * @brief Metadata for data stream frame.
 */
struct FrameMeta
{
	uint64_t timestamp {0};
};

/**
 * @ingroup DataStream_group
 * @brief Accelerometer data frame.
 */
struct AccelFrame
{
	Vector3   direction;
	FrameMeta meta;

	static DataStreamType type() { return DataStreamType::AccelFrame; }
};

/**
 * @ingroup DataStream_group
 * @brief Gyroscope data frame.
 */
struct GyroFrame
{
	Vector3   direction;
	FrameMeta meta;

	static DataStreamType type() { return DataStreamType::GyroFrame; }
};

enum class SensorRotation
{
	NORMAL, RIGHT, UPSIDE_DOWN, LEFT, COUNT
};

enum class MirrorMode
{
	OFF, ON
};

enum class DistortionModel
{
	NONE                  , /** @brief Rectilinear images. No distortion compensation required. */
	MODIFIED_BROWN_CONRADY, /** @brief Equivalent to Brown-Conrady distortion, except that tangential distortion is applied to radially distorted points */
	INVERSE_BROWN_CONRADY , /** @brief Equivalent to Brown-Conrady distortion, except undistorts image instead of distorting it */
	FTHETA                , /** @brief F-Theta fish-eye distortion model */
	BROWN_CONRADY         , /** @brief Unmodified Brown-Conrady distortion model */
	KANNALA_BRANDT4       , /** @brief Four parameter Kannala Brandt distortion model */
	Count
};

/**
 * @ingroup DepthSensor_group
 * @brief Stores the distortion sensor parameters.
 */
struct Distortion
{
	float k[6] = {}; /** @brief Radial distortion factors */
	float p[2] = {}; /** @brief Tangential distortion factors */
	DistortionModel model { DistortionModel::NONE };
};

/**
* @ingroup DepthSensor_group
* @brief Stores sensor data properties.
*/
struct CameraModel
{
	int            fps; // WARNING: deprecated

	nuitrack::Size size;
	float          hfov, vfov; /** @brief Fields of view in radians. */
	float          fx,   fy;   /** @brief Focal length (for current size) */
	float          cx,   cy;   /** @brief Optical center (for current size) */
	Distortion     distortion;

	CameraModel(int        fps  = 0,
	            Size       size = {},
	            float      hfov = 0,
	            float      vfov = 0,
	            float      fx   = 0,
	            float      fy   = 0,
	            float      cx   = 0,
	            float      cy   = 0,
	            Distortion dstr = {}) :
		fps(fps), size(size), hfov(hfov), vfov(vfov), fx(fx), fy(fy), cx(cx), cy(cy), distortion(dstr) {}

	void fillEmptyFields()
	{
		if (size.empty()) throw std::runtime_error("ERROR: `CameraModel.fillEmptyFields()`: size is empty");

		auto e = 0.01f;
		if (fx < e || fy < e || cx < e || cy < e)
		{
			if (hfov < e) throw std::runtime_error("ERROR: `CameraModel.fillEmptyFields()`: hfov parameter is empty");

			cx = size.width / 2.0f;
			cy = size.height / 2.0f;
			fx = cx / std::tan(hfov / 2.0f);
			fy = fx;
		}
		if (hfov < e)
			hfov = 2.0f * std::atan(cx / fx);
		if (vfov < e)
			vfov = 2.0f * std::atan(cy / fy);
	}

	void applyRotation(SensorRotation rotation)
	{
		if (rotation == SensorRotation::UPSIDE_DOWN)
		{
			cx = size.width - cx;
			cy = size.height - cy;
		}
		else if (rotation == SensorRotation::LEFT || rotation == SensorRotation::RIGHT)
		{
			std::swap(size.width, size.height);
			std::swap(hfov, vfov);
			std::swap(fx, fy);
			std::swap(cx, cy);

			if (rotation == SensorRotation::LEFT)
				cx = size.width - cx;
			else
				cy = size.height - cy;
		}
	}


	void applyMirror()
	{
		cx = size.width - cx;
	}

	void updateSize(nuitrack::Size newSize)
	{
		if (newSize.empty()) throw std::runtime_error("ERROR: `CameraModel.updateSize()`: size is empty");

		fx   = fx / float(size.width)  * float(newSize.width);
		fy   = fy / float(size.height) * float(newSize.height);
		cx   = cx / float(size.width)  * float(newSize.width);
		cy   = cy / float(size.height) * float(newSize.height);
		size = newSize;
	}
};


namespace device {
/**
 * @ingroup CommonElements_group
 * @brief Contains information types for NuitrackDevice.
 */
struct DeviceInfo
{
	enum Type
	{
		PROVIDER_NAME = 0,	///< device provider
		DEVICE_NAME,		///< device name from a driver
		SERIAL_NUMBER,		///< device serial number from a driver
		Count
	};
};
using DeviceInfoType = DeviceInfo::Type;


/**
 * @ingroup CommonElements_group
 * @brief Contains stream data types.
 */
struct Stream
{
	enum Type
	{
		DEPTH = 0,	///< depth stream
		COLOR,		///< color stream
		Count
	};
};
using StreamType = Stream::Type;
}


struct PointCloud
{
	enum class Format
	{
		NUITRACK, TD, UE
	};
};

/// Frames
class Frame: public virtual nuitrack::Traceable
{
public:
	using Ptr = std::shared_ptr<Frame>;

	virtual int      getRows() const = 0;
	virtual int      getCols() const = 0;
	virtual uint64_t getID() const = 0;
	virtual Ptr      updateSize(nuitrack::Size size) const = 0;
};

class RGBFrame: public Frame
{
public:
	using Ptr      = std::shared_ptr<RGBFrame>;
	using DataType = nuitrack::Color3;

	virtual const DataType* getData() const = 0;
	virtual void writeTextureBGRA(uint8_t* outBuf, size_t size) const = 0;
};

class DepthFrame: public Frame
{
public:
	using Ptr      = std::shared_ptr<DepthFrame>;
	using DataType = uint16_t;

	virtual const DataType* getData() const = 0;
	virtual void writePointCloudTextureRGBA(float* outBuf, size_t size, PointCloud::Format format = PointCloud::Format::NUITRACK) const = 0;
};


/**
 * @ingroup UserTracker_group
 * @brief Stores a bounding box properties.
 */
struct BoundingBox
{
	explicit BoundingBox(float top = 0.0, float bottom = 1.0, float left = 0.0, float right = 1.0) : top(top),
		bottom(bottom),
		left(left),
		right(right) {}

	float top, bottom, left, right;
};


/// --- User Tracking and Segmentation / Scene Analysis

/**
 * @ingroup UserTracker_group
 * @brief Stores information about a detected user.
 */
struct User
{
	using Ptr = std::shared_ptr<User>;

	int id; /** @brief %User identifier. */

	Vector3 proj; /** @brief Center of mass in projective coordinates. */
	Vector3 real; /** @brief Center of mass in real coordinates. */

	BoundingBox box; /** @brief Bounding box. Face positions are given in normalized floating-point coordinates in range [0;1]. */

	float occlusion; /** @brief Occlusion rate in range [0;1] */
};


/// --- Skeleton Tracking

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


/// --- Hand Tracking

/**
 * @ingroup HandTracker_group
 * @brief Stores information about the user's hand.
 */
struct Hand
{
	using Ptr = std::shared_ptr<Hand>;

	float x, y;   ///< The normalized projective coordinates of the hand (in range [0, 1]).
	bool click;   ///< True if the hand makes a click, false otherwise.
	int pressure; ///< Rate of hand clenching.

	float xReal, yReal, zReal; ///< Coordinates of the hand in the world system.
};

/**
 * @ingroup HandTracker_group
 * @brief Stores information about the user's hand.
 */
struct UserHands
{
	int userId;
	Hand::Ptr leftHand, rightHand;
};


/// --- Gesture Recognition

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a gesture type.
 */
enum GestureType
{
	GESTURE_WAVING          = 0,
	GESTURE_SWIPE_LEFT      = 1,
	GESTURE_SWIPE_RIGHT     = 2,
	GESTURE_SWIPE_UP        = 3,
	GESTURE_SWIPE_DOWN      = 4,
	GESTURE_PUSH            = 5,
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a user state.
 */
enum UserStateType
{
	USER_IS_ABSENT			= 0,
	USER_IN_SCENE			= 1,
	USER_ACTIVE				= 2
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a gesture with a binding to a user.
 */
struct Gesture
{
	int userId;			/* ID of the user */
	GestureType type;	/* Type of the gesture */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes a state of a particular user.
 */
struct UserState
{
	int userId;			 /* ID of the user */
	UserStateType state; /* State of the user */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the state of a gesture.
 */
struct GestureState
{
	GestureType type;		/* Type of the gesture */
	int         progress;	/* Execution progress (in percents) */
};

/**
 * @ingroup GestureRecognizer_group
 * @brief Describes the user's state, supplemented
 * by information about the actions currently being performed.
 */
struct UserGesturesState : UserState
{
	std::vector<GestureState> gestures;
};


namespace device {

/**
 * @ingroup CommonElements_group
 * @brief Contains activation types.
 */
struct ActivationInfo
{
	enum class Status // please also refer to NuitrackDeviceCommon.cs
	{
		NONE = 0,	///< no valid license
		TRIAL,		///< time-limited license
		PRO,		///< Pro license types
		AI,			///< AI license types 
		AI_ONLINE,  ///< AI subscription license types
		PRO_ONLINE  ///< Pro subscription license types
	};
};

inline std::ostream& operator<< (std::ostream& s, const ActivationInfo::Status status)
{
	switch (status)
	{
		case ActivationInfo::Status::NONE:		 s << "None";		break;
		case ActivationInfo::Status::TRIAL:		 s << "Trial";		break;
		case ActivationInfo::Status::AI:		 s << "AI";			break;
		case ActivationInfo::Status::AI_ONLINE:  s << "AI_Online";	break;
		case ActivationInfo::Status::PRO:		 s << "Pro";		break;
		case ActivationInfo::Status::PRO_ONLINE: s << "Pro_Online"; break;
	}
	return s;
}

using ActivationStatus = ActivationInfo::Status;

}

}}
