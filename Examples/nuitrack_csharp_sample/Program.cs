using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using nuitrack;
using nuitrack.issues;

namespace nuitrack
{
	public class Program
	{
		static public void Main()
		{
			Console.CancelKeyPress += delegate {
				Nuitrack.Release();
				GC.Collect();
				GC.WaitForPendingFinalizers();
			};
			try
			{
				Application.Run(new MainForm());
			}
			catch(Exception exception)
			{
				Console.WriteLine(exception.ToString());
			}
		}
	}

	public class DirectBitmap : IDisposable
	{
		public Bitmap Bitmap { get; private set; }

		public Int32[] Bits { get; private set; }
		public bool Disposed { get; private set; }
		public int Height { get; private set; }
		public int Width { get; private set; }

		protected GCHandle BitsHandle { get; private set; }

		public DirectBitmap(int width, int height)
		{
			Width = width;
			Height = height;
			Bits = new Int32[width * height];
			BitsHandle = GCHandle.Alloc(Bits, GCHandleType.Pinned);
			Bitmap = new Bitmap(width, height, width * 4, PixelFormat.Format32bppPArgb, BitsHandle.AddrOfPinnedObject());
		}

		public void SetPixel(int x, int y, Color colour)
		{
			int index = x + (y * Width);
			int col = colour.ToArgb();

			Bits[index] = col;
		}

		public Color GetPixel(int x, int y)
		{
			int index = x + (y * Width);
			int col = Bits[index];
			Color result = Color.FromArgb(col);

			return result;
		}

		public void Dispose()
		{
			if (Disposed)
				return;
			Disposed = true;
			Bitmap.Dispose();
			BitsHandle.Free();
		}
	}

	public class MainForm : Form
	{
		private DirectBitmap _bitmap;
		private bool _visualizeColorImage = false;
		private bool _colorStreamEnabled = false;

		private DepthSensor _depthSensor;
		private ColorSensor _colorSensor;
		private UserTracker _userTracker;
		private SkeletonTracker _skeletonTracker;
		private GestureRecognizer _gestureRecognizer;
		private HandTracker _handTracker;

		private DepthFrame _depthFrame;
		private SkeletonData _skeletonData;
		private HandTrackerData _handTrackerData;
		private IssuesData _issuesData = null;

		public MainForm()
		{
			// Initialize Nuitrack. This should be called before using any Nuitrack module.
			// By passing the default arguments we specify that Nuitrack must determine
			// the location automatically.
			try
			{
				Nuitrack.Init("");
			}
			catch(Exception exception)
			{
				Console.WriteLine("Cannot initialize Nuitrack.");
				throw exception;
			}

			try
			{
				// Create and setup all required modules
				_depthSensor = DepthSensor.Create();
				_colorSensor = ColorSensor.Create();
				_userTracker = UserTracker.Create();
				_skeletonTracker = SkeletonTracker.Create();
				_handTracker = HandTracker.Create();
				_gestureRecognizer = GestureRecognizer.Create();
			}
			catch(Exception exception)
			{
				Console.WriteLine("Cannot create Nuitrack module.");
				throw exception;
			}

			_depthSensor.SetMirror(false);

			// Add event handlers for all modules
			_depthSensor.OnUpdateEvent += onDepthSensorUpdate;
			_colorSensor.OnUpdateEvent += onColorSensorUpdate;
			_userTracker.OnUpdateEvent += onUserTrackerUpdate;
			_skeletonTracker.OnSkeletonUpdateEvent += onSkeletonUpdate;
			_handTracker.OnUpdateEvent += onHandTrackerUpdate;
			_gestureRecognizer.OnNewGesturesEvent += onNewGestures;

			// Add an event handler for the IssueUpdate event 
			Nuitrack.onIssueUpdateEvent += onIssueDataUpdate;

			// Create and configure the Bitmap object according to the depth sensor output mode
			OutputMode mode = _depthSensor.GetOutputMode();
			OutputMode colorMode = _colorSensor.GetOutputMode();

			if (mode.XRes < colorMode.XRes)
				mode.XRes = colorMode.XRes;
			if (mode.YRes < colorMode.YRes)
				mode.YRes = colorMode.YRes;

			_bitmap = new DirectBitmap(mode.XRes, mode.YRes);
			for (int y = 0; y < mode.YRes; ++y)
			{
				for (int x = 0; x < mode.XRes; ++x)
					_bitmap.SetPixel(x, y, Color.FromKnownColor(KnownColor.Aqua));
			}

			// Set fixed form size
			this.MinimumSize = this.MaximumSize = new Size(mode.XRes, mode.YRes);

			// Disable unnecessary caption bar buttons
			this.MinimizeBox = this.MaximizeBox = false;

			// Enable double buffering to prevent flicker
			this.DoubleBuffered = true;

			// Run Nuitrack. This starts sensor data processing.
			try
			{
				Nuitrack.Run();
			}
			catch(Exception exception)
			{
				Console.WriteLine("Cannot start Nuitrack.");
				throw exception;
			}

			this.Show();
		}

