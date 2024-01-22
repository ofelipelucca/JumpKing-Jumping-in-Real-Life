#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "IOFunctions.hpp"
#include "Var/IOValues.hpp"
#include "../Graphics/GraphicsFunctions.hpp"
#include "../Graphics/Var/GraphicsValues.hpp"
#include "../Detection/DetectionFunctions.hpp"
#include "../Detection/Var/DetectionValues.hpp"
#include "../MapKeys/MapKeys.hpp"

using namespace std;
using namespace cv;

// Funcion to read and create the saved squares 
// Funcao para ler e criar os quadrados salvos
void IO::FileManager::readSavedSquares() {
    ifstream SavedSquares;
    int QntSquares;

    SavedSquares.open("data/SavedSquaresPositions.txt");

    if (SavedSquares.is_open()) {

        SavedSquares >> QntSquares;

        for (int i = 0; i < QntSquares; i++) {

            unsigned SquareX, SquareY, SquareKey;
            string SquareDisplayName;

            SavedSquares >> SquareX >> SquareY >> SquareKey >> SquareDisplayName;

            Graphics::ImageManager::createSquare(SquareX, SquareY, SquareKey, SquareDisplayName);
        }

        cout << "The saved squares were loaded successfully." << endl;

        SavedSquares.close();
    }
    else { cout << "'SavedSquaresPositions.txt' file does not exist, unable to load saved squares." << endl; }
}

// Function to save existing squares
// Funcao para salvar os quadrados existentes
void IO::FileManager::saveSquares() {
    try {
        ofstream SavedSquares("data/SavedSquaresPositions.txt");

        if (SavedSquares.is_open()) {

            SavedSquares << GraphicsValues::CVSquares::Squares.size() << endl;

            for (int i = 0; i < GraphicsValues::CVSquares::Squares.size(); i++) {

                SavedSquares << GraphicsValues::CVSquares::Squares[i].TL.x << endl;
                SavedSquares << GraphicsValues::CVSquares::Squares[i].TL.y << endl;
                SavedSquares << GraphicsValues::CVSquares::Squares[i].KEY << endl;
                SavedSquares << GraphicsValues::CVSquares::Squares[i].DISPLAYKEY << endl;
            }

            SavedSquares.close();
        }
    }
    catch (const exception& e) {
        cerr << "The program could not save properly to SavedSquaresPositions.txt, the program returned the following error: " << e.what() << endl;
    }
}

// Function to read TOLERANCE value
// Funcao para ler o valor de TOLERANCE'
void IO::FileManager::readTolerance() {
    ifstream MoveTOLERANCE;
    MoveTOLERANCE.open("data/DetectionTolerance.txt");

    if (MoveTOLERANCE.is_open()) {

        MoveTOLERANCE >> GraphicsValues::TOLERANCE;

        cout << "The tolerance value was loaded successfully" << endl;

        MoveTOLERANCE.close();
    }
    else { cout << "'DetectionTolerance.txt' file does not exist, unable to load saved tolarence, using the default value." << endl; }
}

// Function to display instructions
// Funcao para exibir instrucoes
void IO::UserInput::DisplayInstructions() {

    cout << "Welcome :) This program was made by Felipe Lucca" << endl;
    cout << "Repository on GitHub: ..." << endl;

    cout << endl << "Choose language: (send 'pt-br' or 'en-us')" << endl;

    string LanguageINPUT;

    cin >> LanguageINPUT;

    if (LanguageINPUT == "pt-br") {

        cout << endl << "pt-br";

        cout << endl << "USO:" << endl;
        cout << endl << "COMO CRIAR UM QUADRADO:" << endl
            << "- Clique duplo com o botao esquerdo do mouse para adicionar um quadrado na posicao atual do mouse." << endl;

        cout << endl << "COMO BINDAR UMA TECLA:" << endl
            << "- Clique em um quadrado para seleciona-lo." << endl
            << "- Pressione a tecla para bindar no quadrado selecionado" << endl;

        cout << endl << "COMO MOVER UM QUADRADO:" << endl
            << "- Clique em um quadrado para seleciona-lo." << endl
            << "- Use as setas do teclado para mover o quadrado dentro da janela." << endl;

        cout << endl << "COMO REMOVER UM QUADRADO:" << endl
            << "- Clique em um quadrado para seleciona-lo." << endl
            << "- Clique com botao direito do mouse dentro do quadrado selecionado para remove-lo" << endl;

        cout << endl << "Ativar deteccao de pulo? (envie 'sim' ou 'nao')" << endl;
    }
    else {

        cout << endl << "en-us";

        cout << endl << "USAGE:" << endl;
        cout << endl << "HOW TO CREATE A SQUARE:" << endl
            << "- Double-click with the left mouse button to add a detection square at the clicked location." << endl;

        cout << endl << "HOW TO BIND A KEY:" << endl
            << "- Click on a square to select it." << endl
            << "- Press a key to bind it to the selected square." << endl;

        cout << endl << "HOW TO MOVE A SQUARE:" << endl
            << "- Click on a square to select it." << endl
            << "- Use arrow keys to move the square within the window." << endl;

        cout << endl << "HOW TO REMOVE A SQUARE:" << endl
            << "- Click on a square to select it." << endl
            << "- Right-click on a square to remove it." << endl;

        cout << endl << "Enable jump detection? (send 'yes' or 'no')" << endl;
    }
}

