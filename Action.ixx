export module All_Modules:Action;

export
{
	class Action
	{
	protected:
		int points;

	public:
		//constructor for a new game
		Action()
		{
			this->points = 0;
		}

		//constructor for a resume
		Action(int x)
		{
			this->points = x;
		}

		void increasePoints()
		{
			this->points++;
		}

		int getPoints()
		{
			return this->points;
		}

		void setPoints(int x)
		{
			this->points = x;
		}
	};

	class Needs : public Action
	{
	public:
		//the default constructor for needs is different since the dog is fully happy at the beginning
		Needs()
		{
			this->points = 10;
		}

		void decreasePoints()
		{
			this->points--;
		}
	};

	class Progress : public Action
	{
	public:
		Progress()
		{
			this->points = 0;
		}
	};
}