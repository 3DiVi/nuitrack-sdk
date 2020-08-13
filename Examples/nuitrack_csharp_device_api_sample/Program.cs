using System;
using System.Collections.Generic;

using nuitrack;
using nuitrack.device;

public class Program
{
	static bool _finished = false;
	static bool _run = false;

	static void consoleEventHandler(object sender, ConsoleCancelEventArgs args)
	{
		if (!_run)
			return;

		if (args.SpecialKey == ConsoleSpecialKey.ControlC)
		{
			_finished = true;
			args.Cancel = true;
		}
	}

	static public void Main()
	{
		Console.CancelKeyPress += new ConsoleCancelEventHandler(consoleEventHandler);
		try
		{
			Nuitrack.Init("");

			// get devices list
			List<NuitrackDevice> devices = Nuitrack.GetDeviceList();
			if(devices.Count == 0)
				throw new nuitrack.Exception("No devices found.");

			// print available devices
			Console.Write("\nAvailable devices:\n");
			for(int i = 0; i < devices.Count; i++)
			{
				Console.WriteLine("    [{0}] {1} ({2}), License: {3}",
					i,
					devices[i].GetInfo(DeviceInfoType.SERIAL_NUMBER),
					devices[i].GetInfo(DeviceInfoType.DEVICE_NAME),
					ToString(devices[i].GetActivationStatus()));
			}
			// select a device
			int devIndex = UserInteraction.AskInt("\nSelect the device number: ", 0, devices.Count);
			NuitrackDevice device = devices[devIndex];

			// select video modes
			selectDeviceVideoMode(device, StreamType.DEPTH);
			selectDeviceVideoMode(device, StreamType.COLOR);

			// activate selected device
			bool isActivated = Convert.ToBoolean(device.GetActivationStatus());
			if(isActivated)
				isActivated = !UserInteraction.Confirm("The device is already activated. Do you want to reactivate it?");

			if (!isActivated)
			{
				string activationKey = UserInteraction.AskString("Enter the activation key: ");
				device.Activate(activationKey);
				Console.WriteLine("Activation status: {0}", ToString(device.GetActivationStatus()));
			}

			// set device and run Nuitrack
			if (UserInteraction.Confirm("Do you want to run Nuitrack with the selected device?"))
			{
				Nuitrack.SetDevice(device);

				DepthSensor depthSensor = DepthSensor.Create();
				ColorSensor colorSensor = ColorSensor.Create();

				depthSensor.OnUpdateEvent += onDepthSensorUpdate;
				colorSensor.OnUpdateEvent += onColorSensorUpdate;

				Nuitrack.Run();
				_run = true;

				while (!_finished)
					Nuitrack.WaitUpdate(depthSensor);

				colorSensor.OnUpdateEvent -= onColorSensorUpdate;
				depthSensor.OnUpdateEvent -= onDepthSensorUpdate;
			}

			Nuitrack.Release();
		}
		catch (nuitrack.Exception exception)
		{
			Console.WriteLine("Error: " + exception.ToString());
		}
	}

	static private void onDepthSensorUpdate(DepthFrame depthFrame)
	{
		if (depthFrame != null)
			Console.WriteLine("Depth frame [{0}]: {1} x {2}",
				depthFrame.Timestamp, depthFrame.Cols, depthFrame.Rows);
	}

	static private void onColorSensorUpdate(ColorFrame colorFrame)
	{
		if (colorFrame != null)
			Console.WriteLine("Color frame [{0}]: {1} x {2}",
				colorFrame.Timestamp, colorFrame.Cols, colorFrame.Rows);
	}

	static private string ToString(ActivationStatus status)
	{
		switch(status)
		{
			case ActivationStatus.NONE: return "None";
			case ActivationStatus.TRIAL: return "Trial";
			case ActivationStatus.PRO: return "Pro";
			default: return "Unknown type";
		}
	}

	static private void selectDeviceVideoMode(NuitrackDevice device, StreamType stream)
	{
		List<VideoMode> modes = device.GetAvailableVideoModes(stream);

		if(stream == StreamType.DEPTH)
			Console.WriteLine("Available depth video modes:");
		else if(stream == StreamType.COLOR)
			Console.WriteLine("Available color video modes:");

		for(int vm = 0; vm < modes.Count; vm++)
			Console.WriteLine("    [{0}] {1} x {2} @ {3} fps",
					vm,
					modes[vm].width,
					modes[vm].height,
					modes[vm].fps);
		Console.WriteLine("(WARNING: not all video modes are supported)");

		int vmIdx = UserInteraction.AskIntDefault("\nSelect the video mode", 0, modes.Count, -1);
		if (vmIdx != -1)
			device.SetVideoMode(stream, modes[vmIdx]);
	}
}

public class UserInteraction
{
	static public int AskInt(string msg, int minValue, int maxValue)
	{
		int input = minValue - 1;
		while (input < minValue || input >= maxValue)
		{
			Console.Write(msg);
			string inputStr = Console.ReadLine();
			if (!Int32.TryParse(inputStr, out input))
				input =  minValue - 1;
		}
		return input;
	}

	static public int AskIntDefault(string msg, int minValue, int maxValue, int defaultValue)
	{
		int input = defaultValue - 1;
		while (input != defaultValue && (input < minValue || input >= maxValue))
		{
			input = defaultValue;
			Console.Write(msg + " (default is {0}): ", defaultValue);
			string inputStr = Console.ReadLine();
			if (inputStr != string.Empty)
				if (!Int32.TryParse(inputStr, out input))
					input =  defaultValue - 1;
		}
		return input;
	}

	static public string AskString(string msg)
	{
		Console.Write(msg);
		string input = Console.ReadLine();
		return input;
	}

	static public bool Confirm(string msg)
	{
		string input = "";
		while (input != "y" && input != "n")
		{
			Console.Write(msg + " [y/n] ");
			input = Console.ReadLine().ToLower();
		}
		return input == "y";
	}
}
