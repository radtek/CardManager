// CardObject.h : Declaration of the CCardObject

#pragma once
#include "resource.h"       // main symbols



#include "CardOCX_i.h"
#include "_ICardObjectEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CCardObject

class ATL_NO_VTABLE CCardObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCardObject, &CLSID_CardObject>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCardObject>,
	public CProxy_ICardObjectEvents<CCardObject>,
	public IObjectWithSiteImpl<CCardObject>,
	public IDispatchImpl<ICardObject, &IID_ICardObject, &LIBID_CardOCXLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCardObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CARDOBJECT)


BEGIN_COM_MAP(CCardObject)
	COM_INTERFACE_ENTRY(ICardObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCardObject)
	CONNECTION_POINT_ENTRY(__uuidof(_ICardObjectEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(OCX_Init)(LONG* retValue);
	STDMETHOD(OCX_About)(BSTR* message);
	STDMETHOD(OCX_ReadTrack)(SHORT trackNo, BSTR* trackInfo);
	STDMETHOD(OCX_WriteTrack)(SHORT trackNo, BSTR* trackInfo, LONG* retValue);
	STDMETHOD(OCX_GetLastError)(BSTR* message);
	STDMETHOD(OCX_EjectCard)(LONG* retValue);
	STDMETHOD(OCX_SetCoercivity)(BSTR* coercivity, LONG* retValue);
};

OBJECT_ENTRY_AUTO(__uuidof(CardObject), CCardObject)
