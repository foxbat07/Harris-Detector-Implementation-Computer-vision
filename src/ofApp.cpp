#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    checkerBoard.loadImage("checkerboard.png");
    //checkerBoard.resize(60, 60);
    //checkerBoard.loadImage("notredame.png");
    
    cHeight =  checkerBoard.height;
    cWidth  =  checkerBoard.width;
    
    dxImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dyImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dx2Image.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dy2Image.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dxyImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    
    dx2SumMatrix.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dy2SumMatrix.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    dxySumMatrix.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    responseImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    intermediateImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);
    visualizingImage.allocate(cHeight, cWidth, OF_IMAGE_GRAYSCALE);

    cout<< "allocated memory"<<endl ;
    
    //checkerBoardinCV.allocate ( cWidth , cHeight);
    checkerBoardinCV.setFromPixels(checkerBoard.getPixelsRef());
    checkerBoardinCV.blurGaussian();
    //checkerBoardinCV.blur();
    checkerBoard.setFromPixels(checkerBoardinCV.getPixelsRef());
    
    deriveAlongX();
    deriveALongY();
    cout<< "derive x,y"<<endl ;

    squareTheXImage();
    squareTheYImage();
    multiplyXY();
    cout<< "multiply x,y"<<endl ;

    
    dx2SumMatrix = computeSumMatrix(dx2Image);
    dy2SumMatrix = computeSumMatrix(dy2Image);
    dxySumMatrix = computeSumMatrix(dxyImage);
    
    
    cout<< "created sum matrices"<<endl ;

    computeRMatrix();
    
    cout<< "created response"<<endl ;

    createVisuals();
    cout<< "created visuals"<<endl ;

    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(128);
    
    checkerBoardinCV.draw(0, 0, cWidth  , cHeight);
    checkerBoard.draw(cWidth , 0, cWidth  , cHeight);
    dxImage.draw( 2 * cWidth,0, cWidth , cHeight);
    
    dyImage.draw(0,cHeight, cWidth , cHeight);
    dxyImage.draw(cWidth,cHeight, cWidth , cHeight);

    
    responseImage.draw(2* cWidth ,cHeight, cWidth , cHeight);

    
    
    
    
}

//--------------------------------------------------------------


void ofApp::deriveAlongX()
{
    // -1 as we arent going all the way to the end
    for ( int i = 0 ; i< cHeight -1; i++)
    {
        for ( int j = 0; j< cWidth -1 ; j++)
        {
            int currentPixel = checkerBoard.getPixelsRef()[i*cWidth+ j];
            int nextPixel    = checkerBoard.getPixelsRef()[i*cWidth+ (j+1)];
            
            int difference = currentPixel - nextPixel;
 
            dxImage.getPixelsRef()[i*cWidth+ j] =  difference;
            
        
            
        }
    }
    
    dxImage.update();
    
    
}

    

void ofApp::deriveALongY()
{
    // -1 as we arent going all the way to the end
    for ( int i = 0 ; i< cHeight -1; i++)
    {
        for ( int j = 0; j< cWidth -1 ; j++)
        {
            int currentPixel = checkerBoard.getPixelsRef()[i*cWidth+ j];
            int nextPixel    = checkerBoard.getPixelsRef()[(i+1)*cWidth+ j];
            
            int difference = currentPixel - nextPixel;

            
            dyImage.getPixelsRef()[i*cWidth+ j] =  difference;
            
            
            
        }
    }
    
    dyImage.update();
    
    
}



void ofApp::squareTheXImage()

{
    // -1 as we arent going all the way to the end
    for ( int i = 0 ; i< cHeight -1 ; i++)
    {
        for ( int j = 0; j< cWidth -1 ; j++)
        {
            
            int pixelValue = dxImage.getPixelsRef()[i*cWidth+ j]  ;
            pixelValue = pixelValue*pixelValue;
            
            dx2Image.getPixelsRef()[i*cWidth+ j] = pixelValue;
            //cout<< pixelValue <<" ";
            

            
        }
        cout<< endl;
        
    }
    
    dx2Image.update();
    
    
}



void ofApp::squareTheYImage()