// Function to get user input for jump detection activation
// Funcao obter a entrada do usuario para a ativacao da deteccao de pulo
bool IO::UserInput::activateJumpDetection() {
    string JumpDetectionINPUT;

    cin >> JumpDetectionINPUT;

    if (JumpDetectionINPUT == "yes" || JumpDetectionINPUT == "sim") {

        cout << endl << ">> Jump Detection ON\n\n\n\n" << endl;

        return true;
    }
    
    cout << endl << ">> Jump Detection OFF\n\n\n\n" << endl;
    return false;
}

// Function to handle mouse events
// Funcao para lidar com eventos de mouse
void IO::UserInput::onMouse(int event, int x, int y, int flags, void* userdata) {
    try {
        if (event == EVENT_LBUTTONDOWN) {

            if (DetectionValues::jumpDetectionActivated && GraphicsValues::CVJumpLine::Lines.size() != 0) {

                // Click on the jump line
                if (y >= GraphicsValues::CVJumpLine::Lines[0].LineX.y - 15 && y <= GraphicsValues::CVJumpLine::Lines[0].LineX.y + 15) {

                    GraphicsValues::CVJumpLine::Lines[0].SELECTED = true;
                }
                else if (GraphicsValues::CVJumpLine::Lines[0].SELECTED == true) {

                    GraphicsValues::CVJumpLine::Lines[0].SELECTED = false;
                }
            }

            if (GraphicsValues::CVSquares::Squares.size() != 0) {

                for (int i = 0; i < GraphicsValues::CVSquares::Squares.size(); i++) {

                    // Click on a square
                    if (Detection::ClickDetection::WasClickOnSquare(i, x, y)) {

                        if (DetectionValues::jumpDetectionActivated) {

                            GraphicsValues::CVJumpLine::Lines[0].SELECTED = false;
                        }

                        if (IOValues::selectedSquare == GraphicsValues::CVSquares::Squares[i].ID) { break; }
                        else {
                            for (auto& square : GraphicsValues::CVSquares::Squares) {
                                if (square.ID == IOValues::selectedSquare) {
                                    square.SELECTED = false;
                                    break;
                                }
                            }
                        }

                        IOValues::selectedSquare = GraphicsValues::CVSquares::Squares[i].ID;

                        GraphicsValues::CVSquares::Squares[i].SELECTED = true;

                        break;
                    }
                    else if (IOValues::selectedSquare != -1) {

                        for (auto& square : GraphicsValues::CVSquares::Squares) {
                            if (square.ID == IOValues::selectedSquare) {
                                square.SELECTED = false;
                                break;
                            }
                        }

                        IOValues::selectedSquare = -1;
                    }
                }
            }
        }
        if (event == EVENT_LBUTTONDBLCLK) {
            Graphics::ImageManager::createSquare(x, y, 0, "...");
        }
        if (event == EVENT_RBUTTONDOWN) {

            if (GraphicsValues::CVSquares::Squares.size() != 0 || IOValues::selectedSquare != -1) {

                for (int i = 0; i < GraphicsValues::CVSquares::Squares.size(); i++) {

                    if (Detection::ClickDetection::WasClickOnSquare(i, x, y)) {
                        try {
                            auto lambda = IOValues::selectedSquare;

                            GraphicsValues::CVSquares::Squares.erase(remove_if(GraphicsValues::CVSquares::Squares.begin(), GraphicsValues::CVSquares::Squares.end(),
                                [lambda](const GraphicsValues::CVSquares::Rectangles& square) { return square.ID == IOValues::selectedSquare; }), GraphicsValues::CVSquares::Squares.end());

                            GraphicsValues::CVSquares::Frames.erase(remove_if(GraphicsValues::CVSquares::Frames.begin(), GraphicsValues::CVSquares::Frames.end(),
                                [lambda](const GraphicsValues::CVSquares::Images& frame) { return frame.ID == IOValues::selectedSquare; }), GraphicsValues::CVSquares::Frames.end());

                            IOValues::selectedSquare = -1;

                            IO::FileManager::saveSquares();
                        }
                        catch (const exception& e) {
                            cerr << "Nao foi possivel remover o quadrado selecionado, o metodo erase retornou o seguinte erro: " << e.what() << endl;
                        }
                    }
                }
            }
        }
    }
    catch (const exception& e) {
        cerr << "It was not possible to handle the mouse event, the program returned the following error: " << e.what() << endl;
    }
}

