#pragma once

#include <vector>

class DisjointSets 
{
public:
	DisjointSets(int N);
	void connect(int a, int b);
	void isConnected(int a, int b);

private:
	int size;
	std::vector<int> nodes;
	std::vector<int> weights;
	int find(int a);
};