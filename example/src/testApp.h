#pragma once

#include "ofMain.h"
#include "ofxNFCReader.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void onNewTag(uint64_t  & uid);
    void onTagAlive(uint64_t  & uid);
    void onTagLeft(uint64_t  & uid);

    ofxNFCReader NFCReader;
    uint64_t uid;
    ofTrueTypeFont	font;
    int colorText;
    int colorGreenLed;
    int colorRedLed;
};