{
    // -1 as we arent going all the way to the end
    for ( int i = 0 ; i< cHeight -1; i++)
    {
        for ( int j = 0; j< cWidth -1 ; j++)
        {
            
            int pixelValue = dyImage.getPixelsRef()[i*cWidth+ j]  ;
            pixelValue = pixelValue*pixelValue;
            //cout<< pixelValue <<" ";
            dy2Image.getPixelsRef()[i*cWidth+ j] = pixelValue;
        }
        cout<< endl;

    }
    
    dy2Image.update();
    
    
}





void ofApp::multiplyXY()
{
    for ( int i = 0 ; i< cHeight -1; i++)
    {
        for ( int j = 0; j< cWidth -1 ; j++)
        {
            int pixelValueX = dxImage.getPixelsRef()[i*cWidth+ j]  ;
            int pixelValueY = dyImage.getPixelsRef()[i*cWidth+ j]  ;
            int pixelValueXY = pixelValueX * pixelValueY;           // /255 to see points
            
            dxyImage.getPixelsRef()[i*cWidth+ j] = pixelValueXY;
            //cout<< pixelValueXY <<" ";
        }
        cout << endl;
    }
    
    dxyImage.update();
    
    
    
}


ofImage ofApp::computeSumMatrix( ofImage image)
{
    
    for ( int i = 0 ; i< cHeight - windowSize -1; i++)
    {
        for ( int j = 0; j< cWidth - windowSize -1 ; j++)
        {
            
            int tempSum = 0 ;
            for( int a  = 0 ; a< windowSize ; a++ )
            {
                for ( int b = 0 ; b< windowSize ; b++)
                {
                  tempSum+= image.getPixelsRef()[ ( i + a ) * cWidth+ ( j + b )  ] ;
                }
            }
            
            intermediateImage.getPixelsRef()[i*cWidth+j] = tempSum;
            //cout<< tempSum <<" ";
        }
        cout<<endl;
        
    }
    cout<<"created"<<endl;
    
    return intermediateImage;
    
} // end of function





void ofApp::computeRMatrix()
{
    
    for ( int i = 0 ; i< cHeight - windowSize -1; i++)
    {
        for ( int j = 0; j< cWidth - windowSize -1 ; j++)
        {
        
            float determinant = ( dx2SumMatrix.getPixelsRef()[i*cWidth+j] *  dy2SumMatrix.getPixelsRef()[i*cWidth+j] ) - (dxySumMatrix.getPixelsRef()[i*cWidth+j] * dxySumMatrix.getPixelsRef()[i*cWidth+j] );
            
            
            float traceX = dx2SumMatrix.getPixelsRef()[i*cWidth+j] ;
            float traceY = dy2SumMatrix.getPixelsRef()[i*cWidth+j] ;

            float response = determinant - k * (traceX + traceY ) * (traceX + traceY )  ;
            
            //if ( response> 5000)
                //cout<< response << " ";
            
            if ( response > tau )
                {
                responseData rData;
                rData.x = j;
                rData.y = i;
                rData.r = response;
                cout<< rData.x << " "<< rData.y <<" "<< rData.r   <<endl;
                
                //cout<<"exceeds 10000" ;
                extractedResponses.push_back(rData);
                }
            

            responseImage.getPixelsRef()[ i*cWidth+j ] = response;
            
            
        }
        //cout<<endl;
        
    }
    cout<<"computing R"<<endl;
    
    
    
} // end of function


void ofApp::createVisuals()
{
    for ( int i = 0 ; i< cHeight - windowSize -1; i++)
    {
        for ( int j = 0; j< cWidth - windowSize -1 ; j++)
        {
            
            //cout<< int (responseImage.getPixelsRef()[i*cWidth+j])  <<" ";
            
            if ( responseImage.getPixelsRef()[i*cWidth+j] > tau)
            {

                visualizingImage.getPixelsRef()[i*cWidth+j] =255;
                
             
            }
            else
            {
                 visualizingImage.getPixelsRef()[i*cWidth+j] =0;
                 //cout<<"1 00 ";
            
            }
            
            
            
            
        }
    }
    
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