		~MainForm()
		{
			_bitmap.Dispose();
		}

		protected override void OnFormClosing(FormClosingEventArgs e)
		{
			// Release Nuitrack and remove all modules
			try
			{
				Nuitrack.onIssueUpdateEvent -= onIssueDataUpdate;

				_depthSensor.OnUpdateEvent -= onDepthSensorUpdate;
				_colorSensor.OnUpdateEvent -= onColorSensorUpdate;
				_userTracker.OnUpdateEvent -= onUserTrackerUpdate;
				_skeletonTracker.OnSkeletonUpdateEvent -= onSkeletonUpdate;
				_handTracker.OnUpdateEvent -= onHandTrackerUpdate;
				_gestureRecognizer.OnNewGesturesEvent -= onNewGestures;

				Nuitrack.Release();
			}
			catch(Exception exception)
			{
				Console.WriteLine("Nuitrack release failed.");
				throw exception;
			}
		}

		// Switch visualization mode on a mouse click
		protected override void OnClick(EventArgs args)
		{
			base.OnClick(args);

			_visualizeColorImage = !_visualizeColorImage;
		}

		protected override void OnPaint(PaintEventArgs args)
		{
			base.OnPaint(args);

			// Update Nuitrack data. Data will be synchronized with skeleton time stamps.
			try
			{
				Nuitrack.Update(_skeletonTracker);
			}
			catch(LicenseNotAcquiredException exception)
			{
				Console.WriteLine("LicenseNotAcquired exception. Exception: ", exception);
				throw exception;
			}
			catch(Exception exception)
			{
				Console.WriteLine("Nuitrack update failed. Exception: ", exception);
			}

			// Draw a bitmap
			args.Graphics.DrawImage(_bitmap.Bitmap, new Point(0, 0));

			// Draw skeleton joints
			if (_skeletonData != null)
			{
				const int jointSize = 10;
				foreach (var skeleton in _skeletonData.Skeletons)
				{
					SolidBrush brush = new SolidBrush(Color.FromArgb(255 - 40 * skeleton.ID, 0, 0));
					foreach (var joint in skeleton.Joints)
					{
						args.Graphics.FillEllipse(brush, joint.Proj.X * _bitmap.Width - jointSize / 2,
												  joint.Proj.Y * _bitmap.Height - jointSize / 2, jointSize, jointSize);
					}
				}
			}

			// Draw hand pointers
			if (_handTrackerData != null)
			{
				foreach (var userHands in _handTrackerData.UsersHands)
				{
					if (userHands.LeftHand != null)
					{
						HandContent hand = userHands.LeftHand.Value;
						int size = hand.Click ? 20 : 30;
						Brush brush = new SolidBrush(Color.Aquamarine);
						args.Graphics.FillEllipse(brush, hand.X * _bitmap.Width - size/2, hand.Y * _bitmap.Height - size / 2, size, size);
					}

					if (userHands.RightHand != null)
					{
						HandContent hand = userHands.RightHand.Value;
						int size = hand.Click ? 20 : 30;
						Brush brush = new SolidBrush(Color.DarkBlue);
						args.Graphics.FillEllipse(brush, hand.X * _bitmap.Width - size/2, hand.Y * _bitmap.Height - size / 2, size, size);
					}
				}
			}

			// Update Form
			this.Invalidate();
		}

		private void onIssueDataUpdate(IssuesData issuesData)
		{
			_issuesData = issuesData;
		}

		// Event handler for the DepthSensorUpdate event
		private void onDepthSensorUpdate(DepthFrame depthFrame)
		{
			_depthFrame = depthFrame;
		}

