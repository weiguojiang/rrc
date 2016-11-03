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

class OFHelloVer14 implements OFHello {
    private static final Logger logger = LoggerFactory.getLogger(OFHelloVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 8;

        private final static long DEFAULT_XID = 0x0L;
        private final static List<OFHelloElem> DEFAULT_ELEMENTS = ImmutableList.<OFHelloElem>of();

    // OF message fields
    private final long xid;
    private final List<OFHelloElem> elements;
//
    // Immutable default instance
    final static OFHelloVer14 DEFAULT = new OFHelloVer14(
        DEFAULT_XID, DEFAULT_ELEMENTS
    );

    // package private constructor - used by readers, builders, and factory
    OFHelloVer14(long xid, List<OFHelloElem> elements) {
        if(elements == null) {
            throw new NullPointerException("OFHelloVer14: property elements cannot be null");
        }
        this.xid = xid;
        this.elements = elements;
    }

    // Accessors for OF message fields
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.HELLO;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public List<OFHelloElem> getElements() {
        return elements;
    }



    public OFHello.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFHello.Builder {
        final OFHelloVer14 parentMessage;

        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean elementsSet;
        private List<OFHelloElem> elements;

        BuilderWithParent(OFHelloVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.HELLO;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFHello.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public List<OFHelloElem> getElements() {
        return elements;
    }

    @Override
    public OFHello.Builder setElements(List<OFHelloElem> elements) {
        this.elements = elements;
        this.elementsSet = true;
        return this;
    }


        @Override
        public OFHello build() {
                long xid = this.xidSet ? this.xid : parentMessage.xid;
                List<OFHelloElem> elements = this.elementsSet ? this.elements : parentMessage.elements;
                if(elements == null)
                    throw new NullPointerException("Property elements must not be null");

                //
                return new OFHelloVer14(
                    xid,
                    elements
                );
        }

    }

    static class Builder implements OFHello.Builder {
        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean elementsSet;
        private List<OFHelloElem> elements;

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.HELLO;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFHello.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public List<OFHelloElem> getElements() {
        return elements;
    }

    @Override
    public OFHello.Builder setElements(List<OFHelloElem> elements) {
        this.elements = elements;
        this.elementsSet = true;
        return this;
    }
//
        @Override
        public OFHello build() {
            long xid = this.xidSet ? this.xid : DEFAULT_XID;
            List<OFHelloElem> elements = this.elementsSet ? this.elements : DEFAULT_ELEMENTS;
            if(elements == null)
                throw new NullPointerException("Property elements must not be null");


            return new OFHelloVer14(
                    xid,
                    elements
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFHello> {
        @Override
        public OFHello readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property version == 5
            byte version = bb.readByte();
            if(version != (byte) 0x5)
                throw new OFParseError("Wrong version: Expected=OFVersion.OF_14(5), got="+version);
            // fixed value property type == 0
            byte type = bb.readByte();
            if(type != (byte) 0x0)
                throw new OFParseError("Wrong type: Expected=OFType.HELLO(0), got="+type);
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
            List<OFHelloElem> elements = ChannelUtils.readList(bb, length - (bb.readerIndex() - start), OFHelloElemVer14.READER);

            OFHelloVer14 helloVer14 = new OFHelloVer14(
                    xid,
                      elements
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", helloVer14);
            return helloVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFHelloVer14Funnel FUNNEL = new OFHelloVer14Funnel();
    static class OFHelloVer14Funnel implements Funnel<OFHelloVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFHelloVer14 message, PrimitiveSink sink) {
            // fixed value property version = 5
            sink.putByte((byte) 0x5);
            // fixed value property type = 0
            sink.putByte((byte) 0x0);
            // FIXME: skip funnel of length
            sink.putLong(message.xid);
            FunnelUtils.putList(message.elements, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFHelloVer14> {
        @Override
        public void write(ByteBuf bb, OFHelloVer14 message) {
            int startIndex = bb.writerIndex();
            // fixed value property version = 5
            bb.writeByte((byte) 0x5);
            // fixed value property type = 0
            bb.writeByte((byte) 0x0);
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            bb.writeInt(U32.t(message.xid));
            ChannelUtils.writeList(bb, message.elements);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFHelloVer14(");
        b.append("xid=").append(xid);
        b.append(", ");
        b.append("elements=").append(elements);
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
        OFHelloVer14 other = (OFHelloVer14) obj;

        if( xid != other.xid)
            return false;
        if (elements == null) {
            if (other.elements != null)
                return false;
        } else if (!elements.equals(other.elements))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime *  (int) (xid ^ (xid >>> 32));
        result = prime * result + ((elements == null) ? 0 : elements.hashCode());
        return result;
    }

}
