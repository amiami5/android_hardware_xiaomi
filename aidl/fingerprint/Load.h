/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <hardware/fingerprint.h>

namespace aidl {
namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {

class Load {
public:
    bool openHal(fingerprint_notify_t notify);
    int request(int cmd, int param);

    int (*fingerprint_close)();
    int (*fingerprint_open)(const char* id);
    int (*set_notify_callback)(fingerprint_notify_t notify);
    int (*fingerprint_request)(uint32_t cmd, char *inBuf, uint32_t inBuf_length, char *outBuf, uint32_t outBuf_length, uint32_t param);
};

} // namespace fingerprint
} // namespace biometrics
} // namespace hardware
} // namespace android
} // namespace aidl
