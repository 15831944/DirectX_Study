#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

enum Choice_Num { NewData = 0, DelData, DataPrint, FindNum, FindName, DataSave, DataLoad, DataCreat, Exit = 99 };

struct Student {
	int iNum;
	char Name[5];
	int Kor;
	int Mat;
	int Eng;
	int Sum;
	float Aver;
	Student *pNext;
	Student *pPrev;
};
class JStudent
{
public:
	Student * m_pHead;
	Student *m_pLast;
	int m_iNumber;
public:
	void Data_Creat();
	void Data_Print();
	void Find_Num();
	Student *Find_Name();
	void Data_Save();
	void Data_Load();
	void New_Data();
	void Del_Data(Student *S_Del);
	void ALL_Data_Del();
	void Add_Link(Student* Link);
public:
	JStudent();
	virtual ~JStudent();
};
