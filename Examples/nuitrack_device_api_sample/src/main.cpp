#include <nuitrack/Nuitrack.h>

#include <signal.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace tdv::nuitrack;
using namespace tdv::nuitrack::device;

class UserInteraction
{
public:
	static int askInt(string msg, int minValue, int maxValue)
	{
		int input = minValue - 1;
		string s;
		do
		{
			cout << msg;
			getline(cin, s);
			if (!(istringstream(s) >> input))
				input = minValue - 1;
		} while (!cin.fail() && (input < minValue || input >= maxValue));
		return input;
	}

	static int askIntDefault(string msg, int minValue, int maxValue, int defaultValue)
	{
		int input = defaultValue - 1;
		while (input != defaultValue && (input < minValue || input >= maxValue))
		{
			cout << msg << " (default is " << defaultValue << "): ";

			string s;
			getline(cin, s);

			input = defaultValue;
			if (!s.empty())
			{
				if (!(istringstream(s) >> input))
					input = defaultValue - 1;
			}
		}
		return input;
	}

	static string askString(string msg)
	{
		cout << msg;
		string input;
		getline(cin, input);
		return input;
	}

	static bool confirm(string msg)
	{
		string input;
		do
		{
			cout << msg + " [y/n] ";
			getline(cin, input);
		} while (!cin.fail() && input != "y" && input != "n");
		return input == "y";
	}
};


string toString(ActivationStatus status)
{
	switch (status)
	{
		case ActivationStatus::NONE: return "None";
		case ActivationStatus::TRIAL: return "Trial";
		case ActivationStatus::PRO: return "Pro";
		default: return "Unknown type";
	}
}

void selectDeviceVideoMode(NuitrackDevice::Ptr device, StreamType streamType)
{
	const vector<VideoMode> modes = device->getAvailableVideoModes(streamType);
	string streamName;
	switch (streamType)
	{
		case StreamType::DEPTH:
			streamName = "depth"; break;
		case StreamType::COLOR:
			streamName = "color"; break;
	}

	cout << "Available " << streamName << " video modes:" << endl;
	for (int vm = 0; vm < modes.size(); vm++)
		printf("    [%d] %d x %d @ %d fps\n",
			vm,
			modes[vm].width,
			modes[vm].height,
			modes[vm].fps);
	cout << "(WARNING: not all video modes are supported)\n" << endl;

	int vmIndex = UserInteraction::askIntDefault("\nSelect the video mode", 0, modes.size(), -1);
	if (vmIndex >= 0)
		device->setVideoMode(streamType, modes[vmIndex]);
}

void onNewDepthFrame(DepthFrame::Ptr frame)
{
	if (frame)
		printf("Depth frame [%llu]: %d x %d\n",
			frame->getTimestamp(), frame->getCols(), frame->getRows());
}

void onNewColorFrame(RGBFrame::Ptr frame)
{
	if (frame)
		printf("Color frame [%llu]: %d x %d\n",
			frame->getTimestamp(), frame->getCols(), frame->getRows());
}

bool finished;
void signalHandler(int signal)
{
	if (signal == SIGINT)
		finished = true;
}

int main(int argc, char* argv[])
{
	int errorCode = EXIT_SUCCESS;

	try
	{
		Nuitrack::init();

		// get devices list
		vector<NuitrackDevice::Ptr> devices = Nuitrack::getDeviceList();
		if (devices.empty())
			throw Exception("No devices found.");

		// print available devices
		cout << endl << "Available devices:" << endl;
		for (int i = 0; i < devices.size(); i++)
		{
			printf("    [%d] %s (%s), License: %s\n",
				i,
				devices[i]->getInfo(DeviceInfoType::SERIAL_NUMBER).c_str(),
				devices[i]->getInfo(DeviceInfoType::DEVICE_NAME).c_str(),
				toString(devices[i]->getActivationStatus()).c_str());
		}
		// select a device
		int devIndex = UserInteraction::askInt("\nSelect the device number: ", 0, devices.size());
		if (devIndex < 0)
			throw Exception("Invalid device index.");

		const auto& device = devices[devIndex];

		// select video modes
		selectDeviceVideoMode(device, StreamType::DEPTH);
		selectDeviceVideoMode(device, StreamType::COLOR);

		// activate selected device
		bool isActivated = device->getActivationStatus() != ActivationStatus::NONE;
		if (isActivated)
			isActivated = !UserInteraction::confirm("The device is already activated! Do you want to reactivate it?");

		if (!isActivated)
		{
			string activationKey = UserInteraction::askString("Enter the activation key: ");
			device->activate(activationKey);
			cout << "Activation status: " << toString(device->getActivationStatus()) << endl;
		}

		// set device and run Nuitrack
		if (UserInteraction::confirm("Do you want to run Nuitrack with the selected device?"))
		{
			Nuitrack::setDevice(device);

			auto depthSensor = DepthSensor::create();
			auto colorSensor = ColorSensor::create();

			depthSensor->connectOnNewFrame(onNewDepthFrame);
			colorSensor->connectOnNewFrame(onNewColorFrame);

			Nuitrack::run();

			signal(SIGINT, &signalHandler);
			while (!finished)
				Nuitrack::waitUpdate(depthSensor);
		}
	}
	catch (const LicenseNotAcquiredException& e)
	{
		cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << endl;
		errorCode = EXIT_FAILURE;
	}
	catch (const Exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
		errorCode = EXIT_FAILURE;
	}

	Nuitrack::release();
	return errorCode;
}
