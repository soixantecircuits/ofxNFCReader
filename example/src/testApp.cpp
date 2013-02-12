#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  NFCReader.open();
	ofAddListener(NFCReader.newTagEvent, this, &testApp::onNewTag);
	ofAddListener(NFCReader.tagAliveEvent, this, &testApp::onTagAlive);
	ofAddListener(NFCReader.tagLeftEvent, this, &testApp::onTagLeft);

	font.loadFont("verdana.ttf", 64, true, true);
	font.setLineHeight(60.0f);
	font.setLetterSpacing(1.035);
  ofSetWindowShape(1024, 240);
}

//--------------------------------------------------------------
void testApp::onNewTag(uint64_t & uid){
  this->uid = uid;
  colorText = 225;
}

//--------------------------------------------------------------
void testApp::onTagAlive(uint64_t & uid){
  this->uid = uid;
  colorGreenLed = 255;
}

//--------------------------------------------------------------
void testApp::onTagLeft(uint64_t & uid){
  this->uid = uid;
  colorRedLed = 255;
}

//--------------------------------------------------------------
void testApp::update(){
  // Example if you use a flag warning for a new tag
  /*
  if (NFCReader.isTagNew()){
    uid = NFCReader.getTagUID();
    color = 225;
  }
  */

  if (colorText > 0){
    colorText--;
  }
  if (colorGreenLed > 0){
    colorGreenLed--;
  }
  if (colorRedLed > 0){
    colorRedLed--;
  }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(colorText);
	font.drawString("Welcome\n" + ofToHex(uid), 40, 120);
	ofSetColor(0, colorGreenLed, 0);
  ofEllipse(ofGetWidth() - 40, 20, 10, 10);
	ofSetColor(colorRedLed, 0, 0);
  ofEllipse(ofGetWidth() - 20, 20, 10, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
