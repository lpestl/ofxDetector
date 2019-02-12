#include "ofxContourDetector.h"

void ofxContourDetector::setup(unsigned width_image, unsigned height_image, unsigned char threshold)
{
	ofxDetectorBase::setup(width_image, height_image, threshold);

	background_.allocate(width_image, height_image);
	working_image_.allocate(width_image, height_image);
}

void ofxContourDetector::update(ofxCvColorImage color_frame)
{
	ofxDetectorBase::update(color_frame);

	working_image_.absDiff(background_, gray_image_);
	working_image_.threshold(threshold_);

	contour_finder_.findContours(working_image_, 20, background_.width * background_.height / 3, 10, true);
}

void ofxContourDetector::draw(int x, int y, int w, int h)
{
	ofPushMatrix();
	//ofSetHexColor(0xFFFFFF);
	//gray_image_.draw(x, y, w, h);
	//working_image_.draw(x, y, w, h);

	for(int i = 0; i < contour_finder_.nBlobs; ++i)
	{
		/*if (contour_finder_.blobs[i].hole)
			ofSetHexColor(0x0000FF);
		else
			ofSetHexColor(0xFF0000);*/

		contour_finder_.blobs[i].draw(x, y);

		/*if (!contour_finder_.blobs[i].hole) {
			ofSetHexColor(0x00FF00);
			ofDrawRectangle(
				contour_finder_.blobs[i].boundingRect.x + x,
				contour_finder_.blobs[i].boundingRect.y + y,
				contour_finder_.blobs[i].boundingRect.width,
				contour_finder_.blobs[i].boundingRect.height);
		}*/
	}
	ofPopMatrix();
}

void ofxContourDetector::setBackgroundImage(ofxCvGrayscaleImage bg_image)
{
	background_ = bg_image;
}

ofxCvGrayscaleImage ofxContourDetector::getBackgroungImage() const
{
	return background_;
}
