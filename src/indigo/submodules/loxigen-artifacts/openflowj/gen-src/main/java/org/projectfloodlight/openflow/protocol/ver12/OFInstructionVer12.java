// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_virtual_class.java
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
import io.netty.buffer.ByteBuf;

abstract class OFInstructionVer12 {
    // version: 1.2
    final static byte WIRE_VERSION = 3;
    final static int MINIMUM_LENGTH = 8;


    public final static OFInstructionVer12.Reader READER = new Reader();

    static class Reader implements OFMessageReader<OFInstruction> {
        @Override
        public OFInstruction readFrom(ByteBuf bb) throws OFParseError {
            if(bb.readableBytes() < MINIMUM_LENGTH)
                return null;
            int start = bb.readerIndex();
            short type = bb.readShort();
            bb.readerIndex(start);
            switch(type) {
               case (short) 0x4:
                   // discriminator value OFInstructionType.APPLY_ACTIONS=4 for class OFInstructionApplyActionsVer12
                   return OFInstructionApplyActionsVer12.READER.readFrom(bb);
               case (short) 0x5:
                   // discriminator value OFInstructionType.CLEAR_ACTIONS=5 for class OFInstructionClearActionsVer12
                   return OFInstructionClearActionsVer12.READER.readFrom(bb);
               case (short) 0xffff:
                   // discriminator value OFInstructionType.EXPERIMENTER=65535 for class OFInstructionExperimenterVer12
                   return OFInstructionExperimenterVer12.READER.readFrom(bb);
               case (short) 0x1:
                   // discriminator value OFInstructionType.GOTO_TABLE=1 for class OFInstructionGotoTableVer12
                   return OFInstructionGotoTableVer12.READER.readFrom(bb);
               case (short) 0x3:
                   // discriminator value OFInstructionType.WRITE_ACTIONS=3 for class OFInstructionWriteActionsVer12
                   return OFInstructionWriteActionsVer12.READER.readFrom(bb);
               case (short) 0x2:
                   // discriminator value OFInstructionType.WRITE_METADATA=2 for class OFInstructionWriteMetadataVer12
                   return OFInstructionWriteMetadataVer12.READER.readFrom(bb);
               default:
                   throw new OFParseError("Unknown value for discriminator type of class OFInstructionVer12: " + type);
            }
        }
    }
}
