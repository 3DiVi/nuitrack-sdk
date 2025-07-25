#pragma once

#include <nuitrack/Nuitrack.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#if defined(ANDROID) || defined(__ANDROID__)
#include <GLES/gl.h>
#else
#include <GL/gl.h>
#endif

#include <string>


enum  ViewMode
{
	DEPTH_SEGMENT_MODE = 0,
	RGB_MODE = 1,
	MODES_MAX_COUNT
};



// Main class of the sample
class NuitrackGLSample final
{
public:
	NuitrackGLSample();
	~NuitrackGLSample();
	
	// Initialize sample: initialize Nuitrack, create all required modules,
	// register callbacks and start Nuitrack
	void init(const std::string& config = "");
	
	// Update the depth map, tracking and gesture recognition data,
	// then redraw the view
	bool update();
	
	// Release all sample resources
	void release();

	void nextViewMode()
	{
		_viewMode = ViewMode((uint32_t(_viewMode) + 1) % _modesNumber);
	}

	tdv::nuitrack::OutputMode getOutputMode() const
	{
		return _outputMode;
	}

private:
	int _width, _height;
	
	// GL data
	GLuint _textureID;
	uint8_t* _textureBuffer;
	GLfloat _textureCoords[8];
	GLfloat _vertexes[8];
	std::vector<GLfloat> _lines;
	std::vector<GLfloat> _leftHandPointers;
	std::vector<GLfloat> _rightHandPointers;
	std::vector<tdv::nuitrack::Gesture> _userGestures;
	
	tdv::nuitrack::OutputMode _outputMode;
	
	tdv::nuitrack::DepthSensor::Ptr _depthSensor;
	tdv::nuitrack::ColorSensor::Ptr _colorSensor;
	tdv::nuitrack::UserTracker::Ptr _userTracker;
	tdv::nuitrack::SkeletonTracker::Ptr _skeletonTracker;
	tdv::nuitrack::HandTracker::Ptr _handTracker;
	tdv::nuitrack::GestureRecognizer::Ptr _gestureRecognizer;
	
	tdv::nuitrack::IssuesData::Ptr _issuesData;
	uint64_t _onIssuesUpdateHandler;
	
	ViewMode _viewMode;
	uint32_t _modesNumber;
	bool _isInitialized;

	/**
	 * Nuitrack callbacks
	 */
	void onNewDepthFrame(tdv::nuitrack::DepthFrame::Ptr frame);
	void onNewRGBFrame(tdv::nuitrack::RGBFrame::Ptr frame);
	void onUserUpdateCallback(tdv::nuitrack::UserFrame::Ptr frame);
	static void onNewUserCallback(int id);
	static void onLostUserCallback(int id);
	void onSkeletonUpdate(const tdv::nuitrack::SkeletonData::Ptr &userSkeletons);
	void onHandUpdate(const tdv::nuitrack::HandTrackerData::Ptr &handData);
	void onIssuesUpdate(const tdv::nuitrack::IssuesData::Ptr &issuesData);
	static void onNewGesture(const tdv::nuitrack::GestureData::Ptr &gestureData);
	
	/**
	 * Draw methods
	 */
	void drawSkeleton(const std::vector<tdv::nuitrack::Joint>& joints);
	void drawBone(const tdv::nuitrack::Joint& j1, const tdv::nuitrack::Joint& j2);
	void renderTexture();
	void renderLines() const;

	static int power2(int n);
	void initTexture(int width, int height);
};
