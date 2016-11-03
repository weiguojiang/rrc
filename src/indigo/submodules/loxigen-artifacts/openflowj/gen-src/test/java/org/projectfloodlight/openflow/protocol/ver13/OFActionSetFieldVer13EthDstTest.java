// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template unit_test.java
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
import static org.junit.Assert.*;
import java.util.Set;
import org.junit.Test;
import org.junit.Before;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import org.hamcrest.CoreMatchers;



public class OFActionSetFieldVer13EthDstTest {
    OFActions factory;

    final static byte[] ACTION_SET_FIELD_SERIALIZED =
        new byte[] { 0x0, 0x19, 0x0, 0x10, (byte) 0x80, 0x0, 0x6, 0x6, 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x0, 0x0 };

    @Before
    public void setup() {
        factory = OFActionsVer13.INSTANCE;
    }

    @Test
    public void testWrite() {
        OFActionSetField.Builder builder = factory.buildSetField();
        OFOxms oxms = OFFactories.getFactory(OFVersion.OF_13).oxms();
builder.setField(oxms.ethDst(MacAddress.of("00:01:02:03:04:05")));
        OFActionSetField actionSetField = builder.build();
        ByteBuf bb = Unpooled.buffer();
        actionSetField.writeTo(bb);
        byte[] written = new byte[bb.readableBytes()];
        bb.readBytes(written);

        assertThat(written, CoreMatchers.equalTo(ACTION_SET_FIELD_SERIALIZED));
    }

    @Test
    public void testRead() throws Exception {
        OFActionSetField.Builder builder = factory.buildSetField();
        OFOxms oxms = OFFactories.getFactory(OFVersion.OF_13).oxms();
builder.setField(oxms.ethDst(MacAddress.of("00:01:02:03:04:05")));
        OFActionSetField actionSetFieldBuilt = builder.build();

        ByteBuf input = Unpooled.copiedBuffer(ACTION_SET_FIELD_SERIALIZED);

        // FIXME should invoke the overall reader once implemented
        OFActionSetField actionSetFieldRead = OFActionSetFieldVer13.READER.readFrom(input);
        assertEquals(ACTION_SET_FIELD_SERIALIZED.length, input.readerIndex());

        assertEquals(actionSetFieldBuilt, actionSetFieldRead);
   }

   @Test
   public void testReadWrite() throws Exception {
       ByteBuf input = Unpooled.copiedBuffer(ACTION_SET_FIELD_SERIALIZED);

       // FIXME should invoke the overall reader once implemented
       OFActionSetField actionSetField = OFActionSetFieldVer13.READER.readFrom(input);
       assertEquals(ACTION_SET_FIELD_SERIALIZED.length, input.readerIndex());

       // write message again
       ByteBuf bb = Unpooled.buffer();
       actionSetField.writeTo(bb);
       byte[] written = new byte[bb.readableBytes()];
       bb.readBytes(written);

       assertThat(written, CoreMatchers.equalTo(ACTION_SET_FIELD_SERIALIZED));
   }

}
