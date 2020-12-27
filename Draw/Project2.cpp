// 4글자 영단어 끝말잇기를 하는 코드입니다.
// 김성엽이라는 분이 간단하게 gui로 c언어를 다뤄볼수 있도록 만들어둔 EesyWin32를 사용해서 만들었습니다. 
// EasyWin32 카페주소  https://cafe.naver.com/easywin32
//

#include "pch.h"
#include <stdio.h> 
#include <stdlib.h> 
#include "tipsware.h"
#include <time.h>
#include <string.h>


typedef struct VOCA_STORE {
	char voca[15];
	struct VOCA_STORE* next;
}VOCA_STORE;

void* p;
int case_num;
char spell;
VOCA_STORE* start;
VOCA_STORE* last;

void function_1();
void function_2();
void function_3();
void function_4(int reason);

void  Drawagainbutton()
{
	Rectangle(600, 510, 725, 545, RGB(100, 150, 255), RGB(150, 255, 255));
	SelectFontObject("굴림", 30, 1);
	TextOut(600, 512, RGB(255, 30, 30), "다시하기");
}

void DrawaddButton()
{
	Rectangle(160, 510, 210, 540, RGB(100, 150, 255));
	SelectFontObject("굴림", 30, 1);
	TextOut(175, 512, RGB(100, 255, 150), "+");
}

void LeftButtonDown(int a_mixed_key, POINT a_pos)
{
	if ((case_num == 0) && (a_pos.x >= 160) && (a_pos.x <= 210) && (a_pos.y >= 510) && (a_pos.y <= 540))                   //data add버튼
	{
		function_2();

	}
	if ((case_num == 1) && (a_pos.x >= 600) && (a_pos.x <= 725) && (a_pos.y >= 510) && (a_pos.y <= 545))                    //리셋버튼
	{
		function_1();
	}
}


MOUSE_MESSAGE(LeftButtonDown, NULL, NULL)


int extract(char* s)                                               // 마지막 스펠링을 뽑아서 그 스펠링의 아스키코드를 int형으로 반환                                
{
	int last;
	last = (int)s[strlen(s) - 1];
	return last;
}

char* readfile(int s)                                                     // 전달된 스펠링으로 시작하는 단어를 랜덤으로 뽑아서 (char*) 문자열의 포인터로 반환
{
	int count = 0;
	char file_ad[26][17];
	strcpy(file_ad[0], "C:\\voca\\a.txt");
	strcpy(file_ad[1], "C:\\voca\\b.txt");
	strcpy(file_ad[2], "C:\\voca\\c.txt");
	strcpy(file_ad[3], "C:\\voca\\d.txt");
	strcpy(file_ad[4], "C:\\voca\\e.txt");
	strcpy(file_ad[5], "C:\\voca\\f.txt");
	strcpy(file_ad[6], "C:\\voca\\g.txt");
	strcpy(file_ad[7], "C:\\voca\\h.txt");
	strcpy(file_ad[8], "C:\\voca\\i.txt");
	strcpy(file_ad[9], "C:\\voca\\j.txt");
	strcpy(file_ad[10], "C:\\voca\\k.txt");
	strcpy(file_ad[11], "C:\\voca\\l.txt");
	strcpy(file_ad[12], "C:\\voca\\m.txt");
	strcpy(file_ad[13], "C:\\voca\\n.txt");
	strcpy(file_ad[14], "C:\\voca\\o.txt");
	strcpy(file_ad[15], "C:\\voca\\p.txt");
	strcpy(file_ad[16], "C:\\voca\\q.txt");
	strcpy(file_ad[17], "C:\\voca\\r.txt");
	strcpy(file_ad[18], "C:\\voca\\s.txt");
	strcpy(file_ad[19], "C:\\voca\\t.txt");
	strcpy(file_ad[20], "C:\\voca\\u.txt");
	strcpy(file_ad[21], "C:\\voca\\v.txt");
	strcpy(file_ad[22], "C:\\voca\\w.txt");
	strcpy(file_ad[23], "C:\\voca\\x.txt");
	strcpy(file_ad[24], "C:\\voca\\y.txt");
	strcpy(file_ad[25], "C:\\voca\\z.txt");


	int num_of_voca[26] = {119,184,172,152,66,129,133,120,43,54,40,157,134,60,61,177,7,134,249,163,15,43,120,4,36,18};                                                             ////////////////////////////////////////////////////////////////////////////////
	char* voca;
	voca = (char*)malloc(sizeof(char) * 15);

	FILE* fp = NULL;
	fp = fopen(file_ad[s - 97], "r");
	if (fp != NULL)
	{
		int num;
		srand(time(NULL));
		num = rand();
		num = (num % num_of_voca[s-97])+1;                                                       


		while (count != num)
		{
			fscanf(fp, "%s", voca);
			count = count + 1;


		}
	}

	fclose(fp);

	return voca;
}

