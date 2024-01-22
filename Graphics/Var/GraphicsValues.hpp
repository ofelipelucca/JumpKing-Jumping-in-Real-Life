#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace GraphicsValues {

    // Tolerance value (minimum area of detected contours detected by OpenCV)
    /// @brief Minimum area of detected contours by OpenCV.
    /// @details Default value: 100.
    extern unsigned TOLERANCE;

    namespace CVMatFrames {

        // OpenCV frames
        /// @brief Holds the original image and its flipped counterpart.
        extern cv::Mat img, imgFlip;

        // OpenCV above line frames
        /// @brief Holds images for various processing steps above the jump line.
        extern cv::Mat JumpIMGCrop, JumpIMGGray, JumpIMGBackground, JumpIMGThres, JumpIMGSub, JumpIMGDil;
    }

    namespace CVSquares {

        // Square frames OpenCV data
        /// @brief Structure to store different processed frames for each square.
        struct Images {
            cv::Mat imgCrop;       ///< Cropped image of the square.
            cv::Mat imgDil;        ///< Dilated image of the square.
            cv::Mat imgGray;       ///< Grayscale image of the square.
            cv::Mat imgThres;      ///< Thresholded image of the square.
            cv::Mat imgBackground; ///< Background image of the square.
            cv::Mat imgSub;        ///< Subtracted image of the square.
            int ID;                ///< Random ID of the square.
        };

        // Square struct data
        /// @brief Structure to store information about each square.
        struct Rectangles {
            cv::Point TL;                ///< Top-left corner of the square.
            cv::Point BR;                ///< Bottom-right corner of the square.
            cv::Scalar COLOR;            ///< Color of the square.
            int KEY;                     ///< Key associated with the square.
            std::string DISPLAYKEY;      ///< Display key associated with the square.
            bool SELECTED;               ///< Indicates whether the square is selected.
            bool MOTION_DETECTED;        ///< Indicates whether motion is detected within the square.
            int ID;                      ///< Random ID of the square.
        };

        extern std::vector<Images> Frames;  ///< Vector containing processed frames for each square.

        extern std::vector<Rectangles> Squares;  ///< Vector containing information about each square.

        extern std::vector<std::vector<cv::Point>> contours;  ///< Detected contours on squares.
    }

    namespace CVJumpLine {

        // Jump Line struct data
        /// @brief Structure to store information about the jump line.
        struct Line {
            cv::Point LineX;             ///< X-coordinate of the jump line.
            cv::Scalar COLOR;            ///< Color of the jump line.
            bool SELECTED = false;       ///< Indicates whether the jump line is selected.
        };

        extern std::vector<Line> Lines;  ///< Vector containing information about the jump line.

        extern bool LineExists; ///< Bool value, true when line exists

        extern const int W; ///< Width of the image above the jump line.
        
        extern const int Y; ///< Y-coordinate of the jump line.

        extern std::vector<std::vector<cv::Point>> mycontours; ///< Detected contours above the jump line.
    }
}