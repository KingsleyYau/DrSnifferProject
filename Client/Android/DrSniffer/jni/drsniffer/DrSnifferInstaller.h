/*
 * DrSnifferInstaller.h
 *
 *  Created on: 2014年3月17日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#ifndef DRSNIFFERINSTALLER_H_
#define DRSNIFFERINSTALLER_H_

#include "DrSinfferExecuteDef.h"

/*
 * 查看DrHttpFS版本
 * 用于检测DrHttpFS是否存在
 */
static inline string GetDrHttpFSVersion() {
	string version = "";

	string suCommand = DrHttpFSFile;
	suCommand += " -V";

	string result = "";
	result = SystemComandExecuteWithResult(suCommand);

	string::size_type posStart = 0;
	string::size_type posEnd = string::npos;
	int iLen = 0;

	if(result.length() > 0) {
		string::size_type pos = result.find(DrHttpFSFileVersionString);
		if(string::npos != pos) {
			ILog("jni.DrSnifferExecuteDef::GetHttpFSVersion()", "已经安装%s!", DrHttpFSFile);
			pos += strlen(DrHttpFSFileVersionString);
			posStart = pos;

			posEnd = result.find(' ', posStart);
			if(string::npos != posEnd) {
				iLen = posEnd - posStart;
			}
			else {
				iLen = result.length() - posStart - 1;
			}
			version = result.substr(posStart, iLen);
			ILog("jni.DrSnifferExecuteDef::GetHttpFSVersion()", "%s版本为%s", DrHttpFSFile, version.c_str());
		}
		else {
			ILog("jni.DrSnifferExecuteDef::GetHttpFSVersion()", "还没安装%s", DrHttpFSFile);
		}
	}
	else {
		ILog("jni.DrSnifferExecuteDef::GetDrHttpFSVersion()", "还没安装%s", DrHttpFSFile);
	}

	return version;
}

/*
 * 查看DrCurl版本
 * 用于检测DrCurl是否存在
 */
static inline string GetDrCurlVersion() {
	string version = "";

	string suCommand = DrCurlFile;
	suCommand += " --version";

	string result = "";
	result = SystemComandExecuteWithResult(suCommand);

	string::size_type posStart = 0;
	string::size_type posEnd = string::npos;
	int iLen = 0;

	if(result.length() > 0) {
		string::size_type pos = result.find(DrCurlFileVersionString);
		if(string::npos != pos) {
			ILog("jni.DrSnifferExecuteDef::GetDrCurlVersion()", "已经安装%s!", DrCurlFile);
			pos += strlen(DrCurlFileVersionString);
			posStart = pos;

			posEnd = result.find(' ', posStart);
			if(string::npos != posEnd) {
				iLen = posEnd - posStart;
			}
			else {
				iLen = result.length() - posStart - 1;
			}
			version = result.substr(posStart, iLen);
			ILog("jni.DrSnifferExecuteDef::GetDrCurlVersion()", "%s版本为%s", DrCurlFile, version.c_str());
		}
		else {
			ILog("jni.DrSnifferExecuteDef::GetDrCurlVersion()", "还没安装%s", DrCurlFile);
		}
	}
	else {
		ILog("jni.DrSnifferExecuteDef::GetDrCurlVersion()", "还没安装%s", DrCurlFile);
	}

	return version;
}

/*
 * 查看DrSniffer版本
 * 用于检测DrSniffer是否存在
 */
