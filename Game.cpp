#include "StdAfx.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include<vector>
#include<time.h>

using namespace std;
CGame::CGame(void) :m_hDC(NULL), m_nScore(0), m_nLevel(0), m_bIsPause(false),
m_vPanel(ROWS, vector<BYTE>(COLS, 0))
{
}

CGame::~CGame(void)
{
	if (m_nTimer)
	{
		KillTimer(m_hWnd, ID_TIMER);
		m_nTimer = 0;
	}
}

//���ؽ���Ŀ��
int CGame::GetUIWidth(void) const
{
	return CELL*COLS + 8 * 40;
}

//���ؽ���ĸ߶�
int CGame::GetUIHeight(void) const
{
	return CELL*ROWS + 32 * 2;
}

bool CGame::Init(HWND hWnd)
{
	Setwnd(hWnd);
	::MoveWindow(m_hWnd, 400, 10, GetUIWidth(), GetUIHeight(), FALSE);

	srand((unsigned int)time(NULL));//Ϊrand�����ṩ��ͬ������ֵ

	CreateBlock();
	m_nTimer = ::SetTimer(m_hWnd, ID_TIMER, GetDownVal(), NULL);

	ShowScore();
	return true;
}

void CGame::Paint(HDC hdc)//�������
{
	SetHDC(hdc);
	DrawPanel();
	RefreshPanel();
}

void CGame::DrawPanel(void)//������Ϸ���
{
	RECT rcRect;

	for (int y = 0; y<ROWS; y++)
	{
		for (int x = 0; x<COLS; x++)
		{
			//���㷽��ı߿�Χ
			rcRect.top = y*CELL + 1;
			rcRect.left = x*CELL + 1;
			rcRect.right = (x + 1)*CELL - 1;
			rcRect.bottom = (y + 1)*CELL - 1;
			::FrameRect(m_hDC, &rcRect, (HBRUSH)GetStockObject(GRAY_BRUSH));//GRAY_BRUSH�ǻ�ɫ
		}
	}
}

void CGame::RefreshPanel(void)   //ˢ�����
{
	RECT rect;
	if (m_vBlock.size() <= 0)
	{
		return;
	}

	HBRUSH h_bSolid = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH h_bEmpty = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//��ˢ�������͹̶��ķ���
	for (int y = 0; y<(int)m_vPanel.size(); y++)
	{
		for (int x = 0; x<(int)m_vPanel[0].size(); x++)
		{
			//Ϊ����ˢ������ı߿�rect��Χ����ȱ߿�ΧС1
			rect.top = y*CELL + 2;
			rect.bottom = (y + 1)*CELL - 2;
			rect.left = x*CELL + 2;
			rect.right = (x + 1)*CELL - 2;
			if (m_vPanel[y][x])
			{
				FillRect(m_hDC, &rect, h_bSolid);
			}
			else
			{
				FillRect(m_hDC, &rect, h_bEmpty);
			}
		}
	}

	//��ʾ�������µķ���
	for (int y = 0; y<m_nGoHeight; y++)
	{
		for (int x = 0; x<m_nGoWidth; x++)
		{
			if (m_vBlock[y*m_nGoWidth + x])  //ʵ��
			{
				rect.top = (y + m_nCurTop)*CELL + 2;
				rect.bottom = (y + m_nCurTop + 1)*CELL - 2;
				rect.left = (x + m_nCurLeft)*CELL + 2;
				rect.right = (x + m_nCurLeft + 1)*CELL - 2;
				FillRect(m_hDC, &rect, h_bSolid);
			}

		}
	}

}

bool CGame::CreateBlock()    //�������
{
	int nSel = rand() % 7;//7����״
	switch (nSel)
	{
	case 0:   //ˮƽ��
		m_nGoWidth = 4;
		m_nGoHeight = 1;


		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 1, 1, 1, 1 };



		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 1:   //����
		m_nGoWidth = 3;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 0,1,0,1,1,1 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 2:   //�����
		m_nGoWidth = 3;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 1,0,0,1,1,1 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 3:   //�Һ���
		m_nGoWidth = 3;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 0,0,1,1,1,1 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 4:   //������
		m_nGoWidth = 3;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 1,1,0,0,1,1 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 5:   //������
		m_nGoWidth = 3;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 0,1,1,1,1,0 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;
	case 6:   //������
		m_nGoWidth = 2;
		m_nGoHeight = 2;

		m_vBlock.resize(m_nGoWidth*m_nGoHeight);
		m_vBlock = { 1,1,1,1 };

		//��ǰ����λ��
		m_nCurTop = 0 - m_nGoHeight;
		m_nCurLeft = (COLS - m_nGoWidth) / 2;
		break;

	}
	return m_vBlock.size()>0;
}

