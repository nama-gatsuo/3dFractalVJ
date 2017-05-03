#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLWindowSettings s;
    s.setGLVersion(3, 2);
    s.width = 640;
    s.height = 480;
    ofCreateWindow(s);
    
	ofRunApp(new ofApp());

}
