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
import java.util.Set;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import com.google.common.hash.Funnel;

class OFOxmMetadataMaskedVer14 implements OFOxmMetadataMasked {
    private static final Logger logger = LoggerFactory.getLogger(OFOxmMetadataMaskedVer14.class);
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int LENGTH = 20;

        private final static OFMetadata DEFAULT_VALUE = OFMetadata.NONE;
        private final static OFMetadata DEFAULT_VALUE_MASK = OFMetadata.NONE;

    // OF message fields
    private final OFMetadata value;
    private final OFMetadata mask;
//
    // Immutable default instance
    final static OFOxmMetadataMaskedVer14 DEFAULT = new OFOxmMetadataMaskedVer14(
        DEFAULT_VALUE, DEFAULT_VALUE_MASK
    );

    // package private constructor - used by readers, builders, and factory
    OFOxmMetadataMaskedVer14(OFMetadata value, OFMetadata mask) {
        if(value == null) {
            throw new NullPointerException("OFOxmMetadataMaskedVer14: property value cannot be null");
        }
        if(mask == null) {
            throw new NullPointerException("OFOxmMetadataMaskedVer14: property mask cannot be null");
        }
        this.value = value;
        this.mask = mask;
    }

    // Accessors for OF message fields
    @Override
    public long getTypeLen() {
        return 0x80000510L;
    }

    @Override
    public OFMetadata getValue() {
        return value;
    }

    @Override
    public OFMetadata getMask() {
        return mask;
    }

    @Override
    public MatchField<OFMetadata> getMatchField() {
        return MatchField.METADATA;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    public OFOxm<OFMetadata> getCanonical() {
        if (OFMetadata.NO_MASK.equals(mask)) {
            return new OFOxmMetadataVer14(value);
        } else if(OFMetadata.FULL_MASK.equals(mask)) {
            return null;
        } else {
            return this;
        }
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



    public OFOxmMetadataMasked.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFOxmMetadataMasked.Builder {
        final OFOxmMetadataMaskedVer14 parentMessage;

        // OF message fields
        private boolean valueSet;
        private OFMetadata value;
        private boolean maskSet;
        private OFMetadata mask;

        BuilderWithParent(OFOxmMetadataMaskedVer14 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getTypeLen() {
        return 0x80000510L;
    }

    @Override
    public OFMetadata getValue() {
        return value;
    }

    @Override
    public OFOxmMetadataMasked.Builder setValue(OFMetadata value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public OFMetadata getMask() {
        return mask;
    }

    @Override
    public OFOxmMetadataMasked.Builder setMask(OFMetadata mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<OFMetadata> getMatchField() {
        return MatchField.METADATA;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<OFMetadata> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.4");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }



        @Override
        public OFOxmMetadataMasked build() {
                OFMetadata value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");
                OFMetadata mask = this.maskSet ? this.mask : parentMessage.mask;
                if(mask == null)
                    throw new NullPointerException("Property mask must not be null");

                //
                return new OFOxmMetadataMaskedVer14(
                    value,
                    mask
                );
        }

    }

    static class Builder implements OFOxmMetadataMasked.Builder {
        // OF message fields
        private boolean valueSet;
        private OFMetadata value;
        private boolean maskSet;
        private OFMetadata mask;

    @Override
    public long getTypeLen() {
        return 0x80000510L;
    }

    @Override
    public OFMetadata getValue() {
        return value;
    }

    @Override
    public OFOxmMetadataMasked.Builder setValue(OFMetadata value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public OFMetadata getMask() {
        return mask;
    }

    @Override
    public OFOxmMetadataMasked.Builder setMask(OFMetadata mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<OFMetadata> getMatchField() {
        return MatchField.METADATA;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<OFMetadata> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.4");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_14;
    }

//
        @Override
        public OFOxmMetadataMasked build() {
            OFMetadata value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");
            OFMetadata mask = this.maskSet ? this.mask : DEFAULT_VALUE_MASK;
            if(mask == null)
                throw new NullPointerException("Property mask must not be null");


            return new OFOxmMetadataMaskedVer14(
                    value,
                    mask
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFOxmMetadataMasked> {
        @Override
        public OFOxmMetadataMasked readFrom(ByteBuf bb) throws OFParseError {
            // fixed value property typeLen == 0x80000510L
            int typeLen = bb.readInt();
            if(typeLen != (int) 0x80000510)
                throw new OFParseError("Wrong typeLen: Expected=0x80000510L(0x80000510L), got="+typeLen);
            OFMetadata value = OFMetadata.read8Bytes(bb);
            OFMetadata mask = OFMetadata.read8Bytes(bb);

            OFOxmMetadataMaskedVer14 oxmMetadataMaskedVer14 = new OFOxmMetadataMaskedVer14(
                    value,
                      mask
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", oxmMetadataMaskedVer14);
            return oxmMetadataMaskedVer14;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFOxmMetadataMaskedVer14Funnel FUNNEL = new OFOxmMetadataMaskedVer14Funnel();
    static class OFOxmMetadataMaskedVer14Funnel implements Funnel<OFOxmMetadataMaskedVer14> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFOxmMetadataMaskedVer14 message, PrimitiveSink sink) {
            // fixed value property typeLen = 0x80000510L
            sink.putInt((int) 0x80000510);
            message.value.putTo(sink);
            message.mask.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFOxmMetadataMaskedVer14> {
        @Override
        public void write(ByteBuf bb, OFOxmMetadataMaskedVer14 message) {
            // fixed value property typeLen = 0x80000510L
            bb.writeInt((int) 0x80000510);
            message.value.write8Bytes(bb);
            message.mask.write8Bytes(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFOxmMetadataMaskedVer14(");
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
        OFOxmMetadataMaskedVer14 other = (OFOxmMetadataMaskedVer14) obj;

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
