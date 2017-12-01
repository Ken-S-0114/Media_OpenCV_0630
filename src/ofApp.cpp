#include "ofApp.h"
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "ofxCv.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  // Read input images
  
  inputOfImg.loadImage("church01.jpg");
  inputOfImg.update();
  inputOfImg2.loadImage("church02.jpg");
  inputOfImg2.update();
  
  src_img = ofxCv::toCv(inputOfImg);
  src_img2 = ofxCv::toCv(inputOfImg2);
  
  cvtColor(src_img, dst_img, CV_RGB2GRAY);
  cvtColor(src_img2, dst_img2, CV_RGB2GRAY);
  
  if (!dst_img.data || !dst_img2.data)
  return 0;
  
  // vector of keypoints
  std::vector<::KeyPoint> keypoints1;
  std::vector<::KeyPoint> keypoints2;
  
  // Construction of the SURF feature detector
  SurfFeatureDetector surf;
  
  // Detection of the SURF features
  surf.detect(dst_img,keypoints1);
  surf.detect(dst_img2,keypoints2);
  
  std::cout << "Number of SURF points (1): " << keypoints1.size() << std::endl;
  std::cout << "Number of SURF points (2): " << keypoints2.size() << std::endl;
  
  
  // Construction of the SURF descriptor extractor
  OrbDescriptorExtractor surfDesc;
  
  // Extraction of the SURF descriptors
  surfDesc.compute(dst_img,keypoints1,descriptors1);
  surfDesc.compute(dst_img2,keypoints2,descriptors2);
  
  // check
  std::cout << "descriptor matrix size: " << descriptors1.rows << " by " << descriptors1.cols << std::endl;
  std::cout << "descriptor matrix size: " << descriptors2.rows << " by " << descriptors2.cols << std::endl;
  
  // Construction of the matcher
  BruteForceMatcher<cv::L2<float>> matcher;
  
  // Match the two image descriptors
  matcher.match(descriptors1,descriptors2, matches);
  
  std::cout << "Number of matched points: " << matches.size() << std::endl;
  
  std::nth_element(matches.begin(),    // initial position
                   matches.begin()+24, // position of the sorted element
                   matches.end());     // end position
  
  matches.erase(matches.begin()+25, matches.end());
  
  KeyPoint::convert(keypoints1, marks1);
  KeyPoint::convert(keypoints2, marks2);
  
  ofxCv::toOf(dst_img, outputOfImg);
  outputOfImg.update();
  ofxCv::toOf(dst_img2, outputOfImg2);
  outputOfImg2.update();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  outputOfImg.draw(0,0);
  outputOfImg2.draw(outputOfImg.getWidth(), 0);
  
  for (int i=0; i<matches.size() ; i++) {
//    if (matches[i].distance < 0.1) {
    left = matches[i].queryIdx;
    right = matches[i].trainIdx;
    ofPushStyle();
    ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    ofDrawCircle(marks1[left].x, marks1[left].y, 3);
    ofDrawCircle(outputOfImg.getWidth() + marks2[right].x, marks2[right].y, 3);
    ofPopStyle();
    ofDrawLine(marks1[left].x, marks1[left].y, outputOfImg.getWidth() + marks2[right].x, marks2[right].y);
//    }
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
