#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include "Detection/DetectionFunctions.hpp"
#include "Detection/Var/DetectionValues.hpp"
#include "IO/IOFunctions.hpp"
#include "IO/Var/IOValues.hpp"
#include "Graphics/GraphicsFunctions.hpp"
#include "Graphics/Var/GraphicsValues.hpp"

using namespace std;

int main() {
    // Initialize instances of the core program classes
    // Inicialize instancias das classes principais do programa
    IO::FileManager fileManager;
    IO::UserInput userInput;
    Detection::MotionDetection motionDetection;
    Graphics::ImageManager imageManager;

    // Initialize the camera
    // Inicializa a camera
    int cam = Graphics::CameraUtils::initializeCamera();
    cv::VideoCapture cap(cam);
    cap.read(GraphicsValues::CVMatFrames::imgFlip);

    // Load saved squares from 'SavedSquaresPositions.txt'
    // Carrega os quadrados salvos de 'SavedSquaresPositions.txt'
    fileManager.readSavedSquares();

    // Load TOLERANCE value from 'DetectionTolerance.txt'
    // Carrega o valor da TOLERANCE de 'DetectionTolerance.txt'
    fileManager.readTolerance();

    // Display instructions
    // Imprime instrucoes
    userInput.DisplayInstructions();

    // Get user input for jump detection activation
    // Registra a entrada do usuario para deteccao de pulo 
    DetectionValues::jumpDetectionActivated = userInput.activateJumpDetection();

    // Initialize threads for jump detection and moviment detection
    // Inicializa threads de deteccao de pulo e deteccao de movimento
    thread keyDetectionThread([&motionDetection]() {
        motionDetection.detectMovement();
    });

    thread jumpDetectionThread([&motionDetection]() {
        motionDetection.detectJump();
    });

    // Declares window
    // Declara janela
    cv::namedWindow("Jump King Jumping in Real Life by Felipe Lucca", cv::WINDOW_AUTOSIZE);
  
    // Program loop
    while (true) {
        // Read frame from the camera
        // Le o frame da camera
        cap.read(GraphicsValues::CVMatFrames::img);
        cv::flip(GraphicsValues::CVMatFrames::img, GraphicsValues::CVMatFrames::imgFlip, 1);

        // Handle mouse events
        // Lida com eventos do mouse
        cv::setMouseCallback("Jump King Jumping in Real Life by Felipe Lucca", userInput.onMouse);

        // Preprossing the frames for moviment detection and drawing the elements on the window
        // Preprocessando os frames para deteccao de movimento e desenhando os elementos na janela
        imageManager.preprocessImage(GraphicsValues::CVMatFrames::imgFlip);
        imageManager.drawSquares(GraphicsValues::CVMatFrames::imgFlip);

        if (DetectionValues::jumpDetectionActivated) {

            imageManager.drawJumpLine(GraphicsValues::CVMatFrames::imgFlip);
            imageManager.preprocessImageAboveLine(GraphicsValues::CVMatFrames::imgFlip);
        }

        // Moving elements on window and binding keys
        // Movendo elementos na janela e atribuindo teclas
        if (IOValues::selectedSquare != -1) {

            userInput.CustomElementsOnWindow(IOValues::selectedSquare, fileManager);
        }
        else if (DetectionValues::jumpDetectionActivated) {

            if (GraphicsValues::CVJumpLine::Lines[0].SELECTED == true) {

                userInput.CustomElementsOnWindow();
            }
        }
        
        cv::imshow("Jump King Jumping in Real Life by Felipe Lucca", GraphicsValues::CVMatFrames::imgFlip);

        cv::waitKey(1);
    }

    // Wait threads to close and release camera
    // Espera as threads fecharem e libera a camera
    keyDetectionThread.join();
    jumpDetectionThread.join();
    cap.release();

    return 0;
}