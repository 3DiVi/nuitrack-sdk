// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

namespace tdv
{
namespace nuitrack
{

extern "C" {

struct CVector3
{
	float x;
	float y;
	float z;
};

}

struct Vector3
{
	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
	Vector3(CVector3 c_vec) : x(c_vec.x), y(c_vec.y), z(c_vec.z) {}

	float x;
	float y;
	float z;
};

}
}
