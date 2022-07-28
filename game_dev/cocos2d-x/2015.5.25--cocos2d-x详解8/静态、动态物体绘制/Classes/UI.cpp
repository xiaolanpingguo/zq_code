#include "UI.h"

//构造
CUI::CUI(const CCRect& r, bool v, bool a)
:
m_Rect(r),
m_Visible(v),
m_Active(a),
m_ID(-1),
m_Layer(0)
{}

//析构
CUI::~CUI()
{}

//虚函数
void CUI::Enter(){}
void CUI::Render(){}
void CUI::OnMessage(int e, int x, int y){}
void CUI::Exit(){}