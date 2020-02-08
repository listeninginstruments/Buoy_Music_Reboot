#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawSensorData();
    
        ofJson jsn;
        ofTrueTypeFont ttf;
        std::string text;
    
    ofFile file;
    
    float text_x;
    float text_y;
    float base_y;
    int curr_n;
    
    void delayStart(float s);
    void delayTimer();
    void delayFire();
    float delay_time;
    float count;
    
    //------------------------------ OSC
    ofxOscSender sender;
    void sendVals();
    float wind, temp, ph, humidity, rain;
};
