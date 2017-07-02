#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    updateSystem.load("shaders/updateSystem");
    render.load("shaders/render");
    
    texWidth = ofGetWidth();
    texHeight = ofGetHeight();
    
    vector<float> color(texWidth * texHeight * 3);
    for(int x=0; x<texWidth; x++){
        for(int y=0; y<texHeight; y++){
            int i = texWidth * y + x;
            color[i*3+0] = 0.0;
            color[i*3+1] = 0.0;
            color[i*3+2] = 0.0;
        }
    }
    
    pingPong.allocate(texWidth, texHeight, GL_RGB32F);
    pingPong.src->getTexture().loadData(color.data(), texWidth, texHeight, GL_RGB);
    pingPong.dst->getTexture().loadData(color.data(), texWidth, texHeight, GL_RGB);
    
    gui.setup();
    gui.add(feed.set("feed", 0.037, 0.0, 1.0));
    gui.add(kill.set("kill", 0.06, 0.0, 1.0));
    gui.add(dA.set("dA", 0.21, 0.0, 1.0));
    gui.add(dB.set("dB", 0.105, 0.0, 1.0));
    gui.add(dt.set("dt", 1.0, 0.01, 5.0));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    pingPong.dst->begin();
    ofClear(0);
    
    updateSystem.begin();
    updateSystem.setUniformTexture("backbuffer", pingPong.src->getTexture(), 0);
    updateSystem.setUniform1f("feed", feed);
    updateSystem.setUniform1f("kill", kill);
    updateSystem.setUniform1f("dA", dA);
    updateSystem.setUniform1f("dB", dB);
    updateSystem.setUniform1f("dt", dt);
    pingPong.src->draw(0, 0);
    updateSystem.end();
    
    pingPong.dst->end();
    
    pingPong.swap();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    render.begin();
    render.setUniformTexture("resultTex", pingPong.dst->getTexture(), 0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    render.end();
    
    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();
    
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
    
    pingPong.dst->begin();
    ofClear(0);
    
    //updateSystem.begin();
    ofSetColor(255);
    ofDrawCircle(x, y, 30);
    pingPong.src->draw(0, 0);
    //updateSystem.end();
    
    pingPong.dst->end();
    
    pingPong.swap();
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    pingPong.dst->begin();
    ofClear(0);
    
    //updateSystem.begin();
    ofSetColor(255);
    ofDrawCircle(x, y, 30);
    pingPong.src->draw(0, 0);
    //updateSystem.end();
    
    pingPong.dst->end();
    
    pingPong.swap();
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
