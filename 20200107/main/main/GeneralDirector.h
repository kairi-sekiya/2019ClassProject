#pragma once
class GeneralDirector
{
public:
	static GeneralDirector* GetInstance();
	void Release();

private:
	GeneralDirector();
	GeneralDirector* instance();

public:



private:

};

