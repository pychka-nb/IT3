
// IT33Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT33.h"
#include "IT33Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define Pi 3.1415926535

// Диалоговое окно CIT33Dlg



CIT33Dlg::CIT33Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT33_DIALOG, pParent)
	, N(1024)
	, fd(1)
	, valueSin(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT33Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, N);
	DDX_Text(pDX, IDC_EDIT3, fd);
	DDX_Text(pDX, IDC_EDIT2, valueSin);
}

BEGIN_MESSAGE_MAP(CIT33Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CIT33Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CIT33Dlg

BOOL CIT33Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	graph1.Create(GetDlgItem(IDC_Signal)->GetSafeHwnd());
	graph2.Create(GetDlgItem(IDC_SignalAR)->GetSafeHwnd());
	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT33Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT33Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*Ф-ция, вычисляющая предел графика*/
double CIT33Dlg::FindMin(vector <double> data, int N)
{
	double min = data[0];
	for (int i = 0; i < N; i++)
	{
		if (min > data[i])
			min = data[i];
	}
	return min;
}
/*Ф-ция, вычисляющая предел графика*/
double CIT33Dlg::FindMax(vector <double> data, int N)
{
	double max = data[0];
	for (int i = 0; i < N; i++)
	{
		if (max < data[i])
			max = data[i];
	}
	return max;
}

void CIT33Dlg::CreateSignal()
{
	double a3, a4,aA, aF;//вспомогательные переменные для амплитуды и частоты;
	for (int i = 0; i < valueSin; i++) {
		aF= rand()/(2.0 * RAND_MAX);
		Fsin.push_back(aF);//вектор частот для каждой синусоиды
	}
	for (int i = 0; i <= N; i++)
	{	
		a3 = 0;
		for (int j = 0; j < valueSin; j++) {
			a3 += sin(2 * Pi * Fsin[j] * (i / fd));
		}
		Sign.push_back(a3);
	}
	int i,j;
	/*for (i = 0; i < valueSin+1; i++) {
		for (j = -valueSin; j <= valueSin; j++) {
			rx[i] += Sign[abs(i + j)] * Sign[i];
		}
		int p1;
		p1 = 2 * valueSin + 1;
		rx[i] /= p1;
	}*/
	for (i = 0; i <= p; i++) {
		for (j = 1; j <= N-p; j++) {
			rx[i] += Sign[i + j] * Sign[j];
		}
		int p1;
		p1 = N-p;
		rx[i] /= p1;
	}
	/*for (i = 0; i < p; i++) {
		for (j = 0; j < p; j++) {
				R[i][j] = rx[abs(i-j)];		
		}
		//R[i][i] = 1.;
		B[i] = rx[i + 1];
	}*/
	for (i = 0; i <= p; i++) {
		for (j = 0; j <=p ; j++) {
			R[i][j] = rx[abs(i - j)];
		}
		//R[i][i] = 1.;

		//B[i] = rx[i + 1];
		B[i] = 0.;
	}
}

void CIT33Dlg::Iter()
{
	/*for (int i = 0; i < p; i++)
	{
		x[i] = B[i] / R[i][i];
	}

	do {
		for (int i = 0; i < p; i++) {
			Xn[i] = B[i] / R[i][i];
			for (int j = 0; j < p; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= (R[i][j] / R[i][i]) * x[j];
				}
			}
		}

		bool flag = true;
		for (int i = 0; i < p - 1; i++) {
			if (abs(Xn[i] - x[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (int i = 0; i < p; i++) {
			x[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);
	*/

	/*for (int k = 0; k < 50; ++k) {//количество итераций
		for (int i = 0; i < p; ++i) {
			x[i] = x[i] + (B[i] - x[i]*R[i][i]) / R[i][i]*R[i][i] * R[i][i];
		}
	}*/
	double scal, square,G;
	G = 0;
	/*do {
		for (int j = 0; j < p; j++) {
			scal = 0;
			square = 0;
			for (int i = 0; i < p; i++) {
				scal += R[i][j] * u[j];
				square += R[i][j] * R[i][j];
			}
			for (int i = 0; i < p; i++) {
				u[j] = u[j] + (B[j] - scal) / square * R[i][j];
			}
		}
		G++;
	} while (G != 100);*/
	/*
	do {
		for (int i = 0; i < p; i++) {
			scal = 0;
			square = 0;
			for (int j = 0; j < p; j++) {
				scal += R[i][j] * u[i];
				square += R[i][j] * R[i][j];
			}
			for (int j = 0; j < p; j++) {
				u[i] = u[i] + (B[i] - scal) / square * R[i][j];
			}
		}
		G++;
	} while (G != 100);
	*/
	
		// nn - количество неизвестных; ny - количество уравнений
		double eps = 0.0001;
		//float s;
		int i, j, k;
		double s1, s2, fa1, t;
		double* x1;

		x1 = new double[p+1];

		x[0] = 1;
		for (i = 1; i <= p ; i++) x[i] = 0.f;

		s1 = s2 = 1.f;
		while (s1 > eps * s2)
		{

			for (i = 0; i <= p; i++) x1[i] = x[i];

			for (i = 0; i <= p; i++)
			{
				s1 = 0.0;
				s2 = 0.0;
				for (j = 0; j <= p; j++)
				{
					fa1 = R[i][j];
					s1 += fa1 * x[j];
					s2 += fa1 * fa1;
				}
				t = (B[i] - s1) / s2;
				for (k = 1; k <= p; k++) x[k] += R[i][k] * t;
			}

			s1 = 0.0;
			s2 = 0.0;
			for (i = 0; i <= p; i++)
			{
				s1 += (x[i] - x1[i]) * (x[i] - x1[i]);
				s2 += x[i] * x[i];
			}
			s1 = (double)sqrt(s1);
			s2 = (double)sqrt(s2);
		}
		delete[] x1;
	

		


}
void CIT33Dlg::CreateSignal2() {
	/*double s2;
	for (int i = N/2; i < N; i++) {
		s2 = 0;
		for (int k = 0; k < p; k++) {
				s2 -= Sign[i - k] * x[k];
		}
		Sign.push_back(s2);
	}*/
	double s2;
	for (int i = p; i < N; i++) {
		s2 = 0;
		for (int k = 0; k < p; k++) {
			s2 -= Sign[i - k] * x[k+1];
		}
		Sign2.push_back(s2);
	}

}
void CIT33Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	srand(time(NULL));
	graph1.DrawW();
	graph2.DrawW();
	
	UpdateData(true);
	

	p = valueSin * 2;
	for (int i = 0; i < p; i++) {
		u[i] = -1.;
	}
	CreateSignal();
	Iter();
	CreateSignal2();
	for (int i = 0; i < N; i++)
	{
		keys.push_back(i / fd);
	}
	double xmax = (N - 1) / fd,
		ymax = FindMax(Sign, N),
		ymin = FindMin(Sign, N);
	graph1.DrawOne(Sign, 0, xmax, ymin, ymax, keys);

	//ymax = 2;
	//ymin = -2;
	graph2.DrawOneBlue(Sign2, 0, xmax, ymin, ymax, keys);
	UpdateData(false);
	Asin.clear();
	Fsin.clear();
	Sign.clear();
	keys.clear();
	Sign2.clear();
}
/*if (i<p){
			for (int j1 = 0; j1 < p; j1++) {
				for (int j2=0; j2 < valueSin; j2++) {
					R[i][j1] += cos(2 * Pi * Fsin[j2] * ((j1 - i) / fd));
				}

			}
		}*/