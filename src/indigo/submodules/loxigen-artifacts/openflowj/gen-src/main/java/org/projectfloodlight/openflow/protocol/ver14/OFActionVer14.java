// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_virtual_class.java
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
import io.netty.buffer.ByteBuf;
import java.util.Set;

abstract class OFActionVer14 {
    // version: 1.4
    final static byte WIRE_VERSION = 5;
    final static int MINIMUM_LENGTH = 8;


    public final static OFActionVer14.Reader READER = new Reader();

    static class Reader implements OFMessageReader<OFAction> {
        @Override
        public OFAction readFrom(ByteBuf bb) throws OFParseError {
            if(bb.readableBytes() < MINIMUM_LENGTH)
                return null;
            int start = bb.readerIndex();
            short type = bb.readShort();
            bb.readerIndex(start);
            switch(type) {
               case (short) 0xffff:
                   // discriminator value OFActionType.EXPERIMENTER=65535 for class OFActionExperimenterVer14
                   return OFActionExperimenterVer14.READER.readFrom(bb);
               case (short) 0x0:
                   // discriminator value OFActionType.OUTPUT=0 for class OFActionOutputVer14
                   return OFActionOutputVer14.READER.readFrom(bb);
               case (short) 0xc:
                   // discriminator value OFActionType.COPY_TTL_IN=12 for class OFActionCopyTtlInVer14
                   return OFActionCopyTtlInVer14.READER.readFrom(bb);
               case (short) 0xb:
                   // discriminator value OFActionType.COPY_TTL_OUT=11 for class OFActionCopyTtlOutVer14
                   return OFActionCopyTtlOutVer14.READER.readFrom(bb);
               case (short) 0x10:
                   // discriminator value OFActionType.DEC_MPLS_TTL=16 for class OFActionDecMplsTtlVer14
                   return OFActionDecMplsTtlVer14.READER.readFrom(bb);
               case (short) 0x18:
                   // discriminator value OFActionType.DEC_NW_TTL=24 for class OFActionDecNwTtlVer14
                   return OFActionDecNwTtlVer14.READER.readFrom(bb);
               case (short) 0x16:
                   // discriminator value OFActionType.GROUP=22 for class OFActionGroupVer14
                   return OFActionGroupVer14.READER.readFrom(bb);
               case (short) 0x14:
                   // discriminator value OFActionType.POP_MPLS=20 for class OFActionPopMplsVer14
                   return OFActionPopMplsVer14.READER.readFrom(bb);
               case (short) 0x12:
                   // discriminator value OFActionType.POP_VLAN=18 for class OFActionPopVlanVer14
                   return OFActionPopVlanVer14.READER.readFrom(bb);
               case (short) 0x13:
                   // discriminator value OFActionType.PUSH_MPLS=19 for class OFActionPushMplsVer14
                   return OFActionPushMplsVer14.READER.readFrom(bb);
               case (short) 0x11:
                   // discriminator value OFActionType.PUSH_VLAN=17 for class OFActionPushVlanVer14
                   return OFActionPushVlanVer14.READER.readFrom(bb);
               case (short) 0xf:
                   // discriminator value OFActionType.SET_MPLS_TTL=15 for class OFActionSetMplsTtlVer14
                   return OFActionSetMplsTtlVer14.READER.readFrom(bb);
               case (short) 0x17:
                   // discriminator value OFActionType.SET_NW_TTL=23 for class OFActionSetNwTtlVer14
                   return OFActionSetNwTtlVer14.READER.readFrom(bb);
               case (short) 0x15:
                   // discriminator value OFActionType.SET_QUEUE=21 for class OFActionSetQueueVer14
                   return OFActionSetQueueVer14.READER.readFrom(bb);
               case (short) 0x19:
                   // discriminator value OFActionType.SET_FIELD=25 for class OFActionSetFieldVer14
                   return OFActionSetFieldVer14.READER.readFrom(bb);
               case (short) 0x1b:
                   // discriminator value OFActionType.POP_PBB=27 for class OFActionPopPbbVer14
                   return OFActionPopPbbVer14.READER.readFrom(bb);
               case (short) 0x1a:
                   // discriminator value OFActionType.PUSH_PBB=26 for class OFActionPushPbbVer14
                   return OFActionPushPbbVer14.READER.readFrom(bb);
               default:
                   throw new OFParseError("Unknown value for discriminator type of class OFActionVer14: " + type);
            }
        }
    }
}
