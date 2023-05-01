#pragma once
#include <iostream>
#include <vector>
#include <map>
#include"Professor.h"
#include"Students_group.h"
#include"Week.h"

using namespace std;

class Schedule
{
private: vector<Professor> prof;
private: vector<Students_group> stud_groups;
public: map<string, Week> week;

public: Schedule(vector<Professor> prof, vector<Students_group> stud_groups)
{
	this->prof = prof;
	this->stud_groups = stud_groups;
}

public: void Genereterandom()
{
	for (int i = 0; i < stud_groups.size(); i++)
	{
		week[stud_groups[i].name] = Genereterandom_eachgroup(stud_groups[i]);
	}
}

private: Week Genereterandom_eachgroup(Students_group stud_group)
{
	srand(clock());
	Week res_week;
	for (auto lesson : stud_group.course)
	{
		for (int i = 0; i < lesson.second; i++)
		{
			Nameday curNameday = Nameday(rand() % 5);
			Lessons curLesson;
			curLesson.students_group = stud_group.name;
			curLesson.course = lesson.first;
			for (auto pr : prof)
			{
				for (auto course : pr.lessons)
				{
					if (course == lesson.first)
					{
						curLesson.professor = pr.name;
						break;
					}
				}
			}
			res_week.Days[curNameday].push_back(curLesson);
		}
	}
	return res_week;
}
};