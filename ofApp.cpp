#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255,255,255);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofOrientation(OF_ORIENTATION_LEFT_90);
	alphaCircle = ofColor(250,150,150,150);


	vidScale = 1.5;
 	grabberWidth = 640 * vidScale;
	grabberHeight = 480 * vidScale;
	height = ofGetWindowHeight();
	width = ofGetWindowWidth();

	grabber.setDeviceID(1);
	grabber.initGrabber(grabberWidth,grabberHeight);

	grayVideoData= new unsigned char [grabberWidth*grabberHeight*3];
	myTexture.allocate(grabberWidth,grabberHeight,GL_RGB);

	//photoIcn.loadImage("images/texture01.jpg");
	//photoIcn.allocate(250,250);
	shotPicture = false;

	colorCv.allocate(grabberWidth, grabberHeight);
	colorCvSmall.allocate(grabberWidth/4, grabberHeight/4);
	grayCv.allocate(grabberWidth/4, grabberHeight/4);

	imageCv.allocate(grabberWidth, grabberHeight , OF_IMAGE_COLOR);

	grayImage.allocate(grabberWidth, grabberHeight );
	picture.allocate(grabberWidth, grabberHeight);

	
	faceFinder.setup("haarcascade_frontalface_default.xml");
	faceFinder.setNeighbors(1);
	faceFinder.setScaleHaar(2);

	 ofLog(OF_LOG_NOTICE , ofToDataPath("data"));
	one_second_time = ofGetSystemTime();
	camera_fps = 0;
	frames_one_sec = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	if( !shotPicture){
		grabber.getPixelsRef().rotate90To(imageCv,3);
		imageCv.mirror(false,true);
	}
 	if(grabber.isFrameNew()  && shotPicture && faceCounter < 1){


    	frames_one_sec++;
   		if( ofGetSystemTime() - one_second_time >= 1000){
    		camera_fps = frames_one_sec;
    		frames_one_sec = 0;
    		one_second_time = ofGetSystemTime();
    	}
		colorCv = grabber.getPixels();
		colorCvSmall.scaleIntoMe(colorCv, CV_INTER_NN);
		grayCv = colorCvSmall;
		faceFinder.findHaarObjects(grayCv);
		faces = faceFinder.blobs;
		if(faces.size() >= 1 ){
			faceCounter ++;
		}
   		}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xDDDDDD);
	if( !shotPicture){
		imageCv.draw(20 ,20);
    //grabber.update();
    }else{

    	myTexture.draw(20,20);


		/*picture = imageCv.getPixels();
		grayImage = imageCv.getPixels() ;
		//grayImage.rotate90(3);

		ofPushMatrix();
		ofRotateZ(-90);
    	grayImage.draw(20 -620 ,20);
    	ofPopMatrix();*/
    }




	float scaleFactor = 3.0;
	ofPushStyle();
	ofNoFill();
	ofSetColor(255, 0, 255);
	if(faces.size() == 1){
		ofxCvBlob& face = faces[0];
		ofRectangle rect( 480 - face.boundingRect.y * scaleFactor  , grabberHeight - face.boundingRect.x * scaleFactor, face.boundingRect.width * scaleFactor, face.boundingRect.height * scaleFactor);
		ofRect(rect);
	}
	ofPopStyle();


	ofSetHexColor(0x000000);

	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()),330,10);
	ofDrawBitmapString("camera fps: " + ofToString(camera_fps),330,30);
	ofDrawBitmapString("Faces Found: " + ofToString(faces.size()),330,50);
	if(!shotPicture){
		ofEnableAlphaBlending();
		ofSetColor(alphaCircle);
		ofCircle(ofGetWidth()/2 , ofGetHeight()*9/10,100);
		ofDisableAlphaBlending();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id){
	//ofCircle(ofGetWidth()/2 , ofGetHeight()*9/10,100);
	if(ofDist(x,y, ofGetWidth()/2 , ofGetHeight()*9/10) < 50){
		shotPicture = true ;
		alphaCircle.a = 100 ;
		circleSize = 80;
		grabber.update();
         		unsigned char* pixelData = grabber.getPixels();

         		int nTotalBytes = grabberWidth * grabberHeight ;
         		unsigned char* grayPixelData  = new unsigned char [nTotalBytes];

         		for(int j=0; j<nTotalBytes; j++){
         			int i= (j * 3);

                	unsigned char R = pixelData[i ];
                	unsigned char G = pixelData[i+1];
                	unsigned char B = pixelData[i+2];

                	unsigned char Y = (R+G+B)/3;
                	grayPixelData[j] = Y;
         		}
        		myTexture.loadData(grayPixelData, grabberWidth, grabberHeight, GL_RGB);


	}

}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id){
	alphaCircle.a = 150 ;
	circleSize = 150;
	faceCounter = 0;

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id){
	shotPicture = false ;
}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

//--------------------------------------------------------------
void ofApp::pause(){

}

//--------------------------------------------------------------
void ofApp::stop(){

}

//--------------------------------------------------------------
void ofApp::resume(){

}

//--------------------------------------------------------------
void ofApp::reloadTextures(){

}

//--------------------------------------------------------------
bool ofApp::backPressed(){
	return false;
}

//--------------------------------------------------------------
void ofApp::okPressed(){

}

//--------------------------------------------------------------
void ofApp::cancelPressed(){

}
