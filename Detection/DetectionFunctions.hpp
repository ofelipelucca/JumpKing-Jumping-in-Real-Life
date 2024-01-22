#pragma once

namespace Detection {
	namespace ClickDetection {

		/// @brief Function to verify if the registered click was inside a square.
		/// @details Funcao para verificar se o clique registrado foi dentro de um quadrado.
		///
		/// @param i The index of the square to be verified.
		/// @param x The x-coordinate of the registered click.
		/// @param y The y-coordinate of the registered click.
		///
		/// @return Returns true if the click was inside a square, false otherwise.
		bool WasClickOnSquare(unsigned i, int x, int y);
	}

	class MotionDetection {
	public:
		/// @brief Function to detect movement.
		/// @details Funcao para detectar o movimento.
		///
		void detectMovement();

		/// @brief Function to detect jump.
		/// @details Funcao para detectar o pulo.
		///
		void detectJump();
	};
}