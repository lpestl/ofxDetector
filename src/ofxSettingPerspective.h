#pragma once

#include "ofxOpenCv.h"
#include "vector"

class ofxSettingPerspective
{
public:

	enum mode { editting, view };

	void setup(unsigned width_image, unsigned height_image);
	void update(ofxCvColorImage color_frame);
	void draw(ofRectangle output_rect);

	void setMode(mode mode);
	mode getMode() const;

	glm::vec2 getTopLeftCorner() const;
	void setTopLeftCorner(glm::vec2 point);
	glm::vec2 getTopRightCorner() const;
	void setTopRightCorner(glm::vec2 point);
	glm::vec2 getBottomRightCorner() const;
	void setBottomRightCorner(glm::vec2 point);
	glm::vec2 getBottomLeftCorner() const;
	void setBottomLeftCorner(glm::vec2 point);

	ofRectangle getSettingsRect() const;
	void setSettingsRect(ofRectangle settings_rect);

	ofxCvGrayscaleImage getResult() const;

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	ofParameterGroup parameters;

private:
	void drawCorner(ofVec2f scale, ofParameter<glm::vec2>& corner) const;

	ofxCvGrayscaleImage			result_;

	short					draggedCornerIndex = -1;
	ofRectangle				setting_rect_;
	ofPoint					last_mouse_position_;
	mode					mode_ = view;

	ofParameter<glm::vec2> topLeftPosition;
	ofParameter<glm::vec2> topRightPosition;
	ofParameter<glm::vec2> bottomRightPosition;
	ofParameter<glm::vec2> bottomLeftPosition;
};