static inline string GetDrSnifferVersion() {
	string version = "";

	string suCommand = DrSinfferFile;
	suCommand += " -v";

	string result = "";
	result = SystemComandExecuteWithResult(suCommand);

	string::size_type posStart = 0;
	string::size_type posEnd = string::npos;
	int iLen = 0;

	if(result.length() > 0) {
		string::size_type pos = result.find(DrSinfferVersionString);
		if(string::npos != pos) {
			ILog("jni.DrSnifferExecuteDef::GetDrSnifferVersion()", "已经安装%s!", DrSinfferFile);
			pos += strlen(DrSinfferVersionString);
			posStart = pos;

			posEnd = result.find(' ', posStart);
			if(string::npos != posEnd) {
				iLen = posEnd - posStart;
			}
			else {
				iLen = result.length() - posStart - 1;
			}
			version = result.substr(posStart, iLen);
			ILog("jni.DrSnifferExecuteDef::GetDrSnifferVersion()", "%s版本为%s", DrSinfferFile, version.c_str());
		}
		else {
			ILog("jni.DrSnifferExecuteDef::GetDrSnifferVersion()", "还没安装%s", DrSinfferFile);
		}
	}
	else {
		ILog("jni.DrSnifferExecuteDef::GetDrSnifferVersion()", "还没安装%s", DrSinfferFile);
	}

	return version;
}

/*
 * 释放DrSniffer到指定路径
 */
static inline string ReleaseDrSniffer(string filePath = "/sdcard/") {
	string result = "";

	if(filePath.find_last_of('/') != filePath.length() - 1) {
		filePath += "/";
	}

	filePath += DrSinfferFile;
	ILog("jni.DrSnifferExecuteDef::ReleaseDrSniffer()", "准备释放释放DrSniffer到:%s", filePath.c_str());

	FILE* file = fopen(filePath.c_str(), "wb+");
	if(NULL != file) {
		char *p = (char *)DrSinfferExcute;
		int iLen = sizeof(DrSinfferExcute);
		ILog("jni.DrSnifferExecuteDef::ReleaseDrSniffer()", "文件大小:(%d)byte", iLen);
		int iWrite = 0;
		do {
			int iNeedWrite = (4096 > iLen)?iLen:4096;
			iWrite = fwrite(p, 1, iNeedWrite, file);
			if(iWrite > 0) {
				p += iWrite;
				iLen -= iWrite;
			}
		}while(iLen > 0);
		fclose(file);
		result = filePath;
		ILog("jni.DrSnifferExecuteDef::ReleaseDrSniffer()", "释放DrSniffer到%s成功!", filePath.c_str());
	}
	else {
		ELog("jni.DrSnifferExecuteDef::ReleaseDrSniffer()", "释放DrSniffer到%s失败!", filePath.c_str());
	}

	return result;
}

/*
 * 释放AutoStartScript到指定路径
 */
static inline string ReleaseAutoStartScript(string filePath = "/sdcard/") {
	string result = "";

	if(filePath.find_last_of('/') != filePath.length() - 1) {
		filePath += "/";
	}

	filePath += AutoStartScriptFile;
	ILog("jni.DrSnifferExecuteDef::ReleaseAutoStartScript()", "准备释放释放AutoStartScript到:%s", filePath.c_str());

	FILE* file = fopen(filePath.c_str(), "wb+");
	if(NULL != file) {
		char *p = (char *)AutoStartScript;
		int iLen = sizeof(AutoStartScript);
		ILog("jni.DrSnifferExecuteDef::ReleaseAutoStartScript()", "文件大小:(%d)byte", iLen);
		int iWrite = 0;
		do {
			int iNeedWrite = (4096 > iLen)?iLen:4096;
			iWrite = fwrite(p, 1, iNeedWrite, file);
			if(iWrite > 0) {
				p += iWrite;
				iLen -= iWrite;
			}
		}while(iLen > 0);
		fclose(file);
		result = filePath;
		ILog("jni.DrSnifferExecuteDef::ReleaseAutoStartScript()", "释放AutoStartScript到%s成功!", filePath.c_str());
	}
	else {
		ELog("jni.DrSnifferExecuteDef::ReleaseAutoStartScript()", "释放AutoStartScript到%s失败!", filePath.c_str());
	}

	return result;
}

/*
 * 完整安装DrSniffer
 * packageName:	安装器包名, 如com.drcom.drsnifferinstaller
 * filePath: 临时可写路径, 如/sdcard/
 */
