#if !defined(_NCP_RELEASE_ID_H_)
#define _NCP_RELEASE_ID_H_

#include <ncp_sal_types.h>

#define NCP_RELEASE_ID_CONST   "NCP-1.3.0.064"

#define NCP_PACKED_RELEASE_ID  0x103000040

#if defined(NCP_RELEASE_VARIABLES)

const char *release_id="NCP-1.3.0.064";

const ncp_uint64_t packedId = 0x103000040;

#ifndef NCP_EXCLUDE_BUILD_DATE
const char *build_date="Thu Apr 2 18:06:35 CDT 2015";
#endif
#ifndef NCP_EXCLUDE_BUILD_NAME
const char *build_name="gsudhir";
#endif

#else

NCP_API const char *release_id;
NCP_API const char *build_date;
NCP_API const char *build_name;
NCP_API const ncp_uint64_t packedId;

#endif /* NCP_RELEASE_VARIABLES */

#endif /* _NCP_RELEASE_ID_H_ */
