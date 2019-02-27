#include "JStudent.h"

void JStudent::Add_Link(Student* Link)
{
	m_pLast->pNext = new Student;
	Link->pPrev = new Student;

	m_pLast->pNext = Link;
	Link->pPrev = m_pLast;
	m_pLast = m_pLast->pNext;
}
void JStudent::ALL_Data_Del()
{
	while (m_pLast != m_pHead)
	{
		for (auto Temp = m_pHead;
			Temp != nullptr;
			Temp = Temp->pNext)
		{
			if (Temp->pNext == m_pLast)
			{
				m_pLast = Temp;
				delete(Temp->pNext);
				Temp->pNext = nullptr;
			}
		}
	}
	m_iNumber = 0;
}
void JStudent::Del_Data(Student *S_Del)
{
	Student *S_Temp = 0;
	for (auto Front_Stu = m_pHead;
		Front_Stu != nullptr;
		Front_Stu = Front_Stu->pNext)
	{
		if (Front_Stu->pNext == S_Del)
		{
			S_Temp = S_Del->pNext;
			delete(S_Del);
			S_Del = nullptr;
			Front_Stu->pNext = S_Temp;
			break;
		}
	}
}
void JStudent::New_Data()
{
	Student *NewStu = new Student;

	printf("새로운 데이터를 입력하시오\n");
	printf("\t이름 : ");
	scanf("%s", NewStu->Name);
	printf("\t국어 : ");
	scanf("%d", &NewStu->Kor);
	printf("\t수학 : ");
	scanf("%d", &NewStu->Mat);
	printf("\t영어 : ");
	scanf("%d", &NewStu->Eng);
	NewStu->iNum = m_iNumber;
	NewStu->Sum = NewStu->Kor + NewStu->Mat + NewStu->Eng;
	NewStu->Aver = NewStu->Sum / 3.0f;
	NewStu->pNext = nullptr;
	NewStu->pPrev = nullptr;
	m_iNumber += 1;

	Add_Link(NewStu);
	Data_Save();
}
void JStudent::Data_Load()
{
	ALL_Data_Del();
	FILE *File = fopen("Student_Data.txt", "r+");
	FILE* fData = fopen("Student_Data2.txt", "rb");
	while (!feof(fData))
	{
		Student *S_Temp = new Student;
		m_pLast->pNext = new Student;

		//fscanf(File, "%d%s%d%d%d%d%f\n",
		//	&S_Temp->iNum,
		//	S_Temp->Name,
		//	&S_Temp->Kor,
		//	&S_Temp->Mat,
		//	&S_Temp->Eng,
		//	&S_Temp->Sum,
		//	&S_Temp->Aver);
		//S_Temp->iNum = m_iNumber;
		//S_Temp->pNext = NULL;
		//m_pLast->pNext = S_Temp;
		//m_pLast = m_pLast->pNext;
		//m_iNumber++;

		fread(S_Temp, sizeof(Student), 1, fData);
		int i = 0;
	}
	fclose(fData);
	fclose(File);
}
void JStudent::Data_Save()
{
	FILE *File = fopen("Student_Data.txt", "w+");
	FILE* fData = fopen("Student_Data2.txt", "wb");
	for (Student *S_Temp = m_pHead->pNext;
		S_Temp != NULL;
		S_Temp = S_Temp->pNext)
	{
		fprintf(File, "%d\t %s\t %d\t %d\t %d\t %d\t %0.1f\n",
			S_Temp->iNum,
			S_Temp->Name,
			S_Temp->Kor,
			S_Temp->Mat,
			S_Temp->Eng,
			S_Temp->Sum,
			S_Temp->Aver);

		fwrite(S_Temp, sizeof(Student), 1, fData);
		int i = 0;
	}
	fclose(fData);
	fclose(File);
}
Student *JStudent::Find_Name()
{
	char NameFind[5] = { 0, };
	printf("찾고싶은 이름을 입력하시오 : ");
	scanf("%s", NameFind);

	for (Student *S_Temp = m_pHead->pNext;
		S_Temp != NULL;
		S_Temp = S_Temp->pNext)
	{
		if (strcmp(NameFind, S_Temp->Name) == 0)
		{
			printf("%d\t %s\t %d\t %d\t %d\t %d\t %0.1f\n",
				S_Temp->iNum,
				S_Temp->Name,
				S_Temp->Kor,
				S_Temp->Mat,
				S_Temp->Eng,
				S_Temp->Sum,
				S_Temp->Aver);
			return S_Temp;
		}
	}
	return NULL;
}
void JStudent::Find_Num()
{
	int FindNumber;
	printf("찾고싶은 번호를 입력하시오 : ");
	scanf("%d", &FindNumber);

	for (Student *S_Temp = m_pHead->pNext;
		S_Temp != NULL;
		S_Temp = S_Temp->pNext)
	{
		if (FindNumber == S_Temp->iNum)
		{
			printf("%d\t %s\t %d\t %d\t %d\t %d\t %0.1f\n",
				S_Temp->iNum,
				S_Temp->Name,
				S_Temp->Kor,
				S_Temp->Mat,
				S_Temp->Eng,
				S_Temp->Sum,
				S_Temp->Aver);
		}
	}
}
void JStudent::Data_Creat()
{
	ALL_Data_Del();

	printf("생성하고싶은 인원을 입력하시오 : ");
	scanf("%d", &m_iNumber);

	srand((unsigned)time(NULL));

	for (int Creat = 0; Creat < m_iNumber; Creat++)
	{
		Student *S_Temp = new Student;

		S_Temp->iNum = Creat;
		S_Temp->Name[0] = 65 + rand() % 26;
		S_Temp->Name[1] = 65 + rand() % 26;
		S_Temp->Name[2] = 65 + rand() % 26;
		S_Temp->Name[3] = '\0';
		S_Temp->Name[4] = '\0';
		S_Temp->Kor = rand() % 100;
		S_Temp->Mat = rand() % 100;
		S_Temp->Eng = rand() % 100;
		S_Temp->Sum = S_Temp->Kor +
			S_Temp->Mat +
			S_Temp->Eng;
		S_Temp->Aver = S_Temp->Sum / 3.0f;
		S_Temp->pNext = NULL;

		Add_Link(S_Temp);

		S_Temp = S_Temp->pNext;
	}
	Data_Print();
}
void JStudent::Data_Print()
{
	printf("======================================================\n");
	printf("====================학생정보시스템====================\n");
	printf("======================================================\n");
	printf("번호\t 이름\t 국어\t 수학\t 영어\t 총점\t 평균\t\n");

	for (Student *Link = m_pHead->pNext;
		Link != NULL;
		Link = Link->pNext)
	{
		printf("%d\t %s\t %d\t %d\t %d\t %d\t %0.1f\n",
			Link->iNum,
			Link->Name,
			Link->Kor,
			Link->Mat,
			Link->Eng,
			Link->Sum,
			Link->Aver);
	}
}

JStudent::JStudent()
{
	m_pHead = new Student;
	m_pLast = new Student;
	memset(m_pHead, 0, sizeof(Student));
	memset(m_pLast, 0, sizeof(Student));
	m_pLast = m_pHead;
}


JStudent::~JStudent()
{
	if (m_pHead)
	{
		delete(m_pHead);
		m_pHead = NULL;
	}
	if (m_pHead)
	{
		delete(m_pLast);
		m_pLast = NULL;
	}
}
