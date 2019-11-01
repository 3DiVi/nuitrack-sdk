#ifndef NUITRACK_COLOR3_H_
#define NUITRACK_COLOR3_H_

namespace tdv
{
namespace nuitrack
{

struct Color3
{
	Color3(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0)
		: blue(blue), green(green), red(red) {}

	uint8_t blue;
	uint8_t green;
	uint8_t red;
};

}
}

#endif /* NUITRACK_COLOR3_H_ */
