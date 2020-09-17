#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string.h>
#include <algorithm>

int main()
{
	///////////////////////////////////|||WINDOW|||////////////////////////////////////////
	srand(time(NULL));
	//set window
	sf::RenderWindow window(sf::VideoMode(1440, 750), "Dragon's Revenge", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	

	sf::Image icon;
	icon.loadFromFile("image/image.png");
	window.setIcon(600, 450, icon.getPixelsPtr());
	/////////////////////////////////||Main-(start / highscore )||//////////////////////
	sf::Texture maintexture;
	if (!maintexture.loadFromFile("image/Dragonbg.png"))return EXIT_FAILURE;
	sf::Sprite main(maintexture);
	main.setScale((float)window.getSize().x / maintexture.getSize().x, (float)window.getSize().y / maintexture.getSize().y);

	sf::Texture Nametexture;
	if (!Nametexture.loadFromFile("image/name.png"))return EXIT_FAILURE;
	sf::Sprite name(Nametexture);
	name.setPosition(50, 50);
	//name.setScale((float)1.1, (float)1.1);

	sf::Texture playtexture;
	if (!playtexture.loadFromFile("image/play.png"))return EXIT_FAILURE;
	sf::Sprite playbt(playtexture);
	playbt.setPosition(400, 375);
	playbt.setScale((float)1.1, (float)1.1);
	sf::Texture HStexture;
	if (!HStexture.loadFromFile("image/highscore.png"))return EXIT_FAILURE;
	sf::Sprite HSbt(HStexture);
	HSbt.setPosition(175, 555);
	
	//////////////////////////////////||CHARACTER||///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//main character
	//rectangle to crop texture dragon
	sf::RectangleShape Dragon(sf::Vector2f(191, 136));
	Dragon.setPosition(sf::Vector2f(100, 450));

	sf::Texture texdragon;
	texdragon.setRepeated(true);
	texdragon.setSmooth(true);

	if (!texdragon.loadFromFile("image/dragon.png"))return EXIT_FAILURE;
	Dragon.setTexture(&texdragon);
	Dragon.setScale((float)1.25, (float)1.25);

	sf::Vector2u currentBox(0, 0);
	sf::IntRect boxRecDg;
	boxRecDg.width = texdragon.getSize().x / 3;
	boxRecDg.height = texdragon.getSize().y;
	boxRecDg.left = currentBox.x;
	boxRecDg.top = currentBox.y;

	//HP
	int DragonHP = 100000;
	sf::RectangleShape HP(sf::Vector2f(DragonHP / 250, 30));
	HP.setFillColor(sf::Color::Green);
	HP.setPosition(sf::Vector2f(160, 50));

	sf::Sprite hpbar;
	sf::Texture HPbar;
	if (!HPbar.loadFromFile("image/hp.png"))return EXIT_FAILURE;
	hpbar.setTexture(HPbar);
	hpbar.setPosition(48, 32);
	hpbar.setScale(1, 1);

	//////////////////////////////////////////////////////////////////////////////////
	//fire
	//rectangle to crop texture fire
	sf::RectangleShape fire(sf::Vector2f(516, 512));

	sf::Texture firetex;
	firetex.setRepeated(true);
	firetex.setSmooth(true);
	if (!firetex.loadFromFile("image/flame.png"))return EXIT_FAILURE;
	fire.setTexture(&firetex);

	sf::Vector2u currentfireBox(0, 0);
	sf::IntRect boxRecfire;
	boxRecfire.width = firetex.getSize().x / 6;
	boxRecfire.height = firetex.getSize().y;
	boxRecfire.left = currentfireBox.x;
	boxRecfire.top = currentfireBox.y;
	fire.setScale((float)1 / 5, (float)1 / 5);// a/b=wanted size/real size

	std::vector<sf::RectangleShape> fires;
	fires.push_back(sf::RectangleShape(fire));
	fires[0].setPosition(-100, -100);//debug first fire draw at start of the game
	int firetimer = 0;//to draw fire with delay time
	////////////////////////////////||ENEMY||///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	//enemy knight
	sf::RectangleShape knight(sf::Vector2f(550, 598));
	sf::Texture knighttex;
	knighttex.setRepeated(true);
	knighttex.setSmooth(true);
	if (!knighttex.loadFromFile("image/knight.png"))return EXIT_FAILURE;
	knight.setTexture(&knighttex);

	sf::Vector2u currentknightBox(0, 0);
	sf::IntRect boxRecknight;
	boxRecknight.width = knighttex.getSize().x / 8;
	boxRecknight.height = knighttex.getSize().y;
	boxRecknight.left = currentknightBox.x;
	boxRecknight.top = currentknightBox.y;
	knight.setScale((float)1 / 6, (float)1 / 6);// a/b=wanted size/real size

	std::vector<sf::RectangleShape> knights;
	knights.push_back(sf::RectangleShape(knight));
	int knightspawn = 0;

	//knight atk
	sf::Texture knightatk;
	knightatk.setRepeated(true);
	knightatk.setSmooth(true);
	if (!knightatk.loadFromFile("image/knightatk.png"))return EXIT_FAILURE;
	//-----------------------------------------------------------------------------//
	//wizard
	sf::RectangleShape wizard(sf::Vector2f(1592 / 4, 375));
	sf::Texture wizardtex;
	wizardtex.setRepeated(true);
	wizardtex.setSmooth(true);
	if (!wizardtex.loadFromFile("image/wizard.png"))return EXIT_FAILURE;
	wizard.setTexture(&wizardtex);

	sf::Vector2u currentwizardBox(0, 0);
	sf::IntRect boxRecwizard;
	boxRecwizard.width = wizardtex.getSize().x / 4;
	boxRecwizard.height = wizardtex.getSize().y;
	boxRecwizard.left = currentwizardBox.x;
	boxRecwizard.top = currentwizardBox.y;
	wizard.setScale((float)1 / 4, (float)1 / 4);// a/b=wanted size/real size

	std::vector<sf::RectangleShape> wizards;
	wizards.push_back(sf::RectangleShape(wizard));
	wizards[0].setPosition(-1111, -1111);
	int wizardspawn = 0;

	//wizard atk
	sf::Texture wizardatk;
	wizardatk.setRepeated(true);
	wizardatk.setSmooth(true);
	if (!wizardatk.loadFromFile("image/wizardatk.png"))return EXIT_FAILURE;

	//wizardfire
	sf::RectangleShape wizardfire(sf::Vector2f(1536 / 3, 394 / 2));

	sf::Texture wizardfiretex;
	wizardfiretex.setRepeated(true);
	wizardfiretex.setSmooth(true);
	if (!wizardfiretex.loadFromFile("image/wifire.png"))return EXIT_FAILURE;
	wizardfire.setTexture(&wizardfiretex);

	sf::Vector2u currentwizardfireBox(0, 0);
	sf::IntRect boxRecwizardfire;
	boxRecwizardfire.width = wizardfiretex.getSize().x / 3;
	boxRecwizardfire.height = wizardfiretex.getSize().y / 2;
	boxRecwizardfire.left = currentwizardfireBox.x;
	boxRecwizardfire.top = currentwizardfireBox.y;
	wizardfire.setScale((float)1 / 4, (float)1 / 4);// a/b=wanted size/real size

	std::vector<sf::RectangleShape> wizardfires;
	wizardfires.push_back(sf::RectangleShape(wizardfire));
	wizardfires[0].setPosition(-100, -100);//debug first wizardfire draw at start of the game
	int wizardfiretimer = 0;//to draw wizardfire with delay time
	//-----------------------------------------------------------------------------
	//arrow
	sf::Texture Arrowtex; if (!Arrowtex.loadFromFile("image/Arrow.png"))return EXIT_FAILURE;
	sf::RectangleShape arrow(sf::Vector2f(254, 53));
	arrow.setTexture(&Arrowtex);
	arrow.setRotation(115);
	arrow.setScale((float)1 / 3, (float)1 / 3);
	std::vector<sf::RectangleShape> arrows;
	arrows.push_back(sf::RectangleShape(arrow));
	arrows[0].setPosition(-500, -500);//debug
	int arrowspawn = 0;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////||Explosion||////////////////////////////////////////
	sf::RectangleShape exp(sf::Vector2f(128, 120));
	sf::Texture explosion;
	explosion.setRepeated(true);
	explosion.setSmooth(true);
	if (!explosion.loadFromFile("image/explosion.png"))return EXIT_FAILURE;
	exp.setTexture(&explosion);

	sf::Vector2u currentexp(0, 0);
	sf::IntRect boxexp;
	boxexp.width = explosion.getSize().x / 10;
	boxexp.height = explosion.getSize().y;
	boxexp.left = currentexp.x;
	boxexp.top = currentexp.y;
	//
	int startexplosion = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////||Special Item||///////////////////////////////////////////////////////////////
	sf::RectangleShape star(sf::Vector2f(875/7, 114));
	sf::Texture Star;
	Star.setRepeated(true);
	Star.setSmooth(true);
	if (!Star.loadFromFile("image/star.png"))return EXIT_FAILURE;
	star.setTexture(&Star);
	star.setScale((float)2 / 3, (float)2 / 3);
	star.setPosition(1500, 1000);
	sf::Vector2u currentstar(0, 0);
	sf::IntRect boxstar;
	boxstar.width = Star.getSize().x / 7;
	boxstar.height = Star.getSize().y;
	boxstar.left = currentstar.x;
	boxstar.top = currentstar.y;
	int spawnspecialitem=0;

	//shield
	sf::Texture shieldtex;
	if (!shieldtex.loadFromFile("image/shield.png"))return EXIT_FAILURE;
	sf::Sprite shield(shieldtex);
	shield.setScale((float)1.2 / 3, (float)1.2 / 3);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//time variable
	float totalTime = 0, switchTime = 0.2, firetime = 0, fireswitch = 0.1, knighttime = 0, knightswitch = 0.2, expTime = 0, expswitch = 0.1;
	float wizardtime = 0, wizardswitch = 0.4, wizardfiretime = 0, wizardfireswitch = 0.2,startime=0,starswitch=0.1;
	///////////////////////////////////////////////BACKGROUND////////////////////////////////////////////////////////////
	//background
	sf::Texture background; if (!background.loadFromFile("image/BG.png"))return EXIT_FAILURE;
	sf::Sprite bg1(background), bg2(background);
	bg1.setScale((float)window.getSize().x / background.getSize().x, (float)window.getSize().y / background.getSize().y);
	bg2.setScale((float)window.getSize().x / background.getSize().x, (float)window.getSize().y / background.getSize().y);
	bg2.setPosition(bg1.getPosition().x + 1440, 0);
	// lose bg
	sf::Texture endbackground; if (!endbackground.loadFromFile("image/bgend.jpg"))return EXIT_FAILURE;
	sf::Sprite bgend(endbackground);
	bgend.setScale((float)window.getSize().x / endbackground.getSize().x, (float)window.getSize().y / endbackground.getSize().y);

	sf::Texture hsbackground; if (!hsbackground.loadFromFile("image/highscorebg.png"))return EXIT_FAILURE;
	sf::Sprite hsbg(hsbackground);
	hsbg.setScale((float)window.getSize().x / hsbackground.getSize().x, (float)window.getSize().y / hsbackground.getSize().y);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////||SOUND||//////////////////////////////////////////////
	//BGM
	sf::Music music;
	music.openFromFile("image/BGM.wav");
	music.setLoop(true);

	sf::Music musicgame;
	musicgame.openFromFile("image/BGM2.wav");
	musicgame.setLoop(true);

	sf::Music losemusic;
	losemusic.openFromFile("image/lose.wav");
	losemusic.setLoop(true);

	//fire sound effect
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("image/flamestrike.wav")) {}
	sf::Sound sound;
	sound.setBuffer(buffer);

	//explosion sound
	sf::SoundBuffer expsfx;
	if (!expsfx.loadFromFile("image/Explosion.wav")) {}
	sf::Sound explosionsound;
	explosionsound.setVolume(25);
	explosionsound.setBuffer(expsfx);

	//Arrowhit
	sf::SoundBuffer ah;
	if (!ah.loadFromFile("image/Arrowhit.wav")) {}
	sf::Sound Arrowhit;
	Arrowhit.setBuffer(ah);

	//hsbgm
	sf::Music HSbgm;
	HSbgm.openFromFile("image/thrud.wav");
	HSbgm.setLoop(true);
	//////////////////////////////////////////////////////////////////////////////////
	//text
	sf::Font font;
	font.loadFromFile("image/m5x7.ttf");

	sf::Font dgfont;
	dgfont.loadFromFile("image/drgfont.ttf");

	sf::Text text("SCORE : ", font, 60);
	text.setPosition(1150, 5);
	text.setFillColor(sf::Color::Black);

	sf::Text score("", font, 60);
	score.setPosition(1320, 5);
	score.setFillColor(sf::Color::Black);
	int Score = 0;
	//////////////////////////////////////////////////////////////////////////////////
	int specialitem = 0;
	int specialitemtime = 0;
	//////////////////////////////////////////////////////////////////////////////////
	//High Score
	std::ofstream highscore;
	sf::Text entername(" Please Enter Your Name : ", dgfont, 30);
	entername.setPosition(200, 150);
	entername.setFillColor(sf::Color::Yellow);

	sf::String yourname;
	sf::Text player;
	player.setFillColor(sf::Color::Yellow);
	int t = 0;
	
	std::vector<std::pair<int, std::string>>scoreboard;

	sf::Text x("HIGHSCORE ", font, 100);
	x.setPosition(570, 10);
	x.setFillColor(sf::Color::Black);


	sf::Text esc("Press esc to go back ", font, 50);
	esc.setPosition(1050, 675);
	esc.setFillColor(sf::Color::Black);

	/////////////////////////////////////////////////////////////////////////////////
	sf::Event event;
	goto Main;

	//////////////////////////////[LOOP Main]////////////////////////////////////
Main:
	losemusic.stop();
	music.setVolume(100);
	music.play();
	HSbgm.stop();
	t = 0;
	sf::Text myname("Developed by Nattarat Serirat 61010352 ", font, 50);
	myname.setPosition(720, 675);
	myname.setFillColor(sf::Color::Yellow);

	Score = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		playbt.setColor(sf::Color::White);
		HSbt.setColor(sf::Color::White);
		sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
		if (MousePosition.x > 400 && MousePosition.x < 594 && MousePosition.y>375 && MousePosition.y < 375 + 131)
		{
			playbt.setColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				goto Game;
			}
		}
		if (MousePosition.x > 175 && MousePosition.x < 589 + 175 && MousePosition.y>555 && MousePosition.y < 128 + 555)
		{
			HSbt.setColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				scoreboard.clear();
				std::ifstream loadFile;
				loadFile.open("example.txt");
				while (!loadFile.eof()) {
					std::string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					//cout << ">> \"" << tempName << "\" " << tempScore << endl;
					scoreboard.push_back({ tempScore,tempName });
				}
				std::sort(scoreboard.begin(), scoreboard.end(), std::greater<std::pair<int, std::string>>());
				goto Highscore;

				
			}
		}

		window.clear();
		window.draw(main);
		window.draw(name);
		window.draw(HSbt);
		window.draw(myname);
		window.draw(playbt);
		window.display();
	}
