
// IT33.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CIT33App:
// Сведения о реализации этого класса: IT33.cpp
//

class CIT33App : public CWinApp
{
public:
	CIT33App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CIT33App theApp;
