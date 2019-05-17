#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <cmath>
#include <string>
#include<sstream>
#include<fstream>
using namespace sf;
using namespace std;

    // HÀM XỬ LÝ VA CHẠM
bool collision1(double x, double y, double x1, double y1)
{
    if (abs(x - x1) <= 40 && abs(y - y1) <= 40)
    {
        return true ;

    }
    else
        return false;

}

    // RAMDOM VỊ TRÍ CHƯỚNG NGẠI VẬT BÊN ĐỎ
double spawnTrap1()
{
    int n=rand()%2;
    if (n==0)
        return 30;
    else if (n==1)
        return 130;
}
    //RANDOM VỊ TRÍ CHƯỚNG NGẠI VẬT BÊN XANH
double spawnTrap2()
{
    int n=rand()%2;
    if (n==0)
        return 230;
    else  if (n==1)
        return 330;
}
    //RANDOM VỊ TRÍ ITEM
double spawnItem ()
{
    int n=rand () %4;
    if (n==0)
        return 30;
    if (n==1)
        return 130;
    if (n==2)
        return 230;
    if (n==3)
        return 330;
}

    //KEYBOARD
void keyboard(sf::Sprite& red, sf::Sprite& blue)
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        blue.setPosition(330, 570);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        blue.setPosition(230, 570);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        red.setPosition(30, 570);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        red.setPosition(130, 570);

}
int main ()
{
    // KHAI BÁO
    sf::RenderWindow window(sf::VideoMode(420, 700), "GAME 2CARS");
    window.setFramerateLimit(60);
    sf::Texture _road,_red, _blue,  _gameover, _increase, _fall,_menu ;
    sf::Texture red_eat, red_dodge,blue_eat, blue_dodge;
    sf::Font font, font_gameover;
    sf::Text Score, highScore;
    sf::SoundBuffer gamesoundbuffer, game_over ;
    int trapNumber = 0,score=0,frame=3000;
    double speed=5;
    bool addedSpeed = 0;
    bool die=false , test =false ;
    bool start=false;
    vector<double>posX ;
    vector<double>posY;
    vector<int>eatordodge;

        //ÂM THANH
    gamesoundbuffer.loadFromFile("sound/game.wav");
    game_over.loadFromFile("sound/crash.wav");
    Sound Gamesound, Gameoversound;
        Gamesound.setBuffer(gamesoundbuffer);
        Gameoversound.setBuffer(game_over);
        //ĐỌC ĐIỂM CAO NHẤT
    fstream Highscore;
    Highscore.open("highscore.txt");
    int highscore;
    Highscore>>highscore;


        // load file ảnh
        _road.loadFromFile("image/street.png");
        _red.loadFromFile("image/red.png");
        _blue.loadFromFile("image/blue.png");
        _gameover.loadFromFile("image/gameover.png");
        _increase.loadFromFile("image/increase.png");
        _fall.loadFromFile("image/fall.png");
        _menu.loadFromFile("image/gamemenu.png");
         red_eat.loadFromFile("image/red_eat.png");
         red_dodge.loadFromFile("image/red_dodge.png");
         blue_eat.loadFromFile("image/blue_eat.png");
         blue_dodge.loadFromFile("image/blue_dodge.png");


    // set sprite ;
    sf::Sprite road(_road), red_car(_red),blue_car (_blue);
    sf::Sprite gameover(_gameover), increase ( _increase), fall ( _fall );
    sf::Sprite trap,  menu(_menu);

    font.loadFromFile("mine.ttf");
    font_gameover.loadFromFile("mistral.ttf");
    Score.setFont(font);
    highScore.setFont(font);
    std::stringstream  _score;
    std::stringstream  _highScore;

    red_car.setPosition(30, 570);
    blue_car.setPosition(230, 570);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        if (die)
        {

            Gamesound.stop();
            sf::Text Score_gameover , highscore_gameover;

            Score_gameover.setFont(font_gameover);
            stringstream _Score_gameover;
            _Score_gameover.str("");
            _Score_gameover<<score;
            Score_gameover.setString(_score.str());
            Score_gameover.setCharacterSize(60);
            Score_gameover.setPosition(185  , 560);
            Score_gameover.setFillColor(sf::Color(255   ,255, 255,255));
            Score_gameover.setOutlineColor(sf::Color(40, 40 , 40 ,255));
            Score_gameover.setOutlineThickness(7);


            highscore_gameover.setFont(font_gameover);
            if (highscore >= score  )
            {
                stringstream _highScore_gameover;
                _highScore_gameover.str("");
                _highScore_gameover<<highscore;
                highscore_gameover.setString(_highScore_gameover.str());
                highscore_gameover.setPosition(185  , 410);
                highscore_gameover.setFillColor(sf::Color(255   ,255, 255,255));
                highscore_gameover.setOutlineColor(sf::Color(40, 40 , 40 ,255));
            }
            else if  (highscore < score   )
            {
                stringstream _highScore_gameover;
                _highScore_gameover.str("");
                _highScore_gameover<<"NEW HIGHSCORE";
                highscore_gameover.setFillColor(sf::Color(255   ,255, 255,255));
                highscore_gameover.setOutlineColor(sf::Color(255, 0 , 0 ,255));
                highscore_gameover.setString(_highScore_gameover.str());
                highscore_gameover.setPosition(30  , 410);
            }
                highscore_gameover.setCharacterSize(60);
                highscore_gameover.setOutlineThickness(7);


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && die==true)
            {
                if (highscore  < score )
                {
                    highscore=score;
                    ofstream highScoreOut;
                    highScoreOut.open("highscore.txt");
                    highScoreOut << highscore;
                    highScoreOut.close();
                }
                Gamesound.play();
                die=0;
                score = 0;
                trapNumber=0;
                speed=5;
                eatordodge.clear();
                posX.clear();
                posY.clear();
            }

            window.draw(gameover);
            window.draw(Score_gameover);
            window.draw(highscore_gameover);
            window.display();
            //continue;




        }

            //MENU
        if (start==false)
        {
            int x_mouse = Mouse::getPosition(window).x;
            int y_mouse = Mouse::getPosition(window).y;
            window.draw(menu);
            window.display();

                //CLICK TO START
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x_mouse>110 &&x_mouse<310 &&y_mouse>470 &&y_mouse<570)
            {
                start=true;
                Gamesound.play();
                Gamesound.setLoop(true);
            }
        }

        if (start==true &&  die ==false)
        {
            window.clear(sf::Color(150,10,140));
            _score.str("");
            _score<<score;
            Score.setString(_score.str());
            //Score.setColor(sf::Color::Red);
            Score.setCharacterSize(40);
            Score.setPosition(30, 10);
            Score.setFillColor(sf::Color(255   ,255, 255,255));
            Score.setOutlineColor(sf::Color(40, 40 , 40 ,255));
            Score.setOutlineThickness(1);

            window.draw(road);
            window.draw(Score);
            window.draw(highScore);
            window.draw(red_car);
            window.draw(blue_car);



            // create trap
            if (trapNumber == 0 || posY[trapNumber-2] >= 120)
            {

                // random create trap1
                int randomtrap1=rand() %30;


                if (randomtrap1<14)
                {
                    // create trap= eat;
                    eatordodge.push_back(1);
                    posX.push_back(spawnTrap1());
                    posY.push_back(-200);
                    trapNumber++;
                }
                if (randomtrap1>15)
                {
                    //create trap =dodge
                    eatordodge.push_back(0);
                    posX.push_back(spawnTrap1());
                    posY.push_back(-200);
                    trapNumber++;
                }
                if (randomtrap1==14 )
                {
                    //create trap =increase
                    eatordodge.push_back(randomtrap1);
                    posX.push_back(spawnTrap1());
                    posY.push_back(-200);
                    trapNumber++;
                }
                if (randomtrap1==15)
                {
                    // create trap = fall
                    eatordodge.push_back(randomtrap1);
                    posX.push_back(spawnTrap1());
                    posY.push_back(-200);
                    trapNumber++;
                }

                // random create trap 2
                int randomtrap2=rand() %30;

                // the same
                if (randomtrap2<14)
                {
                    eatordodge.push_back(2);
                    posX.push_back(spawnTrap2());
                    posY.push_back(-150);
                    trapNumber++;
                }
                if (randomtrap2>15)
                {
                    eatordodge.push_back(3);
                    posX.push_back(spawnTrap2());
                    posY.push_back(-150);
                    trapNumber++;
                }
                if (randomtrap2==14 )
                {
                    eatordodge.push_back(randomtrap2);
                    posX.push_back(spawnTrap2());
                    posY.push_back(-150);
                    trapNumber++;
                }
                if (randomtrap2==15)
                {
                    eatordodge.push_back(randomtrap2);
                    posX.push_back(spawnTrap2());
                    posY.push_back(-150);
                    trapNumber++;
                }

            }
            if ( score % 4 == 0 && !addedSpeed && frame >1000)
            {
                speed +=0.5;
                addedSpeed = 1;
            }

            // collision handling
            for (int i=0; i<trapNumber  ; i++)
            {
                double x_red=red_car.getPosition().x;
                double y_red=red_car.getPosition().y;
                double x_blue=blue_car.getPosition().x;
                double y_blue=blue_car.getPosition().y;

                if (collision1( x_red, y_red, posX[i], posY[i])==true)
                {
                    if (eatordodge[i]==0)
                    {
                        Gameoversound.play();
                        die=true;
                    }
                    else if (eatordodge[i]==1)
                    {
                        posY[i]=-100;
                        eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                        posX.erase(posX.begin()+i,posX.begin()+i+1);
                        posY.erase(posY.begin()+i,posY.begin()+i+1);
                        trapNumber--;
                        score++;
                        addedSpeed = 0;
                    }
                }
                if (collision1( x_blue, y_blue, posX[i], posY[i])==true)
                {
                    if (eatordodge[i]==2)
                    {
                        Gameoversound.play();
                        die=true;
                    }
                    if (eatordodge[i]==3)
                    {
                        eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                        posX.erase(posX.begin()+i,posX.begin()+i+1);
                        posY.erase(posY.begin()+i,posY.begin()+i+1);
                        i--;
                        trapNumber--;
                        score++;
                        addedSpeed = 0;
                    }
                }
                if (collision1( x_blue, y_blue, posX[i], posY[i])==true && eatordodge[i]==14 )
                {
                    speed+=0.05;
                    eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                    posX.erase(posX.begin()+i,posX.begin()+i+1);
                    posY.erase(posY.begin()+i,posY.begin()+i+1);
                    i--;
                    trapNumber--;
                }
                if (collision1( x_blue, y_blue, posX[i], posY[i])==true && eatordodge[i]==15 )
                {
                    speed-=0.05;
                    eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                    posX.erase(posX.begin()+i,posX.begin()+i+1);
                    posY.erase(posY.begin()+i,posY.begin()+i+1);
                    i--;
                    trapNumber--;

                }
                if (collision1( x_red, y_red, posX[i], posY[i])==true && eatordodge[i]==14 )
                {
                    speed+=1;
                    eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                    posX.erase(posX.begin()+i,posX.begin()+i+1);
                    posY.erase(posY.begin()+i,posY.begin()+i+1);
                    trapNumber--;
                    i--;
                }
                if (collision1( x_red, y_red, posX[i], posY[i])==true && eatordodge[i]==15 )
                {
                    speed-=1;
                    eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                    posX.erase(posX.begin()+i,posX.begin()+i+1);
                    posY.erase(posY.begin()+i,posY.begin()+i+1);
                    trapNumber--;
                    i--;
                }

                if (posY[i]>700 )
                {
                    if (eatordodge[i]==1 || eatordodge[i]==3)
                    {
                        die=true ;
                    }
                    else
                    {
                        eatordodge.erase(eatordodge.begin()+i,eatordodge.begin()+i+1);
                        posX.erase(posX.begin()+i,posX.begin()+i+1);
                        posY.erase(posY.begin()+i,posY.begin()+i+1);
                        trapNumber--;
                        i--;
                    }
                }

            }
            // draw trap
            for (int i = 0; i < trapNumber; i++)
            {

                //input
                if  (eatordodge[i] == 0)
                    trap.setTexture(red_dodge);
                if  (eatordodge[i] == 1)
                    trap.setTexture(red_eat);
                if  (eatordodge[i] == 2)
                    trap.setTexture(blue_dodge);
                if  (eatordodge[i] == 3)
                    trap.setTexture(blue_eat);
                if  (eatordodge[i] == 14)
                    trap.setTexture(_increase);
                if  (eatordodge[i]==15)
                    trap.setTexture(_fall);
                trap.setPosition(posX[i],posY[i]);
                //update
                posY[i] +=speed;
                if (start==true)
                    window.draw(trap);

            }
            keyboard(red_car, blue_car);
            window.display();

        }


    }

    return 0;
}