static inline bool InstallDrSniffer(string packageName, string filePath) {
	bool bFlag = false;

	char pBuffer[2048] = {'\0'};
	string curVersion = "";
	string libPath = DrRelaseFilePrefix + packageName + DrRelaseFileLib;
	string releaseFile = "";

	ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "开始安装依赖包...");

	// 判断是否需要安装curl
	ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "判断是否需要安装%s...", DrCurlFile);
	curVersion = GetDrCurlVersion();
	if(curVersion.compare(DrCurlVersion) >= 0) {
		// 不需要升级
		ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "%s当前版本:(%s) 安装包版本:(%s)要新,不需要升级!", DrCurlFile, curVersion.c_str(), DrCurlVersion);
	}
	else {
		releaseFile = libPath + DrCurlInStallerFile;
		bool bFlag1 = RootExecutableFile(releaseFile, "/system/bin/", DrCurlFile);
		if(bFlag1) {
			// 安装curl成功
			ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装%s成功,版本为:(%s)", DrCurlFile, DrCurlVersion);
		}
		else {
			ELog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装%s失败!", DrCurlFile);
		}
	}

//	// 判断是否需要安装drhttpfs
//	ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "判断是否需要安装%s...", DrHttpFSFile);
//	curVersion = GetDrHttpFSVersion();
//	if(curVersion.compare(DrHttpFSVersion) >= 0) {
//		// 不需要升级
//		ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "%s当前版本:(%s) 安装包版本:(%s)要新,不需要升级!", DrHttpFSFile, curVersion.c_str(), DrHttpFSVersion);
//	}
//	else {
//		releaseFile = libPath + DrHttpFSInStallerFile;
//		bool bFlag1 = RootExecutableFile(releaseFile, "/system/bin/", DrHttpFSFile);
//		if(bFlag1) {
//			// 安装curl成功
//			ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装%s成功,版本为:(%s)", DrHttpFSFile, DrHttpFSVersion);
//		}
//		else {
//			ELog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装%s失败!", DrHttpFSFile);
//		}
//	}

	ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "所有依赖包安装完成!");

	// 判断是否需要安装或者升级
	ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "开始安装DrSniffer,判断是否需要安装或者升级...");
	curVersion = GetDrSnifferVersion();
	if(curVersion.compare(DrSnifferVersion) >= 0) {
		// 不需要升级
		ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "%s当前版本:(%s) 安装包版本:(%s)要新,不需要升级!", DrSinfferFile, curVersion.c_str(), DrSnifferVersion);
		bFlag = true;
	}
	else {
		ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "开始安装DrSniffer, 版本为:%s", DrSnifferVersion);

		// 拷贝DrSniffer到系统目录
		releaseFile = libPath + DrSnifferInStallerFile;
		bool bFlag1 = RootExecutableFile(releaseFile, "/system/bin/", DrSinfferFile);
		if(bFlag1) {
			ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装DrSniffer成功!");
			// 安装DrSniffer成功, 继续释放自动启动脚本
			ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "释放自动启动脚...");
			releaseFile = ReleaseAutoStartScript(filePath);

			if(releaseFile.length() > 0) {
				// 拷贝AutoStartScript到系统目录
				bFlag = RootExecutableFile(releaseFile, "/etc/");
				if(bFlag) {
					ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "安装DrSniffer自启动脚本成功!");
				}
				// 删除临时目录下AutoStartScript
				sprintf(pBuffer, "rm %s", releaseFile.c_str());
				SystemComandExecute(pBuffer);
			}
		}
		else {
			return false;
		}
	}

	if(bFlag) {
		// 如果在运行先关闭
		int iPid = -1;
		while(-1 != (iPid = GetProcessPid(DrSinfferFile))) {
			ILog("jni.command::RootExecutableFile", "发现%s(PID:%d)正在运行, 先杀掉!", DrSinfferFile, iPid);
			sprintf(pBuffer, "kill -9 %d", iPid);
			SystemComandExecuteWithRoot(pBuffer);
		}

		ILog("jni.command::RootExecutableFile", "重新启动DrSniffer...");
		SystemComandExecuteWithRoot("(drsniffer &)");
		ILog("jni.DrSnifferExecuteDef::InstallDrSniffer()", "DrSniffer启动成功!");
	}

	return bFlag;
}


#endif /* DRSNIFFERINSTALLER_H_ */
