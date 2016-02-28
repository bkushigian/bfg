#include "winManager.hpp"

winManager::winManager(){
	displayMode = DSP_TEXT;		// Start with text screen
	WIDTH = 1000; HEIGHT = 1000; MAX_ITERS = 255;
	pixArray = new Uint8[HEIGHT * WIDTH * 4];
	winMain.create(VideoMode(WIDTH, HEIGHT), "Fractals");
	FM.setWM(this);
	commandMode = false;
	if (!font.loadFromFile("Fonts/FreeMono.otf"))
		throw std::runtime_error("Unable to load font FreeMono.otf");
	commandText.setFont(font);
	fontSize = 15;
	lineSpace = 3;
	commandText.setCharacterSize(fontSize);
	//commandText.setStyle(sf::Text::Bold);
	commandText.setColor(sf::Color::White);
}

winManager::~winManager(){
	if (pixArray != NULL) delete[] pixArray;
	FM.reset();
}

void winManager::mainLoop(){
	/* Clear/Display black */
    winMain.clear(Color::Black);
    winMain.display();

    // Setup Arr
	FM.getCurrent()->draw();

	/* image/texture for display */
	image.create(WIDTH, HEIGHT, pixArray);

	if (!texture.create(WIDTH,HEIGHT)) 
		throw std::runtime_error("winManager: Failed to create Texture");

	texture.update(image);
	sprite.setTexture(texture);
	int eventNum = 0;	// Handle returns from event call

    while (winMain.isOpen())
    {
		eventNum = 0;
        Event event;
        while(winMain.pollEvent(event)) {
			eventNum = handleEvent(event);	
			if (eventNum == 1){
				FM.reset();	
			}
			if (eventNum == 2){ // Next Fractal
				image.create(WIDTH, HEIGHT, pixArray);
				texture.update(image);
				sprite.setTexture(texture);
			}
			else if (eventNum == 3){ // Clear Black
				winMain.clear(sf::Color::Black);
				winMain.display();
			}
        }
		// Refresh Screen
        winMain.clear(sf::Color::Black);
		// Draw Sprite in case it was regenerated above
        winMain.draw(sprite);
		// Check for command Mode
		if (commandMode){
			unsigned int hSize = command.getHistorySize();
			for (int i = hSize-1; i >= 0; --i){
				commandText.setString(command.getHistory(i));
				positionText(commandText, hSize - i);
				winMain.draw(commandText);
			}
			commandText.setString(command.toString());
			positionText(commandText);
			winMain.draw(commandText);
		}
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
	// @ToDo To be split into seperate function
	// Command Mode
	
	if (commandMode){
		if (event.type == Event::TextEntered){
			if (event.text.unicode <= 128){
				char c = static_cast<char>(event.text.unicode);
				if (('!' <= c && c  <= '~') || c == ' '){	// Std char
					command.insert(static_cast<char>(event.text.unicode));
					return 0;
				}
			}
		}
		/*** Key Pressed ***/
		if(event.type == Event::KeyPressed){
			switch(event.key.code){
				case sf::Keyboard::Escape:
					commandMode = !commandMode;
					break;
				case sf::Keyboard::BackSpace:
					command.remove();
					break;
				case sf::Keyboard::Return: 
					command.execute();
					break;
				case sf::Keyboard::Up:
					command.up();
					break;
				case sf::Keyboard::Down:
					command.down();
					break;
				case sf::Keyboard::Left:
					command.left();
					break;
				case sf::Keyboard::Right:
					command.right();
					break;
			}
		}
		return 0;
	}
	
	/*** Normal Mode ***/
    switch (event.type)
    {
			
        /* Closed */
        case Event::Closed:
			winMain.close();
			FM.reset();
            return 1;
        /* Key Pressed */
        case Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				commandMode = !commandMode;
			}
			// Command Line
			// Quit
			if (event.key.code == sf::Keyboard::Q) {
				winMain.close();
				FM.reset();
				return 1;
			}
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
			if(event.key.code == sf::Keyboard::I){
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

    for (int i = 0; i < height*width; ++i){
		pix[4*i] = (15 * grid[i]) % 256;
		pix[4*i+1] = (11 * grid[i]) % 256;
		pix[4*i+2] = (18 * grid[i]) % 256;
		pix[4*i + 3] = 255;
    }
}

void winManager::setPixArray(Uint16* grid, int width, int height){
	for (int i = 0; i < height*width; ++i){
		pixArray[4*i] = (15 * grid[i]) % 256;
		pixArray[4*i+1] = (11 * grid[i]) % 256;
		pixArray[4*i+2] = (18 * grid[i]) % 256;
		pixArray[4*i + 3] = 255;
	}
}


// Command Line Stuff
void winManager::positionText(sf::Text& t){
	t.setPosition(2, HEIGHT - t.getCharacterSize() - lineSpace);
}

void winManager::positionText(sf::Text& t, int n){
	t.setPosition(15, HEIGHT - (n + 1)*(t.getCharacterSize() + lineSpace));
}
