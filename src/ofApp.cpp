#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundColor(0);
    
    simulateShader.load("shaders/pass.vert", "shaders/simulate.frag");
    renderShader.load("shaders/pass.vert", "shaders/render.frag");
    
    w = ofGetWidth();
    h = ofGetHeight();
    auto color = make_unique<float[]>(w * h * 3);
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int i = y * w + x;
            color[i * 3 + 0] = 0.0;
            color[i * 3 + 1] = 0.0;
            color[i * 3 + 2] = 0.0;
        }
    }
    
    pingPong.allocate(w, h, GL_RGB32F);
    pingPong.src->getTexture().loadData(color.get(), w, h, GL_RGB32F);
    pingPong.dst->getTexture().loadData(color.get(), w, h, GL_RGB32F);

    gui.setup();
    gui.add(feed.set("feed", 0.055, 0.0, 1.0));
    gui.add(kill.set("kill", 0.062, 0.0, 1.0));
    gui.add(dA.set("dA", 1.0, 0.0, 1.0));
    gui.add(dB.set("dB", 0.5, 0.0, 1.0));
    gui.add(dt.set("dt", 1.0, 0.0, 1.0));
    gui.add(color1.set("color1", ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color2.set("color2", ofFloatColor(0.0, 1.0, 0.0, 0.2), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color3.set("color3", ofFloatColor(1.0, 1.0, 0.0, 0.21), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color4.set("color4", ofFloatColor(1.0, 0.0, 0.0, 0.4), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color5.set("color5", ofFloatColor(1.0, 1.0, 1.0, 0.6), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    pingPong.dst->begin();
    ofClear(0);
    simulateShader.begin();
    simulateShader.setUniformTexture("u_prevBuffer", pingPong.src->getTexture(), 0);
    simulateShader.setUniform1f("u_feed", feed);
    simulateShader.setUniform1f("u_kill", kill);
    simulateShader.setUniform1f("u_dA", dA);
    simulateShader.setUniform1f("u_dB", dB);
    simulateShader.setUniform1f("u_dt", dt);
    pingPong.src->draw(0, 0, w, h);
    simulateShader.end();
    pingPong.dst->end();
    
    pingPong.swap();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    renderShader.begin();
    renderShader.setUniformTexture("u_tex", pingPong.dst->getTexture(), 0);
    renderShader.setUniform4f("color1", color1);
    renderShader.setUniform4f("color2", color2);
    renderShader.setUniform4f("color3", color3);
    renderShader.setUniform4f("color4", color4);
    renderShader.setUniform4f("color5", color5);
    ofDrawRectangle(0, 0, w, h);
    renderShader.end();

    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // ------------------------------------------------------------------
    // reference: http://mrob.com/pub/comp/xmorphia/pearson-classes.html
    // ------------------------------------------------------------------
    switch (key) {
        case 'a':
            feed = 0.014;
            kill = 0.057;
            break;
        case 'b':
            feed = 0.050;
            kill = 0.059;
            break;
        case 'c':
            feed = 0.010;
            kill = 0.047;
            break;
        case 'd':
            feed = 0.014;
            kill = 0.039;
            break;
        case 'e':
            feed = 0.022;
            kill = 0.051;
            break;
        case 'f':
            feed = 0.030;
            kill = 0.055;
            break;
        case 'g':
            feed = 0.018;
            kill = 0.055;
            break;
        case 'h':
            feed = 0.022;
            kill = 0.061;
            break;
        case 'i':
            feed = 0.034;
            kill = 0.063;
            break;
        case 'j':
            feed = 0.030;
            kill = 0.057;
            break;
        case 'k':
            feed = 0.046;
            kill = 0.0594;
            break;
        case 'l':
            feed = 0.050;
            kill = 0.063;
            break;
        case 'm':
            feed = 0.026;
            kill = 0.061;
            break;
        case 'n':
            feed = 0.046;
            kill = 0.065;
            break;
        case 'o':
            feed = 0.010;
            kill = 0.041;
            break;
        case 'p':
            feed = 0.062;
            kill = 0.061;
            break;
        case 'q':
            feed = 0.090;
            kill = 0.059;
            break;
        case 'r':
            feed = 0.090;
            kill = 0.057;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    pingPong.dst->begin();
    ofClear(0);
    ofSetColor(255);
    ofDrawCircle(x, y, 30);
    pingPong.src->draw(0, 0);
    pingPong.dst->end();

    pingPong.swap();
}

//--------------------------------------------------------------
