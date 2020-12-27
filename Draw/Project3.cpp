// 알파벳을 그리고 캡쳐하는 프로그램을 만드는 코드입니다.
// 김성엽이라는 분이 간단하게 gui로 c언어를 다뤄볼수 있도록 만들어둔 EesyWin32과 그 예제를 사용및 변형해서 만들었습니다. 
// EasyWin32 카페주소  https://cafe.naver.com/easywin32
//


#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include "pch.h"
#include "tipsware.h"
#include "Python.h"

struct AppData
{
    char is_clicked; 
    char line_tick;    
};


void DrawMenu(AppData* ap_data)
{
    Rectangle(5, 5, 100, 28, RGB(0, 0, 255), RGB(0, 0, 200));
    TextOut(10, 8, RGB(0, 200, 255), "다시 그리기");

    Rectangle(250, 5, 345, 28, RGB(0, 0, 255), RGB(0, 0, 200));
    TextOut(280, 8, RGB(0, 200, 255), "저장");
   
    Rectangle(149, 50, 199, 100, RGB(255, 200, 200), RGB(255, 255, 255));
}
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
    AppData* p = (AppData*)GetAppData();

    
    if (a_pos.x >= 5 && a_pos.y >= 5 && a_pos.x <= 100 && a_pos.y <= 28) {
        Clear(); 
        DrawMenu(p); 
        ShowDisplay(); 
    }
    else if (a_pos.x >= 250 && a_pos.y >= 5 && a_pos.x <= 345 && a_pos.y <= 28) {
        void* p_image = CaptureScreenGP(261,166,320,225);
        SaveImageGP(p_image, "screen.jpeg");
        Clear(); 
        DrawMenu(p);
        ShowDisplay();
        char filename[] = "pred.py";                                                                                          
        FILE* fp;
        Py_Initialize();
        fp = _Py_fopen(filename, "r");
        PyRun_SimpleFile(fp, filename);
        Py_Finalize();
    }

    else {
        MoveTo(a_pos.x, a_pos.y);
        SelectPenObject(RGB(0, 0, 0), p->line_tick);
        p->is_clicked = 1;
    }
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
    AppData* p = (AppData*)GetAppData();
    if (p->is_clicked == 1) {
        LineTo(a_pos.x, a_pos.y);
        ShowDisplay(); 
    }
}

void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
    AppData* p = (AppData*)GetAppData();
    if (p->is_clicked == 1) {
        LineTo(a_pos.x, a_pos.y);
        p->is_clicked = 0;
        ShowDisplay();
    }
}

MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)

int main()
{
    ChangeWorkSize(350, 130); 
    int wnd_style = ::GetWindowLong(gh_main_wnd, GWL_STYLE);
    ::SetWindowLong(gh_main_wnd, GWL_STYLE, wnd_style & ~WS_THICKFRAME);

    AppData data = { 0, 5 };
    SetAppData(&data, sizeof(AppData));

    DrawMenu(&data);
    ShowDisplay();
    return 0;
}
//[출처] 마우스로 그림 그리기 - Step 5 (EasyWin32) | 작성자 김성엽