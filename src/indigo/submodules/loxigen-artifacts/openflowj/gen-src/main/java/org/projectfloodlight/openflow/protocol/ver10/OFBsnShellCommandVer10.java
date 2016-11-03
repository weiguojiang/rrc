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
import java.util.Arrays;

class OFBsnShellCommandVer10 implements OFBsnShellCommand {
    private static final Logger logger = LoggerFactory.getLogger(OFBsnShellCommandVer10.class);
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int MINIMUM_LENGTH = 20;

        private final static long DEFAULT_XID = 0x0L;
        private final static long DEFAULT_SERVICE = 0x0L;
        private final static byte[] DEFAULT_DATA = new byte[0];

    // OF message fields
    private final long xid;
    private final long service;
    private final byte[] data;
//
    // Immutable default instance
    final static OFBsnShellCommandVer10 DEFAULT = new OFBsnShellCommandVer10(
        DEFAULT_XID, DEFAULT_SERVICE, DEFAULT_DATA
    );

    // package private constructor - used by readers, builders, and factory
    OFBsnShellCommandVer10(long xid, long service, byte[] data) {
        if(data == null) {
            throw new NullPointerException("OFBsnShellCommandVer10: property data cannot be null");
        }
        this.xid = xid;
        this.service = service;
        this.data = data;
    }

    // Accessors for OF message fields
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }

    @Override
    public OFType getType() {
        return OFType.EXPERIMENTER;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x6L;
    }

    @Override
    public long getService() {
        return service;
    }

    @Override
    public byte[] getData() {
        return data;
    }



    public OFBsnShellCommand.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFBsnShellCommand.Builder {
        final OFBsnShellCommandVer10 parentMessage;

        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean serviceSet;
        private long service;
        private boolean dataSet;
        private byte[] data;

        BuilderWithParent(OFBsnShellCommandVer10 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }

    @Override
    public OFType getType() {
        return OFType.EXPERIMENTER;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFBsnShellCommand.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x6L;
    }

    @Override
    public long getService() {
        return service;
    }

    @Override
    public OFBsnShellCommand.Builder setService(long service) {
        this.service = service;
        this.serviceSet = true;
        return this;
    }
    @Override
    public byte[] getData() {
        return data;
    }

    @Override
    public OFBsnShellCommand.Builder setData(byte[] data) {
        this.data = data;
        this.dataSet = true;
        return this;
    }


        @Override
        public OFBsnShellCommand build() {
                long xid = this.xidSet ? this.xid : parentMessage.xid;
                long service = this.serviceSet ? this.service : parentMessage.service;
                byte[] data = this.dataSet ? this.data : parentMessage.data;
                if(data == null)
                    throw new NullPointerException("Property data must not be null");

                //
                return new OFBsnShellCommandVer10(
                    xid,
                    service,
                    data
                );
        }

    }

    static class Builder implements OFBsnShellCommand.Builder {
        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean serviceSet;
        private long service;
        private boolean dataSet;
        private byte[] data;

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_10;
    }

    @Override
    public OFType getType() {
        return OFType.EXPERIMENTER;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFBsnShellCommand.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getExperimenter() {
        return 0x5c16c7L;
    }

    @Override
    public long getSubtype() {
        return 0x6L;
    }

    @Override
    public long getService() {
        return service;
    }

    @Override
    public OFBsnShellCommand.Builder setService(long service) {
        this.service = service;
        this.serviceSet = true;
        return this;
    }
    @Override
    public byte[] getData() {
        return data;
    }

    @Override
    public OFBsnShellCommand.Builder setData(byte[] data) {
        this.data = data;
        this.dataSet = true;
        return this;
    }
//
        @Override
        public OFBsnShellCommand build() {
            long xid = this.xidSet ? this.xid : DEFAULT_XID;
            long service = this.serviceSet ? this.service : DEFAULT_SERVICE;
            byte[] data = this.dataSet ? this.data : DEFAULT_DATA;
            if(data == null)
                throw new NullPointerException("Property data must not be null");


            return new OFBsnShellCommandVer10(
                    xid,
                    service,
                    data
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFBsnShellCommand> {
        @Override
        public OFBsnShellCommand readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property version == 1
            byte version = bb.readByte();
            if(version != (byte) 0x1)
                throw new OFParseError("Wrong version: Expected=OFVersion.OF_10(1), got="+version);
            // fixed value property type == 4
            byte type = bb.readByte();
            if(type != (byte) 0x4)
                throw new OFParseError("Wrong type: Expected=OFType.EXPERIMENTER(4), got="+type);
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
            long xid = U32.f(bb.readInt());
            // fixed value property experimenter == 0x5c16c7L
            int experimenter = bb.readInt();
            if(experimenter != 0x5c16c7)
                throw new OFParseError("Wrong experimenter: Expected=0x5c16c7L(0x5c16c7L), got="+experimenter);
            // fixed value property subtype == 0x6L
            int subtype = bb.readInt();
            if(subtype != 0x6)
                throw new OFParseError("Wrong subtype: Expected=0x6L(0x6L), got="+subtype);
            long service = U32.f(bb.readInt());
            byte[] data = ChannelUtils.readBytes(bb, length - (bb.readerIndex() - start));

            OFBsnShellCommandVer10 bsnShellCommandVer10 = new OFBsnShellCommandVer10(
                    xid,
                      service,
                      data
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", bsnShellCommandVer10);
            return bsnShellCommandVer10;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFBsnShellCommandVer10Funnel FUNNEL = new OFBsnShellCommandVer10Funnel();
    static class OFBsnShellCommandVer10Funnel implements Funnel<OFBsnShellCommandVer10> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFBsnShellCommandVer10 message, PrimitiveSink sink) {
            // fixed value property version = 1
            sink.putByte((byte) 0x1);
            // fixed value property type = 4
            sink.putByte((byte) 0x4);
            // FIXME: skip funnel of length
            sink.putLong(message.xid);
            // fixed value property experimenter = 0x5c16c7L
            sink.putInt(0x5c16c7);
            // fixed value property subtype = 0x6L
            sink.putInt(0x6);
            sink.putLong(message.service);
            sink.putBytes(message.data);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFBsnShellCommandVer10> {
        @Override
        public void write(ByteBuf bb, OFBsnShellCommandVer10 message) {
            int startIndex = bb.writerIndex();
            // fixed value property version = 1
            bb.writeByte((byte) 0x1);
            // fixed value property type = 4
            bb.writeByte((byte) 0x4);
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            bb.writeInt(U32.t(message.xid));
            // fixed value property experimenter = 0x5c16c7L
            bb.writeInt(0x5c16c7);
            // fixed value property subtype = 0x6L
            bb.writeInt(0x6);
            bb.writeInt(U32.t(message.service));
            bb.writeBytes(message.data);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFBsnShellCommandVer10(");
        b.append("xid=").append(xid);
        b.append(", ");
        b.append("service=").append(service);
        b.append(", ");
        b.append("data=").append(Arrays.toString(data));
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
        OFBsnShellCommandVer10 other = (OFBsnShellCommandVer10) obj;

        if( xid != other.xid)
            return false;
        if( service != other.service)
            return false;
        if (!Arrays.equals(data, other.data))
                return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime *  (int) (xid ^ (xid >>> 32));
        result = prime *  (int) (service ^ (service >>> 32));
        result = prime * result + Arrays.hashCode(data);
        return result;
    }

}
