#include <map>
#include <iostream>
#include <stdio.h>
using namespace std;



int goldRabbits(int n)
{
	static map<int, int> fiboMap;
	fiboMap.insert(pair <int, int> (0, 0));
	fiboMap.insert(pair <int, int> (1, 1));

	map<int, int>::iterator it;
	it = fiboMap.find(n);
	if (it == fiboMap.end())
	{
		fiboMap.insert(pair <int, int> (n, (fiboMap[n - 1] + fiboMap[n - 2])));
		it = fiboMap.find(n);
	}
	return it->second;
}

int main()
{

	for(int i = 0; i < 15; i++)
	{
		cout << (i < 950 ? "\n" : "\n\n") << "The GoldRabbit of (" << i << ") is " << goldRabbits(i);
	}
	return 0;
}