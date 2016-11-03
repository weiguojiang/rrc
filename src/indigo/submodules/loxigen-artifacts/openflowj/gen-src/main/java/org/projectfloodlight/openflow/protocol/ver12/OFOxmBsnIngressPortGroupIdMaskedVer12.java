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

class OFOxmBsnIngressPortGroupIdMaskedVer12 implements OFOxmBsnIngressPortGroupIdMasked {
    private static final Logger logger = LoggerFactory.getLogger(OFOxmBsnIngressPortGroupIdMaskedVer12.class);
    // version: 1.2
    final static byte WIRE_VERSION = 3;
    final static int LENGTH = 12;

        private final static ClassId DEFAULT_VALUE = ClassId.NONE;
        private final static ClassId DEFAULT_VALUE_MASK = ClassId.NONE;

    // OF message fields
    private final ClassId value;
    private final ClassId mask;
//
    // Immutable default instance
    final static OFOxmBsnIngressPortGroupIdMaskedVer12 DEFAULT = new OFOxmBsnIngressPortGroupIdMaskedVer12(
        DEFAULT_VALUE, DEFAULT_VALUE_MASK
    );

    // package private constructor - used by readers, builders, and factory
    OFOxmBsnIngressPortGroupIdMaskedVer12(ClassId value, ClassId mask) {
        if(value == null) {
            throw new NullPointerException("OFOxmBsnIngressPortGroupIdMaskedVer12: property value cannot be null");
        }
        if(mask == null) {
            throw new NullPointerException("OFOxmBsnIngressPortGroupIdMaskedVer12: property mask cannot be null");
        }
        this.value = value;
        this.mask = mask;
    }

    // Accessors for OF message fields
    @Override
    public long getTypeLen() {
        return 0x32908L;
    }

    @Override
    public ClassId getValue() {
        return value;
    }

    @Override
    public ClassId getMask() {
        return mask;
    }

    @Override
    public MatchField<ClassId> getMatchField() {
        return MatchField.BSN_INGRESS_PORT_GROUP_ID;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    public OFOxm<ClassId> getCanonical() {
        if (ClassId.NO_MASK.equals(mask)) {
            return new OFOxmBsnIngressPortGroupIdVer12(value);
        } else if(ClassId.FULL_MASK.equals(mask)) {
            return null;
        } else {
            return this;
        }
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



    public OFOxmBsnIngressPortGroupIdMasked.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFOxmBsnIngressPortGroupIdMasked.Builder {
        final OFOxmBsnIngressPortGroupIdMaskedVer12 parentMessage;

        // OF message fields
        private boolean valueSet;
        private ClassId value;
        private boolean maskSet;
        private ClassId mask;

        BuilderWithParent(OFOxmBsnIngressPortGroupIdMaskedVer12 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getTypeLen() {
        return 0x32908L;
    }

    @Override
    public ClassId getValue() {
        return value;
    }

    @Override
    public OFOxmBsnIngressPortGroupIdMasked.Builder setValue(ClassId value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public ClassId getMask() {
        return mask;
    }

    @Override
    public OFOxmBsnIngressPortGroupIdMasked.Builder setMask(ClassId mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<ClassId> getMatchField() {
        return MatchField.BSN_INGRESS_PORT_GROUP_ID;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<ClassId> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



        @Override
        public OFOxmBsnIngressPortGroupIdMasked build() {
                ClassId value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");
                ClassId mask = this.maskSet ? this.mask : parentMessage.mask;
                if(mask == null)
                    throw new NullPointerException("Property mask must not be null");

                //
                return new OFOxmBsnIngressPortGroupIdMaskedVer12(
                    value,
                    mask
                );
        }

    }

    static class Builder implements OFOxmBsnIngressPortGroupIdMasked.Builder {
        // OF message fields
        private boolean valueSet;
        private ClassId value;
        private boolean maskSet;
        private ClassId mask;

    @Override
    public long getTypeLen() {
        return 0x32908L;
    }

    @Override
    public ClassId getValue() {
        return value;
    }

    @Override
    public OFOxmBsnIngressPortGroupIdMasked.Builder setValue(ClassId value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public ClassId getMask() {
        return mask;
    }

    @Override
    public OFOxmBsnIngressPortGroupIdMasked.Builder setMask(ClassId mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<ClassId> getMatchField() {
        return MatchField.BSN_INGRESS_PORT_GROUP_ID;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<ClassId> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }

//
        @Override
        public OFOxmBsnIngressPortGroupIdMasked build() {
            ClassId value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");
            ClassId mask = this.maskSet ? this.mask : DEFAULT_VALUE_MASK;
            if(mask == null)
                throw new NullPointerException("Property mask must not be null");


            return new OFOxmBsnIngressPortGroupIdMaskedVer12(
                    value,
                    mask
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFOxmBsnIngressPortGroupIdMasked> {
        @Override
        public OFOxmBsnIngressPortGroupIdMasked readFrom(ByteBuf bb) throws OFParseError {
            // fixed value property typeLen == 0x32908L
            int typeLen = bb.readInt();
            if(typeLen != 0x32908)
                throw new OFParseError("Wrong typeLen: Expected=0x32908L(0x32908L), got="+typeLen);
            ClassId value = ClassId.read4Bytes(bb);
            ClassId mask = ClassId.read4Bytes(bb);

            OFOxmBsnIngressPortGroupIdMaskedVer12 oxmBsnIngressPortGroupIdMaskedVer12 = new OFOxmBsnIngressPortGroupIdMaskedVer12(
                    value,
                      mask
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", oxmBsnIngressPortGroupIdMaskedVer12);
            return oxmBsnIngressPortGroupIdMaskedVer12;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFOxmBsnIngressPortGroupIdMaskedVer12Funnel FUNNEL = new OFOxmBsnIngressPortGroupIdMaskedVer12Funnel();
    static class OFOxmBsnIngressPortGroupIdMaskedVer12Funnel implements Funnel<OFOxmBsnIngressPortGroupIdMaskedVer12> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFOxmBsnIngressPortGroupIdMaskedVer12 message, PrimitiveSink sink) {
            // fixed value property typeLen = 0x32908L
            sink.putInt(0x32908);
            message.value.putTo(sink);
            message.mask.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFOxmBsnIngressPortGroupIdMaskedVer12> {
        @Override
        public void write(ByteBuf bb, OFOxmBsnIngressPortGroupIdMaskedVer12 message) {
            // fixed value property typeLen = 0x32908L
            bb.writeInt(0x32908);
            message.value.write4Bytes(bb);
            message.mask.write4Bytes(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFOxmBsnIngressPortGroupIdMaskedVer12(");
        b.append("value=").append(value);
        b.append(", ");
        b.append("mask=").append(mask);
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
        OFOxmBsnIngressPortGroupIdMaskedVer12 other = (OFOxmBsnIngressPortGroupIdMaskedVer12) obj;

        if (value == null) {
            if (other.value != null)
                return false;
        } else if (!value.equals(other.value))
            return false;
        if (mask == null) {
            if (other.mask != null)
                return false;
        } else if (!mask.equals(other.mask))
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((value == null) ? 0 : value.hashCode());
        result = prime * result + ((mask == null) ? 0 : mask.hashCode());
        return result;
    }

}
