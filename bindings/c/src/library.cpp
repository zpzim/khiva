// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_c/library.h>
#include <cstring>

void backend_info(char **info) { strcpy(*info, khiva::library::backendInfo().c_str()); }

void set_backend(int *backend) { khiva::library::setBackend(static_cast<khiva::library::Backend>(*backend)); }

void get_backend(int *backend) { *backend = static_cast<int>(khiva::library::getBackend()); }

void get_backends(int *backends) { *backends = khiva::library::getBackends(); }

void set_device(int *device) { khiva::library::setDevice(*device); }

void get_device_id(int *device_id) { *device_id = khiva::library::getDevice(); }

void get_device_count(int *device_count) { *device_count = khiva::library::getDeviceCount(); }

void setDeviceMemoryInGB(double *memory) { khiva::library::setDeviceMemoryInGB(*memory); }

void version(char **v) { strcpy(*v, khiva::version().c_str()); }
