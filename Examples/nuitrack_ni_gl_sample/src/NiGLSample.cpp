#include "NiGLSample.h"

#include <cstring>
#include <stdexcept>
#include <iostream>

std::deque<XnPoint3D> handGenHistory[50];

void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& userGen, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("[%d] New User %d\n", epochTime, nId);

	userGen.GetSkeletonCap().RequestCalibration(nId, TRUE);
}

void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& userGen, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	userGen.GetSkeletonCap().StopTracking(nId);

	printf("[%d] Lost user %d\n", epochTime, nId);
}

void XN_CALLBACK_TYPE PoseDetected(xn::PoseDetectionCapability& pose, const XnChar* strPose, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("[%d] Pose %s detected for user %d\n", epochTime, strPose, nId);
}

void XN_CALLBACK_TYPE CalibrationStarted(xn::SkeletonCapability& skeletonCap, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("[%d] Calibration started for user %d\n", epochTime, nId);
}

void XN_CALLBACK_TYPE CalibrationCompleted(xn::SkeletonCapability& skeletonCap, XnUserID nId, XnCalibrationStatus eStatus, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);

	if (eStatus == XN_CALIBRATION_STATUS_OK)
	{
		printf("[%d] Calibration complete, start tracking user %d\n", epochTime, nId);
		skeletonCap.StartTracking(nId);
	}
	else
	{
		printf("[%d] Calibration failed for user %d\n", epochTime, nId);
	}
}

void XN_CALLBACK_TYPE Hand_Create(xn::HandsGenerator& handsGen, XnUserID nId, const XnPoint3D *pPosition, XnFloat fTime, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	const char* hands[] = {"left", "right"};
	printf("[%d] New Hand (%s) for user %d\n", epochTime, hands[nId & 1], nId / 2);
}

void XN_CALLBACK_TYPE Hand_Update(xn::HandsGenerator& handsGen, XnUserID nId, const XnPoint3D *pPosition, XnFloat fTime, void* pCookie)
{
	handGenHistory[nId].push_back(*pPosition);
	if (handGenHistory[nId].size() > 10)
		handGenHistory[nId].pop_front();
}

void XN_CALLBACK_TYPE Hand_Destroy(xn::HandsGenerator& handsGen, XnUserID nId, XnFloat fTime, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	const char* hands[] = {"left", "right"};
	printf("[%d] Lost Hand (%s) for user %d\n", epochTime, hands[nId & 1], nId / 2);
}

void XN_CALLBACK_TYPE Gesture_Recognized(xn::GestureGenerator& gestureGen,
                                        const XnChar* strGesture,
                                        const XnPoint3D* pIDPosition,
                                        const XnPoint3D* pEndPosition,
                                        void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("[%d] Gesture recognized: \"%s\"\n", epochTime, strGesture);
}

NiGLSample::NiGLSample() :
	_textureID(0),
	_textureBuffer(0),
	_width(640),
	_height(480)
{}

NiGLSample::~NiGLSample()
{
	release();
}

void NiGLSample::init()
{
	XnStatus status = XN_STATUS_OK;
	
	status = _context.Init();
	if (status != XN_STATUS_OK )
	{
		std::cerr << "Can't init OpenNI context" << std::endl;
		exit(-1);
	}
	
	status = _depthGen.Create(_context);
	if (status != XN_STATUS_OK)
	{
		std::cerr << "Can't create depth generator with error: " << xnGetStatusString(status) << std::endl;
		exit(-1);
	}
	
	status = _sceneAnalyzer.Create(_context);
	if (status != XN_STATUS_OK)
	{
		std::cerr << "Can't create scene analyzer" << std::endl;
		exit(-1);
	}
	
	status = _userGen.Create(_context);
	if (status != XN_STATUS_OK)
	{
		std::cerr << "Can't create user generator" << std::endl;
		exit(-1);
	}
	
	XnCallbackHandle hUserCB, hCalibrationStartCB, hCalibrationCompleteCB, hPoseCB;
	_userGen.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCB);
	_userGen.GetSkeletonCap().RegisterToCalibrationStart(CalibrationStarted, NULL, hCalibrationStartCB);
	_userGen.GetSkeletonCap().RegisterToCalibrationComplete(CalibrationCompleted, NULL, hCalibrationCompleteCB);
	_userGen.GetPoseDetectionCap().RegisterToPoseDetected(PoseDetected, NULL, hPoseCB);
	_userGen.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
	
	status = _handsGen.Create(_context);
	if (status != XN_STATUS_OK)
	{
		std::cerr << "Can't create hand generator" << std::endl;
	}
	else
	{
		XnCallbackHandle hCallback;
		_handsGen.RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL, hCallback);
	}
	
	status = _gestureGen.Create(_context);
	if(status != XN_STATUS_OK)
	{
		std::cerr << "Can't create gesture generator" << std::endl;
	}
	else
	{
		XnCallbackHandle gCallback;
		_gestureGen.RegisterGestureCallbacks(Gesture_Recognized, NULL, NULL, gCallback);
	}

	_context.SetGlobalMirror(true);
	
	_depthGen.GetMapOutputMode(_outputMode);
	
	_wStep = _width / _outputMode.nXRes;
	_hStep = _height / _outputMode.nYRes;

	initTexture(_width, _height);
	
	_context.StartGeneratingAll();
}

