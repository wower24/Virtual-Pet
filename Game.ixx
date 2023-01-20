export module All_Modules:Game;

import <iostream>;
import <filesystem>;
import <fstream>;
import <map>;
import <string>;
export import :Player;

using namespace std;
namespace fs = std::filesystem;

export
{
	std::map<std::string, fs::path> dogMap;

	class Game
	{
	public:
		Player p;
		pDog d;
		int userCounter;

		Game()
		{
			cout << "Default game constructor" << endl;
		}

		void newGame(string username, string dogname)
		{

			//username and dogname are passed through textboxes at the beginning

			p.setName(username);
			d.setName(dogname);
			
			//player set up
			p.initialValues();
			//dog set up
			d.initialValues();

			fs::path path{ "C:\\Users\\marta\\Desktop\\STUDIA\\INFE\\SEM4\\CP\\Project\\Virtual_Pet\\x64\\Release" };
			
			fstream f;
			ofstream fc;
			fc.open(dogname);
			if (!fc.is_open())
				cout << "ERROR! Couldn't open the game file." << endl;
			else
			{
				//load all the values - each in different line
				//for player - name, coins, foodCount
				fc << username << endl << p.getValue(0) << endl << p.getValue(1) << endl;
				//for dog
				fc << d.getAge() << endl;

				for (int i = 0; i < 5; i++)
					fc << d.getPoints(i) << endl;
				
				fs::path temp = fs::current_path();
				fc.close();

				temp /= dogname;
				dogMap.insert(pair<string, fs::path>(dogname, temp));

				f.open(path / "dogmap.txt", ios::out|ios::app);
				f << dogname << endl << temp.string() << endl;
				f.close();
			}
		}

		void resume(std::string dogname)
		{
			fs::path rPath{ dogMap.find(dogname)->second };
			d.setName(dogname);
			loadData(rPath);
		}

		void loadData(fs::path loadPath)
		{
			fstream f;
			string n;
			int x;
			int i = 0;
			f.open(loadPath);
			while (!f.eof())
			{
				if (i == 0)
					getline(f, n);
				else
					f >> x;

				if (i == 0)
					p.setName(n);
				else if (i == 1)
					p.setValue(0, x);
				else if (i == 2)
					p.setValue(1, x);
				else if (i == 3)
					d.setAge(x);
				else if (i == 4)
					d.setPoints(0, x);
				else if (i == 5)
					d.setPoints(1, x);
				else if (i == 6)
					d.setPoints(2, x);
				else if (i == 7)
					d.setPoints(3, x);
				else if (i == 8)
					d.setPoints(4, x);
				else if (i == 9)
					d.setPoints(5, x);

				i++;
			}
		}

		void uploadData(string dogname)
		{
			fstream f;
			f.open(dogname);
			f.clear();
			f << p.getName() << endl << p.getValue(0) << endl << p.getValue(1) << endl;
			f << d.getAge() << endl;
			for (int i = 0; i < 5; i++)
				f << d.getPoints(i) << endl;
			f.close();
		}

		void loadMap()
		{
			fs::path lPath{ "C:/Users/marta/Desktop/STUDIA/INFE/SEM4/CP/Project/Virtual_Pet/x64/Release" };
			fstream f;
			string x;
			string y;
			int i = 0;
			this->userCounter = 0;

			cout << "Loading map..." << endl;

			f.open(lPath / "dogmap.txt");
			while (!f.eof())
			{
				getline(f, x);
				getline(f, y);
				fs::path p{ y };

				if (!f.eof())
				{
					dogMap.insert(pair<string, fs::path>(x, y));
					userCounter++;
				}
			}
			f.close();

			cout << "Map Loaded!" << endl;
		}
	};
}