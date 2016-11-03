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

class OFBsnPduTxRequestVer10 implements OFBsnPduTxRequest {
    private static final Logger logger = LoggerFactory.getLogger(OFBsnPduTxRequestVer10.class);
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int MINIMUM_LENGTH = 26;

        private final static long DEFAULT_XID = 0x0L;
        private final static long DEFAULT_TX_INTERVAL_MS = 0x0L;
        private final static OFPort DEFAULT_PORT_NO = OFPort.ANY;
        private final static short DEFAULT_SLOT_NUM = (short) 0x0;
        private final static byte[] DEFAULT_DATA = new byte[0];

    // OF message fields
    private final long xid;
    private final long txIntervalMs;
    private final OFPort portNo;
    private final short slotNum;
    private final byte[] data;
//
    // Immutable default instance
    final static OFBsnPduTxRequestVer10 DEFAULT = new OFBsnPduTxRequestVer10(
        DEFAULT_XID, DEFAULT_TX_INTERVAL_MS, DEFAULT_PORT_NO, DEFAULT_SLOT_NUM, DEFAULT_DATA
    );

    // package private constructor - used by readers, builders, and factory
    OFBsnPduTxRequestVer10(long xid, long txIntervalMs, OFPort portNo, short slotNum, byte[] data) {
        if(portNo == null) {
            throw new NullPointerException("OFBsnPduTxRequestVer10: property portNo cannot be null");
        }
        if(data == null) {
            throw new NullPointerException("OFBsnPduTxRequestVer10: property data cannot be null");
        }
        this.xid = xid;
        this.txIntervalMs = txIntervalMs;
        this.portNo = portNo;
        this.slotNum = slotNum;
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
        return 0x1fL;
    }

    @Override
    public long getTxIntervalMs() {
        return txIntervalMs;
    }

    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public short getSlotNum() {
        return slotNum;
    }

    @Override
    public byte[] getData() {
        return data;
    }



