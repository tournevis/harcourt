#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"

#include "ofxOpenCv.h"
#include <vector>

class ofApp : public ofxAndroidApp{
	
	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
		void cancelPressed();
		bool shotPicture;

		ofVideoGrabber grabber;
		ofxCvColorImage picture;
		ofxCvColorImage colorCv;
		ofxCvColorImage colorCvSmall;
		ofImage imageCv;
		ofxCvGrayscaleImage grayCv;
		ofxCvGrayscaleImage grayImage;
		ofxCvHaarFinder faceFinder;
		std::vector<ofxCvBlob> faces;

		/*
		ofxCvHaarFinder eyeFinder;
		std::vector<ofxCvBlob> eyes;
		*/

		ofColor alphaCircle;

		ofTexture           myTexture;
        unsigned char*      grayVideoData;

		int oneTouch;
		int one_second_time;
		int camera_fps;
		int frames_one_sec;
		int height;
		int width;
		int faceCounter;
		int grabberWidth;
		int grabberHeight;
		int circleSize;
		float vidScale;
};
