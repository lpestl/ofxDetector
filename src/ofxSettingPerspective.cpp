#include "ofxSettingPerspective.h"

void ofxSettingPerspective::setup(unsigned width_image, unsigned height_image)
{
	result_.allocate(width_image, height_image);

	//setting_corners_.reserve(4);
	parameters.setName("Corners");

	//setting_corners_.emplace_back(0, 0);								// Top-left corner
	parameters.add(topLeftPosition.set("TopLeft", glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(width_image, height_image)));

	//setting_corners_.emplace_back(width_image - 1, 0);					// Top-Right corner
	parameters.add(topRightPosition.set("TopRight", glm::vec2(width_image - 1, 0), glm::vec2(0, 0), glm::vec2(width_image, height_image)));

	//setting_corners_.emplace_back(width_image - 1, height_image - 1);	// Bottom-Right corner
	parameters.add(bottomRightPosition.set("BottomRight", glm::vec2(width_image - 1, height_image - 1), glm::vec2(0, 0), glm::vec2(width_image, height_image)));
	
	//setting_corners_.emplace_back(0, height_image - 1);					// Bottom-left corner
	parameters.add(bottomLeftPosition.set("BottomLeft", glm::vec2(0, height_image - 1), glm::vec2(0, 0), glm::vec2(width_image, height_image)));
}

void ofxSettingPerspective::update(ofxCvColorImage color_frame)
{
	//source_ = color_frame;

	result_ = color_frame;
	//result_.warpPerspective(setting_corners_[0], setting_corners_[1], setting_corners_[2], setting_corners_[3]);
	result_.warpPerspective(ofPoint(topLeftPosition.get()), ofPoint(topRightPosition.get()), ofPoint(bottomRightPosition.get()), ofPoint(bottomLeftPosition.get()));
}

