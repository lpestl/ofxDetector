#pragma once

//#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxContourDetector.h"
#include "ofxMotionDetector.h"
#include "ofxSettingPerspective.h"

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

	void thresholdContourChnaged(int &threshold);
	void learnedBgChanged();
	void minAreaChanged(int &minArea);
	void maxAreaChanged(int &maxArea);
	void nConsidiredChanged(int &nConsidired);
	void bFindHolesChanged(bool &bFindHoles);
	void bUseApproximation(bool &bUseApproximation);

	ofVideoGrabber 			cam_grabber_;
	ofxCvColorImage			frame_;

	ofxMotionDetector		motion_detector_;
	ofxContourDetector		contour_detector_;
	ofxSettingPerspective	setting_perspective_;

	ofxPanel				common_panel_;

	ofxPanel				perspective_panel_;

	ofxPanel				motion_settings_panel_;
	ofxIntSlider			motion_threshold_slider_;
	ofxIntSlider			count_frames_;

	ofxPanel				contour_settings_panel_;
	ofxIntSlider			contour_threshold_slider_;
	ofxButton				learn_bg_button_;
	ofxIntSlider			min_area_slider_;
	ofxIntSlider			max_area_slider_;
	ofxIntSlider			considered_slider_;
	ofxToggle				find_holes_toogle_;
	ofxToggle				use_approximation_toggle_;

};
