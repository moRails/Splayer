#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    filmWidth = ofGetWindowWidth();
    filmHeight = ofGetWindowHeight();
    
    filmToRead.setPixelFormat(OF_PIXELS_RGB);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
    filmToRead.loadMovie("FILM04_1.mov", decodeMode);
    filmToRead.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    filmToRead.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (filmToRead.isLoaded())
    {
        filmToRead.draw(0, 0, filmWidth, filmHeight);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
