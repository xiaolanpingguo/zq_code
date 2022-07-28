#include "GameInput.h"
#include <windows.h>

CGameInput::CGameInput(HWND hWnd)
:
m_hWnd(hWnd)
{
	//µÃµ½´°¿ÚµÄ¿Í»§Çø
	GetClientRect(m_hWnd, &m_ClientRect);

	m_Key[_GI_M_L] = VK_LBUTTON; //Êó±ê×ó¼ü
	m_Key[_GI_M_M] = VK_MBUTTON; //Êó±êÖĞ¼ü
	m_Key[_GI_M_R] = VK_RBUTTON; //Êó±êÓÒ¼ü
	m_Key[_GI_K_A] = 'A'; //¼üÅÌ×ÖÄ¸¼üA
	m_Key[_GI_K_B] = 'B'; //¼üÅÌ×ÖÄ¸¼üB
	m_Key[_GI_K_C] = 'C'; //¼üÅÌ×ÖÄ¸¼üC
	m_Key[_GI_K_D] = 'D'; //¼üÅÌ×ÖÄ¸¼üD
	m_Key[_GI_K_E] = 'E'; //¼üÅÌ×ÖÄ¸¼üE
	m_Key[_GI_K_F] = 'F'; //¼üÅÌ×ÖÄ¸¼üF
	m_Key[_GI_K_G] = 'G'; //¼üÅÌ×ÖÄ¸¼üG
	m_Key[_GI_K_H] = 'H'; //¼üÅÌ×ÖÄ¸¼üH
	m_Key[_GI_K_I] = 'I'; //¼üÅÌ×ÖÄ¸¼üI
	m_Key[_GI_K_J] = 'J'; //¼üÅÌ×ÖÄ¸¼üJ
	m_Key[_GI_K_K] = 'K'; //¼üÅÌ×ÖÄ¸¼üK
	m_Key[_GI_K_L] = 'L'; //¼üÅÌ×ÖÄ¸¼üL
	m_Key[_GI_K_M] = 'M'; //¼üÅÌ×ÖÄ¸¼üM
	m_Key[_GI_K_N] = 'N'; //¼üÅÌ×ÖÄ¸¼üN
	m_Key[_GI_K_O] = 'O'; //¼üÅÌ×ÖÄ¸¼üO
	m_Key[_GI_K_P] = 'P'; //¼üÅÌ×ÖÄ¸¼üP
	m_Key[_GI_K_Q] = 'Q'; //¼üÅÌ×ÖÄ¸¼üQ
	m_Key[_GI_K_R] = 'R'; //¼üÅÌ×ÖÄ¸¼üR
	m_Key[_GI_K_S] = 'S'; //¼üÅÌ×ÖÄ¸¼üS
	m_Key[_GI_K_T] = 'T'; //¼üÅÌ×ÖÄ¸¼üT
	m_Key[_GI_K_U] = 'U'; //¼üÅÌ×ÖÄ¸¼üU
	m_Key[_GI_K_V] = 'V'; //¼üÅÌ×ÖÄ¸¼üV
	m_Key[_GI_K_W] = 'W'; //¼üÅÌ×ÖÄ¸¼üW
	m_Key[_GI_K_X] = 'X'; //¼üÅÌ×ÖÄ¸¼üX
	m_Key[_GI_K_Y] = 'Y'; //¼üÅÌ×ÖÄ¸¼üY
	m_Key[_GI_K_Z] = 'Z'; //¼üÅÌ×ÖÄ¸¼üZ
	m_Key[_GI_K_0] = 0x30; //¼üÅÌÊı×Ö¼ü0
	m_Key[_GI_K_1] = 0x31; //¼üÅÌÊı×Ö¼ü1
	m_Key[_GI_K_2] = 0x32; //¼üÅÌÊı×Ö¼ü2
	m_Key[_GI_K_3] = 0x33; //¼üÅÌÊı×Ö¼ü3
	m_Key[_GI_K_4] = 0x34; //¼üÅÌÊı×Ö¼ü4
	m_Key[_GI_K_5] = 0x35; //¼üÅÌÊı×Ö¼ü5
	m_Key[_GI_K_6] = 0x36; //¼üÅÌÊı×Ö¼ü6
	m_Key[_GI_K_7] = 0x37; //¼üÅÌÊı×Ö¼ü7
	m_Key[_GI_K_8] = 0x38; //¼üÅÌÊı×Ö¼ü8
	m_Key[_GI_K_9] = 0x39; //¼üÅÌÊı×Ö¼ü9
	m_Key[_GI_K_F01] = VK_F1; //¼üÅÌ¼üF1
	m_Key[_GI_K_F02] = VK_F2; //¼üÅÌ¼üF2
	m_Key[_GI_K_F03] = VK_F3; //¼üÅÌ¼üF3
	m_Key[_GI_K_F04] = VK_F4; //¼üÅÌ¼üF4
	m_Key[_GI_K_F05] = VK_F5; //¼üÅÌ¼üF5
	m_Key[_GI_K_F06] = VK_F6; //¼üÅÌ¼üF6
	m_Key[_GI_K_F07] = VK_F7; //¼üÅÌ¼üF7
	m_Key[_GI_K_F08] = VK_F8; //¼üÅÌ¼üF8
	m_Key[_GI_K_F09] = VK_F9; //¼üÅÌ¼üF9
	m_Key[_GI_K_F10] = VK_F10; //¼üÅÌ¼üF10
	m_Key[_GI_K_F11] = VK_F11; //¼üÅÌ¼üF11
	m_Key[_GI_K_F12] = VK_F12; //¼üÅÌ¼üF12
	m_Key[_GI_K_ESC] = VK_ESCAPE; //¼üÅÌ¼üEsc
	m_Key[_GI_K_OEM_3] = VK_OEM_3; //¼üÅÌ¼ü~
	m_Key[_GI_K_OEM_MINUS] = VK_OEM_MINUS; //¼üÅÌ¼ü_
	m_Key[_GI_K_OEM_PLUS] = VK_OEM_PLUS; //¼üÅÌ¼ü+
	m_Key[_GI_K_OEM_5] = VK_OEM_5; //¼üÅÌ¼ü|
	m_Key[_GI_K_BACK] = VK_BACK; //¼üÅÌ¼üBack Space
	m_Key[_GI_K_TAB] = VK_TAB; //¼üÅÌ¼üTab
	m_Key[_GI_K_OEM_4] = VK_OEM_4; //¼üÅÌ¼ü{
	m_Key[_GI_K_OEM_6] = VK_OEM_6; //¼üÅÌ¼ü}
	m_Key[_GI_K_RETURN] = VK_RETURN; //¼üÅÌ¼üEnter
	m_Key[_GI_K_CAPITAL_LOCK] = VK_CAPITAL; //¼üÅÌ¼üCaps Lock
	m_Key[_GI_K_OEM_1] = VK_OEM_1; //¼üÅÌ¼ü:
	m_Key[_GI_K_OEM_7] = VK_OEM_7; //¼üÅÌ¼ü"
	m_Key[_GI_K_L_SHIFT] = VK_LSHIFT; //¼üÅÌ¼ü×óShift
	m_Key[_GI_K_OEM_COMMA] = VK_OEM_COMMA; //¼üÅÌ¼ü<
	m_Key[_GI_K_OEM_PERIOD] = VK_OEM_PERIOD; //¼üÅÌ¼ü>
	m_Key[_GI_K_OEM_2] = VK_OEM_2; //¼üÅÌ¼ü?
	m_Key[_GI_K_R_SHIFT] = VK_RSHIFT; //¼üÅÌ¼üÓÒShift
	m_Key[_GI_K_L_CTRL] = VK_LCONTROL; //¼üÅÌ¼ü×óCtrl
	m_Key[_GI_K_L_ALT] = VK_LMENU; //¼üÅÌ¼ü×óAlt
	m_Key[_GI_K_SPACE] = VK_SPACE; //¼üÅÌ¼üSpacebar
	m_Key[_GI_K_R_ALT] = VK_RMENU; //¼üÅÌ¼üÓÒAlt
	m_Key[_GI_K_R_CTRL] = VK_RCONTROL; //¼üÅÌ¼üÓÒCtrl
	m_Key[_GI_K_PRINT_SCREEN] = VK_SNAPSHOT; //¼üÅÌ¼üPrint Screen
	m_Key[_GI_K_SCROLL_LOCK] = VK_SCROLL; //¼üÅÌ¼üScroll Lock
	m_Key[_GI_K_INSERT] = VK_INSERT; //¼üÅÌ¼üInsert
	m_Key[_GI_K_HOME] = VK_HOME; //¼üÅÌ¼üHome
	m_Key[_GI_K_PAGE_UP] = VK_PRIOR; //¼üÅÌ¼üPage Up
	m_Key[_GI_K_DELETE] = VK_DELETE; //¼üÅÌ¼üDelete
	m_Key[_GI_K_END] = VK_END; //¼üÅÌ¼üEnd
	m_Key[_GI_K_PAGE_DOWN] = VK_NEXT; //¼üÅÌ¼üPage Down
	m_Key[_GI_K_UP] = VK_UP; //¼üÅÌ¼ü¡ü
	m_Key[_GI_K_DOWN] = VK_DOWN; //¼üÅÌ¼ü¡ı
	m_Key[_GI_K_LEFT] = VK_LEFT; //¼üÅÌ¼ü¡û
	m_Key[_GI_K_RIGHT] = VK_RIGHT; //¼üÅÌ¼ü¡ú
	m_Key[_GI_NK_NUM_LOCK] = VK_NUMLOCK; //Ğ¡¼üÅÌ¼üNum Lock
	m_Key[_GI_NK_DIVIDE] = VK_DIVIDE; //Ğ¡¼üÅÌ¼ü³ı
	m_Key[_GI_NK_MULTIPLY] = VK_MULTIPLY; //Ğ¡¼üÅÌ¼ü³Ë
	m_Key[_GI_NK_ADD] = VK_ADD; //Ğ¡¼üÅÌ¼ü¼Ó
	m_Key[_GI_NK_SEPARATOR] = VK_SEPARATOR; //Ğ¡¼üÅÌ¼ü¼õ
	m_Key[_GI_NK_DECIMAL] = VK_DECIMAL; //Ğ¡¼üÅÌ¼üĞ¡Êıµã
	m_Key[_GI_NK_0] = VK_NUMPAD0; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü0
	m_Key[_GI_NK_1] = VK_NUMPAD1; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü1
	m_Key[_GI_NK_2] = VK_NUMPAD2; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü2
	m_Key[_GI_NK_3] = VK_NUMPAD3; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü3
	m_Key[_GI_NK_4] = VK_NUMPAD4; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü4
	m_Key[_GI_NK_5] = VK_NUMPAD5; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü5
	m_Key[_GI_NK_6] = VK_NUMPAD6; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü6
	m_Key[_GI_NK_7] = VK_NUMPAD7; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü7
	m_Key[_GI_NK_8] = VK_NUMPAD8; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü8
	m_Key[_GI_NK_9] = VK_NUMPAD9; //Ğ¡¼üÅÌ¼üÊı×Ö¼ü9

	//³õÊ¼»¯ËùÓĞ°´¼ü×´Ì¬Îª³ÖĞø·Å¿ª
	for (unsigned int i = 0; i < _GI_KEY_NUM; ++i)
		m_KeyState[i] = _KS_UH;
}

CGameInput::~CGameInput()
{}

void CGameInput::Run()
{
	for (unsigned int i = 0; i < _GI_KEY_NUM; ++i)
		m_KeyState[i] = (GetAsyncKeyState(m_Key[i]) & 0x8000) ? ((m_KeyState[i] < _KS_DH) ? _KS_DC : _KS_DH) : ((m_KeyState[i] > _KS_UC) ? _KS_UC : _KS_UH);
}

int CGameInput::Get(unsigned char Key)
{
	return (Key >= _GI_KEY_NUM) ? _KS_IK : m_KeyState[Key];
}

bool CGameInput::GetCursorPosition(int* X, int* Y)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
	*X = p.x;
	*Y = p.y;
	return TRUE == PtInRect(&m_ClientRect, p);
}