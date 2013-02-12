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
#include "ofMain.h"
#include "ofxNFCReader.h"

#include <nfc/nfc.h>
//--------------------------------------------------------------------
ofxNFCReader::ofxNFCReader() {
  deviceId = -1;
  bIsTagNew = false;
  pnd = NULL;
}

//--------------------------------------------------------------------
ofxNFCReader::~ofxNFCReader() {
	close();
}

//--------------------------------------------------------------------
bool ofxNFCReader::open(int id) {

  nfc_init(&context);

  pnd = nfc_open(context, NULL);

  if (pnd == NULL) {
    ofLog(OF_LOG_ERROR, "Unable to open NFC device.");
    return false;
  }

  if (nfc_initiator_init(pnd) < 0) {
    nfc_perror(pnd, "nfc_initiator_init");
    pnd = NULL;
    return false;
  }

  ofLog(OF_LOG_NOTICE, "NFC reader: %s opened\n", nfc_device_get_name(pnd));

	startThread(true, false); // blocking, not verbose
  return true;
}

//--------------------------------------------------------------------
void ofxNFCReader::close() {
	if(isThreadRunning()) {
		waitForThread(true);
	}
  nfc_close(pnd);
  nfc_exit(context);
}

//--------------------------------------------------------------------
bool ofxNFCReader::isConnected() {
  return (pnd != NULL);
}

//--------------------------------------------------------------------
bool ofxNFCReader::isTagNew() {
  return bIsTagNew;
}

//--------------------------------------------------------------------
uint64_t ofxNFCReader::getTagUID() {
  bIsTagNew = false;
  return targetUid;
}

//--------------------------------------------------------------------
void ofxNFCReader::threadedFunction() {
  if (!isConnected()){
    ofLog(OF_LOG_WARNING,"ofxNFCReader: Can't read tag. No device connected.");
    return ;
  }
  const uint8_t uiPollNr = 0xFF;
  const uint8_t uiPeriod = 1;
  const size_t szModulations = 1;
  const nfc_modulation nmModulations[szModulations] = {
    {NMT_ISO14443A, NBR_106 },
    /*
    {NMT_ISO14443B, NBR_106 },
    {NMT_FELICA, NBR_212 },
    {NMT_FELICA, NBR_424 },
    {NMT_JEWEL, NBR_106 },
    */
  };

  nfc_target nt;
  int res = 0;

	while(isThreadRunning()) {
    ofLog(OF_LOG_NOTICE, "NFC device will poll during %ld ms (%u pollings of %lu ms for %zd modulations)\n", (unsigned long) uiPollNr * szModulations * uiPeriod * 150, uiPollNr, (unsigned long) uiPeriod * 150, szModulations);
    if ((res = nfc_initiator_poll_target(pnd, nmModulations, szModulations, uiPollNr, uiPeriod, &nt))  < 0) {
      nfc_perror(pnd, "nfc_initiator_poll_target");
    }

    if (res > 0) {
      // print target: tag found
      bool verbose = false;
      char *s;
      str_nfc_target(&s, nt, verbose);
      ofLog(OF_LOG_NOTICE, s);
      free(s);

      // get uid
      if (nt.nm.nmt == NMT_ISO14443A){
        uint64_t uid = 0;
        int len = nt.nti.nai.szUidLen;
        uint8_t* src = nt.nti.nai.abtUid;
        while (len--)
        {
          uid = (uid << 8) | (*src);
          src++;
        }
        //cout << "length: " <<nt.nti.nai.szUidLen<<endl; 
        //cout << "uid: " << uid << endl; 
        bIsTagNew = true;
        if (uid == targetUid){
          ofNotifyEvent(tagAliveEvent, uid, this);
        } else{
          ofNotifyEvent(newTagEvent, uid, this);
        }
        targetUid = uid;
      }
      else {
        ofLog(OF_LOG_WARNING,"ofxNFCReader: Can't get UID. Tag is not of type  ISO 14443A");
      }
    } else {
      ofLog(OF_LOG_NOTICE, "No target found.\n");
      if (targetUid != -1){
          ofNotifyEvent(tagLeftEvent, targetUid, this);
          targetUid = -1;
      }

    }
  }
  return;
}

//--------------------------------------------------------------------
int ofxNFCReader::getDeviceId() {
}

//static
//--------------------------------------------------------------------
int ofxNFCReader::numTotalDevices() {
}

//static
//--------------------------------------------------------------------
int ofxNFCReader::numAvailableDevices() {
}

//static
//--------------------------------------------------------------------
int ofxNFCReader::numConnectedDevices() {
}

//static
//--------------------------------------------------------------------
bool ofxNFCReader::isDeviceConnected(int id) {
}

//static
//--------------------------------------------------------------------
int ofxNFCReader::nextAvailableId() {
}

