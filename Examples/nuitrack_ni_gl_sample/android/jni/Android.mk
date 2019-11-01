LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE	:=	nuitrack_gl_sample

NUITRACK_INCLUDE_PATH	:=	../../../../Nuitrack/include
NUITRACK_LIBRARY_PATH	:=	../../../../Nuitrack/lib/android

OPEN_NI_INCLUDE	:= ../../OpenNI/Include
OPEN_NI_LIBRARY_DIR	:= ../../../../Nuitrack/lib/android

LOCAL_C_INCLUDES :=	../../src \
					$(NUITRACK_INCLUDE_PATH) \
					$(OPEN_NI_INCLUDE)

LOCAL_SRC_FILES :=	android_main.cpp \
					../../src/NiGLSample.cpp

LOCAL_LDLIBS	:=	-L$(NUITRACK_LIBRARY_PATH) -llog -landroid -lEGL -lGLESv1_CM -lnuitrack -lmiddleware -L$(OPEN_NI_LIBRARY_DIR) -lOpenNI
LOCAL_STATIC_LIBRARIES	:=	android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
