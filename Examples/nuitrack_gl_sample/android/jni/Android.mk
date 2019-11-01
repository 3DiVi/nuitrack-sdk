LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE	:=	nuitrack_gl_sample

NUITRACK_INCLUDE_PATH	:=	../../../../Nuitrack/include
NUITRACK_LIBRARY_PATH	:=	../../../../Nuitrack/lib/android	 

LOCAL_C_INCLUDES :=	../../src \
					$(NUITRACK_INCLUDE_PATH)

LOCAL_SRC_FILES :=	android_main.cpp \
					../../src/NuitrackGLSample.cpp

LOCAL_LDLIBS	:=	-L$(NUITRACK_LIBRARY_PATH) -llog -landroid -lEGL -lGLESv1_CM -lnuitrack
LOCAL_STATIC_LIBRARIES	:=	android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
