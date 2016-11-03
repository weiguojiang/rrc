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

class OFOxmBsnUdf1MaskedVer12 implements OFOxmBsnUdf1Masked {
    private static final Logger logger = LoggerFactory.getLogger(OFOxmBsnUdf1MaskedVer12.class);
    // version: 1.2
    final static byte WIRE_VERSION = 3;
    final static int LENGTH = 12;

        private final static UDF DEFAULT_VALUE = UDF.ZERO;
        private final static UDF DEFAULT_VALUE_MASK = UDF.ZERO;

    // OF message fields
    private final UDF value;
    private final UDF mask;
//
    // Immutable default instance
    final static OFOxmBsnUdf1MaskedVer12 DEFAULT = new OFOxmBsnUdf1MaskedVer12(
        DEFAULT_VALUE, DEFAULT_VALUE_MASK
    );

    // package private constructor - used by readers, builders, and factory
    OFOxmBsnUdf1MaskedVer12(UDF value, UDF mask) {
        if(value == null) {
            throw new NullPointerException("OFOxmBsnUdf1MaskedVer12: property value cannot be null");
        }
        if(mask == null) {
            throw new NullPointerException("OFOxmBsnUdf1MaskedVer12: property mask cannot be null");
        }
        this.value = value;
        this.mask = mask;
    }

    // Accessors for OF message fields
    @Override
    public long getTypeLen() {
        return 0x31308L;
    }

    @Override
    public UDF getValue() {
        return value;
    }

    @Override
    public UDF getMask() {
        return mask;
    }

    @Override
    public MatchField<UDF> getMatchField() {
        return MatchField.BSN_UDF1;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    public OFOxm<UDF> getCanonical() {
        if (UDF.NO_MASK.equals(mask)) {
            return new OFOxmBsnUdf1Ver12(value);
        } else if(UDF.FULL_MASK.equals(mask)) {
            return null;
        } else {
            return this;
        }
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



    public OFOxmBsnUdf1Masked.Builder createBuilder() {
        return new BuilderWithParent(this);
    }

    static class BuilderWithParent implements OFOxmBsnUdf1Masked.Builder {
        final OFOxmBsnUdf1MaskedVer12 parentMessage;

        // OF message fields
        private boolean valueSet;
        private UDF value;
        private boolean maskSet;
        private UDF mask;

        BuilderWithParent(OFOxmBsnUdf1MaskedVer12 parentMessage) {
            this.parentMessage = parentMessage;
        }

    @Override
    public long getTypeLen() {
        return 0x31308L;
    }

    @Override
    public UDF getValue() {
        return value;
    }

    @Override
    public OFOxmBsnUdf1Masked.Builder setValue(UDF value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public UDF getMask() {
        return mask;
    }

    @Override
    public OFOxmBsnUdf1Masked.Builder setMask(UDF mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<UDF> getMatchField() {
        return MatchField.BSN_UDF1;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<UDF> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }



        @Override
        public OFOxmBsnUdf1Masked build() {
                UDF value = this.valueSet ? this.value : parentMessage.value;
                if(value == null)
                    throw new NullPointerException("Property value must not be null");
                UDF mask = this.maskSet ? this.mask : parentMessage.mask;
                if(mask == null)
                    throw new NullPointerException("Property mask must not be null");

                //
                return new OFOxmBsnUdf1MaskedVer12(
                    value,
                    mask
                );
        }

    }

    static class Builder implements OFOxmBsnUdf1Masked.Builder {
        // OF message fields
        private boolean valueSet;
        private UDF value;
        private boolean maskSet;
        private UDF mask;

    @Override
    public long getTypeLen() {
        return 0x31308L;
    }

    @Override
    public UDF getValue() {
        return value;
    }

    @Override
    public OFOxmBsnUdf1Masked.Builder setValue(UDF value) {
        this.value = value;
        this.valueSet = true;
        return this;
    }
    @Override
    public UDF getMask() {
        return mask;
    }

    @Override
    public OFOxmBsnUdf1Masked.Builder setMask(UDF mask) {
        this.mask = mask;
        this.maskSet = true;
        return this;
    }
    @Override
    public MatchField<UDF> getMatchField() {
        return MatchField.BSN_UDF1;
    }

    @Override
    public boolean isMasked() {
        return true;
    }

    @Override
    public OFOxm<UDF> getCanonical()throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Property canonical not supported in version 1.2");
    }

    @Override
    public OFVersion getVersion() {
        return OFVersion.OF_12;
    }

//
        @Override
        public OFOxmBsnUdf1Masked build() {
            UDF value = this.valueSet ? this.value : DEFAULT_VALUE;
            if(value == null)
                throw new NullPointerException("Property value must not be null");
            UDF mask = this.maskSet ? this.mask : DEFAULT_VALUE_MASK;
            if(mask == null)
                throw new NullPointerException("Property mask must not be null");


            return new OFOxmBsnUdf1MaskedVer12(
                    value,
                    mask
                );
        }

    }


    final static Reader READER = new Reader();
    static class Reader implements OFMessageReader<OFOxmBsnUdf1Masked> {
        @Override
        public OFOxmBsnUdf1Masked readFrom(ByteBuf bb) throws OFParseError {
            // fixed value property typeLen == 0x31308L
            int typeLen = bb.readInt();
            if(typeLen != 0x31308)
                throw new OFParseError("Wrong typeLen: Expected=0x31308L(0x31308L), got="+typeLen);
            UDF value = UDF.read4Bytes(bb);
            UDF mask = UDF.read4Bytes(bb);

            OFOxmBsnUdf1MaskedVer12 oxmBsnUdf1MaskedVer12 = new OFOxmBsnUdf1MaskedVer12(
                    value,
                      mask
                    );
            if(logger.isTraceEnabled())
                logger.trace("readFrom - read={}", oxmBsnUdf1MaskedVer12);
            return oxmBsnUdf1MaskedVer12;
        }
    }

    public void putTo(PrimitiveSink sink) {
        FUNNEL.funnel(this, sink);
    }

    final static OFOxmBsnUdf1MaskedVer12Funnel FUNNEL = new OFOxmBsnUdf1MaskedVer12Funnel();
    static class OFOxmBsnUdf1MaskedVer12Funnel implements Funnel<OFOxmBsnUdf1MaskedVer12> {
        private static final long serialVersionUID = 1L;
        @Override
        public void funnel(OFOxmBsnUdf1MaskedVer12 message, PrimitiveSink sink) {
            // fixed value property typeLen = 0x31308L
            sink.putInt(0x31308);
            message.value.putTo(sink);
            message.mask.putTo(sink);
        }
    }


    public void writeTo(ByteBuf bb) {
        WRITER.write(bb, this);
    }

    final static Writer WRITER = new Writer();
    static class Writer implements OFMessageWriter<OFOxmBsnUdf1MaskedVer12> {
        @Override
        public void write(ByteBuf bb, OFOxmBsnUdf1MaskedVer12 message) {
            // fixed value property typeLen = 0x31308L
            bb.writeInt(0x31308);
            message.value.write4Bytes(bb);
            message.mask.write4Bytes(bb);


        }
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder("OFOxmBsnUdf1MaskedVer12(");
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
        OFOxmBsnUdf1MaskedVer12 other = (OFOxmBsnUdf1MaskedVer12) obj;

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