bool NiGLSample::update()
{
	try
	{
		_context.WaitAnyUpdateAll();
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return false;
	}
	
	updateDepthMap();
	
	updateUserMap();
	
	updateSkeletons();
	
	updateHands();
	
	renderTexture();
	renderLines();
	
	return true;
}

void NiGLSample::release()
{
	_gestureGen.Release();
	_handsGen.Release();
	_userGen.Release();
	_sceneAnalyzer.Release();
	_depthGen.Release();
	
	_context.Release();
}

void NiGLSample::updateDepthMap()
{
	xn::DepthMetaData depthMD;
	_depthGen.GetMetaData(depthMD);
	const XnDepthPixel* depthPtr = depthMD.Data();
	
	uint8_t* texturePtr = _textureBuffer;
	
	int next_i_border = _hStep;
	
	for (size_t i = 0; i < _height; ++i)
	{
		if (i == next_i_border)
		{
			next_i_border += _hStep;
			depthPtr += depthMD.FullXRes();
		}
		
		int col = 0;
		int next_j_border = _wStep;
		uint16_t depthValue = *depthPtr >> 5;
		
		for (size_t j = 0; j < _width; ++j, texturePtr += 3)
		{
			if (j == next_j_border)
			{
				++col;
				next_j_border += _wStep;
				depthValue = *(depthPtr + col) >> 5;
			}
			
			texturePtr[0] = depthValue;
			texturePtr[1] = depthValue;
			texturePtr[2] = depthValue;
		}
	}
}

void NiGLSample::updateUserMap()
{
	xn::SceneMetaData sceneMD;
	_sceneAnalyzer.GetMetaData(sceneMD);
	
	static uint8_t colors[8][3] =
	{
	    {255, 0, 0},
	    {0, 255, 0},
	    {0, 0, 255},
	    {255, 255, 0},
	    
	    {0, 255, 255},
	    {255, 0, 255},
	    {255, 255, 255},
	    {127, 255, 0}
	};
	
	uint8_t* texturePtr = _textureBuffer;
	const uint16_t* labelPtr = sceneMD.Data();
	
	int next_i_border = _hStep;
	
	for (size_t i = 0; i < _height; ++i)
	{
		if (i == next_i_border)
		{
			next_i_border += _hStep;
			labelPtr += sceneMD.FullXRes();
		}
		
		int col = 0;
		int next_j_border = _wStep;
		uint16_t label = *labelPtr;
		
		for (size_t j = 0; j < _width; ++j, texturePtr += 3)
		{
			if (j == next_j_border)
			{
				++col;
				next_j_border += _wStep;
				label = *(labelPtr + col);
			}
			
			if (label)
			{
				texturePtr[0] = colors[label & 7][0];
				texturePtr[1] = colors[label & 7][1];
				texturePtr[2] = colors[label & 7][2];
			}
		}
	}
}

void NiGLSample::updateSkeletons()
{
	_lines.clear();
	
	XnUserID aUsers[15];
	XnUInt16 nUsers = 15;
	XnSkeletonJointPosition joints_positions[25];
	_userGen.GetUsers(aUsers, nUsers);
	for (int u = 0; u < nUsers; ++u)
	{
		int uid = aUsers[u];
		if (_userGen.GetSkeletonCap().IsTracking(uid))
		{
			for (int i = 0; i < 25; ++i)
			{
				_userGen.GetSkeletonCap().GetSkeletonJointPosition(uid, (XnSkeletonJoint)i, joints_positions[i]);
			}
			if (std::string(_userGen.GetInfo().GetDescription().strVendor) == "3DiVi")
				drawSkeleton(joints_positions);
			if (std::string(_userGen.GetInfo().GetDescription().strVendor) == "PrimeSense")
				drawSkeletonNITE(joints_positions);
		}
	}
}

