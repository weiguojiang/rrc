// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_interface.java
// Do not modify

package org.projectfloodlight.openflow.protocol;

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
import java.util.List;
import java.util.Set;
import io.netty.buffer.ByteBuf;

public interface OFFlowStatsEntry extends OFObject {
    TableId getTableId();
    long getDurationSec();
    long getDurationNsec();
    int getPriority();
    int getIdleTimeout();
    int getHardTimeout();
    U64 getCookie();
    U64 getPacketCount();
    U64 getByteCount();
    Match getMatch();
    List<OFInstruction> getInstructions() throws UnsupportedOperationException;
    List<OFAction> getActions() throws UnsupportedOperationException;
    Set<OFFlowModFlags> getFlags() throws UnsupportedOperationException;
    int getImportance() throws UnsupportedOperationException;
    OFVersion getVersion();


    void writeTo(ByteBuf channelBuffer);

    Builder createBuilder();
    public interface Builder  {
        OFFlowStatsEntry build();
        TableId getTableId();
        Builder setTableId(TableId tableId);
        long getDurationSec();
        Builder setDurationSec(long durationSec);
        long getDurationNsec();
        Builder setDurationNsec(long durationNsec);
        int getPriority();
        Builder setPriority(int priority);
        int getIdleTimeout();
        Builder setIdleTimeout(int idleTimeout);
        int getHardTimeout();
        Builder setHardTimeout(int hardTimeout);
        U64 getCookie();
        Builder setCookie(U64 cookie);
        U64 getPacketCount();
        Builder setPacketCount(U64 packetCount);
        U64 getByteCount();
        Builder setByteCount(U64 byteCount);
        Match getMatch();
        Builder setMatch(Match match);
        List<OFInstruction> getInstructions() throws UnsupportedOperationException;
        Builder setInstructions(List<OFInstruction> instructions) throws UnsupportedOperationException;
        List<OFAction> getActions() throws UnsupportedOperationException;
        Builder setActions(List<OFAction> actions) throws UnsupportedOperationException;
        Set<OFFlowModFlags> getFlags() throws UnsupportedOperationException;
        Builder setFlags(Set<OFFlowModFlags> flags) throws UnsupportedOperationException;
        int getImportance() throws UnsupportedOperationException;
        Builder setImportance(int importance) throws UnsupportedOperationException;
        OFVersion getVersion();
    }
}
