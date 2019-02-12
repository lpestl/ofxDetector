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

	const auto w = 960;
	const auto h = 720;
	cam_grabber_.setup(w, h);
	frame_.allocate(w, h);

	motion_detector_.setup(w, h, 50, 5);
	contour_detector_.setup(w, h, 10);
	contour_detector_.maxArea = w * h / 3;

	motion_threshold_slider_.addListener(this, &ofApp::thresholdChanged);
	count_frames_.addListener(this, &ofApp::countFramesChanged);

	contour_threshold_slider_.addListener(this, &ofApp::thresholdContourChnaged);
	learn_bg_button_.addListener(this, &ofApp::learnedBgChanged);
	min_area_slider_.addListener(this, &ofApp::minAreaChanged);
	max_area_slider_.addListener(this, &ofApp::maxAreaChanged);
	considered_slider_.addListener(this, &ofApp::nConsidiredChanged);
	find_holes_toogle_.addListener(this, &ofApp::bFindHolesChanged);
	use_approximation_toggle_.addListener(this, &ofApp::bUseApproximation);

	motion_settings_panel_.setup("MotionDetectorSettings", "motion_settings.xml");
	motion_settings_panel_.add(motion_threshold_slider_.setup("threshold_motion", 80, 0, 255));
	motion_settings_panel_.add(count_frames_.setup("number_of_frames", 1, 1, 10));

	contour_settings_panel_.setup("ContourDetectorSettings", "contour_settings.xml", motion_settings_panel_.getWidth() + 20, 10);
	contour_settings_panel_.add(learn_bg_button_.setup("Learn Background"));
	contour_settings_panel_.add(contour_threshold_slider_.setup("threshold_contour", 30, 0, 255));
	contour_settings_panel_.add(min_area_slider_.setup("minArea", 20, 1, w*h / 3));
	contour_settings_panel_.add(max_area_slider_.setup("minArea", w*h / 3, 20, w*h));
	contour_settings_panel_.add(considered_slider_.setup("nConsidered", 10, 1, 100));
	contour_settings_panel_.add(find_holes_toogle_.setup("bFindHoles", true));
	contour_settings_panel_.add(use_approximation_toggle_.setup("bUseApproximation", true));
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
	frame_.draw(ofGetWindowWidth() / 2 - 320, 10, 640, 480);

	motion_detector_.draw(ofGetWindowWidth() / 2 - 650, 500, 640, 480);

	ofSetHexColor(0xFFFFFF);
	contour_detector_.getGreyImage().draw(ofGetWindowWidth() / 2 + 10, 500, 640, 480);
	contour_detector_.draw(ofGetWindowWidth() / 2 + 10, 500, 640, 480);

	motion_settings_panel_.draw();
	contour_settings_panel_.draw();
}

void ofApp::exit()
{
	min_area_slider_.removeListener(this, &ofApp::minAreaChanged);
	max_area_slider_.removeListener(this, &ofApp::maxAreaChanged);
	considered_slider_.removeListener(this, &ofApp::nConsidiredChanged);
	find_holes_toogle_.removeListener(this, &ofApp::bFindHolesChanged);
	use_approximation_toggle_.removeListener(this, &ofApp::bUseApproximation);
	learn_bg_button_.removeListener(this, &ofApp::learnedBgChanged);
	contour_threshold_slider_.removeListener(this, &ofApp::thresholdContourChnaged);
	motion_threshold_slider_.removeListener(this, &ofApp::thresholdChanged);
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

void ofApp::thresholdContourChnaged(int& threshold)
{
	contour_detector_.setThreshold(threshold);
}

void ofApp::learnedBgChanged()
{
	ofxCvGrayscaleImage bg;
	bg.allocate(frame_.width, frame_.height);
	bg = frame_;
	contour_detector_.setBackgroundImage(bg);

}

void ofApp::minAreaChanged(int& minArea)
{
	max_area_slider_.setMin(minArea);
	contour_detector_.minArea = minArea;
}

void ofApp::maxAreaChanged(int& maxArea)
{
	min_area_slider_.setMax(maxArea);
	contour_detector_.maxArea = maxArea;
}

void ofApp::nConsidiredChanged(int& nConsidired)
{
	contour_detector_.nConsidired = nConsidired;
}

void ofApp::bFindHolesChanged(bool& bFindHoles)
{
	contour_detector_.bFindHoles = bFindHoles;
}

void ofApp::bUseApproximation(bool& bUseApproximation)
{
	contour_detector_.bUseApproximation = bUseApproximation;
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