// Function to change Y position of the jump line
// Funcao para mudar a posicao Y da linha de pulo
void IO::UserInput::CustomElementsOnWindow() {
    try {
        int keyPressed = waitKeyEx(10);

        if (GraphicsValues::CVJumpLine::Lines[0].SELECTED == true) {

            // Moves the jump line up
            if (keyPressed == 2490368) {

                if (GraphicsValues::CVJumpLine::Lines[0].LineX.y > 5) {

                    GraphicsValues::CVJumpLine::Lines[0].LineX.y -= 5;
                    Graphics::ImageManager::resizeJumpArea();
                }
            }
            // Moves the jump line down
            if (keyPressed == 2621440) {

                if (GraphicsValues::CVJumpLine::Lines[0].LineX.y + 5 < GraphicsValues::CVMatFrames::imgFlip.size().height) {

                    GraphicsValues::CVJumpLine::Lines[0].LineX.y += 5;
                    Graphics::ImageManager::resizeJumpArea();
                }
            }
        }
    }
    catch (const exception& e) {
        cerr << "It was not possible to custom the jump line height, the program returned the following error: " << e;what() << endl;
    }
}

// Function to move and bind the selected square 
// Funcao para mover e bindar o quadrado selecionado
void IO::UserInput::CustomElementsOnWindow(unsigned selectedSquare, IO::FileManager& fileManager) {
        try {
        int keyPressed = waitKeyEx(10);

        for (auto& square : GraphicsValues::CVSquares::Squares) {
            if (square.ID == selectedSquare) {

                // Moves the selected square to left
                // Move o quadrado selecionado para a esquerda
                if (keyPressed == 2424832 && square.TL.x > 5) {

                    square.TL.x -= 5;

                    square.BR = Point(square.TL.x + 80, square.TL.y + 100);
                }
                // Moves the selected square up
                // Move o quadrado selecionado para cima
                if (keyPressed == 2490368 && square.TL.y > 5) {

                    square.TL.y -= 5;

                    square.BR = Point(square.TL.x + 80, square.TL.y + 100);
                }
                // Moves the selected square to right
                // Move o quadrado selecionado para a direita
                if (keyPressed == 2555904 && square.BR.x + 5 < GraphicsValues::CVMatFrames::imgFlip.size().width) {

                    square.TL.x += 5;

                    square.BR = Point(square.TL.x + 80, square.TL.y + 100);
                }
                // Moves the seSelectedSquarelected square down
                // Move o quadrado selecionado para baixo
                if (keyPressed == 2621440 && square.BR.y + 5 < GraphicsValues::CVMatFrames::imgFlip.size().height) {

                    square.TL.y += 5;

                    square.BR = Point(square.TL.x + 80, square.TL.y + 100);
                }

                // Assign bind to the selected square
                // Atribue a tecla ao quadrado selecionado
                if (MapKeys::keyMap.find(static_cast<char>(keyPressed)) != MapKeys::keyMap.end()) {

                    square.KEY = MapKeys::keyMap[static_cast<char>(keyPressed)];

                    square.DISPLAYKEY = toupper(static_cast<char>(keyPressed));
                }
                // Special keys
                // Teclas especiais
                else if (MapKeys::keyMapEX.find(static_cast<char>(keyPressed)) != MapKeys::keyMapEX.end()) {

                    square.KEY = MapKeys::keyMapEX[keyPressed];

                    MapKeys::keyEXName.find(static_cast<char>(keyPressed));

                    square.DISPLAYKEY = MapKeys::keyEXName[square.ID];
                }

                fileManager.saveSquares();

                break;
            }
        }
    }
    catch (const exception& e) {
        cerr << "It was not possible to custom the selected square, the program returned the following error: " << e.what() << endl;
    }
}