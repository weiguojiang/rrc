// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver12;

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

class OFOxmIpProtoVer12 implements OFOxmIpProto {
    private static final Logger logger = LoggerFactory.getLogger(OFOxmIpProtoVer12.class);
    // version: 1.2
    final static byte WIRE_VERSION = 3;
    final static int LENGTH = 5;

        private final static IpProtocol DEFAULT_VALUE = IpProtocol.NONE;

    // OF message fields
    private final IpProtocol value;
//
    // Immutable default instance
    final static OFOxmIpProtoVer12 DEFAULT = new OFOxmIpProtoVer12(
        DEFAULT_VALUE
    );

    // package private constructor - used by readers, builders, and factory
    OFOxmIpProtoVer12(IpProtocol value) {
        if(value == null) {
            throw new NullPointerException("OFOxmIpProtoVer12: property value cannot be null");
        }
        this.value = value;
    }

    // Accessors for OF message fields
    @Override
    public long getTypeLen() {
        return 0x80001401L;
    }

    @Override
    public IpProtocol getValue() {
        return value;
    }

    @Override
    public MatchField<IpProtocol> getMatchField() {
        return MatchField.IP_PROTO;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    public OFOxm<IpProtocol> getCanonical() {
        // exact match OXM is always canonical
        return this;
    }

    @Override
    public IpProtocol getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



    public OFOxmIpProto.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFOxmIpProto.Builder {
        final OFOxmIpProtoVer12 parentMessage;

        // OF message fields
        private boolean valueSet;
        private IpProtocol value;

        BuilderWithParent(OFOxmIpProtoVer12 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getTypeLen() {
        return 0x80001401L;
    }

    @Override
    public IpProtocol getValue() {
        return value;
    }

    @Override
    public OFOxmIpProto.Builder setValue(IpProtocol value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public MatchField<IpProtocol> getMatchField() {
        return MatchField.IP_PROTO;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    @Override
    public OFOxm<IpProtocol> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public IpProtocol getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



        @Override
        public OFOxmIpProto build() {
                IpProtocol value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");

                //
                return new OFOxmIpProtoVer12(
                    value
                );
        }

    }

    static class Builder implements OFOxmIpProto.Builder {
        // OF message fields
        private boolean valueSet;
        private IpProtocol value;

    @Override
    public long getTypeLen() {
        return 0x80001401L;
    }

    @Override
    public IpProtocol getValue() {
        return value;
    }

    @Override
    public OFOxmIpProto.Builder setValue(IpProtocol value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public MatchField<IpProtocol> getMatchField() {
        return MatchField.IP_PROTO;
    }

    @Override
    public boolean isMasked() {
        return false;
    }

    @Override
    public OFOxm<IpProtocol> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public IpProtocol getMask()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property mask not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }

//
        @Override
        public OFOxmIpProto build() {
            IpProtocol value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");


            return new OFOxmIpProtoVer12(
                    value
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFOxmIpProto> {
        @Override
        public OFOxmIpProto readFrom(ByteBuf bb) throws OFParseError {
            // fixed value property typeLen == 0x80001401L
            int typeLen = bb.readInt();
            if(typeLen != (int) 0x80001401)
                throw new OFParseError("Wrong typeLen: Expected=0x80001401L(0x80001401L), got="+typeLen);
            IpProtocol value = IpProtocol.readByte(bb);

            OFOxmIpProtoVer12 oxmIpProtoVer12 = new OFOxmIpProtoVer12(
                    value
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", oxmIpProtoVer12);
            return oxmIpProtoVer12;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFOxmIpProtoVer12Funnel FUNNEL = new OFOxmIpProtoVer12Funnel();
    static class OFOxmIpProtoVer12Funnel implements Funnel<OFOxmIpProtoVer12> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFOxmIpProtoVer12 message, PrimitiveSink sink) {
            // fixed value property typeLen = 0x80001401L
            sink.putInt((int) 0x80001401);
            message.value.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFOxmIpProtoVer12> {
        @Override
        public void write(ByteBuf bb, OFOxmIpProtoVer12 message) {
            // fixed value property typeLen = 0x80001401L
            bb.writeInt((int) 0x80001401);
            message.value.writeByte(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFOxmIpProtoVer12(");
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
        OFOxmIpProtoVer12 other = (OFOxmIpProtoVer12) obj;

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
