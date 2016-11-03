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

class OFActionBsnChecksumVer10 implements OFActionBsnChecksum {
    private static final Logger logger = LoggerFactory.getLogger(OFActionBsnChecksumVer10.class);
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int LENGTH = 28;

        private final static U128 DEFAULT_CHECKSUM = U128.ZERO;

    // OF message fields
    private final U128 checksum;
//
    // Immutable default instance
    final static OFActionBsnChecksumVer10 DEFAULT = new OFActionBsnChecksumVer10(
        DEFAULT_CHECKSUM
    );

    // package private constructor - used by readers, builders, and factory
    OFActionBsnChecksumVer10(U128 checksum) {
        if(checksum == null) {
            throw new NullPointerException("OFActionBsnChecksumVer10: property checksum cannot be null");
        }
        this.checksum = checksum;
    }

    // Accessors for OF message fields
    @Override
    public OFActionType getType() {
        return OFActionType.EXPERIMENTER;
    }

    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x4L;
    }

    @Override
    public U128 getChecksum() {
        return checksum;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }



    public OFActionBsnChecksum.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFActionBsnChecksum.Builder {
        final OFActionBsnChecksumVer10 parentMessage;

        // OF message fields
        private boolean checksumSet;
        private U128 checksum;

        BuilderWithParent(OFActionBsnChecksumVer10 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFActionType getType() {
        return OFActionType.EXPERIMENTER;
    }

    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x4L;
    }

    @Override
    public U128 getChecksum() {
        return checksum;
    }

    @Override
    public OFActionBsnChecksum.Builder setChecksum(U128 checksum) {
        this.checksum = checksum;
        this.checksumSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }



        @Override
        public OFActionBsnChecksum build() {
                U128 checksum = this.checksumSet ? this.checksum : parentMessage.checksum;
                if(checksum == null)
                    throw new NullPointerException("Property checksum must not be null");

                //
                return new OFActionBsnChecksumVer10(
                    checksum
                );
        }

    }

    static class Builder implements OFActionBsnChecksum.Builder {
        // OF message fields
        private boolean checksumSet;
        private U128 checksum;

    @Override
    public OFActionType getType() {
        return OFActionType.EXPERIMENTER;
    }

    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x4L;
    }

    @Override
    public U128 getChecksum() {
        return checksum;
    }

    @Override
    public OFActionBsnChecksum.Builder setChecksum(U128 checksum) {
        this.checksum = checksum;
        this.checksumSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }

//
        @Override
        public OFActionBsnChecksum build() {
            U128 checksum = this.checksumSet ? this.checksum : DEFAULT_CHECKSUM;
            if(checksum == null)
                throw new NullPointerException("Property checksum must not be null");


            return new OFActionBsnChecksumVer10(
                    checksum
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFActionBsnChecksum> {
        @Override
        public OFActionBsnChecksum readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 65535
            short type = bb.readShort();
            if(type != (short) 0xffff)
                throw new OFParseError("Wrong type: Expected=OFActionType.EXPERIMENTER(65535), got="+type);
            int length = U16.f(bb.readShort());
            if(length != 28)
                throw new OFParseError("Wrong length: Expected=28(28), got="+length);
            if(bb.readableBytes() + (bb.readerIndex() - start) < length) {
                // Buffer does not have all data yet
                bb.readerIndex(start);
                return null;
            }
            if(logger.isTraceEnabled())
                logger.trace("readFrom - length={}", length);
            // fixed value property experimenter == 0x5c16c7L
            int experimenter = bb.readInt();
            if(experimenter != 0x5c16c7)
                throw new OFParseError("Wrong experimenter: Expected=0x5c16c7L(0x5c16c7L), got="+experimenter);
            // fixed value property subtype == 0x4L
            int subtype = bb.readInt();
            if(subtype != 0x4)
                throw new OFParseError("Wrong subtype: Expected=0x4L(0x4L), got="+subtype);
            U128 checksum = U128.read16Bytes(bb);

            OFActionBsnChecksumVer10 actionBsnChecksumVer10 = new OFActionBsnChecksumVer10(
                    checksum
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", actionBsnChecksumVer10);
            return actionBsnChecksumVer10;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFActionBsnChecksumVer10Funnel FUNNEL = new OFActionBsnChecksumVer10Funnel();
    static class OFActionBsnChecksumVer10Funnel implements Funnel<OFActionBsnChecksumVer10> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFActionBsnChecksumVer10 message, PrimitiveSink sink) {
            // fixed value property type = 65535
            sink.putShort((short) 0xffff);
            // fixed value property length = 28
            sink.putShort((short) 0x1c);
            // fixed value property experimenter = 0x5c16c7L
            sink.putInt(0x5c16c7);
            // fixed value property subtype = 0x4L
            sink.putInt(0x4);
            message.checksum.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFActionBsnChecksumVer10> {
        @Override
        public void write(ByteBuf bb, OFActionBsnChecksumVer10 message) {
            // fixed value property type = 65535
            bb.writeShort((short) 0xffff);
            // fixed value property length = 28
            bb.writeShort((short) 0x1c);
            // fixed value property experimenter = 0x5c16c7L
            bb.writeInt(0x5c16c7);
            // fixed value property subtype = 0x4L
            bb.writeInt(0x4);
            message.checksum.write16Bytes(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFActionBsnChecksumVer10(");
        b.append("checksum=").append(checksum);
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
        OFActionBsnChecksumVer10 other = (OFActionBsnChecksumVer10) obj;

        if (checksum == null) {
            if (other.checksum != null)
                return false;
        } else if (!checksum.equals(other.checksum))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((checksum == null) ? 0 : checksum.hashCode());
        return result;
    }

}
