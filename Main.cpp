#include<iostream>
#include "Professor.h"
#include "Students_group.h"
#include "Shedule.h"
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

void CrossingHelp(Week& fakeweek1, Week& fakeweek2, Week week1, Week week2,
	Students_group stud_group);

void Initialize(vector<Professor> &prof, 
	vector<Students_group> &stud_groups)
{
	prof.push_back({ "Sergii", {"C++", "Neyron"} });
	prof.push_back({ "Dmytro", {"C#", "Algoritms"}});

	Students_group TK41, TK42;
	TK41.name = "TK-41";
	TK41.course["C++"] = 3;
	TK41.course["Neyron"] = 2;
	TK41.course["C#"] = 1;
	TK41.course["Algoritms"] = 4;
	TK42.name = "TK-42";
	TK42.course["C++"] = 2;
	TK42.course["Neyron"] = 3;
	TK42.course["C#"] = 2;
	TK42.course["Algoritms"] = 3;
	stud_groups.push_back(TK41);
	stud_groups.push_back(TK42);
}

int Rating(Schedule schedule) {
	int rating = 100 * schedule.week.size();

	for (auto week : schedule.week)
	{
		for (int i = 0; i < 5; i++)
		{
			int sum = 1;
			for (auto lesson : week.second.Days[Nameday(i)])
			{
				sum = sum * 2;
			}
			rating += sum;
			if (week.second.Days[Nameday(i)].size() == 0)
			{
				rating -= 50;
			}
		}
	}

	return rating;
}

void PrintSchedule(Schedule schedule)
{
	for (auto week : schedule.week)
	{
		cout << week.first << endl;
		for (auto day : week.second.Days)
		{
			cout << "Day " << day.first << endl;
			for (auto lesson : day.second)
			{
				cout << lesson.course << " " << lesson.professor << endl;
			}
		}
	}
}

void Generate_num_of_Schedules(vector<Schedule> &shvector, 
	vector<Students_group> stud_groups,
	vector<Professor> prof, int count)
{
	for (int i = 0; i < count; i++) {
		Schedule sh(prof, stud_groups);
		sh.Genereterandom();
		shvector.push_back(sh);
	}
}

vector<Schedule> Crossing(Schedule shvector1, Schedule shvector2,
	vector<Students_group> stud_groups,
	vector<Professor> prof)
{
	Schedule newchild1(prof, stud_groups), newchild2(prof, stud_groups);
	for (auto week : shvector1.week)
	{
		Students_group curgroup;
		for (auto sg : stud_groups)
		{
			if (sg.name == week.first)
			{
				curgroup = sg;
				break;
			}
		}
		Week fakeweek1, fakeweek2;
		CrossingHelp(fakeweek1, fakeweek2, shvector1.week[curgroup.name], shvector2.week[curgroup.name], curgroup);
		newchild1.week[curgroup.name] = fakeweek1;
		newchild2.week[curgroup.name] = fakeweek2;
	}
	vector<Schedule> res;
	res.push_back(newchild1);
	res.push_back(newchild2);
	return res;
}

void CrossingHelp(Week &resweek1, Week &resweek2, Week week1, Week week2,
	Students_group stud_group)
{
	string curcourse;
	for (int i = 0; i < 2; i++)
	{
		Week fakeweek1, fakeweek2;
		int course_num = rand() % stud_group.course.size();
		int j = 0;
		for (auto c : stud_group.course)
		{
			if (j == course_num)
			{
				curcourse = c.first;
			}
			j++;
		}
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < max(week1.Days[Nameday(x)].size(), week2.Days[Nameday(x)].size()); y++)
			{
				if (y < week1.Days[Nameday(x)].size())
				{
					if (week1.Days[Nameday(x)][y].course != curcourse)
					{
						fakeweek1.Days[Nameday(x)].push_back(week1.Days[Nameday(x)][y]);
					}
					else
					{
						fakeweek2.Days[Nameday(x)].push_back(week1.Days[Nameday(x)][y]);
					}
				}
				if (y < week2.Days[Nameday(x)].size())
				{
					if (week2.Days[Nameday(x)][y].course != curcourse)
					{
						fakeweek2.Days[Nameday(x)].push_back(week2.Days[Nameday(x)][y]);
					}
					else
					{
						fakeweek1.Days[Nameday(x)].push_back(week2.Days[Nameday(x)][y]);
					}
				}
			}
		}
		resweek1 = fakeweek1;
		resweek2 = fakeweek2;
		week1 = fakeweek1;
		week2 = fakeweek2;
	}
}

