#ifndef NUITRACK_HUMAN_H_
#define NUITRACK_HUMAN_H_

#include <string>
#include <map>

#include "nuitrack/types/Skeleton.h"

namespace tdv
{
namespace nuitrack
{

struct Human
{
	std::size_t id;
	std::string uuid;
	Skeleton skeletonReal;
	std::map<std::string, Skeleton> views;

};

}
}

#endif //NUITRACK_HUMAN_H_
