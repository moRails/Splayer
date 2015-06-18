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
    gui.add(infoPosX.setup( "infoPosX", filmWidth/2, 0, ofGetWindowWidth()));
    gui.add(infoPosY.setup( "infoPosY", filmHeight/2, 0, ofGetWindowHeight()));
    
    gui.loadFromFile("settings.xml");
    
    showGui = false;
    showCursor = false;
    CGDisplayHideCursor(NULL);
    filmToRead.loadMovie("blc0.mov");
    filmToRead.play();
    
    lang = "";
    nbOfLoop = 0;
    loopLangState = false;
    videoIsPaused = false;
    animIsplaying = false;
    timeReleased = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    filmToRead.update();
    
    //-- back to the language loop
    if(filmToRead.getCurrentFrame() == filmToRead.getTotalNumFrames() && lang != "")
    {
        loadTheNewFilm(lang);
        animIsplaying = false;
    }
    //-- back to the loop 00
    if(filmToRead.getMoviePath() == "DE/film0.mov" || filmToRead.getMoviePath() == "EN/film0.mov" || filmToRead.getMoviePath() == "FR/film0.mov")
    {
        if(filmToRead.getCurrentFrame() == 240)
        {
            nbOfLoop += 1;
        }
    }
    if (nbOfLoop > 2)
    {
        filmToRead.close();
        filmToRead.loadMovie("blc0.mov");
        nbOfLoop = 0;
        lang = "";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    filmToRead.draw(fPosX, fPosY, fWidth, fHeight);
    
    if(showGui)
    {
        ofSetColor(0, 200);
        ofFill();
        ofRect(infoPosX - 20,infoPosY - 20,300, 200);
        ofSetColor(255);
        gui.draw();
        ofDrawBitmapString("lang = " + lang, infoPosX,infoPosY);
        ofDrawBitmapString("FrameRate = " + ofToString(ofGetFrameRate()), infoPosX,infoPosY + 20);
        ofDrawBitmapString("nbOfLoop = " + ofToString(nbOfLoop), infoPosX,infoPosY + 40);
        ofDrawBitmapString("CurrentFrame = " + ofToString(filmToRead.getCurrentFrame()), infoPosX,infoPosY + 60);
        ofDrawBitmapString("TotalFrame = " + ofToString(filmToRead.getTotalNumFrames()), infoPosX,infoPosY + 80);
        ofDrawBitmapString("You can pause = " + ofToString(animIsplaying), infoPosX,infoPosY + 100);
        bool canPress; //-- Maybe clear this var i think it's not util
        if (timeReleasedNew > timeReleased + 1500)
        {
            canPress = true;
        }
        else
        {
            canPress = false;
        }
        ofDrawBitmapString("delay is = " + ofToString(canPress), infoPosX,infoPosY + 120);
        ofDrawBitmapString("delay value = " + ofToString(timeReleased) + " |   | "+ofToString(timeReleasedNew), infoPosX,infoPosY + 140);
        ofDrawBitmapString("Film path = " + filmToRead.getMoviePath(), infoPosX,infoPosY + 160);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
    {
        ofToggleFullscreen();
    }

    if (key == 'g')
    {
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
    timeReleasedNew = ofGetElapsedTimeMillis();
    if (filmToRead.isLoaded() && filmToRead.getCurrentFrame() > 25 && timeReleasedNew > timeReleased + 1500)
    {
        switch (key)
        {
            case '1':
                //-- Read the blc FR
                if (filmToRead.isLoaded())
                {
                    lang = "FR";
                    loadTheNewFilm(lang);
                    loopLangState = true;

                }
                break;
                
            case '2':
                if (filmToRead.isLoaded())
                {
                    //-- Read the blc EN
                    lang = "EN";
                    loadTheNewFilm(lang);
                    loopLangState = true;
                }
                break;
                
            case '3':
                if (filmToRead.isLoaded())
                {
                    //-- Read the blc DE
                    lang = "DE";
                    loadTheNewFilm(lang);
                    loopLangState = true;
                }
                break;
              
            case 'a':
                if (filmToRead.isLoaded())
                {
                    loadTheNewFilmByLang(lang, 1);
                }
                break;
                
            case 'z':
                if (filmToRead.isLoaded())
                {
                    loadTheNewFilmByLang(lang, 2);
                }
                break;
                
            case 'e':
                if (filmToRead.isLoaded())
                {
                    loadTheNewFilmByLang(lang, 3);
                }
                break;
                
            case 'r':
                if (filmToRead.isLoaded())
                {
                    loadTheNewFilmByLang(lang, 4);
                }
                break;
            
            case 'p':
                if(animIsplaying)
                {
                    videoIsPaused = !videoIsPaused;
                    filmToRead.setPaused(videoIsPaused);
                }
                break;
                
            default:
                break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::loadTheNewFilm(string l){
    filmToRead.closeMovie();
    filmToRead.close();
    filmToRead.loadMovie(l + "/film0.mov");
    loopLangState = true;
    timeReleased = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::loadTheNewFilmByLang(string l, int num){
    if(lang == "FR" || lang == "EN" || lang == "DE")
    {
        filmToRead.closeMovie();
        filmToRead.close();
        filmToRead.loadMovie(l + "/film" + ofToString(num) + ".mp4");
        loopLangState = false;
        animIsplaying = true;
        timeReleased = ofGetElapsedTimeMillis();
    }
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
