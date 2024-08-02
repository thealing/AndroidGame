#pragma once

#include <android/log.h>

#include <android/native_activity.h>

#include <android/native_window.h>

#include <android/asset_manager.h>

#include <GLES/egl.h>

#include <SLES/OpenSLES.h>

#include <SLES/OpenSLES_Android.h>

#include <malloc.h>

#include <pthread.h>

extern AAssetManager* asset_manager;

extern JNIEnv* env;

extern jclass ByteArrayInputStream;

extern jclass Bitmap;

extern jclass BitmapFactory;

extern jmethodID ByteArrayInputStream_init;

extern jmethodID Bitmap_getWidth;

extern jmethodID Bitmap_getHeight;

extern jmethodID Bitmap_getPixels;

extern jmethodID BitmapFactory_decodeByteArray;

void platform_init(ANativeActivity* activity);
