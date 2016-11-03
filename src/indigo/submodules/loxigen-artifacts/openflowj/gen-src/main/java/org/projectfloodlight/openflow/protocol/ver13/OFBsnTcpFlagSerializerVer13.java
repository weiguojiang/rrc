// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template const_set_serializer.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver13;

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
import org.projectfloodlight.openflow.protocol.OFBsnTcpFlag;
import java.util.Set;
import io.netty.buffer.ByteBuf;
import com.google.common.hash.PrimitiveSink;
import java.util.EnumSet;
import java.util.Collections;


public class OFBsnTcpFlagSerializerVer13 {

    public final static short BSN_TCP_FLAG_FIN_VAL = (short) 0x1;
    public final static short BSN_TCP_FLAG_SYN_VAL = (short) 0x2;
    public final static short BSN_TCP_FLAG_RST_VAL = (short) 0x4;
    public final static short BSN_TCP_FLAG_PSH_VAL = (short) 0x8;
    public final static short BSN_TCP_FLAG_ACK_VAL = (short) 0x10;
    public final static short BSN_TCP_FLAG_URG_VAL = (short) 0x20;
    public final static short BSN_TCP_FLAG_ECE_VAL = (short) 0x40;
    public final static short BSN_TCP_FLAG_CWR_VAL = (short) 0x80;
    public final static short BSN_TCP_FLAG_NS_VAL = (short) 0x100;

    public static Set<OFBsnTcpFlag> readFrom(ByteBuf bb) throws OFParseError {
        try {
            return ofWireValue(bb.readShort());
        } catch (IllegalArgumentException e) {
            throw new OFParseError(e);
        }
    }

    public static void writeTo(ByteBuf bb, Set<OFBsnTcpFlag> set) {
        bb.writeShort(toWireValue(set));
    }

    public static void putTo(Set<OFBsnTcpFlag> set, PrimitiveSink sink) {
        sink.putShort(toWireValue(set));
    }


    public static Set<OFBsnTcpFlag> ofWireValue(short val) {
        EnumSet<OFBsnTcpFlag> set = EnumSet.noneOf(OFBsnTcpFlag.class);

        if((val & BSN_TCP_FLAG_FIN_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_FIN);
        if((val & BSN_TCP_FLAG_SYN_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_SYN);
        if((val & BSN_TCP_FLAG_RST_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_RST);
        if((val & BSN_TCP_FLAG_PSH_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_PSH);
        if((val & BSN_TCP_FLAG_ACK_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_ACK);
        if((val & BSN_TCP_FLAG_URG_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_URG);
        if((val & BSN_TCP_FLAG_ECE_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_ECE);
        if((val & BSN_TCP_FLAG_CWR_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_CWR);
        if((val & BSN_TCP_FLAG_NS_VAL) != 0)
            set.add(OFBsnTcpFlag.BSN_TCP_FLAG_NS);
        return Collections.unmodifiableSet(set);
    }

    public static short toWireValue(Set<OFBsnTcpFlag> set) {
        short wireValue = 0;

        for(OFBsnTcpFlag e: set) {
            switch(e) {
                case BSN_TCP_FLAG_FIN:
                    wireValue |= BSN_TCP_FLAG_FIN_VAL;
                    break;
                case BSN_TCP_FLAG_SYN:
                    wireValue |= BSN_TCP_FLAG_SYN_VAL;
                    break;
                case BSN_TCP_FLAG_RST:
                    wireValue |= BSN_TCP_FLAG_RST_VAL;
                    break;
                case BSN_TCP_FLAG_PSH:
                    wireValue |= BSN_TCP_FLAG_PSH_VAL;
                    break;
                case BSN_TCP_FLAG_ACK:
                    wireValue |= BSN_TCP_FLAG_ACK_VAL;
                    break;
                case BSN_TCP_FLAG_URG:
                    wireValue |= BSN_TCP_FLAG_URG_VAL;
                    break;
                case BSN_TCP_FLAG_ECE:
                    wireValue |= BSN_TCP_FLAG_ECE_VAL;
                    break;
                case BSN_TCP_FLAG_CWR:
                    wireValue |= BSN_TCP_FLAG_CWR_VAL;
                    break;
                case BSN_TCP_FLAG_NS:
                    wireValue |= BSN_TCP_FLAG_NS_VAL;
                    break;
                default:
                    throw new IllegalArgumentException("Illegal enum value for type OFBsnTcpFlag in version 1.3: " + e);
            }
        }
        return wireValue;
    }

}
