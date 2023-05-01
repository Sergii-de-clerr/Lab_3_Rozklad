#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"Lesson.h"

using namespace std;

enum Nameday {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
};

class Week
{
public:	map<Nameday, vector<Lessons>> Days;
};