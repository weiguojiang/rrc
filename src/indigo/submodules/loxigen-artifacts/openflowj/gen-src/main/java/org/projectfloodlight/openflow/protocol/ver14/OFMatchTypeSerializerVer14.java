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
import org.projectfloodlight.openflow.protocol.OFMatchType;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;

public class OFMatchTypeSerializerVer14 {

    public final static short STANDARD_VAL = (short) 0x0;
    public final static short OXM_VAL = (short) 0x1;

    public static OFMatchType readFrom(ByteBuf bb) throws OFParseError {
        try {
            return ofWireValue(bb.readShort());
        } catch (IllegalArgumentException e) {
            throw new OFParseError(e);
        }
    }

    public static void writeTo(ByteBuf bb, OFMatchType e) {
        bb.writeShort(toWireValue(e));
    }

    public static void putTo(OFMatchType e, PrimitiveSink sink) {
        sink.putShort(toWireValue(e));
    }

    public static OFMatchType ofWireValue(short val) {
        switch(val) {
            case STANDARD_VAL:
                return OFMatchType.STANDARD;
            case OXM_VAL:
                return OFMatchType.OXM;
            default:
                throw new IllegalArgumentException("Illegal wire value for type OFMatchType in version 1.4: " + val);
        }
    }


    public static short toWireValue(OFMatchType e) {
        switch(e) {
            case STANDARD:
                return STANDARD_VAL;
            case OXM:
                return OXM_VAL;
            default:
                throw new IllegalArgumentException("Illegal enum value for type OFMatchType in version 1.4: " + e);
        }
    }

}