int check_right(char* s, int a)															// 존재하는단어인지 체크 존재하면 0
{

	char file_ad[26][17];
	strcpy(file_ad[0], "C:\\voca\\a.txt");
	strcpy(file_ad[1], "C:\\voca\\b.txt");
	strcpy(file_ad[2], "C:\\voca\\c.txt");
	strcpy(file_ad[3], "C:\\voca\\d.txt");
	strcpy(file_ad[4], "C:\\voca\\e.txt");
	strcpy(file_ad[5], "C:\\voca\\f.txt");
	strcpy(file_ad[6], "C:\\voca\\g.txt");
	strcpy(file_ad[7], "C:\\voca\\h.txt");
	strcpy(file_ad[8], "C:\\voca\\i.txt");
	strcpy(file_ad[9], "C:\\voca\\j.txt");
	strcpy(file_ad[10], "C:\\voca\\k.txt");
	strcpy(file_ad[11], "C:\\voca\\l.txt");
	strcpy(file_ad[12], "C:\\voca\\m.txt");
	strcpy(file_ad[13], "C:\\voca\\n.txt");
	strcpy(file_ad[14], "C:\\voca\\o.txt");
	strcpy(file_ad[15], "C:\\voca\\p.txt");
	strcpy(file_ad[16], "C:\\voca\\q.txt");
	strcpy(file_ad[17], "C:\\voca\\r.txt");
	strcpy(file_ad[18], "C:\\voca\\s.txt");
	strcpy(file_ad[19], "C:\\voca\\t.txt");
	strcpy(file_ad[20], "C:\\voca\\u.txt");
	strcpy(file_ad[21], "C:\\voca\\v.txt");
	strcpy(file_ad[22], "C:\\voca\\w.txt");
	strcpy(file_ad[23], "C:\\voca\\x.txt");
	strcpy(file_ad[24], "C:\\voca\\y.txt");
	strcpy(file_ad[25], "C:\\voca\\z.txt");
	FILE* fp = NULL;
	fp = fopen(file_ad[a - 97], "r");


	int count = 0;
	int k;
	int state=1;
	char text[15];

	int end;

	if (fp != NULL)
	{

		while (1)
		{
			end = fscanf(fp, "%s", text);
			state = strcmp(s, text);
			if (state == 0)
			{
				break;
			}
			if (end == EOF)
			{
				break;
			}
		}
	}
	fclose(fp);
	return state;
}

void store_data(char* s)
{
	VOCA_STORE* new_1 = (VOCA_STORE*)malloc(sizeof(VOCA_STORE));
	(*last).next = new_1;
	(*new_1).next = NULL;
	strcpy((*new_1).voca, s);
	last = new_1;
}

int clear_data(int count)
{
	VOCA_STORE* temp;
	temp = (*start).next;
	free(start);
	start = temp;
	if (start != NULL)
	{
		count = clear_data((count + 1));
	}
	return count;
}

int check_twice(char* s)																	// 중복단어인지 체크 중복이면 0
{
	VOCA_STORE* temp;
	int state=1;
	temp = start;
	while (temp != NULL)
	{
		state = strcmp((*temp).voca, s);
		if (state == 0)																		//중복단어
		{
			break;
		}
		else
		{
			temp = (*temp).next;
		}
	}
	return state;
}





