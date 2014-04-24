#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifndef uint8
#define uint8  unsigned char
#endif

#define EVOLIS_DRIVER "Evolis"

#define COERCIVITY_LOW 'l'
#define COERCIVITY_HIGH 'h'

#define CHECK_PRINTER() if(printer==NULL) return NO_PRINTER

//系统返回码定义
#define SUCCESS 0                           //成功
#define NO_PRINTER 1001                     //未找到打印机
#define ERR_READ_TRACK 1002                 //读取磁道信息失败
#define ERR_WRITE_TRACK 1003                //写磁道信息失败

#define OK_PRINTER           0
#define ERR_PRINTER          1103
#define ERR_CDE              1104
#define ERR_PAR              1105
#define ERR_NEED_CLEAN       1107
#define ERR_TIME             1111
#define ERR_MECA_HOPPER      1113
#define ERR_HOPPER_FULL      1114
#define ERR_HOPPER_DOOR      1115
#define ERR_PRINT_HEAD       1116
#define ERR_COVER            1117
#define ERR_FEEDER           1118
#define ERR_CARD_JAM         1119
#define ERR_RIBBON           1120
#define ERR_FLASH            1122
#define ERR_CHECKSUM         1123
#define ERR_OPTION           1124
#define ERR_CHECK_M          1126
#define ERR_DATA_M           1127
#define ERR_WRITE_M          1128
#define	ERR_UNKNOW           1129

#endif