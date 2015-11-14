/*
 * SnifferMain.cpp
 *
 *  Created on: 2014年3月3日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#include "SnifferMain.h"

int main(int argc, char** argv) {
	char stra[16] = {'\0'};
	sprintf(stra, "%d", argc);

	if(2 == argc) {
		if(0 == strcmp(argv[1], "-v")) {
			printf("%s%s%s\n", SinfferVersionString, SnifferVersion, SnifferVersionEnd);
			return 0;
		}
	}

	int uid = 0, gid = 0;
	if(setgid(gid) || setuid(uid)) {
		ELog("sniffer", "权限不够, 请提升至管理员权限再运行程序!");
		return 0;
	}

	if( !MountSystem() ) {
		ELog("sniffer", "重新挂载/system失败, 日志文件可能无法保存!");
	}

	KLog::SetLogDirectory("/sdcard/sniffer/");
	FileLog(SnifferLogFileName, "sniffer启动, 版本:%s", SnifferVersion);

	SnifferMain sniffer;
	if( sniffer.Run() ) {
		while(1) {
			sleep(3);
		}
	}

	FileLog(SnifferLogFileName, "sniffer退出!");
	return 1;
}