//////////////////////////////HIGHSCORE/////////////////////////////////////
Highscore:
	music.stop();
	HSbgm.play();
	music.stop();
	while (window.isOpen())
	{
		
		//close Event/////////////////////////////////
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{

				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{

				goto Main;
			}	
		}
		window.clear();
		window.draw(hsbg);
		window.draw(esc);
		window.draw(x);
		int cnt = 0;  //ประกาศตัวนับ
		for (std::vector<std::pair<int, std::string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i) {
			++cnt;                     //เมื่อตัวนับเกิน 5 ให้จบการทำงาน
			sf::Text a, b;                                //ประกาศ Text             //เนื่องจากค่าคะแนนเป็น integer จึงต้องทำการแปลงเป็น string ก่อนนำมาแสดงผล (first คือpair ตัวที่หนึ่ง =>int)
			a.setFont(font);                        //การตั้งค่า Font คะแนน
			a.setCharacterSize(40);                   //ตั้งค่าขนาด Font คะแนน
			b.setFont(font);                        //การตั้งค่า Font ชื่อผู้เล่น
			b.setCharacterSize(40);                   //ตั้งค่าขนาด Font ชื่อผู้เล่น
			b.setString(i->second);            // (second คือpair ตัวที่สอง =>string) 
			a.setString(std::to_string(i->first));
			if (cnt < 8) {
				a.setPosition(900, 120 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของคะแนน และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
				b.setPosition(500, 120 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของชื่อผู้เล่น และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
			}
			else break;

			window.draw(a);                           //แสดงผลคะแนน
			window.draw(b);                           //แสดงผลชื่อผู้เล่น
		}
		window.display();
		
	}
//////////////////////////////[LOOP Game]////////////////////////////////////
Game:
	music.stop();
	musicgame.setVolume(50);
	musicgame.play();
	sf::Clock clockdragon, clockfire, clockknight, clockexp, clockexpII, clockwizard, clockwizardfire,clockstar;


	while (window.isOpen())
	{
		//close Event/////////////////////////////////
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		//animation 
			totalTime += clockdragon.restart().asSeconds();
			if (totalTime >= switchTime)
			{
				currentBox.x++;
				if (currentBox.x >= 3)
				{
					currentBox.x = 0;
				}
				boxRecDg.left = currentBox.x*boxRecDg.width;
				totalTime -= switchTime;
			}
			//----------------------------------------------------------------//
			//animation of Fire
			firetime += clockfire.restart().asSeconds();
			if (firetime >= fireswitch)
			{
				currentfireBox.x++;
				if (currentfireBox.x >= 6)
				{
					currentfireBox.x = 0;
				}
				boxRecfire.left = currentfireBox.x*boxRecfire.width;
				firetime -= fireswitch;
			}
			//------------------------------------------------------------------//
			//animation of knight
			knighttime += clockknight.restart().asSeconds();
			if (knighttime >= knightswitch)
			{
				currentknightBox.x++;
				if (currentknightBox.x >= 8)
				{
					currentknightBox.x = 0;
				}
				boxRecknight.left = currentknightBox.x*boxRecknight.width;
				knighttime -= knightswitch;
			}
			//----------------------------------------------------------------//
			//animation of wizard
			wizardtime += clockwizard.restart().asSeconds();
			if (wizardtime >= wizardswitch)
			{
				currentwizardBox.x++;
				if (currentwizardBox.x >= 4)
				{
					currentwizardBox.x = 0;
				}
				boxRecwizard.left = currentwizardBox.x*boxRecwizard.width;
				wizardtime -= wizardswitch;
			}
			wizardfiretime += clockwizardfire.restart().asSeconds();
			if (wizardfiretime >= wizardfireswitch)
			{
				currentwizardfireBox.x++;
				if (currentwizardfireBox.x >= 3)
				{
					currentwizardfireBox.x = 0;
				}
				boxRecwizardfire.left = currentwizardfireBox.x*boxRecwizardfire.width;
				wizardfiretime -= wizardfireswitch;
			}
			startime += clockstar.restart().asSeconds();
			if (startime >= starswitch)
			{
				currentstar.x++;
				if (currentstar.x >= 7)
				{
					currentstar.x = 0;
				}
				boxstar.left = currentstar.x*boxstar.width;
				startime -= starswitch;
			}
			//animation of explosion
			expTime += clockexp.restart().asSeconds();
			if (expTime >= expswitch && startexplosion == 1)
			{
				currentexp.x++;
				if (currentexp.x >= 10)
				{
					startexplosion = 0;
					currentexp.x = 0;
				}

				boxexp.left = currentexp.x*boxexp.width;
				expTime -= expswitch;
			}
			//-------------------------------------------------------------------//

			//animation of Background
			if (bg1.getPosition().x < -1440) bg1.setPosition(1430, 0);
			if (bg2.getPosition().x < -1440) bg2.setPosition(1430, 0);

			if (bg1.getPosition().x > 1440) bg1.setPosition(-1430, 0);
			if (bg2.getPosition().x > 1440) bg2.setPosition(-1430, 0);
			/////////////////////////////////////MOVEMENT/////////////////////////////////////////////////
			sf::Vector2f posdragon = Dragon.getPosition();//get position to keep Dragon doesn't go off screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && posdragon.x < 1440 - boxRecDg.width*1.25) {
				Dragon.move(5, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && posdragon.x > 0) {
				Dragon.move(-5, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && posdragon.y > 0) {
				Dragon.move(0, -5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && posdragon.y < 700 - boxRecDg.height*1.25) {
				Dragon.move(0, 5);
			}
			//////for test & debug [Cheat]////
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				specialitem = 3;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				if (DragonHP < 100000)DragonHP += 2000;
			}*/
			//////////////////////////////////////////||ATTACK||///////////////////////////////////////////
			//fire
			if (firetimer <= 25)
			{
				firetimer++;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && firetimer > 25)
			{
				firetimer = 0;
				fire.setPosition(posdragon.x + boxRecDg.width - 20, posdragon.y + (boxRecDg.height / 2));
				fires.push_back(sf::RectangleShape(fire));
				sound.play();

			}
			for (size_t i = 0; i < fires.size(); i++)
			{
				fires[i].move(6, 0);
				if (fires[i].getPosition().x >= 1440)
				{
					fires.erase(fires.begin() + i);
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////
			//knight spawn//////
			int spawn, level;
			level = Score / 500 + 1;
			if (level >= 300)level = 300;
			spawn = 300 / level;
			if (knightspawn < rand() % spawn + 20)
			{
				knightspawn++;
			}
			if (knightspawn >= rand() % spawn + 20)
			{
				knight.setPosition(1440, rand() % 250 + 350);
				knights.push_back(sf::RectangleShape(knight));
				knightspawn = 0;
			}
			//knight atk&move//////
			for (size_t i = 0; i < knights.size(); i++)
			{
				if (Dragon.getGlobalBounds().intersects(knights[i].getGlobalBounds()) && Dragon.getPosition().y < knights[i].getPosition().y + 30 && Dragon.getPosition().y + boxRecDg.height*1.25 > knights[i].getPosition().y + boxRecknight.height / 6 - 20)
				{
					knights[i].move(0, 0);
					knights[i].setTexture(&knightatk);
					if (specialitem != 3)DragonHP -= 50;
					//break;
				}
				else
				{
					knights[i].move(-5, 0);

					if (knights[i].getPosition().x < 0)
					{
						knights.erase(knights.begin() + i);
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////
			//wizard spawn///////
			int spawnwi;
			if (level >= 300)level = 300;
			spawnwi = 300 / level;
			if (wizardspawn < rand() % spawn + 250)
			{
				wizardspawn++;
			}
			if (wizardspawn >= rand() % spawn + 250)
			{
				wizard.setPosition(1540, rand() % 250 + 350);
				wizards.push_back(sf::RectangleShape(wizard));
				wizardspawn = 0;

			}
			//wizard atk&move///////
			if (wizardfiretimer < rand() % 50 + 100)
			{
				wizardfiretimer++;
			}
			for (size_t i = 0; i < wizards.size(); i++)
			{

				if (wizards[i].getPosition().x < rand() % 300 + 900)
				{
					wizards[i].move(0, 0);
					wizards[i].setTexture(&wizardatk);
					if (wizardfiretimer >= rand() % 50 + 100)
					{

						for (size_t i = 0; i < wizards.size(); i++)
						{
							if (wizards[i].getPosition().x < 1200)
							{
								wizardfiretimer = 0;
								wizardfire.setPosition(wizards[i].getPosition().x, wizards[i].getPosition().y);
								wizardfires.push_back(sf::RectangleShape(wizardfire));
							}
						}

					}
				}
				else
				{
					wizards[i].move(-3, 0);
					if (wizards[i].getPosition().x < 0)
					{
						wizards.erase(wizards.begin() + i);
					}
				}
			}
			///wizard fire move///////
			for (size_t i = 0; i < wizardfires.size(); i++)
			{
				wizardfires[i].move(-6, 0);
				if (wizardfires[i].getPosition().x < 0)
				{
					wizardfires.erase(wizardfires.begin() + i);
				}
			}
			//////////////////////////////////////////////////////////////////////////////
			//Arrow
			//ArrowSpawn
			int spawnarrow;
			if (level >= 300)level = 300;
			spawnarrow = 300 / level;
			if (arrowspawn < rand() % spawn + 30)
			{
				arrowspawn++;
			}
			if (arrowspawn >= rand() % spawn + 30)
			{
				arrow.setPosition(rand() % 700 + 500, 0);
				arrows.push_back(sf::RectangleShape(arrow));
				arrowspawn = 0;
			}
			//arrowatk
			for (size_t i = 0; i < arrows.size(); i++)
			{
				if (Dragon.getGlobalBounds().intersects(arrows[i].getGlobalBounds()))
				{
					arrows[i].move(-5, 7);
					arrows.erase(arrows.begin() + i);
					if(specialitem!=3)DragonHP -= 3000;
					Arrowhit.play();
					//break;
				}
				else
				{
					arrows[i].move(-5, 7);

					if (arrows[i].getPosition().y > window.getSize().y)
					{
						arrows.erase(arrows.begin() + i);
					}
				}

			}
			/////////////////////////////////////////////////////////////////////
			//special itemspawn
			
			if (spawnspecialitem < 800+rand()%400)
			{
				spawnspecialitem++;
			}
			if (spawnspecialitem >= 800 + rand() % 400 && specialitem==0)
			{
				star.setPosition(rand() % 700 + 200, rand() % 300 );
				spawnspecialitem = 0;
			}

			//////////////////////////////////////||COLLISTION||//////////////////////////////////////////////
			if (!knights.empty() && !fires.empty())
			{
				for (size_t i = 0; i < fires.size(); i++)
				{
					for (size_t j = 0; j < knights.size(); j++)
					{
						if (fires[i].getGlobalBounds().intersects(knights[j].getGlobalBounds()))
						{
							exp.setPosition(knights[j].getPosition());
							startexplosion = 1;
							if (specialitem != 1)fires.erase(fires.begin() + i);
							knights.erase(knights.begin() + j);
							explosionsound.play();
							Score += 10;//<-------------result
							break;
						}
					}
				}
			}
			if (!wizards.empty() && !fires.empty())
			{
				for (size_t i = 0; i < fires.size(); i++)
				{
					for (size_t j = 0; j < wizards.size(); j++)
					{
						if (fires[i].getGlobalBounds().intersects(wizards[j].getGlobalBounds()))
						{
							exp.setPosition(wizards[j].getPosition());
							startexplosion = 1;
							if (specialitem != 1)fires.erase(fires.begin() + i);
							wizards.erase(wizards.begin() + j);
							Score += 50;//<-------------result
							explosionsound.play();
							break;
						}
					}
				}
			}
			if (!wizardfires.empty())
			{
				for (size_t i = 0; i < wizardfires.size(); i++)
				{
					if (wizardfires[i].getGlobalBounds().intersects(Dragon.getGlobalBounds()))
					{
						exp.setPosition(Dragon.getPosition().x + boxRecDg.width * 2 / 3, Dragon.getPosition().y + boxRecDg.height / 2);
						startexplosion = 1;
						wizardfires.erase(wizardfires.begin() + i);
						if (specialitem != 3)DragonHP -= 4000;//<-------------result
						explosionsound.play();
						break;
					}
				}
			}
			if (Dragon.getGlobalBounds().intersects(star.getGlobalBounds()))
			{
				specialitem = rand() % 3 + 1;
				star.setPosition(1000, 1000);
				
			}
			///////////////////////////////||ITEM||/////////////////////////////////////////////////////
			if (specialitem != 0)
			{
				if (specialitem == 1)//Fire bigger
				{
					fire.setScale((float)1 / 2, (float)1 / 2);
					fire.setPosition(posdragon.x + boxRecDg.width - 20, posdragon.y + (boxRecDg.height / 3));
				}
				if (specialitem == 2)//Heal
				{
					if(DragonHP<=100000)
					DragonHP += 70;
					//specialitem == 0;
				}
				if (specialitem == 3)//shield
				{
					shield.setPosition(posdragon.x, posdragon.y);
				}
				//time end
				if (specialitemtime < 300)specialitemtime++;
				if (specialitemtime >= 300)
				{
					specialitem = 0;
					fire.setScale((float)1 / 5, (float)1 / 5);
					specialitemtime = 0;
					spawnspecialitem = 0;
				}
			}
			//////////////////////////////////\\\UPDATE\\////////////////////////////////////////////////
			//update score
			std::string n = std::to_string(Score);
			score.setString(n.c_str());
			//move background
			bg1.move(-2, 0);
			bg2.move(-2, 0);
			//move box every loop
			Dragon.setTextureRect(boxRecDg);
			exp.setTextureRect(boxexp);
			star.setTextureRect(boxstar);
			HP.setSize(sf::Vector2f(DragonHP / 275, 30));
			if (DragonHP > 50000)HP.setFillColor(sf::Color::Green);
			else if (DragonHP > 25000)HP.setFillColor(sf::Color::Yellow);
			else if (DragonHP > 0)HP.setFillColor(sf::Color::Red);
			for (size_t i = 0; i < fires.size(); i++)
			{
				fires[i].setTextureRect(boxRecfire);
			}
			for (size_t i = 0; i < knights.size(); i++)
			{
				knights[i].setTextureRect(boxRecknight);
			}
			for (size_t i = 0; i < wizards.size(); i++)
			{
				wizards[i].setTextureRect(boxRecwizard);
			}
			for (size_t i = 0; i < wizardfires.size(); i++)
			{
				wizardfires[i].setTextureRect(boxRecwizardfire);
			}
			//////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////\\\DRAW\\\\////////////////////////////////////////
			window.clear();
			window.draw(bg1);
			window.draw(bg2);
			window.draw(Dragon);
			if (specialitem == 3)window.draw(shield);
			for (size_t i = 0; i < wizards.size(); i++)
			{
				window.draw(wizards[i]);
			}
			for (size_t i = 0; i < arrows.size(); i++)
			{
				window.draw(arrows[i]);
			}
			for (size_t i = 0; i < knights.size(); i++)
			{
				window.draw(knights[i]);
			}
			for (size_t i = 0; i < fires.size(); i++)
			{
				window.draw(fires[i]);
			}
			for (size_t i = 0; i < wizardfires.size(); i++)
			{
				window.draw(wizardfires[i]);
			}
			if (currentexp.x != 0)window.draw(exp);
			window.draw(text);
			window.draw(score);
			window.draw(HP);
			window.draw(hpbar);
			window.draw(star);
			window.display();
			//LOSE&Esc
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || DragonHP <= 0)
			{
				
				DragonHP = 100000;
				level = 1;
				for (size_t i = 0; i < wizards.size(); i++)
				{
					wizards.erase(wizards.begin());
					wizard.setPosition(1500, 900);
					wizards.push_back(sf::RectangleShape(wizard));
				}
				for (size_t i = 0; i < arrows.size(); i++)
				{
					arrows.erase(arrows.begin());
					arrow.setPosition(1500, 900);
					arrows.push_back(sf::RectangleShape(arrow));
				}
				for (size_t i = 0; i < knights.size(); i++)
				{
					knights.erase(knights.begin() );
					knight.setPosition(1500,900);
					knights.push_back(sf::RectangleShape(knight));
				}
				for (size_t i = 0; i < fires.size(); i++)
				{
					fires.erase(fires.begin());
					fire.setPosition(10000, 4500);
					fires.push_back(sf::RectangleShape(fire));
				}
				for (size_t i = 0; i < wizardfires.size(); i++)
				{
					wizardfires.erase(wizardfires.begin());
					wizardfire.setPosition(15000, 4500);
					wizardfires.push_back(sf::RectangleShape(wizardfire));
				}
				window.clear();
				window.display();

				Sleep(2000);
				goto END;
			}
	}
END:
	musicgame.stop();
	losemusic.setVolume(50);
	losemusic.play();
	yourname.clear();
	while (window.isOpen())
	{
		//close Event/////////////////////////////////
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
	
				window.close();
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\b')
				{//ถ้ากด Backspace เป็นการลบตัวอักษร
					if (yourname.getSize() > 0)yourname.erase(yourname.getSize() - 1, 1);

					player.setFont(font);
					player.setString(yourname);
				}
				else
				{
					std::string name;
					
					if ((event.text.unicode >32)&&(event.text.unicode <128) && (yourname.getSize() < 8)) {
						yourname += static_cast<char>(event.text.unicode);
						name += static_cast<char>(event.text.unicode);
						player.setFont(font);
						player.setString(yourname);
					}
				}
				player.setCharacterSize(60);   //เซ็ตขนาดของข้อความ
				player.setPosition(850, 110);  //เซ็ตขนาดของข้อความ
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					player.setString(yourname);
					std::ofstream myFile;
					myFile.open("example.txt", std::ios::out | std::ios::app);
					myFile << "\n" << std::string(yourname) << " " << (Score);
					myFile.close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				goto Main;
			}
		}
		window.clear();
		window.draw(bgend);
		window.draw(entername);
		window.draw(player);
		window.display();
	}
}
