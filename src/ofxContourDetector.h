#pragma once

#include "ofxDetectorBase.h"

class ofxContourDetector : public ofxDetectorBase
{
public:
	void setup(unsigned width_image, unsigned height_image, unsigned char threshold) override;
	void update(ofxCvGrayscaleImage color_frame) override;
	void draw(int x, int y, int w, int h) override;

	void setBackgroundImage(ofxCvGrayscaleImage bg_image);
	ofxCvGrayscaleImage getBackgroungImage() const;

	int minArea = 20;
	int maxArea = 1000;
	int nConsidired = 10;
	bool bFindHoles = true;
	bool bUseApproximation = true;

private:
	ofxCvGrayscaleImage background_;
	ofxCvGrayscaleImage working_image_;
	ofxCvContourFinder contour_finder_;
};

