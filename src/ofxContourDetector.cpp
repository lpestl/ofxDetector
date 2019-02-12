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
	
	ofVec2f ratio{ static_cast<float>(w) / gray_image_.width, static_cast<float>(h) / gray_image_.height };

	for(int i = 0; i < contour_finder_.nBlobs; ++i)
	{
		ofPushStyle();
		ofNoFill();
		ofSetHexColor(0x00FFFF);
		ofBeginShape();
		for (int j = 0; j < contour_finder_.blobs[i].nPts; ++j) {
			ofVertex(x + contour_finder_.blobs[i].pts[j].x * ratio.x, y + contour_finder_.blobs[i].pts[j].y * ratio.y);
		}
		ofEndShape(true);
		ofSetHexColor(0xff0099);
		ofDrawRectangle(
			x + contour_finder_.blobs[i].boundingRect.x * ratio.x, 
			y + contour_finder_.blobs[i].boundingRect.y * ratio.y, 
			contour_finder_.blobs[i].boundingRect.width * ratio.x,
			contour_finder_.blobs[i].boundingRect.height * ratio.y);
		ofPopStyle();
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
