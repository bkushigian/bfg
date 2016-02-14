#include "winManager.hpp"

winManager::winManager(){
	displayMode = DSP_TEXT;		// Start with text screen
	WIDTH = 1000; HEIGHT = 1000; MAX_ITERS = 255;
	pixArray = new Uint8[HEIGHT * WIDTH * 4];
	winMain.create(VideoMode(WIDTH, HEIGHT), "Fractals");
	FM.setWM(this);
}

void winManager::mainLoop(){
	/* Clear/Display black */
    winMain.clear(Color::Black);
    winMain.display();

    // Setup Arr
	setPixArray( FM.getCurrent()->getGrid(),  WIDTH, HEIGHT);
	
	/* image/texture for display */

	image.create(WIDTH, HEIGHT, pixArray);
	if (!texture.create(WIDTH,HEIGHT)) return;
	texture.update(image);
	sprite.setTexture(texture);
	std::cout << "Entering Loop\n";
    while (winMain.isOpen())
    {
        Event event;
		int eventNum = 0;
        while(winMain.pollEvent(event)) {
			eventNum = handleEvent(event);	
			if (eventNum == 2){
				std::cout << "Creating Image\n";
				
				image.create(WIDTH, HEIGHT, pixArray);
				std::cout << "Updating Texture";
				texture.update(image);
				
				std::cout << "Setting Sprite Texture\n";
				sprite.setTexture(texture);
			}
			else if (eventNum == 3){
				winMain.clear(sf::Color::Black);
				winMain.display();
			}
        }
        winMain.clear(sf::Color::Black);
        winMain.draw(sprite);

        winMain.display();
    }
}



void winManager::addFractal(fractal* f){
	FM.add(f);
}

int winManager::handleEvent(sf::Event event){
	if (displayMode & DSP_CMND) {
		return handleCmndEvent(event);
	}
	else{
		return handleNormalEvent(event);
	}
}

int winManager::handleCmndEvent(sf::Event event){
	toggleCmnd();
	return 0;
}

int winManager::handleNormalEvent(sf::Event event){
    switch (event.type)
    {
        /* Closed */
        case Event::Closed:
            return 1;
        /* Key Pressed */
        case Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) toggleCmnd();
			// Command Line
			if (event.key.code == sf::Keyboard::C) toggleCmnd();
			// Quit
			if (event.key.code == sf::Keyboard::Q) winMain.close();
			// Next Fractal
			if (event.key.code == sf::Keyboard::N     ) {
				FM.next();
				FM.draw();
				
				return 2;
			}
			// Color Black
			if (event.key.code == sf::Keyboard::B     ) {
				return 3;
			}
			// Dump Info
			if(event.key.code == sf::Keyboard::I	  ){
				std::cout << "===================== Info ======================\n";
				std::cout << "\tWIDTH.............. " << WIDTH << std::endl;
				std::cout << "\tHEIGHT............. " << HEIGHT << std::endl;
				std::cout << "\tCURRENT............ " << FM.getCurrent()->getName();
				std::cout << std::endl;
			}
			return 0;
        /* Resize */
        case Event::Resized:
            //glViewport(0, 0, event.size.width, event.size.height);
            return 0;
        /* Loose Focus */
        case Event::LostFocus:
            //std::cout << "lost focus" << std::endl;
            return 0;
        /* Gained Focus */
        case Event::GainedFocus:
            //std::cout << "gained focus" << std::endl;
            return 0;
        /* Mouse Wheel Scroll */
        case Event::MouseWheelScrolled:
            // if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
            //     cout << "wheel type: vertical" << endl;
            // else if (event.mouseWheelScroll.wheel == Mouse::HorizontalWheel)
            //     cout << "wheel type: horizontal" << endl;
            // else
            //     cout << "wheel type: unknown" << endl;
            //     cout << "wheel movement: " << event.mouseWheelScroll.delta << endl;
            //     cout << "mouse x: " << event.mouseWheelScroll.x << endl;
            //     cout << "mouse y: " << event.mouseWheelScroll.y << endl;
                return 0;
        /* Mouse Button Pressed */
        case Event::MouseButtonPressed:
            return 0;
        /* Mouse Moved */
        case Event::MouseMoved:
            // cout  << "mouse pos: (" << event.mouseMove.x << ',' << event.mouseMove.y << ")\n";
            return 0;
        case Event::MouseEntered:
            // cout << "mouse entered window\n";
            return 0;
        case Event::MouseLeft:
            // cout <<"mouse left window\n";
            return 0;
        default:
            return 0;
    }
}



void winManager::setPixArray(Uint8* pix, Uint16* grid, int width, int height){

	std::cout << "SetPixArray()\n";
    for (int i = 0; i < height*width; ++i){
		pix[4*i] = (15 * grid[i]) % 256;
		pix[4*i+1] = (11 * grid[i]) % 256;
		pix[4*i+2] = (18 * grid[i]) % 256;
		pix[4*i + 3] = 255;
    }
}

void winManager::setPixArray(Uint16* grid, int width, int height){
	std::cout << "SetPixArray()\n";
	for (int i = 0; i < height*width; ++i){
		pixArray[4*i] = (15 * grid[i]) % 256;
		pixArray[4*i+1] = (11 * grid[i]) % 256;
		pixArray[4*i+2] = (18 * grid[i]) % 256;
		pixArray[4*i + 3] = 255;
	}
}

