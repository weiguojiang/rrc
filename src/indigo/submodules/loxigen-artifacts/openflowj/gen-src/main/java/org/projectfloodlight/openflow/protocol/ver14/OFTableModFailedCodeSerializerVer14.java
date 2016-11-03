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
import org.projectfloodlight.openflow.protocol.OFTableModFailedCode;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;

public class OFTableModFailedCodeSerializerVer14 {

    public final static short BAD_TABLE_VAL = (short) 0x0;
    public final static short BAD_CONFIG_VAL = (short) 0x1;
    public final static short EPERM_VAL = (short) 0x2;

    public static OFTableModFailedCode readFrom(ByteBuf bb) throws OFParseError {
        try {
            return ofWireValue(bb.readShort());
        } catch (IllegalArgumentException e) {
            throw new OFParseError(e);
        }
    }

    public static void writeTo(ByteBuf bb, OFTableModFailedCode e) {
        bb.writeShort(toWireValue(e));
    }

    public static void putTo(OFTableModFailedCode e, PrimitiveSink sink) {
        sink.putShort(toWireValue(e));
    }

    public static OFTableModFailedCode ofWireValue(short val) {
        switch(val) {
            case BAD_TABLE_VAL:
                return OFTableModFailedCode.BAD_TABLE;
            case BAD_CONFIG_VAL:
                return OFTableModFailedCode.BAD_CONFIG;
            case EPERM_VAL:
                return OFTableModFailedCode.EPERM;
            default:
                throw new IllegalArgumentException("Illegal wire value for type OFTableModFailedCode in version 1.4: " + val);
        }
    }


    public static short toWireValue(OFTableModFailedCode e) {
        switch(e) {
            case BAD_TABLE:
                return BAD_TABLE_VAL;
            case BAD_CONFIG:
                return BAD_CONFIG_VAL;
            case EPERM:
                return EPERM_VAL;
            default:
                throw new IllegalArgumentException("Illegal enum value for type OFTableModFailedCode in version 1.4: " + e);
        }
    }

}
