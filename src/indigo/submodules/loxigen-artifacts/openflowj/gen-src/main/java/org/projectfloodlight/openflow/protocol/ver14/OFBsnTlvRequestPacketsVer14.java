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

class OFBsnTlvRequestPacketsVer14 implements OFBsnTlvRequestPackets {
    private static final Logger logger = LoggerFactory.getLogger(OFBsnTlvRequestPacketsVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int LENGTH = 12;

        private final static U64 DEFAULT_VALUE = U64.ZERO;

    // OF message fields
    private final U64 value;
//
    // Immutable default instance
    final static OFBsnTlvRequestPacketsVer14 DEFAULT = new OFBsnTlvRequestPacketsVer14(
        DEFAULT_VALUE
    );

    // package private constructor - used by readers, builders, and factory
    OFBsnTlvRequestPacketsVer14(U64 value) {
        if(value == null) {
            throw new NullPointerException("OFBsnTlvRequestPacketsVer14: property value cannot be null");
        }
        this.value = value;
    }

    // Accessors for OF message fields
    @Override
    public int getType() {
        return 0xb;
    }

    @Override
    public U64 getValue() {
        return value;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFBsnTlvRequestPackets.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFBsnTlvRequestPackets.Builder {
        final OFBsnTlvRequestPacketsVer14 parentMessage;

        // OF message fields
        private boolean valueSet;
        private U64 value;

        BuilderWithParent(OFBsnTlvRequestPacketsVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public int getType() {
        return 0xb;
    }

    @Override
    public U64 getValue() {
        return value;
    }

    @Override
    public OFBsnTlvRequestPackets.Builder setValue(U64 value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFBsnTlvRequestPackets build() {
                U64 value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");

                //
                return new OFBsnTlvRequestPacketsVer14(
                    value
                );
        }

    }

    static class Builder implements OFBsnTlvRequestPackets.Builder {
        // OF message fields
        private boolean valueSet;
        private U64 value;

    @Override
    public int getType() {
        return 0xb;
    }

    @Override
    public U64 getValue() {
        return value;
    }

    @Override
    public OFBsnTlvRequestPackets.Builder setValue(U64 value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFBsnTlvRequestPackets build() {
            U64 value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");


            return new OFBsnTlvRequestPacketsVer14(
                    value
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFBsnTlvRequestPackets> {
        @Override
        public OFBsnTlvRequestPackets readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 0xb
            short type = bb.readShort();
            if(type != (short) 0xb)
                throw new OFParseError("Wrong type: Expected=0xb(0xb), got="+type);
            int length = U16.f(bb.readShort());
            if(length != 12)
                throw new OFParseError("Wrong length: Expected=12(12), got="+length);
            if(bb.readableBytes() + (bb.readerIndex() - start) < length) {
                // Buffer does not have all data yet
                bb.readerIndex(start);
                return null;
            }
            if(logger.isTraceEnabled())
                logger.trace("readFrom - length={}", length);
            U64 value = U64.ofRaw(bb.readLong());

            OFBsnTlvRequestPacketsVer14 bsnTlvRequestPacketsVer14 = new OFBsnTlvRequestPacketsVer14(
                    value
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", bsnTlvRequestPacketsVer14);
            return bsnTlvRequestPacketsVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFBsnTlvRequestPacketsVer14Funnel FUNNEL = new OFBsnTlvRequestPacketsVer14Funnel();
    static class OFBsnTlvRequestPacketsVer14Funnel implements Funnel<OFBsnTlvRequestPacketsVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFBsnTlvRequestPacketsVer14 message, PrimitiveSink sink) {
            // fixed value property type = 0xb
            sink.putShort((short) 0xb);
            // fixed value property length = 12
            sink.putShort((short) 0xc);
            message.value.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFBsnTlvRequestPacketsVer14> {
        @Override
        public void write(ByteBuf bb, OFBsnTlvRequestPacketsVer14 message) {
            // fixed value property type = 0xb
            bb.writeShort((short) 0xb);
            // fixed value property length = 12
            bb.writeShort((short) 0xc);
            bb.writeLong(message.value.getValue());


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFBsnTlvRequestPacketsVer14(");
        b.append("value=").append(value);
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
        OFBsnTlvRequestPacketsVer14 other = (OFBsnTlvRequestPacketsVer14) obj;

        if (value == null) {
            if (other.value != null)
                return false;
        } else if (!value.equals(other.value))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((value == null) ? 0 : value.hashCode());
        return result;
    }

}
