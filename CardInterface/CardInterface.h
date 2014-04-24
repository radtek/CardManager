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

#define IN         //入参
#define OUT        //出参

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief 初始化CardInterface工作环境
	///
    /// @return     :0 表示成功
	CARDINTERFACE_API int Card_Init();

	/// @brief 获取当前可用打印机数量，只包含Evolis打印机
	///
	/// @return     :打印机数量
	CARDINTERFACE_API int Card_GetPrinterCount();

	/// @brief 获取当前可用打印机名称
	///
	/// int printerCount = Card_GetPrinterCount();
	/// char** printers = new char*[printerCount];
	///	for (int i = 0; i < printerCount; ++i)
    ///		{
	///		printers[i] = new char[100];
	///		memset(printers[i],0x00,100);
	///	}
	///
	/// @param[out] :printers 打印机名称数组
	/// @param[in ] :size 打印机数量
	CARDINTERFACE_API void Card_GetPrinters(OUT char **printers,IN int size);

	/// @brief 执行指定命令
	///
	/// @param[in ] :command 待执行命令
	/// @param[out] :answer 响应
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_ExecuteCommand(IN const char* command, OUT char* answer);

	/// @brief 读取指定磁道信息
	///
	/// @param[in ] :trackNo 磁道索引(1-3)
	/// @param[out] :trackInfo 磁道信息
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_ReadTrack(IN int trackNo, OUT char* trackInfo);

	/// @brief 写磁道信息
    ///
    /// @param[in ] :trackNumber 磁道
    /// @param[in ] :trackInfo 对应磁道信息
    /// @return     :0 表示成功
	CARDINTERFACE_API int Card_WriteTrack(IN int trackNo,IN char *trackInfo);

	/// @brief 在执行命令失败之后，调用此方法返回错误信息
	///
	/// @param[out] :message 错误信息
	CARDINTERFACE_API void Card_GetLastError(OUT char *message);

	/// @brief 弹出卡片
	///
	/// @param[out] :answer 响应
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_EjectCard(OUT char* answer);

	/// @brief 设置coercivity
	///
	/// @param[in ] :coercivity 'l' or 'h'
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_SetCoercivity(IN char coercivity);

	/// @brief 打印卡片，包括有效日期和面值
	///
	/// @param[in ] :expiredDate 有效日期
	/// @param[in ] :parValue 面值
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_Print(IN char* expiredDate, IN int parValue);

	/// @brief 打印卡片密码
	///
	/// @param[in ] :password 卡片密码
	/// @return     :0 表示成功
	CARDINTERFACE_API int Card_PrintPassword(IN char* password);

#ifdef __cplusplus
}
#endif