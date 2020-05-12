package com.youme.voiceengine.video;

/**
 * Created by fire on 2017/2/14.
 */

import android.annotation.TargetApi;
import android.content.Context;
import android.hardware.camera2.CameraManager;

@TargetApi(21)
public class Camera2Capturer extends CameraCapturer {
    private final Context context;
    private final CameraManager cameraManager;

    public Camera2Capturer(Context context, String cameraName, CameraEventsHandler eventsHandler) {
        super(cameraName, eventsHandler, new Camera2Enumerator(context));

        this.context = context;
        cameraManager = (CameraManager) context.getSystemService(Context.CAMERA_SERVICE);
    }

    @Override
    protected void createCameraSession(CameraSession.CreateSessionCallback createSessionCallback,
                                       CameraSession.Events events, Context applicationContext,
                                       SurfaceTextureHelper surfaceTextureHelper, String cameraName, int width, int height,
                                       int framerate) {
        Camera2Session.create(createSessionCallback, events, applicationContext, cameraManager,
                surfaceTextureHelper, cameraName, width, height, framerate);
    }
}
