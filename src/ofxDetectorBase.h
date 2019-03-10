#pragma once

#include "ofxOpenCv.h"

class ofxDetectorBase
{
	public:
		virtual void setup(unsigned int width_image, unsigned int height_image, unsigned char threshold);
		virtual void update(ofxCvGrayscaleImage color_frame);
		virtual void draw(int x, int y, int w, int h);

		void setThreshold(unsigned char threshold);
		unsigned char getThreshold() const;

		ofxCvGrayscaleImage getGreyImage() const;

	protected:
		ofxCvGrayscaleImage 	gray_image_;

		unsigned char			threshold_ = 80;
};

