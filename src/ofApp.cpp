#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//get back a list of devices.
	vector<ofVideoDevice> devices = cam_grabber_.listDevices();

	for (size_t i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			//log the device
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else {
			//log the device and note it as unavailable
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}

	cam_grabber_.setDeviceID(0);
	cam_grabber_.setDesiredFrameRate(60);

	auto w = 960;
	auto h = 720;
	cam_grabber_.setup(w, h);
	frame_.allocate(w, h);

	motion_detector_.setup(w, h, 50, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam_grabber_.update();

	if (cam_grabber_.isFrameNew())
	{
		frame_.setFromPixels(cam_grabber_.getPixels());

		motion_detector_.update(frame_);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::lightBlue, ofColor::blue);

	motion_detector_.draw(25, 25, 960, 720);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
