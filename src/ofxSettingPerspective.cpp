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

	result_ = source_;
	result_.warpPerspective(setting_corners_[0], setting_corners_[1], setting_corners_[2], setting_corners_[3]);
}

void ofxSettingPerspective::draw(ofRectangle output_rect)
{
	const auto scale = ofVec2f(source_.width / setting_rect_.width, source_.height / setting_rect_.height);

	ofPushMatrix();
	ofPushStyle();

	ofSetLineWidth(1);
	ofSetHexColor(0x005555);

	ofDrawLine(setting_rect_.x + setting_corners_[0].x / scale.x, setting_rect_.y + setting_corners_[0].y / scale.y, setting_rect_.x + setting_corners_[1].x / scale.x, setting_rect_.y + setting_corners_[1].y / scale.y);
	ofDrawLine(setting_rect_.x + setting_corners_[1].x / scale.x, setting_rect_.y + setting_corners_[1].y / scale.y, setting_rect_.x + setting_corners_[2].x / scale.x, setting_rect_.y + setting_corners_[2].y / scale.y);
	ofDrawLine(setting_rect_.x + setting_corners_[2].x / scale.x, setting_rect_.y + setting_corners_[2].y / scale.y, setting_rect_.x + setting_corners_[3].x / scale.x, setting_rect_.y + setting_corners_[3].y / scale.y);
	ofDrawLine(setting_rect_.x + setting_corners_[3].x / scale.x, setting_rect_.y + setting_corners_[3].y / scale.y, setting_rect_.x + setting_corners_[0].x / scale.x, setting_rect_.y + setting_corners_[0].y / scale.y);

	ofPopMatrix();
	ofPopStyle();

	if (mode_ == editting) {
		for (auto& corner : setting_corners_)
			drawCorner(scale, corner);
	}

	result_.draw(output_rect);
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

ofRectangle ofxSettingPerspective::getSettingsRect() const
{
	return setting_rect_;
}

void ofxSettingPerspective::setSettingsRect(ofRectangle settings_rect)
{
	setting_rect_ = settings_rect;
}

ofxCvGrayscaleImage ofxSettingPerspective::getResult() const
{
	return result_;
}

void ofxSettingPerspective::mouseDragged(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		if ((draggedCornerIndex >= 0) && (draggedCornerIndex < 4))
		{
			const auto scale = ofVec2f(source_.width / setting_rect_.width, source_.height / setting_rect_.height);

			setting_corners_[draggedCornerIndex].x += (x - last_mouse_position_.x) * scale.x;
			setting_corners_[draggedCornerIndex].y += (y - last_mouse_position_.y) * scale.y;

			if (setting_corners_[draggedCornerIndex].x < 0)
				setting_corners_[draggedCornerIndex].x = 0;

			if (setting_corners_[draggedCornerIndex].y < 0)
				setting_corners_[draggedCornerIndex].y = 0;

			if (setting_corners_[draggedCornerIndex].x > setting_rect_.width * scale.x)
				setting_corners_[draggedCornerIndex].x = setting_rect_.width * scale.x;

			if (setting_corners_[draggedCornerIndex].y > setting_rect_.height * scale.y)
				setting_corners_[draggedCornerIndex].y = setting_rect_.height * scale.y;

		}

		last_mouse_position_.set(x, y);
	}
}

void ofxSettingPerspective::mousePressed(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		last_mouse_position_.set(x, y);

		const auto scale = ofVec2f(source_.width / setting_rect_.width, source_.height / setting_rect_.height);

		for (auto i = 0; i < 4; ++i)
			if (ofRectangle(setting_rect_.x + (setting_corners_[i].x - 10) / scale.x, setting_rect_.y + (setting_corners_[i].y - 10) / scale.y, 20 / scale.x, 20 / scale.y).inside(x, y))
				draggedCornerIndex = i;
	}
}

void ofxSettingPerspective::mouseReleased(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		draggedCornerIndex = -1;
	}
}

void ofxSettingPerspective::drawCorner(ofVec2f scale, ofPoint& corner) const
{
	ofPushMatrix();
	ofPushStyle();

	ofSetLineWidth(2);
	ofSetHexColor(0xAA0000);
	
	ofDrawLine(setting_rect_.x + (corner.x - 10) / scale.x, setting_rect_.y + (corner.y) / scale.y, setting_rect_.x + (corner.x - 2) / scale.x, setting_rect_.y + (corner.y) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.x + 10) / scale.x, setting_rect_.y + (corner.y) / scale.y, setting_rect_.x + (corner.x + 2) / scale.x, setting_rect_.y + (corner.y) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.x) / scale.x, setting_rect_.y + (corner.y - 10) / scale.y, setting_rect_.x + (corner.x) / scale.x, setting_rect_.y + (corner.y - 2) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.x) / scale.x, setting_rect_.y + (corner.y + 10) / scale.y, setting_rect_.x + (corner.x) / scale.x, setting_rect_.y + (corner.y + 2) / scale.y);

	ofPopStyle();
	ofPopMatrix();
}
