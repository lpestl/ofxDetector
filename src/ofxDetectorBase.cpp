#include "ofxDetectorBase.h"

void ofxDetectorBase::setup(unsigned width_image, unsigned height_image, unsigned char threshold)
{
	gray_image_.allocate(width_image, height_image);

	threshold_ = threshold;
}

void ofxDetectorBase::update(ofxCvGrayscaleImage color_frame)
{
	gray_image_ = color_frame;
}

void ofxDetectorBase::draw(int x, int y, int w, int h)
{
	ofSetHexColor(0xffffff);
	gray_image_.draw(x, y, w, h);
}

void ofxDetectorBase::setThreshold(unsigned char threshold)
{
	threshold_ = threshold;
}

unsigned char ofxDetectorBase::getThreshold() const
{
	return threshold_;
}

ofxCvGrayscaleImage ofxDetectorBase::getGreyImage() const
{
	return gray_image_;
}
