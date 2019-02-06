#pragma once

#include "ofxDetectorBase.h"
#include "vector"

class ofxMotionDetector : public ofxDetectorBase
{
	public:
		void setup(unsigned width_image, unsigned height_image, unsigned char threshold) override;
		void setup(unsigned width_image, unsigned height_image, unsigned char threshold, unsigned int count_remember_frames);
		void update(ofxCvColorImage color_frame) override;
		void draw(int x, int y, int w, int h) override;

	private:
		ofxCvGrayscaleImage result_image_;
		ofxCvGrayscaleImage last_frame_;
		std::vector<ofxCvGrayscaleImage> last_frames_diffs_;
};

