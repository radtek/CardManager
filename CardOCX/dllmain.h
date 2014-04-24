// dllmain.h : Declaration of module class.

class CCardOCXModule : public ATL::CAtlDllModuleT< CCardOCXModule >
{
public :
	DECLARE_LIBID(LIBID_CardOCXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CARDOCX, "{EC8E707B-F319-4EA4-B435-0648998773C7}")
};

extern class CCardOCXModule _AtlModule;
