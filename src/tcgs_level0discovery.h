/////////////////////////////////////////////////////////////////////////////
/// tcgs_level0discovery.h
///
/// Structures and types used in TCG commands payload   
///
/// (c) Artem Zankovich, 2012
//////////////////////////////////////////////////////////////////////////////   

#ifndef _TCGS_STREAM_H
#define _TCGS_STREAM_H
   
#include "tcgs_types.h"

// Level 0 Descriptors
typedef enum
{
	FEATURE_RESERVED    = 0x0000,
	FEATURE_TPER        = 0x0001,
	FEATURE_LOCKING     = 0x0002,
	FEATURE_GEOMETRY    = 0x0003,
	FEATURE_ENTERPRISE  = 0x0100,
	FEATURE_OPAL1       = 0x0200,
	FEATURE_OPAL2       = 0x0203,
} TCGS_Level0Discovery_FeatureCode_t;

/*#define L0_TPER_FEATURE_DESCRIPTOR		0x0001
#define L0_LOCKING_FEATURE_DESCRIPTOR	0x0002
#define L0_GEOMETRY_FEATURE_DESCRIPTOR  0x0003
#define L0_ENT_A_FEATURE_DESCRIPTOR		0x0100
#define L0_OPAL_1_FEATURE_DESCRIPTOR    0x0200
#define L0_OPAL_2_FEATURE_DESCRIPTOR    0x0203
*/

typedef struct {
    uint32		length;
    uint16		versionMajor;
    uint16		versionMinor;
    uint8		reserved[8];
    uint8		vendor[32];
} __attribute__((packed)) TCGS_Level0Discovery_Header_t;

typedef struct {	   
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;
} __attribute__((packed)) TCGS_Level0Discovery_Feature_t;

typedef struct {
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;

    uint8		syncSupported				:1;
    uint8		asyncSupported				:1;
    uint8		ackSupported				:1;
    uint8		bufferManagementSupported	:1;
    uint8		streamingSupported			:1;
    uint8		reserved1					:1;
    uint8		comIdManagementSupported	:1;
    uint8		reserved2					:1;

    uint8		reserved3[11];
} __attribute__((packed)) TCGS_Level0Discovery_FeatureTper_t;

typedef struct {
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;

    uint8		lockingSupport				:1;
    uint8		lockingEnabled				:1;
    uint8		locked						:1;
    uint8		mediaEncryption				:1;
    uint8		MBREnabled					:1;
    uint8		MBRDone						:1;
    uint8		reserved1                   :2;

    uint8		reserved2[11];
} __attribute__((packed)) TCGS_Level0Discovery_FeatureLocking_t;

typedef struct {
    uint16 		code;
    uint8		reserved	                :4;
    uint8		version						:4;
    uint8		length;

    uint8		reserved1;
    uint8		reserved2[7];
    uint32		LogicalBlockSize;
    uint64		AlignmentGranularity;
    uint64		LowestAlignedLBA;
} __attribute__((packed)) TCGS_Level0Discovery_FeatureGeometry_t;

typedef struct {
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;

    uint16  	baseComID;
    uint16  	numberOfComIDs;
    uint8 		rangeCrossing				:1;
    uint8		reserved1					:7;
    uint8		reserved2[10];
} __attribute__((packed)) TCGS_Level0Discovery_FeatureOpal1_t;

typedef struct {
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;

    uint16  	baseComID;
    uint16  	numberOfComIDs;
    uint8 		rangeCrossing				:1;
	uint8		reserved1					:7;
    uint16		numberOfAdminsSupported;
    uint16		numberOfUsersSupported;
    uint8		initialPinSidIndicator;
    uint8		behaviorPinSinRevert;
    uint8		reserved2[5];
} __attribute__((packed)) TCGS_Level0Discovery_FeatureOpal2_t;

typedef struct {
    uint16 		code;
    uint8		reserved					:4;
    uint8		version						:4;
    uint8		length;

    uint16  	baseComID;
    uint16  	numberOfComIDs;
    uint8 		rangeCrossing				:1;
	uint8		reserved1					:7;
    uint8		reserved2[7];
} __attribute__((packed)) TCGS_Level0Discovery_FeatureEnterprise_t;

/*****************************************************************************
 * \brief Extracts the first Level 0 Discovery feature header from command
 * payload
 *
 * \par The function returns a pointer to internal buffer with the first
 * feature code from Level 0 Discovery command payload.
 *
 * \par TCGS_Level0Discovery shall be called before.
 *
 * @param[in]  payload      Pointer to payload returned by TCGS_Level0Discovery
 *
 * \return TCGS_Level0Discovery_Feature_t* pointer to feature header
 *
 * \see TCGS_Level0Discovery
 *****************************************************************************/
TCGS_Level0Discovery_Feature_t* TCGS_GetLevel0DiscoveryFirstFeatureHeader(TCGS_Level0Discovery_Header_t* payload);

TCGS_Level0Discovery_Feature_t* TCGS_GetLevel0DiscoveryNextFeatureHeader(TCGS_Level0Discovery_Header_t* payload, TCGS_Level0Discovery_Feature_t* featureHeader);

/*****************************************************************************
 * \brief Return Level 0 Discovery feature header with specified code
 *
 * \par The function returns a pointer to internal buffer with Level 0 Discovery
 * feature header data.
 *
 * \par TCGS_Level0Discovery shall be called before.
 *
 * @param[in]  payload      Pointer to payload returned by TCGS_Level0Discovery
 *
 * \return void* pointer to Level 0 Discovery feature header data, NULL is returned
 * when feature with specified code is not included in response
 *
 * \see TCGS_Level0Discovery
 *****************************************************************************/
TCGS_Level0Discovery_Feature_t* TCGS_GetLevel0DiscoveryFeatureHeader(
		TCGS_Level0Discovery_Header_t* payload, TCGS_Level0Discovery_FeatureCode_t featureCode);

#define TCGS_GetLevel0DiscoveryFeatureTperHeader(payload) ((TCGS_Level0Discovery_FeatureTper_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_TPER))

#define TCGS_GetLevel0DiscoveryFeatureLockingHeader(payload) ((TCGS_Level0Discovery_FeatureLocking_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_LOCKING))

#define TCGS_GetLevel0DiscoveryFeatureGeometryHeader(payload) ((TCGS_Level0Discovery_FeatureGeometry_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_GEOMETRY))

#define TCGS_GetLevel0DiscoveryFeatureEnterpriseHeader(payload) ((TCGS_Level0Discovery_FeatureEnterprise_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_ENTERPRISE))

#define TCGS_GetLevel0DiscoveryFeatureOpal1Header(payload) ((TCGS_Level0Discovery_FeatureOpal1_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_OPAL1))

#define TCGS_GetLevel0DiscoveryFeatureOpal2Header(payload) ((TCGS_Level0Discovery_FeatureOpal1_t*)TCGS_GetLevel0DiscoveryFeatureHeader(payload, FEATURE_OPAL2))

typedef enum {
    ENCODING_IS_INTEGER,    //set for integer values, byte value is considered otherwise
    ENCODING_IS_SIGNED,     //set for signed integer values
    ENCODING_REVERSED,      //set for byte values that are provided in reverse order
    ENCODING_CONTROL,       //set for control tokens
    ENCODING_OPTIMIZE_SIZE  //don't rely on provided length and try to select token of minimum length
} TCGS_EncodingFlags_t;

uint32 encode();

#endif //_TCGS_STREAM_H  
