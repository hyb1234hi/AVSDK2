﻿/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MODULES_VIDEO_PROCESSING_BRIGHTEN_H_
#define WEBRTC_MODULES_VIDEO_PROCESSING_BRIGHTEN_H_

#include "webrtc/modules/video_processing/include/video_processing.h"
#include "webrtc/typedefs.h"

namespace youme {
namespace webrtc {
namespace VideoProcessing {

int32_t Brighten(VideoFrame* frame, int delta);

}  // namespace VideoProcessing
}  // namespace webrtc
}  // namespace youme

#endif  // WEBRTC_MODULES_VIDEO_PROCESSING_BRIGHTEN_H_
