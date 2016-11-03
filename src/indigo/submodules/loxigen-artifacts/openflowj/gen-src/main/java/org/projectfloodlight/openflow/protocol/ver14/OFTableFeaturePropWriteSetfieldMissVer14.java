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
import java.util.Set;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.List;
import com.google.common.collect.ImmutableList;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFTableFeaturePropWriteSetfieldMissVer14 implements OFTableFeaturePropWriteSetfieldMiss {
    private static final Logger logger = LoggerFactory.getLogger(OFTableFeaturePropWriteSetfieldMissVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 4;

        private final static List<U32> DEFAULT_OXM_IDS = ImmutableList.<U32>of();

    // OF message fields
    private final List<U32> oxmIds;
//
    // Immutable default instance
    final static OFTableFeaturePropWriteSetfieldMissVer14 DEFAULT = new OFTableFeaturePropWriteSetfieldMissVer14(
        DEFAULT_OXM_IDS
    );

    // package private constructor - used by readers, builders, and factory
    OFTableFeaturePropWriteSetfieldMissVer14(List<U32> oxmIds) {
        if(oxmIds == null) {
            throw new NullPointerException("OFTableFeaturePropWriteSetfieldMissVer14: property oxmIds cannot be null");
        }
        this.oxmIds = oxmIds;
    }

    // Accessors for OF message fields
    @Override
    public int getType() {
        return 0xd;
    }

    @Override
    public List<U32> getOxmIds() {
        return oxmIds;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFTableFeaturePropWriteSetfieldMiss.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFTableFeaturePropWriteSetfieldMiss.Builder {
        final OFTableFeaturePropWriteSetfieldMissVer14 parentMessage;

        // OF message fields
        private boolean oxmIdsSet;
        private List<U32> oxmIds;

        BuilderWithParent(OFTableFeaturePropWriteSetfieldMissVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public int getType() {
        return 0xd;
    }

    @Override
    public List<U32> getOxmIds() {
        return oxmIds;
    }

    @Override
    public OFTableFeaturePropWriteSetfieldMiss.Builder setOxmIds(List<U32> oxmIds) {
        this.oxmIds = oxmIds;
        this.oxmIdsSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFTableFeaturePropWriteSetfieldMiss build() {
                List<U32> oxmIds = this.oxmIdsSet ? this.oxmIds : parentMessage.oxmIds;
                if(oxmIds == null)
                    throw new NullPointerException("Property oxmIds must not be null");

                //
                return new OFTableFeaturePropWriteSetfieldMissVer14(
                    oxmIds
                );
        }

    }

    static class Builder implements OFTableFeaturePropWriteSetfieldMiss.Builder {
        // OF message fields
        private boolean oxmIdsSet;
        private List<U32> oxmIds;

    @Override
    public int getType() {
        return 0xd;
    }

    @Override
    public List<U32> getOxmIds() {
        return oxmIds;
    }

    @Override
    public OFTableFeaturePropWriteSetfieldMiss.Builder setOxmIds(List<U32> oxmIds) {
        this.oxmIds = oxmIds;
        this.oxmIdsSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFTableFeaturePropWriteSetfieldMiss build() {
            List<U32> oxmIds = this.oxmIdsSet ? this.oxmIds : DEFAULT_OXM_IDS;
            if(oxmIds == null)
                throw new NullPointerException("Property oxmIds must not be null");


            return new OFTableFeaturePropWriteSetfieldMissVer14(
                    oxmIds
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFTableFeaturePropWriteSetfieldMiss> {
        @Override
        public OFTableFeaturePropWriteSetfieldMiss readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 0xd
            short type = bb.readShort();
            if(type != (short) 0xd)
                throw new OFParseError("Wrong type: Expected=0xd(0xd), got="+type);
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
            List<U32> oxmIds = ChannelUtils.readList(bb, length - (bb.readerIndex() - start), U32.READER);

            OFTableFeaturePropWriteSetfieldMissVer14 tableFeaturePropWriteSetfieldMissVer14 = new OFTableFeaturePropWriteSetfieldMissVer14(
                    oxmIds
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", tableFeaturePropWriteSetfieldMissVer14);
            return tableFeaturePropWriteSetfieldMissVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFTableFeaturePropWriteSetfieldMissVer14Funnel FUNNEL = new OFTableFeaturePropWriteSetfieldMissVer14Funnel();
    static class OFTableFeaturePropWriteSetfieldMissVer14Funnel implements Funnel<OFTableFeaturePropWriteSetfieldMissVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFTableFeaturePropWriteSetfieldMissVer14 message, PrimitiveSink sink) {
            // fixed value property type = 0xd
            sink.putShort((short) 0xd);
            // FIXME: skip funnel of length
            FunnelUtils.putList(message.oxmIds, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFTableFeaturePropWriteSetfieldMissVer14> {
        @Override
        public void write(ByteBuf bb, OFTableFeaturePropWriteSetfieldMissVer14 message) {
            int startIndex = bb.writerIndex();
            // fixed value property type = 0xd
            bb.writeShort((short) 0xd);
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            ChannelUtils.writeList(bb, message.oxmIds);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFTableFeaturePropWriteSetfieldMissVer14(");
        b.append("oxmIds=").append(oxmIds);
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
        OFTableFeaturePropWriteSetfieldMissVer14 other = (OFTableFeaturePropWriteSetfieldMissVer14) obj;

        if (oxmIds == null) {
            if (other.oxmIds != null)
                return false;
        } else if (!oxmIds.equals(other.oxmIds))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((oxmIds == null) ? 0 : oxmIds.hashCode());
        return result;
    }

}
