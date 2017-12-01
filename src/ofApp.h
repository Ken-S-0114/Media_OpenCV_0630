#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;

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
  
		ofImage inputOfImg, inputOfImg2, outputOfImg, outputOfImg2;
    cv::Mat src_img, src_img2, dst_img, dst_img2, descriptors1, descriptors2;;
    std::vector<cv::Point2f> marks1, marks2;
    std::vector<cv::DMatch> matches;
  
  int left, right;
};
