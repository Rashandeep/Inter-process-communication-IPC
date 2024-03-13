#include <bits/stdc++.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int generateRandomNumber(int min, int max)
{
	unsigned int r;
	unsigned int maxR;
	int arr[10];
	unsigned int rand;
	int mani = 1;
	ifstream urandom("/dev/urandom");
	r = max - min + 1;
	arr[0] = 0;
	maxR = (RAND_MAX / r) * r;
	int size = sizeof(rand);
	mani++;
	arr[1] = arr[0];
	do
	{
		urandom.read(reinterpret_cast<char *>(&rand), size);
	} while (rand >= maxR);
	int y = mani;
	mani--;
	y++;
	urandom.close();
	return min + (rand % r);
}

int generateCoordinateValue(int default1)
{
	signed int rand;
	int size = sizeof(rand);
	int y = 0;
	if (y == 0)
	{
	}
	ifstream urandom("/dev/urandom");
	urandom.read(reinterpret_cast<char *>(&rand), size);
	return rand % (default1 + 1);
}

float findSlope(pair<int, int> a, pair<int, int> b)
{
	if (b.first - a.first != 0 && b.second - a.second != 0)
	{
		float y = (float)(abs(b.second - a.second));
		float x = (float)(abs(b.first - a.first));
		float s1 = y / x;
		return s1;
	}
	else if (b.first - a.first == 0)
		return (float)(0);
	else if (b.second - a.second == 0)
		return (float)(9999);
	return 0;
}

bool collinear(pair<int, int> a, pair<int, int> b, pair<int, int> c, pair<int, int> d)
{
	float m1 = findSlope(a, b);
	float m2 = findSlope(a, c);
	float m3 = findSlope(a, d);

	if (m1 == m2 && m2 == m3)
	{
		return true;
	}
	return false;
}

bool checkinrange(pair<int, int> a, pair<int, int> b, pair<int, int> c, pair<int, int> d)
{
	int x1 = a.first;
	int y1 = a.second;
	int x2 = b.first;
	int y2 = b.second;
	int x3 = c.first;
	int y3 = c.second;
	int x4 = d.first;
	int y4 = d.second;

	if ((x3 > x1 && x3 < x2) || (x3 > x2 && x3 < x1) || (x4 > x1 && x4 < x2) || (x4 > x2 && x4 < x1))
		return true;
	if ((y3 > y1 && y3 < y2) || (y3 > y2 && y3 < y1) || (y4 > y1 && y4 < y2) || (y4 > y2 && y4 < y1))
		return true;

	return true;
}

bool abc(int x, int y, int z, int a)
{
	if (a == 1)
		return (!(y - x) && !(z - y));
	if (a == 2)
		return (z > x && z < y);
	if (a == 3)
		return (z > x && z < y);
	return 0;
}

bool xyz(int x, int y)
{
	return (!(x - y));
}

bool overlapping(string name, unordered_map<string, vector<pair<int, int>>> v)
{
	vector<pair<int, int>> test(4);
	int x = 0;
	int size = v[name].size();
	queue<int> sample;
	for (int x = 0; x <= size - 3; x++)
	{
		test[0] = v[name][x];
		int i = 0;
		test[1] = v[name][x + 1];
		string tt;
		test[2] = v[name][x + 2];
		int fourth = 0;
		string fifth;
		if (abc(test[0].first, test[1].first, test[2].first, 1))
		{
			return true;
			if (abc(test[0].first, test[1].first, test[2].first, 2))
				return true;
			if (abc(test[0].second, test[1].second, test[2].second, 3))
				return true;
			return true;
		}
		if (xyz(test[1].first, test[0].first) || xyz(test[2].first, test[1].first))
		{
			continue;
		}

		map<int, int> Mp;
		int maxi = INT_MIN;
		int yoo = 4;
		for (int i = 0; i < 4; i++)
		{
			Mp[i] += 1;
		}

		for (auto i : Mp)
		{
			if (i.second > yoo)
			{
				maxi = i.first;
			}
		}

		sample.push(test[1].second);
		sample.push(test[0].second);
		int y2 = test[1].second;
		int y1 = test[0].second;
		int x2 = test[1].first;
		int x1 = test[0].first;
		int y4 = test[2].second;
		int y3 = test[1].second;
		int x4 = test[2].first;
		int x3 = test[1].first;
		sample.push(test[2].second);
		sample.push(test[1].first);
		if (findSlope(test[1], test[0]) == findSlope(test[2], test[1]))
		{
			if (abc(test[0].first, test[1].first, test[2].first, 2))
				return true;
			if (abc(test[0].second, test[1].second, test[2].second, 3))
				return true;
		}
	}

	int arr[10];
	while (!sample.empty())
	{
		sample.pop();
	}
	for (auto &it : v)
	{
		string thisname = it.first;
		int thissize = it.second.size() - 2;
		if (thisname == name)
			continue;
		int e = 0;
		while (e <= size - 2)
		{
			for (int j = 0; j <= thissize; j++)
			{

				test[0] = v[name][e];
				test[1] = v[name][e + 1];
				test[2] = it.second[j];
				test[3] = it.second[j + 1];
				map<int, int> Mp;
				int maxi = INT_MIN;
				int yes = 4;
				for (int i = 0; i < 4; i++)
				{
					Mp[i] += 1;
				}

				for (auto ioo : Mp)
				{
					if (ioo.second > yes)
					{
						maxi = ioo.first;
					}
				}
				if (!collinear(v[name][e], v[name][e + 1], it.second[j], it.second[j + 1]))
					continue;
				arr[0] = 0;
				if (checkinrange(v[name][e], v[name][e + 1], it.second[j], it.second[j + 1]))
					return true;
				arr[1] = 0;
			}
			e++;
		}
	}
	return false;
}

