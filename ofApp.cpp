#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    filmWidth  = ofGetWindowWidth(); // change it later with the saving data
    filmHeight = ofGetWindowHeight(); // change it later with the saving data
    filmPosX = 0;
    filmPosY = 0;
    
    gui.setup();
    gui.add(fWidth.setup ( "fWidth",  filmWidth,  0, ofGetWindowWidth()	));
    gui.add(fHeight.setup( "fHeight", filmHeight, 0, ofGetWindowHeight()));
    gui.add(fPosX.setup( "fPosX", filmPosX, 0, ofGetWindowWidth()));
    gui.add(fPosY.setup( "fPosY", filmPosY, 0, ofGetWindowHeight()));
    
    gui.loadFromFile("settings.xml");
    fWidth  = fWidth;
    fHeight = fHeight;
    fPosX = fPosX;
    fPosY = fPosY;
    
    showGui = false;
    showCursor = false;
    CGDisplayHideCursor(NULL);
    filmToRead.loadMovie("blc0.mov");
    filmToRead.play();
    
    lang = "";
}

//--------------------------------------------------------------
void ofApp::update(){
        filmToRead.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    filmToRead.draw(fPosX, fPosY, fWidth, fHeight);
    
    if(showGui)
    {
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f'){
        ofToggleFullscreen();
    }

    if (key == 'g'){
        showGui =! showGui;
        showCursor = !showCursor;
        if (showCursor == true)
        {
            CGDisplayShowCursor(NULL);
        }
        else if ( showCursor == false)
        {
            CGDisplayHideCursor(NULL);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (filmToRead.isLoaded() && filmToRead.getCurrentFrame() > 25)
    {
        switch (key)
        {
            case '1':
                //-- Read the blc FR
                lang = "FR";
                loadTheNewFilm(1);
                break;
                
            case '2':
                //-- Read the blc EN
                lang = "EN";
                loadTheNewFilm(2);
                break;
                
            case '3':
                //-- Read the blc DE
                lang = "DE";
                loadTheNewFilm(3);
                break;
                
            case 'a':
                loadTheNewFilmByLang(lang, 1);
                break;
                
            case 'z':
                loadTheNewFilmByLang(lang, 2);
                break;
                
            case 'e':
                loadTheNewFilmByLang(lang, 3);
                break;
                
            case 'r':
                loadTheNewFilmByLang(lang, 4);
                break;
                
            default:
                break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::loadTheNewFilm(int num){
    filmToRead.close();
    filmToRead.loadMovie("blc" +ofToString(num) + ".mov");
    filmToRead.play();
}

//--------------------------------------------------------------
void ofApp::loadTheNewFilmByLang(string l, int num){
    filmToRead.close();
    filmToRead.loadMovie(l + "/film" + ofToString(num) + ".mp4");
    filmToRead.play();
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
