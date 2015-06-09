#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void loadTheNewFilm(string l);
        void loadTheNewFilmByLang(string l, int num);
    
    ofVideoPlayer filmToRead;
    int filmWidth,filmHeight;
    int filmPosX, filmPosY;
    
    
    ofxIntSlider fWidth;
    ofxIntSlider fHeight;
    ofxIntSlider fPosX;
    ofxIntSlider fPosY;
    ofxPanel gui;
    bool showGui;
    bool showCursor;
    
    string lang;
    int nbOfLoop;
    bool loopLangState;
		
};
