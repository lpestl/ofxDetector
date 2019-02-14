#pragma once

#include "ofxOpenCv.h"
#include "vector"

class ofxSettingPerspective
{
public:
	void setup(unsigned width_image, unsigned height_image);
	void update(ofxCvColorImage color_frame);
	void draw(ofRectangle setting_rect, ofRectangle output_rect);

private:
	void drawCorner(ofRectangle setting_rect, ofPoint & corner);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	ofxCvGrayscaleImage		result_;
	std::vector<ofPoint>	setting_corners_;
	ofPoint					last_mouse_position_;
};

