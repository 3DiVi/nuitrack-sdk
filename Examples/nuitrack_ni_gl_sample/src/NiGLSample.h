#ifndef NIGLSAMPLE_H_
#define NIGLSAMPLE_H_

#include <XnCppWrapper.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef ANDROID
#include <GL/gl.h>
#else
#include <GLES/gl.h>
#endif

#include <deque>
#include <string>
#include <vector>

// Main class of the sample
class NiGLSample final
{
public:
	NiGLSample();
	~NiGLSample();
	
	// Initialize sample: create the OpenNI context and all required nodes,
	// register callbacks and start the data generation process
	void init();
	
	// Update the depth map and tracking data, then redraw the view
	bool update();
	
	// Release OpenNI nodes and the context
	void release();
	
private:
	int _width, _height;
	int _wStep, _hStep;
	
	// GL data
	GLuint _textureID;
	uint8_t* _textureBuffer;
	GLfloat _textureCoords[8];
	GLfloat _vertexes[8];
	std::vector<GLfloat> _lines;
	std::vector<GLfloat> _leftHandPointers;
	std::vector<GLfloat> _rightHandPointers;
	
	// OpenNI data
	XnMapOutputMode _outputMode;
	
	xn::Context _context;
	xn::DepthGenerator _depthGen;
	xn::SceneAnalyzer _sceneAnalyzer;
	xn::UserGenerator _userGen;
	xn::HandsGenerator _handsGen;
	xn::GestureGenerator _gestureGen;
	
	void updateDepthMap();
	void updateUserMap();
	void updateSkeletons();
	void updateHands();
	
	// Draw methods
	void drawSkeleton(const XnSkeletonJointPosition joints[]);
	void drawSkeletonNITE(const XnSkeletonJointPosition joints[]);
	void drawBone(const XnSkeletonJointPosition& j1, const XnSkeletonJointPosition& j2);
	void renderTexture();
	void renderLines();
	
	int power2(int n);
	void initTexture(int width, int height);
};

#endif
