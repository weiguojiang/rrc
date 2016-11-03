// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_factory_class.java
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


public class OFMeterBandsVer12 implements OFMeterBands {
    public final static OFMeterBandsVer12 INSTANCE = new OFMeterBandsVer12();




    public OFMeterBandDrop.Builder buildDrop() {
        throw new UnsupportedOperationException("OFMeterBandDrop not supported in version 1.2");
    }
    public OFMeterBandDrop drop(long rate, long burstSize) {
        throw new UnsupportedOperationException("OFMeterBandDrop not supported in version 1.2");
    }

    public OFMeterBandDscpRemark.Builder buildDscpRemark() {
        throw new UnsupportedOperationException("OFMeterBandDscpRemark not supported in version 1.2");
    }

    public OFMeterBandExperimenter.Builder buildExperimenter() {
        throw new UnsupportedOperationException("OFMeterBandExperimenter not supported in version 1.2");
    }

    public OFMessageReader<OFMeterBand> getReader() {
        throw new UnsupportedOperationException("Reader<OFMeterBand> not supported in version 1.2");
    }


    public OFVersion getVersion() {
            return OFVersion.OF_12;
    }
}
