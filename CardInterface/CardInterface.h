// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CARDINTERFACE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CARDINTERFACE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CARDINTERFACE_EXPORTS
#define CARDINTERFACE_API __declspec(dllexport)
#else
#define CARDINTERFACE_API __declspec(dllimport)
#endif

#define IN         //���
#define OUT        //����

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief ��ʼ��CardInterface��������
	///
    /// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_Init();

	/// @brief ��ȡ��ǰ���ô�ӡ��������ֻ����Evolis��ӡ��
	///
	/// @return     :��ӡ������
	CARDINTERFACE_API int Card_GetPrinterCount();

	/// @brief ��ȡ��ǰ���ô�ӡ������
	///
	/// int printerCount = Card_GetPrinterCount();
	/// char** printers = new char*[printerCount];
	///	for (int i = 0; i < printerCount; ++i)
    ///		{
	///		printers[i] = new char[100];
	///		memset(printers[i],0x00,100);
	///	}
	///
	/// @param[out] :printers ��ӡ����������
	/// @param[in ] :size ��ӡ������
	CARDINTERFACE_API void Card_GetPrinters(OUT char **printers,IN int size);

	/// @brief ִ��ָ������
	///
	/// @param[in ] :command ��ִ������
	/// @param[out] :answer ��Ӧ
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_ExecuteCommand(IN const char* command, OUT char* answer);

	/// @brief ��ȡָ���ŵ���Ϣ
	///
	/// @param[in ] :trackNo �ŵ�����(1-3)
	/// @param[out] :trackInfo �ŵ���Ϣ
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_ReadTrack(IN int trackNo, OUT char* trackInfo);

	/// @brief д�ŵ���Ϣ
    ///
    /// @param[in ] :trackNumber �ŵ�
    /// @param[in ] :trackInfo ��Ӧ�ŵ���Ϣ
    /// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_WriteTrack(IN int trackNo,IN char *trackInfo);

	/// @brief ��ִ������ʧ��֮�󣬵��ô˷������ش�����Ϣ
	///
	/// @param[out] :message ������Ϣ
	CARDINTERFACE_API void Card_GetLastError(OUT char *message);

	/// @brief ������Ƭ
	///
	/// @param[out] :answer ��Ӧ
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_EjectCard(OUT char* answer);

	/// @brief ����coercivity
	///
	/// @param[in ] :coercivity 'l' or 'h'
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_SetCoercivity(IN char coercivity);

	/// @brief ��ӡ��Ƭ��������Ч���ں���ֵ
	///
	/// @param[in ] :expiredDate ��Ч����
	/// @param[in ] :parValue ��ֵ
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_Print(IN char* expiredDate, IN int parValue);

	/// @brief ��ӡ��Ƭ����
	///
	/// @param[in ] :password ��Ƭ����
	/// @return     :0 ��ʾ�ɹ�
	CARDINTERFACE_API int Card_PrintPassword(IN char* password);

#ifdef __cplusplus
}
#endif