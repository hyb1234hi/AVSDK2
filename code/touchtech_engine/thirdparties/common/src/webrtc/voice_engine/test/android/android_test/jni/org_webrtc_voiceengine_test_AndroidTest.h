﻿/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_webrtc_voiceengine_test_AndroidTest */

#ifndef _Included_org_webrtc_voiceengine_test_AndroidTest
#define _Included_org_webrtc_voiceengine_test_AndroidTest
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    NativeInit
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_NativeInit
  (JNIEnv *, jclass);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    RunAutoTest
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_RunAutoTest
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    Create
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_Create
  (JNIEnv *, jobject);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    Delete
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_Delete
  (JNIEnv *, jobject);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    Init
 * Signature: (IIIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_Init
  (JNIEnv *, jobject, jboolean, jboolean);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    Terminate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_Terminate
  (JNIEnv *, jobject);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    CreateChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_CreateChannel
  (JNIEnv *, jobject);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    DeleteChannel
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_DeleteChannel
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetLocalReceiver
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetLocalReceiver
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetSendDestination
 * Signature: (IILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetSendDestination
  (JNIEnv *, jobject, jint, jint, jstring);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartListen
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartListen
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartPlayout
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartPlayout
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartSend
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartSend
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopListen
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopListen
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopPlayout
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopPlayout
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopSend
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopSend
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartPlayingFileLocally
 * Signature: (ILjava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartPlayingFileLocally
  (JNIEnv *, jobject, jint, jstring, jboolean);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopPlayingFileLocally
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopPlayingFileLocally
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartRecordingPlayout
 * Signature: (ILjava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartRecordingPlayout
  (JNIEnv *, jobject, jint, jstring, jboolean);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopRecordingPlayout
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopRecordingPlayout
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StartPlayingFileAsMicrophone
 * Signature: (ILjava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StartPlayingFileAsMicrophone
  (JNIEnv *, jobject, jint, jstring, jboolean);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    StopPlayingFileAsMicrophone
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_StopPlayingFileAsMicrophone
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    NumOfCodecs
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_NumOfCodecs
  (JNIEnv *, jobject);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetSendCodec
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetSendCodec
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetVADStatus
 * Signature: (IZI)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetVADStatus
  (JNIEnv *, jobject, jint, jboolean, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetNSStatus
 * Signature: (ZI)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetNSStatus
  (JNIEnv *, jobject, jboolean, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetAGCStatus
 * Signature: (ZI)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetAGCStatus
  (JNIEnv *, jobject, jboolean, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetECStatus
 * Signature: (ZI)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetECStatus
  (JNIEnv *, jobject, jboolean, jint);

/*
 * Class:     org_webrtc_voiceengine_test_AndroidTest
 * Method:    SetSpeakerVolume
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_webrtc_voiceengine_test_AndroidTest_SetSpeakerVolume
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
