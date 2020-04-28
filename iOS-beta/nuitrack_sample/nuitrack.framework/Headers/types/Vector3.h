#ifndef NUITRACK_VECTOR3_H_
#define NUITRACK_VECTOR3_H_

namespace tdv
{
namespace nuitrack
{

struct Vector3
{
	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	float x;
	float y;
	float z;
};

}
}

#endif /* NUITRACK_VECTOR3_H_ */
