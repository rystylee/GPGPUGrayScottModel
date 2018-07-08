#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
    ofGLFWWindowSettings s;
    s.setGLVersion(4, 0);
    s.width = 1024;
    s.height = 768;
    ofCreateWindow(s);
    
	ofRunApp(new ofApp());
}
