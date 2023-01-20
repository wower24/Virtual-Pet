#include <iostream>

export module All_Modules:Player;

export import :Dog;

export
{
	class Player
	{
		std::string username; //name of the user - same user can have many dogs
		int coins; //number of money (to buy food)
		int foodCount; //number of food in Storage
		int abilityPoints = 0;

	public:

		//default constructor will never be used if everything goes right
		Player()
		{
			std::cout << "This is a default player." << std::endl;
			this->username = "x";
			this->coins = 0;
			this->foodCount = 0;
		}

		//for this constructor load parameters from a file
		Player(std::string s, int i, int fc)
		{
			this->username = s;
			this->coins = i;
			this->foodCount = fc;
		}

		//if there's a need to change name
		void setName(std::string s)
		{
			this->username = s;
		}

		std::string getName()
		{
			return this->username;
		}

		void setValue(int x, int y)
		{
			if (x == 0)
				this->coins = y;
			else if (x == 1)
				this->foodCount = y;
		}

		int getValue(int x)
		{
			//0 - coins, 1 - foodCount
			if (x == 0)
				return this->coins;
			else if (x == 1)
				return this->foodCount;
			else if (x == 2)
				return this->abilityPoints;
			else
				return 12345;
		}

		void initialValues()
		{
			this->coins = 10;
			this->foodCount = 3;
		}

		void buyFood()
		{
			this->foodCount++;
			this->coins--;
		}

		void feed(pDog& d)
		{
			//IT WILL BE ACTIVATED WITH DRAG&DROP METHOD
			//TODO
			if (this->foodCount > 0)
			{
				this->foodCount--;
				d.dFeed();
			}
			else
				std::cout << "THERE'S NO FOOD IN YOUR INVENTORY, BUY SOME TO FEED THE DOG" << std::endl;
		}

		void play(pDog& d)
		{
			d.dPlay();
		}

		void putToSleep(pDog& d)
		{
			d.dPutToSleep();
		}

		void train(pDog& d)
		{
			d.training();
			this->abilityPoints += 5;
		}

		void assignPoints(pDog &d, int x)
		{
			if (this->abilityPoints > 0)
			{
				this->abilityPoints--;
				if (x == 0)
				{
					d.setPoints(3, 1);
				}
				else if (x == 1)
				{
					d.setPoints(4, 1);
				}
				else if (x == 2)
				{
					d.setPoints(5, 1);
				}
			}
			else
				std::cout << "NO ABILITY POINTS LEFT, TRAIN YOUR DOG TO GAIN SOME" << std::endl;
		}

		void comp(pDog& d)
		{
			std::cout << "COMPETITION" << std::endl;
			this->setValue(0, this->getValue(0) + d.compete());

		}
	};
}
