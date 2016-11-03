// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver13;

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

class OFOxmTcpSrcVer13 implements OFOxmTcpSrc {
    private static final Logger logger = LoggerFactory.getLogger(OFOxmTcpSrcVer13.class);
    // version: 1.3
    final static byte WIRE_VERSION = 4;
    final static int LENGTH = 6;

        private final static TransportPort DEFAULT_VALUE = TransportPort.NONE;

    // OF message fields
    private final TransportPort value;
//
    // Immutable default instance
    final static OFOxmTcpSrcVer13 DEFAULT = new OFOxmTcpSrcVer13(
        DEFAULT_VALUE
    );

    // package private constructor - used by readers, builders, and factory
    OFOxmTcpSrcVer13(TransportPort value) {
        if(value == null) {
            throw new NullPointerException("OFOxmTcpSrcVer13: property value cannot be null");
        }
        this.value = value;
    }

    // Accessors for OF message fields
    @Override
    public long getTypeLen() {
        return 0x80001a02L;
    }

    @Override
    public TransportPort getValue() {
        return value;
    }

    @Override
    public MatchField<TransportPort> getMatchField() {
        return MatchField.TCP_SRC;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    public OFOxm<TransportPort> getCanonical() {
        // exact match OXM is always canonical
        return this;
    }

    @Override
    public TransportPort getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.3");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_13;
    }



    public OFOxmTcpSrc.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFOxmTcpSrc.Builder {
        final OFOxmTcpSrcVer13 parentMessage;

        // OF message fields
        private boolean valueSet;
        private TransportPort value;

        BuilderWithParent(OFOxmTcpSrcVer13 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getTypeLen() {
        return 0x80001a02L;
    }

    @Override
    public TransportPort getValue() {
        return value;
    }

    @Override
    public OFOxmTcpSrc.Builder setValue(TransportPort value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public MatchField<TransportPort> getMatchField() {
        return MatchField.TCP_SRC;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    @Override
    public OFOxm<TransportPort> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.3");
    }

    @Override
    public TransportPort getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.3");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_13;
    }



        @Override
        public OFOxmTcpSrc build() {
                TransportPort value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");

                //
                return new OFOxmTcpSrcVer13(
                    value
                );
        }

    }

    static class Builder implements OFOxmTcpSrc.Builder {
        // OF message fields
        private boolean valueSet;
        private TransportPort value;

    @Override
    public long getTypeLen() {
        return 0x80001a02L;
    }

    @Override
    public TransportPort getValue() {
        return value;
    }

    @Override
    public OFOxmTcpSrc.Builder setValue(TransportPort value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public MatchField<TransportPort> getMatchField() {
        return MatchField.TCP_SRC;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    @Override
    public OFOxm<TransportPort> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.3");
    }

    @Override
    public TransportPort getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.3");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_13;
    }

//
        @Override
        public OFOxmTcpSrc build() {
            TransportPort value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");


            return new OFOxmTcpSrcVer13(
                    value
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFOxmTcpSrc> {
        @Override
        public OFOxmTcpSrc readFrom(ByteBuf bb) throws OFParseError {
            // fixed value property typeLen == 0x80001a02L
            int typeLen = bb.readInt();
            if(typeLen != (int) 0x80001a02)
                throw new OFParseError("Wrong typeLen: Expected=0x80001a02L(0x80001a02L), got="+typeLen);
            TransportPort value = TransportPort.read2Bytes(bb);

            OFOxmTcpSrcVer13 oxmTcpSrcVer13 = new OFOxmTcpSrcVer13(
                    value
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", oxmTcpSrcVer13);
            return oxmTcpSrcVer13;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFOxmTcpSrcVer13Funnel FUNNEL = new OFOxmTcpSrcVer13Funnel();
    static class OFOxmTcpSrcVer13Funnel implements Funnel<OFOxmTcpSrcVer13> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFOxmTcpSrcVer13 message, PrimitiveSink sink) {
            // fixed value property typeLen = 0x80001a02L
            sink.putInt((int) 0x80001a02);
            message.value.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFOxmTcpSrcVer13> {
        @Override
        public void write(ByteBuf bb, OFOxmTcpSrcVer13 message) {
            // fixed value property typeLen = 0x80001a02L
            bb.writeInt((int) 0x80001a02);
            message.value.write2Bytes(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFOxmTcpSrcVer13(");
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
        OFOxmTcpSrcVer13 other = (OFOxmTcpSrcVer13) obj;

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
