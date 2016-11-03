// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_virtual_class.java
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
import io.netty.buffer.ByteBuf;
import java.util.Set;

abstract class OFBsnHeaderVer10 {
    // version: 1.0
    final static byte WIRE_VERSION = 1;
    final static int MINIMUM_LENGTH = 16;


    public final static OFBsnHeaderVer10.Reader READER = new Reader();

    static class Reader implements OFMessageReader<OFBsnHeader> {
        @Override
        public OFBsnHeader readFrom(ByteBuf bb) throws OFParseError {
            if(bb.readableBytes() < MINIMUM_LENGTH)
                return null;
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
            if(length < MINIMUM_LENGTH)
                throw new OFParseError("Wrong length: Expected to be >= " + MINIMUM_LENGTH + ", was: " + length);
            U32.f(bb.readInt());
            // fixed value property experimenter == 0x5c16c7L
            int experimenter = bb.readInt();
            if(experimenter != 0x5c16c7)
                throw new OFParseError("Wrong experimenter: Expected=0x5c16c7L(0x5c16c7L), got="+experimenter);
            int subtype = bb.readInt();
            bb.readerIndex(start);
            switch(subtype) {
               case 0x16:
                   // discriminator value 0x16L=0x16L for class OFBsnBwClearDataReplyVer10
                   return OFBsnBwClearDataReplyVer10.READER.readFrom(bb);
               case 0x15:
                   // discriminator value 0x15L=0x15L for class OFBsnBwClearDataRequestVer10
                   return OFBsnBwClearDataRequestVer10.READER.readFrom(bb);
               case 0x14:
                   // discriminator value 0x14L=0x14L for class OFBsnBwEnableGetReplyVer10
                   return OFBsnBwEnableGetReplyVer10.READER.readFrom(bb);
               case 0x13:
                   // discriminator value 0x13L=0x13L for class OFBsnBwEnableGetRequestVer10
                   return OFBsnBwEnableGetRequestVer10.READER.readFrom(bb);
               case 0x17:
                   // discriminator value 0x17L=0x17L for class OFBsnBwEnableSetReplyVer10
                   return OFBsnBwEnableSetReplyVer10.READER.readFrom(bb);
               case 0x12:
                   // discriminator value 0x12L=0x12L for class OFBsnBwEnableSetRequestVer10
                   return OFBsnBwEnableSetRequestVer10.READER.readFrom(bb);
               case 0xa:
                   // discriminator value 0xaL=0xaL for class OFBsnGetInterfacesReplyVer10
                   return OFBsnGetInterfacesReplyVer10.READER.readFrom(bb);
               case 0x9:
                   // discriminator value 0x9L=0x9L for class OFBsnGetInterfacesRequestVer10
                   return OFBsnGetInterfacesRequestVer10.READER.readFrom(bb);
               case 0x2:
                   // discriminator value 0x2L=0x2L for class OFBsnGetIpMaskReplyVer10
                   return OFBsnGetIpMaskReplyVer10.READER.readFrom(bb);
               case 0x1:
                   // discriminator value 0x1L=0x1L for class OFBsnGetIpMaskRequestVer10
                   return OFBsnGetIpMaskRequestVer10.READER.readFrom(bb);
               case 0xe:
                   // discriminator value 0xeL=0xeL for class OFBsnGetL2TableReplyVer10
                   return OFBsnGetL2TableReplyVer10.READER.readFrom(bb);
               case 0xd:
                   // discriminator value 0xdL=0xdL for class OFBsnGetL2TableRequestVer10
                   return OFBsnGetL2TableRequestVer10.READER.readFrom(bb);
               case 0x5:
                   // discriminator value 0x5L=0x5L for class OFBsnGetMirroringReplyVer10
                   return OFBsnGetMirroringReplyVer10.READER.readFrom(bb);
               case 0x4:
                   // discriminator value 0x4L=0x4L for class OFBsnGetMirroringRequestVer10
                   return OFBsnGetMirroringRequestVer10.READER.readFrom(bb);
               case 0x1c:
                   // discriminator value 0x1cL=0x1cL for class OFBsnHybridGetReplyVer10
                   return OFBsnHybridGetReplyVer10.READER.readFrom(bb);
               case 0x1b:
                   // discriminator value 0x1bL=0x1bL for class OFBsnHybridGetRequestVer10
                   return OFBsnHybridGetRequestVer10.READER.readFrom(bb);
               case 0x22:
                   // discriminator value 0x22L=0x22L for class OFBsnPduRxReplyVer10
                   return OFBsnPduRxReplyVer10.READER.readFrom(bb);
               case 0x21:
                   // discriminator value 0x21L=0x21L for class OFBsnPduRxRequestVer10
                   return OFBsnPduRxRequestVer10.READER.readFrom(bb);
               case 0x23:
                   // discriminator value 0x23L=0x23L for class OFBsnPduRxTimeoutVer10
                   return OFBsnPduRxTimeoutVer10.READER.readFrom(bb);
               case 0x20:
                   // discriminator value 0x20L=0x20L for class OFBsnPduTxReplyVer10
                   return OFBsnPduTxReplyVer10.READER.readFrom(bb);
               case 0x1f:
                   // discriminator value 0x1fL=0x1fL for class OFBsnPduTxRequestVer10
                   return OFBsnPduTxRequestVer10.READER.readFrom(bb);
               case 0x0:
                   // discriminator value 0x0L=0x0L for class OFBsnSetIpMaskVer10
                   return OFBsnSetIpMaskVer10.READER.readFrom(bb);
               case 0x18:
                   // discriminator value 0x18L=0x18L for class OFBsnSetL2TableReplyVer10
                   return OFBsnSetL2TableReplyVer10.READER.readFrom(bb);
               case 0xc:
                   // discriminator value 0xcL=0xcL for class OFBsnSetL2TableRequestVer10
                   return OFBsnSetL2TableRequestVer10.READER.readFrom(bb);
               case 0x3:
                   // discriminator value 0x3L=0x3L for class OFBsnSetMirroringVer10
                   return OFBsnSetMirroringVer10.READER.readFrom(bb);
               case 0x19:
                   // discriminator value 0x19L=0x19L for class OFBsnSetPktinSuppressionReplyVer10
                   return OFBsnSetPktinSuppressionReplyVer10.READER.readFrom(bb);
               case 0xb:
                   // discriminator value 0xbL=0xbL for class OFBsnSetPktinSuppressionRequestVer10
                   return OFBsnSetPktinSuppressionRequestVer10.READER.readFrom(bb);
               case 0x6:
                   // discriminator value 0x6L=0x6L for class OFBsnShellCommandVer10
                   return OFBsnShellCommandVer10.READER.readFrom(bb);
               case 0x7:
                   // discriminator value 0x7L=0x7L for class OFBsnShellOutputVer10
                   return OFBsnShellOutputVer10.READER.readFrom(bb);
               case 0x8:
                   // discriminator value 0x8L=0x8L for class OFBsnShellStatusVer10
                   return OFBsnShellStatusVer10.READER.readFrom(bb);
               case 0x10:
                   // discriminator value 0x10L=0x10L for class OFBsnVirtualPortCreateReplyVer10
                   return OFBsnVirtualPortCreateReplyVer10.READER.readFrom(bb);
               case 0xf:
                   // discriminator value 0xfL=0xfL for class OFBsnVirtualPortCreateRequestVer10
                   return OFBsnVirtualPortCreateRequestVer10.READER.readFrom(bb);
               case 0x1a:
                   // discriminator value 0x1aL=0x1aL for class OFBsnVirtualPortRemoveReplyVer10
                   return OFBsnVirtualPortRemoveReplyVer10.READER.readFrom(bb);
               case 0x11:
                   // discriminator value 0x11L=0x11L for class OFBsnVirtualPortRemoveRequestVer10
                   return OFBsnVirtualPortRemoveRequestVer10.READER.readFrom(bb);
               default:
                   throw new OFParseError("Unknown value for discriminator subtype of class OFBsnHeaderVer10: " + subtype);
            }
        }
    }
}
