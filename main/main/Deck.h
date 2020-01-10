#pragma once
#include"include.h"

class Deck
{
public:
	Deck();
	~Deck();

	virtual void SetAllCards() = 0;
private:
	Card* deck;
	int iterator;

	void ReadImageFromFile(const char* filename);

};

