#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include "../IO/IOFunctions.hpp"

namespace Graphics {
	namespace CameraUtils {

		/// @brief Initializes the camera.
		/// @details Funcao para inicializar a camera.
		/// 
		/// @return Retorna o indice da camera encontrada, caso nao encontre, retorna 6.
		unsigned initializeCamera();
	}

	class ImageManager {
	public:

		/// @brief Creates a square at the specified position.
		/// @details Funcao para criar um quadrado na posicao especificada.
		/// 
		/// @param SquareX The x-coordinate of the square.
		/// @param SquareY The y-coordinate of the square.
		/// @param SquareKey The KEY code of the square.
		/// @param SquareDisplayName The Display Name of the KEY.
		static void createSquare(unsigned SquareX, unsigned SquareY, unsigned SquareKey, std::string SquareDisplayName);

		/// @brief Resizes the image above the jump line.
		/// @details Funcao para redimensionar a imagem acima da linha de pulo.
		static void resizeJumpArea();

		/// @brief Displays the jump line.
		/// @details Funcao para exibir a linha de pulo.
		///
		/// @param imgFlip The flipped image.
		void drawJumpLine(cv::Mat imgFlip);

		/// @brief Preprocesses the image above the jump line.
		/// @details Funcao para pre-processar a imagem acima da linha de pulo.
		///
		/// @param imgFlip The flipped image.
		void preprocessImageAboveLine(cv::Mat imgFlip);

		/// @brief Preprocesses the image and positions squares.
		/// @details Funcao para pre-processar a imagem e posicionar os quadrados.
		///
		/// @param imgFlip The flipped image.
		void preprocessImage(cv::Mat imgFlip);

		/// @brief Draws the squares on the window.
		/// @details Funcao para desenhar os quadrados na janela.
		///
		/// @param imgFlip The flipped image.
		void drawSquares(cv::Mat imgFlip);
	};
}