void function_4(int reason)
{
	int count;
	count = clear_data(1);
	if (reason == 1)
	{
		Clear();
		Drawagainbutton();
		SelectFontObject("굴림", 45, 1);
		TextOut(285, 220, RGB(255, 150, 150), "알파벳 첫글자 틀림");
		SelectFontObject("굴림", 30, 5);
		TextOut(430, 310, RGB(255, 150, 150), "개수:%d개", count / 2);
	}

	else if (reason == 2)
	{
		Clear();
		Drawagainbutton();
		SelectFontObject("굴림", 45, 1);
		TextOut(410, 220, RGB(255, 150, 150), "중복단어");
		SelectFontObject("굴림", 30, 5);
		TextOut(430, 310, RGB(255, 150, 150), "개수:%d개", count / 2);
	}

	else if (reason == 3)
	{
		Clear();
		Drawagainbutton();
		SelectFontObject("굴림", 45, 1);
		TextOut(250, 220, RGB(255, 150, 150), "없는단어 단어추가요망");
		SelectFontObject("굴림", 30, 5);
		TextOut(430, 310, RGB(255, 150, 150), "개수:%d개", count / 2);
	}
	else
	{
		Clear();
		Drawagainbutton();
		SelectFontObject("굴림", 45, 1);
		TextOut(250, 220, RGB(150, 150, 255), "YOU WIN");
		SelectFontObject("굴림", 30, 5);
		TextOut(430, 310, RGB(255, 150, 150), "개수:%d개", count / 2);
	}
	ShowDisplay();

}

void function_3()
{
	char random_s[15];
	int count = 0;
	int num_of_voca[26] = { 119,184.172,152,66,129,133,120,43,54,40,157,134,60,61,177,7,134,249,163,15,43,120,4,36,18 };
	strcpy(random_s, readfile((int)spell));
	ListBox_InsertString(FindControl(1001), -1, random_s, 1);
	while (check_twice(random_s) == 0)
	{
		strcpy(random_s, readfile((int)spell));                      //랜덤단어 만들기
		count = count + 1;
		if (count > (num_of_voca[spell - 97]))
		{
			function_4(4);
		}
	}
	store_data(random_s);
	spell = random_s[strlen(random_s) - 1];
	Clear();
	DrawaddButton();
	SelectFontObject("굴림", 45, 3);
	TextOut(350, 220, RGB(100, 255, 150), random_s);
	ShowDisplay();
}

void function_2()
{
	char* str = {};
	char str_receive[15] = {};
	FILE* fp;
	fp = fopen("C:\Study2019\Win32\changetocpp\Project3\output.txt","r");
	if (fp != NULL)
	{
		fscanf(fp, "%s", str);
		strcpy(str_receive, (str + strlen(str) - 4));
		fclose(fp);
	}
	
	//GetCtrlName(FindControl(1000), str_receive, 5);                                                                              //텍스트창
	//store_data(str_receive);
	ListBox_InsertString(FindControl(1001), -1, str_receive, 1);
	if (spell != str_receive[0])																								//첫글자확인
	{
		case_num = 1;
		function_4(1);
	}
	else if (0 == check_twice(str_receive))																								//중복확인
	{
		case_num = 1;
		function_4(2);
	}
	else if (0 != check_right(str_receive, (int)str_receive[0]))																				//있는지 확인
	{
		case_num = 1;
		function_4(3);
	}
	else
	{
		store_data(str_receive);
		spell = str_receive[strlen(str_receive) - 1];
		function_3();
	}
}

void function_1()                                   ///완전 새게임 시작
{
	case_num = 0;
	ListBox_ResetContent(p);
	Clear();
	DrawaddButton();
	int a;
	srand(time(NULL));
	a = (rand() % 26) + 97;
	char random_s[15];
	strcpy(random_s, readfile(a));
	ListBox_InsertString(FindControl(1001), -1, random_s, 1);
	VOCA_STORE* new_one = (VOCA_STORE*)malloc(sizeof(VOCA_STORE));
	(*new_one).next = NULL;
	strcpy((*new_one).voca, random_s);
	start = new_one;
	last = new_one;
	spell = random_s[strlen(random_s) - 1];
	SelectFontObject("굴림", 45, 3);
	TextOut(350, 220, RGB(100, 255, 150), random_s);
	ShowDisplay();
}


int main()
{
	p = CreateListBox(10, 10, 200, 500, 1001);                                                   
	//CreateEdit(10, 510, 150, 30, 1000, 0);                                                                           //텍스트창
	start = NULL;
	last = NULL;
	spell = ' ';
	function_1();
	return 0;
}



