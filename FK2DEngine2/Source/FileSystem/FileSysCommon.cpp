/**
*	created:		2012-6-16   2:54
*	filename: 		FileSysCommon
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../Include/FileSystem/FileSysCommon.h"
#include "../../Include/FileSystem/StdFileSystem.h"
#include "../../Include/FileSystem/StdFileObject.h"
#include "../../Include/FileSystem/PackFileSystem.h"
//------------------------------------------------------------------------
// 输出函数 : CreateFileSystem
// 参数：
// szFileSystemName : 	对于目录态系统,这是某个文件所在的目录，如e:\dxGame\data\bmp
//						对于包态文件系统,这是个包文件
// dwStyle			: 	指定是创建目录态文件系统还是包态文件系统；还可以指定其它选项
BOOL CIFileSystemHelper::CreateFileSystem(DWORD dwExpectVersion,
													   LPCSTR szFileSystemName, DWORD dwStyle, ITrace* pTrace,
													   IFileSystem** ppFileSystem,	void* Reserved)
{
	if(dwExpectVersion != VERSION_QUERY_FILE_SYSTEM)
	{
		TraceLn("CreateFileSystem() : Version error!");
		return FALSE;
	}

	if (dwStyle != FSS_DIRECTORY && dwStyle != FSS_PACKAGE)
		dwStyle = FSS_DIRECTORY;

	// 根据传入的参数智能识别文件系统类型
	if (szFileSystemName == NULL || 
		*szFileSystemName == '.' || 
		*szFileSystemName == 0)  // 表明用当前目录作目录态
		dwStyle = FSS_DIRECTORY;
	else
	{
		char buf[1024];
		int nLen = lstrlenA(szFileSystemName);
		lstrcpynA(buf, szFileSystemName, 1024);
		if (buf[nLen-1] == '\\' || buf[nLen-1] == '/')
			buf[nLen-1] = '\0';

		WIN32_FIND_DATAA wfd;
		if (INVALID_HANDLE_VALUE != ::FindFirstFileA(buf, &wfd)) // 存在
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // 目录，说明是目录态
				dwStyle = FSS_DIRECTORY;
			else  // 说明是包态
				dwStyle = FSS_PACKAGE;
		}
		else // 不存在，说明是新建，则依参数dwStyle而定
		{
			if (-1 != _access(buf, 0)) // 存在，说明是根目录
			{
				dwStyle = FSS_DIRECTORY;
			}

		}

	}

	if (dwStyle == FSS_DIRECTORY)
	{
		CStdFileSystem*	pStdFileSystem = new CStdFileSystem();
		ASSERT(pStdFileSystem);
		if (!pStdFileSystem->Init(szFileSystemName))
		{
			SAFE_DELETE(pStdFileSystem);
			return FALSE;
		}
		*ppFileSystem = static_cast<IFileSystem*>(pStdFileSystem);
	}
	else if (dwStyle == FSS_PACKAGE)
	{
		CPackFileSystem* pPackFileSystem = new CPackFileSystem();
		ASSERT(pPackFileSystem);
		if (!pPackFileSystem->Init(szFileSystemName))
		{
			SAFE_DELETE(pPackFileSystem);
			return FALSE;
		}
		*ppFileSystem = static_cast<IFileSystem*>(pPackFileSystem);
	}

	TraceLn("CreateFileSystem('%s')......OK", szFileSystemName);
	return *ppFileSystem != NULL;
}
//------------------------------------------------------------------------
// 这里只提供创建标准文件对象
BOOL CIFileSystemHelper::CreateFileObject(DWORD dwExpectVersion,
													   LPCSTR szFileName, ITrace* pTrace,
													   IFileObject** ppFileObject)
{
	if(dwExpectVersion != VERSION_QUERY_FILE_SYSTEM)
	{
		TraceLn("CreateFileObject() : Version error!");
		return FALSE;
	}

	CStdFileObject* pStdFileObject = new CStdFileObject;
	ASSERT(pStdFileObject != NULL);

	pStdFileObject->SetFilePath(szFileName);
	*ppFileObject = static_cast<IFileObject*>(pStdFileObject);
	TraceLn("CreateFileObject()......OK");
	return pStdFileObject != NULL;
}
//------------------------------------------------------------------------