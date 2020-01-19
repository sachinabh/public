/*
 *  For AstroMediComp.org
 *  Assignment # 06 by Sachin Bhosale
 *  Pledge
 */

#include<windows.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
  WNDCLASSEX wndclass;
  TCHAR szAppName[] = TEXT("Pledge");

  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.cbSize = sizeof(WNDCLASSEX);
  wndclass.style = CS_VREDRAW | CS_HREDRAW;
  wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wndclass.hInstance = hInstance;
  wndclass.lpfnWndProc = WndProc;
  wndclass.lpszClassName = szAppName;
  wndclass.lpszMenuName = NULL;

  RegisterClassEx(&wndclass);

  HWND hwnd;
  hwnd = CreateWindow(szAppName
    , TEXT("Pledge")
    , WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL
    , 30
    , 40
    , 300
    , 400
    , NULL
    , NULL
    , hInstance
    , NULL);

  ShowWindow(hwnd, iCmdShow);
  UpdateWindow(hwnd);

  MSG msg;

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int(msg.wParam));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
  TEXTMETRIC tm;
  static int iVertPos, iHorzPos;
  static int cxChar, cyChar;
  static int cxClient, cyClient;
  int x, y, i;
  static int NbLines = 0, NbChars = 0;
  TCHAR szPledge[20][60];
  COLORREF color[4];
  color[0] = RGB(155, 0, 255);
  color[1] = RGB(255, 155, 0);
  color[2] = RGB(255, 255, 255);
  color[3] = RGB(0, 155, 0);
  switch (iMsg)
  {
  case WM_SIZE:
    cxClient = LOWORD(lParam);
    cyClient = HIWORD(lParam);
    if (cyClient <= cyChar*NbLines)
    {
      SetScrollRange(hwnd, SB_VERT, 0, 2*NbLines*cyChar, TRUE);
      SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);
    //  ShowScrollBar(hwnd, SB_VERT, 1);
    //}
    //else
    //{
    //  ShowScrollBar(hwnd, SB_VERT, 0);
    }
    if (cxClient <= cxChar*NbChars)
    {
      SetScrollRange(hwnd, SB_HORZ, 0, 2*NbChars*cxChar, TRUE);
      SetScrollPos(hwnd, SB_HORZ, iHorzPos, TRUE);
    //  ShowScrollBar(hwnd, SB_HORZ, 1);
    //}
    //else
    //{
    //  ShowScrollBar(hwnd, SB_HORZ, 0);
    }
    break;
  case WM_CREATE:
    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight + tm.tmExternalLeading;
    ReleaseDC(hwnd, hdc);
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    SetBkColor(hdc, RGB(0, 0, 0));
    i = 0;
    wsprintf(szPledge[i], TEXT("Pledge$"));
    wsprintf(szPledge[i], TEXT("- - - - - - - -$"));
    wsprintf(szPledge[i], TEXT("India is my country.$"));
    wsprintf(szPledge[i], TEXT("All Indians are my Brothers and Sisters. $"));
    wsprintf(szPledge[i], TEXT("I love my country $"));
    wsprintf(szPledge[i], TEXT("and I am proud of $"));
    wsprintf(szPledge[i], TEXT("its rich and varied heritage. $"));
    wsprintf(szPledge[i], TEXT("I shall always strive $"));
    wsprintf(szPledge[i], TEXT("to be worthy of it. $"));
    wsprintf(szPledge[i], TEXT("I shall give my parents, teachers and all elders respect$"));
    wsprintf(szPledge[i], TEXT("and treat everyone with courtesy. $"));
    wsprintf(szPledge[i], TEXT("To my country and my people, I pledge my devotion. $"));
    wsprintf(szPledge[i], TEXT("In their well being and prosperity alone, $"));
    wsprintf(szPledge[i], TEXT("lies my happiness. $"));
    NbLines = i;
    for (i = 0; i <= NbLines; i++)
    {
      x = cxChar * (0 - iHorzPos);
      y = cyChar * (i - iVertPos);
      if (i < 2)
        SetTextColor(hdc, color[0]);
      else if (i < 6)
        SetTextColor(hdc, color[1]);
      else if (i < 10)
        SetTextColor(hdc, color[2]);
      else if (i < 14)
        SetTextColor(hdc, color[3]);
      NbChars = NbChars < lstrlen(szPledge[i]) ? lstrlen(szPledge[i]) : NbChars;
      TextOut(hdc, x, y, szPledge[i], lstrlen(szPledge[i]));
    }
    EndPaint(hwnd, &ps);
    break;
  case WM_VSCROLL:
    switch (LOWORD(wParam))
    {
    case SB_LINEUP:
      iVertPos -= 1;
      break;
    case SB_LINEDOWN:
      iVertPos += 1;
      break;
    case SB_PAGEUP:
      iVertPos -= cyClient / cyChar;
      break;
    case SB_PAGEDOWN:
      iVertPos += cyClient / cyChar;
      break;
    case SB_THUMBPOSITION:
      iVertPos = HIWORD(wParam);
      break;
    }
    iVertPos = max(0, min(iVertPos, NbLines - 1));
    if (iVertPos != GetScrollPos(hwnd, SB_VERT))
    {
      SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);
      InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
  case WM_HSCROLL:
    switch (LOWORD(wParam))
    {
    case SB_LINEUP:
      iHorzPos -= 1;
      break;
    case SB_LINEDOWN:
      iHorzPos += 1;
      break;
    case SB_PAGEUP:
      iHorzPos -= cxClient / cxChar;
      break;
    case SB_PAGEDOWN:
      iHorzPos += cxClient / cxChar;
      break;
    case SB_THUMBPOSITION:
      iHorzPos = HIWORD(wParam);
      break;
    }
    iHorzPos = max(0, min(iHorzPos, NbChars - 1));
    if (iHorzPos != GetScrollPos(hwnd, SB_HORZ))
    {
      SetScrollPos(hwnd, SB_HORZ, iHorzPos, TRUE);
      InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
  case WM_KEYDOWN:
    switch (LOWORD(wParam))
    {
    case VK_ESCAPE:
      PostQuitMessage(0);
      break;
    case VK_DOWN:
      iVertPos += 1;
      break;
    case VK_UP:
      iVertPos -= 1;
      break;
    case VK_LEFT:
      iHorzPos += 1;
      break;
    case VK_RIGHT:
      iHorzPos -= 1;
      break;
    }
    iHorzPos = max(0, min(iHorzPos, NbChars - 1));
    if (iHorzPos != GetScrollPos(hwnd, SB_HORZ))
    {
      SetScrollPos(hwnd, SB_HORZ, iHorzPos, TRUE);
      InvalidateRect(hwnd, NULL, TRUE);
    }
    iVertPos = max(0, min(iVertPos, NbLines - 1));
    if (iVertPos != GetScrollPos(hwnd, SB_VERT))
    {
      SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);
      InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }
  return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
