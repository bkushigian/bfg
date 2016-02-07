#include "winManager.hpp"

void winManager::mainLoop(){

	std::cout << "Creating Window\n";
	/* Create Window */
    RenderWindow winMain(VideoMode(WIDTH, HEIGHT), "Fractals");

	/* Clear/Display black */
    winMain.clear(Color::Black);
    winMain.display();

	/* Populate Grid, Set up arr */
	std::cout << "Populating mandelbrot grid\n";
	FM.get(0)->populateGrid();
	FM.get(1)->populateGrid();
    // Setup Arr
	std::cout << "Declaring arr\n";
    Uint8 arr[WIDTH * HEIGHT * 4]; // Stores Pixels
	std::cout << "Updating arr\n";
	setPixArray(arr, FM.getCurrent()->getGrid(),  WIDTH, HEIGHT);
	
	/* image/texture for display */
    Image image;
    Texture texture;

	image.create(WIDTH, HEIGHT, arr);
	if (!texture.create(WIDTH,HEIGHT)) return -1;
	texture.update(image);
	Sprite sprite(texture);
	std::cout << "Entering Loop\n";
    while (winMain.isOpen())
    {
        Event event;
		int eventNum = 0;
        while(winMain.pollEvent(event))
        {
			eventNum = handleEvent(event);	
            if (eventNum == 1) winMain.close();
			else if (eventNum == 2){
				FM.next();
				setPixArray(arr, FM.getCurrent()->getGrid(), WIDTH, HEIGHT);
				image.create(WIDTH, HEIGHT, arr);
				texture.update(image);
				sprite.setTexture(texture);
			}
			
        }
        winMain.clear(Color::Black);
        winMain.draw(sprite);

        winMain.display();
    }
}

int winManager::handleEvent(Event event){
    switch (event.type)
    {
        /* Closed */
        case Event::Closed:
            return 1;
        /* Key Pressed */
        case Event::KeyPressed:
            //cout << "Key Pressed\n";
            return 2;
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

void winManager::setPixArray(Uint8* pix, int width, int height){
	Uint16* grid = FM.getCurrent()->getGrid(); for (int i = 0; i < height*width; ++i){
		pix[4*i] = (15 * grid[i]) % 256;
		pix[4*i+1] = (11 * grid[i]) % 256;
		pix[4*i+2] = (18 * grid[i]) % 256;
		pix[4*i + 3] = 255;
	}
}
