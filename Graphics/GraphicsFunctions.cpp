#include <opencv2/opencv.hpp>
#include <vector>
#include <random>
#include "GraphicsFunctions.hpp"
#include "Var/GraphicsValues.hpp"
#include "../IO/IOFunctions.hpp"

using namespace std;
using namespace cv;

// Attempt to open a camera, index 1 to 5
// Tenta abror a camera, indice 1 ate 5
unsigned Graphics::CameraUtils::initializeCamera() {
    for (unsigned i = 0; i < 5; i++) {

        VideoCapture cap(i);

        if (cap.isOpened()) {

            cout << "Camera index chosen: " << i << endl;
            cap.release();

            return i;
        }
    }
    cerr << "The program could not find an available camera on the system" << endl;

    return 1;
}

// Function to create a new square
// Funcao para criar um novo quadrado
void Graphics::ImageManager::createSquare(unsigned SquareX, unsigned SquareY, unsigned SquareKey, string SquareDisplayName) {
    
    // Checks if the square is valid
    // Verifica se o quadrado eh valido
    if (SquareX > 0 && SquareY > 0 && SquareX + 80 <= GraphicsValues::CVMatFrames::imgFlip.size().width && SquareY + 100 <= GraphicsValues::CVMatFrames::imgFlip.size().height) {
        try {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(1, 1000);

            GraphicsValues::CVSquares::Rectangles new_square;
            new_square.TL = Point(SquareX, SquareY);
            new_square.BR = Point(SquareX + 80, SquareY + 100);
            new_square.COLOR = Scalar(0, 0, 255); // BGR FORMAT
            new_square.KEY = SquareKey;
            new_square.DISPLAYKEY = SquareDisplayName;
            new_square.SELECTED = false;
            new_square.MOTION_DETECTED = false;
            new_square.ID = dis(gen);

            GraphicsValues::CVSquares::Squares.push_back(new_square);

            GraphicsValues::CVSquares::Images new_frame;
            new_frame.ID = new_square.ID;
            GraphicsValues::CVSquares::Frames.push_back(new_frame);

            IO::FileManager::saveSquares();
        }
        catch (const exception& e) {
            cerr << "It was not possible to create a square, the program returned the following error: " << e.what() << endl;
        }
    }
}

// Function to resize the image above the jump line
// Funcao para redimensionar a imagem acima da linha de pulo
void Graphics::ImageManager::resizeJumpArea() {
    try {
        Size new_jumpareasize(GraphicsValues::CVMatFrames::imgFlip.size().width, GraphicsValues::CVJumpLine::Lines[0].LineX.y);

        resize(GraphicsValues::CVMatFrames::JumpIMGCrop, GraphicsValues::CVMatFrames::JumpIMGCrop, new_jumpareasize);
        resize(GraphicsValues::CVMatFrames::JumpIMGGray, GraphicsValues::CVMatFrames::JumpIMGGray, new_jumpareasize);
        resize(GraphicsValues::CVMatFrames::JumpIMGBackground, GraphicsValues::CVMatFrames::JumpIMGBackground, new_jumpareasize);
        resize(GraphicsValues::CVMatFrames::JumpIMGThres, GraphicsValues::CVMatFrames::JumpIMGThres, new_jumpareasize);
        resize(GraphicsValues::CVMatFrames::JumpIMGSub, GraphicsValues::CVMatFrames::JumpIMGSub, new_jumpareasize);
        resize(GraphicsValues::CVMatFrames::JumpIMGDil, GraphicsValues::CVMatFrames::JumpIMGDil, new_jumpareasize);
    }
    catch (const exception& e) {
        cerr << "It was not possible to resize the jump detection image, the program returned the following error: " << e.what() << endl;
    }
}

// Function to display the jump line
// Funcao para exibir a linha de pulo
void Graphics::ImageManager::drawJumpLine(Mat imgFlip) {
    try {
        if (GraphicsValues::CVJumpLine::Lines.size() == 0) {

            GraphicsValues::CVJumpLine::Line new_jumpline;
            new_jumpline.LineX = Point(0, 120);
            new_jumpline.COLOR = Scalar(255, 255, 255); // BGR FORMAT
            new_jumpline.SELECTED = false;

            GraphicsValues::CVJumpLine::Lines.push_back(new_jumpline);
        }

        if (GraphicsValues::CVJumpLine::Lines[0].SELECTED == true) {

            GraphicsValues::CVJumpLine::Lines[0].COLOR = Scalar(255, 0, 0); // BGR FORMAT
        }
        if (GraphicsValues::CVJumpLine::Lines[0].SELECTED == false) {

            GraphicsValues::CVJumpLine::Lines[0].COLOR = Scalar(255, 255, 255); // BGR FORMAT
        }

        line(imgFlip, GraphicsValues::CVJumpLine::Lines[0].LineX, Point(imgFlip.size().width, GraphicsValues::CVJumpLine::Lines[0].LineX.y), GraphicsValues::CVJumpLine::Lines[0].COLOR, 1.5);

        GraphicsValues::CVJumpLine::LineExists = true;
    } 
    catch (const exception& e) {
        cerr << "It was not possible to draw the jump line, the program returned the following error: " << e.what() << endl;
    }
}

