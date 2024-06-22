/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Fingerprint.h"

#include <android-base/logging.h>

#include <dlfcn.h>

namespace aidl {
namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {

bool Load::openHal(fingerprint_notify_t notify) {
    void* load = dlopen("fingerprint.goodix_fod.so", RTLD_NOW);

    if (load) {
        int err;
        fingerprint_close = reinterpret_cast<typeof(fingerprint_close)>(dlsym(load, "fingerprint_close"));
        fingerprint_open = reinterpret_cast<typeof(fingerprint_open)>(dlsym(load, "fingerprint_open"));
        set_notify_callback = reinterpret_cast<typeof(set_notify_callback)>(dlsym(load, "set_notify_callback"));
        fingerprint_request = reinterpret_cast<typeof(fingerprint_request)>(dlsym(load, "fingerprint_request"));

        if ((err = fingerprint_open(nullptr)) != 0) {
            LOG(ERROR) << "Can't open fingerprint, error: " << err;
            return false;
        }

        if ((err = set_notify_callback(notify)) != 0) {
            LOG(ERROR) << "Can't register fingerprint module callback, error: " << err;
            return false;
        }

        return true;
    }

    return false;
}

int Load::request(int cmd, int param) {
    // TO-DO: input, output handling not implemented
    int result = fingerprint_request(cmd, nullptr, 0, nullptr, 0, param);
    LOG(INFO) << "request(cmd=" << cmd << ", param=" << param << ", result=" << result << ")";
    return result;
}

} // namespace fingerprint
} // namespace biometrics
} // namespace hardware
} // namespace android
} // namespace aidl