void NiGLSample::updateHands()
{
	_leftHandPointers.clear();
	_rightHandPointers.clear();
	
	XnUserID aUsers[15];
	XnUInt16 nUsers = 15;
	_userGen.GetUsers(aUsers, nUsers);
	for (int u = 0; u < nUsers; ++u)
	{
		int uid = aUsers[u];

		for(int i = 0; i < (int)handGenHistory[uid * 2].size() - 1; i++)
		{
			XnPoint3D pos = handGenHistory[uid * 2][i];
			XnPoint3D projPos;
			_depthGen.ConvertRealWorldToProjective(1, &pos, &projPos);

			_leftHandPointers.push_back(projPos.X * _wStep);
			_leftHandPointers.push_back(projPos.Y * _hStep);
			
			pos = handGenHistory[uid * 2][i + 1];
			_depthGen.ConvertRealWorldToProjective(1, &pos, &projPos);
			
			_leftHandPointers.push_back(projPos.X * _wStep);
			_leftHandPointers.push_back(projPos.Y * _hStep);
		}

		for(int i = 0; i < (int)handGenHistory[uid * 2 + 1].size() - 1; i++)
		{
			XnPoint3D pos = handGenHistory[uid * 2 + 1][i];
			XnPoint3D projPos;
			_depthGen.ConvertRealWorldToProjective(1, &pos, &projPos);

			_rightHandPointers.push_back(projPos.X * _wStep);
			_rightHandPointers.push_back(projPos.Y * _hStep);
			
			pos = handGenHistory[uid * 2 + 1][i + 1];
			_depthGen.ConvertRealWorldToProjective(1, &pos, &projPos);
			
			_rightHandPointers.push_back(projPos.X * _wStep);
			_rightHandPointers.push_back(projPos.Y * _hStep);
		}
	}
}

void NiGLSample::drawSkeleton(const XnSkeletonJointPosition joints[])
{
	drawBone(joints[XN_SKEL_HEAD], joints[XN_SKEL_NECK]);
	drawBone(joints[XN_SKEL_NECK], joints[XN_SKEL_LEFT_COLLAR]);
	drawBone(joints[XN_SKEL_LEFT_COLLAR], joints[XN_SKEL_TORSO]);
	drawBone(joints[XN_SKEL_LEFT_COLLAR], joints[XN_SKEL_LEFT_SHOULDER]);
	drawBone(joints[XN_SKEL_LEFT_COLLAR], joints[XN_SKEL_RIGHT_SHOULDER]);
	drawBone(joints[XN_SKEL_WAIST], joints[XN_SKEL_LEFT_HIP]);
	drawBone(joints[XN_SKEL_WAIST], joints[XN_SKEL_RIGHT_HIP]);
	drawBone(joints[XN_SKEL_TORSO], joints[XN_SKEL_WAIST]);
	drawBone(joints[XN_SKEL_LEFT_SHOULDER], joints[XN_SKEL_LEFT_ELBOW]);
	drawBone(joints[XN_SKEL_LEFT_ELBOW], joints[XN_SKEL_LEFT_WRIST]);
	drawBone(joints[XN_SKEL_LEFT_WRIST], joints[XN_SKEL_LEFT_HAND]);
	drawBone(joints[XN_SKEL_RIGHT_SHOULDER], joints[XN_SKEL_RIGHT_ELBOW]);
	drawBone(joints[XN_SKEL_RIGHT_ELBOW], joints[XN_SKEL_RIGHT_WRIST]);
	drawBone(joints[XN_SKEL_RIGHT_WRIST], joints[XN_SKEL_RIGHT_HAND]);
	drawBone(joints[XN_SKEL_RIGHT_HIP], joints[XN_SKEL_RIGHT_KNEE]);
	drawBone(joints[XN_SKEL_LEFT_HIP], joints[XN_SKEL_LEFT_KNEE]);
	drawBone(joints[XN_SKEL_RIGHT_KNEE], joints[XN_SKEL_RIGHT_ANKLE]);
	drawBone(joints[XN_SKEL_LEFT_KNEE], joints[XN_SKEL_LEFT_ANKLE]);
}

