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

class OFQueueDescVer14 implements OFQueueDesc {
    private static final Logger logger = LoggerFactory.getLogger(OFQueueDescVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 16;

        private final static long DEFAULT_PORT_NO = 0x0L;
        private final static long DEFAULT_QUEUE_ID = 0x0L;
        private final static List<OFQueueDescProp> DEFAULT_PROPERTIES = ImmutableList.<OFQueueDescProp>of();

    // OF message fields
    private final long portNo;
    private final long queueId;
    private final List<OFQueueDescProp> properties;
//
    // Immutable default instance
    final static OFQueueDescVer14 DEFAULT = new OFQueueDescVer14(
        DEFAULT_PORT_NO, DEFAULT_QUEUE_ID, DEFAULT_PROPERTIES
    );

    // package private constructor - used by readers, builders, and factory
    OFQueueDescVer14(long portNo, long queueId, List<OFQueueDescProp> properties) {
        if(properties == null) {
            throw new NullPointerException("OFQueueDescVer14: property properties cannot be null");
        }
        this.portNo = portNo;
        this.queueId = queueId;
        this.properties = properties;
    }

    // Accessors for OF message fields
    @Override
    public long getPortNo() {
        return portNo;
    }

    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public List<OFQueueDescProp> getProperties() {
        return properties;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFQueueDesc.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFQueueDesc.Builder {
        final OFQueueDescVer14 parentMessage;

        // OF message fields
        private boolean portNoSet;
        private long portNo;
        private boolean queueIdSet;
        private long queueId;
        private boolean propertiesSet;
        private List<OFQueueDescProp> properties;

        BuilderWithParent(OFQueueDescVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getPortNo() {
        return portNo;
    }

    @Override
    public OFQueueDesc.Builder setPortNo(long portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public OFQueueDesc.Builder setQueueId(long queueId) {
        this.queueId = queueId;
        this.queueIdSet = true;
        return this;
    }
    @Override
    public List<OFQueueDescProp> getProperties() {
        return properties;
    }

    @Override
    public OFQueueDesc.Builder setProperties(List<OFQueueDescProp> properties) {
        this.properties = properties;
        this.propertiesSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFQueueDesc build() {
                long portNo = this.portNoSet ? this.portNo : parentMessage.portNo;
                long queueId = this.queueIdSet ? this.queueId : parentMessage.queueId;
                List<OFQueueDescProp> properties = this.propertiesSet ? this.properties : parentMessage.properties;
                if(properties == null)
                    throw new NullPointerException("Property properties must not be null");

                //
                return new OFQueueDescVer14(
                    portNo,
                    queueId,
                    properties
                );
        }

    }

    static class Builder implements OFQueueDesc.Builder {
        // OF message fields
        private boolean portNoSet;
        private long portNo;
        private boolean queueIdSet;
        private long queueId;
        private boolean propertiesSet;
        private List<OFQueueDescProp> properties;

    @Override
    public long getPortNo() {
        return portNo;
    }

    @Override
    public OFQueueDesc.Builder setPortNo(long portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public OFQueueDesc.Builder setQueueId(long queueId) {
        this.queueId = queueId;
        this.queueIdSet = true;
        return this;
    }
    @Override
    public List<OFQueueDescProp> getProperties() {
        return properties;
    }

    @Override
    public OFQueueDesc.Builder setProperties(List<OFQueueDescProp> properties) {
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
        public OFQueueDesc build() {
            long portNo = this.portNoSet ? this.portNo : DEFAULT_PORT_NO;
            long queueId = this.queueIdSet ? this.queueId : DEFAULT_QUEUE_ID;
            List<OFQueueDescProp> properties = this.propertiesSet ? this.properties : DEFAULT_PROPERTIES;
            if(properties == null)
                throw new NullPointerException("Property properties must not be null");


            return new OFQueueDescVer14(
                    portNo,
                    queueId,
                    properties
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFQueueDesc> {
        @Override
        public OFQueueDesc readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            long portNo = U32.f(bb.readInt());
            long queueId = U32.f(bb.readInt());
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
            // pad: 6 bytes
            bb.skipBytes(6);
            List<OFQueueDescProp> properties = ChannelUtils.readList(bb, length - (bb.readerIndex() - start), OFQueueDescPropVer14.READER);

            OFQueueDescVer14 queueDescVer14 = new OFQueueDescVer14(
                    portNo,
                      queueId,
                      properties
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", queueDescVer14);
            return queueDescVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFQueueDescVer14Funnel FUNNEL = new OFQueueDescVer14Funnel();
    static class OFQueueDescVer14Funnel implements Funnel<OFQueueDescVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFQueueDescVer14 message, PrimitiveSink sink) {
            sink.putLong(message.portNo);
            sink.putLong(message.queueId);
            // FIXME: skip funnel of length
            // skip pad (6 bytes)
            FunnelUtils.putList(message.properties, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFQueueDescVer14> {
        @Override
        public void write(ByteBuf bb, OFQueueDescVer14 message) {
            int startIndex = bb.writerIndex();
            bb.writeInt(U32.t(message.portNo));
            bb.writeInt(U32.t(message.queueId));
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            // pad: 6 bytes
            bb.writeZero(6);
            ChannelUtils.writeList(bb, message.properties);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFQueueDescVer14(");
        b.append("portNo=").append(portNo);
        b.append(", ");
        b.append("queueId=").append(queueId);
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
        OFQueueDescVer14 other = (OFQueueDescVer14) obj;

        if( portNo != other.portNo)
            return false;
        if( queueId != other.queueId)
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

        result = prime *  (int) (portNo ^ (portNo >>> 32));
        result = prime *  (int) (queueId ^ (queueId >>> 32));
        result = prime * result + ((properties == null) ? 0 : properties.hashCode());
        return result;
    }

}
