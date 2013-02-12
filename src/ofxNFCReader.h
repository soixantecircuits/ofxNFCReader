/*==============================================================================

    Copyright (c) 2013 Soixante circuits

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
    
==============================================================================*/
#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include <nfc/nfc-types.h>

#if defined(_MSC_VER) || defined(_WIN32) || defined(WIN32) || defined(__MINGW32__)
    // do windows stuff
#else
    // mac and linux need this
    #include <libusb.h>
#endif

class ofxNFCReader: protected ofThread {
  public:
    ofxNFCReader();
    virtual ~ofxNFCReader();
    bool open (int id=-1);
    void close();
    bool isConnected();
    bool isTagNew();
    uint64_t getTagUID();

    /// get the device id
    /// returns -1 if not connected
    int getDeviceId();

    /// get the total number of devices
    static int numTotalDevices();

    /// get the number of available devices (not connected)
    static int numAvailableDevices();

    /// get the number of currently connected devices
    static int numConnectedDevices();

    /// is a device already connected?
    static bool isDeviceConnected(int id);

    /// get the id of the next available device,
    /// returns -1 if nothing found
    static int nextAvailableId();

    /// thread function
    void threadedFunction();
    
    ofEvent<uint64_t> newTagEvent;
    ofEvent<uint64_t> tagAliveEvent;
    ofEvent<uint64_t> tagLeftEvent;

  private:
    bool bIsTagNew;
    int deviceId;
    nfc_device *pnd;
    nfc_context *context;
    uint64_t targetUid;
};
