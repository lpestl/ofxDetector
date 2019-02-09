#include "ofxMotionDetector.h"

void ofxMotionDetector::setup(unsigned width_image, unsigned height_image, unsigned char threshold)
{
	setup(width_image, height_image, threshold, 1);
}

void ofxMotionDetector::setup(unsigned width_image, unsigned height_image, unsigned char threshold, unsigned short number_frames_remembered)
{
	ofxDetectorBase::setup(width_image, height_image, threshold);

	number_frames_remembered_ = number_frames_remembered;
	result_image_.allocate(width_image, height_image);
}

// WARNING: ofxOpenCv not contain ofxCvGrayscaleImage::max(...) method. 
// Its my temporary realization.
//void ofxCvGrayscaleImage::max(ofxCvGrayscaleImage& mom)
//{
//	if (!mom.bAllocated) {
//		ofLogError("ofxCvGrayscaleImage") << "max(): source image not allocated";
//		return;
//	}
//	if (!bAllocated) {
//		ofLogNotice("ofxCvGrayscaleImage") << "max(): allocating to match dimensions: "
//			<< mom.getWidth() << " " << mom.getHeight();
//		allocate(mom.getWidth(), mom.getHeight());
//	}
//
//	if (matchingROI(getROI(), mom.getROI())) {
//		cvMax(cvImage, mom.getCvImage(), cvImageTemp);
//		swapTemp();
//		flagImageChanged();
//	}
//	else {
//		ofLogError("ofxCvGrayscaleImage") << "max(): region of interest mismatch";
//	}
//}
//
//void ofxCvGrayscaleImage::max(ofxCvGrayscaleImage& mom, ofxCvGrayscaleImage& dad)
//{
//	if (!mom.bAllocated) {
//		ofLogError("ofxCvGrayscaleImage") << "max(): first source image (mom) not allocated";
//		return;
//	}
//	if (!dad.bAllocated) {
//		ofLogError("ofxCvGrayscaleImage") << "max(): second source image (dad) not allocated";
//		return;
//	}
//	if (!bAllocated) {
//		ofLogNotice("ofxCvGrayscaleImage") << "max(): allocating to match dimensions: "
//			<< mom.getWidth() << " " << mom.getHeight();
//		allocate(mom.getWidth(), mom.getHeight());
//	}
//
//	ofRectangle roi = getROI();
//	ofRectangle momRoi = mom.getROI();
//	ofRectangle dadRoi = dad.getROI();
//	if ((momRoi.width == roi.width && momRoi.height == roi.height) &&
//		(dadRoi.width == roi.width && dadRoi.height == roi.height))
//	{
//		cvMax(mom.getCvImage(), dad.getCvImage(), cvImage);
//		flagImageChanged();
//	}
//	else {
//		ofLogError("ofxCvGrayscaleImage") << "max(): source image size mismatch between first (mom) & second (dad) image";
//	}
//}
void ofxMotionDetector::update(ofxCvColorImage color_frame)
{
	ofxDetectorBase::update(color_frame);

	if (!frames_.empty())
	{
		std::queue<ofxCvGrayscaleImage> frames_calc = frames_;
		
		for (size_t i = 0; i < frames_.size(); ++i)
		{
			auto frame_diff = gray_image_;

			auto frame = frames_calc.front();
			frames_calc.pop();

			frame_diff.absDiff(frame);
			frame_diff.threshold(threshold_);

			if (i == 0)
				result_image_ = frame_diff;
			else
				result_image_.maxCustom(frame_diff);
		}
	}

	frames_.push(gray_image_);
	while (frames_.size() > number_frames_remembered_)
		frames_.pop();
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

ofxCvGrayscaleImage ofxMotionDetector::getResultImage() const
{
	return result_image_;
}