		// Event handler for the ColorSensorUpdate event
		private void onColorSensorUpdate(ColorFrame colorFrame)
		{
			if (!_visualizeColorImage)
				return;

			_colorStreamEnabled = true;

			float wStep = (float)_bitmap.Width / colorFrame.Cols;
			float hStep = (float)_bitmap.Height / colorFrame.Rows;
			
			float nextVerticalBorder = hStep;
			
			Byte[] data = colorFrame.Data;
			int colorPtr = 0;
			int bitmapPtr = 0;
			const int elemSizeInBytes = 3;

			for (int i = 0; i < _bitmap.Height; ++i)
			{
				if (i == (int)nextVerticalBorder)
				{
					colorPtr += colorFrame.Cols * elemSizeInBytes;
					nextVerticalBorder += hStep;
				}

				int offset = 0;
				int argb = data[colorPtr]
					| (data[colorPtr + 1] << 8)
					| (data[colorPtr + 2] << 16)
					| (0xFF << 24);
				float nextHorizontalBorder = wStep;
				for (int j = 0; j < _bitmap.Width; ++j)
				{
					if (j == (int)nextHorizontalBorder)
					{
						offset += elemSizeInBytes;
						argb = data[colorPtr + offset]
							| (data[colorPtr + offset + 1] << 8)
							| (data[colorPtr + offset + 2] << 16)
							| (0xFF << 24);
						nextHorizontalBorder += wStep;
					}

					_bitmap.Bits[bitmapPtr++] = argb;
				}
			}
		}

		// Event handler for the UserTrackerUpdate event
		private void onUserTrackerUpdate(UserFrame userFrame)
		{
			if (_visualizeColorImage && _colorStreamEnabled)
				return;
			if (_depthFrame == null)
				return;

			const int MAX_LABELS = 7;
			bool[] labelIssueState = new bool[MAX_LABELS];
			for (UInt16 label = 0; label < MAX_LABELS; ++label)
			{
				labelIssueState[label] = false;
				if (_issuesData != null)
				{
					FrameBorderIssue frameBorderIssue = _issuesData.GetUserIssue<FrameBorderIssue>(label);
					labelIssueState[label] = (frameBorderIssue != null);
				}
			}

			float wStep = (float)_bitmap.Width / _depthFrame.Cols;
			float hStep = (float)_bitmap.Height / _depthFrame.Rows;

			float nextVerticalBorder = hStep;

			Byte[] dataDepth = _depthFrame.Data;
			Byte[] dataUser = userFrame.Data;
			int dataPtr = 0;
			int bitmapPtr = 0;
			const int elemSizeInBytes = 2;
			for (int i = 0; i < _bitmap.Height; ++i)
			{
				if (i == (int)nextVerticalBorder)
				{
					dataPtr += _depthFrame.Cols * elemSizeInBytes;
					nextVerticalBorder += hStep;
				}

				int offset = 0;
				int argb = 0;
				int label = dataUser[dataPtr] | dataUser[dataPtr + 1] << 8;
				int depth = Math.Min(255, (dataDepth[dataPtr] | dataDepth[dataPtr + 1] << 8) / 32);
				float nextHorizontalBorder = wStep;
				for (int j = 0; j < _bitmap.Width; ++j)
				{
					if (j == (int)nextHorizontalBorder)
					{
						offset += elemSizeInBytes;
						label = dataUser[dataPtr + offset] | dataUser[dataPtr + offset + 1] << 8;
						if (label == 0)
							depth = Math.Min(255, (dataDepth[dataPtr + offset] | dataDepth[dataPtr + offset + 1] << 8) / 32);
						nextHorizontalBorder += wStep;
					}

					if (label > 0)
					{
						int user = label * 40;
						if (!labelIssueState[label])
							user += 40;
						argb = 0 | (user << 8) | (0 << 16) | (0xFF << 24);
					}
					else
					{
						argb = depth | (depth << 8) | (depth << 16) | (0xFF << 24);
					}

					_bitmap.Bits[bitmapPtr++] = argb;
				}
			}
		}

		// Event handler for the SkeletonUpdate event
		private void onSkeletonUpdate(SkeletonData skeletonData)
		{
			_skeletonData = skeletonData;
		}

		// Event handler for the HandTrackerUpdate event
		private void onHandTrackerUpdate(HandTrackerData handTrackerData)
		{
			_handTrackerData = handTrackerData;
		}

		// Event handler for the gesture detection event
		private void onNewGestures(GestureData gestureData)
		{
			// Display the information about detected gestures in the console
			foreach (var gesture in gestureData.Gestures)
				Console.WriteLine("Recognized {0} from user {1}", gesture.Type.ToString(), gesture.UserID);
		}
	}
}
