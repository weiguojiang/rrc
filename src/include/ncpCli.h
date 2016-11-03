/**************************************************************************
 **                                                                       *
 **   LSI Corporation, Inc.     CONFIDENTIAL                              *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of LSI Corporation Inc.*
 **    (c) 2008-2011, LSI Corporation Inc.  All rights reserved.          *
 **                                                                       *
 **  **********************************************************************
 **
 **   File:       : $
 **   Version:    : $
 **   Date:       : $
 **
 **************************************************************************/

#ifndef _NCPCLI_H_
#define _NCPCLI_H_

#if     !defined(DOXYGEN)

#ifndef SWIG
#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

#include "ncp.h"
#else
%header
%{
#include "ncp.h"
#include "ncpCli.h"
%}
NCP_SETUP();
#endif /* #ifndef SWIG */


#if !defined(SWIG)
NCP_API int ncpDpiLoad(char *cmdArgs);
NCP_API int ncpDpiLoadMain(int argc, const char *argv[]);
#else
%rename(ncpDpiLoad) ncpDpiLoadMain;
NCP_API int ncpDpiLoadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSysmemPhyStatusShow(char *cmdArgs);
NCP_API int ncpSysmemPhyStatusShowMain(int argc, const char *argv[]);
#else
%rename(ncpSysmemPhyStatusShow) ncpSysmemPhyStatusShowMain;
NCP_API int ncpSysmemPhyStatusShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSetRev(char *cmdArgs);
NCP_API int ncpSetRevMain(int argc, const char *argv[]);
#else
%rename(ncpSetRev) ncpSetRevMain;
NCP_API int ncpSetRevMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonQuery(char *cmdArgs);
NCP_API int ncpSmonQueryMain(int argc, const char *argv[]);
#else
%rename(ncpSmonQuery) ncpSmonQueryMain;
NCP_API int ncpSmonQueryMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpBcastFill(char *cmdArgs);
NCP_API int ncpBcastFillMain(int argc, const char *argv[]);
#else
%rename(ncpBcastFill) ncpBcastFillMain;
NCP_API int ncpBcastFillMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacMtuRead(char *cmdArgs);
NCP_API int ncpMacMtuReadMain(int argc, const char *argv[]);
#else
%rename(ncpMacMtuRead) ncpMacMtuReadMain;
NCP_API int ncpMacMtuReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmAutoZqcsStart(char *cmdArgs);
NCP_API int ncpSmAutoZqcsStartMain(int argc, const char *argv[]);
#else
%rename(ncpSmAutoZqcsStart) ncpSmAutoZqcsStartMain;
NCP_API int ncpSmAutoZqcsStartMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaSlotOvrclkSet(char *cmdArgs);
NCP_API int ncpEioaSlotOvrclkSetMain(int argc, const char *argv[]);
#else
%rename(ncpEioaSlotOvrclkSet) ncpEioaSlotOvrclkSetMain;
NCP_API int ncpEioaSlotOvrclkSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaVPidWrite(char *cmdArgs);
NCP_API int ncpEioaVPidWriteMain(int argc, const char *argv[]);
#else
%rename(ncpEioaVPidWrite) ncpEioaVPidWriteMain;
NCP_API int ncpEioaVPidWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonStop(char *cmdArgs);
NCP_API int ncpSmonStopMain(int argc, const char *argv[]);
#else
%rename(ncpSmonStop) ncpSmonStopMain;
NCP_API int ncpSmonStopMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskSend(char *cmdArgs);
NCP_API int ncpTaskSendMain(int argc, const char *argv[]);
#else
%rename(ncpTaskSend) ncpTaskSendMain;
NCP_API int ncpTaskSendMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaSwitchStatistics(char *cmdArgs);
NCP_API int ncpEioaSwitchStatisticsMain(int argc, const char *argv[]);
#else
%rename(ncpEioaSwitchStatistics) ncpEioaSwitchStatisticsMain;
NCP_API int ncpEioaSwitchStatisticsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskShutdown(char *cmdArgs);
NCP_API int ncpTaskShutdownMain(int argc, const char *argv[]);
#else
%rename(ncpTaskShutdown) ncpTaskShutdownMain;
NCP_API int ncpTaskShutdownMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmZqCalibrateStop(char *cmdArgs);
NCP_API int ncpSmZqCalibrateStopMain(int argc, const char *argv[]);
#else
%rename(ncpSmZqCalibrateStop) ncpSmZqCalibrateStopMain;
NCP_API int ncpSmZqCalibrateStopMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSeFemEventsGet(char *cmdArgs);
NCP_API int ncpSeFemEventsGetMain(int argc, const char *argv[]);
#else
%rename(ncpSeFemEventsGet) ncpSeFemEventsGetMain;
NCP_API int ncpSeFemEventsGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpI2cEepromUtil(char *cmdArgs);
NCP_API int ncpI2cEepromUtilMain(int argc, const char *argv[]);
#else
%rename(ncpI2cEepromUtil) ncpI2cEepromUtilMain;
NCP_API int ncpI2cEepromUtilMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacAutoNegSet(char *cmdArgs);
NCP_API int ncpMacAutoNegSetMain(int argc, const char *argv[]);
#else
%rename(ncpMacAutoNegSet) ncpMacAutoNegSetMain;
NCP_API int ncpMacAutoNegSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpBcastWrite(char *cmdArgs);
NCP_API int ncpBcastWriteMain(int argc, const char *argv[]);
#else
%rename(ncpBcastWrite) ncpBcastWriteMain;
NCP_API int ncpBcastWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpAnd(char *cmdArgs);
NCP_API int ncpAndMain(int argc, const char *argv[]);
#else
%rename(ncpAnd) ncpAndMain;
NCP_API int ncpAndMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpApiTraceDump(char *cmdArgs);
NCP_API int ncpApiTraceDumpMain(int argc, const char *argv[]);
#else
%rename(ncpApiTraceDump) ncpApiTraceDumpMain;
NCP_API int ncpApiTraceDumpMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMdioWrite(char *cmdArgs);
NCP_API int ncpMdioWriteMain(int argc, const char *argv[]);
#else
%rename(ncpMdioWrite) ncpMdioWriteMain;
NCP_API int ncpMdioWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCfgTool(char *cmdArgs);
NCP_API int ncpCfgToolMain(int argc, const char *argv[]);
#else
%rename(ncpCfgTool) ncpCfgToolMain;
NCP_API int ncpCfgToolMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpDeviceInfo(char *cmdArgs);
NCP_API int ncpDeviceInfoMain(int argc, const char *argv[]);
#else
%rename(ncpDeviceInfo) ncpDeviceInfoMain;
NCP_API int ncpDeviceInfoMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpNvmStatsGet(char *cmdArgs);
NCP_API int ncpNvmStatsGetMain(int argc, const char *argv[]);
#else
%rename(ncpNvmStatsGet) ncpNvmStatsGetMain;
NCP_API int ncpNvmStatsGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacStatistics(char *cmdArgs);
NCP_API int ncpMacStatisticsMain(int argc, const char *argv[]);
#else
%rename(ncpMacStatistics) ncpMacStatisticsMain;
NCP_API int ncpMacStatisticsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTqsState(char *cmdArgs);
NCP_API int ncpTaskTqsStateMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTqsState) ncpTaskTqsStateMain;
NCP_API int ncpTaskTqsStateMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMtmNodeShow(char *cmdArgs);
NCP_API int ncpMtmNodeShowMain(int argc, const char *argv[]);
#else
%rename(ncpMtmNodeShow) ncpMtmNodeShowMain;
NCP_API int ncpMtmNodeShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSysmemLsiPhyRegDump(char *cmdArgs);
NCP_API int ncpSysmemLsiPhyRegDumpMain(int argc, const char *argv[]);
#else
%rename(ncpSysmemLsiPhyRegDump) ncpSysmemLsiPhyRegDumpMain;
NCP_API int ncpSysmemLsiPhyRegDumpMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskRecvV2(char *cmdArgs);
NCP_API int ncpTaskRecvV2Main(int argc, const char *argv[]);
#else
%rename(ncpTaskRecvV2) ncpTaskRecvV2Main;
NCP_API int ncpTaskRecvV2Main(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskDebug(char *cmdArgs);
NCP_API int ncpTaskDebugMain(int argc, const char *argv[]);
#else
%rename(ncpTaskDebug) ncpTaskDebugMain;
NCP_API int ncpTaskDebugMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpNsEntryRead(char *cmdArgs);
NCP_API int ncpNsEntryReadMain(int argc, const char *argv[]);
#else
%rename(ncpNsEntryRead) ncpNsEntryReadMain;
NCP_API int ncpNsEntryReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceLogShow(char *cmdArgs);
NCP_API int ncpTaskTraceLogShowMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceLogShow) ncpTaskTraceLogShowMain;
NCP_API int ncpTaskTraceLogShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacAddrRead(char *cmdArgs);
NCP_API int ncpMacAddrReadMain(int argc, const char *argv[]);
#else
%rename(ncpMacAddrRead) ncpMacAddrReadMain;
NCP_API int ncpMacAddrReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacPhyRegWrite(char *cmdArgs);
NCP_API int ncpMacPhyRegWriteMain(int argc, const char *argv[]);
#else
%rename(ncpMacPhyRegWrite) ncpMacPhyRegWriteMain;
NCP_API int ncpMacPhyRegWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceDisable(char *cmdArgs);
NCP_API int ncpTaskTraceDisableMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceDisable) ncpTaskTraceDisableMain;
NCP_API int ncpTaskTraceDisableMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpModify(char *cmdArgs);
NCP_API int ncpModifyMain(int argc, const char *argv[]);
#else
%rename(ncpModify) ncpModifyMain;
NCP_API int ncpModifyMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCowQueueDiscardStatsShow(char *cmdArgs);
NCP_API int ncpCowQueueDiscardStatsShowMain(int argc, const char *argv[]);
#else
%rename(ncpCowQueueDiscardStatsShow) ncpCowQueueDiscardStatsShowMain;
NCP_API int ncpCowQueueDiscardStatsShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpPortXoverTest(char *cmdArgs);
NCP_API int ncpPortXoverTestMain(int argc, const char *argv[]);
#else
%rename(ncpPortXoverTest) ncpPortXoverTestMain;
NCP_API int ncpPortXoverTestMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskSendV2(char *cmdArgs);
NCP_API int ncpTaskSendV2Main(int argc, const char *argv[]);
#else
%rename(ncpTaskSendV2) ncpTaskSendV2Main;
NCP_API int ncpTaskSendV2Main(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSpeedDuplexGet(char *cmdArgs);
NCP_API int ncpSpeedDuplexGetMain(int argc, const char *argv[]);
#else
%rename(ncpSpeedDuplexGet) ncpSpeedDuplexGetMain;
NCP_API int ncpSpeedDuplexGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskRecv(char *cmdArgs);
NCP_API int ncpTaskRecvMain(int argc, const char *argv[]);
#else
%rename(ncpTaskRecv) ncpTaskRecvMain;
NCP_API int ncpTaskRecvMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskDebugV2(char *cmdArgs);
NCP_API int ncpTaskDebugV2Main(int argc, const char *argv[]);
#else
%rename(ncpTaskDebugV2) ncpTaskDebugV2Main;
NCP_API int ncpTaskDebugV2Main(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCmdPPC(char *cmdArgs);
NCP_API int ncpCmdPPCMain(int argc, const char *argv[]);
#else
%rename(ncpCmdPPC) ncpCmdPPCMain;
NCP_API int ncpCmdPPCMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacAddrWrite(char *cmdArgs);
NCP_API int ncpMacAddrWriteMain(int argc, const char *argv[]);
#else
%rename(ncpMacAddrWrite) ncpMacAddrWriteMain;
NCP_API int ncpMacAddrWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTrngTest(char *cmdArgs);
NCP_API int ncpTrngTestMain(int argc, const char *argv[]);
#else
%rename(ncpTrngTest) ncpTrngTestMain;
NCP_API int ncpTrngTestMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpPkaTest(char *cmdArgs);
NCP_API int ncpPkaTestMain(int argc, const char *argv[]);
#else
%rename(ncpPkaTest) ncpPkaTestMain;
NCP_API int ncpPkaTestMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEcm(char *cmdArgs);
NCP_API int ncpEcmMain(int argc, const char *argv[]);
#else
%rename(ncpEcm) ncpEcmMain;
NCP_API int ncpEcmMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpBootMem(char *cmdArgs);
NCP_API int ncpBootMemMain(int argc, const char *argv[]);
#else
%rename(ncpBootMem) ncpBootMemMain;
NCP_API int ncpBootMemMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpXrt73Cfg(char *cmdArgs);
NCP_API int ncpXrt73CfgMain(int argc, const char *argv[]);
#else
%rename(ncpXrt73Cfg) ncpXrt73CfgMain;
NCP_API int ncpXrt73CfgMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpXrt73Read(char *cmdArgs);
NCP_API int ncpXrt73ReadMain(int argc, const char *argv[]);
#else
%rename(ncpXrt73Read) ncpXrt73ReadMain;
NCP_API int ncpXrt73ReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpXrt73Write(char *cmdArgs);
NCP_API int ncpXrt73WriteMain(int argc, const char *argv[]);
#else
%rename(ncpXrt73Write) ncpXrt73WriteMain;
NCP_API int ncpXrt73WriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacPauseRead(char *cmdArgs);
NCP_API int ncpMacPauseReadMain(int argc, const char *argv[]);
#else
%rename(ncpMacPauseRead) ncpMacPauseReadMain;
NCP_API int ncpMacPauseReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMmeMpcqPollingIntervalGet(char *cmdArgs);
NCP_API int ncpMmeMpcqPollingIntervalGetMain(int argc, const char *argv[]);
#else
%rename(ncpMmeMpcqPollingIntervalGet) ncpMmeMpcqPollingIntervalGetMain;
NCP_API int ncpMmeMpcqPollingIntervalGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpUnicastAddrRead(char *cmdArgs);
NCP_API int ncpUnicastAddrReadMain(int argc, const char *argv[]);
#else
%rename(ncpUnicastAddrRead) ncpUnicastAddrReadMain;
NCP_API int ncpUnicastAddrReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpLinkStatusBlock(char *cmdArgs);
NCP_API int ncpLinkStatusBlockMain(int argc, const char *argv[]);
#else
%rename(ncpLinkStatusBlock) ncpLinkStatusBlockMain;
NCP_API int ncpLinkStatusBlockMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpBcastScatter(char *cmdArgs);
NCP_API int ncpBcastScatterMain(int argc, const char *argv[]);
#else
%rename(ncpBcastScatter) ncpBcastScatterMain;
NCP_API int ncpBcastScatterMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCeScriptUnload(char *cmdArgs);
NCP_API int ncpCeScriptUnloadMain(int argc, const char *argv[]);
#else
%rename(ncpCeScriptUnload) ncpCeScriptUnloadMain;
NCP_API int ncpCeScriptUnloadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpPllInit(char *cmdArgs);
NCP_API int ncpPllInitMain(int argc, const char *argv[]);
#else
%rename(ncpPllInit) ncpPllInitMain;
NCP_API int ncpPllInitMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTimerUtil(char *cmdArgs);
NCP_API int ncpTimerUtilMain(int argc, const char *argv[]);
#else
%rename(ncpTimerUtil) ncpTimerUtilMain;
NCP_API int ncpTimerUtilMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCatDecode(char *cmdArgs);
NCP_API int ncpCatDecodeMain(int argc, const char *argv[]);
#else
%rename(ncpCatDecode) ncpCatDecodeMain;
NCP_API int ncpCatDecodeMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpOr(char *cmdArgs);
NCP_API int ncpOrMain(int argc, const char *argv[]);
#else
%rename(ncpOr) ncpOrMain;
NCP_API int ncpOrMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMmePoolConfigGet(char *cmdArgs);
NCP_API int ncpMmePoolConfigGetMain(int argc, const char *argv[]);
#else
%rename(ncpMmePoolConfigGet) ncpMmePoolConfigGetMain;
NCP_API int ncpMmePoolConfigGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpVersion(char *cmdArgs);
NCP_API int ncpVersionMain(int argc, const char *argv[]);
#else
%rename(ncpVersion) ncpVersionMain;
NCP_API int ncpVersionMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskStats(char *cmdArgs);
NCP_API int ncpTaskStatsMain(int argc, const char *argv[]);
#else
%rename(ncpTaskStats) ncpTaskStatsMain;
NCP_API int ncpTaskStatsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCompare(char *cmdArgs);
NCP_API int ncpCompareMain(int argc, const char *argv[]);
#else
%rename(ncpCompare) ncpCompareMain;
NCP_API int ncpCompareMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaPortCounterGet(char *cmdArgs);
NCP_API int ncpEioaPortCounterGetMain(int argc, const char *argv[]);
#else
%rename(ncpEioaPortCounterGet) ncpEioaPortCounterGetMain;
NCP_API int ncpEioaPortCounterGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpExtMemBist(char *cmdArgs);
NCP_API int ncpExtMemBistMain(int argc, const char *argv[]);
#else
%rename(ncpExtMemBist) ncpExtMemBistMain;
NCP_API int ncpExtMemBistMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSysmemLsiPhyStatusShow(char *cmdArgs);
NCP_API int ncpSysmemLsiPhyStatusShowMain(int argc, const char *argv[]);
#else
%rename(ncpSysmemLsiPhyStatusShow) ncpSysmemLsiPhyStatusShowMain;
NCP_API int ncpSysmemLsiPhyStatusShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpRead(char *cmdArgs);
NCP_API int ncpReadMain(int argc, const char *argv[]);
#else
%rename(ncpRead) ncpReadMain;
NCP_API int ncpReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpI2CWrite(char *cmdArgs);
NCP_API int ncpI2CWriteMain(int argc, const char *argv[]);
#else
%rename(ncpI2CWrite) ncpI2CWriteMain;
NCP_API int ncpI2CWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmAutoZqcsStop(char *cmdArgs);
NCP_API int ncpSmAutoZqcsStopMain(int argc, const char *argv[]);
#else
%rename(ncpSmAutoZqcsStop) ncpSmAutoZqcsStopMain;
NCP_API int ncpSmAutoZqcsStopMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmZqCalibrateStart(char *cmdArgs);
NCP_API int ncpSmZqCalibrateStartMain(int argc, const char *argv[]);
#else
%rename(ncpSmZqCalibrateStart) ncpSmZqCalibrateStartMain;
NCP_API int ncpSmZqCalibrateStartMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpUsleep(char *cmdArgs);
NCP_API int ncpUsleepMain(int argc, const char *argv[]);
#else
%rename(ncpUsleep) ncpUsleepMain;
NCP_API int ncpUsleepMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacsecStatistics(char *cmdArgs);
NCP_API int ncpMacsecStatisticsMain(int argc, const char *argv[]);
#else
%rename(ncpMacsecStatistics) ncpMacsecStatisticsMain;
NCP_API int ncpMacsecStatisticsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskRecvV2Raw(char *cmdArgs);
NCP_API int ncpTaskRecvV2RawMain(int argc, const char *argv[]);
#else
%rename(ncpTaskRecvV2Raw) ncpTaskRecvV2RawMain;
NCP_API int ncpTaskRecvV2RawMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceTriggerDisable(char *cmdArgs);
NCP_API int ncpTaskTraceTriggerDisableMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceTriggerDisable) ncpTaskTraceTriggerDisableMain;
NCP_API int ncpTaskTraceTriggerDisableMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCatWrite(char *cmdArgs);
NCP_API int ncpCatWriteMain(int argc, const char *argv[]);
#else
%rename(ncpCatWrite) ncpCatWriteMain;
NCP_API int ncpCatWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpLbiCfg(char *cmdArgs);
NCP_API int ncpLbiCfgMain(int argc, const char *argv[]);
#else
%rename(ncpLbiCfg) ncpLbiCfgMain;
NCP_API int ncpLbiCfgMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaTSPollRead(char *cmdArgs);
NCP_API int ncpEioaTSPollReadMain(int argc, const char *argv[]);
#else
%rename(ncpEioaTSPollRead) ncpEioaTSPollReadMain;
NCP_API int ncpEioaTSPollReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaTSRead(char *cmdArgs);
NCP_API int ncpEioaTSReadMain(int argc, const char *argv[]);
#else
%rename(ncpEioaTSRead) ncpEioaTSReadMain;
NCP_API int ncpEioaTSReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCachePreload(char *cmdArgs);
NCP_API int ncpCachePreloadMain(int argc, const char *argv[]);
#else
%rename(ncpCachePreload) ncpCachePreloadMain;
NCP_API int ncpCachePreloadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceTriggerSet(char *cmdArgs);
NCP_API int ncpTaskTraceTriggerSetMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceTriggerSet) ncpTaskTraceTriggerSetMain;
NCP_API int ncpTaskTraceTriggerSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpFill(char *cmdArgs);
NCP_API int ncpFillMain(int argc, const char *argv[]);
#else
%rename(ncpFill) ncpFillMain;
NCP_API int ncpFillMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTemplateShow(char *cmdArgs);
NCP_API int ncpTemplateShowMain(int argc, const char *argv[]);
#else
%rename(ncpTemplateShow) ncpTemplateShowMain;
NCP_API int ncpTemplateShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSysmemLsiPhyRegRestore(char *cmdArgs);
NCP_API int ncpSysmemLsiPhyRegRestoreMain(int argc, const char *argv[]);
#else
%rename(ncpSysmemLsiPhyRegRestore) ncpSysmemLsiPhyRegRestoreMain;
NCP_API int ncpSysmemLsiPhyRegRestoreMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpBootParamGen(char *cmdArgs);
NCP_API int ncpBootParamGenMain(int argc, const char *argv[]);
#else
%rename(ncpBootParamGen) ncpBootParamGenMain;
NCP_API int ncpBootParamGenMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpWrite(char *cmdArgs);
NCP_API int ncpWriteMain(int argc, const char *argv[]);
#else
%rename(ncpWrite) ncpWriteMain;
NCP_API int ncpWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMmeAvailableBlocksGet(char *cmdArgs);
NCP_API int ncpMmeAvailableBlocksGetMain(int argc, const char *argv[]);
#else
%rename(ncpMmeAvailableBlocksGet) ncpMmeAvailableBlocksGetMain;
NCP_API int ncpMmeAvailableBlocksGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacAutoNegGet(char *cmdArgs);
NCP_API int ncpMacAutoNegGetMain(int argc, const char *argv[]);
#else
%rename(ncpMacAutoNegGet) ncpMacAutoNegGetMain;
NCP_API int ncpMacAutoNegGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTvSense(char *cmdArgs);
NCP_API int ncpTvSenseMain(int argc, const char *argv[]);
#else
%rename(ncpTvSense) ncpTvSenseMain;
NCP_API int ncpTvSenseMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonParamSelect(char *cmdArgs);
NCP_API int ncpSmonParamSelectMain(int argc, const char *argv[]);
#else
%rename(ncpSmonParamSelect) ncpSmonParamSelectMain;
NCP_API int ncpSmonParamSelectMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceTriggerEnable(char *cmdArgs);
NCP_API int ncpTaskTraceTriggerEnableMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceTriggerEnable) ncpTaskTraceTriggerEnableMain;
NCP_API int ncpTaskTraceTriggerEnableMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacANPortTrace(char *cmdArgs);
NCP_API int ncpMacANPortTraceMain(int argc, const char *argv[]);
#else
%rename(ncpMacANPortTrace) ncpMacANPortTraceMain;
NCP_API int ncpMacANPortTraceMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacPhyRegRead(char *cmdArgs);
NCP_API int ncpMacPhyRegReadMain(int argc, const char *argv[]);
#else
%rename(ncpMacPhyRegRead) ncpMacPhyRegReadMain;
NCP_API int ncpMacPhyRegReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpVoltage(char *cmdArgs);
NCP_API int ncpVoltageMain(int argc, const char *argv[]);
#else
%rename(ncpVoltage) ncpVoltageMain;
NCP_API int ncpVoltageMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonQueueSelect(char *cmdArgs);
NCP_API int ncpSmonQueueSelectMain(int argc, const char *argv[]);
#else
%rename(ncpSmonQueueSelect) ncpSmonQueueSelectMain;
NCP_API int ncpSmonQueueSelectMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpShutDownPPC(char *cmdArgs);
NCP_API int ncpShutDownPPCMain(int argc, const char *argv[]);
#else
%rename(ncpShutDownPPC) ncpShutDownPPCMain;
NCP_API int ncpShutDownPPCMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSysClock(char *cmdArgs);
NCP_API int ncpSysClockMain(int argc, const char *argv[]);
#else
%rename(ncpSysClock) ncpSysClockMain;
NCP_API int ncpSysClockMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaSlotOvrclkGet(char *cmdArgs);
NCP_API int ncpEioaSlotOvrclkGetMain(int argc, const char *argv[]);
#else
%rename(ncpEioaSlotOvrclkGet) ncpEioaSlotOvrclkGetMain;
NCP_API int ncpEioaSlotOvrclkGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSpeedDuplexSet(char *cmdArgs);
NCP_API int ncpSpeedDuplexSetMain(int argc, const char *argv[]);
#else
%rename(ncpSpeedDuplexSet) ncpSpeedDuplexSetMain;
NCP_API int ncpSpeedDuplexSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCmemInit(char *cmdArgs);
NCP_API int ncpCmemInitMain(int argc, const char *argv[]);
#else
%rename(ncpCmemInit) ncpCmemInitMain;
NCP_API int ncpCmemInitMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpPoll(char *cmdArgs);
NCP_API int ncpPollMain(int argc, const char *argv[]);
#else
%rename(ncpPoll) ncpPollMain;
NCP_API int ncpPollMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacPauseWrite(char *cmdArgs);
NCP_API int ncpMacPauseWriteMain(int argc, const char *argv[]);
#else
%rename(ncpMacPauseWrite) ncpMacPauseWriteMain;
NCP_API int ncpMacPauseWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpShell(char *cmdArgs);
NCP_API int ncpShellMain(int argc, const char *argv[]);
#else
%rename(ncpShell) ncpShellMain;
NCP_API int ncpShellMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCatRead(char *cmdArgs);
NCP_API int ncpCatReadMain(int argc, const char *argv[]);
#else
%rename(ncpCatRead) ncpCatReadMain;
NCP_API int ncpCatReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMtmGlobalStats(char *cmdArgs);
NCP_API int ncpMtmGlobalStatsMain(int argc, const char *argv[]);
#else
%rename(ncpMtmGlobalStats) ncpMtmGlobalStatsMain;
NCP_API int ncpMtmGlobalStatsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpStatusPrint(char *cmdArgs);
NCP_API int ncpStatusPrintMain(int argc, const char *argv[]);
#else
%rename(ncpStatusPrint) ncpStatusPrintMain;
NCP_API int ncpStatusPrintMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpI2CRead(char *cmdArgs);
NCP_API int ncpI2CReadMain(int argc, const char *argv[]);
#else
%rename(ncpI2CRead) ncpI2CReadMain;
NCP_API int ncpI2CReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpLinkStatus(char *cmdArgs);
NCP_API int ncpLinkStatusMain(int argc, const char *argv[]);
#else
%rename(ncpLinkStatus) ncpLinkStatusMain;
NCP_API int ncpLinkStatusMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpDomainCfg(char *cmdArgs);
NCP_API int ncpDomainCfgMain(int argc, const char *argv[]);
#else
%rename(ncpDomainCfg) ncpDomainCfgMain;
NCP_API int ncpDomainCfgMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpScatter(char *cmdArgs);
NCP_API int ncpScatterMain(int argc, const char *argv[]);
#else
%rename(ncpScatter) ncpScatterMain;
NCP_API int ncpScatterMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCeScriptLoad(char *cmdArgs);
NCP_API int ncpCeScriptLoadMain(int argc, const char *argv[]);
#else
%rename(ncpCeScriptLoad) ncpCeScriptLoadMain;
NCP_API int ncpCeScriptLoadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMdioRead(char *cmdArgs);
NCP_API int ncpMdioReadMain(int argc, const char *argv[]);
#else
%rename(ncpMdioRead) ncpMdioReadMain;
NCP_API int ncpMdioReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpAlarmGet(char *cmdArgs);
NCP_API int ncpAlarmGetMain(int argc, const char *argv[]);
#else
%rename(ncpAlarmGet) ncpAlarmGetMain;
NCP_API int ncpAlarmGetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpReset(char *cmdArgs);
NCP_API int ncpResetMain(int argc, const char *argv[]);
#else
%rename(ncpReset) ncpResetMain;
NCP_API int ncpResetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpRamTest(char *cmdArgs);
NCP_API int ncpRamTestMain(int argc, const char *argv[]);
#else
%rename(ncpRamTest) ncpRamTestMain;
NCP_API int ncpRamTestMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaSwitchBridgeKeys(char *cmdArgs);
NCP_API int ncpEioaSwitchBridgeKeysMain(int argc, const char *argv[]);
#else
%rename(ncpEioaSwitchBridgeKeys) ncpEioaSwitchBridgeKeysMain;
NCP_API int ncpEioaSwitchBridgeKeysMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpTaskTraceEnable(char *cmdArgs);
NCP_API int ncpTaskTraceEnableMain(int argc, const char *argv[]);
#else
%rename(ncpTaskTraceEnable) ncpTaskTraceEnableMain;
NCP_API int ncpTaskTraceEnableMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonInit(char *cmdArgs);
NCP_API int ncpSmonInitMain(int argc, const char *argv[]);
#else
%rename(ncpSmonInit) ncpSmonInitMain;
NCP_API int ncpSmonInitMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCoherentRead(char *cmdArgs);
NCP_API int ncpCoherentReadMain(int argc, const char *argv[]);
#else
%rename(ncpCoherentRead) ncpCoherentReadMain;
NCP_API int ncpCoherentReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEngineSeqShow(char *cmdArgs);
NCP_API int ncpEngineSeqShowMain(int argc, const char *argv[]);
#else
%rename(ncpEngineSeqShow) ncpEngineSeqShowMain;
NCP_API int ncpEngineSeqShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpRegister(char *cmdArgs);
NCP_API int ncpRegisterMain(int argc, const char *argv[]);
#else
%rename(ncpRegister) ncpRegisterMain;
NCP_API int ncpRegisterMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpUnicastAddrWrite(char *cmdArgs);
NCP_API int ncpUnicastAddrWriteMain(int argc, const char *argv[]);
#else
%rename(ncpUnicastAddrWrite) ncpUnicastAddrWriteMain;
NCP_API int ncpUnicastAddrWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMacMtuWrite(char *cmdArgs);
NCP_API int ncpMacMtuWriteMain(int argc, const char *argv[]);
#else
%rename(ncpMacMtuWrite) ncpMacMtuWriteMain;
NCP_API int ncpMacMtuWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpVirtualPipelineShow(char *cmdArgs);
NCP_API int ncpVirtualPipelineShowMain(int argc, const char *argv[]);
#else
%rename(ncpVirtualPipelineShow) ncpVirtualPipelineShowMain;
NCP_API int ncpVirtualPipelineShowMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaVPidRead(char *cmdArgs);
NCP_API int ncpEioaVPidReadMain(int argc, const char *argv[]);
#else
%rename(ncpEioaVPidRead) ncpEioaVPidReadMain;
NCP_API int ncpEioaVPidReadMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpDevStats(char *cmdArgs);
NCP_API int ncpDevStatsMain(int argc, const char *argv[]);
#else
%rename(ncpDevStats) ncpDevStatsMain;
NCP_API int ncpDevStatsMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpMmeMpcqPollingIntervalSet(char *cmdArgs);
NCP_API int ncpMmeMpcqPollingIntervalSetMain(int argc, const char *argv[]);
#else
%rename(ncpMmeMpcqPollingIntervalSet) ncpMmeMpcqPollingIntervalSetMain;
NCP_API int ncpMmeMpcqPollingIntervalSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpEioaVlanList(char *cmdArgs);
NCP_API int ncpEioaVlanListMain(int argc, const char *argv[]);
#else
%rename(ncpEioaVlanList) ncpEioaVlanListMain;
NCP_API int ncpEioaVlanListMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpCoherentWrite(char *cmdArgs);
NCP_API int ncpCoherentWriteMain(int argc, const char *argv[]);
#else
%rename(ncpCoherentWrite) ncpCoherentWriteMain;
NCP_API int ncpCoherentWriteMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpChanLoopbackSet(char *cmdArgs);
NCP_API int ncpChanLoopbackSetMain(int argc, const char *argv[]);
#else
%rename(ncpChanLoopbackSet) ncpChanLoopbackSetMain;
NCP_API int ncpChanLoopbackSetMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpIoPerf(char *cmdArgs);
NCP_API int ncpIoPerfMain(int argc, const char *argv[]);
#else
%rename(ncpIoPerf) ncpIoPerfMain;
NCP_API int ncpIoPerfMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */
#if !defined(SWIG)
NCP_API int ncpSmonMuxSelect(char *cmdArgs);
NCP_API int ncpSmonMuxSelectMain(int argc, const char *argv[]);
#else
%rename(ncpSmonMuxSelect) ncpSmonMuxSelectMain;
NCP_API int ncpSmonMuxSelectMain(int argc=1, const char * argv[]="");
#endif /* #ifndef SWIG */


#ifndef SWIG
#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */
#endif /* #ifndef SWIG */

#endif  /* !defined(DOXYGEN) */

#endif /* #ifdef _NCPCLI_H_ */
