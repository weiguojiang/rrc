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
import org.junit.Test;
import org.junit.Before;
import java.util.List;
import com.google.common.collect.ImmutableList;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import org.hamcrest.CoreMatchers;



public class OFBsnGentableEntryAddVer13Test {
    OFFactory factory;

    final static byte[] BSN_GENTABLE_ENTRY_ADD_SERIALIZED =
        new byte[] { 0x4, 0x4, 0x0, 0x48, 0x12, 0x34, 0x56, 0x78, 0x0, 0x5c, 0x16, (byte) 0xc7, 0x0, 0x0, 0x0, 0x2e, 0x0, 0x14, 0x0, 0x12, (byte) 0xfe, (byte) 0xdc, (byte) 0xba, (byte) 0x98, 0x76, 0x54, 0x32, 0x10, (byte) 0xff, (byte) 0xee, (byte) 0xcc, (byte) 0xbb, (byte) 0xaa, (byte) 0x99, (byte) 0x88, 0x77, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x5, 0x0, 0x1, 0x0, 0xa, 0x1, 0x23, 0x45, 0x67, (byte) 0x89, (byte) 0xab, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x6, 0x0, 0x1, 0x0, 0xa, (byte) 0xff, (byte) 0xee, (byte) 0xdd, (byte) 0xcc, (byte) 0xbb, (byte) 0xaa };

    @Before
    public void setup() {
        factory = OFFactoryVer13.INSTANCE;
    }

    @Test
    public void testWrite() {
        OFBsnGentableEntryAdd.Builder builder = factory.buildBsnGentableEntryAdd();
        builder.setXid(0x12345678)
    .setChecksum(U128.of(0xFEDCBA9876543210L, 0xFFEECCBBAA998877L))
    .setTableId(GenTableId.of(20))
    .setKey(
        ImmutableList.<OFBsnTlv>of(
            factory.bsnTlvs().port(OFPort.of(5)),
            factory.bsnTlvs().mac(MacAddress.of("01:23:45:67:89:ab"))
        )
    )
    .setValue(
        ImmutableList.<OFBsnTlv>of(
            factory.bsnTlvs().port(OFPort.of(6)),
            factory.bsnTlvs().mac(MacAddress.of("ff:ee:dd:cc:bb:aa"))
        )
    );
        OFBsnGentableEntryAdd bsnGentableEntryAdd = builder.build();
        ByteBuf bb = Unpooled.buffer();
        bsnGentableEntryAdd.writeTo(bb);
        byte[] written = new byte[bb.readableBytes()];
        bb.readBytes(written);

        assertThat(written, CoreMatchers.equalTo(BSN_GENTABLE_ENTRY_ADD_SERIALIZED));
    }

    @Test
    public void testRead() throws Exception {
        OFBsnGentableEntryAdd.Builder builder = factory.buildBsnGentableEntryAdd();
        builder.setXid(0x12345678)
    .setChecksum(U128.of(0xFEDCBA9876543210L, 0xFFEECCBBAA998877L))
    .setTableId(GenTableId.of(20))
    .setKey(
        ImmutableList.<OFBsnTlv>of(
            factory.bsnTlvs().port(OFPort.of(5)),
            factory.bsnTlvs().mac(MacAddress.of("01:23:45:67:89:ab"))
        )
    )
    .setValue(
        ImmutableList.<OFBsnTlv>of(
            factory.bsnTlvs().port(OFPort.of(6)),
            factory.bsnTlvs().mac(MacAddress.of("ff:ee:dd:cc:bb:aa"))
        )
    );
        OFBsnGentableEntryAdd bsnGentableEntryAddBuilt = builder.build();

        ByteBuf input = Unpooled.copiedBuffer(BSN_GENTABLE_ENTRY_ADD_SERIALIZED);

        // FIXME should invoke the overall reader once implemented
        OFBsnGentableEntryAdd bsnGentableEntryAddRead = OFBsnGentableEntryAddVer13.READER.readFrom(input);
        assertEquals(BSN_GENTABLE_ENTRY_ADD_SERIALIZED.length, input.readerIndex());

        assertEquals(bsnGentableEntryAddBuilt, bsnGentableEntryAddRead);
   }

   @Test
   public void testReadWrite() throws Exception {
       ByteBuf input = Unpooled.copiedBuffer(BSN_GENTABLE_ENTRY_ADD_SERIALIZED);

       // FIXME should invoke the overall reader once implemented
       OFBsnGentableEntryAdd bsnGentableEntryAdd = OFBsnGentableEntryAddVer13.READER.readFrom(input);
       assertEquals(BSN_GENTABLE_ENTRY_ADD_SERIALIZED.length, input.readerIndex());

       // write message again
       ByteBuf bb = Unpooled.buffer();
       bsnGentableEntryAdd.writeTo(bb);
       byte[] written = new byte[bb.readableBytes()];
       bb.readBytes(written);

       assertThat(written, CoreMatchers.equalTo(BSN_GENTABLE_ENTRY_ADD_SERIALIZED));
   }

}
