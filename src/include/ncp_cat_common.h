/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file       ncp_cat_common.h
    @brief      Common constants, structures, and function signatures
                related to the creation and decoding of CAT memory blocks.
                These constants, typedefs, etc. are shared between the
                user library-level code, and the kernel driver-level code.
*/

#ifndef _NCP_CAT_COMMON_H_
#define _NCP_CAT_COMMON_H_

#include "ncp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @defgroup   _cat_mem_ CAT Memory Block Structures
    @brief      Common constants, structures, and function signatures
                related to the creation and decoding of CAT memory blocks.
    @{
    @ingroup    _cat_
 */

/**************************************************************************
* Constants                                                               *
**************************************************************************/

/*! @def NCP_CAT_CHIP_VERSION_X1R1
 *  @brief Human-readable representation of the X1R1 RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_X1R1      "NCP.0.0"

/*! @def NCP_CAT_CHIP_VERSION_X1R2
 *  @brief Human-readable representation of the X1R2 RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_X1R2      "NCP.1.0"

/*! @def NCP_CAT_CHIP_VERSION_X2R1
 *  @brief Human-readable representation of the X2R1 RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_X2R1      "NCP.2.0"

/*! @def NCP_CAT_CHIP_VERSION_ACP2500
 *  @brief Human-readable representation of the ACP2500 RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_ACP2500   "NCP.6.0"

/*! @def NCP_CAT_CHIP_VERSION_ACP2500R2
 *  @brief Human-readable representation of the ACP2500R2 RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_ACP2500R2  "NCP.7.0"

/*! @def NCP_CAT_CHIP_VERSION_AXM5500
 *  @brief Human-readable representation of the X7 v1.0/AXM55xx RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_AXM5500    "NCP.9.0"

/*! @def NCP_CAT_CHIP_VERSION_AXM5500P1
 *  @brief Human-readable representation of the X7P1 v1.1/AXM55xx RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_AXM5500P1    "NCP.9.1"

/*! @def NCP_CAT_CHIP_VERSION_AXM3500
 *  @brief Human-readable representation of the X3/AXM35xx RDL chip version
 */
#define NCP_CAT_CHIP_VERSION_AXM3500    "NCP.16.0"

/*! @def NCP_CAT_FORMAT_REVISION_ANY
 *  @brief Wildcard value that matches any version of the CAT memory
 *         structure header.
 */
#define NCP_CAT_FORMAT_REVISION_ANY     0xffffffff

/*! @def NCP_CAT_MAPMERGE_TAG_ANY
 *  @brief Wildcard value that matches any value of the 'mapMergeTag'
 *         attribute of the CAT register list memory structure header.
 */
#define NCP_CAT_MAPMERGETAG_ANY         0xffffffff

/*! @def NCP_CAT_GMEM_FORMAT_REVISION
 *  @brief Current version of the CAT global memory structure header.
 *         The value of this constant is expected to change as the
 *         content of the 'ncp_cat_globalMemHdr_t' structure changes.
 *         Revision=0: Original format
 *         Revision=1: Addition of map merge generation tag
 *         Revision=2: Growth to major- and minor sub-regions of CAT data
 *                     Addition of MTM L1 cache data
 *                     Option for raw data blocks
 */
#define NCP_CAT_GMEM_FORMAT_REVISION    2

/*! @def NCP_CAT_GMEM_COOKIE0
 *  @brief Value to be stored in 'cookie0' field of \link ncp_cat_globalMemHdr_t \endlink
 */
#define NCP_CAT_GMEM_COOKIE0            0x47434154

/*! @def NCP_CAT_GMEM_COOKIE1
 *  @brief Value to be placed in 'cookie1' field of \link ncp_cat_globalMemHdr_t \endlink
 */
#define NCP_CAT_GMEM_COOKIE1            0x41444d30

/*! @def NCP_CAT_REGMAP_FORMAT_REVISION
 *  @brief Current version of the CAT global memory structure header.
 *         The value of this constant is expected to change as the
 *         content of the 'ncp_cat_regMemHdr_t' structure changes,
 *         and/or format of the register data.
 *         Revision=0: Original format
 *         Revision=1: Addition of map merge generation tag
 */
#define NCP_CAT_REGMAP_FORMAT_REVISION    1

/*! @def NCP_CAT_REGMAP_MEM_COOKIE0
 *  @brief Value to be stored in 'cookie0' field of \link ncp_cat_regMemHdr_t \endlink
 */
#define NCP_CAT_REGMAP_MEM_COOKIE0      0x43415430

/*! @def NCP_CAT_REGMAP_MEM_COOKIE1
 *  @brief Value to be placed in 'cookie1' field of \link ncp_cat_regMemHdr_t \endlink
 */
#define NCP_CAT_REGMAP_MEM_COOKIE1      0x52544b52

/*! @def NCP_CAT_MTML1C_FORMAT_REVISION
 *  @brief Current version of the CAT global memory structure header.
 *         The value of this constant is expected to change as the
 *         content of the 'ncp_cat_mtmL1CacheHdr_t' structure changes,
 *         and/or the content of the L1 cache data.
 *         Revision=1: Original format
 */
#define NCP_CAT_MTML1C_FORMAT_REVISION    1

/*! @def NCP_CAT_MTML1C_MEM_COOKIE0
 *  @brief Value to be stored in 'cookie0' field of \link ncp_cat_memL1CacheHdr_t \endlink
 */
#define NCP_CAT_MTML1C_MEM_COOKIE0      0x4D544D4C

/*! @def NCP_CAT_MTML1C_MEM_COOKIE1
 *  @brief Value to be placed in 'cookie1' field of \link ncp_cat_memL1CacheHdr_t \endlink
 */
#define NCP_CAT_MTML1C_MEM_COOKIE1      0x31434143

/*! @def NCP_CAT_MME_MEM_COOKIE0
 *  @brief Value to be stored in 'cookie0' field of \link ncp_cat_rawMemHdr_t \endlink
 */
#define NCP_CAT_MME_MEM_COOKIE0         0x4d4d4543

/*! @def NCP_CAT_MME_MEM_COOKIE1
 *  @brief Value to be placed in 'cookie1' field of \link ncp_cat_rawMemHdr_t \endlink
 */
#define NCP_CAT_MME_MEM_COOKIE1         0x6d6d6563

/*! @def NCP_CAT_RAW_MEM_COOKIE0
 *  @brief Value to be stored in 'cookie0' field of \link ncp_cat_rawMemHdr_t \endlink
 */
#define NCP_CAT_RAW_MEM_COOKIE0         0x52434154

/*! @def NCP_CAT_RAW_MEM_COOKIE1
 *  @brief Value to be placed in 'cookie1' field of \link ncp_cat_rawMemHdr_t \endlink
 */
#define NCP_CAT_RAW_MEM_COOKIE1         0x72617763

/*! @def NCP_CAT_REG_BAD_VALUE
 *  @brief Value to be stored into register information array that follows the
 *         \link ncp_cat_regMemHdr_t \endlink when the software encounters an
 *         error reading a register from the 'crashed' hardware.
 */
#define NCP_CAT_REG_BAD_VALUE           0xdeadbeef

/*! @def NCP_CAT_RTE_VER_NAME_LEN
 *  @brief Byte length of char field 'rteVer' in \link ncp_cat_globalMemHdr_t \endlink, or \link ncp_cat_regMemHdr_t \endlink, or \link ncp_cat_mtmL1CacheHdr_t \endlink, or \link ncp_cat_rawMemHdr_t \endlink
 *         Value is the RTE Release ID for the build.
 */
#define NCP_CAT_RTE_VER_NAME_LEN       32 

/*! @def NCP_CAT_CHIP_VER_NAME_LEN
 *  @brief Byte length of char field 'chipVer' in \link ncp_cat_globalMemHdr_t \endlink, or \link ncp_cat_regMemHdr_t \endlink, or \link ncp_cat_mtmL1CacheHdr_t \endlink, or \link ncp_cat_rawMemHdr_t \endlink
 *         Value is a representation of the chip version/revision from which
 *         the register values were retrieved.
 */
#define NCP_CAT_CHIP_VER_NAME_LEN       16

/*! @def NCP_CAT_REGS_PQM
 *  @brief Mask value for the field 'flags' in \link ncp_cat_regMap_t \endlink
 *         that enables special processing for the 'PQM' registers.
 */
#define NCP_CAT_REGS_PQM                0x00000001

/*! @def NCP_CAT_REGS_FEMAC
 *  @brief Mask value for the field 'flags' in \link ncp_cat_regMap_t \endlink
 *         that enables special processing for the X7 'FEMAC' registers.
 *         Only applicable to X7 and X7_REL1P1 register maps!
 */
#define NCP_CAT_REGS_FEMAC              0x00000002

/*! @def NCP_CAT_MAX_READ_CHUNK_SIZE
    @brief Max number of 8-bit bytes that should be read at one time.
           Allows for 'paging' of the total amount of stored data.
           Must be a multiple of 4!
*/
#define NCP_CAT_MAX_READ_CHUNK_SIZE       4096

/*! @def NCP_CAT_MAX_WRITE_CHUNK_SIZE
    @brief Max number of 8-bit bytes that should be written at one time.
           Allows for 'paging' of the total amount of stored data.
           Must be a multiple of 4!
*/
#define NCP_CAT_MAX_WRITE_CHUNK_SIZE      4096

/*! @def NCP_CAT_REG_VAL_CHUNK
    @brief Useful processing granularity for a group of 32-bit words
           within the CAT APIs & CLIs.
*/
#define NCP_CAT_REG_VAL_CHUNK              256

/**************************************************************************
* Macros                                                                  *
**************************************************************************/

#ifndef NCP_CAT_GET_RTEVERSION
/*! @def NCP_CAT_GET_RTEVERSION(inDevHdl, outRteVersion)
    @brief Macro to generate a 'standardized' RTE Version string for
           comparison across different stored CAT memory records.
*/
#define NCP_CAT_GET_RTEVERSION(devHdl, rteVersion)                   \
    {                                                                \
        char _rv[NCP_DEV_MAX_VERSION_LENGTH];                        \
        int  _r1, _r2, _r3;                                          \
        NCP_CALL(ncp_dev_version(_rv));                              \
        if (sscanf(_rv, "NCP-%d.%d.%d", &_r1, &_r2, &_r3) != 3)      \
        {                                                            \
            NCP_CALL(NCP_ST_ERROR);                                  \
        }                                                            \
        sprintf(rteVersion, "%d.%d.%d", _r1, _r2, _r3);              \
    }
#endif

#ifndef NCP_CAT_GET_DEVVERSION
/*! @def NCP_CAT_GET_DEVVERSION(inDevHdl, outChipVersion)
    @brief Macro to generate a 'standardized' Device Version string for
           comparison across different stored CAT memory records.
*/
#define NCP_CAT_GET_DEVVERSION(devHdl, version)                      \
    {                                                                \
        ncp_uint32_t  _rv;                                           \
        ncp_rev_id_t *_ri = (ncp_rev_id_t*)&_rv;                     \
        NCP_CALL(ncp_dev_read32(devHdl, NCP_REGION_DRIVER_CFG,       \
                                NCP_DEV_CFG_REVISION_ID, &_rv));     \
        sprintf(version, "NCP.%d.%d", _ri->chipType, _ri->chipVersion); \
    }
#endif

#ifndef NCP_CAT_GET_DEVVERSION_VAL
/*! @def NCP_CAT_GET_DEVVERSION_VAL(inChipVer, outChipType, outChipVersion)
    @brief Macro to decompose a 'standardized' Device Version string for
           comparison across different stored CAT memory records.
*/
#define NCP_CAT_GET_DEVVERSION_VAL(inChipVer, outChipType, outChipVersion) \
    {                                                                   \
       int _rv = sscanf((inChipVer), "NCP.%d.%d", &(outChipType), &(outChipVersion)); \
       if (_rv != 2)                                                    \
       {                                                                \
           NCP_CALL(NCP_ST_CAT_CORRUPT_RECOVERY_DATA);                  \
       }                                                                \
    }
#endif

/**************************************************************************
* Type definitions: Function callback signatures                          *
**************************************************************************/

/*! @typedef ncp_st_t (*ncp_cat_write_t)(ncp_uint64_t offset, ncp_uint8_t *buffer, ncp_uint32_t len, void *wrFnArg);
 *  @brief Function signature for callback functions passsed to ncp_dev_cat_write()
 *  @param[in] offset Displacement into recovery memory at which to write
 *  @param[in] buffer Data to be written
 *  @param[in] len Number of bytes to write
 *  @param[in,out] wrFnArg Support region for this callback function
 *  @retval NCP_ST_SUCCESS Operation successfully completed
 *  @retval NCP_ST_CAT_WRITE_ERROR unable to write any or all of the bytes
 *          to the specified memory
 *  @retval Other Other device driver errors may be observed
 */

typedef ncp_st_t (*ncp_cat_write_t)(
    ncp_uint64_t   offset,
    ncp_uint8_t   *buffer,
    ncp_uint32_t   len,
    void          *wrFnArg);

/*! @typedef ncp_st_t (*ncp_cat_read_t)(ncp_uint64_t offset, ncp_uint8_t *buffer, ncp_uint32_t len, void *rdFnArg);
 *  @brief Function signature for callback functions passsed to ncp_dev_cat_read()
 *  @param[in] offset Displacement into recovery memory at which to read
 *  @param[in] buffer Location to place read data for caller
 *  @param[in] len Number of bytes to read
 *  @param[in,out] rdFnArg Support region for this callback function
 *  @retval NCP_ST_SUCCESS Operation successfully completed
 *  @retval NCP_ST_CAT_READ_ERROR unable to read any or all of the bytes
 *          from the specified memory
 *  @retval other Other device driver errors may be observed
 */

typedef ncp_st_t (*ncp_cat_read_t)(
    ncp_uint64_t   offset,
    ncp_uint8_t   *buffer,
    ncp_uint32_t   length,
    void          *rdFnArg);

/**************************************************************************
* Type definitions: Data & state structures                               *
**************************************************************************/

/*
 * Crash Analysis Tools recovery data:
 *
 * This is a mechanism that allows the user and/or the RTE to store a
 * snapshot of useful information about the NCP RTE environment and/or
 * the chip into RAM memory for later recovery and debug analysis.
 * Items that may be included in such a mechanism include:
 *
 * + registers read from the ACP/AXM chips
 * + MTM L1 cache data
 * + arbitrary state data from the RTE, driver, or an application
 *
 * The C.A.T. recovery data is stored in the NCP_REGION_NCA_NIC_SYSMEM
 * memory region.  It consists of a region header followed by one or
 * more data blocks.
 *
 * + The major region header includes ID 'cookies', checksums, and
 *   counters of the number of regions that follow, and a count of
 *   the total number of words in all of the following regions plus
 *   the header.  It can be viewed as a header on top of a data block.
 *
 * + Each of the following data blocks can be viewed as a miniature
 *   version of the major i.e. a fixed size/format region header,
 *   plus a block of words.  Each of these blocks is identified by
 *   a couple of checksum words at their beginning.  Dedicated code
 *   may then be used to determine the size of each block, and to
 *   decode it.
 *
 * + We try to use 64-byte major and minor region headers for standardization.
 *
 * Example:
 *
 *   --------------------------------------------------------------
 *   | Major region header                                        |
 *   | ... | Global ChkSum | ... | Subsection count | ...         |
 *   | ... | Total word count | ...                               |
 *   --------------------------------------------------------------
 *   |                                                            |
 *   | ---------------------------------------------------------- |
 *   | |Sub-region header (register list)                       | |
 *   | |... | Sub-region ChkSum | ... | Total word count | ...  | |
 *   | +--------------------------------------------------------+ |
 *   | |Sub-region data                                         | |
 *   | |                                                        | |
 *   | |                                                        | |
 *   | +--------------------------------------------------------+ |
 *   |                                                            |
 *   | ---------------------------------------------------------- |
 *   | |Sub-region header (MTM L1 cache)                        | |
 *   | |... | Sub-region ChkSum | ... | Total word count | ...  | |
 *   | +--------------------------------------------------------+ |
 *   | |Sub-region data                                         | |
 *   | |                                                        | |
 *   | |                                                        | |
 *   | +--------------------------------------------------------+ |
 *   |                                                            |
 *   | ---------------------------------------------------------- |
 *   | |Sub-region header (MME Data)                            | |
 *   | |... | Sub-region ChkSum | ... | Total word count | ...  | |
 *   | +--------------------------------------------------------+ |
 *   | |Sub-region data                                         | |
 *   | |                                                        | |
 *   | |                                                        | |
 *   | +--------------------------------------------------------+ |
 *   |                                                            |
 *   | ...                                                        |
 *   |                                                            |
 *   | ---------------------------------------------------------- |
 *   | |Sub-region header (other)                               | |
 *   | |... | Sub-region ChkSum | ... | Total word count | ...  | |
 *   | +--------------------------------------------------------+ |
 *   | |Sub-region data                                         | |
 *   | |                                                        | |
 *   | |                                                        | |
 *   | +--------------------------------------------------------+ |
 *   -------------------------------------------------------------
 *
 * As of 'NCP_CAT_FORMAT_REVISION' == '2', the total stored information
 * consists of the "globalMemhdr', followed by the register map (regMemhdr
 * plus array of register values), and finally the MTM L1 Cache Data
 * (mtmL1CacheHdr plus 1 or more instances of (mtmL1CacheBlockHdr plus
 * zero or more register values)).
 *
 */

/*! @struct ncp_cat_globalMemHdr_t
 *  @brief  Standardized memory header for organizaing all of the
 *          CAT recovery data
 *
 *  @details The header is placed at the beginning of the stored CAT
 *           recovery data.  It provides information that may be used
 *           after a power-cycle to determine whether the stored data
 *           is valid, as well as the amount of data stored.
 *
 *           This header fronts a series of one or more stored data
 *           blocks.  Each data block may describe different kinds of
 *           information of interest to the debug and analysis process.
 *           This header provides a convenient way to group these lesser
 *           pieces of data, as well as provide some validation of the
 *           total via checksums.
 */
typedef struct
{
    ncp_uint32_t    cookie0;    /*!< First GM validation cookie */
    ncp_uint32_t    cookie1;    /*!< Second GM validation cookie */
    ncp_uint32_t    crcValue;   /*!< Computed checksum across the
                                 *   header and stored values */
    ncp_uint32_t    formatRevision;
                       /*!< Revision/version code that denotes the overall
                        *   structure of the following data. */
    char            rteVer[NCP_CAT_RTE_VER_NAME_LEN];
                       /*!< RTE Release ID of the software that was used
                        *   to store this information */
    char            chipVer[NCP_CAT_CHIP_VER_NAME_LEN];
                       /*!< NCP Chip version/revision from which the
                        *   information was read */
    ncp_uint32_t    wordCount;
                      /*!< Size of all memory blocks that follow the header
                       *   rounded up to the specified number of 32-bit
                       *   words */
    ncp_uint32_t    regionCount;
                      /*!< Num of subsidiary regions actually stored in
                       *   the word array that follows this struct */
    ncp_uint32_t    pad1;
    ncp_uint32_t    pad2;
} ncp_cat_globalMemHdr_t;


/*! @struct ncp_cat_regMemHdr_t
 *  @brief  Standardized memory header for stored CAT list of registers
 *          with recovery data
 *
 *  @details The header is placed at the beginning of the stored CAT
 *           register block of recovery data.  It provides information
 *           that may be used after a power-cycle to determine whether
 *           the stored data is valid, as well as the amount of data
 *           stored.
 *
 *           The list of register values is stored in an array placed
 *           contiguously at the end of this memory header structure.
 *           The 'formatRevision' and other pieces of version info
 *           are used to find the 'register map' that should be used
 *           to decode the stored data.
 */
typedef struct
{
    ncp_uint32_t    cookie0;    /*!< First validation cookie */
    ncp_uint32_t    cookie1;    /*!< Second validation cookie */
    ncp_uint32_t    crcValue;   /*!< Computed checksum across the
                                 *   header and stored register values */
    ncp_uint32_t    formatRevision;
                       /*!< Revision/version code that denotes the struct
                        *   of the following register list.  This value is
                        *   matched against the field 'formatRevision' in
                        *   the \link ncp_cat_regMap_t \endlink struct by
                        *   the software that encodes or decodes the hdr. */
    char            rteVer[NCP_CAT_RTE_VER_NAME_LEN];
                       /*!< RTE Release ID of the software that was used
                        *   to store this information */
    char            chipVer[NCP_CAT_CHIP_VER_NAME_LEN];
                       /*!< NCP Chip version/revision from which the
                        *   register information was read */
    ncp_uint32_t    memorySize;
                      /*!< Size of total memory required to store all of
                       *   the information */
    ncp_uint32_t    registerCount;
                      /*!< Num of registers actually stored in the array
                       *   that follows this struct */
    ncp_uint32_t    mapMergeTag;
                       /*!< Secondary key for identifying the information
                        *   that must be stored/retrieved from a CAT register
                        *   list memory block.  This value is matched against
                        *   the field 'mapMergeTag' in the \link ncp_cat_regChip_t \endlink
                        *   struct by the software that encodes or decodes
                        *   the stored CAT Memory block. */
    ncp_uint32_t    pad1;
} ncp_cat_regMemHdr_t;

/*! @struct ncp_cat_regList_t
 *  @brief  Row struct identifying a group of U32 register(s) to be
 *          stored/retrieved in CAT recovery data.  An array of these
 *          rows describes the complete set of ACP data that the system
 *          needs to store and recover for a crash event.
 */
typedef struct
{
    ncp_region_id_t regionId;   /*!< NCP regionId handle for this group
                                 *   of registers */
    ncp_uint64_t    baseOffset; /*!< Byte offset to start of this group
                                 *   of registers */
    ncp_uint32_t    count;      /*!< Number of registers in this group */
} ncp_cat_regList_t;

/*! @struct ncp_cat_cfg_check_t
 *  @brief  Table struct listing the set of regions that contain CFG nodes
 *          with scratch registers.  This information is used to help
 *          identify whether a node is actually present and valid in the
 *          current platform.  This list should be associated with a
 *          versioned register map.
 */
typedef struct
{
    ncp_uint32_t        scratchRI;       /* node+target of region w scratch reg*/
    ncp_uint32_t        scratchOff;     /* offset to scratch register  */
} ncp_cat_cfg_check_t;

/*! @struct ncp_cat_regMap_t
 *  @brief  Table struct identifying a group of registers that may be
 *          stored as CAT recovery data.  One or more of these lists
 *          is associated with each chip description to describe the
 *          content of one crash event snapshot.
 *
 *          Note: The last entry of this array is always a dummy terminator.
 *          It is identified by (~0) for the region node, and zeros for the
 *          region id, and line count.
 */
typedef struct ncp_cat_regMap_s
{
    ncp_uint32_t       flags;
                        /*!< Control flags that support the storage/recovery
                         *   of register data with this mechanism. */
    ncp_uint32_t       registerListCount;
                        /*!< Number of rows of information in the array of
                         *  'registerList' structures */
    ncp_uint32_t       registerCount;
                        /*!< Total number of registers included in the
                         *   array of 'registerList' structures.  This
                         *   value should equal the 'registerCount' field
                         *   in the \link ncp_cat_memHdr_t \endlink struct
                         *   in the stored CAT memory block */
    ncp_cat_regList_t *registerList;
                        /*!< Array of structures describing blocks of NCP
                         *   registers to be loaded into or decoded from
                         *   the CAT memory block. */
    ncp_cat_cfg_check_t *cfgList;
                        /*!< Array of CFG nodes of interest for runtime
                         *   validation of the accompanying register list.
                         */
    ncp_uint32_t       cfgListSize;
                        /*!< Total number of nodes included in the array
                         *   of 'cfgList' structures. */
    struct ncp_cat_regMap_s     *next;
                        /*!< Link to the next entry in this description.
                         *   registers to be loaded into or decoded from
                         *   the CAT memory block. */

} ncp_cat_regMap_t;

/*! @struct ncp_cat_regChip_t
 *  @brief  Table struct identifying a chip-versioned group of registers that
 *          may be stored as CAT recovery data.  Only one table is needed
 *          to describe one crash event snapshot for the chip of a specific
 *          version.  An array of these tables describes the evolution of
 *          the information stored by various software releases.
 *
 *          Note: The last entry of this array is always a dummy terminator.
 *          It is identified by a NULL for the 'mapList' pointer.
 */
typedef struct
{
    ncp_uint32_t       formatRevision;
                       /*!< Primary key for identifying the information that
                        *   must be stored/retrieved from a CAT memory block.
                        *   This value is matched against the field 'formatRevision'
                        *   in the \link ncp_cat_memHdr_t \endlink struct by
                        *   the software that encodes or decodes the stored
                        *   CAT Memory block. */

    ncp_uint32_t       mapMergeTag;
                       /*!< Secondary key for identifying the information
                        *   that must be stored/retrieved from a CAT memory
                        *   block.  This value is matched against the field
                        *   'mapMergeTag' in the \link ncp_cat_memHdr_t \endlink
                        *   struct by the software that encodes or decodes
                        *   the stored CAT Memory block. */

    char               rteVer[NCP_CAT_RTE_VER_NAME_LEN];
                        /*!< RTE Release ID for which this may was last
                         *   created */

    char               chipVer[NCP_CAT_CHIP_VER_NAME_LEN];
                        /*!< NCP Chip version/revision for this map */

    ncp_uint32_t       registerCount;
                        /*!< Number of rows of information in the one or
                         *  more 'mapList' structures */

    ncp_cat_regMap_t  *mapList;
                        /*!< Array of structures describing blocks of NCP
                         *   registers to be loaded into or decoded from
                         *   the CAT memory block. */

} ncp_cat_regChip_t;


/*! @struct ncp_cat_mtmL1CacheHdr_t
 *  @brief  Standardized memory header for storing a block of data from
 *          from the NCP RTE / driver / application containing MTM L1
 *          cache information into the CAT recovery data
 *
 *  @details The header is placed at the beginning of a stored, MTM L1
 *           cache block of information within the CAT recovery data memory.
 *           It provides information that may be used after a power-cycle
 *           to determine whether the stored data is valid, as well as
 *           the amount of data stored.
 */
typedef struct
{
    ncp_uint32_t    cookie0;    /*!< First GM validation cookie */
    ncp_uint32_t    cookie1;    /*!< Second GM validation cookie */
    ncp_uint32_t    crcValue;   /*!< Computed checksum across the
                                 *   header and stored values */
    ncp_uint32_t    formatRevision;
                       /*!< Revision/version code that denotes the struct
                        *   of the following register list. */
    char            rteVer[NCP_CAT_RTE_VER_NAME_LEN];
                       /*!< RTE Release ID of the software that was used
                        *   to store this information */
    char            chipVer[NCP_CAT_CHIP_VER_NAME_LEN];
                       /*!< NCP Chip version/revision from which the
                        *   register information was read */
    ncp_uint32_t    wordCount;
                      /*!< Size of memory block that follows the header
                       *   rounded up to the specified number of 32-bit
                       *   words */
    ncp_uint32_t    regionCount;
                      /*!< Num of subsidiary regions actually stored in
                       *   the word array that follows this struct */
    ncp_uint32_t    pad2;
    ncp_uint32_t    pad3;
} ncp_cat_mtmL1CacheHdr_t;


/*! @struct ncp_cat_mtmL1CacheBlock_t
 *  @brief  Standardized memory block for data from the NCP RTE / driver /
 *          application containing MTM L1 cache information into the CAT
 *          recovery data
 *
 *  @details One or more of these blocks are CAT recovery data memory with
 *           the MTM L1 Cache data.  The format/version of these blocks of
 *           data tracks the format/version of the master MTM L1 Cache
 *           header, so separate tracking information will not be kept.
 *
 *           A block with zeroed counts, preceding a set of blocks with
 *           non-zero counts, will be used to group and name each MTM L1
 *           region.
 */
typedef struct
{
    char                name[32];
                        /*!< Human-readable Block name / ID */
    ncp_region_id_t     regionId;
                        /*!< Approximate NCP location of the values */
    ncp_uint32_t        numEntries;
                        /*!< number of entries of MTM L1 contained */
    ncp_uint32_t        wordsPerEntry;
                        /*!< number of words per entry of MTM L1 contained */
    ncp_uint32_t        wordCount;
                        /*!< Size of memory block that follows the header
                         *   rounded up to the specified number of 32-bit
                         *   words */
    ncp_uint32_t        custom0;
                        /*!< Byte offset to first of "Undocumented Registers"
                         *   Zero otherwise */
    ncp_uint32_t        pad0;
    ncp_uint32_t        pad1;
    ncp_uint32_t        pad2;
} ncp_cat_mtmL1CacheBlock_t;


/*! @struct ncp_cat_rawMemHdr_t
 *  @brief  Standardized memory header for storing a 'raw' block of
 *          data from the NCP RTE / driver / application along with
 *          the CAT recovery data
 *
 *  @details The header is placed at the beginning of a stored, 'raw'
 *           block of information within the CAT recovery data memory.
 *           It provides information that may be used after a power-cycle
 *           to determine whether the stored data is valid, as well as
 *           the amount of data stored.
 */
typedef struct
{
    ncp_uint32_t    cookie0;    /*!< First RAW validation cookie */
    ncp_uint32_t    cookie1;    /*!< Second RAW validation cookie */
    ncp_uint32_t    crcValue;   /*!< Computed checksum across the
                                 *   header and stored values */
    ncp_uint32_t    formatRevision;
                       /*!< Revision/version code that denotes the struct
                        *   of the following data. */
    char            rteVer[NCP_CAT_RTE_VER_NAME_LEN];
                       /*!< RTE Release ID of the software that was used
                        *   to store this information */
    char            chipVer[NCP_CAT_CHIP_VER_NAME_LEN];
                       /*!< NCP Chip version/revision from which the
                        *   register information was read */
    ncp_uint32_t    wordCount;
                      /*!< Size of memory block that follows the header
                       *   rounded up to the specified number of 32-bit
                       *   words */
    ncp_uint32_t    user0;      /*!< Example data 'ndx' value to
                                     distinguish between instances
                                     of the 'raw' structure. */
    ncp_uint32_t    user1;      /*!< Example data 'numEntries' */
    ncp_uint32_t    user2;      /*!< Example data 'wordsPerEntry' */
} ncp_cat_rawMemHdr_t;


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_CAT_COMMON_H_ */
