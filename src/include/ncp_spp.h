/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL      *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **
 **************************************************************************/
/*! @file        ncp_spp.h
    @brief       Security Protocol Processor (spp)

    @detail      APIs and data structures for public access to SPP module.
                 The definitions and APIs in this module are organized
                 by the following sub-components:
    <ul>
     <li> Shared Definitions </li>
     <li> IPSec Context      </li>
     <li> 3GPP Context       </li>
     <li> TLS/SSL Context    </li>
     <li> SRTP Context       </li>
     <li> Generic Context    </li>
     <li> Alg Acc Context    </li>
     <li> Firmware           </li>
    </ul>
*/

#ifndef ncp_spp_h
#define ncp_spp_h

#include "ncp_types.h"

#ifndef NCP_KERNEL
#include "ncp_pka.h"
#include "ncp_trng.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*! 
 * @defgroup _spp_ Security Protocol Processor
 * @brief    Security Protocol Processor (spp)
 * @{
 */

/****************************************************************************
**    SHARED DEFINITIONS
****************************************************************************/

/*!
 * @brief Specifies the list of anti-replay wnidow 
 * sizes supported by the SPP. They are
 * 64, 128, 256, 512, 1024.
 */
typedef enum ncp_spp_arw_size_e {
    NCP_SPP_ARW_MIN  = 64,
    NCP_SPP_ARW_64   = 64,
    NCP_SPP_ARW_128  = 128,
    NCP_SPP_ARW_256  = 256,
    NCP_SPP_ARW_512  = 512,
    NCP_SPP_ARW_1024 = 1024,
    NCP_SPP_ARW_2048 = 2048,
    NCP_SPP_ARW_MAX  = 2048
} ncp_spp_arw_size_t;

/*!
 * @brief Tells whether the given context should be used for
 * inbound or outbound processing. 
 *
 * The outbound processing normally encrypts the packet and calculates
 * the Message Authentication Code (MAC), while the inbound processing
 * decrypts the packet and checks the MAC to verify message integrity.
 */
typedef enum ncp_spp_direction_e {
    NCP_SPP_OUTBOUND,
    NCP_SPP_INBOUND
} ncp_spp_direction_t;


/*!
 * @brief Cuts off any traffic going through this context.
 * 
 * This API reverts the effects of any <b>_context_set</b>
 * API by writing zeros into the first 16 bytes of the context
 * record. From that point on, any traffic sent to this context 
 * will be dropped: the same effect as sending the traffic to a
 * context that has never been set.
 * <p>
 * NOTE: This API (just like all other SPP APIs) does
 * not perform any ID management, i.e. it does not mark 
 * the given ID as available to be re-used: 
 * it is the caller's responsibility to do so.
 *
 * @param id A 24-bit ID of the context entry to invalidate
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_SPP_NOT_CONFIGURED
 *      \li ::NCP_ST_NS_NO_NAMESPACES_DEFINED
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li Low level device access error codes
 *       
 */
NCP_API ncp_st_t
ncp_spp_context_invalidate(ncp_hdl_t ncpHdl, 
                           ncp_uint32_t id);

/*!
 * @brief The structure is used for retrieving the counters
 * (maintained by the hardware) via ncp_spp_counters_get() 
 * API call. 
 *
 * For every protocol, the SPP maintains two 64-bit
 * counters, but their interpretation is different for
 * each protocol. The structure defines the field names
 * according to the per-protocol interpretation.
 * <p>
 * Note, the "down-counter" means that the counter is being 
 * initialized with some large value and the SPP Hardware
 * is actually decrementing it. This is done for the protocols
 * that supports packet or byte lifetimes, so the same field
 * can be used both as lifetime and statistics counter.
 */
typedef union ncp_spp_counters_u {
    struct {
        ncp_uint64_t count0;
        ncp_uint64_t count1;
    } generic;
    struct {
        ncp_uint64_t softByteDownCount;
        ncp_uint64_t hardByteDownCount;
    } ipsec;
    struct {
        ncp_uint64_t byteCount;
        ncp_uint64_t packetCount;
    } w3gpp;
    struct {
        ncp_uint64_t byteCount;
        ncp_uint64_t packetCount;
    } tls;
    struct {
        ncp_uint64_t byteCount;
        ncp_uint64_t packetDownCount;
    } srtp;
} ncp_spp_counters_t;


/*!
 * @brief Read the values of the counters, maintained 
 *        by the hardware, from the SPP Context.
 *
 * NOTE: This API must only be called for the context that
 * includes the counters. Otherwise, it may return an error
 * code or retreive invalid data (it is not always possible to
 * detect this error). Whether the context includes the
 * counter is defined on a per-protocol basis:
 * <ul>
 *   <li> IPSec/SRTP: always included </li>
 *   <li> 3GPP/TLS: determined by the value
 *          of "countersPresent" field </li>
 *   <li> Generic Context: determined by the 
 *         value of "countersPresent" field </li>
 * </ul>
 *
 * @param contextId A 24-bit ID of the context entry to get the counters from
 * @param coherentRead Tells whether to perform the coherent read
 *   of the System Memory, or the regular one. It should be 
 *   <b>false</b> for most of the use cases and only need to be set
 *   to true when a really up-to-date counter is needed, or the
 *   SPP L1 cache is configured not to perform periodic write-backs.
 *
 * @param outCounters The resulting counters will be written into
 *                    this structure. It can then be interpreted
 *                    according to the protocol.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_SPP_NOT_CONFIGURED
 *      \li ::NCP_ST_NS_NO_NAMESPACES_DEFINED
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_SPP_CTX_INVALID
 *      \li ::NCP_ST_SPP_CTX_COUNTERS_MISSING
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_context_counters_get(ncp_hdl_t           ncpHdl,
                             ncp_uint32_t        contextId,
                             ncp_bool_t          coherentRead,
                             ncp_spp_counters_t *outCounters);

/*! \defgroup contextSetErrorCodes Error Codes for Context Set APIs
 * 
 * The following specifies the error codes that can be returned
 * by the "context_set" APIs. Not all these codes are
 * applicable to every API.
 *
 *   \li ::NCP_ST_INVALID_HANDLE
 *   \li ::NCP_ST_SPP_NOT_CONFIGURED
 *   \li ::NCP_ST_INVALID_PARAMETER
 *   \li ::NCP_ST_NO_MEMORY
 *   \li ::NCP_ST_NS_NO_NAMESPACES_DEFINED
 *   \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *
 *   \li All the error codes that start with <b>NCP_ST_SPP_CTX_</b> 
 *       prefix. See the list in ncp_status.h starting from
 *       ::NCP_ST_SPP_NOT_CONFIGURED  onward.
 *   \li Low level device access error codes
 */

/*! \defgroup contextSizeDescription Overview & Error Codes for Context Size APIs
 * 
 * The _context_size APIs for various protocols can be used
 * to determine the how large a hardware context entry
 * is going to be. They can be used to:
 * <ol>
 * <li> Make sure the context is going to fit into a given entry,
 *      to avoid getting ::NCP_ST_SPP_CTX_TOO_BIG error 
 *      from a _context_set API. </li>
 * 
 * <li> Select a namespace (assuming we have several options)
 *      with sufficiently large entry for a given context </li>
 * </ol>
 *
 * For the second option, the application code should
 * proceed as follows:
 * <ul>
 * <li> At the configuration time, define several 
 *      Namespaces that have different "entrySize" values
 *      for the SPPSecurityContexts element. 
 * 
 * <li> Determine the context parameters and fill
 *      in all the fields in the "_context_t"
 *      structure, except for the <b>id</b> field. 
 *
 * <li> Call the "_context_size" API with that structure
 *      to determine the minimum entry size needed.
 *
 * <li> Look through Namespaces defined in the first
 *      step and find the one with the smallest entry that
 *      can fit our context.
 *
 * <li> Use the Resource Manager to allocate an ID from 
 *      that Namespace.
 *
 * <li> Write that ID into "_context_t" structure and
 *      call the "_context_set" API.
 * </ul>
 * <p>
 * <b> Return Codes for _context_size APIs. </b> <br>
 * NOTE: Not all these codes are applicable to every API.
 *
 *   \li ::NCP_ST_INVALID_HANDLE
 *   \li ::NCP_ST_INVALID_PARAMETER
 *   \li ::NCP_ST_SPP_NOT_CONFIGURED
 *   \li ::NCP_ST_SPP_CTX_PROTO_INVALID
 *   \li ::NCP_ST_SPP_CTX_AUTH_INVALID
 *   \li ::NCP_ST_SPP_CTX_AUTH_KEY_LEN_INVALID
 *   \li ::NCP_ST_SPP_CTX_ENCR_INVALID
 *   \li ::NCP_ST_SPP_CTX_ENCR_KEY_LEN_INVALID
 *   \li ::NCP_ST_SPP_CTX_ARW_SIZE_INVALID
 *   \li ::NCP_ST_SPP_CTX_IV_INVALID (generic context only)
 *   \li ::NCP_ST_SPP_CTX_CIPHER_STATE_INVALID (generic context only)
 */


/****************************************************************************
**    IPSec CONTEXT
****************************************************************************/

/*!
 * @brief IPSec Encryption algorithms; the enum values are
 *        assigned to match the IKEv2. 
 *
 * See RFC 4306 and also: <br>
 * http://www.iana.org/assignments/ikev2-parameters
 */
typedef enum ncp_spp_ipsec_encr_e {
    NCP_SPP_IPSEC_ENCR_DES_CBC       = 2,  /* 64-bit key */
    NCP_SPP_IPSEC_ENCR_3DES_CBC      = 3,
    NCP_SPP_IPSEC_ENCR_NULL          = 11,
    NCP_SPP_IPSEC_ENCR_AES_CBC       = 12,
    NCP_SPP_IPSEC_ENCR_AES_CTR       = 13,
    NCP_SPP_IPSEC_ENCR_AES_CCM_ICV8  = 14,
    NCP_SPP_IPSEC_ENCR_AES_CCM_ICV12 = 15,
    NCP_SPP_IPSEC_ENCR_AES_CCM_ICV16 = 16,
    NCP_SPP_IPSEC_ENCR_AES_GCM_ICV8  = 18,
    NCP_SPP_IPSEC_ENCR_AES_GCM_ICV12 = 19,
    NCP_SPP_IPSEC_ENCR_AES_GCM_ICV16 = 20,
    NCP_SPP_IPSEC_ENCR_NULL_GMAC     = 21,
    NCP_SPP_IPSEC_ENCR_MAX
} ncp_spp_ipsec_encr_t;


/*!
 * @brief IPSec Authentication/Integrity algorithms; the enum 
 *        values are assigned to match the IKE2 (see above).
 *
 * See RFC 4306 and also: <br>
 * http://www.iana.org/assignments/ikev2-parameters
 */
typedef enum ncp_spp_ipsec_auth_e {
    NCP_SPP_IPSEC_AUTH_NULL          = 0,
    NCP_SPP_IPSEC_AUTH_HMAC_MD5      = 1,  /* 128-bit key, 96-bit ICV */
    NCP_SPP_IPSEC_AUTH_HMAC_SHA1     = 2,  /* 160-bit key, 96-bit ICV */
    NCP_SPP_IPSEC_AUTH_AES_XCBC_MAC  = 5,  /* 128-bit key, 96-bit ICV */
    NCP_SPP_IPSEC_AUTH_AES_CMAC      = 8,  /* 128-bit key, 96-bit ICV */
    NCP_SPP_IPSEC_AUTH_AES_128_GMAC  = 9,  /* 128-bit ICV for ALL GMACs*/
    /* NOTE: The HW does NOT support AES-192-GCM or AES-192-GMAC */
    NCP_SPP_IPSEC_AUTH_AES_256_GMAC  = 11,
    NCP_SPP_IPSEC_AUTH_HMAC_SHA_256  = 12, /* 128-bit ICV */
    NCP_SPP_IPSEC_AUTH_HMAC_SHA_384  = 13, /* 192-bit ICV */
    NCP_SPP_IPSEC_AUTH_HMAC_SHA_512  = 14, /* 256-bit ICV */
    /* NCP_SPP_IPSEC_AUTH_HMAC_SHA2_224,            , ??-bit ICV */
    NCP_SPP_IPSEC_AUTH_MAX
} ncp_spp_ipsec_auth_t;


typedef enum ncp_spp_ipsec_mode_e {
    NCP_SPP_IPSEC_TUNNEL,
    NCP_SPP_IPSEC_TRANSPORT
} ncp_spp_ipsec_mode_t;


typedef enum ncp_spp_ipsec_protocol_e {
    NCP_SPP_IPSEC_AH   = 2,
    NCP_SPP_IPSEC_ESP  = 3
} ncp_spp_ipsec_protocol_t;

/*!
 * @struct ncp_spp_ipsec_context_t
 * @brief Data structure that contains the fields needed
 *        to create a Security Context for IPSec
 *        protocols (ESP or AH).
 */
typedef struct ncp_spp_ipsec_context_s {

    /*!
     * If "lifetimesEnabled" is true, this value gives a soft 
     * SA lifetime (in bytes) as defined by the RFC4301. 
     * Once the Soft Lifetime expires, the SPP will set a flag 
     * in the Output parameters telling the downstream engine to 
     * trigger the auto-negotiation. If "lifetimesEnabled" is false, 
     * this is a simple byte down-counter that can be used for statistics.
     */
    ncp_uint64_t             softByteLifetime;

    /*!
     * If "lifetimesEnabled" is true, this value gives a hard SA 
     * lifetime (in bytes) as defined by RFC4301. Once the Hard Lifetime
     * expires, no packets for that SA will be processed by the SPP. 
     * If "lifetimesEnabled" is false, this is a simple byte 
     * down-counter that can be used for statistics.
     */
    ncp_uint64_t             hardByteLifetime;
    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t             id;
    ncp_spp_direction_t      direction;
    /*!
     * @brief Selects Tunnel or Transport Mode.
     */
    ncp_spp_ipsec_mode_t     mode;
    /*!
     * @brief Selects ESP or AH protocol.
     */   
    ncp_spp_ipsec_protocol_t protocol;

    ncp_spp_ipsec_encr_t     encr;
    ncp_byte_string_t        encrKey;
    /*!
     * @brief NONCE or SALT value for some algorithms.
     *
     * This value is used to specify NONCE value for 
     * AES_CTR encryption algorithm (see RFC3686) or SALT value 
     * for AES_GCM_XXX encryption and AES_XXX_GMAC authentication 
     * algorithms (see RFC4106 and RFC4543). 
     * Otherwise, the value must be empty.
     */
    ncp_byte_string_t        salt;
    ncp_spp_ipsec_auth_t     auth;
    ncp_byte_string_t        authKey;

    /*!
     * Security Parameters Index (SPI) (as defined by RFC4301).
     * It is to be inserted into the packet for OUTBOUND processing. 
     * The value is ignored for the INBOUND.
     */
    ncp_uint32_t             spi;

    /*! 
     * @brief Specifies whether the context uses 64-bit extended 
     * sequence number or 32-bit sequence numbers (see RFC4302/4303).
     */
    ncp_bool_t               extSeqNum;
    union {
        /*!
         * @brief Applies only to INBOUND Context. 
         *        Enables the anti-replay checking by the SPP. 
         *
         * It must be set to true if "extSeqNum" is true
         */
        ncp_bool_t           antiReplayEnable;
        /*!
         * @brief Applies only to OUTBOUND. Specifies whether a 
         *        Sequence Number counter is allowed to rollover. 
         *
         * It must be set to false if "extSeqNum" is true.
         */
        ncp_bool_t           seqRollover;
    } sn;
    
    /*!
     * @brief Specifies whether the SPP needs to check for
     * Soft/Hard byte lifetime expiration. 
     *
     * If false, these lifetimes work as simple decrementing counters.
     */
    ncp_bool_t               lifetimesEnabled;
    /**
     * This value is used ONLY for the Inbound and ONLY
     * when anti-replay is enabled. The SPP only supports
     * ARW sizes specified by the enum values.
     */
    ncp_spp_arw_size_t       antiReplayWindowSize;
} ncp_spp_ipsec_context_t;


/*!
 * @gn ncp_st_t ncp_spp_ipsec_context_set(ncp_hdl_t ncpHdl, ncp_spp_ipsec_context_t *ctx);
 * @brief Create an IPSec context.
 *
 * RESTRICTIONS:
 * <ul>
 *  <li> For ESP, it is not allowed to set both 
 *       encryption and authentication to NULL </li>
 *  <li> For AH, it is not allowed to set authentication to NULL</li>
 * </ul>
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_ipsec_context_set(ncp_hdl_t ncpHdl, 
                          ncp_spp_ipsec_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_ipsec_context_get(ncp_hdl_t ncpHdl, ncp_spp_ipsec_context_t *ctx);
 * @brief Retrieve the settings of a current IPSec context.
 *
 * Populate the context structure fields with values from a current IPSec
 * context.  The <b>id</b> field of the structure needs to be assigned with
 * the ID for the context whose values are to be retrieved.
 * <p>
 * If the buf pointer values for <b>encrKey</b>, <b>authKey</b> and
 * <b>salt</b> are not NULL, and the len value indicates that the buffer
 * is large enough to fit the byte string, the buffer will be populated
 * with the corresponding values from the context structure, if they exist
 * for the specified context ID.  The <b>authKey</b> and  <b>encrKey</b>
 * values will not be available for authentication and encryption algorithms
 * that use precomputes (HMAC, AES_CMAC, AES_XCBC, AES_CBC).  The len value
 * for these fields will be updated with the number of bytes that the API
 * copied into the buffer.  If nothing is copied into the buffer, the API
 * will set the len field for the respective buffer to zero.
 * <p>
 * Note that for the AH protocol, the encryption will always be NULL for
 * contexts that use non-GMAC authentication and will always be NULL_GMAC
 * for contexts that use GMAC authentication.
 * <p>
 * The PROTO_INVALID error code indicates that the id represents a
 * valid SPP context, but it is not an IPSec context.  The ENCR and AUTH invalid
 * error codes indicate that the context has been corrupted.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_SPP_NOT_CONFIGURED
 *      \li ::NCP_ST_NS_NO_NAMESPACES_DEFINED
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_SPP_CTX_DISABLED
 *      \li ::NCP_ST_SPP_CTX_PROTO_INVALID
 *      \li ::NCP_ST_SPP_CTX_ENCR_INVALID
 *      \li ::NCP_ST_SPP_CTX_AUTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_ipsec_context_get(ncp_hdl_t ncpHdl, 
                          ncp_spp_ipsec_context_t *ctx);


/*!
 * @fn ncp_st_t ncp_spp_ipsec_context_size(ncp_spp_ipsec_context_t *context, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create this context.
 *
 * See \link contextSizeDescription this description \endlink for more details.
 */
NCP_API ncp_st_t
ncp_spp_ipsec_context_size(ncp_spp_ipsec_context_t *context,
                           ncp_uint32_t *outSize);

/****************************************************************************
**    3GPP CONTEXT
****************************************************************************/

/*!
 * @brief Defines protocols supported by 3GPP SPP APIs.
 */
typedef enum ncp_spp_3gpp_protocol_e {
    NCP_SPP_3GPP_RLC,
    NCP_SPP_3GPP_MACd,
    NCP_SPP_3GPP_RRC,
    NCP_SPP_3GPP_RRC_UE,
    NCP_SPP_3GPP_PDCP_TX,
    NCP_SPP_3GPP_PDCP_RX,
    NCP_SPP_3GPP_GSM,
    NCP_SPP_3GPP_PROTO_MAX
} ncp_spp_3gpp_protocol_t;


/*!
 * @brief Defines encryption algorithms supported
 * by 3GPP SPP APIs.
 */
typedef enum ncp_spp_3gpp_encr_e {
    NCP_SPP_3GPP_ENCR_NULL,
    NCP_SPP_3GPP_ENCR_KASUMI_F8,
    NCP_SPP_3GPP_ENCR_SNOW_3G_F8,
    NCP_SPP_3GPP_ENCR_AES_CTR,
    NCP_SPP_3GPP_ENCR_ZUC_F8,
    NCP_SPP_3GPP_ENCR_A5_1,
    NCP_SPP_3GPP_ENCR_A5_3,
    NCP_SPP_3GPP_ENCR_A5_4,
    NCP_SPP_3GPP_ENCR_A5_3_ECSD,
    NCP_SPP_3GPP_ENCR_A5_4_ECSD,
    NCP_SPP_3GPP_ENCR_MAX
} ncp_spp_3gpp_encr_t;


/*!
 * @brief Defines authentication algorithms
 *  supported by 3GPP SPP APIs.
 */
typedef enum ncp_spp_3gpp_auth_e {
    NCP_SPP_3GPP_AUTH_NULL,
    NCP_SPP_3GPP_AUTH_KASUMI_F9,
    NCP_SPP_3GPP_AUTH_SNOW_3G_F9,
    NCP_SPP_3GPP_AUTH_AES_CMAC,
    NCP_SPP_3GPP_AUTH_ZUC_F9,
    NCP_SPP_3GPP_AUTH_MAX
} ncp_spp_3gpp_auth_t;


/*!
 * @brief Data structure that defines all the Security context 
 *        fields needed to support 3GPP SPP APIs.
 *
 * <h3>Programming the contexts for different protocols </h3>
 * One of the SPP task parameters is a "direction" bit that tells whether
 * the traffic is going in the uplink or downlink direction:
 * <ul>
 *   <li> <b>Downlink</b>, direction=1, sending the data from eNodeB to UE(Handset)</li>
 *   <li> <b>Uplink</b>, direction=0, sending the data from UE to eNodeB</li>
 * </ul>
 *
 * For <b>RLC</b> and <b>MACd</b> and <b>GSM<\b> protocols, the context is the same
 * for either direction, regardless of whether it's located in the
 * eNodeB or UE.
 *
 * For <b>RRC</b>, the \e protocol field should be programmed as \e RRC
 * when ACP is running in the RNC, and as \e RRC_UE when running from the 
 * UE(Handset). For either RNC or UE, only a single context is needed
 * to establish a bidirectional link.
 * <table>
 *   <tr> <th>ACP in RNC</th>       <th>       </th> <th>UE(Handset)</th>         </tr>
 *   <tr> <td>RRC, direction=1</td> <td>---&gt;</td> <td>RRC_UE, direction=1</td> </tr>
 *   <tr> <td>RRC, direction=0</td> <td>&lt;---</td> <td>RRC_UE, direction=0</td> </tr>
 * </table>
 *
 * For <b>PDCP</b> protocol, different contexts must be created for transmitting
 * and receiving packets. Overall, 2 contexts for eNodeB and 2 contexts for UE are needed.
 * <table>
 *   <tr> <th>ACP in eNodeB</th>    <th>       </th> <th>UE(Handset)</th>              </tr>
 *   <tr> <td>PDCP_TX, direction=1</td> <td>---&gt;</td> <td>PDCP_RX, direction=1</td> </tr>
 *   <tr> <td>PDCP_RX, direction=0</td> <td>&lt;---</td> <td>PDCP_TX, direction=0</td> </tr>
 * </table>
 */
typedef struct ncp_spp_3gpp_context_s {
    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t                    id;
    /*!
     * @brief Specifies what Wireless protocol the given
     * Context is being created for.
     */
    ncp_spp_3gpp_protocol_t         protocol;
    /*!
     * @brief Specified Confidentiality (encryption) algorithm.
     */
    ncp_spp_3gpp_encr_t             encr; 
    ncp_byte_string_t               encrKey;
    /*!
     * @brief The 4-byte "fresh" value needed by the RRC protocol.
     *
     * It shall be empty for all the other protocols
     * or in the PDU Mode.
     */
    ncp_byte_string_t               fresh;
    /*!
     * @brief Specified Integrity (authentication) algorithm.
     */
    ncp_spp_3gpp_auth_t             auth;
    ncp_byte_string_t               authKey;
    /*!
     * @brief The PDU Mode is a special mode of operation, when
     * the keying information is supplied to the SPP by
     * prepending it to the PDU, as opposed to programming
     * it into the Context Record. 
     *
     * The following information must be supplied with the PDU:
     * <ul>
     *  <li> Encryption Key </li>
     *  <li> Authentication Key </li>
     *  <li> Fresh value (whenever needed) </li>
     *  <li> Radio Bearer value </li>
     * </ul>
     * Note, the statistics counters may still be present
     * in the Context Record, even in the PDU mode.
     * Please see the SPP section of the "Technical Guide"
     * for more details on how the key information should
     * be prepended to the PDU.
     */
    ncp_bool_t                      pduMode;
    /*!
     * @brief A 5-bit Radio Bearer value.
     */
    ncp_uint8_t                     radioBearer;
    /*!
     * @brief Indicates whether the SPP should maintain
     *        a byte count and packet count statistics
     *        as a part of the Context. 
     *
     * These statistics can be retrieved by calling
     * ncp_spp_context_counters_get() API.
     */
    ncp_bool_t                      countersPresent;
} ncp_spp_3gpp_context_t;


/*!
 * @fn ncp_st_t ncp_spp_3gpp_context_set(ncp_hdl_t ncpHdl, ncp_spp_3gpp_context_t *ctx);
 * @brief Create a 3GPP context.
 *
 * NOTE: The API does not place any restrictions on
 *       using NULL encryption or authentication algorithms.
 *
 * See the definition of the context structure for more
 * details on how to program the "protocol" field for 
 * different scenarions.
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_3gpp_context_set(ncp_hdl_t ncpHdl, 
                          ncp_spp_3gpp_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_3gpp_context_get(ncp_hdl_t ncpHdl, ncp_spp_3gpp_context_t *ctx);
 * @brief Retrieve the settings of a current 3GPP context.
 *
 * Populate the context structure fields with values from a current 3GPP
 * context.  The <b>id</b> field of the structure needs to be assigned with
 * the ID for the context whose values are to be retrieved.
 * <p>
 * If the buf pointer values for <b>encrKey</b>, <b>authKey</b> and
 * <b>fresh</b> are not NULL, and the len value indicates that the buffer
 * is large enough to fit the byte string, the buffer will be populated
 * with the corresponding values from the context structure, if they exist
 * for the specified context ID.  The <b>authKey</b> values will not be
 * available for authentication algorithms that use precomputes (AES_CMAC).
 * The len value for these fields will be updated with the number of bytes
 * that the API copied into the buffer.  If nothing is copied into the buffer,
 * the API will set the len field for the respective buffer to zero.
 * <p>
 * Note that the protocol field will be populated with the the RLC enumeration
 * value for contexts that were set with either RLC or MACd.  This is because
 * the SPP treats these two protocols identically.
 * <p>
 * The PROTO_INVALID error code indicates that the id represents a
 * valid SPP context, but it is not a 3GPP context.  The ENCR and AUTH
 * invalid error codes indicate that the context has been corrupted.
 *
 * @retval NCP_ST_SUCCESS
 * @retval NCP_ST_INVALID_HANDLE
 * @retval NCP_ST_SPP_NOT_CONFIGURED
 * @retval NCP_ST_NS_NO_NAMESPACES_DEFINED
 * @retval NCP_ST_NS_ENTRY_ID_INVALID
 * @retval NCP_ST_SPP_CTX_DISABLED
 * @retval NCP_ST_SPP_CTX_PROTO_INVALID
 * @retval NCP_ST_SPP_CTX_ENCR_INVALID
 * @retval NCP_ST_SPP_CTX_AUTH_INVALID
 * @retval Low level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_3gpp_context_get(ncp_hdl_t ncpHdl, 
                          ncp_spp_3gpp_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_3gpp_context_size(ncp_spp_3gpp_context_t *context, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create this context.
 *
 * See \link contextSizeDescription this description \endlink for more details. 
 */
NCP_API ncp_st_t
ncp_spp_3gpp_context_size(ncp_spp_3gpp_context_t *context,
                           ncp_uint32_t *outSize);


/****************************************************************************
**    TLS/SSL CONTEXT
****************************************************************************/

/*!
 * @enum ncp_spp_tls_protocol_t
 * @brief Defines supported TLS/SSL protocol versions 
 *        and specifies what protocol is to be used for a specific context.
 */
typedef enum ncp_spp_tls_protocol_e {
    NCP_SPP_SSL_3_0,
    NCP_SPP_TLS_1_0,
    NCP_SPP_TLS_1_1,
    NCP_SPP_TLS_1_2,
    NCP_SPP_TLS_PROTO_MAX
} ncp_spp_tls_protocol_t;


/*!
 * @enum ncp_spp_tls_encr_t
 * @brief Defines encryption algorithms supported by TLS and SSL. 
 */
typedef enum ncp_spp_tls_encr_e {
    NCP_SPP_TLS_ENCR_NULL,
    NCP_SPP_TLS_ENCR_DES_CBC,
    NCP_SPP_TLS_ENCR_3DES_CBC,
    NCP_SPP_TLS_ENCR_ARC4_40,
    NCP_SPP_TLS_ENCR_ARC4_128,
    NCP_SPP_TLS_ENCR_AES_128_CBC,
    NCP_SPP_TLS_ENCR_AES_256_CBC,
    NCP_SPP_TLS_ENCR_AES_128_GCM,
    NCP_SPP_TLS_ENCR_AES_256_GCM,
    NCP_SPP_TLS_ENCR_MAX
} ncp_spp_tls_encr_t;


/*!
 * @enum ncp_spp_tls_auth_t
 * @brief Defines authentication algorithm supported 
 * by TLS and SSL. 
 */
typedef enum ncp_spp_tls_auth_e {
    NCP_SPP_TLS_AUTH_NULL,
    NCP_SPP_TLS_AUTH_MD5,
    NCP_SPP_TLS_AUTH_SHA1,
    NCP_SPP_TLS_AUTH_SHA_256,
    NCP_SPP_TLS_AUTH_SHA_384,
    NCP_SPP_TLS_AUTH_MAX
} ncp_spp_tls_auth_t;


/*!
 * @enum ncp_spp_tls_context_t
 * @brief Data structure that defines all the Security context fields needed to  
 * support TLS and SSL. 
 */
typedef struct ncp_spp_tls_context_s {
    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t                     id;
    /*!
     * @brief Selects between SSL/TLS protocols and
     *        specifies the protocol version.
     */
    ncp_spp_tls_protocol_t           protocol;
    ncp_spp_direction_t              direction;
    ncp_spp_tls_encr_t               encr; 
    ncp_byte_string_t                encrKey;
    /*!
     * @brief Message Authentication algorithm, called
     * "MACAlgorithm" in TLS RFCs.
     */
    ncp_spp_tls_auth_t               auth;
    /*!
     * @brief Message Authentication algorithm key
     */
    ncp_byte_string_t                authKey;
    /*!
     * Enables the "truncated_hmac" extension,
     * as defined by RFCs 3546/4366. If true, then 
     * the ICV length will be truncated to 10 bytes
     * for the HMAC message authentication algorithms
     * (e.g. MD5, SHA1). The extension is
     * invalid for SSL 3.0 and ignored for 
     * the non-HMAC authentication algorithms.
     */
    ncp_bool_t                       truncatedHmac;
    /*!
     * @brief Initialization Vector needed by CBC 
     *        encryption algorithms for SSL 3.0 and TLS 1.0
     *        and Salt needed by AES-GCM.
     *
     * For AES-GCM, supported only in TLS 1.2, this value
     * specifies the "salt" parameter and it must be 4 bytes.
     * <p>
     * For SSL 3.0 and TLS 1.0 it shall be:
     * <ul>
     *   <li> 8 bytes for DES/3DES algorithms </li>
     *   <li> 16 bytes for AES algorithm </li>
     *   <li> empty for NULL and ARC4 (because the 
     *        ARC4 state is derived from its key) </li>
     * </ul>
     */
    ncp_byte_string_t                iv;
    /*!
     * @brief Indicates whether the SPP should maintain
     *        a byte count and packet count statistics
     *        as a part of the Context. 
     *
     * These statistics can be retrieved by calling
     * ncp_spp_context_counters_get() API.
     */
    ncp_bool_t                       countersPresent;
} ncp_spp_tls_context_t;


/*!
 * @fn ncp_st_t ncp_spp_tls_context_set(ncp_hdl_t ncpHdl, ncp_spp_tls_context_t *ctx);
 * @brief Create a TLS or SSL context.
 *
 * RESTRICTION: the SPP currently does <b>not</b> support 
 * running NULL authentication with a non-NULL encryption.
 * The NULL, NULL combination is allowed.
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_tls_context_set(ncp_hdl_t ncpHdl, 
                        ncp_spp_tls_context_t *ctx);


/*!
 * @fn ncp_st_t ncp_spp_tls_context_get(ncp_hdl_t ncpHdl, ncp_spp_tls_context_t *ctx);
 * @brief Retrieve the settings of a current TLS or SSL context.
 *
 * Populate the context structure fields with values from a current TLS or SSL
 * context.  The <b>id</b> field of the structure needs to be assigned with
 * the ID for the context whose values are to be retrieved.
 * <p>
 * If the buf pointer values for <b>encrKey</b>, <b>authKey</b> and
 * <b>iv</b> are not NULL, and the len value indicates that the buffer
 * is large enough to fit the byte string, the buffer will be populated
 * with the corresponding values from the context structure, if they exist
 * for the specified context ID.  The <b>authKey</b> and <b>encrKey</b>
 * values will not be available for authentication and encryption algorithms
 * that use precomputes (HMAC, AES_CBC).  The <b>iv</b> value will not be
 * available for ARC4 since it uses a pre-computed cipher state.  The len
 * value for these fields will be updated with the number of bytes that
 * the API copied into the buffer.  If nothing is copied into the buffer,
 * the API will set the len field for the respective buffer to zero.
 * <p>
 * Note that the programming for different TLS versions for some combinations
 * are identical.  In these cases, this API will return the lowest TLS version
 * that supports the combination.  For example, a get call on a context that
 * was created specifying TLS_1_1 as the protocol, but uses only features that
 * are supported by TLS_1_0 will, return TLS_1_0 in the protocol field.
 * <p>
 * The PROTO_INVALID error code indicates that the id represents a
 * valid SPP context, but it is not an TLS or SSL context.  The ENCR and AUTH
 * invalid error codes indicate that the context has been corrupted.
 *
 * @retval NCP_ST_SUCCESS
 * @retval NCP_ST_INVALID_HANDLE
 * @retval NCP_ST_SPP_NOT_CONFIGURED
 * @retval NCP_ST_NS_NO_NAMESPACES_DEFINED
 * @retval NCP_ST_NS_ENTRY_ID_INVALID
 * @retval NCP_ST_SPP_CTX_DISABLED
 * @retval NCP_ST_SPP_CTX_PROTO_INVALID
 * @retval NCP_ST_SPP_CTX_ENCR_INVALID
 * @retval NCP_ST_SPP_CTX_AUTH_INVALID
 * @retval level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_tls_context_get(ncp_hdl_t ncpHdl, 
                        ncp_spp_tls_context_t *ctx);


/*!
 * @fn ncp_st_t ncp_spp_tls_context_size(ncp_spp_tls_context_t *context, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create this context.
 *
 * See \link contextSizeDescription this description \endlink for more details. 
 */
NCP_API ncp_st_t
ncp_spp_tls_context_size(ncp_spp_tls_context_t *context,
                           ncp_uint32_t *outSize);


/****************************************************************************
**    SRTP CONTEXT
****************************************************************************/

/*!
 * @enum ncp_spp_srtp_protocol_t
 * @brief Tells whether the context is for SRTP or SRTCP.
 */
typedef enum ncp_spp_srtp_protocol_e {
    NCP_SPP_SRTP,
    NCP_SPP_SRTCP,
    NCP_SPP_SRTP_PROTO_MAX
} ncp_spp_srtp_protocol_t;


/*!
 * @enum ncp_spp_srtp_encr_t
 * @brief Defines encryption algorithm supported by SRTP/SRTCP
 */
typedef enum ncp_spp_srtp_encr_e {
    NCP_SPP_SRTP_ENCR_NULL,
    NCP_SPP_SRTP_ENCR_AES_CM,
    NCP_SPP_SRTP_ENCR_AES_GCM,
    NCP_SPP_SRTP_ENCR_MAX
} ncp_spp_srtp_encr_t;


/*!
 * @enum ncp_spp_srtp_auth_t
 * @brief Defines authentication algorithms supported by SRTP/SRTCP.
 */
typedef enum ncp_spp_srtp_auth_e {
    NCP_SPP_SRTP_AUTH_NULL,
    NCP_SPP_SRTP_AUTH_HMAC_SHA1,
    NCP_SPP_SRTP_AUTH_MAX
} ncp_spp_srtp_auth_t;


/*!
 * @enum ncp_spp_srtp_auth_tag_len_t
 * @brief This enum defines the standard choices for the SRTP ICV length
 *
 * The API currently checks the ICV length only against maximum allowed 
 * value, so this list does not cover all possible choices.
 */
typedef enum ncp_spp_srtp_auth_tag_len_e {
    NCP_SPP_SRTP_AUTH_TAG_SHA1_4  = 4,
    NCP_SPP_SRTP_AUTH_TAG_SHA1_10 = 10,
    NCP_SPP_SRTP_AUTH_TAG_GCM_8   = 8,
    NCP_SPP_SRTP_AUTH_TAG_GCM_12  = 12,
    NCP_SPP_SRTP_AUTH_TAG_GCM_16  = 16
} ncp_spp_srtp_auth_tag_len_t;


/*!
 * @enum ncp_spp_srtp_context_t
 * @brief  Data structure that defines all the Security context 
 * fields needed to create an SRTP or SRTCP context.
 */
typedef struct ncp_spp_srtp_context_s {
    /*!
     * @brief The key lifetime (in packets).
     *
     * The value can be at most 2^48 for SRTP and 2^31 for SRTCP.
     */
    ncp_uint64_t                     packetLifetime;
    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t                     id;
    /*!
     * @brief Selects between SRTP and SRTCP protocols
     */
    ncp_spp_srtp_protocol_t          protocol; 
    ncp_spp_direction_t              direction;

    ncp_spp_srtp_encr_t              encr; 
    ncp_byte_string_t                encrKey;
    ncp_spp_srtp_auth_t              auth;
    ncp_byte_string_t                authKey;

    /*!
     * @brief The length of the Authentication Tag.
     */
    ncp_spp_srtp_auth_tag_len_t      authTagLen;

    /*!
     * @brief The salting key, which is used for IV generation.
     *
     * The length must be:
     * <ul>
     * <li> NULL encryption: 0 </li>
     * <li> AES-CM encryption: 14 bytes (112 bits) </li>
     * <li> AES-GCM encryption: 12 bytes (96 bits) </li>
     * </ul>
     */
    ncp_byte_string_t                saltKey;
    /*!
     * @brief The 'SSRC' value which is needed for
     * the IV generation
     */
    ncp_uint32_t                     ssrc;

    /*!
     * @brief Initial value of Rollover Couner (ROC) as
     *        defined by RFC3711; ignored for SRTCP.
     *
     * Must be set to 0 at session start, but may be
     * set to a different value if joining an existing
     * session or re-keying.
     */
    ncp_uint32_t                     roc;
    /*!
     * @brief RTP Sequence Number (SEQ) value as
     *        defined by RFC3711; ignored for SRTCP or
     *        Inbound context if 'seqFromFirstPacket' is true.
     */
    ncp_uint16_t                     seq; 

    /*!
     * @brief Applies only to Inbound SRTP context.
     *        Tells whether the initial value of 'seq'
     *        should be taken from the first packet, as
     *        opposed to being specified in this structure.
     */
    ncp_bool_t                       seqFromFirstPacket;

    /*!
     * The Master Key Identifier (MKI) field, 
     * as defined by RFC 3711. The API is always writing
     * this value, but it is only used by the Firmware 
     * for OUTBOUND context when 'mkiPresent' is set to true.
     *
     * Note, currently the API is only designed 
     * to work with 32-bit MKIs.
     */
    ncp_uint32_t                     mki;
    /*!
     * @brief Tells whether MKI should be appended to
     *        the Outbound PDU and expected in the Inbound one.
     */
    ncp_bool_t                       mkiPresent;

    /*!
     * @brief Enables Replay Protection check. Applies only to the Inbound context.
     */
    ncp_bool_t                       antiReplayEnable;
    
    /*!
     * @brief Applies only to the Inbound
     * contetext when "antiReplayEnable" is true.
     */
    ncp_spp_arw_size_t               antiReplayWindowSize;
} ncp_spp_srtp_context_t;


/*!
 * @fn ncp_st_t ncp_spp_srtp_context_set(ncp_hdl_t ncpHdl, ncp_spp_srtp_context_t *ctx);
 * @brief Create an SRTP/SRTCP context.
 * 
 * RESTRICTION: NULL authentication is <b>not</b> 
 * allowed for SRTCP protocol.
 * <p>
 * Note, SRTP protocol allows both NULL authentication
 * and NULL/NULL combination.
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_srtp_context_set(ncp_hdl_t ncpHdl, 
                         ncp_spp_srtp_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_srtp_context_get(ncp_hdl_t ncpHdl, ncp_spp_srtp_context_t *ctx);
 * @brief Retrieve the settings of a current SRTP/SRTCP context.
 *
 * Populate the context structure fields with values from a current SRTP/SRTCP
 * context.  The <b>id</b> field of the structure needs to be assigned with
 * the ID for the context whose values are to be retrieved.
 * <p>
 * If the buf pointer value for <b>encrKey</b> is not NULL, and the len value
 * indicates that the buffer is large enough to fit the byte string, the
 * buffer will be populated with the corresponding value from the context
 * structure, if it exists for the specified context ID.  The <b>authKey</b>
 * value will not be available since the authentication algorithm stores a
 * precomputed value in the context.  The <b>saltKey</b> and <b>ssrc</b>
 * fields will not be available.  They are used for IV generation and are
 * not stored in the context.  The len value for byte string fields will be
 * updated with the number of bytes that the API copied into the buffer.
 * If nothing is copied into the buffer, the API will set the len field for
 * the respective buffer to zero.
 * <p>
 * The PROTO_INVALID error code indicates that the id represents a
 * valid SPP context, but it is not an SRTP/SRTCP context.  The ENCR and AUTH
 * invalid error codes indicate that the context has been corrupted.
 *
 * @retval NCP_ST_SUCCESS
 * @retval NCP_ST_INVALID_HANDLE
 * @retval NCP_ST_SPP_NOT_CONFIGURED
 * @retval NCP_ST_NS_NO_NAMESPACES_DEFINED
 * @retval NCP_ST_NS_ENTRY_ID_INVALID
 * @retval NCP_ST_SPP_CTX_DISABLED
 * @retval NCP_ST_SPP_CTX_PROTO_INVALID
 * @retval NCP_ST_SPP_CTX_ENCR_INVALID
 * @retval NCP_ST_SPP_CTX_AUTH_INVALID
 * @retval Low level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_srtp_context_get(ncp_hdl_t ncpHdl, 
                         ncp_spp_srtp_context_t *ctx);


/*!
 * @fn ncp_st_t ncp_spp_srtp_context_size(ncp_spp_srtp_context_t *context, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create this context.
 *
 * See \link contextSizeDescription this description \endlink for more details. 
 */
NCP_API ncp_st_t
ncp_spp_srtp_context_size(ncp_spp_srtp_context_t *context,
                           ncp_uint32_t *outSize);


/****************************************************************************
**    GENERIC CONTEXT
****************************************************************************/

/*NCP_AUTO_GENERATED_SECTION_BEGIN_SPP_CIPHER_HASH_IDS*/
/*
 * This section was auto-generated by the Perl
 * script in <ASE_TREE>/bldtools/sppupdate.pl 
 * based on what was specified in the SPP Firmware source code
 */
typedef enum ncp_spp_cipher_id_e {
    NCP_SPP_CIPHER_ID_NULL               = 1,
    NCP_SPP_CIPHER_ID_KASUMI_F8          = 3,
    NCP_SPP_CIPHER_ID_SNOW_3G_F8         = 5,
    NCP_SPP_CIPHER_ID_AES_GCM            = 7,
    NCP_SPP_CIPHER_ID_AES_ECB            = 9,
    NCP_SPP_CIPHER_ID_AES_CBC            = 11,
    NCP_SPP_CIPHER_ID_AES_CTR            = 13,
    NCP_SPP_CIPHER_ID_AES_CM             = 15,
    NCP_SPP_CIPHER_ID_TDES_ECB           = 17,
    NCP_SPP_CIPHER_ID_TDES_CBC           = 19,
    NCP_SPP_CIPHER_ID_DES_ECB            = 21,
    NCP_SPP_CIPHER_ID_DES_CBC            = 23,
    NCP_SPP_CIPHER_ID_ARC4               = 25,
    NCP_SPP_CIPHER_ID_AES_CCM            = 27,
    NCP_SPP_CIPHER_ID_ZUC_F8             = 31,
    NCP_SPP_CIPHER_ID_A5_1               = 33,
    NCP_SPP_CIPHER_ID_A5_3               = 35,
    NCP_SPP_CIPHER_ID_A5_4               = 35,
    NCP_SPP_CIPHER_ID_A5_3_ECSD          = 37,
    NCP_SPP_CIPHER_ID_A5_4_ECSD          = 37,
    NCP_SPP_CIPHER_ID_MAX                = 39
} ncp_spp_cipher_id_t; 

typedef enum ncp_spp_hash_id_e {
    NCP_SPP_HASH_ID_NULL                 = 0,
    NCP_SPP_HASH_ID_KASUMI_F9            = 2,
    NCP_SPP_HASH_ID_SNOW_3G_F9           = 4,
    NCP_SPP_HASH_ID_AES_GMAC             = 6,
    NCP_SPP_HASH_ID_AES_XCBC_MAC         = 8,
    NCP_SPP_HASH_ID_AES_CMAC             = 10,
    NCP_SPP_HASH_ID_HMAC_MD5             = 12,
    NCP_SPP_HASH_ID_MD5                  = 14,
    NCP_SPP_HASH_ID_HMAC_SHA_224         = 16,
    NCP_SPP_HASH_ID_SHA_224              = 18,
    NCP_SPP_HASH_ID_HMAC_SHA_256         = 20,
    NCP_SPP_HASH_ID_SHA_256              = 22,
    NCP_SPP_HASH_ID_HMAC_SHA1            = 24,
    NCP_SPP_HASH_ID_SHA1                 = 26,
    NCP_SPP_HASH_ID_SSL_SHA1             = 28,
    NCP_SPP_HASH_ID_ZUC_F9               = 30,
    NCP_SPP_HASH_ID_HMAC_SHA_384         = 32,
    NCP_SPP_HASH_ID_SHA_384              = 34,
    NCP_SPP_HASH_ID_HMAC_SHA_512         = 36,
    NCP_SPP_HASH_ID_SHA_512              = 38,
    NCP_SPP_HASH_ID_MAX                  = 40
} ncp_spp_hash_id_t;
/*NCP_AUTO_GENERATED_SECTION_END_SPP_CIPHER_HASH_IDS*/


/*!
 * @struct ncp_spp_generic_context_t
 * @brief The structure specifying the information
 *        needed to create a Generic Context.
 */
typedef struct ncp_spp_generic_context_s {
    ncp_byte_string_t             iv;
    ncp_byte_string_t             cipherKey;
    ncp_byte_string_t             cipherState;
    ncp_byte_string_t             hashKey;

    ncp_uint64_t                  softLifetimeByteCnt;
    ncp_uint64_t                  hardLifetimePacketCnt;

    ncp_byte_string_t             antiReplayWindow;

    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t                  id;

    ncp_uint64_t                  seqNum;
    ncp_uint32_t                  spiMkiRb;
   
    ncp_uint16_t                  scriptId;
    ncp_spp_cipher_id_t           cipherId;
    ncp_spp_hash_id_t             hashId;
    ncp_uint8_t                   icvLen;

    /*!
     * Defined in the context, but not used.
     * May be re-used for something else.
     */
    ncp_uint8_t                   maskedTunnelHdrLen;

    /*!
     * Defined in the context, but not used. 
     * May be re-used for something else.
     */
    ncp_uint8_t                   tunnelHdrLen;

    /*!
     * NOTE: If 'word3Present' is false, the 'spiMkiRb'
     * 'maskedTunnelHdrLen', 'tunnelHdrLen' will be
     * ignored, because there would be no place to write 
     * them.
     */
    ncp_uint32_t                  word3Present          : 1;
    /*!
     * This controls the flag in the context structure, not the 
     * fact whether the counters are written into the SA record.
     */
    ncp_uint32_t                  cntPresentLifetimeEn  : 1;
    ncp_uint32_t                  tunnelMode            : 1;
    ncp_uint32_t                  antiReplaySeqRollover : 1;
    ncp_uint32_t                  esnEnMkiPresent       : 1;
    ncp_uint32_t                  pduMode               : 1;

    ncp_uint32_t                  hashFirst             : 1;
    ncp_uint32_t                  seqNumPresent         : 1;
    ncp_uint32_t                  seqNumInRegion2       : 1;

    /*!
     * This flag actualy controls whether the conters are 
     * written into the Context data structure
     */
    ncp_uint32_t                  countersPresent       : 1;
  
    /*!
     * If true, the API takes the value of the 'hashKey'
     * and writes it directly into the context record
     * without performing any hash precomputes. I.e.
     * it assumes that the 'hashKey' value actually
     * contains the final precompute.
     */
    ncp_uint32_t                  hashPrecompDisable    : 1;
    /*!
     * We use the HMAC_MD5 hashId for both the regular
     * HMAC mode, as well as SSL MD5 mode. They use the
     * the same algorithm, but require slightly 
     * different precomputes. This flag tells the API
     * that precompute needs to be performed 
     * for SSL MD5, as opposed to regular HMAC MD5.
     * The value must be false if the 'hashId' is 
     * not HMAC_MD5.
     */
    ncp_uint32_t                  hashPrecompSSLMD5     : 1;
    /*!
     * If this flag is true, the context add will treat
     * the incoming key as AES encryption key,
     * calculate the AES decryption key, and write the 
     * decription key into the context.
     */
    ncp_uint32_t                  computeDecryptionKey  : 1;
    
} ncp_spp_generic_context_t;


/*!
 * @fn ncp_st_t ncp_spp_generic_context_set(ncp_hdl_t ncpHdl, ncp_spp_generic_context_t *ctx);
 * @brief Create a Generic Context; this is primarily 
 *        designed for debug and testing purposes.
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_generic_context_set(ncp_hdl_t ncpHdl, 
                          ncp_spp_generic_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_generic_context_size(ncp_spp_generic_context_t *ctx, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create that context.
 *
 * See \link contextSizeDescription this description \endlink for more details. 
 * <p>
 * Note, the generic context is mostly designed for debug
 * and testing purposes.
 */
NCP_API ncp_st_t
ncp_spp_generic_context_size(ncp_spp_generic_context_t *ctx,
                             ncp_uint32_t *outSize);

/****************************************************************************
**    ALG_ACC CONTEXT
****************************************************************************/

/*!
 * @brief Defines protocols supported by ALG_ACC SPP APIs.
 *
 */
typedef enum ncp_spp_alg_acc_protocol_e {
    /*! Authentication followed by Encryption */
    NCP_SPP_ALG_ACC_AE,
    /*! Decryption followed by Authentication */
    NCP_SPP_ALG_ACC_DA,
    NCP_SPP_ALG_ACC_PROTO_MAX
} ncp_spp_alg_acc_protocol_t;


/*!
 * @brief Defines encryption algorithms supported
 * by ALG_ACC SPP APIs.
 */
typedef enum ncp_spp_alg_acc_encr_e {
    NCP_SPP_ALG_ACC_ENCR_NULL,
    NCP_SPP_ALG_ACC_ENCR_AES_ECB,
    NCP_SPP_ALG_ACC_ENCR_AES_CBC,
    NCP_SPP_ALG_ACC_ENCR_AES_CTR,
    NCP_SPP_ALG_ACC_ENCR_AES_CM,
    NCP_SPP_ALG_ACC_ENCR_3DES_ECB,
    NCP_SPP_ALG_ACC_ENCR_3DES_CBC,
    NCP_SPP_ALG_ACC_ENCR_DES_ECB,
    NCP_SPP_ALG_ACC_ENCR_DES_CBC,
    NCP_SPP_ALG_ACC_ENCR_ARC4,
    NCP_SPP_ALG_ACC_ENCR_MAX
} ncp_spp_alg_acc_encr_t;


/*!
 * @brief Defines authentication algorithms
 *  supported by ALG_ACC SPP APIs.
 */
typedef enum ncp_spp_alg_acc_auth_e {
    NCP_SPP_ALG_ACC_AUTH_NULL,
    NCP_SPP_ALG_ACC_AUTH_AES_GMAC,
    NCP_SPP_ALG_ACC_AUTH_AES_XCBC_MAC,
    NCP_SPP_ALG_ACC_AUTH_AES_CMAC,
    NCP_SPP_ALG_ACC_AUTH_HMAC_MD5,
    NCP_SPP_ALG_ACC_AUTH_MD5,
    NCP_SPP_ALG_ACC_AUTH_HMAC_SHA_224,
    NCP_SPP_ALG_ACC_AUTH_SHA_224,
    NCP_SPP_ALG_ACC_AUTH_HMAC_SHA_256,
    NCP_SPP_ALG_ACC_AUTH_SHA_256,
    NCP_SPP_ALG_ACC_AUTH_HMAC_SHA1,
    NCP_SPP_ALG_ACC_AUTH_SHA1,
    NCP_SPP_ALG_ACC_AUTH_HMAC_SHA_384,
    NCP_SPP_ALG_ACC_AUTH_SHA_384,
    NCP_SPP_ALG_ACC_AUTH_HMAC_SHA_512,
    NCP_SPP_ALG_ACC_AUTH_SHA_512,
    NCP_SPP_ALG_ACC_AUTH_MAX
} ncp_spp_alg_acc_auth_t;


/*!
 * @brief Data structure that defines all the Security context 
 *        fields needed to support Algorithm Acceleration SPP APIs.
 *
 */
typedef struct ncp_spp_alg_acc_context_s {
    /*!
     * @brief A 24-bit ID of the context entry to write.
     */
    ncp_uint32_t                    id;
    /*!
     * @brief Specifies what protocol the given
     * Context is being created for.
     */
    ncp_spp_alg_acc_protocol_t         protocol;

    /*!
     * @brief Specified Confidentiality (encryption) algorithm.
     */
    ncp_spp_alg_acc_encr_t             encr; 

    /*!
     * @brief Cipher Key
     *	Cipher key is not applicable if NULL Cipher. Set the len field to zero if encryption 
     * key is not present.
     */
    ncp_byte_string_t                  encrKey;

   
     /*!
     * @brief Specified Integrity (authentication) algorithm.
     */
    ncp_spp_alg_acc_auth_t          auth;

     /*!
     * @brief Specified Integrity (authentication) Key.
     * Hash Key or Precompute is stored here.
     * For NULL, MD5, SHA1,SHA224/256/384/512 authentication modes, 
     * set the len field to zero.
     */

    ncp_byte_string_t               authKey;

  
     /*!
     * @brief  Initialization Vector value
     *  IV/Nonce/Fresh: Contains the IV Value for a protocol 
     *  If IV is not stored in SA, set the len field to zero.
     *  Depending on protocol it may contain NONCE/SALT and IV.
     *	
     */
    ncp_byte_string_t 	        iv;


    /*!
     * @brief The AID source  
     * 0: AID is sourced from the SA  <br>
     *		Length and content are defined in AID_Data field. <br>
     * 1: AID is sourced from the the PDU Data <br> 
     *		Length and content are pointed to by AID offset and AID Length field 
     *		in the input task parameters.
     *
     *
     */
    ncp_bool_t                AID_Src;

    /*!
     * @brief  Additional Integrity Data  
     *      This field is only valid if the AID Source Flag is zero.
     *  Store up to 256 bytes of AID which will be included in the ICV calculation after the
     * PDU data. Set the len field to zero when there is no AID Data present.
     */

    ncp_byte_string_t         	AID_Data;


    /*!
     * @brief Indicates whether the SPP should maintain
     *        a byte count and packet count statistics
     *        as a part of the Context. <br>
     *	0 - No per SA byte and packet counters <br>
     *  1 - per SA byte and packet counters present<br>
     *
     * IMPORTANT NOTE: countersPresent should always be 
     * set to FALSE for ALG_ACC context as the byte/packet 
     * counters are not applicable.
     */
    ncp_bool_t                      countersPresent;

    /*!
     * @brief  Encrypt ICV <br>
     * 0: If Authentication then Encrypt script, the ICV is not included as encryption data <br>
     * 1: If Authentication then Encrypt script, the ICV is included as encryption data immediately
     *		following the last byte of regular encryption data.<br>
     */
    ncp_bool_t 		encrypt_icv;
    /*!
     * @brief   Word3 Present 
     * 0: If Additional Integrity Data is not stored in the SA.<br>
     * 1: If Additional Integrity Data is stored in the SA.<br>
     *
     */
    ncp_bool_t 	word3Present     ;


     /*!
     * @brief  ICV length <br>
     * This contains the truncation length. <br>
     *  0 - if NULL authentication
     */
    ncp_uint8_t			icvLength;

} ncp_spp_alg_acc_context_t;


/*!
 * @fn ncp_st_t ncp_spp_alg_acc_context_set(ncp_hdl_t ncpHdl, ncp_spp_alg_acc_context_t *ctx);
 * @brief Create a ALG_ACC context.
 *
 * NOTE: The API does not place any restrictions on
 *       using NULL encryption or authentication algorithms.
 *
 * See the definition of the context structure for more
 * details on how to program the "protocol" field for 
 * different scenarions.
 *
 * @return \link contextSetErrorCodes Context Set Error Codes \endlink
 */
NCP_API ncp_st_t
ncp_spp_alg_acc_context_set(ncp_hdl_t ncpHdl, 
                          ncp_spp_alg_acc_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_alg_acc_context_get(ncp_hdl_t ncpHdl, ncp_spp_alg_acc_context_t *ctx);
 * @brief Retrieve the settings of a current ALG_ACC context.
 *
 * Populate the context structure fields with values from a current ALG_ACC
 * context.  The <b>id</b> field of the structure needs to be assigned with
 * the ID for the context whose values are to be retrieved.
 * <p>
 * If the buf pointer values for <b>encrKey</b>, <b>authKey</b>, <b>iv</b> and
 * <b>AID_Data</b>
 * are not NULL, and the len value indicates that the buffer
 * is large enough to fit the byte string, the buffer will be populated
 * with the corresponding values from the context structure, if they exist
 * for the specified context ID.  The <b>authKey</b> values will not be
 * available for authentication algorithms that use precomputes (AES_CMAC).
 * The len value for these fields will be updated with the number of bytes
 * that the API copied into the buffer.  If nothing is copied into the buffer,
 * the API will set the len field for the respective buffer to zero.
 * <p>
 * The PROTO_INVALID error code indicates that the id represents a
 * valid SPP context, but it is not a ALG_ACC context.  The ENCR and AUTH
 * invalid error codes indicate that the context has been corrupted.
 *
 * @retval NCP_ST_SUCCESS
 * @retval NCP_ST_INVALID_HANDLE
 * @retval NCP_ST_SPP_NOT_CONFIGURED
 * @retval NCP_ST_INVALID_PARAMETER
 * @retval NCP_ST_NO_MEMORY
 * @retval NCP_ST_NS_NO_NAMESPACES_DEFINED
 * @retval NCP_ST_NS_ENTRY_ID_INVALID
 * @retval NCP_ST_SPP_CTX_DISABLED
 * @retval NCP_ST_SPP_CTX_PROTO_INVALID
 * @retval NCP_ST_SPP_CTX_ENCR_INVALID
 * @retval NCP_ST_SPP_CTX_AUTH_INVALID
 * @retval Low level device access error codes
 */
NCP_API ncp_st_t
ncp_spp_alg_acc_context_get(ncp_hdl_t ncpHdl, 
                          ncp_spp_alg_acc_context_t *ctx);

/*!
 * @fn ncp_st_t ncp_spp_alg_acc_context_size(ncp_spp_alg_acc_context_t *context, ncp_uint32_t *outSize);
 * @brief Determine the size of the System Memory context
 *        entry needed to create this context.
 *
 * See \link contextSizeDescription this description \endlink for more details. 
 */
NCP_API ncp_st_t
ncp_spp_alg_acc_context_size(ncp_spp_alg_acc_context_t *context,
                           ncp_uint32_t *outSize);



/**************************************************************************/
/*       FIRMWARE                                                         */
/**************************************************************************/

/*!
 * @brief This constant is used by Firmware Script APIs to 
 *        represent an invalid Script ID value.
 */
#define NCP_SPP_FW_SCRIPT_ID_INVALID       0xFFFF


/*! 
 * @fn ncp_st_t ncp_spp_fw_script_id_find(ncp_hdl_t ncpHdl, const char *inScriptName, ncp_uint16_t *outScriptId);
 *  @brief Get the Firmware Script ID given its name.
 *
 *  The script IDs are firmware-specific, so the script name is a 
 *  portable way to refer to the firmware scripts. Given the name,
 *  this method looks up the Firmware Script ID. The lookup table
 *  is based on the information in the Firmware binary. If the 
 *  application intends to use Script ID very often, it should 
 *  perform the name-based lookup only once and cache the result.
 *
 *  @param outScriptId  Resulting script ID or 
 *        #NCP_SPP_FW_SCRIPT_ID_INVALID value if there is no script
 *        with such name (and the appropriate error code is returned).
 *
 *  @return Error Codes:
 *          \li ::NCP_ST_INVALID_HANDLE
 *          \li ::NCP_ST_SPP_NOT_CONFIGURED
 *          \li ::NCP_ST_SPP_FW_INV_SCRIPT_NAME
 */
NCP_API ncp_st_t
ncp_spp_fw_script_id_find(ncp_hdl_t ncpHdl, 
                          const char *inScriptName,
                          ncp_uint16_t *outScriptId);

/*! 
 * @fn ncp_st_t ncp_spp_fw_script_name_get(ncp_hdl_t ncpHdl, const ncp_uint16_t inScriptId, const char **outScriptName);
 *  @brief Get a Firmware Script name given its ID; 
 *         can also be used for iterating over all scripts.
 *
 *  The script IDs are firmware-specific, so the script name is a 
 *  portable way to refer to the firmware scripts. The valid ID 
 *  values are <b>even</b> numbers between 0 (inclusive) and 
 *  scriptIdLimit (exclusive), where the scriptIdLimit can
 *  be obtained by calling ncp_spp_script_id_limit_get().
 *  Note, there may be "gaps" within the valid ID range,
 *  which means a given ID is undefined. In that case, the
 *  API would return SUCCESS status, but the *outScriptName 
 *  will be NULL.
 *  <p>
 *  Here is an example of how to print all the valid Script IDs:
 *  <code><pre>
 *    ncp_uint16_t i, limit;
 *    const char *outScript = NULL;
 *
 *    NCP_CALL(ncp_spp_fw_script_id_limit_get(ncpHdl, &limit));
 *    for (i = 0; i < limit; i+=2)
 *    {
 *        NCP_CALL(ncp_spp_fw_script_name_get(ncpHdl, i, &outScript));
 *        if (outScript != NULL) 
 *        {
 *            printf("ID = %02d, Name = %s\n", i, outScript);
 *        }
 *    }
 *  </pre></code>
 *
 *  @param inScriptId The Script IDs MUST always be EVEN.
 *
 *  @param outScriptName Sets the pointer to point to the name.
 *         WARNING: This may be set to NULL, if the "gap" is found.
 *         NOTE: the pointed memory must NOT be overwritten.
 *
 *  @return Error Codes:
 *          \li ::NCP_ST_INVALID_HANDLE
 *          \li ::NCP_ST_SPP_NOT_CONFIGURED
 *          \li ::NCP_ST_SPP_FW_INV_SCRIPT_ID
 */
NCP_API ncp_st_t
ncp_spp_fw_script_name_get(ncp_hdl_t ncpHdl, 
                           const ncp_uint16_t inScriptId,
                           const char **outScriptName);


/*!
 * @fn ncp_st_t ncp_spp_fw_script_id_limit_get(ncp_hdl_t ncpHdl, ncp_uint16_t *outScriptIdLimit);
 * @brief Returns an even number, 'scriptIdLimit', such that 
 *        scriptId &lt; scriptIdLimit for all the valid Scritpt IDs.
 *
 * This method can be helpful if we want to display all the
 * script names/IDs. The following must be taken into account:
 * <ul>
 *   <li> The Script IDs <b>must be even</b> </li>
 *   <li> There may "gaps", i.e. some script IDs may be undefined </li>
 * </ul>
 *
 * @param outScriptIdLimit  Will return script ID limit or 0 if there 
 *                        are no scripts. It will also return 0 if 
 *                        there are any errors. 
 * @retval NCP_ST_SUCCESS
 * @retval NCP_ST_INVALID_HANDLE
 * @retval NCP_ST_SPP_NOT_CONFIGURED
 */
NCP_API ncp_st_t
ncp_spp_fw_script_id_limit_get(ncp_hdl_t ncpHdl,
                               ncp_uint16_t *outScriptIdLimit);

/*!
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* ncp_spp_h */
