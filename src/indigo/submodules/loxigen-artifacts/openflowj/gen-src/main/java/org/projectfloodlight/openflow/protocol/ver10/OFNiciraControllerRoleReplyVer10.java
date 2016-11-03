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

class OFNiciraControllerRoleReplyVer10 implements OFNiciraControllerRoleReply {
    private static final Logger logger = LoggerFactory.getLogger(OFNiciraControllerRoleReplyVer10.class);
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int LENGTH = 20;

        private final static long DEFAULT_XID = 0x0L;

    // OF message fields
    private final long xid;
    private final OFNiciraControllerRole role;
//

    // package private constructor - used by readers, builders, and factory
    OFNiciraControllerRoleReplyVer10(long xid, OFNiciraControllerRole role) {
        if(role == null) {
            throw new NullPointerException("OFNiciraControllerRoleReplyVer10: property role cannot be null");
        }
        this.xid = xid;
        this.role = role;
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
        return 0x2320L;
    }

    @Override
    public long getSubtype() {
        return 0xbL;
    }

    @Override
    public OFNiciraControllerRole getRole() {
        return role;
    }



    public OFNiciraControllerRoleReply.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFNiciraControllerRoleReply.Builder {
        final OFNiciraControllerRoleReplyVer10 parentMessage;

        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean roleSet;
        private OFNiciraControllerRole role;

        BuilderWithParent(OFNiciraControllerRoleReplyVer10 parentMessage) {
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
    public OFNiciraControllerRoleReply.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getExperimenter() {
        return 0x2320L;
    }

    @Override
    public long getSubtype() {
        return 0xbL;
    }

    @Override
    public OFNiciraControllerRole getRole() {
        return role;
    }

    @Override
    public OFNiciraControllerRoleReply.Builder setRole(OFNiciraControllerRole role) {
        this.role = role;
        this.roleSet = true;
        return this;
    }


        @Override
        public OFNiciraControllerRoleReply build() {
                long xid = this.xidSet ? this.xid : parentMessage.xid;
                OFNiciraControllerRole role = this.roleSet ? this.role : parentMessage.role;
                if(role == null)
                    throw new NullPointerException("Property role must not be null");

                //
                return new OFNiciraControllerRoleReplyVer10(
                    xid,
                    role
                );
        }

    }

    static class Builder implements OFNiciraControllerRoleReply.Builder {
        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean roleSet;
        private OFNiciraControllerRole role;

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
    public OFNiciraControllerRoleReply.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getExperimenter() {
        return 0x2320L;
    }

    @Override
    public long getSubtype() {
        return 0xbL;
    }

    @Override
    public OFNiciraControllerRole getRole() {
        return role;
    }

    @Override
    public OFNiciraControllerRoleReply.Builder setRole(OFNiciraControllerRole role) {
        this.role = role;
        this.roleSet = true;
        return this;
    }
//
        @Override
        public OFNiciraControllerRoleReply build() {
            long xid = this.xidSet ? this.xid : DEFAULT_XID;
            if(!this.roleSet)
                throw new IllegalStateException("Property role doesn't have default value -- must be set");
            if(role == null)
                throw new NullPointerException("Property role must not be null");


            return new OFNiciraControllerRoleReplyVer10(
                    xid,
                    role
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFNiciraControllerRoleReply> {
        @Override
        public OFNiciraControllerRoleReply readFrom(ByteBuf bb) throws OFParseError {
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
            if(length != 20)
                throw new OFParseError("Wrong length: Expected=20(20), got="+length);
            if(bb.readableBytes() + (bb.readerIndex() - start) < length) {
                // Buffer does not have all data yet
                bb.readerIndex(start);
                return null;
            }
            if(logger.isTraceEnabled())
                logger.trace("readFrom - length={}", length);
            long xid = U32.f(bb.readInt());
            // fixed value property experimenter == 0x2320L
            int experimenter = bb.readInt();
            if(experimenter != 0x2320)
                throw new OFParseError("Wrong experimenter: Expected=0x2320L(0x2320L), got="+experimenter);
            // fixed value property subtype == 0xbL
            int subtype = bb.readInt();
            if(subtype != 0xb)
                throw new OFParseError("Wrong subtype: Expected=0xbL(0xbL), got="+subtype);
            OFNiciraControllerRole role = OFNiciraControllerRoleSerializerVer10.readFrom(bb);

            OFNiciraControllerRoleReplyVer10 niciraControllerRoleReplyVer10 = new OFNiciraControllerRoleReplyVer10(
                    xid,
                      role
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", niciraControllerRoleReplyVer10);
            return niciraControllerRoleReplyVer10;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFNiciraControllerRoleReplyVer10Funnel FUNNEL = new OFNiciraControllerRoleReplyVer10Funnel();
    static class OFNiciraControllerRoleReplyVer10Funnel implements Funnel<OFNiciraControllerRoleReplyVer10> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFNiciraControllerRoleReplyVer10 message, PrimitiveSink sink) {
            // fixed value property version = 1
            sink.putByte((byte) 0x1);
            // fixed value property type = 4
            sink.putByte((byte) 0x4);
            // fixed value property length = 20
            sink.putShort((short) 0x14);
            sink.putLong(message.xid);
            // fixed value property experimenter = 0x2320L
            sink.putInt(0x2320);
            // fixed value property subtype = 0xbL
            sink.putInt(0xb);
            OFNiciraControllerRoleSerializerVer10.putTo(message.role, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFNiciraControllerRoleReplyVer10> {
        @Override
        public void write(ByteBuf bb, OFNiciraControllerRoleReplyVer10 message) {
            // fixed value property version = 1
            bb.writeByte((byte) 0x1);
            // fixed value property type = 4
            bb.writeByte((byte) 0x4);
            // fixed value property length = 20
            bb.writeShort((short) 0x14);
            bb.writeInt(U32.t(message.xid));
            // fixed value property experimenter = 0x2320L
            bb.writeInt(0x2320);
            // fixed value property subtype = 0xbL
            bb.writeInt(0xb);
            OFNiciraControllerRoleSerializerVer10.writeTo(bb, message.role);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFNiciraControllerRoleReplyVer10(");
        b.append("xid=").append(xid);
        b.append(", ");
        b.append("role=").append(role);
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
        OFNiciraControllerRoleReplyVer10 other = (OFNiciraControllerRoleReplyVer10) obj;

        if( xid != other.xid)
            return false;
        if (role == null) {
            if (other.role != null)
                return false;
        } else if (!role.equals(other.role))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime *  (int) (xid ^ (xid >>> 32));
        result = prime * result + ((role == null) ? 0 : role.hashCode());
        return result;
    }

}
