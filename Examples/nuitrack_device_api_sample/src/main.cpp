#include <nuitrack/Nuitrack.h>
#include <nuitrack/utils/TablePrint.h>
#include <csignal>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;
using namespace tdv::nuitrack;
using namespace tdv::nuitrack::device;


namespace console {
	namespace interaction {
		int askInt(const string& msg, int minValue, int maxValue, bool allowToSkip = false, int defaultValue = -1) {
			const auto INVALID_VALUE = minValue - 1;
			auto input = INVALID_VALUE;
			do {
				cout << msg;
				string s;
				getline(cin, s);

				if (s.empty() && allowToSkip){
					input = defaultValue;
					break;
				}

				if (!s.empty() && !(istringstream(s) >> input))
					input = INVALID_VALUE;

			} while (input < minValue || input >= maxValue);

			return input;
		}

		string askString(const string& msg) {
			cout << msg;
			string input;
			getline(cin, input);
			return input;
		}

		bool confirm(const string& msg) {
			string input;
			do { input = askString(msg + " [y/n] "); } 
			while (!cin.fail() && input != "y" && input != "n");
			return input == "y";
		}
	}
} // namespace console

NuitrackDevice::Ptr selectDevice() {
		vector<NuitrackDevice::Ptr> devices;
		while (true)
		{
			devices = Nuitrack::getDeviceList();
			if (!devices.empty()) break;

			cout << "\nConnect sensor and press Enter to continue" << endl;
			cin.ignore();
		}

		Table<4> table({"Index", "Name", "Serial Number", "License"});
		for (size_t i = 0; i < devices.size(); i++)
		{
			stringstream ss; ss << devices[i]->getActivationStatus();
			table.addRow({ to_string(i), devices[i]->getInfo(DeviceInfoType::DEVICE_NAME), 
				devices[i]->getInfo(DeviceInfoType::SERIAL_NUMBER), ss.str() });
		}
		cout << "\nAvailable devices:" << endl;
		table.printTable();

		int devIndex = console::interaction::askInt("\nSelect a device. Enter an index from the list (or leave empty for the first one): ", 0, devices.size(), true, 0);

		return devices[devIndex];
}

void selectDeviceVideoMode(const NuitrackDevice::Ptr& device, StreamType streamType) {
	string streamName;
	switch (streamType) {
		case StreamType::DEPTH:
			streamName = "depth"; break;
		case StreamType::COLOR:
			streamName = "color"; break;
	}

	const auto videoModes = device->getAvailableVideoModes(streamType);

	Table<4, string, int> table({"Index", "Width", "Height", "FPS"});
	for (int i = 0; i < videoModes.size(); ++i)
		table.addRow({i, videoModes[i].width, videoModes[i].height, videoModes[i].fps});

	cout << "\nAvailable " << streamName << " video modes:" << endl;
	table.printTable();
	cout << "(WARNING: not all video modes are supported)" << endl;

	int vmIndex = console::interaction::askInt("\nSelect " + streamName + " video mode. Enter an index from the list (or leave empty for default settings): ",
		 0, videoModes.size(), true, -1);
	if (vmIndex >= 0)
		device->setVideoMode(streamType, videoModes[vmIndex]);
}

void activateDevice(NuitrackDevice::Ptr device) {
		auto isActivated = device->getActivationStatus() != ActivationStatus::NONE;

		if (isActivated) isActivated = !console::interaction::confirm("The device is already activated! Do you want to reactivate it?");

		if (!isActivated) {
			auto activationKey = console::interaction::askString("Enter the activation key: ");
			device->activate(activationKey);
			cout << "Activation status: " << device->getActivationStatus() << endl;
		}
}

void onNewDepthFrameCallback(const DepthFrame::Ptr& frame) {
	if (!frame) return;
	cout << "Nuitrack received Depth Frame [" << frame->getTimestamp() << "]: " << frame->getCols() <<  " x " << frame->getRows() << '\n';
}

void onNewColorFrameCallback(const RGBFrame::Ptr& frame) {
	if (!frame) return;
	cout << "Nuitrack received Color Frame [" << frame->getTimestamp() << "]: " << frame->getCols() <<  " x " << frame->getRows() << '\n';
}

void onNewSkeletonCallback(const SkeletonData::Ptr& skeletonData) {
	if (!skeletonData) return;
	cout << "Nuitrack detected " << skeletonData->getNumSkeletons() << " skeletons" << '\n';
	for (const auto& skeleton : skeletonData->getSkeletons())
	{
		printf("Skeleton (ID: %d) at position - X: %d, Y: %d, Z: %d\n",
				skeleton.id, int(skeleton.joints[JOINT_LEFT_COLLAR].real.x),
							int(skeleton.joints[JOINT_LEFT_COLLAR].real.y),
							int(skeleton.joints[JOINT_LEFT_COLLAR].real.z));
	}
	cout << "-----------------------\n";
}

bool finished;
void signalHandler(int signal) { if (signal == SIGINT) finished = true; }

int main(int argc, char* argv[]) {
	int errorCode = EXIT_SUCCESS;

	try {
		Nuitrack::init();

		const auto device = selectDevice();
		activateDevice(device);

		if (console::interaction::confirm("Do you want to run Nuitrack with the selected device?")) {
			selectDeviceVideoMode(device, StreamType::DEPTH);
			selectDeviceVideoMode(device, StreamType::COLOR);

			Nuitrack::setDevice(device);

			auto depthSensor = DepthSensor::create();
			auto colorSensor = ColorSensor::create();
			auto skeletonTracker = SkeletonTracker::create();

			depthSensor->connectOnNewFrame(onNewDepthFrameCallback);
			colorSensor->connectOnNewFrame(onNewColorFrameCallback);
			skeletonTracker->connectOnUpdate(onNewSkeletonCallback);

			Nuitrack::run();

			signal(SIGINT, &signalHandler);
			while (!finished)
				Nuitrack::waitUpdate(skeletonTracker);
		}
	}
	catch (const LicenseNotAcquiredException& e)
	{
		cerr << "LicenseNotAcquired exception (ExceptionType: " << int(e.type()) << ')' << endl;
		errorCode = EXIT_FAILURE;
	}
	catch (const tdv::nuitrack::Exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
		errorCode = EXIT_FAILURE;
	}

	Nuitrack::release();
	return errorCode;
}
