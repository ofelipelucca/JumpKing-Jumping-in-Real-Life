#include <vector>
#include <opencv2/opencv.hpp>
#include "GraphicsValues.hpp"

// Matrix OpenCV 

cv::Mat GraphicsValues::CVMatFrames::img, GraphicsValues::CVMatFrames::imgFlip;

// Matrix OpenCV above line 
cv::Mat GraphicsValues::CVMatFrames::JumpIMGCrop, GraphicsValues::CVMatFrames::JumpIMGGray, GraphicsValues::CVMatFrames::JumpIMGBackground, GraphicsValues::CVMatFrames::JumpIMGThres, GraphicsValues::CVMatFrames::JumpIMGSub, GraphicsValues::CVMatFrames::JumpIMGDil;

// Square frames vector

std::vector<GraphicsValues::CVSquares::Images> GraphicsValues::CVSquares::Frames;

// Contours points from OpenCV 

std::vector<std::vector<cv::Point>> GraphicsValues::CVSquares::contours;
std::vector<std::vector<cv::Point>> GraphicsValues::CVJumpLine::mycontours;

// Square and line vectors

std::vector<GraphicsValues::CVSquares::Rectangles> GraphicsValues::CVSquares::Squares;

std::vector<GraphicsValues::CVJumpLine::Line> GraphicsValues::CVJumpLine::Lines;

bool GraphicsValues::CVJumpLine::LineExists = false;

// Tolerance value (minimum area of ​​detected contours detected by OpenCV)
// Default value: 80

unsigned GraphicsValues::TOLERANCE = 80;