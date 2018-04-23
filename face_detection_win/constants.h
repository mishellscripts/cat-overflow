#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef struct Dual_Points
{
    cv::Point2d point1;
    cv::Point2d point2;
} Dual_Points;

// Multithreading
const size_t NUM_THREAD = 4;

// Image file type
#define IMAGE_TYPE ".png"

// Shape predictor data file
#define FACE_LANDMARKS "shape_predictor_68_face_landmarks.dat"

// Debugging
const bool kPlotVectorField = false;

// Size constants
const int kEyePercentTop = 25;
const int kEyePercentSide = 13;
const int kEyePercentHeight = 30;
const int kEyePercentWidth = 35;

// Preprocessing
const bool kSmoothFaceImage = false;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 50;
const int kWeightBlurSize = 5;
const bool kEnableWeight = true;
const float kWeightDivisor = 1.0;
const double kGradientThreshold = 50.0;

// Postprocessing
const bool kEnablePostProcess = true;
const float kPostProcessThreshold = 0.97;

// Eye Corner
const bool kEnableEyeCorner = false;

#endif