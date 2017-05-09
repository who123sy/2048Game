#include "stdafx.h"
#include "StringContainer.h"


StringContainer::StringContainer(int msgId, int* value, CPoint* position)
{
	CString* str = new CString();
	str->LoadString(msgId);

	this->descriptionText = str;
	this->value = value;
	this->position = position;

	descriptionTextFont.CreatePointFont(200, L"Times New Roman");
	valueTextFont.CreatePointFont(300, L"Times New Roman");

	margin = 10;
}


StringContainer::~StringContainer()
{
	delete descriptionText;
	delete position;
}

int StringContainer::GetWidth()
{
	/*LOGFONT lf1, lf2;
	valueTextFont.GetLogFont(&lf1);
	descriptionTextFont.GetLogFont(&lf2);

	return  max(
		2 * margin + lf1.lfWidth * valueText->GetLength(), 
		2 * margin + lf2.lfWidth * descriptionText->GetLength());*/
	return 0;
}

int StringContainer::GetHeight()
{
	LOGFONT lf1, lf2;
	valueTextFont.GetLogFont(&lf1);
	descriptionTextFont.GetLogFont(&lf2);

	return margin * 2 + abs(lf1.lfHeight) + abs(lf2.lfHeight);
}

void StringContainer::OnDraw(CDC * pDC)
{
	CBrush brushBlue(RGB(188, 172, 157));
	LOGFONT descriptionFont;
	descriptionTextFont.GetLogFont(&descriptionFont);
	CPen grayPen;
	grayPen.CreatePen(PS_SOLID, 0, RGB(188, 172, 157));

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	CFont* oldFont = pDC->SelectObject(&descriptionTextFont);
	CBrush* oldBrush = pDC->SelectObject(&brushBlue);
	CPen* oldPen = pDC->SelectObject(&grayPen);

	//value
	CString valueText;
	valueText.Format(L"%d", *value);
	pDC->SelectObject(&valueTextFont);

	CSize valueSize = pDC->GetTextExtent((valueText.GetLength() < 3) ? CString(L"123") : valueText);

	// rect
	CRect rect(
		position->x, position->y, 
		position->x + valueSize.cx + 2 * margin, GetHeight());
	pDC->RoundRect(rect, CPoint(17, 17));

	valueSize = pDC->GetTextExtent(valueText);
	pDC->TextOutW(position->x + (rect.Width() - valueSize.cx) / 2, position->y + abs(descriptionFont.lfHeight) + margin, valueText);

	//description
	pDC->SelectObject(&descriptionTextFont);
	CSize descriptionSize = pDC->GetTextExtent(*descriptionText);
	pDC->TextOutW(position->x + (rect.Width() - descriptionSize.cx) / 2, position->y + margin, *descriptionText);

	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldFont);
}
