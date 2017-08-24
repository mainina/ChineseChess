#pragma once

enum CmdType
{
	// Login Command
	LCommand = 1001,
	// Login Rec Command
	LRCommand = 1002,
	// Move Command
	MCommand = 2001,
	// Move Rec Command
	MRCommand = 2002,
	// Select Room Command
	SRCommand = 3001,
	// Select Room Rec Command
	SRRCommand = 3002,
	// Select Desk Command
	SDCommand = 4001,
	// Select Desk Rec Command
	SDRCommand = 4002,
	// Start Chess Command
	SCCommand = 5001,
	// Start Chess Rec Command
	SCRCommand = 5002,
	// Authorize Error Command
	AECommand = 6001,
	// go to war command
	GTWCommand = 7001,
	// go to war rec command
	GTWRCommand = 7002
};

const char chBegin = 0x02;
const char chEnd = 0x03;