void ofxSettingPerspective::draw(ofRectangle output_rect)
{
	const auto scale = ofVec2f(result_.width / setting_rect_.width, result_.height / setting_rect_.height);

	ofPushMatrix();
	ofPushStyle();

	ofSetLineWidth(1);
	ofSetHexColor(0x005555);

	ofDrawLine(setting_rect_.x + topLeftPosition.get().x / scale.x, setting_rect_.y + topLeftPosition.get().y / scale.y, setting_rect_.x + topRightPosition.get().x / scale.x, setting_rect_.y + topRightPosition.get().y / scale.y);
	ofDrawLine(setting_rect_.x + topRightPosition.get().x / scale.x, setting_rect_.y + topRightPosition.get().y / scale.y, setting_rect_.x + bottomRightPosition.get().x / scale.x, setting_rect_.y + bottomRightPosition.get().y / scale.y);
	ofDrawLine(setting_rect_.x + bottomRightPosition.get().x / scale.x, setting_rect_.y + bottomRightPosition.get().y / scale.y, setting_rect_.x + bottomLeftPosition.get().x / scale.x, setting_rect_.y + bottomLeftPosition.get().y / scale.y);
	ofDrawLine(setting_rect_.x + bottomLeftPosition.get().x / scale.x, setting_rect_.y + bottomLeftPosition.get().y / scale.y, setting_rect_.x + topLeftPosition.get().x / scale.x, setting_rect_.y + topLeftPosition.get().y / scale.y);

	ofPopMatrix();
	ofPopStyle();

	if (mode_ == editting) {
		//for (auto& corner : setting_corners_)
		drawCorner(scale, topLeftPosition);
		drawCorner(scale, topRightPosition);
		drawCorner(scale, bottomRightPosition);
		drawCorner(scale, bottomLeftPosition);
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

glm::vec2 ofxSettingPerspective::getTopLeftCorner() const
{
	return topLeftPosition.get();
}

void ofxSettingPerspective::setTopLeftCorner(glm::vec2 point)
{
	if (mode_ == editting)
		topLeftPosition.set(point);
}

glm::vec2 ofxSettingPerspective::getTopRightCorner() const
{
	return topRightPosition.get();
}

void ofxSettingPerspective::setTopRightCorner(glm::vec2 point)
{
	if (mode_ == editting)
		topRightPosition.set(point);
}

glm::vec2 ofxSettingPerspective::getBottomRightCorner() const
{
	return bottomRightPosition.get();
}

void ofxSettingPerspective::setBottomRightCorner(glm::vec2 point)
{
	if (mode_ == editting)
		bottomRightPosition.set(point);
}

glm::vec2 ofxSettingPerspective::getBottomLeftCorner() const
{
	return bottomLeftPosition.get();
}

void ofxSettingPerspective::setBottomLeftCorner(glm::vec2 point)
{
	if (mode_ == editting)
		bottomLeftPosition.set(point);
}

ofRectangle ofxSettingPerspective::getSettingsRect() const
{
	return setting_rect_;
}

void ofxSettingPerspective::setSettingsRect(ofRectangle settings_rect)
{
	setting_rect_ = settings_rect;
}

ofxCvColorImage ofxSettingPerspective::getResult() const
{
	return result_;
}

void ofxSettingPerspective::mouseDragged(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		const auto scale = ofVec2f(result_.width / setting_rect_.width, result_.height / setting_rect_.height);

		auto dx = (x - last_mouse_position_.x) * scale.x;
		auto dy = (y - last_mouse_position_.y) * scale.y;

		float new_x, new_y;
		switch (draggedCornerIndex)
		{
		case 0:
			new_x = topLeftPosition.get().x + dx;
			new_y = topLeftPosition.get().y + dy;
			if (new_x < 0) new_x = 0;
			if (new_y < 0) new_y = 0;
			if (new_x > setting_rect_.width * scale.x)
				new_x = setting_rect_.width * scale.x;
			if (new_y > setting_rect_.height * scale.y)
				new_y = setting_rect_.height * scale.y;

			topLeftPosition.set(glm::vec2(new_x, new_y));
			break;
		case 1:
			new_x = topRightPosition.get().x + dx;
			new_y = topRightPosition.get().y + dy;
			if (new_x < 0) new_x = 0;
			if (new_y < 0) new_y = 0;
			if (new_x > setting_rect_.width * scale.x)
				new_x = setting_rect_.width * scale.x;
			if (new_y > setting_rect_.height * scale.y)
				new_y = setting_rect_.height * scale.y;

			topRightPosition.set(glm::vec2(new_x, new_y));
			break;
		case 2:
			new_x = bottomRightPosition.get().x + dx;
			new_y = bottomRightPosition.get().y + dy;
			if (new_x < 0) new_x = 0;
			if (new_y < 0) new_y = 0;
			if (new_x > setting_rect_.width * scale.x)
				new_x = setting_rect_.width * scale.x;
			if (new_y > setting_rect_.height * scale.y)
				new_y = setting_rect_.height * scale.y;

			bottomRightPosition.set(glm::vec2(new_x, new_y));
			break;
		case 3:
			new_x = bottomLeftPosition.get().x + dx;
			new_y = bottomLeftPosition.get().y + dy;
			if (new_x < 0) new_x = 0;
			if (new_y < 0) new_y = 0;
			if (new_x > setting_rect_.width * scale.x)
				new_x = setting_rect_.width * scale.x;
			if (new_y > setting_rect_.height * scale.y)
				new_y = setting_rect_.height * scale.y;

			bottomLeftPosition.set(glm::vec2(new_x, new_y));
			break;
		default:
			break;
		}

		last_mouse_position_.set(x, y);
	}
}

void ofxSettingPerspective::mousePressed(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		last_mouse_position_.set(x, y);

		const auto scale = ofVec2f(result_.width / setting_rect_.width, result_.height / setting_rect_.height);

		if (ofRectangle(setting_rect_.x + (topLeftPosition.get().x - 10) / scale.x, setting_rect_.y + (topLeftPosition.get().y - 10) / scale.y, 20 / scale.x, 20 / scale.y).inside(x, y))
			draggedCornerIndex = 0;

		if (ofRectangle(setting_rect_.x + (topRightPosition.get().x - 10) / scale.x, setting_rect_.y + (topRightPosition.get().y - 10) / scale.y, 20 / scale.x, 20 / scale.y).inside(x, y))
			draggedCornerIndex = 1;

		if (ofRectangle(setting_rect_.x + (bottomRightPosition.get().x - 10) / scale.x, setting_rect_.y + (bottomRightPosition.get().y - 10) / scale.y, 20 / scale.x, 20 / scale.y).inside(x, y))
			draggedCornerIndex = 2;

		if (ofRectangle(setting_rect_.x + (bottomLeftPosition.get().x - 10) / scale.x, setting_rect_.y + (bottomLeftPosition.get().y - 10) / scale.y, 20 / scale.x, 20 / scale.y).inside(x, y))
			draggedCornerIndex = 3;
	}
}

void ofxSettingPerspective::mouseReleased(int x, int y, int button)
{
	if ((button == 0) && (mode_ == editting))
	{
		draggedCornerIndex = -1;
	}
}

void ofxSettingPerspective::drawCorner(ofVec2f scale, ofParameter<glm::vec2>& corner) const
{
	ofPushMatrix();
	ofPushStyle();

	ofSetLineWidth(2);
	ofSetHexColor(0xAA0000);
	
	ofDrawLine(setting_rect_.x + (corner.get().x - 10) / scale.x, setting_rect_.y + (corner.get().y) / scale.y, setting_rect_.x + (corner.get().x - 2) / scale.x, setting_rect_.y + (corner.get().y) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.get().x + 10) / scale.x, setting_rect_.y + (corner.get().y) / scale.y, setting_rect_.x + (corner.get().x + 2) / scale.x, setting_rect_.y + (corner.get().y) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.get().x) / scale.x, setting_rect_.y + (corner.get().y - 10) / scale.y, setting_rect_.x + (corner.get().x) / scale.x, setting_rect_.y + (corner.get().y - 2) / scale.y);
	ofDrawLine(setting_rect_.x + (corner.get().x) / scale.x, setting_rect_.y + (corner.get().y + 10) / scale.y, setting_rect_.x + (corner.get().x) / scale.x, setting_rect_.y + (corner.get().y + 2) / scale.y);

	ofPopStyle();
	ofPopMatrix();
}
