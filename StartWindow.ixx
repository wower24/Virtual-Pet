import <SFML/Graphics.hpp>;
import <iostream>;
import <string>;
import <fstream>;
import <vector>;
import<map>;

#include <thread>
#include <future>
#include <chrono>

using namespace std::chrono;

export module All_Modules:StartWindow;

export import :BT;
export import :GlobalGame;

export
{
    std::string header = "Virtual Pet (author: Marta Wower)";

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::VideoMode x(1350, 1250, desktop.bitsPerPixel);
    sf::RenderWindow gWindow(x, header);
    

    std::string tempUser = "";
    std::string tempDog = "";

    bool walk(sf::RenderWindow& window, sf::Sprite &dog, float destination, sf::Sprite &ball)
    {
        sf::VertexArray startSquare(sf::Quads, 4);
        startSquare[0].position = sf::Vector2f(0, 0);
        startSquare[1].position = sf::Vector2f(1350, 0);
        startSquare[2].position = sf::Vector2f(1350, 1250);
        startSquare[3].position = sf::Vector2f(0, 1250);

        startSquare[3].color = sf::Color(0, 128, 0);
        startSquare[2].color = sf::Color(0, 128, 0);
        startSquare[1].color = sf::Color(173, 216, 230);
        startSquare[0].color = sf::Color(173, 216, 230);


        float dogX = dog.getPosition().x;

        if (destination > dogX)
        {
            while (destination > dog.getPosition().x + 150)
            {
                //walk right
                //first stand right
                    std::this_thread::sleep_for(seconds(1));
                    dog.setTextureRect(sf::IntRect(0, 930, 300, 300));
                    
                    window.clear();
                    window.draw(startSquare);
                    window.draw(ball);
                    window.draw(dog);
                    window.display();
                //then walk right and move
                    std::this_thread::sleep_for(seconds(1));
                    dog.setTextureRect(sf::IntRect(620, 930, 300, 300));
                    
                    window.clear();
                    window.draw(startSquare);
                    window.draw(ball);
                    window.draw(dog);
                    window.display();
                    float dX = dog.getPosition().x;
                    float dY = dog.getPosition().y;
                    dog.setPosition({ dX + 30, dY });
            }
            
            return true;
        }
        else if (destination < dogX)
        {
            while (destination < dog.getPosition().x)
            {
                std::this_thread::sleep_for(seconds(1));
                dog.setTextureRect(sf::IntRect(930, 620, 300, 300));
                window.clear();
                window.draw(startSquare);
                window.draw(ball);
                window.draw(dog);
                window.display();
                std::this_thread::sleep_for(seconds(1));
                dog.setTextureRect(sf::IntRect(310, 930, 300, 300));
                window.clear();
                window.draw(startSquare);
                window.draw(ball);
                window.draw(dog);
                window.display();
                float dX = dog.getPosition().x;
                float dY = dog.getPosition().y;
                dog.setPosition({ dX - 30, dY });
            }

            return true;
        }
        else
            return true;
    }

    sf::Vector2f dragAndDrop(sf::RenderWindow &window, sf::Sprite &s)
    {
        sf::Vector2f initialPosition = s.getPosition();

        int mX = sf::Mouse::getPosition(window).x;
        int mY = sf::Mouse::getPosition(window).y;

        bool movingDone = true;
        int i = 0;

        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
               sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
               
               if (e.type == sf::Event::MouseButtonPressed)
               {
                   if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mousePosition.x > s.getPosition().x &&
                       mousePosition.y > s.getPosition().y && mousePosition.x < s.getPosition().x + s.getGlobalBounds().width &&
                       mousePosition.y < s.getPosition().y + s.getGlobalBounds().height)
                       movingDone = false;
               }
               else if (e.type == sf::Event::MouseButtonReleased)
               {
                   if (e.mouseButton.button == sf::Mouse::Left)
                   {
                       s.move({ mousePosition.x - 3*(s.getGlobalBounds().left)/2, mousePosition.y - 3*(s.getGlobalBounds().top)/2});
                       movingDone = true;
                   }
               }
               
               if (movingDone)
               {
                   if (i == 0)
                   {
                       s.setPosition(initialPosition);
                       i++;
                   }
                   
                   window.draw(s);    
               }
               
               window.display();

               if (e.type == sf::Event::KeyPressed)
               {
                   if (e.key.code == sf::Keyboard::Enter)
                       return s.getPosition();
               }
               
            }
        }

        
    }

    void shop(sf::RenderWindow &window)
    {
        sf::VertexArray startSquare(sf::Quads, 4);
        startSquare[0].position = sf::Vector2f(0, 0);
        startSquare[1].position = sf::Vector2f(1350, 0);
        startSquare[2].position = sf::Vector2f(1350, 1250);
        startSquare[3].position = sf::Vector2f(0, 1250);

        startSquare[3].color = sf::Color(0, 128, 0);
        startSquare[2].color = sf::Color(0, 128, 0);
        startSquare[1].color = sf::Color(173, 216, 230);
        startSquare[0].color = sf::Color(173, 216, 230);

        sf::RectangleShape sRec;
        sRec.setSize({ 1000, 800 });
        sRec.setFillColor(sf::Color(244, 194, 194));
        sRec.setOutlineThickness(15);
        sRec.setOutlineColor(sf::Color(200, 112, 126));
        sRec.setPosition(170, 230);

        sf::Font sFont;
        sFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/CollegiateBlackFLF.ttf");
        sf::Text sText;
        sText.setString("SHOP:");
        sText.setFont(sFont);
        sText.setCharacterSize(70);
        sText.setFillColor(sf::Color(200, 112, 126));
        sText.setPosition({ 550, 130 });

        sf::Texture sT;
        sT.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/dogsheet.png");
        sf::Sprite cookie(sT, sf::IntRect{310, 310, 300, 300});
        cookie.setPosition({ 185, 245 });

        Button sCookie("", { 200, 200 }, 1, sf::Color::Transparent, sf::Color::Transparent);
        sCookie.setPosition({ 235, 295 });
        sCookie.button.setOutlineThickness(10);
        sCookie.button.setOutlineColor(sf::Color(200, 112, 126));

        sf::CircleShape coinG(10, 30);
        coinG.setFillColor(sf::Color::Yellow);
        coinG.setOutlineThickness(4);
        coinG.setOutlineColor(sf::Color(118, 57, 49));
        coinG.setPosition({ 1050, 265 });

        sf::CircleShape coinG2(10, 30);
        coinG2.setFillColor(sf::Color::Yellow);
        coinG2.setOutlineThickness(4);
        coinG2.setOutlineColor(sf::Color(118, 57, 49));
        coinG2.setPosition({ 310, 530 });

        sf::Text coinsLeft;
        coinsLeft.setCharacterSize(40);
        coinsLeft.setFont(sFont);
        coinsLeft.setFillColor(sf::Color(118, 57, 49));
        coinsLeft.setPosition({ 1080, 250 });

        sf::Text priceT;
        priceT.setCharacterSize(40);
        priceT.setFont(sFont);
        priceT.setString("1");
        priceT.setFillColor(sf::Color(118, 57, 49));
        priceT.setPosition({ 350, 515 });

        sf::RectangleShape priceR({ 100, 50 });
        priceR.setFillColor(sf::Color(200, 112, 126));
        priceR.setPosition({285, 515});

        bool getOut = false;

        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (sCookie.isMouseOver(window))
                {
                    sCookie.button.setFillColor(sf::Color(200, 112, 126));

                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        if (e.mouseButton.button == sf::Mouse::Left)
                        {
                            if (g.p.getValue(0) > 0)
                            {
                                g.p.buyFood();
                            }
                            else
                            {
                                std::cout << "NO MONEY FOR FOOD. COMPETE TO GET MONEY." << std::endl;
                            }
                        }
                    }
                }
                else
                    sCookie.button.setFillColor(sf::Color::Transparent);

                if (e.type == sf::Event::Closed)
                {
                    std::cout << "UPLOADING DATA..." << std::endl;
                    g.uploadData(g.d.getName());
                    window.close();
                }
                
                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::Escape)
                    {
                        getOut = true;
                        break;
                    }
                }
            }

            if (getOut)
                break;

            int cTemp = g.p.getValue(0);
            coinsLeft.setString(std::to_string(cTemp));

            window.clear();

            window.draw(startSquare);
            window.draw(sRec);
            window.draw(sText);
            window.draw(coinG);
            window.draw(coinsLeft);
            sCookie.drawTo(window);
            window.draw(cookie);
            window.draw(priceR);
            window.draw(coinG2);
            window.draw(priceT);

            window.display();
        }


    }

    void startGame(sf::RenderWindow &window)
    {
        sf::Texture backgroundT, needT, dogT;
        sf::Sprite backgroundS;
        sf::Sprite needBars[3];
        int needFramesX[11] = {130, 340, 10, 220, 430, 10, 220, 430, 550, 640, 640};
        int needFramesY[11] = {10, 10, 220, 220, 220, 430, 430, 430, 10, 220, 430};

        // [0][x] right side sit, stand, walk, bJump, jJump, lJump, aJump
        // [1][x] left side
        sf::Vector2i dogXY[2][7] = { { {930, 310}, {0, 930}, {620, 930}, {0, 310}, {0, 620}, {620, 620}, {310, 0} }, 
                                     { {930, 0}, {930, 620}, {310, 930}, {620, 0}, {620, 310}, {310, 620}, {0, 0} } };
        sf::Text texts[7]; //podpisy do increase bars
        sf::Text nameOfDog, foodLeft;
        std::string bWords[12] = { "FEED", "PLAY", "SLEEP", "TRAIN", "COMPETE", "SHOP", "ADD", g.d.getName() + ": " + std::to_string(g.d.getAge()) + " months", "FOOD", 
            "S: " + std::to_string(g.d.getPoints(3)), "J: " + std::to_string(g.d.getPoints(4)), "O: " + std::to_string(g.d.getPoints(5)) };
        Button buttons[9];
        sf::Color bColors[6] = { sf::Color(200, 112, 126), sf::Color(226, 143, 173), sf::Color(239, 180, 193), sf::Color(228, 142, 88), sf::Color(237, 170, 125), sf::Color(172, 153, 193) };

        sf::Font bFont;
        bFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/CollegiateBlackFLF.ttf");

        if (!needT.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/spritesheet.png"))
            std::cout << "ERROR! Need Bar texture not loaded." << std::endl;

        if (!dogT.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/dogsheet.png"))
            std::cout << "ERROR! Dog texture not loaded." << std::endl;
        //need bars sprites

        sf::Sprite dogS(dogT);
        dogS.setTextureRect(sf::IntRect(0, 930, 300, 300));
        dogS.setPosition({ 600, 500 });

        sf::Sprite feedCookie(dogT);
        feedCookie.setTextureRect(sf::IntRect(385, 385, 150, 150));
        feedCookie.setPosition({ 200, 5 });

        sf::Texture ballT;
        ballT.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/ballsprite.png");
        sf::Sprite playBall;
        playBall.setTexture(ballT);
        
        playBall.setPosition({ 250, 160 });

        //initial pose - right stand [0][1]
        int pd = 0; //previous direction
        int pp = 1; //previous pose

        for (int i = 0; i < 3; i++)
        {
            sf::Sprite temp(needT);
            needBars[i] = temp;
            float x = 205 + 370 * i;
            needBars[i].setPosition({x , 975});
        }

        //all non-functional texts
        for (int i = 0; i < 7; i++)
        {
            sf::Text temp;
            temp = texts[i];
            //FOOD, PLAY, SLEEP
            if (i < 3)
            {
                if (i == 0)
                    texts[i].setString(bWords[8]);
                else
                    texts[i].setString(bWords[i]);

                texts[i].setFont(bFont);
                texts[i].setCharacterSize(30);
                texts[i].setFillColor(sf::Color(60, 60, 60));
                float y = 250 + 370 * i;

                texts[i].setPosition({ y, 1190 });
            }
            //NAME AND AGE
            else if (i == 3)
            {
                //name and age
                texts[i].setString(bWords[7]);
                texts[i].setCharacterSize(70);
                texts[i].setFont(bFont);
                texts[i].setFillColor(sf::Color(60, 60, 60));
                texts[i].setPosition({ 600, 40 });
            }
            //SPEED, JUMP, OBEDIENCE
            else
            {
                texts[i].setString(bWords[i + 5]);
                texts[i].setCharacterSize(40);
                texts[i].setFont(bFont);
                texts[i].setFillColor(sf::Color(60, 60, 60));
                float y = 50 * (i - 7) + 365;
                texts[i].setPosition({ 1130, y });
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (i < 6)
            {
                Button temp(bWords[i], { 280, 100 }, 50, bColors[i], sf::Color::White);
                buttons[i] = temp;
                buttons[i].setFont(bFont);
                float y = (100 * i) + 50;

                if (i > 2)
                    y += 50;

                if (i == 5)
                    y += 50;


                buttons[i].setPosition({ 0, y });
            }
            else
            {
               Button temp(bWords[6], { 30, 30 }, 30, sf::Color::Transparent, sf::Color::Black);
               buttons[i] = temp;
               buttons[i].setFont(bFont);
               float y = 50 * (i - 3) + 70;
               buttons[i].setPosition({ 1250, y });
            }
        }
        

        if (!backgroundT.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/background.png"))
            std::cout << "ERROR! Background picture not loaded." << std::endl;
        else
        {
            backgroundS.setTexture(backgroundT);
        }

        foodLeft.setCharacterSize(40);
        foodLeft.setFont(bFont);
        foodLeft.setFillColor(sf::Color::Black);
        foodLeft.setPosition({ 10, 5 });

        sf::Text apLeft;
        apLeft.setCharacterSize(40);
        apLeft.setFont(bFont);
        apLeft.setPosition({ 1100, 170 });
        apLeft.setFillColor(sf::Color::Black);


        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::KeyPressed)
                {
                    switch (e.key.code)
                    {
                    case sf::Keyboard::Down:
                        {
                        std::cout << "PRESSED: DOWN" << std::endl;
                        //down - sit
                        if (pd == 0)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[0][0].x, dogXY[0][0].y, 300, 300));
                            pd = 0;
                            pp = 0;
                        }
                        else
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[1][0].x, dogXY[1][0].y, 300, 300));
                            pd = 1;
                            pp = 0;
                        }
                        break;
                        }
                    case sf::Keyboard::Up:
                    {
                        std::cout << "PRESSED: UP" << std::endl;
                        if (pd == 0)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[0][1].x, dogXY[0][1].y, 300, 300));
                            pd = 0;
                            pp = 1;
                        }
                        else
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[1][1].x, dogXY[1][1].y, 300, 300));
                            pd = 1;
                            pp = 1;
                        }
                        break;
                    }
                    case sf::Keyboard::Left:
                    {
                        std::cout << "PRESSED: LEFT" << std::endl;
                        if (pd == 0)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[1][pp].x, dogXY[1][pp].y, 300, 300));
                            pd = 1;
                        }
                        else if (pd == 1 && pp == 1)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[1][2].x, dogXY[1][2].y, 300, 300));
                            pd = 1;
                            pp = 2;
                        }
                        else if (pd == 1 && pp == 2)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[1][1].x, dogXY[1][1].y, 300, 300));
                            float dX = dogS.getPosition().x;
                            float dY = dogS.getPosition().y;
                            if(dX > 270 && dX < 1100)
                                dogS.setPosition({ dX - 30, dY });
                            pd = 1;
                            pp = 1;
                        }
                        break;
                    }
                    case sf::Keyboard::Right:
                    {
                        std::cout << "PRESSED: RIGHT" << std::endl;
                        if (pd == 1)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[0][pp].x, dogXY[0][pp].y, 300, 300));
                            pd = 0;
                        }
                        else if (pd == 0 && pp == 1)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[0][2].x, dogXY[0][2].y, 300, 300));
                            pd = 0;
                            pp = 2;
                        }
                        else if (pd == 0 && pp == 2)
                        {
                            dogS.setTextureRect(sf::IntRect(dogXY[0][1].x, dogXY[0][1].y, 300, 300));
                            float dX = dogS.getPosition().x;
                            float dY = dogS.getPosition().y;
                            if(dX > 200 && dX < 1050)
                                dogS.setPosition({ dX + 30, dY });
                            pd = 0;
                            pp = 1;
                        }
                        break;
                    }
                    }
                }

                if (e.type == sf::Event::Closed)
                {
                    std::cout << "UPLOADING DATA..." << std::endl;
                    g.uploadData(g.d.getName());
                    window.close();
                }
                
                for (int i = 0; i < 9; i++)
                {
                    if (buttons[i].isMouseOver(window))
                    {
                        if (i == 0)
                        {
                            foodLeft.setString("Food left: " + std::to_string(g.p.getValue(1)));

                        }

                        if (i < 3)
                            buttons[i].setTextColor(sf::Color(173, 216, 230));
                        else if (i < 5)
                            buttons[i].setTextColor(sf::Color(153, 198, 142));
                        else
                            buttons[i].setTextColor(sf::Color(255, 211, 0));

                         if (e.type == sf::Event::MouseButtonPressed)
                         {
                             if (e.mouseButton.button == sf::Mouse::Left)
                             {
                                 switch (i)
                                 {
                                 case 0:
                                 {
                                     std::cout << "MOVE COOKIE TO A DOG AND PRESS ENTER" << std::endl;
                                     dragAndDrop(window, feedCookie);
                                     sf::Vector2f result = feedCookie.getPosition();
                                     if (result.x > dogS.getPosition().x &&
                                         result.y > dogS.getPosition().y &&
                                         result.x < dogS.getPosition().x + 300 &&
                                         result.y < dogS.getPosition().y + 300)
                                     {
                                         g.p.feed(g.d);
                                         std::cout << "FEED DOG" << std::endl;
                                     }

                                     feedCookie.setPosition({ 200, 5 });
                                     break;
                                 }
                                 case 1:
                                 {
                                     std::cout << "MOVE THE BALL TO ANY PLACE IN THE WINDOW AND PRESS ENTER" << std::endl;
                                     dragAndDrop(window, playBall);
                                     sf::Vector2f result = playBall.getPosition();
                                     playBall.setPosition({ playBall.getPosition().x, dogS.getPosition().y + 200 });
                                     if (walk(window, dogS, playBall.getPosition().x, playBall))
                                     {
                                         std::cout << "PLAY WITH DOG" << std::endl;
                                         g.p.play(g.d);
                                     }
                                     playBall.setPosition({250, 160});
                                     break;
                                 }
                                 case 2:
                                 {
                                     std::cout << "DOG ASLEEP" << std::endl;
                                     g.p.putToSleep(g.d);
                                     break;
                                 }
                                 case 3:
                                 {
                                     g.p.train(g.d);
                                     std::cout << "DOG TRAINED" << std::endl;
                                     break;
                                 }
                                 case 4:
                                 {
                                     g.p.comp(g.d);
                                     std::cout << "COMPETITION" << std::endl;
                                     break;
                                 }
                                 case 5:
                                 {
                                     std::cout << "LOADING SHOP..." << std::endl;
                                     shop(window);
                                     break;
                                 }
                                 case 6:
                                 {
                                     g.p.assignPoints(g.d, 0);
                                     break;
                                 }
                                 case 7:
                                 {
                                     g.p.assignPoints(g.d, 1);
                                     break;
                                 }
                                 case 8:
                                 {
                                     g.p.assignPoints(g.d, 2);
                                     break;
                                 }
                                 }
                             }
                         }
                    }
                    else
                    {
                        
                        if(i < 6)
                            buttons[i].setTextColor(sf::Color::White);
                        else
                            buttons[i].setTextColor(sf::Color::Black);
                            
                    }
                    
                }
            }

            //IT'S NOT IN A LOOP BECAUSE LOOP IS NOT WORKING
            needBars[0].setTextureRect(sf::IntRect(needFramesX[g.d.getPoints(0)], needFramesY[g.d.getPoints(0)], 200, 200));
            needBars[1].setTextureRect(sf::IntRect(needFramesX[g.d.getPoints(1)], needFramesY[g.d.getPoints(1)], 200, 200));
            needBars[2].setTextureRect(sf::IntRect(needFramesX[g.d.getPoints(2)], needFramesY[g.d.getPoints(2)], 200, 200));

            foodLeft.setString("Food left: " + std::to_string(g.p.getValue(1)));
            apLeft.setString("AP: " + std::to_string(g.p.getValue(2)));
            texts[4].setString("S: " + std::to_string(g.d.getPoints(3)));
            texts[5].setString("J: " + std::to_string(g.d.getPoints(4)));
            texts[6].setString("O: " + std::to_string(g.d.getPoints(5)));

            window.clear();
            window.draw(backgroundS);

            for (int i = 0; i < 3; i++)
            {
                //needBars[i].setTextureRect(sf::IntRect(needFramesX[g.d.getPoints(i)], needFramesY[g.d.getPoints(i)], 200, 200));
                window.draw(needBars[i]);
            }

            for (int i = 0; i < 7; i++)
                window.draw(texts[i]);

            for (int i = 0; i < 9; i++)
                buttons[i].drawTo(window);
            
            window.draw(foodLeft);
            window.draw(apLeft);
            window.draw(dogS);
            window.draw(playBall);
            
            window.display();

        }
    }

    void resumeGame(sf::RenderWindow &window)
    {
        g.loadMap();
        
        sf::VertexArray startSquare(sf::Quads, 4);
        startSquare[0].position = sf::Vector2f(0, 0);
        startSquare[1].position = sf::Vector2f(1350, 0);
        startSquare[2].position = sf::Vector2f(1350, 1250);
        startSquare[3].position = sf::Vector2f(0, 1250);

        startSquare[3].color = sf::Color(0, 128, 0);
        startSquare[2].color = sf::Color(0, 128, 0);
        startSquare[1].color = sf::Color(173, 216, 230);
        startSquare[0].color = sf::Color(173, 216, 230);
        
        //CREATE MENU
        std::fstream f;
        std::vector<std::string> sOptions;
        std::vector<std::string> dogNames;

        for (auto& x : dogMap)
        {
            std::string temp = x.first; //dogname
            dogNames.push_back(temp);
            std::string temp2; //username

            f.open(x.second);
            getline(f, temp2);
            f.close();

            temp = temp2 + "(" + temp + ")";

            std::cout << temp << std::endl;
            sOptions.push_back(temp);
        }
        int vSize = sOptions.size();
        Button bOptions[5];
        sf::Font fo;
        fo.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/Athletic Outfit.ttf");

        sf::Text choose;
        choose.setString("CHOOSE YOUR  GAME:");
        choose.setCharacterSize(80);
        choose.setFont(fo);
        choose.setFillColor(sf::Color::White);
        choose.setPosition(200, 100);

        for (int i = 0; i < vSize; i++)
        {
            Button temp(sOptions[i], { 500, 100 }, 100, sf::Color::Transparent, sf::Color::White);
            bOptions[i] = temp;
            bOptions[i].setFont(fo);
            float y = 300 + 150 * i;
            bOptions[i].setPosition({ 450, y });
        }

        std::cout << window.getSize().x << std::endl;

        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    window.close();
                }

                for (int i = 0; i < vSize; i++)
                {
                    if (bOptions[i].isMouseOver(window))
                    {
                        bOptions[i].setTextColor(sf::Color(150, 0, 205));

                        if (e.type == sf::Event::MouseButtonPressed)
                        {
                            if (e.mouseButton.button == sf::Mouse::Left)
                            {
                                g.resume(dogNames[i]);
                                startGame(window);
                                //shop(window);
                            }
                        }
                    }
                    else
                        bOptions[i].setTextColor(sf::Color::White);
                }
            }

            window.clear();

            window.draw(startSquare);
            window.draw(choose);

            for (int i = 0; i < vSize; i++)
                bOptions[i].drawTo(window);

            window.display();
        }
    }

    void names(sf::RenderWindow &window)
    {
        
        sf::VertexArray startSquare(sf::Quads, 4);
        startSquare[0].position = sf::Vector2f(0, 0);
        startSquare[1].position = sf::Vector2f(1350, 0);
        startSquare[2].position = sf::Vector2f(1350, 1250);
        startSquare[3].position = sf::Vector2f(0, 1250);

        startSquare[3].color = sf::Color(0, 128, 0);
        startSquare[2].color = sf::Color(0, 128, 0);
        startSquare[1].color = sf::Color(173, 216, 230);
        startSquare[0].color = sf::Color(173, 216, 230);
        
        sf::Text uText, dText;
        sf::Font udFont, bFont;
        std::string doneString = "DONE";
        Button bDone(doneString, { 300, 120 }, 70, sf::Color(92, 116, 229), sf::Color::White);
        
        uText.setCharacterSize(70);
        uText.setFillColor(sf::Color(216, 128, 229));
        uText.setString("USERNAME:");

        dText.setCharacterSize(70);
        dText.setFillColor(sf::Color(216, 222, 128));
        dText.setString("DOG NAME:");

        if(!udFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/Athletic Outfit.ttf"))
            std::cout<<"ERROR! Font file for udText not loaded." <<std::endl;
        else
        {
            uText.setFont(udFont);
            dText.setFont(udFont);
        }

        if (!bFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/CollegiateBlackFLF.ttf"))
            std::cout << "ERROR! Fonr file for bDone not loaded." << std::endl;
        else
            bDone.setFont(bFont);

       
        Textbox user(15, 216, 128, 229);
        Textbox dog(7, 216, 222, 128);

        user.setPosition(350, 1250/3);
        dog.setPosition(350, 733);
        uText.setPosition(350, 316);
        dText.setPosition(350, 633);
        bDone.setPosition({ 550, 1000 });

        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    window.close();
                else if (e.type == sf::Event::MouseButtonPressed)
                {
                    auto pos = sf::Mouse::getPosition(window);
                    user.setSelected(false);
                    dog.setSelected(false);

                    if (user.isInside(sf::Vector2f(pos)))
                    {
                        user.setSelected(true);
                    }
                    else
                        user.setSelected(false);

                    if (dog.isInside(sf::Vector2f(pos)))
                    {
                        dog.setSelected(true);
                    }
                    else
                        dog.setSelected(false);
                }
                else
                {
                    if (user.isSelected == true)
                    {
                        std::cout << "USER SELECTED" << std::endl;
                        user.inputLogic(e, tempUser);
                    }

                    if (dog.isSelected == true)
                    {
                        std::cout << "DOG SELECTED" << std::endl;
                        dog.inputLogic(e, tempDog);
                    }
                }

                if (bDone.isMouseOver(window))
                {
                    bDone.setTextColor(sf::Color(127, 127, 127));
                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        if (e.mouseButton.button == sf::Mouse::Left)
                        {
                            g.newGame(tempUser, tempDog);
                            startGame(window);
                        }
                    }
                }
                else
                    bDone.setTextColor(sf::Color::White);
            }
            window.clear();
            window.draw(startSquare);
            window.draw(uText);
            window.draw(user);
            window.draw(dText);
            window.draw(dog);
            bDone.drawTo(window);
            window.display();
        }    
    }

    void start()
    {
        sf::Font titleFont, buttonFont;
        sf::Text titleText, signatureText;
        std::string ngString = "NEW GAME";
        std::string rString = "RESUME";
        Button ngButton(ngString, { 430, 70 }, 70, sf::Color::Transparent, sf::Color::White);
        Button resumeButton(rString, { 330, 70 }, 70, sf::Color::Transparent, sf::Color::White);

        //setting up the backgorund
        /*
            0 1
            2 3
        */
        
        sf::VertexArray startSquare(sf::Quads, 4);
        startSquare[0].position = sf::Vector2f(0, 0);
        startSquare[1].position = sf::Vector2f(1350, 0);
        startSquare[2].position = sf::Vector2f(1350, 1250);
        startSquare[3].position = sf::Vector2f(0, 1250);

        startSquare[3].color = sf::Color(0, 128, 0);
        startSquare[2].color = sf::Color(0, 128, 0);
        startSquare[1].color = sf::Color(173, 216, 230);
        startSquare[0].color = sf::Color(173, 216, 230);
        
        //setting up title & signature text
        if (!titleFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/Athletic Outfit.ttf"))
        {
            std::cout << "ERROR!!!" << std::endl;
        }
        else
        {
            // select the font
            titleText.setFont(titleFont); // font is a sf::Font
            signatureText.setFont(titleFont);

            // set the string to display
            titleText.setString("My Virtual Pet");
            signatureText.setString("Marta Wower");

            // set the character size
            titleText.setCharacterSize(120); // in pixels, not points!
            signatureText.setCharacterSize(50);

            // set the color
            titleText.setFillColor(sf::Color::White);
            signatureText.setFillColor(sf::Color::White);

            //set position
            titleText.setPosition({ 315, 250 });
            signatureText.setPosition({ 1050, 1150 });
        }

        //setting up ngButton & resumeButton
        
        if (!buttonFont.loadFromFile("C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release/CollegiateBlackFLF.ttf"))
        {
            std::cout << "ERROR!!!" << std::endl;
        }
        else
        {
            ngButton.setFont(buttonFont);
            resumeButton.setFont(buttonFont);

            ngButton.setPosition({ 180, 720 });
            resumeButton.setPosition({ 880, 720 });
        }
        

        //window actions
        while (gWindow.isOpen())
        {
            sf::Event event;

            while (gWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    gWindow.close();

                if (event.type == sf::Event::KeyPressed)
                {

                    if (event.key.code == sf::Keyboard::Escape)
                        gWindow.close();
                }
                
                if (ngButton.isMouseOver(gWindow))
                {
                    ngButton.setTextColor(sf::Color(216, 128, 229));
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            g.loadMap();
                            if (g.userCounter < 5)
                                names(gWindow);
                            else
                                std::cout << "ERROR: There's no space for another  player." << std::endl;
                        }
                    }
                }
                else
                    ngButton.setTextColor(sf::Color::White);

                if (resumeButton.isMouseOver(gWindow))
                {
                    resumeButton.setTextColor(sf::Color(216, 222, 128));
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            resumeGame(gWindow);
                        }
                    }
                }
                else
                    resumeButton.setTextColor(sf::Color::White);
        }

            

            gWindow.clear();

            gWindow.draw(startSquare);
            gWindow.draw(titleText);
            gWindow.draw(signatureText);
            ngButton.drawTo(gWindow);
            resumeButton.drawTo(gWindow);

            gWindow.display();
        }
    }
    
}
