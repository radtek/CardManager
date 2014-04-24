// CardObject.cpp : Implementation of CCardObject


#include "stdafx.h"
#include<comdef.h>
#include <comutil.h>
#include "CardObject.h"
#include "../CardInterface/CardInterface.h"

const char * COMPILED_DATE = __DATE__;

// CCardObject

STDMETHODIMP CCardObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_ICardObject
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CCardObject::OCX_Init(LONG* retValue)
{
	*retValue = Card_Init();
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_About(BSTR* message)
{
    char cMessage[255]; 
    sprintf(cMessage,"Card Interface %s %s","V1.0",COMPILED_DATE);
 	*message = _com_util::ConvertStringToBSTR(cMessage);
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_ReadTrack(SHORT trackNo, BSTR* trackInfo)
{
	char track[50];
	memset(track,0,sizeof(track));
	char error[100];
	memset(error,0,sizeof(error));
	int ret = Card_ReadTrack(trackNo,track);
	if(ret==0)
	{
		*trackInfo = _com_util::ConvertStringToBSTR(track);	
	}
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_WriteTrack(SHORT trackNo, BSTR* trackInfo, LONG* retValue)
{
	*retValue = Card_WriteTrack(trackNo,_com_util::ConvertBSTRToString(*trackInfo));
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_GetLastError(BSTR* message)
{
	char cMessage[250];
	memset(cMessage,0,sizeof(cMessage));
	Card_GetLastError(cMessage);
	*message = _com_util::ConvertStringToBSTR(cMessage);
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_EjectCard(LONG* retValue)
{
	char answer[250];
	memset(answer,0,sizeof(answer));
	*retValue = Card_EjectCard(answer);
	return S_OK;
}


STDMETHODIMP CCardObject::OCX_SetCoercivity(BSTR* coercivity, LONG* retValue)
{
	*retValue = Card_SetCoercivity(_com_util::ConvertBSTRToString(*coercivity)[0]);
	return S_OK;
}
