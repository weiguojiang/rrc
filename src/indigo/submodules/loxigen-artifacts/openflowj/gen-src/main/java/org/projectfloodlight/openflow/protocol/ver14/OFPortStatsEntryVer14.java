// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver14;

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
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.List;
import com.google.common.collect.ImmutableList;
import java.util.Set;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFPortStatsEntryVer14 implements OFPortStatsEntry {
    private static final Logger logger = LoggerFactory.getLogger(OFPortStatsEntryVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 80;

        private final static OFPort DEFAULT_PORT_NO = OFPort.ANY;
        private final static long DEFAULT_DURATION_SEC = 0x0L;
        private final static long DEFAULT_DURATION_NSEC = 0x0L;
        private final static U64 DEFAULT_RX_PACKETS = U64.ZERO;
        private final static U64 DEFAULT_TX_PACKETS = U64.ZERO;
        private final static U64 DEFAULT_RX_BYTES = U64.ZERO;
        private final static U64 DEFAULT_TX_BYTES = U64.ZERO;
        private final static U64 DEFAULT_RX_DROPPED = U64.ZERO;
        private final static U64 DEFAULT_TX_DROPPED = U64.ZERO;
        private final static U64 DEFAULT_RX_ERRORS = U64.ZERO;
        private final static U64 DEFAULT_TX_ERRORS = U64.ZERO;
        private final static List<OFPortStatsProp> DEFAULT_PROPERTIES = ImmutableList.<OFPortStatsProp>of();

    // OF message fields
    private final OFPort portNo;
    private final long durationSec;
    private final long durationNsec;
    private final U64 rxPackets;
    private final U64 txPackets;
    private final U64 rxBytes;
    private final U64 txBytes;
    private final U64 rxDropped;
    private final U64 txDropped;
    private final U64 rxErrors;
    private final U64 txErrors;
    private final List<OFPortStatsProp> properties;
//
    // Immutable default instance
    final static OFPortStatsEntryVer14 DEFAULT = new OFPortStatsEntryVer14(
        DEFAULT_PORT_NO, DEFAULT_DURATION_SEC, DEFAULT_DURATION_NSEC, DEFAULT_RX_PACKETS, DEFAULT_TX_PACKETS, DEFAULT_RX_BYTES, DEFAULT_TX_BYTES, DEFAULT_RX_DROPPED, DEFAULT_TX_DROPPED, DEFAULT_RX_ERRORS, DEFAULT_TX_ERRORS, DEFAULT_PROPERTIES
    );

    // package private constructor - used by readers, builders, and factory
    OFPortStatsEntryVer14(OFPort portNo, long durationSec, long durationNsec, U64 rxPackets, U64 txPackets, U64 rxBytes, U64 txBytes, U64 rxDropped, U64 txDropped, U64 rxErrors, U64 txErrors, List<OFPortStatsProp> properties) {
        if(portNo == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property portNo cannot be null");
        }
        if(rxPackets == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property rxPackets cannot be null");
        }
        if(txPackets == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property txPackets cannot be null");
        }
        if(rxBytes == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property rxBytes cannot be null");
        }
        if(txBytes == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property txBytes cannot be null");
        }
        if(rxDropped == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property rxDropped cannot be null");
        }
        if(txDropped == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property txDropped cannot be null");
        }
        if(rxErrors == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property rxErrors cannot be null");
        }
        if(txErrors == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property txErrors cannot be null");
        }
        if(properties == null) {
            throw new NullPointerException("OFPortStatsEntryVer14: property properties cannot be null");
        }
        this.portNo = portNo;
        this.durationSec = durationSec;
        this.durationNsec = durationNsec;
        this.rxPackets = rxPackets;
        this.txPackets = txPackets;
        this.rxBytes = rxBytes;
        this.txBytes = txBytes;
        this.rxDropped = rxDropped;
        this.txDropped = txDropped;
        this.rxErrors = rxErrors;
        this.txErrors = txErrors;
        this.properties = properties;
    }

    // Accessors for OF message fields
    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public U64 getRxPackets() {
        return rxPackets;
    }

    @Override
    public U64 getTxPackets() {
        return txPackets;
    }

    @Override
    public U64 getRxBytes() {
        return rxBytes;
    }

    @Override
    public U64 getTxBytes() {
        return txBytes;
    }

    @Override
    public U64 getRxDropped() {
        return rxDropped;
    }

    @Override
    public U64 getTxDropped() {
        return txDropped;
    }

    @Override
    public U64 getRxErrors() {
        return rxErrors;
    }

    @Override
    public U64 getTxErrors() {
        return txErrors;
    }

    @Override
    public U64 getRxFrameErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxFrameErr not supported in version 1.4");
    }

    @Override
    public U64 getRxOverErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxOverErr not supported in version 1.4");
    }

    @Override
    public U64 getRxCrcErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxCrcErr not supported in version 1.4");
    }

    @Override
    public U64 getCollisions()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property collisions not supported in version 1.4");
    }

    @Override
    public long getDurationSec() {
        return durationSec;
    }

    @Override
    public long getDurationNsec() {
        return durationNsec;
    }

    @Override
    public List<OFPortStatsProp> getProperties() {
        return properties;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFPortStatsEntry.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFPortStatsEntry.Builder {
        final OFPortStatsEntryVer14 parentMessage;

        // OF message fields
        private boolean portNoSet;
        private OFPort portNo;
        private boolean durationSecSet;
        private long durationSec;
        private boolean durationNsecSet;
        private long durationNsec;
        private boolean rxPacketsSet;
        private U64 rxPackets;
        private boolean txPacketsSet;
        private U64 txPackets;
        private boolean rxBytesSet;
        private U64 rxBytes;
        private boolean txBytesSet;
        private U64 txBytes;
        private boolean rxDroppedSet;
        private U64 rxDropped;
        private boolean txDroppedSet;
        private U64 txDropped;
        private boolean rxErrorsSet;
        private U64 rxErrors;
        private boolean txErrorsSet;
        private U64 txErrors;
        private boolean propertiesSet;
        private List<OFPortStatsProp> properties;

        BuilderWithParent(OFPortStatsEntryVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public OFPortStatsEntry.Builder setPortNo(OFPort portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public U64 getRxPackets() {
        return rxPackets;
    }

    @Override
    public OFPortStatsEntry.Builder setRxPackets(U64 rxPackets) {
        this.rxPackets = rxPackets;
        this.rxPacketsSet = true;
        return this;
    }
    @Override
    public U64 getTxPackets() {
        return txPackets;
    }

    @Override
    public OFPortStatsEntry.Builder setTxPackets(U64 txPackets) {
        this.txPackets = txPackets;
        this.txPacketsSet = true;
        return this;
    }
    @Override
    public U64 getRxBytes() {
        return rxBytes;
    }

    @Override
    public OFPortStatsEntry.Builder setRxBytes(U64 rxBytes) {
        this.rxBytes = rxBytes;
        this.rxBytesSet = true;
        return this;
    }
    @Override
    public U64 getTxBytes() {
        return txBytes;
    }

    @Override
    public OFPortStatsEntry.Builder setTxBytes(U64 txBytes) {
        this.txBytes = txBytes;
        this.txBytesSet = true;
        return this;
    }
    @Override
    public U64 getRxDropped() {
        return rxDropped;
    }

    @Override
    public OFPortStatsEntry.Builder setRxDropped(U64 rxDropped) {
        this.rxDropped = rxDropped;
        this.rxDroppedSet = true;
        return this;
    }
    @Override
    public U64 getTxDropped() {
        return txDropped;
    }

    @Override
    public OFPortStatsEntry.Builder setTxDropped(U64 txDropped) {
        this.txDropped = txDropped;
        this.txDroppedSet = true;
        return this;
    }
    @Override
    public U64 getRxErrors() {
        return rxErrors;
    }

    @Override
    public OFPortStatsEntry.Builder setRxErrors(U64 rxErrors) {
        this.rxErrors = rxErrors;
        this.rxErrorsSet = true;
        return this;
    }
    @Override
    public U64 getTxErrors() {
        return txErrors;
    }

    @Override
    public OFPortStatsEntry.Builder setTxErrors(U64 txErrors) {
        this.txErrors = txErrors;
        this.txErrorsSet = true;
        return this;
    }
    @Override
    public U64 getRxFrameErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxFrameErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxFrameErr(U64 rxFrameErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxFrameErr not supported in version 1.4");
    }
    @Override
    public U64 getRxOverErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxOverErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxOverErr(U64 rxOverErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxOverErr not supported in version 1.4");
    }
    @Override
    public U64 getRxCrcErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxCrcErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxCrcErr(U64 rxCrcErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxCrcErr not supported in version 1.4");
    }
    @Override
    public U64 getCollisions()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property collisions not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setCollisions(U64 collisions) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property collisions not supported in version 1.4");
    }
    @Override
    public long getDurationSec() {
        return durationSec;
    }

    @Override
    public OFPortStatsEntry.Builder setDurationSec(long durationSec) {
        this.durationSec = durationSec;
        this.durationSecSet = true;
        return this;
    }
    @Override
    public long getDurationNsec() {
        return durationNsec;
    }

    @Override
    public OFPortStatsEntry.Builder setDurationNsec(long durationNsec) {
        this.durationNsec = durationNsec;
        this.durationNsecSet = true;
        return this;
    }
    @Override
    public List<OFPortStatsProp> getProperties() {
        return properties;
    }

    @Override
    public OFPortStatsEntry.Builder setProperties(List<OFPortStatsProp> properties) {
        this.properties = properties;
        this.propertiesSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFPortStatsEntry build() {
                OFPort portNo = this.portNoSet ? this.portNo : parentMessage.portNo;
                if(portNo == null)
                    throw new NullPointerException("Property portNo must not be null");
                long durationSec = this.durationSecSet ? this.durationSec : parentMessage.durationSec;
                long durationNsec = this.durationNsecSet ? this.durationNsec : parentMessage.durationNsec;
                U64 rxPackets = this.rxPacketsSet ? this.rxPackets : parentMessage.rxPackets;
                if(rxPackets == null)
                    throw new NullPointerException("Property rxPackets must not be null");
                U64 txPackets = this.txPacketsSet ? this.txPackets : parentMessage.txPackets;
                if(txPackets == null)
                    throw new NullPointerException("Property txPackets must not be null");
                U64 rxBytes = this.rxBytesSet ? this.rxBytes : parentMessage.rxBytes;
                if(rxBytes == null)
                    throw new NullPointerException("Property rxBytes must not be null");
                U64 txBytes = this.txBytesSet ? this.txBytes : parentMessage.txBytes;
                if(txBytes == null)
                    throw new NullPointerException("Property txBytes must not be null");
                U64 rxDropped = this.rxDroppedSet ? this.rxDropped : parentMessage.rxDropped;
                if(rxDropped == null)
                    throw new NullPointerException("Property rxDropped must not be null");
                U64 txDropped = this.txDroppedSet ? this.txDropped : parentMessage.txDropped;
                if(txDropped == null)
                    throw new NullPointerException("Property txDropped must not be null");
                U64 rxErrors = this.rxErrorsSet ? this.rxErrors : parentMessage.rxErrors;
                if(rxErrors == null)
                    throw new NullPointerException("Property rxErrors must not be null");
                U64 txErrors = this.txErrorsSet ? this.txErrors : parentMessage.txErrors;
                if(txErrors == null)
                    throw new NullPointerException("Property txErrors must not be null");
                List<OFPortStatsProp> properties = this.propertiesSet ? this.properties : parentMessage.properties;
                if(properties == null)
                    throw new NullPointerException("Property properties must not be null");

                //
                return new OFPortStatsEntryVer14(
                    portNo,
                    durationSec,
                    durationNsec,
                    rxPackets,
                    txPackets,
                    rxBytes,
                    txBytes,
                    rxDropped,
                    txDropped,
                    rxErrors,
                    txErrors,
                    properties
                );
        }

    }

    static class Builder implements OFPortStatsEntry.Builder {
        // OF message fields
        private boolean portNoSet;
        private OFPort portNo;
        private boolean durationSecSet;
        private long durationSec;
        private boolean durationNsecSet;
        private long durationNsec;
        private boolean rxPacketsSet;
        private U64 rxPackets;
        private boolean txPacketsSet;
        private U64 txPackets;
        private boolean rxBytesSet;
        private U64 rxBytes;
        private boolean txBytesSet;
        private U64 txBytes;
        private boolean rxDroppedSet;
        private U64 rxDropped;
        private boolean txDroppedSet;
        private U64 txDropped;
        private boolean rxErrorsSet;
        private U64 rxErrors;
        private boolean txErrorsSet;
        private U64 txErrors;
        private boolean propertiesSet;
        private List<OFPortStatsProp> properties;

    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public OFPortStatsEntry.Builder setPortNo(OFPort portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public U64 getRxPackets() {
        return rxPackets;
    }

    @Override
    public OFPortStatsEntry.Builder setRxPackets(U64 rxPackets) {
        this.rxPackets = rxPackets;
        this.rxPacketsSet = true;
        return this;
    }
    @Override
    public U64 getTxPackets() {
        return txPackets;
    }

    @Override
    public OFPortStatsEntry.Builder setTxPackets(U64 txPackets) {
        this.txPackets = txPackets;
        this.txPacketsSet = true;
        return this;
    }
    @Override
    public U64 getRxBytes() {
        return rxBytes;
    }

    @Override
    public OFPortStatsEntry.Builder setRxBytes(U64 rxBytes) {
        this.rxBytes = rxBytes;
        this.rxBytesSet = true;
        return this;
    }
    @Override
    public U64 getTxBytes() {
        return txBytes;
    }

    @Override
    public OFPortStatsEntry.Builder setTxBytes(U64 txBytes) {
        this.txBytes = txBytes;
        this.txBytesSet = true;
        return this;
    }
    @Override
    public U64 getRxDropped() {
        return rxDropped;
    }

    @Override
    public OFPortStatsEntry.Builder setRxDropped(U64 rxDropped) {
        this.rxDropped = rxDropped;
        this.rxDroppedSet = true;
        return this;
    }
    @Override
    public U64 getTxDropped() {
        return txDropped;
    }

    @Override
    public OFPortStatsEntry.Builder setTxDropped(U64 txDropped) {
        this.txDropped = txDropped;
        this.txDroppedSet = true;
        return this;
    }
    @Override
    public U64 getRxErrors() {
        return rxErrors;
    }

    @Override
    public OFPortStatsEntry.Builder setRxErrors(U64 rxErrors) {
        this.rxErrors = rxErrors;
        this.rxErrorsSet = true;
        return this;
    }
    @Override
    public U64 getTxErrors() {
        return txErrors;
    }

    @Override
    public OFPortStatsEntry.Builder setTxErrors(U64 txErrors) {
        this.txErrors = txErrors;
        this.txErrorsSet = true;
        return this;
    }
    @Override
    public U64 getRxFrameErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxFrameErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxFrameErr(U64 rxFrameErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxFrameErr not supported in version 1.4");
    }
    @Override
    public U64 getRxOverErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxOverErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxOverErr(U64 rxOverErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxOverErr not supported in version 1.4");
    }
    @Override
    public U64 getRxCrcErr()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property rxCrcErr not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setRxCrcErr(U64 rxCrcErr) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property rxCrcErr not supported in version 1.4");
    }
    @Override
    public U64 getCollisions()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property collisions not supported in version 1.4");
    }

    @Override
    public OFPortStatsEntry.Builder setCollisions(U64 collisions) throws UnsupportedOperationException {
            throw new UnsupportedOperationException("Property collisions not supported in version 1.4");
    }
    @Override
    public long getDurationSec() {
        return durationSec;
    }

    @Override
    public OFPortStatsEntry.Builder setDurationSec(long durationSec) {
        this.durationSec = durationSec;
        this.durationSecSet = true;
        return this;
    }
    @Override
    public long getDurationNsec() {
        return durationNsec;
    }

    @Override
    public OFPortStatsEntry.Builder setDurationNsec(long durationNsec) {
        this.durationNsec = durationNsec;
        this.durationNsecSet = true;
        return this;
    }
    @Override
    public List<OFPortStatsProp> getProperties() {
        return properties;
    }

    @Override
    public OFPortStatsEntry.Builder setProperties(List<OFPortStatsProp> properties) {
        this.properties = properties;
        this.propertiesSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFPortStatsEntry build() {
            OFPort portNo = this.portNoSet ? this.portNo : DEFAULT_PORT_NO;
            if(portNo == null)
                throw new NullPointerException("Property portNo must not be null");
            long durationSec = this.durationSecSet ? this.durationSec : DEFAULT_DURATION_SEC;
            long durationNsec = this.durationNsecSet ? this.durationNsec : DEFAULT_DURATION_NSEC;
            U64 rxPackets = this.rxPacketsSet ? this.rxPackets : DEFAULT_RX_PACKETS;
            if(rxPackets == null)
                throw new NullPointerException("Property rxPackets must not be null");
            U64 txPackets = this.txPacketsSet ? this.txPackets : DEFAULT_TX_PACKETS;
            if(txPackets == null)
                throw new NullPointerException("Property txPackets must not be null");
            U64 rxBytes = this.rxBytesSet ? this.rxBytes : DEFAULT_RX_BYTES;
            if(rxBytes == null)
                throw new NullPointerException("Property rxBytes must not be null");
            U64 txBytes = this.txBytesSet ? this.txBytes : DEFAULT_TX_BYTES;
            if(txBytes == null)
                throw new NullPointerException("Property txBytes must not be null");
            U64 rxDropped = this.rxDroppedSet ? this.rxDropped : DEFAULT_RX_DROPPED;
            if(rxDropped == null)
                throw new NullPointerException("Property rxDropped must not be null");
            U64 txDropped = this.txDroppedSet ? this.txDropped : DEFAULT_TX_DROPPED;
            if(txDropped == null)
                throw new NullPointerException("Property txDropped must not be null");
            U64 rxErrors = this.rxErrorsSet ? this.rxErrors : DEFAULT_RX_ERRORS;
            if(rxErrors == null)
                throw new NullPointerException("Property rxErrors must not be null");
            U64 txErrors = this.txErrorsSet ? this.txErrors : DEFAULT_TX_ERRORS;
            if(txErrors == null)
                throw new NullPointerException("Property txErrors must not be null");
            List<OFPortStatsProp> properties = this.propertiesSet ? this.properties : DEFAULT_PROPERTIES;
            if(properties == null)
                throw new NullPointerException("Property properties must not be null");


            return new OFPortStatsEntryVer14(
                    portNo,
                    durationSec,
                    durationNsec,
                    rxPackets,
                    txPackets,
                    rxBytes,
                    txBytes,
                    rxDropped,
                    txDropped,
                    rxErrors,
                    txErrors,
                    properties
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFPortStatsEntry> {
        @Override
        public OFPortStatsEntry readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            int length = U16.f(bb.readShort());
            if(length < MINIMUM_LENGTH)
                throw new OFParseError("Wrong length: Expected to be >= " + MINIMUM_LENGTH + ", was: " + length);
            if(bb.readableBytes() + (bb.readerIndex() - start) < length) {
                // Buffer does not have all data yet
                bb.readerIndex(start);
                return null;
            }
            if(logger.isTraceEnabled())
                logger.trace("readFrom - length={}", length);
            // pad: 2 bytes
            bb.skipBytes(2);
            OFPort portNo = OFPort.read4Bytes(bb);
            long durationSec = U32.f(bb.readInt());
            long durationNsec = U32.f(bb.readInt());
            U64 rxPackets = U64.ofRaw(bb.readLong());
            U64 txPackets = U64.ofRaw(bb.readLong());
            U64 rxBytes = U64.ofRaw(bb.readLong());
            U64 txBytes = U64.ofRaw(bb.readLong());
            U64 rxDropped = U64.ofRaw(bb.readLong());
            U64 txDropped = U64.ofRaw(bb.readLong());
            U64 rxErrors = U64.ofRaw(bb.readLong());
            U64 txErrors = U64.ofRaw(bb.readLong());
            List<OFPortStatsProp> properties = ChannelUtils.readList(bb, length - (bb.readerIndex() - start), OFPortStatsPropVer14.READER);

            OFPortStatsEntryVer14 portStatsEntryVer14 = new OFPortStatsEntryVer14(
                    portNo,
                      durationSec,
                      durationNsec,
                      rxPackets,
                      txPackets,
                      rxBytes,
                      txBytes,
                      rxDropped,
                      txDropped,
                      rxErrors,
                      txErrors,
                      properties
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", portStatsEntryVer14);
            return portStatsEntryVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFPortStatsEntryVer14Funnel FUNNEL = new OFPortStatsEntryVer14Funnel();
    static class OFPortStatsEntryVer14Funnel implements Funnel<OFPortStatsEntryVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFPortStatsEntryVer14 message, PrimitiveSink sink) {
            // FIXME: skip funnel of length
            // skip pad (2 bytes)
            message.portNo.putTo(sink);
            sink.putLong(message.durationSec);
            sink.putLong(message.durationNsec);
            message.rxPackets.putTo(sink);
            message.txPackets.putTo(sink);
            message.rxBytes.putTo(sink);
            message.txBytes.putTo(sink);
            message.rxDropped.putTo(sink);
            message.txDropped.putTo(sink);
            message.rxErrors.putTo(sink);
            message.txErrors.putTo(sink);
            FunnelUtils.putList(message.properties, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFPortStatsEntryVer14> {
        @Override
        public void write(ByteBuf bb, OFPortStatsEntryVer14 message) {
            int startIndex = bb.writerIndex();
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            // pad: 2 bytes
            bb.writeZero(2);
            message.portNo.write4Bytes(bb);
            bb.writeInt(U32.t(message.durationSec));
            bb.writeInt(U32.t(message.durationNsec));
            bb.writeLong(message.rxPackets.getValue());
            bb.writeLong(message.txPackets.getValue());
            bb.writeLong(message.rxBytes.getValue());
            bb.writeLong(message.txBytes.getValue());
            bb.writeLong(message.rxDropped.getValue());
            bb.writeLong(message.txDropped.getValue());
            bb.writeLong(message.rxErrors.getValue());
            bb.writeLong(message.txErrors.getValue());
            ChannelUtils.writeList(bb, message.properties);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFPortStatsEntryVer14(");
        b.append("portNo=").append(portNo);
        b.append(", ");
        b.append("durationSec=").append(durationSec);
        b.append(", ");
        b.append("durationNsec=").append(durationNsec);
        b.append(", ");
        b.append("rxPackets=").append(rxPackets);
        b.append(", ");
        b.append("txPackets=").append(txPackets);
        b.append(", ");
        b.append("rxBytes=").append(rxBytes);
        b.append(", ");
        b.append("txBytes=").append(txBytes);
        b.append(", ");
        b.append("rxDropped=").append(rxDropped);
        b.append(", ");
        b.append("txDropped=").append(txDropped);
        b.append(", ");
        b.append("rxErrors=").append(rxErrors);
        b.append(", ");
        b.append("txErrors=").append(txErrors);
        b.append(", ");
        b.append("properties=").append(properties);
        b.append(")");
        return b.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        OFPortStatsEntryVer14 other = (OFPortStatsEntryVer14) obj;

        if (portNo == null) {
            if (other.portNo != null)
                return false;
        } else if (!portNo.equals(other.portNo))
            return false;
        if( durationSec != other.durationSec)
            return false;
        if( durationNsec != other.durationNsec)
            return false;
        if (rxPackets == null) {
            if (other.rxPackets != null)
                return false;
        } else if (!rxPackets.equals(other.rxPackets))
            return false;
        if (txPackets == null) {
            if (other.txPackets != null)
                return false;
        } else if (!txPackets.equals(other.txPackets))
            return false;
        if (rxBytes == null) {
            if (other.rxBytes != null)
                return false;
        } else if (!rxBytes.equals(other.rxBytes))
            return false;
        if (txBytes == null) {
            if (other.txBytes != null)
                return false;
        } else if (!txBytes.equals(other.txBytes))
            return false;
        if (rxDropped == null) {
            if (other.rxDropped != null)
                return false;
        } else if (!rxDropped.equals(other.rxDropped))
            return false;
        if (txDropped == null) {
            if (other.txDropped != null)
                return false;
        } else if (!txDropped.equals(other.txDropped))
            return false;
        if (rxErrors == null) {
            if (other.rxErrors != null)
                return false;
        } else if (!rxErrors.equals(other.rxErrors))
            return false;
        if (txErrors == null) {
            if (other.txErrors != null)
                return false;
        } else if (!txErrors.equals(other.txErrors))
            return false;
        if (properties == null) {
            if (other.properties != null)
                return false;
        } else if (!properties.equals(other.properties))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((portNo == null) ? 0 : portNo.hashCode());
        result = prime *  (int) (durationSec ^ (durationSec >>> 32));
        result = prime *  (int) (durationNsec ^ (durationNsec >>> 32));
        result = prime * result + ((rxPackets == null) ? 0 : rxPackets.hashCode());
        result = prime * result + ((txPackets == null) ? 0 : txPackets.hashCode());
        result = prime * result + ((rxBytes == null) ? 0 : rxBytes.hashCode());
        result = prime * result + ((txBytes == null) ? 0 : txBytes.hashCode());
        result = prime * result + ((rxDropped == null) ? 0 : rxDropped.hashCode());
        result = prime * result + ((txDropped == null) ? 0 : txDropped.hashCode());
        result = prime * result + ((rxErrors == null) ? 0 : rxErrors.hashCode());
        result = prime * result + ((txErrors == null) ? 0 : txErrors.hashCode());
        result = prime * result + ((properties == null) ? 0 : properties.hashCode());
        return result;
    }

}
