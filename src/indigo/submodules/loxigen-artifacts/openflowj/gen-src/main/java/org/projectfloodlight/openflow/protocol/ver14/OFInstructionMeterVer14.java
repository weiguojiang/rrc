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

class OFInstructionMeterVer14 implements OFInstructionMeter {
    private static final Logger logger = LoggerFactory.getLogger(OFInstructionMeterVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int LENGTH = 8;

        private final static long DEFAULT_METER_ID = 0x0L;

    // OF message fields
    private final long meterId;
//
    // Immutable default instance
    final static OFInstructionMeterVer14 DEFAULT = new OFInstructionMeterVer14(
        DEFAULT_METER_ID
    );

    // package private constructor - used by readers, builders, and factory
    OFInstructionMeterVer14(long meterId) {
        this.meterId = meterId;
    }

    // Accessors for OF message fields
    @Override
    public OFInstructionType getType() {
        return OFInstructionType.METER;
    }

    @Override
    public long getMeterId() {
        return meterId;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFInstructionMeter.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFInstructionMeter.Builder {
        final OFInstructionMeterVer14 parentMessage;

        // OF message fields
        private boolean meterIdSet;
        private long meterId;

        BuilderWithParent(OFInstructionMeterVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFInstructionType getType() {
        return OFInstructionType.METER;
    }

    @Override
    public long getMeterId() {
        return meterId;
    }

    @Override
    public OFInstructionMeter.Builder setMeterId(long meterId) {
        this.meterId = meterId;
        this.meterIdSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFInstructionMeter build() {
                long meterId = this.meterIdSet ? this.meterId : parentMessage.meterId;

                //
                return new OFInstructionMeterVer14(
                    meterId
                );
        }

    }

    static class Builder implements OFInstructionMeter.Builder {
        // OF message fields
        private boolean meterIdSet;
        private long meterId;

    @Override
    public OFInstructionType getType() {
        return OFInstructionType.METER;
    }

    @Override
    public long getMeterId() {
        return meterId;
    }

    @Override
    public OFInstructionMeter.Builder setMeterId(long meterId) {
        this.meterId = meterId;
        this.meterIdSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFInstructionMeter build() {
            long meterId = this.meterIdSet ? this.meterId : DEFAULT_METER_ID;


            return new OFInstructionMeterVer14(
                    meterId
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFInstructionMeter> {
        @Override
        public OFInstructionMeter readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 6
            short type = bb.readShort();
            if(type != (short) 0x6)
                throw new OFParseError("Wrong type: Expected=OFInstructionType.METER(6), got="+type);
            int length = U16.f(bb.readShort());
            if(length != 8)
                throw new OFParseError("Wrong length: Expected=8(8), got="+length);
            if(bb.readableBytes() + (bb.readerIndex() - start) < length) {
                // Buffer does not have all data yet
                bb.readerIndex(start);
                return null;
            }
            if(logger.isTraceEnabled())
                logger.trace("readFrom - length={}", length);
            long meterId = U32.f(bb.readInt());

            OFInstructionMeterVer14 instructionMeterVer14 = new OFInstructionMeterVer14(
                    meterId
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", instructionMeterVer14);
            return instructionMeterVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFInstructionMeterVer14Funnel FUNNEL = new OFInstructionMeterVer14Funnel();
    static class OFInstructionMeterVer14Funnel implements Funnel<OFInstructionMeterVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFInstructionMeterVer14 message, PrimitiveSink sink) {
            // fixed value property type = 6
            sink.putShort((short) 0x6);
            // fixed value property length = 8
            sink.putShort((short) 0x8);
            sink.putLong(message.meterId);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFInstructionMeterVer14> {
        @Override
        public void write(ByteBuf bb, OFInstructionMeterVer14 message) {
            // fixed value property type = 6
            bb.writeShort((short) 0x6);
            // fixed value property length = 8
            bb.writeShort((short) 0x8);
            bb.writeInt(U32.t(message.meterId));


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFInstructionMeterVer14(");
        b.append("meterId=").append(meterId);
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
        OFInstructionMeterVer14 other = (OFInstructionMeterVer14) obj;

        if( meterId != other.meterId)
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime *  (int) (meterId ^ (meterId >>> 32));
        return result;
    }

}