// Function to preprocess the image above the jump line
// Funcao para pre-processar a imagem acima da linha de pulo
void Graphics::ImageManager::preprocessImageAboveLine(Mat imgFlip) {
    try {
        Rect roi(Point(0, 0), Point(imgFlip.size().width, GraphicsValues::CVJumpLine::Lines[0].LineX.y));

        GraphicsValues::CVMatFrames::JumpIMGCrop = imgFlip(roi);

        cvtColor(GraphicsValues::CVMatFrames::JumpIMGCrop, GraphicsValues::CVMatFrames::JumpIMGGray, COLOR_BGR2GRAY);

        if (GraphicsValues::CVMatFrames::JumpIMGBackground.empty()) {

            GraphicsValues::CVMatFrames::JumpIMGBackground = GraphicsValues::CVMatFrames::JumpIMGGray.clone();
        }

        addWeighted(GraphicsValues::CVMatFrames::JumpIMGBackground, 0.83, GraphicsValues::CVMatFrames::JumpIMGGray, 0.17, 0, GraphicsValues::CVMatFrames::JumpIMGBackground);

        absdiff(GraphicsValues::CVMatFrames::JumpIMGBackground, GraphicsValues::CVMatFrames::JumpIMGGray, GraphicsValues::CVMatFrames::JumpIMGSub);

        threshold(GraphicsValues::CVMatFrames::JumpIMGSub, GraphicsValues::CVMatFrames::JumpIMGThres, 23, 255, THRESH_BINARY);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

        dilate(GraphicsValues::CVMatFrames::JumpIMGThres, GraphicsValues::CVMatFrames::JumpIMGDil, kernel);
    }
    catch (const exception& e) {
        cerr << "OpenCV could not process the jump detection image properly, the program returned the following error: " << e.what() << endl;
    }
}

// Function to preprocess the image and position squares
// Funcao para pre-processar a imagem e posicionar os quadrados
void Graphics::ImageManager::preprocessImage(Mat imgFlip) {
    try {
        for (int i = 0; i < GraphicsValues::CVSquares::Squares.size(); i++) {

            Rect roi(GraphicsValues::CVSquares::Squares[i].TL, Size(80, 100));

            GraphicsValues::CVSquares::Frames[i].imgCrop = imgFlip(roi);

            cvtColor(GraphicsValues::CVSquares::Frames[i].imgCrop, GraphicsValues::CVSquares::Frames[i].imgGray, COLOR_BGR2GRAY);

            if (GraphicsValues::CVSquares::Frames[i].imgBackground.empty()) {

                GraphicsValues::CVSquares::Frames[i].imgBackground = GraphicsValues::CVSquares::Frames[i].imgGray.clone();
            }

            addWeighted(GraphicsValues::CVSquares::Frames[i].imgBackground, 0.83, GraphicsValues::CVSquares::Frames[i].imgGray, 0.17, 0, GraphicsValues::CVSquares::Frames[i].imgBackground);

            absdiff(GraphicsValues::CVSquares::Frames[i].imgBackground, GraphicsValues::CVSquares::Frames[i].imgGray, GraphicsValues::CVSquares::Frames[i].imgSub);

            threshold(GraphicsValues::CVSquares::Frames[i].imgSub, GraphicsValues::CVSquares::Frames[i].imgThres, 23, 255, THRESH_BINARY);

            Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

            dilate(GraphicsValues::CVSquares::Frames[i].imgThres, GraphicsValues::CVSquares::Frames[i].imgDil, kernel);

            putText(imgFlip, GraphicsValues::CVSquares::Squares[i].DISPLAYKEY, Point(GraphicsValues::CVSquares::Squares[i].TL.x + 10, GraphicsValues::CVSquares::Squares[i].TL.y + 45), FONT_HERSHEY_DUPLEX, 0.5, GraphicsValues::CVSquares::Squares[i].COLOR, 1.99);
        }
    }
    catch (const exception& e) {
        cerr << "OpenCV could not process the image properly, the program returned the following error: " << e.what() << endl;
    }
}

// Function to draw squares
// Funcao para desenhar os quadrados   
void Graphics::ImageManager::drawSquares(Mat imgFlip) {
    try {
        if (GraphicsValues::CVSquares::Squares.size() != 0) {

            for (int i = 0; i < GraphicsValues::CVSquares::Squares.size(); i++) {

                Scalar SquareCOLOR = GraphicsValues::CVSquares::Squares[i].COLOR;

                rectangle(imgFlip, GraphicsValues::CVSquares::Squares[i].TL, GraphicsValues::CVSquares::Squares[i].BR, SquareCOLOR, 3);
            }
        }
    }
    catch (const exception& e) {
        cerr << "It was not possible to draw the squares properly, the program returned the following error: " << e.what() << endl;
    }
}