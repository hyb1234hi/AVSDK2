APP_STL := gnustl_static
APP_ABI := armeabi armeabi-v7a x86

NDK_TOOLCHAIN_VERSION := 4.9
ANDROID_API_LEVEL 	:= android-9
APP_PROJECT_PATH  	:= $(LOCAL_PATH)
APP_MODULES 	  	:= sqlite3

APP_CPPFLAGS := -frtti -DANDROID -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

ifeq ($(NDK_DEBUG),1)
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
