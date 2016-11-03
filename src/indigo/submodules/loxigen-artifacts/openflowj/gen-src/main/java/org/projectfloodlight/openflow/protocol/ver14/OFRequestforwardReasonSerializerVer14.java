// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template const_serializer.java
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
import org.projectfloodlight.openflow.protocol.OFRequestforwardReason;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;

public class OFRequestforwardReasonSerializerVer14 {

    public final static short GROUP_MOD_VAL = (short) 0x0;
    public final static short METER_MOD_VAL = (short) 0x1;

    public static OFRequestforwardReason readFrom(ByteBuf bb) throws OFParseError {
        try {
            return ofWireValue(U8.f(bb.readByte()));
        } catch (IllegalArgumentException e) {
            throw new OFParseError(e);
        }
    }

    public static void writeTo(ByteBuf bb, OFRequestforwardReason e) {
        bb.writeByte(U8.t(toWireValue(e)));
    }

    public static void putTo(OFRequestforwardReason e, PrimitiveSink sink) {
        sink.putShort(toWireValue(e));
    }

    public static OFRequestforwardReason ofWireValue(short val) {
        switch(val) {
            case GROUP_MOD_VAL:
                return OFRequestforwardReason.GROUP_MOD;
            case METER_MOD_VAL:
                return OFRequestforwardReason.METER_MOD;
            default:
                throw new IllegalArgumentException("Illegal wire value for type OFRequestforwardReason in version 1.4: " + val);
        }
    }


    public static short toWireValue(OFRequestforwardReason e) {
        switch(e) {
            case GROUP_MOD:
                return GROUP_MOD_VAL;
            case METER_MOD:
                return METER_MOD_VAL;
            default:
                throw new IllegalArgumentException("Illegal enum value for type OFRequestforwardReason in version 1.4: " + e);
        }
    }

}
