#pragma once

#include<vector> 
using namespace std;

class CGame
{
	 const int CELL = 20;  //����ı߳�
	 const int ROWS = 25;  //���������
	 const int COLS = 15;//���������
							   //�����������ֵ
	 const int SCORE_LEVEL_INC = 80;
	//��ʱ��ID
	 const int ID_TIMER = 1;
	 const int INTERVAL_UNIT = 25;
	 const int INTERVAL_BASE = 300;
public:
	CGame(void);
	virtual ~CGame(void);

	//��ʼ����Ϸ
	bool Init(HWND hWnd);
	//�������
	void Paint(HDC hdc);

	void DoDownShift(void);    //����
	void DoLeftShift(void);    //����
	void DoRightShift();       //����
	void DoAccelerate();       //����
	void DoRedirection();      //�ı䷽��

	void SetPause(void);       //������ͣ
	void SetShowEdit(HWND hWnd);






protected:
	void DrawPanel(void);  //������Ϸ���
	void ClearRow();       //����
	bool CreateBlock();    //�������
	bool IsTouchBottom();
	void RefreshPanel(void);//ˢ�����

							//���ؽ���Ŀ��
	int GetUIWidth(void) const;
	//���ؽ���ĸ߶�
	int GetUIHeight(void) const;

	void SetTimer(UINT  nTimer)
	{
		m_nTimer = nTimer;
	}
	UINT GetTimer(void) const
	{
		return m_nTimer;
	}
	void SetHDC(HDC hDC)
	{
		m_hDC = hDC;
	}
	void Setwnd(HWND hWnd)
	{
		m_hWnd = hWnd;
	}
	int GetDownVal(void) const;
	void ShowScore(void);

private:
	HDC m_hDC;             //�����豸���
	HWND m_hWnd;
	HWND m_hWndEdit;       //��ʾ�����ͼ���
	UINT  m_nTimer;         //�����ʱ��ID
	int  m_nScore;         //����
	int m_nLevel;          //����

	int m_nCurLeft;        //������� ��¼���鵱ǰ��λ��
	int m_nCurTop;         //��������

	int m_nGoWidth;        //��������ķ���Ŀ���͸߶�
	int m_nGoHeight;
	bool m_bIsPause;       //��ͣ��ʶ

	vector< vector<BYTE> > m_vPanel;//ÿһ���״̬
	vector<BYTE> m_vBlock;//�󷽿飬����Ϊ�����С
};