vector<Schedule> Mutation(Schedule shvector1)
{
	for (auto resweek1 : shvector1.week)
	{
		for (int i = 0; i < shvector1.week.size(); i++)
		{
			int rand_day1 = rand() % 5;
			while (resweek1.second.Days[Nameday(rand_day1)].size() == 0)
				rand_day1 = rand() % 5;
			int rand_day2 = rand() % 5;
			while (resweek1.second.Days[Nameday(rand_day2)].size() == 0)
				rand_day2 = rand() % 5;
			int rand_less_num1 = rand() % resweek1.second.Days[Nameday(rand_day1)].size();
			int rand_less_num2 = rand() % resweek1.second.Days[Nameday(rand_day2)].size();
			Lessons rand_less1 = resweek1.second.Days[Nameday(rand_day1)][rand_less_num1];
			Lessons rand_less2 = resweek1.second.Days[Nameday(rand_day2)][rand_less_num2];
			resweek1.second.Days[Nameday(rand_day1)][rand_less_num1] = rand_less2;
			resweek1.second.Days[Nameday(rand_day2)][rand_less_num2] = rand_less2;
		}
		shvector1.week[resweek1.first] = resweek1.second;
	}
	vector<Schedule> result;
	result.push_back(shvector1);
	return result;
}

void NewGeneration(vector<Schedule> &Mainsheduls,
	vector<Students_group> stud_groups,
	vector<Professor> prof)
{
	vector<Schedule> newSheduls;
	int cursize = Mainsheduls.size();
	for (int i = 0; i < cursize; i += 2)
	{

		if (rand() % 100 < 20)
		{
			newSheduls = Mutation(Mainsheduls[i]);
			Mainsheduls.push_back(newSheduls[0]);
		}
		newSheduls = Crossing(Mainsheduls[i], Mainsheduls[i + 1], stud_groups, prof);
		Mainsheduls.push_back(newSheduls[0]);
		Mainsheduls.push_back(newSheduls[1]);
	}
}

void Segregate(vector<Schedule>& Mainsheduls, int num)
{
	while (Mainsheduls.size() != num)
	{
		int max_i = 0;
		int max_rating = 0;
		for (int i = 0; i < Mainsheduls.size(); i++)
		{
			if (Rating(Mainsheduls[i]) > max_rating)
			{
				max_i = i;
				max_rating = Rating(Mainsheduls[i]);
			}
		}
		Mainsheduls[max_i] = Mainsheduls[Mainsheduls.size() - 1];
		Mainsheduls.pop_back();
	}
}

int main()
{
	vector<Professor> prof;
	vector<Students_group> stud_groups;
	Initialize(prof, stud_groups);
	/*Schedule Mainsheduls(prof, stud_groups);
	Mainsheduls.Genereterandom();
	PrintSchedule(Mainsheduls);*/
	//cout << endl << Rating(Mainsheduls) << endl;
	vector<Schedule> Mainsheduls;
	Generate_num_of_Schedules(Mainsheduls, stud_groups, prof, 10);
	for (int j = 0; j < 10; j++)
	{
		NewGeneration(Mainsheduls, stud_groups, prof);
		Segregate(Mainsheduls, 10);
		for (int i = 0; i < Mainsheduls.size(); i++)
		{
			//PrintSchedule(Mainsheduls[i]);
			cout << Rating(Mainsheduls[i]) << " ";
			/*if (i == 4)
				cout << endl;*/
		}
		cout << endl;
	}
	system("pause");
}