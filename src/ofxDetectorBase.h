#pragma once

#include "ofxOpenCv.h"

class ofxDetectorBase
{
	public:
		virtual void setup(unsigned int width_image, unsigned int height_image, unsigned char threshold);
		virtual void update(ofxCvColorImage color_frame);
		virtual void draw(int x, int y, int w, int h);

		virtual void setThreshold(unsigned char threshold);

	protected:
		ofxCvGrayscaleImage 	gray_image_;
		ofxCvGrayscaleImage 	gray_diff_image_;

		unsigned char			threshold_;
};

