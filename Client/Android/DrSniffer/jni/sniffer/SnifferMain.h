/*
 * SnifferMain.h
 *
 *  Created on: 2015-11-14
 *      Author: Max
 */

#ifndef SNIFFERMAIN_H_
#define SNIFFERMAIN_H_

#include "Sniffer.h"
#include "SnifferClient.h"

#include <common/command.h>

class SnifferMain : public SnifferClientCallback {
public:
	SnifferMain();
	virtual ~SnifferMain();

	/**
	 * Implement from SnifferClientCallback
	 */
	void OnRecvCommand(SnifferClient* client, const SCMD &scmd);

	bool Run();

private:
	Sniffer mSniffer;
	SnifferClient mSnifferClient;
};

#endif /* SNIFFERMAIN_H_ */