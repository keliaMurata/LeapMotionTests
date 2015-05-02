#include "ofApp.h"

ofApp::ofApp()
{
}

ofApp::~ofApp() //this will stop pulling data from the leap when the app is closed, so that it isn't secretly, unintentionally still tracking
{
	if (leap != NULL)
	{
		leap->close();
		delete leap;
	}
}

void ofApp::setup()
{
	leap = new ofxLeapMotion(); //assigns a leap
	leap->open(); //initiates tracking with the leap
	leap->setupGestures(); //sets up the gestures

	font.loadFont("Fonts/DIN.otf", 12); //loads a font to be used
}

void ofApp::update()
{
	camera.setGlobalPosition(0, 200, 400); //sets up a camera so our hands are actually visible on screen

	if (leap->isFrameNew()) //if the leap data has changed (we moved our hands)...
	{
		hands = leap->getSimpleHands(); //uses the getSimpleHands function from the leap addon
		leap->updateGestures(); //updates the gestures with the new information
	}
}

void ofApp::draw()
{
	camera.begin(); //starts the camera

	ofEnableDepthTest(); //lets us have z space

	ofClear(ofColor::gray); //bg color

	for (auto iter = hands.begin(); iter != hands.end(); ++iter) //go through each hand that is detected
	{
		for (auto iter2 = iter->fingers.begin(); iter2 != iter->fingers.end(); ++iter2) //go through each finger on each hand that is detected
		{
			ofSetColor(ofColor::blue); //blue circles for metacarpals (bones in the back of the hand)
			ofCircle(iter2->second.mcp, 5);

			ofSetColor(ofColor::green); //green for first knuckles
			ofCircle(iter2->second.pip, 5);

			ofSetColor(ofColor::red); //red for second knuckles
			ofCircle(iter2->second.dip, 5);

			ofSetColor(ofColor::yellow); //yellow for the tip
			ofCircle(iter2->second.tip, 5);

			ofSetColor(ofColor::black); //black triangles that follow the finger tips when they move
			ofLine(iter2->second.mcp, iter2->second.pip);
			ofLine(iter2->second.pip, iter2->second.dip);
			ofLine(iter2->second.dip, iter2->second.tip);

			ofDrawArrow(iter2->second.pos, iter2->second.pos + iter2->second.vel / 3, iter2->second.vel.distance(ofVec3f(0, 0, 0)) / 20); //the arrows will change size based on velocity and dis moved
		}

		iter->isLeft ? ofSetColor(ofColor::green) : ofSetColor(ofColor::red); //dots for the palms based on which hand it is (green for left, red for right?)
		ofDrawArrow(iter->handPos, iter->handPos + (iter->handNormal * 20), 5.0f); //an arrow that follows the swipe of the hand
	}

	ofSetColor(ofColor::white); //color for the font
	switch (leap->iGestures) //depending on what gesture is made (or, what the computer thinks is made), this will type the name
	{
	case SCREEN_TAP: //this moves through the enum to determine which case (gesture) has happened and writes the appropriate name
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

	ofDisableDepthTest(); //ends the depth test (if we wanted to put other things on screen, it would go after this)

	camera.end(); //stops the camera (other things after this wouldn't be seen by it)
}