#pragma once

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "ofMain.h"
#include "ofxMotionDetector.h"
#include "ofxGui.h"
#include "ofxContourDetector.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void thresholdChanged(int &threshold);
	void countFramesChanged(int &countFrame);

	ofVideoGrabber 			cam_grabber_;
	ofxCvColorImage			frame_;

	ofxMotionDetector		motion_detector_;
	ofxContourDetector		contour_detector_;

	ofxPanel				settings_panel_;
	ofxIntSlider			threshold_slider_;
	ofxIntSlider			count_frames_;

};
