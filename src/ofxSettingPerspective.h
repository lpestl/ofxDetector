#pragma once

#include "ofxOpenCv.h"
#include "vector"

class ofxSettingPerspective
{
public:

	enum mode { editting, view };

	void setup(unsigned width_image, unsigned height_image);
	void update(ofxCvColorImage color_frame);
	void draw(ofRectangle setting_rect, ofRectangle output_rect);

	void setMode(mode mode);
	mode getMode() const;

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:
	void drawCorner(ofRectangle setting_rect, ofPoint & corner);

	ofxCvGrayscaleImage		source_;
	ofxCvGrayscaleImage		result_;
	std::vector<ofPoint>	setting_corners_;
	ofPoint					last_mouse_position_;
	mode					mode_;
};

