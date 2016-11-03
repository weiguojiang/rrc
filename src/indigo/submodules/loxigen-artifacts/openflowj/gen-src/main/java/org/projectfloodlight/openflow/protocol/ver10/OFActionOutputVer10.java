// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver10;

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

class OFActionOutputVer10 implements OFActionOutput {
    private static final Logger logger = LoggerFactory.getLogger(OFActionOutputVer10.class);
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int LENGTH = 8;

        private final static OFPort DEFAULT_PORT = OFPort.ANY;
        private final static int DEFAULT_MAX_LEN = 0x0;

    // OF message fields
    private final OFPort port;
    private final int maxLen;
//
    // Immutable default instance
    final static OFActionOutputVer10 DEFAULT = new OFActionOutputVer10(
        DEFAULT_PORT, DEFAULT_MAX_LEN
    );

    // package private constructor - used by readers, builders, and factory
    OFActionOutputVer10(OFPort port, int maxLen) {
        if(port == null) {
            throw new NullPointerException("OFActionOutputVer10: property port cannot be null");
        }
        this.port = port;
        this.maxLen = maxLen;
    }

    // Accessors for OF message fields
    @Override
    public OFActionType getType() {
        return OFActionType.OUTPUT;
    }

    @Override
    public OFPort getPort() {
        return port;
    }

    @Override
    public int getMaxLen() {
        return maxLen;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }



    public OFActionOutput.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFActionOutput.Builder {
        final OFActionOutputVer10 parentMessage;

        // OF message fields
        private boolean portSet;
        private OFPort port;
        private boolean maxLenSet;
        private int maxLen;

        BuilderWithParent(OFActionOutputVer10 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFActionType getType() {
        return OFActionType.OUTPUT;
    }

    @Override
    public OFPort getPort() {
        return port;
    }

    @Override
    public OFActionOutput.Builder setPort(OFPort port) {
        this.port = port;
        this.portSet = true;
        return this;
    }
    @Override
    public int getMaxLen() {
        return maxLen;
    }

    @Override
    public OFActionOutput.Builder setMaxLen(int maxLen) {
        this.maxLen = maxLen;
        this.maxLenSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }



        @Override
        public OFActionOutput build() {
                OFPort port = this.portSet ? this.port : parentMessage.port;
                if(port == null)
                    throw new NullPointerException("Property port must not be null");
                int maxLen = this.maxLenSet ? this.maxLen : parentMessage.maxLen;

                //
                return new OFActionOutputVer10(
                    port,
                    maxLen
                );
        }

    }

    static class Builder implements OFActionOutput.Builder {
        // OF message fields
        private boolean portSet;
        private OFPort port;
        private boolean maxLenSet;
        private int maxLen;

    @Override
    public OFActionType getType() {
        return OFActionType.OUTPUT;
    }

    @Override
    public OFPort getPort() {
        return port;
    }

    @Override
    public OFActionOutput.Builder setPort(OFPort port) {
        this.port = port;
        this.portSet = true;
        return this;
    }
    @Override
    public int getMaxLen() {
        return maxLen;
    }

    @Override
    public OFActionOutput.Builder setMaxLen(int maxLen) {
        this.maxLen = maxLen;
        this.maxLenSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }

//
        @Override
        public OFActionOutput build() {
            OFPort port = this.portSet ? this.port : DEFAULT_PORT;
            if(port == null)
                throw new NullPointerException("Property port must not be null");
            int maxLen = this.maxLenSet ? this.maxLen : DEFAULT_MAX_LEN;


            return new OFActionOutputVer10(
                    port,
                    maxLen
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFActionOutput> {
        @Override
        public OFActionOutput readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 0
            short type = bb.readShort();
            if(type != (short) 0x0)
                throw new OFParseError("Wrong type: Expected=OFActionType.OUTPUT(0), got="+type);
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
            OFPort port = OFPort.read2Bytes(bb);
            int maxLen = U16.f(bb.readShort());

            OFActionOutputVer10 actionOutputVer10 = new OFActionOutputVer10(
                    port,
                      maxLen
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", actionOutputVer10);
            return actionOutputVer10;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFActionOutputVer10Funnel FUNNEL = new OFActionOutputVer10Funnel();
    static class OFActionOutputVer10Funnel implements Funnel<OFActionOutputVer10> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFActionOutputVer10 message, PrimitiveSink sink) {
            // fixed value property type = 0
            sink.putShort((short) 0x0);
            // fixed value property length = 8
            sink.putShort((short) 0x8);
            message.port.putTo(sink);
            sink.putInt(message.maxLen);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFActionOutputVer10> {
        @Override
        public void write(ByteBuf bb, OFActionOutputVer10 message) {
            // fixed value property type = 0
            bb.writeShort((short) 0x0);
            // fixed value property length = 8
            bb.writeShort((short) 0x8);
            message.port.write2Bytes(bb);
            bb.writeShort(U16.t(message.maxLen));


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFActionOutputVer10(");
        b.append("port=").append(port);
        b.append(", ");
        b.append("maxLen=").append(maxLen);
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
        OFActionOutputVer10 other = (OFActionOutputVer10) obj;

        if (port == null) {
            if (other.port != null)
                return false;
        } else if (!port.equals(other.port))
            return false;
        if( maxLen != other.maxLen)
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((port == null) ? 0 : port.hashCode());
        result = prime * result + maxLen;
        return result;
    }

}
