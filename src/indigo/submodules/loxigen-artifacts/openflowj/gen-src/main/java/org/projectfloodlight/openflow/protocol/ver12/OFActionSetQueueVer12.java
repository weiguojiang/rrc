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
import java.util.Set;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFActionSetQueueVer12 implements OFActionSetQueue {
    private static final Logger logger = LoggerFactory.getLogger(OFActionSetQueueVer12.class);
    // version: 1.2
    final static byte WIRE_VERSION = 3;
    final static int LENGTH = 8;

        private final static long DEFAULT_QUEUE_ID = 0x0L;

    // OF message fields
    private final long queueId;
//
    // Immutable default instance
    final static OFActionSetQueueVer12 DEFAULT = new OFActionSetQueueVer12(
        DEFAULT_QUEUE_ID
    );

    // package private constructor - used by readers, builders, and factory
    OFActionSetQueueVer12(long queueId) {
        this.queueId = queueId;
    }

    // Accessors for OF message fields
    @Override
    public OFActionType getType() {
        return OFActionType.SET_QUEUE;
    }

    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



    public OFActionSetQueue.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFActionSetQueue.Builder {
        final OFActionSetQueueVer12 parentMessage;

        // OF message fields
        private boolean queueIdSet;
        private long queueId;

        BuilderWithParent(OFActionSetQueueVer12 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFActionType getType() {
        return OFActionType.SET_QUEUE;
    }

    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public OFActionSetQueue.Builder setQueueId(long queueId) {
        this.queueId = queueId;
        this.queueIdSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



        @Override
        public OFActionSetQueue build() {
                long queueId = this.queueIdSet ? this.queueId : parentMessage.queueId;

                //
                return new OFActionSetQueueVer12(
                    queueId
                );
        }

    }

    static class Builder implements OFActionSetQueue.Builder {
        // OF message fields
        private boolean queueIdSet;
        private long queueId;

    @Override
    public OFActionType getType() {
        return OFActionType.SET_QUEUE;
    }

    @Override
    public long getQueueId() {
        return queueId;
    }

    @Override
    public OFActionSetQueue.Builder setQueueId(long queueId) {
        this.queueId = queueId;
        this.queueIdSet = true;
        return this;
    }
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }

//
        @Override
        public OFActionSetQueue build() {
            long queueId = this.queueIdSet ? this.queueId : DEFAULT_QUEUE_ID;


            return new OFActionSetQueueVer12(
                    queueId
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFActionSetQueue> {
        @Override
        public OFActionSetQueue readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property type == 21
            short type = bb.readShort();
            if(type != (short) 0x15)
                throw new OFParseError("Wrong type: Expected=OFActionType.SET_QUEUE(21), got="+type);
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
            long queueId = U32.f(bb.readInt());

            OFActionSetQueueVer12 actionSetQueueVer12 = new OFActionSetQueueVer12(
                    queueId
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", actionSetQueueVer12);
            return actionSetQueueVer12;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFActionSetQueueVer12Funnel FUNNEL = new OFActionSetQueueVer12Funnel();
    static class OFActionSetQueueVer12Funnel implements Funnel<OFActionSetQueueVer12> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFActionSetQueueVer12 message, PrimitiveSink sink) {
            // fixed value property type = 21
            sink.putShort((short) 0x15);
            // fixed value property length = 8
            sink.putShort((short) 0x8);
            sink.putLong(message.queueId);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFActionSetQueueVer12> {
        @Override
        public void write(ByteBuf bb, OFActionSetQueueVer12 message) {
            // fixed value property type = 21
            bb.writeShort((short) 0x15);
            // fixed value property length = 8
            bb.writeShort((short) 0x8);
            bb.writeInt(U32.t(message.queueId));


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFActionSetQueueVer12(");
        b.append("queueId=").append(queueId);
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
        OFActionSetQueueVer12 other = (OFActionSetQueueVer12) obj;

        if( queueId != other.queueId)
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime *  (int) (queueId ^ (queueId >>> 32));
        return result;
    }

}
