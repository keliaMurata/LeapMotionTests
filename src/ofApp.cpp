#include "ofApp.h"

ofApp::ofApp()
{
}

ofApp::~ofApp()
{
	if (leap != NULL)
	{
		leap->close();
		delete leap;
	}
}

void ofApp::setup()
{
	leap = new ofxLeapMotion();
	leap->open();
	leap->setupGestures();

	font.loadFont("Fonts/DIN.otf", 12);
}

void ofApp::update()
{
	camera.setGlobalPosition(0, 200, 400);

	if (leap->isFrameNew())
	{
		hands = leap->getSimpleHands();
		leap->updateGestures();
	}
}

void ofApp::draw()
{
	camera.begin();

	ofEnableDepthTest();

	ofClear(ofColor::gray);

	for (auto iter = hands.begin(); iter != hands.end(); ++iter)
	{
		for (auto iter2 = iter->fingers.begin(); iter2 != iter->fingers.end(); ++iter2)
		{
			ofSetColor(ofColor::blue);
			ofCircle(iter2->second.mcp, 5);

			ofSetColor(ofColor::green);
			ofCircle(iter2->second.pip, 5);

			ofSetColor(ofColor::red);
			ofCircle(iter2->second.dip, 5);

			ofSetColor(ofColor::yellow);
			ofCircle(iter2->second.tip, 5);

			ofSetColor(ofColor::black);
			ofLine(iter2->second.mcp, iter2->second.pip);
			ofLine(iter2->second.pip, iter2->second.dip);
			ofLine(iter2->second.dip, iter2->second.tip);

			ofDrawArrow(iter2->second.pos, iter2->second.pos + iter2->second.vel / 3, iter2->second.vel.distance(ofVec3f(0, 0, 0)) / 20);
		}

		iter->isLeft ? ofSetColor(ofColor::green) : ofSetColor(ofColor::red);
		ofDrawArrow(iter->handPos, iter->handPos + (iter->handNormal * 20), 5.0f);
	}

	ofSetColor(ofColor::white);
	switch (leap->iGestures)
	{
	case SCREEN_TAP:
		font.drawString("Screen Tap", 2, 2);
		break;
	case KEY_TAP:
		font.drawString("Key Tap", 2, 2);
		break;
	case SWIPE_RIGHT:
		font.drawString("Swipe Right", 2, 2);
		break;
	case SWIPE_LEFT:
		font.drawString("Swipe Left", 2, 2);
		break;
	case SWIPE_DOWN:
		font.drawString("Swipe Down", 2, 2);
		break;
	case SWIPE_UP:
		font.drawString("Swipe Up", 2, 2);
		break;
	case SWIPE_FORWARD:
		font.drawString("Swipe Forward", 2, 2);
		break;
	case SWIPE_BACKWARD:
		font.drawString("Swipe Backward", 2, 2);
		break;
	case CIRCLE_COUNTER_CLOCKWISE:
		font.drawString("Circle Counter Clockwise", 2, 2);
		break;
	case CIRCLE_CLOCKWISE:
		font.drawString("Circle Clockwise", 2, 2);
		break;
	}

	ofDisableDepthTest();

	camera.end();
}