void NiGLSample::drawSkeletonNITE(const XnSkeletonJointPosition joints[])
{
	drawBone(joints[XN_SKEL_HEAD], joints[XN_SKEL_NECK]);
	drawBone(joints[XN_SKEL_NECK], joints[XN_SKEL_LEFT_SHOULDER]);
	drawBone(joints[XN_SKEL_LEFT_SHOULDER], joints[XN_SKEL_LEFT_ELBOW]);
	drawBone(joints[XN_SKEL_LEFT_ELBOW], joints[XN_SKEL_LEFT_HAND]);
	drawBone(joints[XN_SKEL_NECK], joints[XN_SKEL_RIGHT_SHOULDER]);
	drawBone(joints[XN_SKEL_RIGHT_SHOULDER], joints[XN_SKEL_RIGHT_ELBOW]);
	drawBone(joints[XN_SKEL_RIGHT_ELBOW], joints[XN_SKEL_RIGHT_HAND]);
	drawBone(joints[XN_SKEL_LEFT_SHOULDER], joints[XN_SKEL_TORSO]);
	drawBone(joints[XN_SKEL_RIGHT_SHOULDER], joints[XN_SKEL_TORSO]);
	drawBone(joints[XN_SKEL_TORSO], joints[XN_SKEL_LEFT_HIP]);
	drawBone(joints[XN_SKEL_LEFT_HIP], joints[XN_SKEL_LEFT_KNEE]);
	drawBone(joints[XN_SKEL_LEFT_KNEE], joints[XN_SKEL_LEFT_FOOT]);
	drawBone(joints[XN_SKEL_TORSO], joints[XN_SKEL_RIGHT_HIP]);
	drawBone(joints[XN_SKEL_RIGHT_HIP], joints[XN_SKEL_RIGHT_KNEE]);
	drawBone(joints[XN_SKEL_RIGHT_KNEE], joints[XN_SKEL_RIGHT_FOOT]);
}

void NiGLSample::drawBone(const XnSkeletonJointPosition &j1, const XnSkeletonJointPosition &j2)
{
	XnPoint3D pos[2] = {j1.position, j2.position};
	XnPoint3D projPos[2];
	
	_depthGen.ConvertRealWorldToProjective(2, pos, projPos);
	
	if (j1.fConfidence > 0.15 && j2.fConfidence > 0.15)
	{
		_lines.push_back(projPos[0].X * _wStep);
		_lines.push_back(projPos[0].Y * _hStep);
		_lines.push_back(projPos[1].X * _wStep);
		_lines.push_back(projPos[1].Y * _hStep);
	}
}

void NiGLSample::renderTexture()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, _textureBuffer);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, _vertexes);
	glTexCoordPointer(2, GL_FLOAT, 0, _textureCoords);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
}

void NiGLSample::renderLines()
{
	if (_lines.empty())
		return;
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glColor4f(1, 1, 1, 1);
	
	glLineWidth(6);
	
	glVertexPointer(2, GL_FLOAT, 0, _lines.data());
	glDrawArrays(GL_LINES, 0, _lines.size() / 2);
	
	glEnable(GL_POINT_SMOOTH);
	glPointSize(16);
	
	glVertexPointer(2, GL_FLOAT, 0, _lines.data());
	glDrawArrays(GL_POINTS, 0, _lines.size() / 2);
	
	if (!_leftHandPointers.empty())
	{
		glColor4f(1, 0, 0, 1);
		glLineWidth(3);
		glVertexPointer(2, GL_FLOAT, 0, _leftHandPointers.data());
		glDrawArrays(GL_LINES, 0, _leftHandPointers.size() / 2);
	}
	
	if (!_rightHandPointers.empty())
	{
		glColor4f(0, 0, 1, 1);
		glLineWidth(3);
		glVertexPointer(2, GL_FLOAT, 0, _rightHandPointers.data());
		glDrawArrays(GL_LINES, 0, _rightHandPointers.size() / 2);
	}
	
	glColor4f(1, 1, 1, 1);
	glLineWidth(1);
	glPointSize(1);
	glDisable(GL_POINT_SMOOTH);
	
	glDisableClientState(GL_VERTEX_ARRAY);
}

int NiGLSample::power2(int n)
{
	unsigned int m = 2;
	while (m < n)
		m <<= 1;
	
	return m;
}

void NiGLSample::initTexture(int width, int height)
{
	glGenTextures(1, &_textureID);
	
	width = power2(width);
	height = power2(height);
	
	if (_textureBuffer != 0)
		delete[] _textureBuffer;
	
	_textureBuffer = new uint8_t[width * height * 3];
	memset(_textureBuffer, 0, sizeof(uint8_t) * width * height * 3);
	
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Set texture coordinates [0, 1] and vertexes position
	{
		_textureCoords[0] = (float) _width / width;
		_textureCoords[1] = (float) _height / height;
		_textureCoords[2] = (float) _width / width;
		_textureCoords[3] = 0.0;
		_textureCoords[4] = 0.0;
		_textureCoords[5] = 0.0;
		_textureCoords[6] = 0.0;
		_textureCoords[7] = (float) _height / height;
		
		_vertexes[0] = _width;
		_vertexes[1] = _height;
		_vertexes[2] = _width;
		_vertexes[3] = 0.0;
		_vertexes[4] = 0.0;
		_vertexes[5] = 0.0;
		_vertexes[6] = 0.0;
		_vertexes[7] = _height;
	}
}


