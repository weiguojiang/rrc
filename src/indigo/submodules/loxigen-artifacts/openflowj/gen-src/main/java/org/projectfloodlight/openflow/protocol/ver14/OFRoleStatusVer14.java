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

class OFRoleStatusVer14 implements OFRoleStatus {
    private static final Logger logger = LoggerFactory.getLogger(OFRoleStatusVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 24;

        private final static long DEFAULT_XID = 0x0L;
        private final static long DEFAULT_ROLE = 0x0L;
        private final static U64 DEFAULT_GENERATION_ID = U64.ZERO;
        private final static List<OFRoleProp> DEFAULT_PROPERTIES = ImmutableList.<OFRoleProp>of();

    // OF message fields
    private final long xid;
    private final long role;
    private final OFControllerRoleReason reason;
    private final U64 generationId;
    private final List<OFRoleProp> properties;
//

    // package private constructor - used by readers, builders, and factory
    OFRoleStatusVer14(long xid, long role, OFControllerRoleReason reason, U64 generationId, List<OFRoleProp> properties) {
        if(reason == null) {
            throw new NullPointerException("OFRoleStatusVer14: property reason cannot be null");
        }
        if(generationId == null) {
            throw new NullPointerException("OFRoleStatusVer14: property generationId cannot be null");
        }
        if(properties == null) {
            throw new NullPointerException("OFRoleStatusVer14: property properties cannot be null");
        }
        this.xid = xid;
        this.role = role;
        this.reason = reason;
        this.generationId = generationId;
        this.properties = properties;
    }

    // Accessors for OF message fields
    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.ROLE_STATUS;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public long getRole() {
        return role;
    }

    @Override
    public OFControllerRoleReason getReason() {
        return reason;
    }

    @Override
    public U64 getGenerationId() {
        return generationId;
    }

    @Override
    public List<OFRoleProp> getProperties() {
        return properties;
    }



    public OFRoleStatus.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFRoleStatus.Builder {
        final OFRoleStatusVer14 parentMessage;

        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean roleSet;
        private long role;
        private boolean reasonSet;
        private OFControllerRoleReason reason;
        private boolean generationIdSet;
        private U64 generationId;
        private boolean propertiesSet;
        private List<OFRoleProp> properties;

        BuilderWithParent(OFRoleStatusVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.ROLE_STATUS;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFRoleStatus.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getRole() {
        return role;
    }

    @Override
    public OFRoleStatus.Builder setRole(long role) {
        this.role = role;
        this.roleSet = true;
        return this;
    }
    @Override
    public OFControllerRoleReason getReason() {
        return reason;
    }

    @Override
    public OFRoleStatus.Builder setReason(OFControllerRoleReason reason) {
        this.reason = reason;
        this.reasonSet = true;
        return this;
    }
    @Override
    public U64 getGenerationId() {
        return generationId;
    }

    @Override
    public OFRoleStatus.Builder setGenerationId(U64 generationId) {
        this.generationId = generationId;
        this.generationIdSet = true;
        return this;
    }
    @Override
    public List<OFRoleProp> getProperties() {
        return properties;
    }

    @Override
    public OFRoleStatus.Builder setProperties(List<OFRoleProp> properties) {
        this.properties = properties;
        this.propertiesSet = true;
        return this;
    }


        @Override
        public OFRoleStatus build() {
                long xid = this.xidSet ? this.xid : parentMessage.xid;
                long role = this.roleSet ? this.role : parentMessage.role;
                OFControllerRoleReason reason = this.reasonSet ? this.reason : parentMessage.reason;
                if(reason == null)
                    throw new NullPointerException("Property reason must not be null");
                U64 generationId = this.generationIdSet ? this.generationId : parentMessage.generationId;
                if(generationId == null)
                    throw new NullPointerException("Property generationId must not be null");
                List<OFRoleProp> properties = this.propertiesSet ? this.properties : parentMessage.properties;
                if(properties == null)
                    throw new NullPointerException("Property properties must not be null");

                //
                return new OFRoleStatusVer14(
                    xid,
                    role,
                    reason,
                    generationId,
                    properties
                );
        }

    }

    static class Builder implements OFRoleStatus.Builder {
        // OF message fields
        private boolean xidSet;
        private long xid;
        private boolean roleSet;
        private long role;
        private boolean reasonSet;
        private OFControllerRoleReason reason;
        private boolean generationIdSet;
        private U64 generationId;
        private boolean propertiesSet;
        private List<OFRoleProp> properties;

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

    @Override
    public OFType getType() {
        return OFType.ROLE_STATUS;
    }

    @Override
    public long getXid() {
        return xid;
    }

    @Override
    public OFRoleStatus.Builder setXid(long xid) {
        this.xid = xid;
        this.xidSet = true;
        return this;
    }
    @Override
    public long getRole() {
        return role;
    }

    @Override
    public OFRoleStatus.Builder setRole(long role) {
        this.role = role;
        this.roleSet = true;
        return this;
    }
    @Override
    public OFControllerRoleReason getReason() {
        return reason;
    }

    @Override
    public OFRoleStatus.Builder setReason(OFControllerRoleReason reason) {
        this.reason = reason;
        this.reasonSet = true;
        return this;
    }
    @Override
    public U64 getGenerationId() {
        return generationId;
    }

    @Override
    public OFRoleStatus.Builder setGenerationId(U64 generationId) {
        this.generationId = generationId;
        this.generationIdSet = true;
        return this;
    }
    @Override
    public List<OFRoleProp> getProperties() {
        return properties;
    }

    @Override
    public OFRoleStatus.Builder setProperties(List<OFRoleProp> properties) {
        this.properties = properties;
        this.propertiesSet = true;
        return this;
    }
//
        @Override
        public OFRoleStatus build() {
            long xid = this.xidSet ? this.xid : DEFAULT_XID;
            long role = this.roleSet ? this.role : DEFAULT_ROLE;
            if(!this.reasonSet)
                throw new IllegalStateException("Property reason doesn't have default value -- must be set");
            if(reason == null)
                throw new NullPointerException("Property reason must not be null");
            U64 generationId = this.generationIdSet ? this.generationId : DEFAULT_GENERATION_ID;
            if(generationId == null)
                throw new NullPointerException("Property generationId must not be null");
            List<OFRoleProp> properties = this.propertiesSet ? this.properties : DEFAULT_PROPERTIES;
            if(properties == null)
                throw new NullPointerException("Property properties must not be null");


            return new OFRoleStatusVer14(
                    xid,
                    role,
                    reason,
                    generationId,
                    properties
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFRoleStatus> {
        @Override
        public OFRoleStatus readFrom(ByteBuf bb) throws OFParseError {
            int start = bb.readerIndex();
            // fixed value property version == 5
            byte version = bb.readByte();
            if(version != (byte) 0x5)
                throw new OFParseError("Wrong version: Expected=OFVersion.OF_14(5), got="+version);
            // fixed value property type == 30
            byte type = bb.readByte();
            if(type != (byte) 0x1e)
                throw new OFParseError("Wrong type: Expected=OFType.ROLE_STATUS(30), got="+type);
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
            long role = U32.f(bb.readInt());
            OFControllerRoleReason reason = OFControllerRoleReasonSerializerVer14.readFrom(bb);
            // pad: 3 bytes
            bb.skipBytes(3);
            U64 generationId = U64.ofRaw(bb.readLong());
            List<OFRoleProp> properties = ChannelUtils.readList(bb, length - (bb.readerIndex() - start), OFRolePropVer14.READER);

            OFRoleStatusVer14 roleStatusVer14 = new OFRoleStatusVer14(
                    xid,
                      role,
                      reason,
                      generationId,
                      properties
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", roleStatusVer14);
            return roleStatusVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFRoleStatusVer14Funnel FUNNEL = new OFRoleStatusVer14Funnel();
    static class OFRoleStatusVer14Funnel implements Funnel<OFRoleStatusVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFRoleStatusVer14 message, PrimitiveSink sink) {
            // fixed value property version = 5
            sink.putByte((byte) 0x5);
            // fixed value property type = 30
            sink.putByte((byte) 0x1e);
            // FIXME: skip funnel of length
            sink.putLong(message.xid);
            sink.putLong(message.role);
            OFControllerRoleReasonSerializerVer14.putTo(message.reason, sink);
            // skip pad (3 bytes)
            message.generationId.putTo(sink);
            FunnelUtils.putList(message.properties, sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFRoleStatusVer14> {
        @Override
        public void write(ByteBuf bb, OFRoleStatusVer14 message) {
            int startIndex = bb.writerIndex();
            // fixed value property version = 5
            bb.writeByte((byte) 0x5);
            // fixed value property type = 30
            bb.writeByte((byte) 0x1e);
            // length is length of variable message, will be updated at the end
            int lengthIndex = bb.writerIndex();
            bb.writeShort(U16.t(0));

            bb.writeInt(U32.t(message.xid));
            bb.writeInt(U32.t(message.role));
            OFControllerRoleReasonSerializerVer14.writeTo(bb, message.reason);
            // pad: 3 bytes
            bb.writeZero(3);
            bb.writeLong(message.generationId.getValue());
            ChannelUtils.writeList(bb, message.properties);

            // update length field
            int length = bb.writerIndex() - startIndex;
            bb.setShort(lengthIndex, length);

        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFRoleStatusVer14(");
        b.append("xid=").append(xid);
        b.append(", ");
        b.append("role=").append(role);
        b.append(", ");
        b.append("reason=").append(reason);
        b.append(", ");
        b.append("generationId=").append(generationId);
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
        OFRoleStatusVer14 other = (OFRoleStatusVer14) obj;

        if( xid != other.xid)
            return false;
        if( role != other.role)
            return false;
        if (reason == null) {
            if (other.reason != null)
                return false;
        } else if (!reason.equals(other.reason))
            return false;
        if (generationId == null) {
            if (other.generationId != null)
                return false;
        } else if (!generationId.equals(other.generationId))
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

        result = prime *  (int) (xid ^ (xid >>> 32));
        result = prime *  (int) (role ^ (role >>> 32));
        result = prime * result + ((reason == null) ? 0 : reason.hashCode());
        result = prime * result + ((generationId == null) ? 0 : generationId.hashCode());
        result = prime * result + ((properties == null) ? 0 : properties.hashCode());
        return result;
    }

}
