#include "com_example_mypc_surrounding_OpencvClass.h"

JNIEXPORT void JNICALL Java_com_example_mypc_surrounding_OpencvClass_surrounding
  (JNIEnv *, jclass, jlong addrRgba){
  Mat& frame = *(Mat*)addrRgba;

  detect(frame);
}

void detect(Mat& frame){
    String surr_cascade_name = "/storage/emulated/0/data/wallclock.xml";
    CascadeClassifier surr_cascade;

    if( !surr_cascade.load( surr_cascade_name ) ){ printf("--(!)Error loading\n"); return; };

    std::vector<Rect> surr;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    surr_cascade.detectMultiScale( frame_gray, surr, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < surr.size(); i++ )
    {
        Point center( surr[i].x + surr[i].width*0.5, surr[i].y + surr[i].height*0.5 );
        ellipse( frame, center, Size( surr[i].width*0.5, surr[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );

    }
}
