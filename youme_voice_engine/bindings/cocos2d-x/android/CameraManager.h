//
//  CameraManager.h
//  youme_voice_engine
//
//  Created by 游密 on 2017/4/11.
//  Copyright © 2017年 Youme. All rights reserved.
//

#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "ICameraManager.hpp"


class CameraManager : public ICameraManager
{
private:
    static CameraManager *sInstance;
    CameraPreviewCallback *cameraPreviewCallback;
    IYouMeEventCallback *youmeEventCallback;
    CameraManager();
    bool enableFrontCamera = true;

public:
    static CameraManager *getInstance();
    
public:
    YouMeErrorCode registerCameraPreviewCallback(CameraPreviewCallback *cb) override;
    YouMeErrorCode unregisterCameraPreviewCallback();
    YouMeErrorCode registerYoumeEventCallback(IYouMeEventCallback *cb) override;
    YouMeErrorCode unregisterYoumeEventCallback() override;
    YouMeErrorCode startCapture() override;
    YouMeErrorCode stopCapture() override;
    YouMeErrorCode setCaptureProperty(float fFps, int nWidth, int nHeight) override;
    YouMeErrorCode setCaptureFrontCameraEnable(bool enable) override;
    bool isCaptureFrontCameraEnable() override;
    YouMeErrorCode switchCamera() override;
    YouMeErrorCode resetCamera() override;
    void openBeautify(bool open) override;
    void beautifyChanged(float param) override;
    void stretchFace(bool stretch) override;
    void setLocalVideoMirrorMode(YouMeVideoMirrorMode_t mirrorMode) override;

    bool isCameraZoomSupported() override;
    float setCameraZoomFactor(float zoomFactor) override;
    bool isCameraFocusPositionInPreviewSupported() override;
    bool setCameraFocusPositionInPreview( float x , float y ) override;
    bool isCameraTorchSupported() override;
    bool setCameraTorchOn( bool isOn ) override;
    bool isCameraAutoFocusFaceModeSupported() override;
    bool setCameraAutoFocusFaceModeEnabled( bool enable ) override;
    
    YouMeErrorCode videoDataOutput(void* data, int len, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp, int renderflag, int streamID = 0);
    YouMeErrorCode videoDataOutputGLESForAndroid(int texture, float* matrix,int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp, int renderflag);

private:
    float _beautyLevel = 0.0f;
    bool  _closeing = false;
    bool  openFailed = false;
};

#endif
