/*
 * SnifferMain.cpp
 *
 *  Created on: 2014年3月3日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#include "SnifferMain.h"

#include <crashhandler/CrashHandler.h>

static void sig_handler(int signum) {
	FileLog(SnifferLogFileName, "sig_handler : %d", signum);
}

int main(int argc, char** argv) {
	KLog::SetLogDirectory("/sdcard/sniffer/");
	CrashHandler::GetInstance()->SetCrashLogDirectory("/sdcard/sniffer/");

	FileLog(SnifferLogFileName, "############## %s ##############", SinfferFile);
	FileLog(SnifferLogFileName, "%s启动, 版本:%s", SinfferFile, SnifferVersion);
	FileLog(SnifferLogFileName, "Build date : %s %s", __DATE__, __TIME__ );

	/* Ignore SIGPIPE */
	struct sigaction sa;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGPIPE, &sa, 0);
	for(int i = 1; i <= NSIG; i++) {
		sigaction(i, &sa, 0);
	}

	char stra[16] = {'\0'};
	sprintf(stra, "%d", argc);

	if(2 == argc) {
		if(0 == strcmp(argv[1], "-v")) {
			printf("%s%s%s\n", SinfferVersionString, SnifferVersion, SnifferVersionEnd);
			return 0;
		}
	}

	int uid = 0, gid = 0;
	if( ( setgid(gid) < 0 ) || ( setuid(uid) < 0 ) ) {
		FileLog(SnifferLogFileName, "权限不够, 部分功能可能缺失!");
	}
	FileLog(SnifferLogFileName, "uid:%d", getuid());

	if( !MountSystem() ) {
		FileLog(SnifferLogFileName, "重新挂载/system失败, 部分功能可能缺失!");
	}

	SnifferMain sniffer;
	if( sniffer.Run() ) {
		while(1) {
			sleep(3);
		}
	}

	FileLog(SnifferLogFileName, "%s退出!", SinfferFile);
	return 1;
}
