#pragma once

#include "ofxDetectorBase.h"
#include <queue>

class ofxMotionDetector : public ofxDetectorBase
{
	public:
		void setup(unsigned width_image, unsigned height_image, unsigned char threshold) override;
		void setup(unsigned width_image, unsigned height_image, unsigned char threshold, unsigned short number_frames_remembered);
		void update(ofxCvColorImage color_frame) override;
		void draw(int x, int y, int w, int h) override;		

		void setNumberFramesRemembered(unsigned short num);
		unsigned short getNumberFramesRememberes() const;

		ofxCvGrayscaleImage getResultImage() const;

	private:
		unsigned short number_frames_remembered_ = 1;

		ofxCvGrayscaleImage result_image_;
		std::queue<ofxCvGrayscaleImage> frames_;
};

