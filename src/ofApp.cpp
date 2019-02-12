#include "ofApp.h"
#include "cuda_perf.hpp"

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

	auto w = 640;
	auto h = 480;
	cam_grabber_.setup(w, h);
	frame_.allocate(w, h);

	motion_detector_.setup(w, h, 50, 5);
	contour_detector_.setup(w, h, 10);

	threshold_slider_.addListener(this, &ofApp::thresholdChanged);
	count_frames_.addListener(this, &ofApp::countFramesChanged);

	settings_panel_.setup("MotionDetectorSettings");
	settings_panel_.add(threshold_slider_.setup("threshold_motion", 80, 0, 255));
	settings_panel_.add(count_frames_.setup("number_of_frames", 1, 1, 10));
}

//--------------------------------------------------------------
void ofApp::update(){
	cam_grabber_.update();

	if (cam_grabber_.isFrameNew())
	{
		frame_.setFromPixels(cam_grabber_.getPixels());

		motion_detector_.update(frame_);
		contour_detector_.update(frame_);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::lightBlue, ofColor::blue);

	ofSetHexColor(0xFFFFFF);
	frame_.draw(10, 10, 640, 480);

	motion_detector_.draw(660, 10, 640, 480);

	ofSetHexColor(0xFFFFFF);
	contour_detector_.working_image_.draw(10, 500, 640, 480);
	contour_detector_.draw(10, 500, 640, 480);

	ofSetHexColor(0xFFFFFF);
	contour_detector_.getGreyImage().draw(660, 500, 640, 480);
	contour_detector_.draw(660, 500, 640, 480);

	settings_panel_.draw();
}

void ofApp::exit()
{
	threshold_slider_.removeListener(this, &ofApp::thresholdChanged);
	count_frames_.removeListener(this, &ofApp::countFramesChanged);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
	{
		ofxCvGrayscaleImage bg;
		bg.allocate(frame_.width, frame_.height);
		bg = frame_;
		contour_detector_.setBackgroundImage(bg);
	}
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

void ofApp::thresholdChanged(int& threshold)
{
	motion_detector_.setThreshold(threshold);
}

void ofApp::countFramesChanged(int& countFrame)
{
	motion_detector_.setNumberFramesRemembered(countFrame);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
