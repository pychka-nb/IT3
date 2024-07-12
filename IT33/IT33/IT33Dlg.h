
// IT33Dlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include "Drawer.h"
#include <math.h>

// Диалоговое окно CIT33Dlg
class CIT33Dlg : public CDialogEx
{
// Создание
public:
	CIT33Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT33_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
public:
	double N;
	double fd;
	int p;
	int valueSin;
	vector <double> Asin;
	vector <double> Fsin;
	vector <double> Sign;
	vector <double> Sign2;
	vector <double> keys;
	double  R[100][100];
	double rx[100];
	//double* B;
	double B[100];
	//double* x;
	double x[100];
	double u[100];
	double eps = 0.001;
	double Xn[100];
	
	void Iter();
	void CreateSignal();
	void CreateSignal2();
	double FindMin(vector<double> data, int N);
	double FindMax(vector<double> data, int N);

	Drawer
		graph1,
		graph2;
	double ymin, ymax;
	
};
