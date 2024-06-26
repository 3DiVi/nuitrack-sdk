// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#ifndef USBGATEKEEPER_H_
#define USBGATEKEEPER_H_

#include <jni.h>
#include <map>
#include <stdint.h>
#include <algorithm>
#include <nuitrack/types/Export.h>

namespace tdv
{
namespace nuitrack
{
namespace middleware
{
namespace android
{

class MIDDLEWARE_API USBGateKeeper
{
public:
	USBGateKeeper();
	virtual ~USBGateKeeper();

	bool requestPermission(uint16_t VendorID, uint16_t ProductID, const std::string& usbPath="", const std::string& sig="(II)Z");
	bool requestPermissionUsbPath(const std::string& usbPath);
	bool requestAllPermissions();

	int getFileDescriptor();
	std::vector<std::pair<int, std::string>> getFileDescriptors();
	void closeFileDescriptor();

	void orbbecDeviceWatcherInit();

	static std::pair<std::string, std::string> getAndroidBrandModel();

private:
	static jobject _object_global_USBGateKeeper;
	static jclass _class_global_USBGateKeeper;
};

}
}
}
}

#endif /* USBGATEKEEPER_H_ */
