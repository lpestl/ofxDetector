#include "ofxSettingPerspective.h"

void ofxSettingPerspective::setup(unsigned width_image, unsigned height_image)
{
	source_.allocate(width_image, height_image);
	result_.allocate(width_image, height_image);

	setting_corners_.reserve(4);
	setting_corners_.emplace_back(0, 0);								// Top-left corner
	setting_corners_.emplace_back(width_image - 1, 0);					// Top-Right corner
	setting_corners_.emplace_back(width_image - 1, height_image - 1);	// Bottom-Right corner
	setting_corners_.emplace_back(0, height_image - 1);					// Bottom-left corner
}

void ofxSettingPerspective::update(ofxCvColorImage color_frame)
{
	source_ = color_frame;
}

void ofxSettingPerspective::draw(ofRectangle setting_rect, ofRectangle output_rect)
{
}

void ofxSettingPerspective::setMode(mode mode)
{
	mode_ = mode;
}

ofxSettingPerspective::mode ofxSettingPerspective::getMode() const
{
	return mode_;
}

ofPoint ofxSettingPerspective::getTopLeftCorner()
{
	return setting_corners_[0];
}

void ofxSettingPerspective::setTopLeftCorner(ofPoint point)
{
	setting_corners_[0] = point;
}

ofPoint ofxSettingPerspective::getTopRightCorner()
{
	return setting_corners_[1];
}

void ofxSettingPerspective::setTopRightCorner(ofPoint point)
{
	setting_corners_[1] = point;
}

ofPoint ofxSettingPerspective::getBottomRightCorner()
{
	return setting_corners_[2];
}

void ofxSettingPerspective::setBottomRightCorner(ofPoint point)
{
	setting_corners_[2] = point;
}

ofPoint ofxSettingPerspective::getBottomLeftCorner()
{
	return setting_corners_[3];
}

void ofxSettingPerspective::setBottomLeftCorner(ofPoint point)
{
	setting_corners_[3] = point;
}

ofxCvGrayscaleImage ofxSettingPerspective::getResult() const
{
	return result_;
}

void ofxSettingPerspective::mouseDragged(int x, int y, int button)
{

	if (button == 0)
		last_mouse_position_.set(x, y);
}

void ofxSettingPerspective::mousePressed(int x, int y, int button)
{
	if (button == 0)
		last_mouse_position_.set(x, y);
}

void ofxSettingPerspective::mouseReleased(int x, int y, int button)
{
}

void ofxSettingPerspective::drawCorner(ofRectangle setting_rect, ofPoint& corner)
{
}
