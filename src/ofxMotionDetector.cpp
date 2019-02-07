#include "ofxMotionDetector.h"

void ofxMotionDetector::setup(unsigned width_image, unsigned height_image, unsigned char threshold)
{
	setup(width_image, height_image, threshold, 1);
}

void ofxMotionDetector::setup(unsigned width_image, unsigned height_image, unsigned char threshold, unsigned short number_frames_remembered)
{
	ofxDetectorBase::setup(width_image, height_image, threshold);

	//last_frame_.allocate(width_image, height_image);
	result_image_.allocate(width_image, height_image);

	//last_frames_diffs_.resize(count_remember_frames);
	/*for (auto& frame : last_frames_diffs_)
	{
		frame.allocate(width_image, height_image);
	}*/
}

void ofxMotionDetector::update(ofxCvColorImage color_frame)
{
	//ofxDetectorBase::update(color_frame);
	//for (size_t i = last_frames_diffs_.size() - 1; i > 0; --i)
	//{
	//	last_frames_diffs_[i] = last_frames_diffs_[i - 1];
	//}

	//last_frames_diffs_[0].absDiff(last_frame_, gray_image_);
	////last_frames_diffs_[0].threshold(threshold_);
	//
	//last_frame_ = gray_image_;
	//
	//result_image_ = last_frames_diffs_[0].getPixels();
	//for (size_t i = 1; i < last_frames_diffs_.size(); ++i)
	//{
	//	/*auto frame_pixels = last_frames_diffs_[i].getPixels();
	//	for(size_t y = 0; y < frame_pixels.getHeight(); ++y)
	//	{
	//		for (size_t x = 0; x < frame_pixels.getWidth(); ++x)
	//		{
	//			const auto pixel_color = frame_pixels.getColor(x, y);
	//			if ((pixel_color == ofColor::white) && (pixel_color != pixels.getColor(x, y)))
	//			{
	//				pixels.setColor(x, y, pixel_color);
	//			}
	//		}
	//	}*/
	//	result_image_.absDiff(result_image_, last_frames_diffs_[i]);
	//}
	//result_image_.threshold(threshold_);
}

void ofxMotionDetector::draw(int x, int y, int w, int h)
{
	ofSetHexColor(0xffffff);
	result_image_.draw(x, y, w, h);
}

void ofxMotionDetector::setNumberFramesRemembered(unsigned short num)
{
	number_frames_remembered_ = num;
}

unsigned short ofxMotionDetector::getNumberFramesRememberes() const
{
	return number_frames_remembered_;
}
