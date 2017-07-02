#pragma once

#include "ofMain.h"
#include "pingPongBuffer.hpp"
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
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    ofShader updateSystem, render;
    pingPongBuffer pingPong;
    
    // parameter for Reaction Diffusion
    ofxPanel gui;
    ofParameter<float> feed;
    ofParameter<float> kill;
    ofParameter<float> dA;
    ofParameter<float> dB;
    ofParameter<float> dt;
    
    int texWidth, texHeight;
};