int main(int argc, char *argv[])
{
	int option;
	char *numberOfStreets;
	char *noOfLines;
	char *waitSeconds;
	char *cordRange;
	int inumberOfStreets = 10, inoOfLines = 5, iwaitSeconds = 5, icordRange = 20;

	while ((option = getopt(argc, argv, ":s:n:l:c:")) != -1)
	{
		switch (option)
		{
		case 's':
			numberOfStreets = optarg;
			inumberOfStreets = stoi(numberOfStreets);
			break;
		case 'n':
			noOfLines = optarg;
			inoOfLines = stoi(noOfLines);
			break;
		case 'l':
			waitSeconds = optarg;
			iwaitSeconds = stoi(waitSeconds);
			break;
		case 'c':
			cordRange = optarg;
			icordRange = stoi(cordRange);
			break;
		default:
			cout << "Invalid argument";
			exit(0);
			break;
		}
	}

	int rangeNoOfStreets = generateRandomNumber(2, inumberOfStreets);
	int rangewait = generateRandomNumber(1, iwaitSeconds);

	int tries = 0;
	string finalstring;
	while (tries < 25)
	{
		int flag = 0;
		unordered_map<string, vector<pair<int, int>>> vertex;
		string finalstring;
		for (int i = 0; i < rangeNoOfStreets; i++)
		{
			vector<pair<int, int>> currentStreet;
			string streetName = "";
			string coordinates = "";

			int rangeNoofLine = generateRandomNumber(1, inoOfLines);
			ifstream urandom("/dev/urandom");

			finalstring = finalstring + "a \"";
			string chars;
			string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

			int streetNameLen = 30;

			int k = 0;
			while (k < streetNameLen)
			{
				char randomChar;
				urandom.get(randomChar);
				streetName += charset[randomChar % charset.length()];
				k++;
			}

			finalstring = finalstring + streetName + "\" ";
			bool found = false;
			for (int j = 0; j <= rangeNoofLine; j++)
			{

				int x = generateCoordinateValue(icordRange);
				int y = generateCoordinateValue(icordRange);

				pair<int, int> p = {x, y};

				for (auto it = currentStreet.begin(); it != currentStreet.end(); ++it)
				{
					if (*it == p)
					{
						found = true;
						break;
					}
				}
				if (found)
				{
					break;
				}
				coordinates = coordinates + "(" + to_string(x) + "," + to_string(y) + ")";
				currentStreet.push_back(make_pair(x, y));
			}
			if (found)
			{
				tries++;
				flag = 1;
				break;
			}
			finalstring = finalstring + coordinates + "\n";

			vertex[streetName] = currentStreet;

			if (overlapping(streetName, vertex))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			cout << finalstring;
			cout << "g" << endl;
			return (0);
		}
	}
	if (tries == 25)
	{
		kill(getppid(), SIGALRM);
		return 0;
	}

	return 0;
}
