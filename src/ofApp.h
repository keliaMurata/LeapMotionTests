#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"

enum Gesture
{
	NONE = 0,
	SCREEN_TAP = 1,
	KEY_TAP = 2,
	SWIPE_RIGHT = 3,
	SWIPE_LEFT = 4,
	SWIPE_DOWN = 5,
	SWIPE_UP = 6,
	SWIPE_FORWARD = 7,
	SWIPE_BACKWARD = 8,
	CIRCLE_COUNTER_CLOCKWISE = 9,
	CIRCLE_CLOCKWISE = 10
};

class ofApp : public ofBaseApp
{
public:
	ofApp();
	~ofApp();
	void setup();
	void update();
	void draw();

private:
	ofxLeapMotion* leap;
	vector<ofxLeapMotionSimpleHand> hands;
	ofEasyCam camera;
	ofTrueTypeFont font;
};