    public OFBsnPduTxRequest.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFBsnPduTxRequest.Builder {
        final OFBsnPduTxRequestVer10 parentMessage;

        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean txIntervalMsSet;
        private long txIntervalMs;
        private boolean portNoSet;
        private OFPort portNo;
        private boolean slotNumSet;
        private short slotNum;
        private boolean dataSet;
        private byte[] data;

        BuilderWithParent(OFBsnPduTxRequestVer10 parentMessage) {
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
    public OFBsnPduTxRequest.Builder setXid(long xid) {
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
        return 0x1fL;
    }

    @Override
    public long getTxIntervalMs() {
        return txIntervalMs;
    }

    @Override
    public OFBsnPduTxRequest.Builder setTxIntervalMs(long txIntervalMs) {
        this.txIntervalMs = txIntervalMs;
        this.txIntervalMsSet = true;
        return this;
    }
    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public OFBsnPduTxRequest.Builder setPortNo(OFPort portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public short getSlotNum() {
        return slotNum;
    }

    @Override
    public OFBsnPduTxRequest.Builder setSlotNum(short slotNum) {
        this.slotNum = slotNum;
        this.slotNumSet = true;
        return this;
    }
    @Override
    public byte[] getData() {
        return data;
    }

    @Override
    public OFBsnPduTxRequest.Builder setData(byte[] data) {
        this.data = data;
        this.dataSet = true;
        return this;
    }


        @Override
        public OFBsnPduTxRequest build() {
                long xid = this.xidSet ? this.xid : parentMessage.xid;
                long txIntervalMs = this.txIntervalMsSet ? this.txIntervalMs : parentMessage.txIntervalMs;
                OFPort portNo = this.portNoSet ? this.portNo : parentMessage.portNo;
                if(portNo == null)
                    throw new NullPointerException("Property portNo must not be null");
                short slotNum = this.slotNumSet ? this.slotNum : parentMessage.slotNum;
                byte[] data = this.dataSet ? this.data : parentMessage.data;
                if(data == null)
                    throw new NullPointerException("Property data must not be null");

                //
                return new OFBsnPduTxRequestVer10(
                    xid,
                    txIntervalMs,
                    portNo,
                    slotNum,
                    data
                );
        }

    }

    static class Builder implements OFBsnPduTxRequest.Builder {
        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean txIntervalMsSet;
        private long txIntervalMs;
        private boolean portNoSet;
        private OFPort portNo;
        private boolean slotNumSet;
        private short slotNum;
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
    public OFBsnPduTxRequest.Builder setXid(long xid) {
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
        return 0x1fL;
    }

    @Override
    public long getTxIntervalMs() {
        return txIntervalMs;
    }

    @Override
    public OFBsnPduTxRequest.Builder setTxIntervalMs(long txIntervalMs) {
        this.txIntervalMs = txIntervalMs;
        this.txIntervalMsSet = true;
        return this;
    }
    @Override
    public OFPort getPortNo() {
        return portNo;
    }

    @Override
    public OFBsnPduTxRequest.Builder setPortNo(OFPort portNo) {
        this.portNo = portNo;
        this.portNoSet = true;
        return this;
    }
    @Override
    public short getSlotNum() {
        return slotNum;
    }

    @Override
    public OFBsnPduTxRequest.Builder setSlotNum(short slotNum) {
        this.slotNum = slotNum;
        this.slotNumSet = true;
        return this;
    }
    @Override
    public byte[] getData() {
        return data;
    }

    @Override
    public OFBsnPduTxRequest.Builder setData(byte[] data) {
        this.data = data;
        this.dataSet = true;
        return this;
    }
//
        @Override
        public OFBsnPduTxRequest build() {
            long xid = this.xidSet ? this.xid : DEFAULT_XID;
            long txIntervalMs = this.txIntervalMsSet ? this.txIntervalMs : DEFAULT_TX_INTERVAL_MS;
            OFPort portNo = this.portNoSet ? this.portNo : DEFAULT_PORT_NO;
            if(portNo == null)
                throw new NullPointerException("Property portNo must not be null");
            short slotNum = this.slotNumSet ? this.slotNum : DEFAULT_SLOT_NUM;
            byte[] data = this.dataSet ? this.data : DEFAULT_DATA;
            if(data == null)
                throw new NullPointerException("Property data must not be null");


            return new OFBsnPduTxRequestVer10(
                    xid,
                    txIntervalMs,
                    portNo,
                    slotNum,
                    data
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFBsnPduTxRequest> {
        @Override
        public OFBsnPduTxRequest readFrom(ByteBuf bb) throws OFParseError {
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
            // fixed value property subtype == 0x1fL
            int subtype = bb.readInt();
            if(subtype != 0x1f)
                throw new OFParseError("Wrong subtype: Expected=0x1fL(0x1fL), got="+subtype);
            long txIntervalMs = U32.f(bb.readInt());
            OFPort portNo = OFPort.read2Bytes(bb);
            short slotNum = U8.f(bb.readByte());
            // pad: 3 bytes
            bb.skipBytes(3);
            byte[] data = ChannelUtils.readBytes(bb, length - (bb.readerIndex() - start));

            OFBsnPduTxRequestVer10 bsnPduTxRequestVer10 = new OFBsnPduTxRequestVer10(
                    xid,
                      txIntervalMs,
                      portNo,
                      slotNum,
                      data
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", bsnPduTxRequestVer10);
            return bsnPduTxRequestVer10;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFBsnPduTxRequestVer10Funnel FUNNEL = new OFBsnPduTxRequestVer10Funnel();
    static class OFBsnPduTxRequestVer10Funnel implements Funnel<OFBsnPduTxRequestVer10> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFBsnPduTxRequestVer10 message, PrimitiveSink sink) {
            // fixed value property version = 1
            sink.putByte((byte) 0x1);
            // fixed value property type = 4
            sink.putByte((byte) 0x4);
            // FIXME: skip funnel of length
            sink.putLong(message.xid);
            // fixed value property experimenter = 0x5c16c7L
            sink.putInt(0x5c16c7);
            // fixed value property subtype = 0x1fL
            sink.putInt(0x1f);
            sink.putLong(message.txIntervalMs);
            message.portNo.putTo(sink);
            sink.putShort(message.slotNum);
            // skip pad (3 bytes)
            sink.putBytes(message.data);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFBsnPduTxRequestVer10> {
        @Override
        public void write(ByteBuf bb, OFBsnPduTxRequestVer10 message) {
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
            // fixed value property subtype = 0x1fL
            bb.writeInt(0x1f);
            bb.writeInt(U32.t(message.txIntervalMs));
            message.portNo.write2Bytes(bb);
            bb.writeByte(U8.t(message.slotNum));
            // pad: 3 bytes
            bb.writeZero(3);
            bb.writeBytes(message.data);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFBsnPduTxRequestVer10(");
        b.append("xid=").append(xid);
        b.append(", ");
        b.append("txIntervalMs=").append(txIntervalMs);
        b.append(", ");
        b.append("portNo=").append(portNo);
        b.append(", ");
        b.append("slotNum=").append(slotNum);
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
        OFBsnPduTxRequestVer10 other = (OFBsnPduTxRequestVer10) obj;

        if( xid != other.xid)
            return false;
        if( txIntervalMs != other.txIntervalMs)
            return false;
        if (portNo == null) {
            if (other.portNo != null)
                return false;
        } else if (!portNo.equals(other.portNo))
            return false;
        if( slotNum != other.slotNum)
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
        result = prime *  (int) (txIntervalMs ^ (txIntervalMs >>> 32));
        result = prime * result + ((portNo == null) ? 0 : portNo.hashCode());
        result = prime * result + slotNum;
        result = prime * result + Arrays.hashCode(data);
        return result;
    }

}
