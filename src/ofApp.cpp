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

	auto w = 960;
	auto h = 720;
	cam_grabber_.setup(w, h);
	frame_.allocate(w, h);

	motion_detector_.setup(w, h, 50, 5);

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
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::lightBlue, ofColor::blue);

	ofSetHexColor(0xAAAA00);
	ofDrawRectangle(5, 5, 330, 750);

	ofSetHexColor(0xFF0000);
	ofDrawRectangle(5, 755, ofGetWindowWidth() - 10, ofGetWindowHeight() - 760);

	ofSetHexColor(0xFFFFFF);
	frame_.draw(10, 10, 320, 240);

	std::queue<ofxCvGrayscaleImage> frames = motion_detector_.frames_;
	//ofxCvGrayscaleImage 
	for (size_t i = 0; i < motion_detector_.frames_.size(); i++)
	{
		frames.front().draw(340 + i * 330, 10, 320, 240);
		frames.pop();
	}

	std::queue<ofxCvGrayscaleImage> frames_diff = motion_detector_.frames_diffs_;
	if (!frames_diff.empty()) {
		auto common_diff = frames_diff.front();
		common_diff.draw(340, 260, 320, 240);
		frames_diff.pop();
		for (size_t i = 0; i < motion_detector_.frames_diffs_.size() - 1; i++)
		{
			auto curr_diff = frames_diff.front();
			curr_diff.draw(340 + 330 + i * 330, 260, 320, 240);
			common_diff.absDiff(curr_diff);
			frames_diff.pop();
		}
		common_diff.draw(10, 260, 320, 240);
	}
	
	std::queue<ofxCvGrayscaleImage> frames_th = motion_detector_.frames_threshold_;
	if (!frames_th.empty()) {
		auto common_th = frames_th.front();
		common_th.draw(340, 510, 320, 240);
		frames_th.pop();
		for (size_t i = 0; i < motion_detector_.frames_threshold_.size() - 1; i++)
		{
			auto curr_th = frames_th.front();
			curr_th.draw(340 + 330 + i * 330, 510, 320, 240);
			common_th.absDiff(curr_th);
			frames_th.pop();
		}
		common_th.draw(10, 510, 320, 240);
	}

	std::vector<ofxCvGrayscaleImage> diffs;
	std::queue<ofxCvGrayscaleImage> frames_calc = motion_detector_.frames_;
	
	if (!frames_calc.empty()) {
		auto result = frames_calc.front();
		frames_calc.pop();

		for (size_t i = 0; i < motion_detector_.frames_.size() - 1; i++)
		{
			ofxCvGrayscaleImage diff = result;
			diff.absDiff(frames_calc.front());
			frames_calc.pop();
			diffs.push_back(diff);
		}

		if (!diffs.empty())
		{
			result = diffs.front();
			for (auto&& diff : diffs)
			{
				result.maxCustom(diff);
			}

			result.threshold(motion_detector_.getThreshold());
			result.draw(10, 760, 320, 240);
		}
	}

	settings_panel_.draw();
}

void ofApp::exit()
{
	threshold_slider_.removeListener(this, &ofApp::thresholdChanged);
	count_frames_.removeListener(this, &ofApp::countFramesChanged);
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