bool CGame::IsTouchBottom()
{
	if (m_vBlock.size() <= 0)
	{
		return false;
	}

	//�Ƿ񵽴�ײ�
	if (ROWS == m_nCurTop + m_nGoHeight)
	{
		//�̶�����
		for (int i = 0; i<m_nGoHeight; i++)
		{
			for (int j = 0; j<m_nGoWidth; j++)
			{
				if (m_vBlock[i*m_nGoWidth + j])
				{
					m_vPanel[m_nCurTop + i][m_nCurLeft + j] = 1;
				}
			}
		}

		return true;
	}

	for (int y = m_nGoHeight - 1; y >= 0; y--)//�ӵ��п�ʼɨ��
	{
		//�жϵ�һ��ʵ�ķ�����������ڽӵ��·������Ƿ�Ϊʵ�ģ��Ǿʹ����Ѿ�����ײ�
		for (int x = 0; x<m_nGoWidth; x++)
		{
			if (!m_vBlock[y*m_nGoWidth + x])
			{
				//�յķ��鲻���жϡ�
				continue;
			}
			if (m_nCurTop + y + 1<0)
			{
				return false;
			}
			if (!m_vPanel[m_nCurTop + y + 1][m_nCurLeft + x])
			{
				//�ײ�Ϊ�յķ���Ҳ�����ж�
				continue;
			}

			//�ж��Ƿ�gameover
			if (m_nCurTop <= 0)
			{
				if (m_nTimer)
				{
					KillTimer(m_hWnd, ID_TIMER);
					m_nTimer = 0;
				}
				MessageBox(m_hWnd, TEXT("��Ϸ����"), TEXT("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
				SendMessage(m_hWnd, WM_CLOSE, 0, 0);
				return true;
			}

			//�̶�����
			for (int i = 0; i<m_nGoHeight; i++)
			{
				for (int j = 0; j<m_nGoWidth; j++)
				{
					if (m_vBlock[i*m_nGoWidth + j])
					{
						m_vPanel[m_nCurTop + i][m_nCurLeft + j] = 1;
					}
				}
			}
			return true;
		}
	}
	return false;
}

void CGame::ClearRow()      //����
{
	int nCount = 0;//���д���
	bool isFilled = false;
	//���д���
	for (int i = ROWS - 1; i >= 0; i--)
	{
		isFilled = true;
		for (int j = 0; j<COLS; j++)
		{
			if (!m_vPanel[i][j])
			{
				isFilled = false;
				break;
			}
		}
		if (isFilled)
		{
			for (int j = 0; j<COLS; j++)
			{
				m_vPanel[i][j] = 0;
			}
			//���з���������
			for (int k = i - 1; k >= 0; k--)
			{
				for (int j = 0; j<COLS; j++)
				{
					m_vPanel[k + 1][j] = m_vPanel[k][j];
				}
			}
			i = i + 1;
			nCount++;
		}
	}

	//��߼���Ϊ9�������Է���Ϊ��9+1��*score_level_inc-1
	if (m_nScore >= 10 * SCORE_LEVEL_INC - 1)
	{
		return;
	}

	//�ӷֹ�������������1�м�10�֣�2�м�15�֣�3�м�20�֣�4�м�30��
	switch (nCount)
	{
	case 1:
		m_nScore += 10;
		break;
	case 2:
		m_nScore += 15;
		break;
	case 3:
		m_nScore += 20;
	case 4:
		m_nScore += 30;
		break;
	}
	int nTemp_level = m_nScore / SCORE_LEVEL_INC;
	if (nTemp_level>m_nLevel)
	{
		m_nLevel = nTemp_level;
		//������ǰ��ʱ����Ȼ������
		if (m_nTimer)
		{
			KillTimer(m_hWnd, ID_TIMER);
		}
		m_nTimer = ::SetTimer(m_hWnd, ID_TIMER, GetDownVal(), NULL);
	}
	std::ostringstream oss;
	oss << "Score:" << m_nScore << ",Level:" << m_nLevel << std::endl;
	OutputDebugStringA(oss.str().c_str());

	ShowScore();
}

void CGame::ShowScore(void)
{
	std::wostringstream woss;
	woss << L"Score:" << m_nScore << L",Level:" << m_nLevel << std::ends;
	SetWindowText(m_hWndEdit, woss.str().c_str());
}

void CGame::DoDownShift(void)//����
{
	if (m_vBlock.size() <= 0)
	{
		return;
	}
	//�ж��Ƿ񵽴�ײ�
	if (IsTouchBottom())
	{
		//���д���
		ClearRow();
		CreateBlock();//�����һ������
	}
	m_nCurTop++;
	RefreshPanel();
}

void CGame::DoLeftShift(void) //����
{
	if (m_bIsPause)
	{
		return;
	}
	if (m_vBlock.size() <= 0)
	{
		return;
	}
	//�Ѿ���������ߣ���������
	if (m_nCurLeft == 0)
	{
		return;
	}
	if (m_nCurTop<0)
	{
		return;  //����û��������ʾǰ����������
	}

	//������µķ������Ѿ��̶��ķ����Ƿ��г�ͻ
	for (int y = 0; y<m_nGoHeight; y++)
	{
		for (int x = 0; x<m_nGoWidth; x++)//����߿�ʼɨ�裬��ȡ���������ʵ�ķ���
		{
			if (m_vBlock[y*m_nGoWidth + x])
			{
				//�жϵ�ǰ����������������һ�������Ƿ�Ϊʵ�ģ��Ǿʹ���������
				if (m_vPanel[m_nCurTop + y][m_nCurLeft + x - 1])
				{
					return;
				}
				break; //ֻ�ж�����ߵ�һ��ʵ�ķ���֮��ֱ��ɨ����һ��
			}
		}
	}

	m_nCurLeft--;
	RefreshPanel();

}

void CGame::DoRightShift() //����
{
	if (m_bIsPause)
	{
		return;
	}

	if (m_vBlock.size() <= 0)
	{
		return;
	}
	if (COLS - m_nGoWidth == m_nCurLeft)
	{
		return;
	}
	if (m_nCurTop < 0)
	{
		return;//����������ʾǰ��������
	}
	for (int y = 0; y<m_nGoHeight; y++)
	{
		for (int x = m_nGoWidth - 1; x >= 0; x--)//���ұ߿�ʼɨ�裬��ȡ�������ұ�ʵ�ķ���
		{
			if (m_vBlock[y*m_nGoWidth + x])
			{
				//�жϵ�ǰ��������������ұ�һ�������Ƿ�Ϊʵ�ģ��Ǿʹ���������
				if (m_vPanel[m_nCurTop + y][m_nCurLeft + x - 1])
				{
					return;
				}
				break; //ֻ�ж����ұߵ�һ��ʵ�ķ���֮��ֱ��ɨ����һ��
			}
		}
	}

	m_nCurLeft++;
	RefreshPanel();


}

void CGame::DoAccelerate()   //����
{
	if (m_bIsPause)
	{
		return;
	}

	if (m_vBlock.size() <= 0)
	{
		return;
	}
	if (IsTouchBottom())
	{
		//���д���
		ClearRow();
		CreateBlock();
	}
	m_nCurTop++;
	RefreshPanel();
}

void CGame::DoRedirection()//�ı䷽��
{
	if (m_bIsPause)
	{
		return;
	}

	if (m_vBlock.size() <= 0)
	{
		return;
	}

	if (m_nCurTop<0)
	{
		return;//����������ʾǰ����ת��
	}
	vector<BYTE> vTemp(m_nGoWidth*m_nGoHeight, 0);
	//��ת����
	for (int i = 0; i<m_nGoWidth; i++)
	{
		for (int j = 0; j<m_nGoHeight; j++)
		{
			vTemp[i*m_nGoHeight + j] = m_vBlock[(m_nGoHeight - j - 1)*m_nGoWidth + i];
		}
	}
	//���������¶�λ
	int incHeight = m_nGoWidth - m_nGoHeight;
	int incWidth = m_nGoHeight - m_nGoWidth;

	//����������µ�����
	int iTemp_cur_top = m_nCurTop - incHeight / 2;
	int iTemp_cur_left = m_nCurLeft - incWidth / 2;

	//�жϵ�ǰ�ռ��Ƿ��㹻�÷���ı䷽��
	int max_len = max(m_nGoWidth, m_nGoHeight);
	//��ֹ�±����Խ��
	if (iTemp_cur_top + max_len - 1 >= ROWS || iTemp_cur_left<0 ||
		iTemp_cur_left + max_len - 1 >= COLS)
	{
		return;
	}
	//�ж��µ������£��Ƿ���Է��÷���
	for (int i = 0; i<max_len; i++)
	{
		for (int j = 0; j<max_len; j++)
		{
			//ת������Ŀռ������ѱ�ռ�õ�ʵ�ķ������ڣ���ת��ʧ��
			if (m_vPanel[iTemp_cur_top + i][iTemp_cur_left + j])
			{
				//���ܷ���
				return;
			}
		}
	}

	//����ʱ������ֵ����block��ֻ�ܸ�ֵ�������ܸ�ָ��ֵ
	for (int i = 0; i<m_nGoHeight; i++)
	{
		for (int j = 0; j<m_nGoWidth; j++)
		{
			m_vBlock[i*m_nGoWidth + j] = vTemp[i*m_nGoWidth + j];
		}
	}
	//��������������±���ֵ
	m_nCurTop = iTemp_cur_top;
	m_nCurLeft = iTemp_cur_left;

	//����
	int iTemp = m_nGoWidth;
	m_nGoWidth = m_nGoHeight;
	m_nGoHeight = iTemp;

	RefreshPanel();
}

void CGame::SetPause(void)
{
	m_bIsPause = !m_bIsPause;
	if (m_bIsPause)
	{
		if (m_nTimer)
		{
			::KillTimer(m_hWnd, ID_TIMER);
		}
		m_nTimer = 0;
	}
	else
	{
		m_nTimer = ::SetTimer(m_hWnd, ID_TIMER, GetDownVal(), FALSE);
	}
}

int CGame::GetDownVal(void) const
{
	return INTERVAL_BASE - m_nLevel*INTERVAL_UNIT;
}

void CGame::SetShowEdit(HWND hWnd)
{
	m_hWndEdit = hWnd;
}
