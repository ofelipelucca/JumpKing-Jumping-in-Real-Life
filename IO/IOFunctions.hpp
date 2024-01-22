#pragma once

#include <fstream>
#include "../Graphics/GraphicsFunctions.hpp"
#include "../Graphics/Var/GraphicsValues.hpp"

namespace IO {
	class FileManager {
	public:
		/// @brief Reads saved squares from 'SavedSquaresPositions.txt'.
		/// @details Funcao para ler os quadrados salvos de 'SavedSquaresPositions.txt'.
		static void readSavedSquares();


		/// @brief Saves squares in 'SavedSquaresPositions.txt'.
		/// @details Funcao para salvar quadrados em 'SavedSquaresPositions.txt'.
		static void saveSquares();

		/// @brief Reads the TOLERANCE value from 'DetectionTolerance.txt'.
		/// @details Funcao para ler o valor de TOLERANCE de 'DetectionTolerance.txt'.
		static void readTolerance();
	};

	class UserInput {
	public:
		/// @brief Displays instructions.
		/// @details Funcao para exibir instrucoes.
		static void DisplayInstructions();

		/// @brief Gets user input for jump detection activation.
		/// @details Funcao para obter a entrada do usuario para a ativacao da deteccao de pulo.
		/// @return Returns true if the user activates jump detection, false otherwise.
		static bool activateJumpDetection();

		/// @brief Customizes elements on the window, changes position, binds squares.
		/// @details Funcao para customizar os elementos na janela, mudar posicao, bindar quadrados.
		///
		/// @overload
		/// @brief Moves the jump line.
		static void CustomElementsOnWindow();

		/// @overload
		/// @brief Customizes elements on the window for the selected square.
		/// @param selectedSquare The index of the square selected by the user.
		static void CustomElementsOnWindow(unsigned selectedSquare, IO::FileManager& fileManager);

		/// @brief Handles mouse events.
		/// @details Funcao para lidar com eventos de mouse.
		///
		/// @param event The type of mouse event.
		/// @param x The x-coordinate of the mouse event.
		/// @param y The y-coordinate of the mouse event.
		/// @param flags Flags associated with the mouse event.
		/// @param userdata User-defined data.
		static void onMouse(int event, int x, int y, int flags, void* userdata);
	};
}