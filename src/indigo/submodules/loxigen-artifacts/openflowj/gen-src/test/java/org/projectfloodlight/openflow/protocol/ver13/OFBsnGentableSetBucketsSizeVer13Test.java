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



public class OFBsnGentableSetBucketsSizeVer13Test {
    OFFactory factory;

    final static byte[] BSN_GENTABLE_SET_BUCKETS_SIZE_SERIALIZED =
        new byte[] { 0x4, 0x4, 0x0, 0x18, 0x12, 0x34, 0x56, 0x78, 0x0, 0x5c, 0x16, (byte) 0xc7, 0x0, 0x0, 0x0, 0x32, 0x0, 0x14, 0x0, 0x0, 0x0, 0x11, 0x22, 0x33 };

    @Before
    public void setup() {
        factory = OFFactoryVer13.INSTANCE;
    }

   // FIXME: No java stanza in test_data for this class. Add for more comprehensive unit testing

   @Test
   public void testReadWrite() throws Exception {
       ByteBuf input = Unpooled.copiedBuffer(BSN_GENTABLE_SET_BUCKETS_SIZE_SERIALIZED);

       // FIXME should invoke the overall reader once implemented
       OFBsnGentableSetBucketsSize bsnGentableSetBucketsSize = OFBsnGentableSetBucketsSizeVer13.READER.readFrom(input);
       assertEquals(BSN_GENTABLE_SET_BUCKETS_SIZE_SERIALIZED.length, input.readerIndex());

       // write message again
       ByteBuf bb = Unpooled.buffer();
       bsnGentableSetBucketsSize.writeTo(bb);
       byte[] written = new byte[bb.readableBytes()];
       bb.readBytes(written);

       assertThat(written, CoreMatchers.equalTo(BSN_GENTABLE_SET_BUCKETS_SIZE_SERIALIZED));
   }

}
