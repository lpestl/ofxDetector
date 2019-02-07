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

	motion_detector_.setup(w, h, 50, 5);
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

	frame_.draw(10, 10, 320, 240);

	std::queue<ofxCvGrayscaleImage> frames = motion_detector_.frames_;
	for (size_t i = 0; i < motion_detector_.frames_.size(); i++)
	{
		frames.front().draw(340 + i * 330, 10, 320, 240);
		frames.pop();
	}

	std::queue<ofxCvGrayscaleImage> frames_diff = motion_detector_.frames_diffs_;
	if (!frames_diff.empty()) {
		auto common_diff = frames_diff.front();
		for (size_t i = 0; i < motion_detector_.frames_diffs_.size(); i++)
		{
			auto curr_diff = frames_diff.front();
			curr_diff.draw(340 + i * 330, 260, 320, 240);
			common_diff.absDiff(common_diff, curr_diff);
			frames_diff.pop();
		}
		common_diff.draw(10, 260, 320, 240);
	}
	
	std::queue<ofxCvGrayscaleImage> frames_th = motion_detector_.frames_threshold_;
	if (!frames_th.empty()) {
		auto common_th = frames_th.front();
		for (size_t i = 0; i < motion_detector_.frames_threshold_.size(); i++)
		{
			auto curr_th = frames_th.front();
			curr_th.draw(340 + i * 330, 510, 320, 240);
			common_th.absDiff(common_th, curr_th);
			frames_th.pop();
		}
		common_th.draw(10, 510, 320, 240);
	}
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
