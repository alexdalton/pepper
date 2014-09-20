#
# WARNING: THIS FILE HAS BEEN GENERATED AUTOMATICALLY BY
# WALY TARGET SETUP.  IF YOU WANT TO EDIT, EDIT THE ORIGINAL
# IN target-files/android/WALY.Android.mk
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -Wall -DWALY_TARGET_ANDROID

LOCAL_MODULE    := libWALY
LOCAL_SRC_FILES := WALYButton.cpp WALYDigitDraw.cpp WALYEntryBox.cpp \
		   WALYEntryBoxIP.cpp WALYFilter.cpp WALYFont.cpp    \
		   WALYFrame.cpp WALYImage.cpp WALYNetwork.cpp       \
		   WALYPlatform.cpp WALYScreen.cpp WALYSound.cpp     \
		   WALYWidget.cpp
#LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_C_INCLUDES := ${LOCAL_PATH}/../libpng
LOCAL_CPP_FEATURES += exceptions

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,android/native_app_glue)
