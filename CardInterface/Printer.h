#ifndef PRINTER_H_
#define PRINTER_H_

#include <map>
#include <string>
#include <vector>
using namespace std;

#include "Iomem.h"

typedef pair<string, string> String_Pair;

class CPrinter : public CIomem //Derive from CIomem to be able to communicate with the printer
{
public:
	CPrinter();
	virtual	~CPrinter();

	void SetDriverName(char *);
	char* GetDriverName();

	/// @brief Send an command to the printer and get its answer
	///
	/// @param[in ] :command without the start character and stop character
	/// @param[in ] :timeout milliseconds
	/// @param[in ] :answer response from the printer
	void SendCommand(const char* command, long timeout, string &answer);

	/// @brief Send an command to the printer,pls make sure the port is opened
	///
	/// @param[in ] :command without the start character and stop character
	/// @param[in ] :timeout milliseconds
	/// @param[in ] :bPrev ithe status of previous command
	/// @return     :if execution correct and answer OK
	bool DoAction(const char* command, long timeout, bool bPrev = true);

	/// @brief add start character and stop character for the command
	///
	/// @param[in ] :command without the start character and stop character
	/// @param[in ] :timeout milliseconds
	/// @param[in ] :bPrev ithe status of previous command
	/// @return     :if execution correct and answer OK
	void SetCommand(const char* command);

	/// @brief Analyze printer answer
	///
	/// @return     :error code
	int AnalyzeAnswer();

	/// @brief get last error message
	///
	/// @return     :error message
	string GetErrorMessage();

	/// @brief get coercivity command
	///
	/// @param[out] :command the command for setting coercivity 
	void GetCoercivityCommand(char* command);

	/// @brief set coercivity in memory
	///
	/// @param[in ] :value coercivity 'l' or 'h'
	void SetCoercivity(char value);

	/// @brief Write the specific magnetic track
	///
	/// @param[in ] :trackNo the index of magnetic 
	/// @param[in ] :trackInfo magnetic track data
	/// @return     :True: done
	bool WriteTrack(int trackNo, string &trackInfo);

	/// @brief Read the specific magnetic track
	///
	/// @param[in ] :trackNo the index of magnetic 
	/// @param[out] :trackInfo magnetic track data
	/// @return     :True: done
	bool ReadTrack(int trackNo, string &trackInfo);

	/// @brief 打印卡片，包括有效日期和面值
	///
	/// @param[in ] :expiredDate 有效日期
	/// @param[in ] :parValue 面值
	/// @return     :True: done
	bool Print(char* expiredDate, int parValue);

	/// @brief 打印卡片密码
	///
	/// @param[in ] :password 卡片密码
	/// @return     :True: done
	bool PrintPassword(char* password);

protected:
	char DriverName[128];

private:
	map<string,int> printerErrors;
	char coercivity;
	string detailAnswer;
};

#endif // PRINTER_H_
