#ifndef SSP_MPDModule_H
#define SSP_MPDModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"

class SSP_MPDModule	: public ModuleFrame
{
public:
	SSP_MPDModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pSSPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", (BaseAddr>>19) & 0x1F);
	}

	void SetupRegisters()
	{
#define SSP_SDIOMUX_NAME_MAP		{\
											28,\
											{"0","1","SYNC","TRIG1","TRIG2","FPIN0","FPIN1","FPIN2","FPIN3","FPIN4","P2IN0","P2IN1","P2IN2","P2IN3","P2IN4","P2IN5","P2IN6","P2IN7","PULSER","BUSY","TRIGBIT0","TRIGBIT1","TRIGBIT2","TRIGBIT3","TRIGBIT4","TRIGBIT5","TRIGBIT6","TRIGBIT7"},\
											{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27}\
										}

		static RegMemDesc regs[] = {
			{"Config", 0},
				{"Spi", 0},
					{"WrData",				REGMEM_DESC_FLAGS_HEX,		{0x0008, 0, 8, 32}},
					{"RdData",				REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 8, 32}},
					{"NCSSet",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 8, 1, 32}},
					{"NCSClear",			REGMEM_DESC_FLAGS_UINT,		{0x0008, 9, 1, 32}},
					{"Start",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 10, 1, 32}},
					{"Done",					REGMEM_DESC_FLAGS_UINT,		{0x000C, 11, 1, 32}},
				{NULL, 0},
				{"BoardId",					REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{"FirmwareRev",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
				{"SoftReset",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 0, 1, 32}},
			{NULL, 0},
			{"Clk", 0},
				{"Drp", 0},
					{"Addr",				REGMEM_DESC_FLAGS_HEX,		{0x0100, 16, 5, 32}},
					{"WrEn",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 21, 1, 32}},
					{"Den",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 22, 1, 32}},
					{"WrData",			REGMEM_DESC_FLAGS_HEX,		{0x0100, 0, 16, 32}},
					{"RdData",			REGMEM_DESC_FLAGS_HEX,		{0x0104, 0, 16, 32}},
					{"RdDataValid",	REGMEM_DESC_FLAGS_UINT,		{0x0104, 16, 1, 32}},
				{NULL, 0},
				{"ClkSerdes",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 24, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
				{"ClkLogic",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 26, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
				{"ClkPllReset",		REGMEM_DESC_FLAGS_UINT,		{0x0100, 31, 1, 32}},
				{"ClkPllLocked",		REGMEM_DESC_FLAGS_UINT,		{0x0104, 17, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"I/O Muxing", 0},
					{"FpOut0",					REGMEM_DESC_FLAGS_STRING,	{0x0200, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut1",					REGMEM_DESC_FLAGS_STRING,	{0x0204, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut2",					REGMEM_DESC_FLAGS_STRING,	{0x0208, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut3",					REGMEM_DESC_FLAGS_STRING,	{0x020C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut4",					REGMEM_DESC_FLAGS_STRING,	{0x0210, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Gpio0",					REGMEM_DESC_FLAGS_STRING,	{0x0214, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Gpio1",					REGMEM_DESC_FLAGS_STRING,	{0x0218, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out0",					REGMEM_DESC_FLAGS_STRING,	{0x021C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out1",					REGMEM_DESC_FLAGS_STRING,	{0x0220, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out2",					REGMEM_DESC_FLAGS_STRING,	{0x0224, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out3",					REGMEM_DESC_FLAGS_STRING,	{0x0228, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out4",					REGMEM_DESC_FLAGS_STRING,	{0x022C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out5",					REGMEM_DESC_FLAGS_STRING,	{0x0230, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out6",					REGMEM_DESC_FLAGS_STRING,	{0x0234, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out7",					REGMEM_DESC_FLAGS_STRING,	{0x0238, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Trig",						REGMEM_DESC_FLAGS_STRING,	{0x023C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Sync",						REGMEM_DESC_FLAGS_STRING,	{0x0240, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x0280, 0, 32, 32}},
					{"LowCycles",				REGMEM_DESC_FLAGS_UINT,		{0x0284, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x0288, 0, 32, 32}},
					{"Start",					REGMEM_DESC_FLAGS_UINT,		{0x028C, 0, 0, 32}},
					{"Done",						REGMEM_DESC_FLAGS_UINT,		{0x0290, 0, 1, 32}},
				{NULL, 0},
				{"Scalers", 0},
					{"Disable",					REGMEM_DESC_FLAGS_UINT,		{0x0300, 0, 1, 32}},
					{"SysClk50",				REGMEM_DESC_FLAGS_UINT,		{0x0304, 0, 32, 32}},
					{"GClk250",					REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"Sync",						REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"Trig1",					REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 32, 32}},
					{"Trig2",					REGMEM_DESC_FLAGS_UINT,		{0x0314, 0, 32, 32}},
					{"Gpio0",					REGMEM_DESC_FLAGS_UINT,		{0x0318, 0, 32, 32}},
					{"Gpio1",					REGMEM_DESC_FLAGS_UINT,		{0x031C, 0, 32, 32}},
					{"FpIn0",					REGMEM_DESC_FLAGS_UINT,		{0x0320, 0, 32, 32}},
					{"FpIn1",					REGMEM_DESC_FLAGS_UINT,		{0x0324, 0, 32, 32}},
					{"FpIn2",					REGMEM_DESC_FLAGS_UINT,		{0x0328, 0, 32, 32}},
					{"FpIn3",					REGMEM_DESC_FLAGS_UINT,		{0x032C, 0, 32, 32}},
					{"FpIn4",					REGMEM_DESC_FLAGS_UINT,		{0x0330, 0, 32, 32}},
					{"FpOut0",					REGMEM_DESC_FLAGS_UINT,		{0x0334, 0, 32, 32}},
					{"FpOut1",					REGMEM_DESC_FLAGS_UINT,		{0x0338, 0, 32, 32}},
					{"FpOut2",					REGMEM_DESC_FLAGS_UINT,		{0x033C, 0, 32, 32}},
					{"FpOut3",					REGMEM_DESC_FLAGS_UINT,		{0x0340, 0, 32, 32}},
					{"FpOut4",					REGMEM_DESC_FLAGS_UINT,		{0x0344, 0, 32, 32}},
					{"Busy",						REGMEM_DESC_FLAGS_UINT,		{0x0348, 0, 32, 32}},
					{"BusyCycles",				REGMEM_DESC_FLAGS_UINT,		{0x034C, 0, 32, 32}},
					{"P2In0",					REGMEM_DESC_FLAGS_UINT,		{0x0350, 0, 32, 32}},
					{"P2In1",					REGMEM_DESC_FLAGS_UINT,		{0x0354, 0, 32, 32}},
					{"P2In2",					REGMEM_DESC_FLAGS_UINT,		{0x0358, 0, 32, 32}},
					{"P2In3",					REGMEM_DESC_FLAGS_UINT,		{0x035C, 0, 32, 32}},
					{"P2In4",					REGMEM_DESC_FLAGS_UINT,		{0x0360, 0, 32, 32}},
					{"P2In5",					REGMEM_DESC_FLAGS_UINT,		{0x0364, 0, 32, 32}},
					{"P2In6",					REGMEM_DESC_FLAGS_UINT,		{0x0368, 0, 32, 32}},
					{"P2In7",					REGMEM_DESC_FLAGS_UINT,		{0x036C, 0, 32, 32}},
					{"P2Out0",					REGMEM_DESC_FLAGS_UINT,		{0x0370, 0, 32, 32}},
					{"P2Out1",					REGMEM_DESC_FLAGS_UINT,		{0x0374, 0, 32, 32}},
					{"P2Out2",					REGMEM_DESC_FLAGS_UINT,		{0x0378, 0, 32, 32}},
					{"P2Out3",					REGMEM_DESC_FLAGS_UINT,		{0x037C, 0, 32, 32}},
					{"P2Out4",					REGMEM_DESC_FLAGS_UINT,		{0x0380, 0, 32, 32}},
					{"P2Out5",					REGMEM_DESC_FLAGS_UINT,		{0x0384, 0, 32, 32}},
					{"P2Out6",					REGMEM_DESC_FLAGS_UINT,		{0x0388, 0, 32, 32}},
					{"P2Out7",					REGMEM_DESC_FLAGS_UINT,		{0x038C, 0, 32, 32}},
				{NULL, 0},
			{NULL, 0},
			{"Event Builder", 0},
				{"Lookback",					REGMEM_DESC_FLAGS_UINT,		{0x2000, 0, 10, 32}},
				{"WindowWidth",				REGMEM_DESC_FLAGS_UINT,		{0x2004, 0, 10, 32}},
				{"BlockSize",					REGMEM_DESC_FLAGS_UINT,		{0x2008, 0, 8, 32}},
				{"Adr32Base",					REGMEM_DESC_FLAGS_HEX,		{0x200C, 7, 9, 32}},
				{"Adr32En",						REGMEM_DESC_FLAGS_UINT,		{0x200C, 0, 1, 32}},
				{"Adr32Mmin",					REGMEM_DESC_FLAGS_HEX,		{0x2010, 0, 9, 32}},
				{"Adr32Mmax",					REGMEM_DESC_FLAGS_HEX,		{0x2010, 16, 9, 32}},
				{"Adr32Men",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 25, 1, 32}},
				{"TokenFirst",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 26, 1, 32}},
				{"TokenLast",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 27, 1, 32}},
				{"TokenTake",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 28, 1, 32}},
				{"BerrEn",						REGMEM_DESC_FLAGS_UINT,		{0x2018, 0, 1, 32}},
				{"FifoBlockCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2020, 0, 32, 32}},
				{"FifoWordCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2024, 0, 32, 32}},
				{"FifoEventCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2028, 0, 32, 32}},
			{NULL, 0},
			{"MPD", 0},
				{"MPD 0", 0},
					{"GTReset",					REGMEM_DESC_FLAGS_UINT,		{0x3000, 0, 1, 32}},
					{"LinkReset",				REGMEM_DESC_FLAGS_UINT,		{0x3000, 1, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x3010, 0, 1, 32}},
					{"HardError",				REGMEM_DESC_FLAGS_UINT,		{0x3010, 1, 1, 32}},
					{"FrameError",				REGMEM_DESC_FLAGS_UINT,		{0x3010, 2, 1, 32}},
					{"SoftErrors",				REGMEM_DESC_FLAGS_UINT,		{0x3010, 8, 8, 32}},
					{"EBEnabled",				REGMEM_DESC_FLAGS_UINT,		{0x3020, 0, 1, 32}},
				{NULL, 0},
				{"MPD 1", 0},
					{"GTReset",					REGMEM_DESC_FLAGS_UINT,		{0x3100, 0, 1, 32}},
					{"LinkReset",				REGMEM_DESC_FLAGS_UINT,		{0x3100, 1, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x3110, 0, 1, 32}},
					{"HardError",				REGMEM_DESC_FLAGS_UINT,		{0x3110, 1, 1, 32}},
					{"FrameError",				REGMEM_DESC_FLAGS_UINT,		{0x3110, 2, 1, 32}},
					{"SoftErrors",				REGMEM_DESC_FLAGS_UINT,		{0x3110, 8, 8, 32}},
					{"EBEnabled",				REGMEM_DESC_FLAGS_UINT,		{0x3120, 0, 1, 32}},
				{NULL, 0},
				{"MPD 2", 0},
					{"GTReset",					REGMEM_DESC_FLAGS_UINT,		{0x3200, 0, 1, 32}},
					{"LinkReset",				REGMEM_DESC_FLAGS_UINT,		{0x3200, 1, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x3210, 0, 1, 32}},
					{"HardError",				REGMEM_DESC_FLAGS_UINT,		{0x3210, 1, 1, 32}},
					{"FrameError",				REGMEM_DESC_FLAGS_UINT,		{0x3210, 2, 1, 32}},
					{"SoftErrors",				REGMEM_DESC_FLAGS_UINT,		{0x3210, 8, 8, 32}},
					{"EBEnabled",				REGMEM_DESC_FLAGS_UINT,		{0x3210, 0, 1, 32}},
				{NULL, 0},
				{"MPD 3", 0},
					{"GTReset",					REGMEM_DESC_FLAGS_UINT,		{0x3300, 0, 1, 32}},
					{"LinkReset",				REGMEM_DESC_FLAGS_UINT,		{0x3300, 1, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x3310, 0, 1, 32}},
					{"HardError",				REGMEM_DESC_FLAGS_UINT,		{0x3310, 1, 1, 32}},
					{"FrameError",				REGMEM_DESC_FLAGS_UINT,		{0x3310, 2, 1, 32}},
					{"SoftErrors",				REGMEM_DESC_FLAGS_UINT,		{0x3310, 8, 8, 32}},
					{"EBEnabled",				REGMEM_DESC_FLAGS_UINT,		{0x3320, 0, 1, 32}},
				{NULL, 0},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "SSP_MPD"; }
	const char *GetModuleFullName() { return "Sub System Processor-MPD"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pSSPTabs;
};

#endif
