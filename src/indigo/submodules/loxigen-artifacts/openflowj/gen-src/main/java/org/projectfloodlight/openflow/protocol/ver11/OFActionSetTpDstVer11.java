// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver11;

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
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFActionSetTpDstVer11 implements OFActionSetTpDst {
    private static final Logger logger = LoggerFactory.getLogger(OFActionSetTpDstVer11.class);
    // version: 1.1
    final static byte WIRE_VERSION = 2;
    final static int LENGTH = 8;

        private final static TransportPort DEFAULT_TP_PORT = TransportPort.NONE;

    // OF message fields
    private final TransportPort tpPort;
//
    // Immutable default instance
    final static OFActionSetTpDstVer11 DEFAULT = new OFActionSetTpDstVer11(
        DEFAULT_TP_PORT
    );

    // package private constructor - used by readers, builders, and factory
    OFActionSetTpDstVer11(TransportPort tpPort) {
        if(tpPort == null) {
            throw new NullPointerException("OFActionSetTpDstVer11: property tpPort cannot be null");
        }
        this.tpPort = tpPort;
    }

    // Accessors for OF message fields
    @Override
    public OFActionType getType() {
        return OFActionType.SET_TP_DST;
    }

    @Override
    public TransportPort getTpPort() {
        return tpPort;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_11;
    }



    public OFActionSetTpDst.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFActionSetTpDst.Builder {
        final OFActionSetTpDstVer11 parentMessage;

        // OF message fields
        private boolean tpPortSet;
        private TransportPort tpPort;

        BuilderWithParent(OFActionSetTpDstVer11 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFActionType getType() {
        return OFActionType.SET_TP_DST;
    }

    @Override
    public TransportPort getTpPort() {
        return tpPort;
    }

    @Override
    public OFActionSetTpDst.Builder setTpPort(TransportPort tpPort) {
        this.tpPort = tpPort;
        this.tpPortSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_11;
    }



        @Override
        public OFActionSetTpDst build() {
                TransportPort tpPort = this.tpPortSet ? this.tpPort : parentMessage.tpPort;
                if(tpPort == null)
                    throw new NullPointerException("Property tpPort must not be null");

                //
                return new OFActionSetTpDstVer11(
                    tpPort
                );
        }

    }

    static class Builder implements OFActionSetTpDst.Builder {
        // OF message fields
        private boolean tpPortSet;
        private TransportPort tpPort;

    @Override
    public OFActionType getType() {
        return OFActionType.SET_TP_DST;
    }

    @Override
    public TransportPort getTpPort() {
        return tpPort;
    }

    @Override
    public OFActionSetTpDst.Builder setTpPort(TransportPort tpPort) {
        this.tpPort = tpPort;
        this.tpPortSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_11;
    }

//
        @Override
        public OFActionSetTpDst build() {
            TransportPort tpPort = this.tpPortSet ? this.tpPort : DEFAULT_TP_PORT;
            if(tpPort == null)
                throw new NullPointerException("Property tpPort must not be null");


            return new OFActionSetTpDstVer11(
                    tpPort
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFActionSetTpDst> {
        @Override
        public OFActionSetTpDst readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 10
            short type = bb.readShort();
            if(type != (short) 0xa)
                throw new OFParseError("Wrong type: Expected=OFActionType.SET_TP_DST(10), got="+type);
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
            TransportPort tpPort = TransportPort.read2Bytes(bb);
            // pad: 2 bytes
            bb.skipBytes(2);

            OFActionSetTpDstVer11 actionSetTpDstVer11 = new OFActionSetTpDstVer11(
                    tpPort
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", actionSetTpDstVer11);
            return actionSetTpDstVer11;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFActionSetTpDstVer11Funnel FUNNEL = new OFActionSetTpDstVer11Funnel();
    static class OFActionSetTpDstVer11Funnel implements Funnel<OFActionSetTpDstVer11> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFActionSetTpDstVer11 message, PrimitiveSink sink) {
            // fixed value property type = 10
            sink.putShort((short) 0xa);
            // fixed value property length = 8
            sink.putShort((short) 0x8);
            message.tpPort.putTo(sink);
            // skip pad (2 bytes)
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFActionSetTpDstVer11> {
        @Override
        public void write(ByteBuf bb, OFActionSetTpDstVer11 message) {
            // fixed value property type = 10
            bb.writeShort((short) 0xa);
            // fixed value property length = 8
            bb.writeShort((short) 0x8);
            message.tpPort.write2Bytes(bb);
            // pad: 2 bytes
            bb.writeZero(2);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFActionSetTpDstVer11(");
        b.append("tpPort=").append(tpPort);
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
        OFActionSetTpDstVer11 other = (OFActionSetTpDstVer11) obj;

        if (tpPort == null) {
            if (other.tpPort != null)
                return false;
        } else if (!tpPort.equals(other.tpPort))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((tpPort == null) ? 0 : tpPort.hashCode());
        return result;
    }

}
