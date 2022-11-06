#include <iostream>//para cout
#include <SDL.h>//para SDL
#include <SDL_image.h>//para SDL de imagen
#include <string>//para string
#include <vector>//para vector
using namespace std;
//SDL2: version:SDL2-devel-2.24.0-VC
//paths relativos a mi proyecto.
//SDL2image: version:SDL2_image-devel-2.6.2-VC

int drawChessBoard(string);

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	string initPosition = "k2r3r/Qb2qp1p/p1N2np1/1p1P4/8/P4PPB/1PP4R/1K6";//"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	int res = drawChessBoard(initPosition);
	return 0;
}

int drawChessBoard(string initPosition) {

	//Inicializaciones
	//Inicializo los modulos del SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}
	//Inicializo SDL_image
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "Error SDL2_image Initialization";
		return 2;
	}
	//creo la ventana
	SDL_Window* window = SDL_CreateWindow("P2-Ajedrez", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		std::cout << "Error window creation";
		return 3;
	}
	//creo el renderer de la imagen
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Error renderer creation";
		return 4;
	}
	//INICIO: espacios separados para cada imagen
	SDL_Rect rect, r2;
	rect.x = 0; r2.x = 65;
	rect.y = 0; r2.y = 80;
	rect.w = 520; r2.w = 64;
	rect.h = 520; r2.h = 64;
	// FIN
	//creo la imagen fondo
	SDL_Surface* fondo_sur = IMG_Load("fondo.png");
	if (fondo_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* fondo_tex = SDL_CreateTextureFromSurface(renderer, fondo_sur);
	if (fondo_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(fondo_sur);
	//creo la imagen blanco-caballo
	SDL_Surface* blanco_caballo_sur = IMG_Load("blanco-caballo.png");
	if (blanco_caballo_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_caballo_tex = SDL_CreateTextureFromSurface(renderer, blanco_caballo_sur);
	if (blanco_caballo_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_caballo_sur);
	//creo la imagen negro-caballo
	SDL_Surface* negro_caballo_sur = IMG_Load("negro-caballo.png");
	if (negro_caballo_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_caballo_tex = SDL_CreateTextureFromSurface(renderer, negro_caballo_sur);
	if (negro_caballo_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_caballo_sur);
	//creo la imagen blanco-torre
	SDL_Surface* blanco_torre_sur = IMG_Load("blanco-torre.png");
	if (blanco_torre_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_torre_tex = SDL_CreateTextureFromSurface(renderer, blanco_torre_sur);
	if (blanco_torre_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_torre_sur);
	//creo la imagen negro-torre
	SDL_Surface* negro_torre_sur = IMG_Load("negro-torre.png");
	if (negro_torre_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_torre_tex = SDL_CreateTextureFromSurface(renderer, negro_torre_sur);
	if (negro_torre_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_torre_sur);
	//creo la imagen blanco-alfil
	SDL_Surface* blanco_alfil_sur = IMG_Load("blanco-alfil.png");
	if (blanco_alfil_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_alfil_tex = SDL_CreateTextureFromSurface(renderer, blanco_alfil_sur);
	if (blanco_alfil_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_alfil_sur);
	//creo la imagen negro-alfil
	SDL_Surface* negro_alfil_sur = IMG_Load("negro-alfil.png");
	if (negro_alfil_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_alfil_tex = SDL_CreateTextureFromSurface(renderer, negro_alfil_sur);
	if (negro_alfil_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_alfil_sur);
	//creo la imagen blanco-reina
	SDL_Surface* blanco_reina_sur = IMG_Load("blanco-reina.png");
	if (blanco_reina_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_reina_tex = SDL_CreateTextureFromSurface(renderer, blanco_reina_sur);
	if (blanco_reina_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_reina_sur);
	//creo la imagen negro-reina
	SDL_Surface* negro_reina_sur = IMG_Load("negro-reina.png");
	if (negro_reina_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_reina_tex = SDL_CreateTextureFromSurface(renderer, negro_reina_sur);
	if (negro_reina_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_reina_sur);
	//creo la imagen blanco-rey
	SDL_Surface* blanco_rey_sur = IMG_Load("blanco-rey.png");
	if (blanco_rey_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_rey_tex = SDL_CreateTextureFromSurface(renderer, blanco_rey_sur);
	if (blanco_rey_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_rey_sur);
	//creo la imagen negro-rey
	SDL_Surface* negro_rey_sur = IMG_Load("negro-rey.png");
	if (negro_rey_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_rey_tex = SDL_CreateTextureFromSurface(renderer, negro_rey_sur);
	if (negro_rey_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_rey_sur);
	//creo la imagen blanco-peon
	SDL_Surface* blanco_peon_sur = IMG_Load("blanco-peon.png");
	if (blanco_peon_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* blanco_peon_tex = SDL_CreateTextureFromSurface(renderer, blanco_peon_sur);
	if (blanco_peon_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(blanco_peon_sur);
	//creo la imagen negro-peon
	SDL_Surface* negro_peon_sur = IMG_Load("negro-peon.png");
	if (negro_peon_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	//creo su textura
	SDL_Texture* negro_peon_tex = SDL_CreateTextureFromSurface(renderer, negro_peon_sur);
	if (negro_peon_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}
	SDL_FreeSurface(negro_peon_sur);

	//Lectura del string
	vector<vector<char>> grid(8, vector<char>(8));

	int row = 0;
	int col = 0;
	for (char c : initPosition) {
		if (isdigit(c)) {
			int num = c - '0';
			for (int i = 0; i < num; i++) {
				grid[row][col] = ' ';
				col++;
			}
			continue;
		}
		if (c == '/') {
			row++;
			col = 0;
			continue;
		}
		grid[row][col] = c;
		col++;
	}


	//Pintado
	//mostrare en loop hasta que me pidan cerrarlo
	while (true) {
		SDL_Event e;
		if (SDL_WaitEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, fondo_tex, NULL, &rect);
		//SDL_RenderCopy(renderer, fondo_tex, NULL, NULL);
		//para las piezas
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				r2.y = 65 * i;//y es vertical
				r2.x = 65 * j;//x es horizontal
				if (grid[i][j] != ' ') {
					if (grid[i][j] == 'N')	SDL_RenderCopy(renderer, blanco_caballo_tex, NULL, &r2);
					if (grid[i][j] == 'n')	SDL_RenderCopy(renderer, negro_caballo_tex, NULL, &r2);
					if (grid[i][j] == 'R')	SDL_RenderCopy(renderer, blanco_torre_tex, NULL, &r2);
					if (grid[i][j] == 'r')	SDL_RenderCopy(renderer, negro_torre_tex, NULL, &r2);
					if (grid[i][j] == 'B')	SDL_RenderCopy(renderer, blanco_alfil_tex, NULL, &r2);
					if (grid[i][j] == 'b')	SDL_RenderCopy(renderer, negro_alfil_tex, NULL, &r2);
					if (grid[i][j] == 'Q')	SDL_RenderCopy(renderer, blanco_reina_tex, NULL, &r2);
					if (grid[i][j] == 'q')	SDL_RenderCopy(renderer, negro_reina_tex, NULL, &r2);
					if (grid[i][j] == 'K')	SDL_RenderCopy(renderer, blanco_rey_tex, NULL, &r2);
					if (grid[i][j] == 'k')	SDL_RenderCopy(renderer, negro_rey_tex, NULL, &r2);
					if (grid[i][j] == 'P')	SDL_RenderCopy(renderer, blanco_peon_tex, NULL, &r2);
					if (grid[i][j] == 'p')	SDL_RenderCopy(renderer, negro_peon_tex, NULL, &r2);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	//libero los recursos al finalizar
	SDL_DestroyTexture(blanco_caballo_tex);
	SDL_DestroyTexture(negro_caballo_tex);
	SDL_DestroyTexture(blanco_torre_tex);
	SDL_DestroyTexture(negro_torre_tex);
	SDL_DestroyTexture(blanco_alfil_tex);
	SDL_DestroyTexture(negro_alfil_tex);
	SDL_DestroyTexture(blanco_reina_tex);
	SDL_DestroyTexture(negro_reina_tex);
	SDL_DestroyTexture(blanco_rey_tex);
	SDL_DestroyTexture(negro_rey_tex);
	SDL_DestroyTexture(blanco_peon_tex);
	SDL_DestroyTexture(negro_peon_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

}