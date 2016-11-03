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
import java.util.Set;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFMeterBandStatsVer14 implements OFMeterBandStats {
    private static final Logger logger = LoggerFactory.getLogger(OFMeterBandStatsVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int LENGTH = 16;

        private final static U64 DEFAULT_PACKET_BAND_COUNT = U64.ZERO;
        private final static U64 DEFAULT_BYTE_BAND_COUNT = U64.ZERO;

    // OF message fields
    private final U64 packetBandCount;
    private final U64 byteBandCount;
//
    // Immutable default instance
    final static OFMeterBandStatsVer14 DEFAULT = new OFMeterBandStatsVer14(
        DEFAULT_PACKET_BAND_COUNT, DEFAULT_BYTE_BAND_COUNT
    );

    // package private constructor - used by readers, builders, and factory
    OFMeterBandStatsVer14(U64 packetBandCount, U64 byteBandCount) {
        if(packetBandCount == null) {
            throw new NullPointerException("OFMeterBandStatsVer14: property packetBandCount cannot be null");
        }
        if(byteBandCount == null) {
            throw new NullPointerException("OFMeterBandStatsVer14: property byteBandCount cannot be null");
        }
        this.packetBandCount = packetBandCount;
        this.byteBandCount = byteBandCount;
    }

    // Accessors for OF message fields
    @Override
    public U64 getPacketBandCount() {
        return packetBandCount;
    }

    @Override
    public U64 getByteBandCount() {
        return byteBandCount;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFMeterBandStats.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFMeterBandStats.Builder {
        final OFMeterBandStatsVer14 parentMessage;

        // OF message fields
        private boolean packetBandCountSet;
        private U64 packetBandCount;
        private boolean byteBandCountSet;
        private U64 byteBandCount;

        BuilderWithParent(OFMeterBandStatsVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public U64 getPacketBandCount() {
        return packetBandCount;
    }

    @Override
    public OFMeterBandStats.Builder setPacketBandCount(U64 packetBandCount) {
        this.packetBandCount = packetBandCount;
        this.packetBandCountSet = true;
        return this;
    }
    @Override
    public U64 getByteBandCount() {
        return byteBandCount;
    }

    @Override
    public OFMeterBandStats.Builder setByteBandCount(U64 byteBandCount) {
        this.byteBandCount = byteBandCount;
        this.byteBandCountSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFMeterBandStats build() {
                U64 packetBandCount = this.packetBandCountSet ? this.packetBandCount : parentMessage.packetBandCount;
                if(packetBandCount == null)
                    throw new NullPointerException("Property packetBandCount must not be null");
                U64 byteBandCount = this.byteBandCountSet ? this.byteBandCount : parentMessage.byteBandCount;
                if(byteBandCount == null)
                    throw new NullPointerException("Property byteBandCount must not be null");

                //
                return new OFMeterBandStatsVer14(
                    packetBandCount,
                    byteBandCount
                );
        }

    }

    static class Builder implements OFMeterBandStats.Builder {
        // OF message fields
        private boolean packetBandCountSet;
        private U64 packetBandCount;
        private boolean byteBandCountSet;
        private U64 byteBandCount;

    @Override
    public U64 getPacketBandCount() {
        return packetBandCount;
    }

    @Override
    public OFMeterBandStats.Builder setPacketBandCount(U64 packetBandCount) {
        this.packetBandCount = packetBandCount;
        this.packetBandCountSet = true;
        return this;
    }
    @Override
    public U64 getByteBandCount() {
        return byteBandCount;
    }

    @Override
    public OFMeterBandStats.Builder setByteBandCount(U64 byteBandCount) {
        this.byteBandCount = byteBandCount;
        this.byteBandCountSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFMeterBandStats build() {
            U64 packetBandCount = this.packetBandCountSet ? this.packetBandCount : DEFAULT_PACKET_BAND_COUNT;
            if(packetBandCount == null)
                throw new NullPointerException("Property packetBandCount must not be null");
            U64 byteBandCount = this.byteBandCountSet ? this.byteBandCount : DEFAULT_BYTE_BAND_COUNT;
            if(byteBandCount == null)
                throw new NullPointerException("Property byteBandCount must not be null");


            return new OFMeterBandStatsVer14(
                    packetBandCount,
                    byteBandCount
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFMeterBandStats> {
        @Override
        public OFMeterBandStats readFrom(ByteBuf bb) throws OFParseError {
            U64 packetBandCount = U64.ofRaw(bb.readLong());
            U64 byteBandCount = U64.ofRaw(bb.readLong());

            OFMeterBandStatsVer14 meterBandStatsVer14 = new OFMeterBandStatsVer14(
                    packetBandCount,
                      byteBandCount
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", meterBandStatsVer14);
            return meterBandStatsVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFMeterBandStatsVer14Funnel FUNNEL = new OFMeterBandStatsVer14Funnel();
    static class OFMeterBandStatsVer14Funnel implements Funnel<OFMeterBandStatsVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFMeterBandStatsVer14 message, PrimitiveSink sink) {
            message.packetBandCount.putTo(sink);
            message.byteBandCount.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFMeterBandStatsVer14> {
        @Override
        public void write(ByteBuf bb, OFMeterBandStatsVer14 message) {
            bb.writeLong(message.packetBandCount.getValue());
            bb.writeLong(message.byteBandCount.getValue());


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFMeterBandStatsVer14(");
        b.append("packetBandCount=").append(packetBandCount);
        b.append(", ");
        b.append("byteBandCount=").append(byteBandCount);
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
        OFMeterBandStatsVer14 other = (OFMeterBandStatsVer14) obj;

        if (packetBandCount == null) {
            if (other.packetBandCount != null)
                return false;
        } else if (!packetBandCount.equals(other.packetBandCount))
            return false;
        if (byteBandCount == null) {
            if (other.byteBandCount != null)
                return false;
        } else if (!byteBandCount.equals(other.byteBandCount))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((packetBandCount == null) ? 0 : packetBandCount.hashCode());
        result = prime * result + ((byteBandCount == null) ? 0 : byteBandCount.hashCode());
        return result;
    }

}
