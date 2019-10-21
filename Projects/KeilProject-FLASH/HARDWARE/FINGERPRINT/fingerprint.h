#ifndef _FINGERPRINT_H
#define _FINGERPRINT_H

#include "sys.h"
#include "usart3.h"

//包类别识别码
// 		Packet类别					Code包类别识别码
#define COMMAND_PACKET_PREFIX		0xAA55				//命令包
#define RESPONSE_PACKET_PREFIX		0x55AA				//响应包
#define COMMAND_DATA_PACKET_PREFIX	0xA55A				//指令数据包
#define RESPONSE_DATA_PACKET_PREFIX 0x5AA5				//响应数据包


//通讯命令综述
// 命令名称(Command Name)			命令码(Code)	命令功能(Function)
#define CMD_TEST_CONNECTION 		0x0001			//进行与设备的通讯测试
#define CMD_SET_PARAM 				0x0002			//设置设备参数(Device ID, Security Level, Baudrate, Duplication Check, Auto Learn, Timeout)
#define CMD_GET_PARAM 				0x0003			//获取设备参数(Device ID, Security Level, Baudrate, Duplication Check, Auto Learn, Timeout)
#define CMD_GET_DEVICE_INFO 		0x0004			//获取设备信息
#define CMD_ENTER_IAP_MODE			0x0005			//将设备设置为IAP状态
#define CMD_GET_IMAGE				0x0020			//从采集器采集指纹图像并保存于ImageBuffer中
#define CMD_FINGER_DETECT			0x0021			//检测指纹输入状态
#define CMD_UP_IMAGE				0x0022			//将保存于ImageBuffer中的指纹图像上传至HOST
#define CMD_DOWN_IMAGE				0x0023			//HOST下载指纹图像到模块的ImageBuffer中
#define CMD_SLED_CTRL				0x0024			//控制采集器背光灯的开/关(注:半导体传感器不用此功能)
#define CMD_STORE_CHAR				0x0040			//将指定编号Ram Buffer中的Template注册到指定编号的库中
#define CMD_LOAD_CHAR				0x0041			//读取库中指定编号中的Template到指定编号的Ram Buffer
#define CMD_UP_CHAR					0x0042			//将保存于指定编号的Ram Buffer中的Template上传至HOST
#define CMD_DOWN_CHAR				0x0043			//从HOST下载Template到模块指定编号的Ram Buffer中
#define CMD_DEL_CHAR				0x0044			//删除指定编号范围内的Template
#define CMD_GET_EMPTY_ID			0x0045			//获取指定范围内可注册的(没有注册的)第一个模板编号
#define CMD_GET_STATUS				0x0046			//获取指定编号的模板注册状态
#define CMD_GET_BROKEN_ID			0x0047			//检查指定编号范围内的所有指纹模板是否存在坏损的情况
#define CMD_GET_ENROLL_COUNT		0x0048			//获取指定编号范围内已注册的模板个数
#define CMD_GENERATE				0x0060			//将ImageBuffer中的指纹图像生成模板数据，并保存于指定编号的Ram Buffer中
#define CMD_MERGE					0x0061			//将保存于Ram Buffer中的两或三个模板数据融合成一个模板数据
#define CMD_MATCH					0x0062			//指定Ram Buffer中的两个指纹模板之间进行1:1比对
#define CMD_SEARCH					0x0063			//指定Ram Buffer中的模板与指纹库中指定编号范围内的所有模板之间进行1:N比对
#define CMD_VERIFY					0x0064			//指定Ram Buffer中的指纹模板与指纹库中指定编号的指纹模板之间进行1:1比对
#define CMD_SET_MODULE_SN			0x0008			//在设备中设置模块序列号信息(Module SN)
#define CMD_GET_MODULE_SN			0x0009			//获取本设备的模块序列号(Module SN)
#define CMD_FP_CANCEL				0x0025			//取消指纹采集操作(只适用于带TimeOut参数的滑动传感器)
#define CMD_GET_ENROLLED_ID_LIST	0x0049			//获取已注册User ID列表
#define CMD_ENTER_STANDY_STATE		0x000C			//使模块进入休眠状态(有些模块不支持休眠功能，虽然模块响应指令返回成功)


















#endif
