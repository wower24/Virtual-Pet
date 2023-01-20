#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::chrono;

export module All_Modules:Dog;

export import :Action;

export
{
	class Dog
	{
	protected:
		Progress speed;
		Progress jump;
		Progress obedience;

	public:
		Dog()
		{
			std::cout << "This is Dog default constructor. It does absolutely nothing." << std::endl;
		}

		void setPoints(Progress x, int y)
		{
			if (y >= 0 && y <= 10)
				x.setPoints(y);
			else if (y < 0)
				x.setPoints(0);
			else
				x.setPoints(10);
		}

		void bark()
		{
			std::cout << "Woof" << std::endl;
		}


	};

	class pDog : Dog
	{
		std::string dName;
		int age;

		Needs food;
		Needs play;
		Needs sleep;

	public:
		//This will be never used if everything goes right
		pDog()
		{
			std::cout << "This is a default played dog constructior." << std::endl;
		}

		//Parameters for this constructor will be loaded from file
		pDog(std::string n, int a, int f, int p, int sl, int sp, int j, int o)
		{
			this->dName = n;
			this->age = a;
			this->food.setPoints(f);
			this->play.setPoints(p);
			this->sleep.setPoints(sl);
			this->speed.setPoints(sp);
			this->jump.setPoints(j);
			this->obedience.setPoints(o);
		}

		void setName(std::string n)
		{
			this->dName = n;
		}

		std::string getName()
		{
			return this->dName;
		}

		int getAge()
		{
			return this->age;
		}

		void setAge(int a)
		{
			this->age = a;
		}

		void setPoints(int x, int y)
		{
			if (x == 0)
				this->food.setPoints(y);
			else if (x == 1)
				this->play.setPoints(y);
			else if (x == 2)
				this->sleep.setPoints(y);
			else if (x == 3)
				this->speed.setPoints(this->speed.getPoints() + y);
			else if (x == 4)
				this->jump.setPoints(this->jump.getPoints() + y);
			else if (x == 5)
				this->obedience.setPoints(this->obedience.getPoints() + y);
		}

		int getPoints(int x)
		{
			//0 - food, 1 - play, 2 - sleep, 3 - speed, 4 - jump, 5 - obedience
			if (x == 0)
				return this->food.getPoints();
			else if (x == 1)
				return this->play.getPoints();
			else if (x == 2)
				return this->sleep.getPoints();
			else if (x == 3)
				return this->speed.getPoints();
			else if (x == 4)
				return this->jump.getPoints();
			else if (x == 5)
				return this->obedience.getPoints();
			else
				return 12345;
		}

		void initialValues()
		{
			this->age = 2;
			this->food.setPoints(5);
			this->play.setPoints(5);
			this->sleep.setPoints(5);
			this->speed.setPoints(0);
			this->jump.setPoints(0);
			this->obedience.setPoints(0);
		}

		void dFeed()
		{
			if (this->food.getPoints() < 10)
				this->food.increasePoints();
			else
				std::cout << "THIS DOG IS NOT HUNGRY" << std::endl;
		}

		void dPlay()
		{
			//playing will take 5 seconds per need point
			//maybe a minigame here if I have time
				//wait 5 seoncds
				std::cout << "PLAY + 1" << std::endl;

				if ((this->sleep.getPoints()) > 0 && (this->food.getPoints()) > 0)
				{
					this->sleep.decreasePoints();
					this->play.increasePoints();
					this->food.decreasePoints();
				}
				else if (this->sleep.getPoints() == 0)
				{
					std::cout << "THE DOG IS TOO TIRED" << std::endl;
				}
				else if (this->food.getPoints() == 0)
				{
					std::cout << "THE DOG IS TOO HUNGRY" << std::endl;
				}

			std::cout << "PLAYING DONE" << std::endl;
		}

		void dPutToSleep()
		{
			//Sleeping will take 10 seconds per need point
			for (int i = (this->sleep.getPoints()); i < 10; i++)
			{
				//wait 10 seconds
				std::this_thread::sleep_for(seconds(10));
				std::cout << "SLEEP + 1" << std::endl;
				this->sleep.increasePoints();
			}

			std::cout << "SLEEPING DONE" << std::endl;
		}

		void training()
		{
			std::cout << "TRAINING HAS STARTED, PLEASE WAIT FOR IT TO BE DONE (5 SECONDS)" << std::endl;
			std::this_thread::sleep_for(seconds(5));
			this->sleep.decreasePoints();
			this->play.decreasePoints();
			this->food.decreasePoints();
		}

		int compete()
		{
			int price = this->speed.getPoints() + this->jump.getPoints() + this->obedience.getPoints();

			return price / 3;
		}

		void bark()
		{
			std::cout << "This is personalized bark: Hau" << std::endl;
		}
	};
}
