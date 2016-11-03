// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_factory_interface.java
// Do not modify

package org.projectfloodlight.openflow.protocol.bsntlv;

import org.projectfloodlight.openflow.protocol.*;
import org.projectfloodlight.openflow.protocol.action.*;
import org.projectfloodlight.openflow.protocol.actionid.*;
import org.projectfloodlight.openflow.protocol.bsntlv.*;
import org.projectfloodlight.openflow.protocol.errormsg.*;
import org.projectfloodlight.openflow.protocol.meterband.*;
import org.projectfloodlight.openflow.protocol.instruction.*;
import org.projectfloodlight.openflow.protocol.instructionid.*;
import org.projectfloodlight.openflow.protocol.match.*;
import org.projectfloodlight.openflow.protocol.oxm.*;
import org.projectfloodlight.openflow.protocol.queueprop.*;
import org.projectfloodlight.openflow.types.*;
import org.projectfloodlight.openflow.util.*;
import org.projectfloodlight.openflow.exceptions.*;
import java.util.Set;
import java.util.List;

public interface OFBsnTlvs {
    // Subfactories

    OFBsnTlvActorKey.Builder buildActorKey() throws UnsupportedOperationException;
    OFBsnTlvActorKey actorKey(int value);
    OFBsnTlvActorPortNum.Builder buildActorPortNum() throws UnsupportedOperationException;
    OFBsnTlvActorPortNum actorPortNum(int value);
    OFBsnTlvActorPortPriority.Builder buildActorPortPriority() throws UnsupportedOperationException;
    OFBsnTlvActorPortPriority actorPortPriority(int value);
    OFBsnTlvActorState.Builder buildActorState() throws UnsupportedOperationException;
    OFBsnTlvActorState actorState(Set<OFBsnLacpState> value);
    OFBsnTlvActorSystemMac.Builder buildActorSystemMac() throws UnsupportedOperationException;
    OFBsnTlvActorSystemMac actorSystemMac(MacAddress value);
    OFBsnTlvActorSystemPriority.Builder buildActorSystemPriority() throws UnsupportedOperationException;
    OFBsnTlvActorSystemPriority actorSystemPriority(int value);
    OFBsnTlvAnchor.Builder buildAnchor() throws UnsupportedOperationException;
    OFBsnTlvAnchor anchor(OFBsnAnchor value);
    OFBsnTlvBroadcastQueryTimeout.Builder buildBroadcastQueryTimeout() throws UnsupportedOperationException;
    OFBsnTlvBroadcastQueryTimeout broadcastQueryTimeout(long value);
    OFBsnTlvBroadcastRate.Builder buildBroadcastRate() throws UnsupportedOperationException;
    OFBsnTlvBroadcastRate broadcastRate(long value);
    OFBsnTlvBucket.Builder buildBucket() throws UnsupportedOperationException;
    OFBsnTlvBucket bucket(List<OFBsnTlv> value);
    OFBsnTlvCircuitId.Builder buildCircuitId() throws UnsupportedOperationException;
    OFBsnTlvCircuitId circuitId(byte[] value);
    OFBsnTlvConvergenceStatus.Builder buildConvergenceStatus() throws UnsupportedOperationException;
    OFBsnTlvConvergenceStatus convergenceStatus(short value);
    OFBsnTlvCrcEnabled.Builder buildCrcEnabled() throws UnsupportedOperationException;
    OFBsnTlvCrcEnabled crcEnabled(short value);
    OFBsnTlvData.Builder buildData() throws UnsupportedOperationException;
    OFBsnTlvData data(byte[] value);
    OFBsnTlvDecap.Builder buildDecap() throws UnsupportedOperationException;
    OFBsnTlvDecap decap(OFBsnDecap value);
    OFBsnTlvEthDst.Builder buildEthDst() throws UnsupportedOperationException;
    OFBsnTlvEthDst ethDst(MacAddress value);
    OFBsnTlvEthSrc.Builder buildEthSrc() throws UnsupportedOperationException;
    OFBsnTlvEthSrc ethSrc(MacAddress value);
    OFBsnTlvExternalGatewayIp.Builder buildExternalGatewayIp() throws UnsupportedOperationException;
    OFBsnTlvExternalGatewayIp externalGatewayIp(IPv4Address value);
    OFBsnTlvExternalGatewayMac.Builder buildExternalGatewayMac() throws UnsupportedOperationException;
    OFBsnTlvExternalGatewayMac externalGatewayMac(MacAddress value);
    OFBsnTlvExternalIp.Builder buildExternalIp() throws UnsupportedOperationException;
    OFBsnTlvExternalIp externalIp(IPv4Address value);
    OFBsnTlvExternalMac.Builder buildExternalMac() throws UnsupportedOperationException;
    OFBsnTlvExternalMac externalMac(MacAddress value);
    OFBsnTlvExternalNetmask.Builder buildExternalNetmask() throws UnsupportedOperationException;
    OFBsnTlvExternalNetmask externalNetmask(IPv4Address value);
    OFBsnTlvGenerationId.Builder buildGenerationId() throws UnsupportedOperationException;
    OFBsnTlvGenerationId generationId(U64 value);
    OFBsnTlvHeaderSize.Builder buildHeaderSize() throws UnsupportedOperationException;
    OFBsnTlvHeaderSize headerSize(long value);
    OFBsnTlvIcmpCode.Builder buildIcmpCode() throws UnsupportedOperationException;
    OFBsnTlvIcmpCode icmpCode(short value);
    OFBsnTlvIcmpId.Builder buildIcmpId() throws UnsupportedOperationException;
    OFBsnTlvIcmpId icmpId(int value);
    OFBsnTlvIcmpType.Builder buildIcmpType() throws UnsupportedOperationException;
    OFBsnTlvIcmpType icmpType(short value);
    OFBsnTlvIdleNotification idleNotification();
    OFBsnTlvIdleTime.Builder buildIdleTime() throws UnsupportedOperationException;
    OFBsnTlvIdleTime idleTime(U64 value);
    OFBsnTlvIdleTimeout.Builder buildIdleTimeout() throws UnsupportedOperationException;
    OFBsnTlvIdleTimeout idleTimeout(long value);
    OFBsnTlvIgmpSnooping igmpSnooping();
    OFBsnTlvInternalGatewayMac.Builder buildInternalGatewayMac() throws UnsupportedOperationException;
    OFBsnTlvInternalGatewayMac internalGatewayMac(MacAddress value);
    OFBsnTlvInternalMac.Builder buildInternalMac() throws UnsupportedOperationException;
    OFBsnTlvInternalMac internalMac(MacAddress value);
    OFBsnTlvInterval.Builder buildInterval() throws UnsupportedOperationException;
    OFBsnTlvInterval interval(long value);
    OFBsnTlvIpProto.Builder buildIpProto() throws UnsupportedOperationException;
    OFBsnTlvIpProto ipProto(short value);
    OFBsnTlvIpv4.Builder buildIpv4() throws UnsupportedOperationException;
    OFBsnTlvIpv4 ipv4(IPv4Address value);
    OFBsnTlvIpv4Dst.Builder buildIpv4Dst() throws UnsupportedOperationException;
    OFBsnTlvIpv4Dst ipv4Dst(IPv4Address value);
    OFBsnTlvIpv4Netmask.Builder buildIpv4Netmask() throws UnsupportedOperationException;
    OFBsnTlvIpv4Netmask ipv4Netmask(IPv4Address value);
    OFBsnTlvIpv4Src.Builder buildIpv4Src() throws UnsupportedOperationException;
    OFBsnTlvIpv4Src ipv4Src(IPv4Address value);
    OFBsnTlvIpv6.Builder buildIpv6() throws UnsupportedOperationException;
    OFBsnTlvIpv6 ipv6(IPv6Address value);
    OFBsnTlvKnownMulticastRate.Builder buildKnownMulticastRate() throws UnsupportedOperationException;
    OFBsnTlvKnownMulticastRate knownMulticastRate(long value);
    OFBsnTlvL2MulticastLookup l2MulticastLookup();
    OFBsnTlvMac.Builder buildMac() throws UnsupportedOperationException;
    OFBsnTlvMac mac(MacAddress value);
    OFBsnTlvMacMask.Builder buildMacMask() throws UnsupportedOperationException;
    OFBsnTlvMacMask macMask(MacAddress value);
    OFBsnTlvMcgTypeVxlan mcgTypeVxlan();
    OFBsnTlvMissPackets.Builder buildMissPackets() throws UnsupportedOperationException;
    OFBsnTlvMissPackets missPackets(U64 value);
    OFBsnTlvMplsControlWord.Builder buildMplsControlWord() throws UnsupportedOperationException;
    OFBsnTlvMplsControlWord mplsControlWord(short value);
    OFBsnTlvMplsLabel.Builder buildMplsLabel() throws UnsupportedOperationException;
    OFBsnTlvMplsLabel mplsLabel(long value);
    OFBsnTlvMplsSequenced.Builder buildMplsSequenced() throws UnsupportedOperationException;
    OFBsnTlvMplsSequenced mplsSequenced(short value);
    OFBsnTlvMulticastInterfaceId.Builder buildMulticastInterfaceId() throws UnsupportedOperationException;
    OFBsnTlvMulticastInterfaceId multicastInterfaceId(long value);
    OFBsnTlvName.Builder buildName() throws UnsupportedOperationException;
    OFBsnTlvName name(byte[] value);
    OFBsnTlvNegate negate();
    OFBsnTlvNexthopTypeVxlan nexthopTypeVxlan();
    OFBsnTlvOffset.Builder buildOffset() throws UnsupportedOperationException;
    OFBsnTlvOffset offset(int value);
    OFBsnTlvPartnerKey.Builder buildPartnerKey() throws UnsupportedOperationException;
    OFBsnTlvPartnerKey partnerKey(int value);
    OFBsnTlvPartnerPortNum.Builder buildPartnerPortNum() throws UnsupportedOperationException;
    OFBsnTlvPartnerPortNum partnerPortNum(int value);
    OFBsnTlvPartnerPortPriority.Builder buildPartnerPortPriority() throws UnsupportedOperationException;
    OFBsnTlvPartnerPortPriority partnerPortPriority(int value);
    OFBsnTlvPartnerState.Builder buildPartnerState() throws UnsupportedOperationException;
    OFBsnTlvPartnerState partnerState(Set<OFBsnLacpState> value);
    OFBsnTlvPartnerSystemMac.Builder buildPartnerSystemMac() throws UnsupportedOperationException;
    OFBsnTlvPartnerSystemMac partnerSystemMac(MacAddress value);
    OFBsnTlvPartnerSystemPriority.Builder buildPartnerSystemPriority() throws UnsupportedOperationException;
    OFBsnTlvPartnerSystemPriority partnerSystemPriority(int value);
    OFBsnTlvPort.Builder buildPort() throws UnsupportedOperationException;
    OFBsnTlvPort port(OFPort value);
    OFBsnTlvPortVxlanMode.Builder buildPortVxlanMode() throws UnsupportedOperationException;
    OFBsnTlvPortVxlanMode portVxlanMode(OFBsnPortVxlanMode value);
    OFBsnTlvPriority.Builder buildPriority() throws UnsupportedOperationException;
    OFBsnTlvPriority priority(long value);
    OFBsnTlvQueueId.Builder buildQueueId() throws UnsupportedOperationException;
    OFBsnTlvQueueId queueId(long value);
    OFBsnTlvQueueWeight.Builder buildQueueWeight() throws UnsupportedOperationException;
    OFBsnTlvQueueWeight queueWeight(long value);
    OFBsnTlvRateUnit.Builder buildRateUnit() throws UnsupportedOperationException;
    OFBsnTlvRateUnit rateUnit(OFBsnRateUnit value);
    OFBsnTlvReference.Builder buildReference() throws UnsupportedOperationException;
    OFBsnTlvReference reference(int tableId, List<OFBsnTlv> key);
    OFBsnTlvReplyPackets.Builder buildReplyPackets() throws UnsupportedOperationException;
    OFBsnTlvReplyPackets replyPackets(U64 value);
    OFBsnTlvRequestPackets.Builder buildRequestPackets() throws UnsupportedOperationException;
    OFBsnTlvRequestPackets requestPackets(U64 value);
    OFBsnTlvRxBytes.Builder buildRxBytes() throws UnsupportedOperationException;
    OFBsnTlvRxBytes rxBytes(U64 value);
    OFBsnTlvRxPackets.Builder buildRxPackets() throws UnsupportedOperationException;
    OFBsnTlvRxPackets rxPackets(U64 value);
    OFBsnTlvSamplingRate.Builder buildSamplingRate() throws UnsupportedOperationException;
    OFBsnTlvSamplingRate samplingRate(long value);
    OFBsnTlvSetLoopbackMode setLoopbackMode();
    OFBsnTlvStatus.Builder buildStatus() throws UnsupportedOperationException;
    OFBsnTlvStatus status(OFBsnStatus value);
    OFBsnTlvStripMplsL2OnIngress stripMplsL2OnIngress();
    OFBsnTlvStripMplsL3OnIngress stripMplsL3OnIngress();
    OFBsnTlvStripVlanOnEgress stripVlanOnEgress();
    OFBsnTlvSubAgentId.Builder buildSubAgentId() throws UnsupportedOperationException;
    OFBsnTlvSubAgentId subAgentId(long value);
    OFBsnTlvTcpDst.Builder buildTcpDst() throws UnsupportedOperationException;
    OFBsnTlvTcpDst tcpDst(int value);
    OFBsnTlvTcpSrc.Builder buildTcpSrc() throws UnsupportedOperationException;
    OFBsnTlvTcpSrc tcpSrc(int value);
    OFBsnTlvTxBytes.Builder buildTxBytes() throws UnsupportedOperationException;
    OFBsnTlvTxBytes txBytes(U64 value);
    OFBsnTlvTxPackets.Builder buildTxPackets() throws UnsupportedOperationException;
    OFBsnTlvTxPackets txPackets(U64 value);
    OFBsnTlvUdfAnchor.Builder buildUdfAnchor() throws UnsupportedOperationException;
    OFBsnTlvUdfAnchor udfAnchor(OFBsnUdfAnchor value);
    OFBsnTlvUdfId.Builder buildUdfId() throws UnsupportedOperationException;
    OFBsnTlvUdfId udfId(int value);
    OFBsnTlvUdfLength.Builder buildUdfLength() throws UnsupportedOperationException;
    OFBsnTlvUdfLength udfLength(int value);
    OFBsnTlvUdfOffset.Builder buildUdfOffset() throws UnsupportedOperationException;
    OFBsnTlvUdfOffset udfOffset(int value);
    OFBsnTlvUdpDst.Builder buildUdpDst() throws UnsupportedOperationException;
    OFBsnTlvUdpDst udpDst(int value);
    OFBsnTlvUdpSrc.Builder buildUdpSrc() throws UnsupportedOperationException;
    OFBsnTlvUdpSrc udpSrc(int value);
    OFBsnTlvUnicastQueryTimeout.Builder buildUnicastQueryTimeout() throws UnsupportedOperationException;
    OFBsnTlvUnicastQueryTimeout unicastQueryTimeout(long value);
    OFBsnTlvUnicastRate.Builder buildUnicastRate() throws UnsupportedOperationException;
    OFBsnTlvUnicastRate unicastRate(long value);
    OFBsnTlvUnknownMulticastRate.Builder buildUnknownMulticastRate() throws UnsupportedOperationException;
    OFBsnTlvUnknownMulticastRate unknownMulticastRate(long value);
    OFBsnTlvUsePacketState.Builder buildUsePacketState() throws UnsupportedOperationException;
    OFBsnTlvUsePacketState usePacketState(short value);
    OFBsnTlvVlanPcp.Builder buildVlanPcp() throws UnsupportedOperationException;
    OFBsnTlvVlanPcp vlanPcp(short value);
    OFBsnTlvVlanVid.Builder buildVlanVid() throws UnsupportedOperationException;
    OFBsnTlvVlanVid vlanVid(VlanVid value);
    OFBsnTlvVlanVidMask.Builder buildVlanVidMask() throws UnsupportedOperationException;
    OFBsnTlvVlanVidMask vlanVidMask(int value);
    OFBsnTlvVni.Builder buildVni() throws UnsupportedOperationException;
    OFBsnTlvVni vni(long value);
    OFBsnTlvVrf.Builder buildVrf() throws UnsupportedOperationException;
    OFBsnTlvVrf vrf(long value);

    OFMessageReader<OFBsnTlv> getReader();
    OFVersion getVersion();
}
