#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxcv.h"
using namespace ofxCv;
using namespace cv;

class responseData{
public:
    int x;
    int y;
    float r;
    
};
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
    
        void deriveAlongX();
        void deriveALongY();
    
        void squareTheXImage();
        void squareTheYImage();
        void multiplyXY();
    
        void computeRMatrix();
        void createVisuals();
        void extractResponses();
        void sortResponses();
    
        ofImage computeSumMatrix( ofImage image);
    
    
    
    
    ofImage checkerBoard;
    ofImage blurCheckerBoard;
    ofImage dxImage;
    ofImage dyImage;
    ofImage dx2Image;
    ofImage dy2Image;
    ofImage dxyImage;
    
    ofImage dx2SumMatrix;
    ofImage dy2SumMatrix;
    ofImage dxySumMatrix;

    ofImage intermediateImage;
    ofImage responseImage;
    ofImage visualizingImage;
    
    ofxCvGrayscaleImage checkerBoardinCV;
    //Mat checkerBoardinCV;
    
    int cWidth;
    int cHeight;
    //int listLength = 100;
    int responseArray[3][100] ;
    int windowSize = 5 ;
    float k = 0.04f;
    int tau = 10000;
    
    vector<responseData> extractedResponses;
    
    
		
};
