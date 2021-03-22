#include <nuitrack/Nuitrack.h>

#include <signal.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>

using namespace tdv::nuitrack;
using namespace tdv::nuitrack::device;


namespace console {
	namespace interaction {
		int askInt(const std::string& msg, int minValue, int maxValue, bool allowToSkip = false, int defaultValue = -1) {
			const int INVALID_VALUE = minValue - 1;
			int input = INVALID_VALUE;
			do {
				std::cout << msg;
				std::string s;
				std::getline(std::cin, s);

				if (s.empty() && allowToSkip){
					input = defaultValue;
					break;
				}

				if (!s.empty() && !(std::istringstream(s) >> input))
					input = INVALID_VALUE;

			} while (input < minValue || input >= maxValue);

			return input;
		}

		std::string askString(const std::string& msg) {
			std::cout << msg;
			std::string input;
			std::getline(std::cin, input);
			return input;
		}

		bool confirm(const std::string& msg) {
			std::string input;
			do {
				input = askString(msg + " [y/n] ");
			} while (!std::cin.fail() && input != "y" && input != "n");
			return input == "y";
		}
	}

	template<std::size_t Columns>
	class Table {
		using RowType = std::array<std::string, Columns>;

	public:
		Table(RowType&& header): _header(header) {
			for (std::size_t i = 0; i < Columns; ++i)
				_maxColumnLengths[i] = _header[i].length();
		}

		void addRow(RowType&& row) {
			_updateColumnLengths(row);
			_rows.push_back(std::move(row));
		}

		void printTable() const  {
			_printHeader(_header);
			for (const auto& row: _rows)
				_printRow(row);
		}

	private:
		void _updateColumnLengths(const RowType& row) {
			for (std::size_t i = 0; i < Columns; ++i) {
				const auto length = row[i].length();
				if (length > _maxColumnLengths[i])
					_maxColumnLengths[i] = length;
			}
		}

		void _printHeader(const RowType& header) const {
			for (std::size_t i = 0; i < Columns - 1; ++i)
				std::cout << ' ' << _centered(header[i], _maxColumnLengths[i]) << " |";
			std::cout << ' ' << _centered(header[Columns - 1], _maxColumnLengths[Columns - 1]) << '\n';
		}

		void _printRow(const RowType& row) const {
			for (std::size_t i = 0; i < Columns - 1; ++i)
				std::cout << ' ' << std::setw(_maxColumnLengths[i]) << row[i] << " |";
			std::cout << ' ' << std::setw(_maxColumnLengths[Columns - 1]) << row[Columns - 1] << '\n';
		}

		static std::string _centered(const std::string& original, int targetSize) {
			const auto padding = targetSize - original.size();
			if (padding > 0) {
				const auto paddingRight = padding / 2;
				const auto paddingLeft = padding - paddingRight;
				return std::string(paddingLeft, ' ') + original + std::string(paddingRight, ' ');
			}
			return original;
		}

	private:
		const RowType _header;
		std::vector<RowType> _rows;
		std::array<std::size_t, Columns> _maxColumnLengths;
	};

} // namespace console

std::string toString(ActivationStatus status) {
	switch (status) {
		case ActivationStatus::NONE: return "None";
		case ActivationStatus::TRIAL: return "Trial";
		case ActivationStatus::PRO: return "Pro";
		default: return "Unknown type";
	}
}

NuitrackDevice::Ptr selectDevice() {
		std::vector<NuitrackDevice::Ptr> devices = Nuitrack::getDeviceList();

		if (devices.empty())
			throw Exception("No devices found.");

		console::Table<4> table({"Index", "Name", "Serial Number", "License"});
		for (std::size_t i = 0; i < devices.size(); i++)
		{
			const auto& device = devices[i];
			table.addRow({
				std::to_string(i),
				device->getInfo(DeviceInfoType::DEVICE_NAME),
				device->getInfo(DeviceInfoType::SERIAL_NUMBER),
				toString(device->getActivationStatus())
			});
		}
		std::cout << "\nAvailable devices:" << std::endl;
		table.printTable();

		int devIndex = console::interaction::askInt("\nSelect a device. Enter an index from the list (or leave empty for the first one): ", 0, devices.size(), true, 0);

		return devices[devIndex];
}

void selectDeviceVideoMode(NuitrackDevice::Ptr device, StreamType streamType) {
	std::string streamName;
	switch (streamType) {
		case StreamType::DEPTH:
			streamName = "depth"; break;
		case StreamType::COLOR:
			streamName = "color"; break;
	}

	const auto videoModes = device->getAvailableVideoModes(streamType);
	const auto vmSize = videoModes.size();

	console::Table<4> table({"Index", "Width", "Height", "FPS"});
	for (std::size_t i = 0; i < vmSize; ++i) {
		const auto vmWidth = videoModes[i].width;
		const auto vmHeight = videoModes[i].height;
		const auto vmFps = videoModes[i].fps;
		table.addRow({std::to_string(i), std::to_string(vmWidth), std::to_string(vmHeight), std::to_string(vmFps)});
	}

	std::cout << "\nAvailable " << streamName << " video modes:" << std::endl;
	table.printTable();
	std::cout << "(WARNING: not all video modes are supported)" << std::endl;

	int vmIndex = console::interaction::askInt("\nSelect " + streamName + " video mode. Enter an index from the list (or leave empty for default settings): ", 0, vmSize, true, -1);
	if (vmIndex >= 0)
		device->setVideoMode(streamType, videoModes[vmIndex]);
}

void activateDevice(NuitrackDevice::Ptr device) {
		bool isActivated = device->getActivationStatus() != ActivationStatus::NONE;

		if (isActivated)
			isActivated = !console::interaction::confirm("The device is already activated! Do you want to reactivate it?");

		if (!isActivated) {
			std::string activationKey = console::interaction::askString("Enter the activation key: ");
			device->activate(activationKey);
			std::cout << "Activation status: " << toString(device->getActivationStatus()) << std::endl;
		}
}

void onNewDepthFrameCallback(DepthFrame::Ptr frame) {
	if (frame)
		std::cout << "Depth frame [" << frame->getTimestamp() << "]: " << frame->getCols() <<  " x " << frame->getRows() << '\n';
}

void onNewColorFrameCallback(RGBFrame::Ptr frame) {
	if (frame)
		std::cout << "Color frame [" << frame->getTimestamp() << "]: " << frame->getCols() <<  " x " << frame->getRows() << '\n';
}

bool finished;
void signalHandler(int signal) {
	if (signal == SIGINT)
		finished = true;
}

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

			depthSensor->connectOnNewFrame(onNewDepthFrameCallback);
			colorSensor->connectOnNewFrame(onNewColorFrameCallback);

			Nuitrack::run();

			signal(SIGINT, &signalHandler);
			while (!finished)
				Nuitrack::waitUpdate(depthSensor);
		}
	}
	catch (const LicenseNotAcquiredException& e)
	{
		std::cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ')' << std::endl;
		errorCode = EXIT_FAILURE;
	}
	catch (const Exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		errorCode = EXIT_FAILURE;
	}

	Nuitrack::release();
	return errorCode;
}
