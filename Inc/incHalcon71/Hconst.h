/*****************************************************************************
 * Hconst.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Definition of constants
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.162 $
 * $Date: 2005/06/30 08:36:19 $
 *
 */



#ifndef HCONST_H
#define HCONST_H

/**************************************************************************/
/* Messages:  Return values of HALCON procedures (no error)               */
/*            The values range from 1 to 999                              */
/*            The other messages are defined in HBase.h                   */
/* Attention: These messages are used only inside the HALCON library      */
/**************************************************************************/
#define H_MSG_OK          1       /* Normal return value                  */
/* Result of checking the runlength data of regions                       */
#define H_MSG_UNSCH       6       /* Runs are not sorted (old)            */
#define H_MSG_UNPCH       7       /* Runs are not packaged (old)          */
/* Data base                                                              */
#define H_MSG_EOR         8       /* No longer in use                     */
#define H_MSG_EOS         9       /* No longer in use                     */
/* Interaction                                                            */
#define H_MSG_MOUW        10      /* Mouse outside of the window          */
/* Result of checking the runlength data of regions                       */
#define H_MSG_UNSRL       11      /* Runs are not sorted                  */
#define H_MSG_UNPRL       12      /* Runs are not packaged                */
#define H_MSG_ILLINE      13      /* Line outside current image size      */
/**************************************************************************/


/**************************************************************************/
/* Return codes for errors                                                */
/**************************************************************************/
/* The values of errors range from 1000 to H_ERR_START_EXT                */
/* Values beyond H_ERR_START_EXT are reserved for user extensions         */
/**************************************************************************/



/*****************************************************************/
/* Groups of error numbers:                                      */
/*****************************************************************/
/*  General errorr:                                              */
/*    Parameter of HALCON operators                              */
/*      Type input parameter            12xx                     */
/*      Value input parameter           13xx                     */
/*      Number values input parameter   14xx                     */
/*      Number objects input parameter  15xx                     */
/*****************************************************************/
/*  Main part:                                                   */
/*    CORE                              2xxx                     */
/*      CORE0                           20xx                     */
/*      CORE1                           21xx                     */
/*      COREx                           22xx                     */
/*      HALCON scheduling               28xx                     */
/*    Image processing                  3xxx                     */
/*      Chords                          30xx                     */
/*      IPxx                            31xx                     */
/*      Contour                         32xx                     */
/*      XLD                             325x                     */
/*      Classification                  33xx                     */
/*      Morphology                      34xx                     */
/*      Runlength encoding              35xx                     */
/*      ShapeFrom                       385x                     */
/*      Kalman                          390x                     */
/*      Background estimation           82xx                     */
/*      OCR                             83xx                     */
/*      OCV                             835x                     */
/*      Function 1D                     837x                     */
/*      Camera calibration              84xx                     */
/*      Template matching               85xx                     */
/*      1D Bar code                     87xx                     */
/*      2D Bar code (old)               8800                     */
/*      2D Data code (new)              8820-88xx                */
/*    Data base                         4xxx                     */
/*    IOxx                              5xxx                     */
/*      General                         50xx                     */
/*      Window                          51xx                     */
/*      File                            52xx                     */
/*      Frame grabber                   53xx                     */
/*      Read picture                    55xx                     */
/*      Socket                          56xx                     */
/*****************************************************************/
/*  Further system components                                    */
/*    Memory management                 6xxx                     */
/*    Interfaces                                                 */
/*      General                         70xx                     */
/*      Prolog                          71xx                     */
/*      VLisp                           72xx                     */
/*      OPS5                            73xx                     */
/*      C                               74xx                     */
/*      RPC                             75xx                     */
/*      SWI                             76xx                     */
/*****************************************************************/
/*  Cxxx (e.g. CIPfeature)                                       */
/*      Cgpx                            80xx                     */
/*      Convol/Rank                     81xx                     */
/*****************************************************************/
/*  Misc                                                         */
/*      Misc                            90xx                     */
/*****************************************************************/

/* Control parameters */
/* Type input parameter 12xx */
#define H_ERR_WIPT1        1201 /* Wrong type of control parameter: 1 */
#define H_ERR_WIPT2        1202 /* Wrong type of control parameter: 2 */
#define H_ERR_WIPT3        1203 /* Wrong type of control parameter: 3 */
#define H_ERR_WIPT4        1204 /* Wrong type of control parameter: 4 */
#define H_ERR_WIPT5        1205 /* Wrong type of control parameter: 5 */
#define H_ERR_WIPT6        1206 /* Wrong type of control parameter: 6 */
#define H_ERR_WIPT7        1207 /* Wrong type of control parameter: 7 */
#define H_ERR_WIPT8        1208 /* Wrong type of control parameter: 8 */
#define H_ERR_WIPT9        1209 /* Wrong type of control parameter: 9 */
#define H_ERR_WIPT10       1210 /* Wrong type of control parameter: 10 */
#define H_ERR_WIPT11       1211 /* Wrong type of control parameter: 11 */
#define H_ERR_WIPT12       1212 /* Wrong type of control parameter: 12 */
#define H_ERR_WIPT13       1213 /* Wrong type of control parameter: 13 */
#define H_ERR_WIPT14       1214 /* Wrong type of control parameter: 14 */
#define H_ERR_WIPT15       1215 /* Wrong type of control parameter: 15 */
#define H_ERR_WIPT16       1216 /* Wrong type of control parameter: 16 */
#define H_ERR_WIPT17       1217 /* Wrong type of control parameter: 17 */
#define H_ERR_WIPT18       1218 /* Wrong type of control parameter: 18 */
#define H_ERR_WIPT19       1219 /* Wrong type of control parameter: 19 */
#define H_ERR_WIPT20       1220 /* Wrong type of control parameter: 20 */
/* Value input parameter 13xx */
#define H_ERR_WIPV1        1301 /* Wrong value of control parameter: 1 */
#define H_ERR_WIPV2        1302 /* Wrong value of control parameter: 2 */
#define H_ERR_WIPV3        1303 /* Wrong value of control parameter: 3 */
#define H_ERR_WIPV4        1304 /* Wrong value of control parameter: 4 */
#define H_ERR_WIPV5        1305 /* Wrong value of control parameter: 5 */
#define H_ERR_WIPV6        1306 /* Wrong value of control parameter: 6 */
#define H_ERR_WIPV7        1307 /* Wrong value of control parameter: 7 */
#define H_ERR_WIPV8        1308 /* Wrong value of control parameter: 8 */
#define H_ERR_WIPV9        1309 /* Wrong value of control parameter: 9 */
#define H_ERR_WIPV10       1310 /* Wrong value of control parameter: 10 */
#define H_ERR_WIPV11       1311 /* Wrong value of control parameter: 11 */
#define H_ERR_WIPV12       1312 /* Wrong value of control parameter: 12 */
#define H_ERR_WIPV13       1313 /* Wrong value of control parameter: 13 */
#define H_ERR_WIPV14       1314 /* Wrong value of control parameter: 14 */
#define H_ERR_WIPV15       1315 /* Wrong value of control parameter: 15 */
#define H_ERR_WIPV16       1316 /* Wrong value of control parameter: 16 */
#define H_ERR_WIPV17       1317 /* Wrong value of control parameter: 17 */
#define H_ERR_WIPV18       1318 /* Wrong value of control parameter: 18 */
#define H_ERR_WIPV19       1319 /* Wrong value of control parameter: 19 */
#define H_ERR_WIPV20       1320 /* Wrong value of control parameter: 20 */
#define H_ERR_WCOMP        1350 /* Wrong value of component */
#define H_ERR_WGCOMP       1351 /* Wrong value of gray value component */
/* Number of values input parameter 14xx */
#define H_ERR_WIPN1        1401 /* Wrong number of values of ctrl.par.: 1 */
#define H_ERR_WIPN2        1402 /* Wrong number of values of ctrl.par.: 2 */
#define H_ERR_WIPN3        1403 /* Wrong number of values of ctrl.par.: 3 */
#define H_ERR_WIPN4        1404 /* Wrong number of values of ctrl.par.: 4 */
#define H_ERR_WIPN5        1405 /* Wrong number of values of ctrl.par.: 5 */
#define H_ERR_WIPN6        1406 /* Wrong number of values of ctrl.par.: 6 */
#define H_ERR_WIPN7        1407 /* Wrong number of values of ctrl.par.: 7 */
#define H_ERR_WIPN8        1408 /* Wrong number of values of ctrl.par.: 8 */
#define H_ERR_WIPN9        1409 /* Wrong number of values of ctrl.par.: 9 */
#define H_ERR_WIPN10       1410 /* Wrong number of values of ctrl.par.: 10 */
#define H_ERR_WIPN11       1411 /* Wrong number of values of ctrl.par.: 11 */
#define H_ERR_WIPN12       1412 /* Wrong number of values of ctrl.par.: 12 */
#define H_ERR_WIPN13       1413 /* Wrong number of values of ctrl.par.: 13 */
#define H_ERR_WIPN14       1414 /* Wrong number of values of ctrl.par.: 14 */
#define H_ERR_WIPN15       1415 /* Wrong number of values of ctrl.par.: 15 */
#define H_ERR_WIPN16       1416 /* Wrong number of values of ctrl.par.: 16 */
#define H_ERR_WIPN17       1417 /* Wrong number of values of ctrl.par.: 17 */
#define H_ERR_WIPN18       1418 /* Wrong number of values of ctrl.par.: 18 */
#define H_ERR_WIPN19       1419 /* Wrong number of values of ctrl.par.: 19 */
#define H_ERR_WIPN20       1420 /* Wrong number of values of ctrl.par.: 20 */
/* Number of input objects 15xx */
#define H_ERR_IONTB        1500 /* Number of input objects too big */
#define H_ERR_WION1        1501 /* Wrong number of values of object par.: 1 */
#define H_ERR_WION2        1502 /* Wrong number of values of object par.: 2 */
#define H_ERR_WION3        1503 /* Wrong number of values of object par.: 3 */
#define H_ERR_WION4        1504 /* Wrong number of values of object par.: 4 */
#define H_ERR_WION5        1505 /* Wrong number of values of object par.: 5 */
#define H_ERR_WION6        1506 /* Wrong number of values of object par.: 6 */
#define H_ERR_WION7        1507 /* Wrong number of values of object par.: 7 */
#define H_ERR_WION8        1508 /* Wrong number of values of object par.: 8 */
#define H_ERR_WION9        1509 /* Wrong number of values of object par.: 9 */
#define H_ERR_OONTB        1510 /* Number of output objects too big */

/* Error codes concerniong the HALCON core */
#define H_ERR_WNP          2000 /* Wrong specification of parameter (error in 
                                   file: xxx.def) */
#define H_ERR_HONI         2001 /* Initialize Halcon: 
                                   reset_obj_db(Width,Height,Components) */
#define H_ERR_WRKNN        2002 /* Used number of symbolic object names 
                                   too big */

/* Error codes concerning licensing */
#define H_ERR_NO_LICENSE   2003 /* No license found */
#define H_ERR_NO_LS_SERVER 2004 /* Lost connection to license server */
#define H_ERR_NO_MODULES   2005 /* No modules in license (no VENDOR_STRING) */
#define H_ERR_NO_LIC_OPER  2006 /* No license for this operator */
#define H_ERR_FLEX_LM_BAD_TZ          2007 /* Time zone offset from GMT is 
                                              > 24 hours */
#define H_ERR_FLEX_LM_BADPLATFORM     2008 /* Vendor keys do not support this 
                                              platform */
#define H_ERR_LM_BADKEYDATA           2009 /* Bad vendor keys */
#define H_ERR_FLEX_LM_BADVENDORDATA   2010 /* Unknown vendor key type */
#define H_ERR_FLEX_LM_CANTMALLOC      2011 /* malloc() call failed */
#define H_ERR_FLEX_LM_EXPIREDKEYS     2012 /* Vendor keys have expired */
#define H_ERR_FLEX_LM_FUNCNOTAVAIL    2013 /* Second call to lc_inti() 
                                              (multiple jobs), and vendore 
                                              keys do not support multiple 
                                              jobs */
#define H_ERR_FLEX_LM_NOKEYDATA       2014 /* Vendor key data not supplied */
#define H_ERR_FLEX_LM_LIBRARYMISMATCH 2015 /* lmclient.h/liblmgr.a version 
                                              mismatch */
#define H_ERR_FLEX_LM_NONETWORK       2016 /* Networking software not 
                                              available on this machine */
#define H_ERR_FLEX_LM_OLDVENDORDATA   2017 /* Old vendor keys supplied */
#define H_ERR_FLEX_LM_BADCODE         2018 /* License key in license file does
                                              not match other data in file */
#define H_ERR_FLEX_LM_BADHANDSHAKE    2019 /* Encryption handshake with daemon
                                              failed */
#define H_ERR_FLEX_LM_BADPARAM        2020 /* 'key' structure is incorrect 
                                              type, or feature == NULL, 
                                              or num_licenses == 0 */
#define H_ERR_FLEX_LM_BADSYSDATE      2021 /* System clock has been set back */
#define H_ERR_FLEX_LM_BAD_VERSION     2022 /* Version argument is invalid 
                                              floating point format */
#define H_ERR_FLEX_LM_BUSYNEWSERV     2023 /* License server busy starting 
                                              another copy of itself */
#define H_ERR_FLEX_LM_CANTCONNECT     2024 /* Cannot establish a connection 
                                              with a license server */
#define H_ERR_FLEX_LM_FEATQUEUE       2025 /* Feature is queued. lc_status 
                                              will determine when it is 
                                              available */
#define H_ERR_FLEX_LM_FUNC_NOT_AVAIL  2026 /* Vendor keys do not support this 
                                              function */
#define H_ERR_FLEX_LM_LOCALFILTER     2027 /* Checkout request filtered by the
                                              vendor-defined filter routine */
#define H_ERR_FLEX_LM_MAXLIMIT        2028 /* Checkout exceeds MAX specified 
                                              in options file */
#define H_ERR_FLEX_LM_MAXUSERS        2029 /* All licenses in use */
#define H_ERR_FLEX_LM_NO_SERVER_IN_FILE 2030 /* No license server specified 
                                                for counted license */
#define H_ERR_FLEX_LM_NOFEATURE       2031 /* Can not find feature in the 
                                              license file */
#define H_ERR_FLEX_LM_NOSERVSUPP      2032 /* Server has different license 
                                              file than client - client's 
                                              license has feature, but 
                                              server's does not */
#define H_ERR_FLEX_LM_OLDVER          2033 /* License file does not support 
                                              a version this new */
#define H_ERR_FLEX_LM_PLATNOTLIC      2034 /* This platform not authorized by 
                                              license - running on platform 
                                              not included in PLATFORMS list */
#define H_ERR_FLEX_LM_SERVBUSY        2035 /* License server busy */
#define H_ERR_FLEX_LM_NOCONFFILE      2036 /* Could not find license.dat */

#define H_ERR_FLEX_LM_BADFILE           2037 /* Invalid license file syntax */
#define H_ERR_FLEX_LM_NOSERVER          2038 /* Cannot connect to a license 
                                                server */
#define H_ERR_FLEX_LM_NOSERVICE         2039 /* No TCP "license" service 
                                                exists */
#define H_ERR_FLEX_LM_NOSOCKET          2040 /* No socket connection to 
                                                license manager server */
#define H_ERR_FLEX_LM_NOTTHISHOST       2041 /* Invalid host */
#define H_ERR_FLEX_LM_LONGGONE          2042 /* Feature has expired */
#define H_ERR_FLEX_LM_BADDATE           2043 /* Invalid date format in license
                                                file */
#define H_ERR_FLEX_LM_BADCOMM           2044 /* Invalid returned data from 
                                                license server */
#define H_ERR_FLEX_LM_BADHOST           2045 /* Cannot find SERVER hostname in
                                                network database */
#define H_ERR_FLEX_LM_CANTREAD          2046 /* Cannot read data from license 
                                                server */
#define H_ERR_FLEX_LM_CANTWRITE         2047 /* Cannot write data to license 
                                                server */
#define H_ERR_FLEX_LM_SELECTERR         2048 /* Error in select system call */
#define H_ERR_FLEX_LM_CHECKINBAD        2049 /* Feature checkin failure 
                                                detected at license */
#define H_ERR_FLEX_LM_USERSQUEUED       2050 /* Users are queued for this 
                                                feature */
#define H_ERR_FLEX_LM_SERVLONGGONE      2051 /* License server does not 
                                                support this version of this 
                                                feature */
#define H_ERR_FLEX_LM_TOOMANY           2052 /* Request for more licenses than
                                                this feature supports */
#define H_ERR_FLEX_LM_CANTREADKMEM      2053 /* Cannot read /dev/kmem */
#define H_ERR_FLEX_LM_CANTREADVMUNIX    2054 /* Cannot read /vmunix */
#define H_ERR_FLEX_LM_CANTFINDETHER     2055 /* Cannot find ethernet device */
#define H_ERR_FLEX_LM_NOREADLIC         2056 /* Cannot read license file */
#define H_ERR_FLEX_LM_TOOEARLY          2057 /* Feature not yet available */
#define H_ERR_FLEX_LM_NOSUCHATTR        2058 /* No such attribute */
#define H_ERR_FLEX_LM_CLOCKBAD          2059 /* Clock difference too large 
                                                between client and server */
#define H_ERR_FLEX_LM_FEATCORRUPT       2060 /* Feature database corrupted in
                                                daemon */
#define H_ERR_FLEX_LM_BADFEATPARAM      2061 /* Duplicate selection mismatch 
                                                for this feature */
#define H_ERR_FLEX_LM_FEATEXCLUDE       2062 /* User/host on EXCLUDE list for 
                                                feature */
#define H_ERR_FLEX_LM_FEATNOTINCLUDE    2063 /* User/host not on INCLUDE list 
                                                for feature */
#define H_ERR_FLEX_LM_NEVERCHECKOUT     2064 /* Feature was never checked 
                                                out */
#define H_ERR_FLEX_LM_BADKEYDATA        2065 /* Invalid FLEXlm key data 
                                                supplied */
#define H_ERR_FLEX_LM_NOCLOCKCHECK      2066 /* Clock setting check not 
                                                available in daemon */
#define H_ERR_FLEX_LM_DATE_TOOBIG       2067 /* Date too late for binary 
                                                format */
#define H_ERR_FLEX_LM_NOFLEXLMINIT      2068 /* FLEXlm not initialized */
#define H_ERR_FLEX_LM_NOSERVRESP        2069 /* Server did not respond to 
                                                message */
#define H_ERR_FLEX_LM_CHECKOUTFILTERED  2070 /* Request rejected by vendor 
                                                defined filter */
#define H_ERR_FLEX_LM_NOFEATSET         2071 /* No FEATURESET line present in 
                                                license file */
#define H_ERR_FLEX_LM_BADFEATSET        2072 /* Incorrect FEATURESET line in 
                                                license file */
#define H_ERR_FLEX_LM_CANTCOMPUTEFEATSET 2073 /* Cannot compute FEATURESET
                                                 line */
#define H_ERR_FLEX_LM_SOCKETFAIL        2074 /* socket() call failed */
#define H_ERR_FLEX_LM_SETSOCKFAIL       2075 /* setsockopt() failed */
#define H_ERR_FLEX_LM_BADCHECKSUM       2076 /* Message checksum failure */
#define H_ERR_FLEX_LM_SERVNOREADLIC     2077 /* Cannot read license file from 
                                                server */
#define H_ERR_FLEX_LM_NOTLICADMIN       2078 /* Not a license administrator */
#define H_ERR_FLEX_LM_REMOVETOOSOON     2079 /* lmremove request too soon */
#define H_ERR_FLEX_LM_ENDPATH           2080 /* Attempt to read beyond the end
                                                of LF path */
#define H_ERR_FLEX_LM_VMS_SETIMR_FAILED 2081 /* SYS$SETIMR call failed */
#define H_ERR_FLEX_LM_INTERNAL_ERROR    2082 /* Internal FLEXlm Erro - Please 
                                                report to Globetrotter 
                                                Software */
#define H_ERR_FLEX_LM_NOADMINAPI        2083 /* FLEXadmin API functions not 
                                                avilable */
#define H_ERR_FLEX_LM_BADPKG            2084 /* Invalid PACKAGE line in 
                                                license file */
#define H_ERR_FLEX_LM_SERVOLDVER        2085 /* Server FLEXlm version older 
                                                than client's */
#define H_ERR_FLEX_LM_USER_BASED        2086 /* Incorrect number of USERS/HOSTS
                                                INCLUDED in options file */
#define H_ERR_FLEX_LM_NOSERVCAP         2087 /* Server doesn't support this 
                                                request */
#define H_ERR_FLEX_LM_OBJECTUSED        2088 /* This license object already in
                                                use */

#define H_ERR_FLEX_LM_FUTURE_FILE       2089 /* Future license file format */
#define H_ERR_FLEX_LM_SERVER_REMOVED    2090 /* Feature removed during 
                                                lmreread */
#define H_ERR_FLEX_LM_POOL              2091 /* This feature is available in a
                                                different license pool */
#define H_ERR_FLEX_LM_NOT_THIS_HOST     2092 /* Network connect to THIS_HOST 
                                                failed */
#define H_ERR_FLEX_LM_HOSTDOWN          2093 /* Server node is down or not 
                                                responding */
#define H_ERR_FLEX_LM_VENDOR_DOWN       2094 /* The desired vendor daemon is 
                                                down */
#define H_ERR_FLEX_LM_BADDECFILE        2095 /* The decimal format license is 
                                                typed incorrectly */
#define H_ERR_FLEX_LM_RESVFOROTHERS     2096 /* All licenses are reserved for 
                                                others */
#define H_ERR_FLEX_LM_TSOK_ERR          2097 /* Terminal Server remote client 
                                                not allowed */
#define H_ERR_FLEX_LM_BORROW_TOOLONG    2098 /* Cannot borrow that long */
#define H_ERR_FLEX_LM_SERVER_MAXED_OUT  2099 /* License server out of network 
                                                connections */
#define H_ERR_FLEX_LM_NODONGLE          2300 /* Dongle not attached, or can't 
                                                read dongle */
#define H_ERR_FLEX_LM_NODONGLEDRIVER    2301 /* Missing Dongle Driver */
#define H_ERR_FLEX_LM_FLEXLOCK2CKOUT    2302 /* FLEXlock checkouts attempted */
#define H_ERR_FLEX_LM_SIGN_REQ          2303 /* SIGN= attribute required */
#define H_ERR_FLEX_LM_NOCROSUPPORT      2304 /* CRO not supported for this 
                                                platform */
#define H_ERR_FLEX_LM_BORROW_LINGER_ERR 2305 /* BORROW failed */
#define H_ERR_FLEX_LM_BORROW_EXPIRED    2306 /* BORROW period has expired */
#define H_ERR_FLEX_LM_FLOATOK_ONEHOSTID 2307 /* FLOAT_OK license must have 
                                                exactly one dongle hostid */




/* Error codes concerning the HALCON core, 2100..2199 */
#define H_ERR_WOOPI        2100 /* Wrong index for output object parameter */
#define H_ERR_WIOPI        2101 /* Wrong index for input object parameter*/
#define H_ERR_WOI          2102 /* Wrong index for image object */
#define H_ERR_WRCN         2103 /* Wrong number region/image component */
#define H_ERR_WRRN         2104 /* Wrong relation name */
#define H_ERR_AUDI         2105 /* Access to undefined gray value component*/
#define H_ERR_WIWI         2106 /* Wrong image width */
#define H_ERR_WIHE         2107 /* Wrong image height */
#define H_ERR_ICUNDEF      2108 /* Undefined gray value component */

/* Error codes concerning the HALCON core (+ Language interfaces),
   2200..2299 */
#define H_ERR_IDBD         2200 /* Inconsistent data of data base (typing) */
#define H_ERR_WICPI        2201 /* Wrong index for input control parameter */
#define H_ERR_DBDU         2202 /* Data of data base not defined 
                                   (internal error) */
#define H_ERR_PNTL         2203 /* Number of operators too big */
#define H_ERR_UEXTNI       2205 /* User extension not properly installed */
#define H_ERR_NPTL         2206 /* Number of packages too large */
#define H_ERR_NSP          2207 /* No such package installed */

/* HALCON agents/scheduler (parallel processing HALCON operators),
   2800..2999 */
#define H_ERR_GV_WA        2830 /* Wrong access to global variable */
#define H_ERR_GV_NC        2831 /* Used global variable does not exist */
#define H_ERR_GV_NG        2832 /* Used global variable not accessible via 
                                   GLOBAL_ID */

#define H_ERR_HM_NT        2835 /* Halcon server to terminate is still 
                                   working on a job */

#define H_ERR_HM_NA        2837 /* No such HALCON software agent */
#define H_ERR_AG_CN        2838 /* Hardware check for parallelization not 
                                   possible on a single-processor machine */
#define H_ERR_AG_NC        2839 /* (Seq.) HALCON does not support parallel 
                                   hardware check (use Parallel HALCON 
                                   instead) */
#define H_ERR_AG_IN        2840 /* Initialization of agent failed */
#define H_ERR_AG_NT        2841 /* Termination of agent failed */
#define H_ERR_AG_HW        2842 /* Inconsistent hardware description file */
#define H_ERR_AG_II        2843 /* Inconsistent agent information file */
#define H_ERR_AG_IK        2844 /* Inconsistent agent knowledge file */
#define H_ERR_AG_WV        2845 /* The file with the parallelization 
                                   information does not match to the 
                                   currently HALCON version/revision */
#define H_ERR_AG_WH        2846 /* The file with the parallelization 
                                   information does not match to the 
                                   currently used machine */
#define H_ERR_AG_KC        2847 /* Inconsistent knowledge base of HALCON 
                                   software agent */
#define H_ERR_AG_CT        2848 /* Unknown communication type */
#define H_ERR_AG_MT        2849 /* Unknown message type for HALCON software 
                                   agent */
#define H_ERR_AG_WK        2850 /* Error while saving the parallelization 
                                   knowledge */
#define H_ERR_AG_WW        2851 /* Wrong type of work information */
#define H_ERR_AG_WA        2852 /* Wrong type of application information */
#define H_ERR_AG_WE        2853 /* Wrong type of experience information */
#define H_ERR_AG_NU        2854 /* Unknown name of HALCON software agent */
#define H_ERR_AG_NE        2855 /* Unknown name and communication address of 
                                   HALCON software agent */
#define H_ERR_AG_RR        2856 /* cpu representative (HALCON software agent) 
                                   not reachable */
#define H_ERR_AG_CR        2857 /* cpu refuses work */
#define H_ERR_AG_RN        2858 /* Description of scheduling resource 
                                   not found */
#define H_ERR_AG_TILT      2859 /* Not accessible function of HALCON 
                                   software agent */

#define H_ERR_WRT          2860 /* Wrong type: HALCON scheduling resource */
#define H_ERR_WRS          2861 /* Wrong state: HALCON scheduling resource */
#define H_ERR_UNKPT        2862 /* Unknown parameter type: 
                                   HALCON scheduling resource */
#define H_ERR_UNKPARVAL    2863 /* Unknown parameter value: 
                                   HALCON scheduling resource */
#define H_ERR_CTRL_WPP     2864 /* Wrong post processing of 
                                   control parameter */

#define H_ERR_GETTI        2867 /* Error while trying to get time */
#define H_ERR_GETCPUNUM    2868 /* Error while trying to get the number 
                                   of processors */
#define H_ERR_TMPFNF       2869 /* Error while accessing temporary file */

#define H_ERR_PTHRD_CR     2970 /* Creation of pthread failed */
#define H_ERR_PTHRD_DT     2971 /* pthread-detach failed */
#define H_ERR_PTHRD_JO     2972 /* pthread-join failed */
#define H_ERR_PTHRD_MI     2973 /* Initialization of mutex variable failed */
#define H_ERR_PTHRD_MD     2974 /* Deletion of mutex variable failed */
#define H_ERR_PTHRD_ML     2975 /* Lock of mutex variable failed */
#define H_ERR_PTHRD_MU     2976 /* Unlock of mutex variable failed */
#define H_ERR_PTHRD_CS     2977 /* Failed to signal pthread condition var. */
#define H_ERR_PTHRD_CW     2978 /* Failed to wait for pthread cond. var. */
#define H_ERR_PTHRD_CI     2979 /* Failed to init pthread condition var. */
#define H_ERR_PTHRD_CD     2980 /* Failed to destroy pthread condition var.*/
#define H_ERR_PTHRD_CH     2981 /* Failed to give free a handle via 
                                   CloseHandle */

#define H_ERR_DCDG_FLE     2985 /* 'Free list' is empty while scheduling */

#define H_ERR_MSG_PNCI     2990 /* Communication partner not checked in */
#define H_ERR_MSG_CSAI     2991 /* The communication system can't be started 
                                   while running */
#define H_ERR_MSG_CSNI     2992 /* Communication partner not checked in */

/* Runlength data 3000..3099 */
#define H_ERR_ROOIMA       3011 /* Region (partially) outside of the 
                                   definition range of the image */
#define H_ERR_RIEI         3012 /* Intersected definition range 
                                   region/image empty */
#define H_ERR_EDEF         3013 /* Image with empty definition range */
#define H_ERR_IIEI         3014 /* No common image point of two images */
#define H_ERR_FLTS         3015 /* Wrong region for image (first row < 0) */
#define H_ERR_LLTB         3016 /* Wrong region for image 
                                   (column in last row >= image width) */
#define H_ERR_UENOI        3017 /* Number of images unequal in input pars. */
#define H_ERR_HTS          3018 /* Image height too small */
#define H_ERR_WTS          3019 /* Image width too small */
#define H_ERR_CHSEG        3020 /* Internal error: 
                                   Multiple call of HRLInitSeg() */
#define H_ERR_RLSEG1       3021 /* Internal error: 
                                   HRLSeg() not initialized */
#define H_ERR_WGAUSSM      3022 /* Wrong size of filter for Gauss */
#define H_ERR_FSEIS        3033 /* Filter size exceeds image size */

/* Cordinates */
#define H_ERR_ROWTB        3040 /* Row value of a coordinate > 2^16 */
#define H_ERR_ROWTS        3041 /* Row value of a coordinate < -2^16 */
#define H_ERR_COLTB        3042 /* Column value of a coordinate > 2^16 */
#define H_ERR_COLTS        3043 /* Column value of a coordinate < -2^16 */

/* Error codes concerning image processing, 31xx */
#define H_ERR_WRTHR        3100 /* Wrong segmentation threshold */
#define H_ERR_UNKF         3101 /* Unknown attribute of a region */
#define H_ERR_UNKG         3102 /* Unknown attribute of a gray value */
#define H_ERR_EINCC        3103 /* Internal error in HContCut */
#define H_ERR_EINCP1       3104 /* Error in HContToPol: 
                                   distance of points too big */
#define H_ERR_EINCP2       3105 /* Error in HContToPol: contour too long */
#define H_ERR_TMR          3106 /* Too many rows (IPImageTransform) */
#define H_ERR_SFZ          3107 /* Scaling factor = 0.0 (IPImageScale) */
#define H_ERR_OOR          3108 /* Wrong range in transformation matrix */
#define H_ERR_NEF          3109 /* Internal error in IPvvf: no element free */
#define H_ERR_NOOB         3110 /* Number of input objects is zero */
#define H_ERR_EMPOB        3111 /* At least one input object has an 
                                   empty region */
#define H_ERR_NPOT         3112 /* Operation allowed for rectangular 
                                   images 2**n only */
#define H_ERR_TMEP         3113 /* Too many relevant points (IPHysterese) */
#define H_ERR_LTB          3114 /* Number of labels in image too big */
#define H_ERR_NNLA         3115 /* No labels with negative values allowed */
#define H_ERR_WFS          3116 /* Wrong filter size (too small ?) */
#define H_ERR_IWDS         3117 /* Images with different image size */
#define H_ERR_IWTL         3118 /* Target image too wide or too far 
                                   on the right */
#define H_ERR_IWTS         3119 /* Target image too narrow or too far 
                                   on the left */
#define H_ERR_IHTL         3120 /* Target image too high or too far down */
#define H_ERR_IHTS         3121 /* Target image too low or too far up */
#define H_ERR_DNOC         3122 /* Number of channels in the input parameters 
                                   are different */
#define H_ERR_WRCFAFLT     3123 /* Wrong color filter array type */
#define H_ERR_WRCFAINT     3124 /* Wrong color filter array interpolation */
#define H_ERR_NO_AFFTRANS  3125 /* Homogeneous matrix does not represent an 
                                   affine transformation */
#define H_ERR_INPNOBDRY    3126 /* Inpainting region too close to the image
                                   border */

/* Coocurrence */
#define H_ERR_COWTS        3131 /* Coocurrence Matrix: 
                                   Too little columns for quantisation */
#define H_ERR_COHTS        3132 /* Coocurrence Matrix: 
                                   Too little rows for quantisation */
#define H_ERR_NUM_COLMN    3133 /* Wrong number of columns */
#define H_ERR_NUM_LINES    3134 /* Wrong number of rows */
#define H_ERR_OVL          3135 /* Number has too many digits */
#define H_ERR_NOT_SYM      3136 /* Matrix is not symmetric */
#define H_ERR_NUM_COLS     3137 /* Matrix is too big */
#define H_ERR_SYNTAX       3138 /* Wrong structure of file */
#define H_ERR_MISSING      3139 /* Less than 2 matrices */
#define H_ERR_COOC_MEM     3140 /* Not enough memory */
#define H_ERR_NO_FILE      3141 /* Can not read the file */
#define H_ERR_FILE_WR      3142 /* Can not open file for writing */
#define H_ERR_NUM_LUCOLS   3143 /* Too many lookup table colors */

#define H_ERR_WNOLI        3145 /* Too many Hough points (lines) */
#define H_ERR_DITS         3146 /* Target image has got wrong height 
                                   (not big enough) */
#define H_ERR_WINTM        3147 /* Wrong interpolation mode */
#define H_ERR_THICK_NK     3148 /* Region not compact or not connected */


/* Laws */
#define H_ERR_WIND3        3170 /* Wrong filter index for filter size 3 */
#define H_ERR_WIND5        3171 /* Wrong filter index for filter size 5 */
#define H_ERR_WIND7        3172 /* Wrong filter index for filter size 7 */
#define H_ERR_WLAWSS       3173 /* Wrong filter size; only 3/5/7 */

/* Noise estimation */
#define H_ERR_NE_NPTS      3175 /* Number of suitable pixels too small to
                                   reliably estimate the noise */

/* Contour */
#define H_ERR_WNEE         3200 /* Different number of entries/exits 
                                   in HContCut */

/* XLD */
#define H_ERR_XLDWT        3250 /* Wrong XLD type */
#define H_ERR_XLD_CTL      3251 /* Contour too long for representation */
#define H_ERR_XLD_RPF      3252 /* Border point is set to FG */
#define H_ERR_XLD_MCL      3253 /* Maximum contour length exceeded */
#define H_ERR_XLD_MCN      3254 /* Maximum number of contours exceeded */
#define H_ERR_XLD_CTS      3255 /* Contour too short for fetch_angle_xld */
#define H_ERR_XLD_CRD      3256 /* Regression parameters of contours 
                                   already computed */
#define H_ERR_XLD_CRND     3257 /* Regression parameters of contours not 
                                   yet entered! */

#define H_ERR_DBXC         3258 /* Data base: XLD object has been deleted */
#define H_ERR_DBWXID       3259 /* Data base: Object has no XLD-ID */

#define H_ERR_XLD_WNP      3260 /* Wrong number of contour points allocated */
#define H_ERR_XLD_CAND     3261 /* Contour attribute not defined */

#define H_ERR_FIT_ELLIPSE  3262 /* Ellipse fitting failed */
#define H_ERR_FIT_CIRCLE   3263 /* Circle fitting failed */
#define H_ERR_FIT_CLIP     3264 /* All points classified as outliers
                                   (ClippingFactor too small) */

#define H_ERR_NWF          3275 /* No ARC/INFO world file */
#define H_ERR_NAIGF        3276 /* No ARC/INFO generate file */

#define H_ERR_XLD_ISOL_POINT 3290 /* Isolated point while contour merging */

/* Classification */
#define H_ERR_SESF         3300 /* Syntax error in file for training */
#define H_ERR_TMFE         3301 /* Maximum number of attributes per example 
                                   exceeded */
#define H_ERR_OPSF         3302 /* Not possible to open file for training */
#define H_ERR_TMSS         3303 /* Too many data sets for training */
#define H_ERR_WSKEY        3304 /* Wrong key for data for training */
#define H_ERR_TMSAM        3305 /* Too many examples for one data set for 
                                   training */
#define H_ERR_TMCLS        3306 /* Too many classes */
#define H_ERR_TMBOX        3307 /* Maximum number of cuboids exceeded */
#define H_ERR_OPCF         3308 /* Not possible to open classificator's file */
#define H_ERR_SCLA         3309 /* Error while saving the classificator */
#define H_ERR_OPF          3310 /* Not possible to open protocol file */
#define H_ERR_CLEX         3311 /* Classificator with this name is already 
                                   existent */
#define H_ERR_TMCLA        3312 /* Maximum number of classificators exceeded */
#define H_ERR_CNTL         3313 /* Name of classificator is too long, >= 20 */
#define H_ERR_CLNNF        3314 /* Classificator with this name is not 
                                   existent */
#define H_ERR_NCCLA        3315 /* Current classificator is not defined */
#define H_ERR_CLASS2_ID    3316 /* Wrong id in classification file */
#define H_ERR_CLASS2_VERS  3317 /* Wrong verion number in classification 
                                   file */

#define H_ERR_MLP_UNKOUTFUNC  3350 /* Unknown output function */
#define H_ERR_MLP_NOT01ENC    3351 /* Target not in 0-1 encoding */
#define H_ERR_MLP_NOTRAINDATA 3352 /* No training samples stored in the 
                                      classifier */
#define H_ERR_MLP_NOTRAINFILE 3353 /* Not a valid training sample file */
#define H_ERR_MLP_WRTRAINVERS 3354 /* Wrong training sample file version */
#define H_ERR_MLP_WRSMPFORMAT 3355 /* Wrong training sample format */
#define H_ERR_MLP_NOCLASSIF   3356 /* MLP is not a classifier */
#define H_ERR_MLP_NOCLASSFILE 3357 /* Not a valid MLP file */
#define H_ERR_MLP_WRCLASSVERS 3358 /* Wrong MLP file version */
#define H_ERR_MLP_WRNUMCHAN   3359 /* Wrong number of channels */
#define H_ERR_MLP_WRNUMPARAM  3360 /* Wrong number of MLP parameters */


/* Morphology */
#define H_ERR_ROTNR        3401 /* Wrong rotation number */
#define H_ERR_GOL          3402 /* Wrong letter for Golay element */
#define H_ERR_BEZ          3403 /* Wrong reference point */
#define H_ERR_ITER         3404 /* Wrong number of iterations */
#define H_ERR_MOSYS        3405 /* Mophology: system error */
#define H_ERR_ART          3406 /* Wrong type of boundary */
#define H_ERR_OBJI         3407 /* Morphology: Wrong number of input obj. */
#define H_ERR_OBJO         3408 /* Morphology: Wrong number of output obj. */
#define H_ERR_PARI         3409 /* Morphology: Wrong number of input 
                                   control parameter */
#define H_ERR_PARO         3410 /* Morphology: Wrong number of output 
                                   control parameter */
#define H_ERR_SELC         3411 /* Morphology: Struct. element is infinite */
#define H_ERR_WRNSE        3412 /* Morphology: Wrong name for struct. elem. */


/* Runlength encoding, 35xxx */
#define H_ERR_WRRLN1       3500 /* Wrong number of run length rows (chords): 
                                   smaller than 0 */
#define H_ERR_WRRLN2       3513 /* Number of chords too big */
#define H_ERR_WRRLL        3502 /* Run length row with negative length */
#define H_ERR_RLLTB        3503 /* Run length row >= image height */
#define H_ERR_RLLTS        3504 /* Run length row < 0 */
#define H_ERR_RLCTB        3505 /* Run length column >= image width */
#define H_ERR_RLCTS        3506 /* Lauflaengenspalte < 0 */
#define H_ERR_CHLTB        3507 /* For CHORD_TYPE: Number of row too big */
#define H_ERR_CHLTS        3508 /* For CHORD_TYPE: Number of row too small */
#define H_ERR_CHCTB        3509 /* For CHORD_TYPE: Number of column too big */
#define H_ERR_MRLE         3510 /* Exceeding the maximum number of run lengths
                                   while automatical expansion */
#define H_ERR_ICCOMPL      3511 /* Region->compl neither TRUE/FALSE */
#define H_ERR_RLEMAX       3512 /* Region->max_num < Region->num */
#define H_ERR_WRRLN3       3513 /* Number of chords too big for num_max */
#define H_ERR_OPNOCOMPL    3514 /* Operator cannot be implemented for 
                                   complemented regions */

/* Image format */
#define H_ERR_WIMAW1       3520 /* Image width < 0 */
#define H_ERR_WIMAW2       3521 /* Image width >= MAX_FORMAT */
#define H_ERR_WIMAH1       3522 /* Image height <= 0 */
#define H_ERR_WIMAH2       3523 /* Image height >= MAX_FORMAT */
#define H_ERR_WIMAW3       3524 /* Image width <= 0 */
#define H_ERR_WIMAH3       3525 /* Image height <= 0 */
#define H_ERR_TMS          3550 /* Too many segments */


/* Projective transformations */
#define H_ERR_POINT_AT_INFINITY    3600 /* Point at infinity cannot be 
                                           converted to a Euclidean point */
#define H_ERR_ML_NO_COVARIANCE     3601 /* Covariance matrix could not be 
                                           determined */
#define H_ERR_RANSAC_PRNG          3602 /* RANSAC algorithm didn't find enough
                                           point correspondences */
#define H_ERR_RANSAC_TOO_DIFFERENT 3603 /* RANSAC algorithm didn't find enough
                                           point correspondences */
#define H_ERR_PTI_FALLBACK         3604 /* Internal diagnosis: fallback method
                                           had to be used */
#define H_ERR_PTI_TRAFO_SING       3605 /* Projective transformation is 
                                           singular */
#define H_ERR_PTI_MOSAIC_UNDERDET  3606 /* Mosaic is under-determined */


/* Self-calibration */
#define H_ERR_INPC         3620 /* Inconsistent number of point
                                   correspondences. */
#define H_ERR_NOPA         3621 /* No path from reference image to one or
                                   more images. */
#define H_ERR_IINE         3622 /* Image with specified index does not
                                   exist. */
#define H_ERR_NOCM         3623 /* Matrix is not a camera matrix. */
#define H_ERR_SKNZ         3624 /* Skew is not zero. */
#define H_ERR_ILFL         3625 /* Illegal focal length. */
#define H_ERR_KANZ         3626 /* Kappa is not zero. */
#define H_ERR_VARA         3627 /* It is not possible to determine all
                                   parameters for in the variable case. */
#define H_ERR_LVDE         3628 /* No valid implementation selected. */
#define H_ERR_KPAR         3629 /* Kappa can only be determined with the
                                   gold-standard method for fixed camera
                                   parameters. */

/* FFT */
#define H_ERR_NOFFTOPT     3650 /* File is not an FFT optimization data file */
#define H_ERR_WRFFTOPTVERS 3651 /* Wrong FFT optimization data file version */
#define H_ERR_WRHALCONVERS 3652 /* Optimization data was created with a 
                                   different HALCON version 
                                   (Standard HALCON / Parallel HALCON) */
#define H_ERR_OPTFAIL      3653 /* Storing of the optimization data failed */


/* Stereo */
#define H_ERR_EPIINIM      3700 /* Epipoles are situated within the image 
                                   domain */


/* Shape-From */
#define H_ERR_SING         3850 /* The light source positions are linearly 
                                   dependent */
#define H_ERR_FEWIM        3851 /* No sufficient image indication */
#define H_ERR_ZBR_NOS      3852 /* Internal error: Function has equal signs 
                                   in HZBrent */


/* Kalman filter */
#define H_ERR_DIMK         3900 /* Kalman: Dimension n,m or p has got a 
                                   undefined value */
#define H_ERR_NOFILE       3901 /* Kalman: File does not exist */
#define H_ERR_FF1          3902 /* Kalman: Error in file (row of dimension) */
#define H_ERR_FF2          3903 /* Kalman: Error in file (row of marking) */
#define H_ERR_FF3          3904 /* Error in file (value is no float) */
#define H_ERR_NO_A         3905 /* Kalman: Matrix A is missing in file */
#define H_ERR_NO_C         3906 /* Kalman: In Datei fehlt Matrix C */
#define H_ERR_NO_Q         3907 /* Kalman: Matrix Q is missing in file */
#define H_ERR_NO_R         3908 /* Kalman: Matrix R is missing in file */
#define H_ERR_NO_GU        3909 /* Kalman: G or u is missing in file */
#define H_ERR_NOTSYMM      3910 /* Kalman: Covariant matrix is not symmetric */
#define H_ERR_SINGU        3911 /* Kalman: Equation system is singular */


/* Data Base and Image data management */
#define H_ERR_DBOIT        4050 /* Object is a object tupel */
#define H_ERR_DBOC         4051 /* Object has been deleted already */
#define H_ERR_DBWOID       4052 /* Wrong object-ID */
#define H_ERR_DBTC         4053 /* Object tupel has been deleted already */
#define H_ERR_DBWTID       4054 /* Wrong object tupel-ID */
#define H_ERR_DBTIO        4055 /* Object tupel is a object */
#define H_ERR_DBIDNULL     4056 /* Object-ID is NULL (0) */
#define H_ERR_WDBID        4057 /* Object-ID outside the valid range */
#define H_ERR_DBIC         4058 /* Access to deleted image */
#define H_ERR_DBWIID       4059 /* Access to image with wrong key */
#define H_ERR_DBRC         4060 /* Access to deleted region */
#define H_ERR_DBWRID       4061 /* Access to region with wrong key */
#define H_ERR_WCHAN        4062 /* Wrong value for image channel */
#define H_ERR_DBITL        4063 /* Index too big */
#define H_ERR_DBIUNDEF     4064 /* Index not defined */


/* i/o and window management, 51xx */
#define H_ERR_WSCN         5100 /* Wrong (logical) window number */
#define H_ERR_DSCO         5101 /* Error while opening the window */
#define H_ERR_WWC          5102 /* Wrong window coordinates */
#define H_ERR_NWA          5103 /* It is not possible to open another window */
#define H_ERR_DNA          5104 /* Device resp. operator not available */
#define H_ERR_UCOL         5105 /* Unknown color */
#define H_ERR_NWO          5106 /* No window has been opened for 
                                   desired action */
#define H_ERR_WFM          5107 /* Wrong filling mode for regions */
#define H_ERR_WGV          5108 /* Wrong gray value (0..255) */
#define H_ERR_WPV          5109 /* Wrong pixel value */
#define H_ERR_WLW          5110 /* Wrong line width */
#define H_ERR_WCUR         5111 /* Wrong name of cursor */
#define H_ERR_WLUT         5112 /* Wrong color table */
#define H_ERR_WDM          5113 /* Wrong representation mode */
#define H_ERR_WRCO         5114 /* Wrong representation color */
#define H_ERR_WRDM         5115 /* Wrong dither matrix */
#define H_ERR_WRIT         5116 /* Wrong image transformation */
#define H_ERR_IPIT         5117 /* Unsuitable image type for image trafo. */
#define H_ERR_WRZS         5118 /* Wrong zooming factor for image trafo. */
#define H_ERR_WRDS         5119 /* Wrong representation mode */
#define H_ERR_WRDV         5120 /* Wrong code of device */
#define H_ERR_WWINF        5121 /* Wrong number for father window */
#define H_ERR_WDEXT        5122 /* Wrong window size */
#define H_ERR_WWT          5123 /* Wrong window type */
#define H_ERR_WND          5124 /* No current window has been set */
#define H_ERR_WRGB         5125 /* Wrong color combination or range (RGB) */
#define H_ERR_WPNS         5126 /* Wrong number of pixels set */
#define H_ERR_WCM          5127 /* Wrong value for comprise */
#define H_ERR_FNA          5128 /* set_fix with 1/4 image levels and 
                                   static not valid */
#define H_ERR_LNFS         5129 /* set_lut not valid in child windows */
#define H_ERR_LOFL         5130 /* Number of concurrent used color tables 
                                   is too big */
#define H_ERR_WIDT         5131 /* Wrong device for window dump */
#define H_ERR_WWDS         5132 /* Wrong window size for window dump */
#define H_ERR_NDVS         5133 /* System variable DISPLAY not defined */
#define H_ERR_WBW          5134 /* Wrong thickness for window margin */
#define H_ERR_WDVS         5135 /* System variable DISPLAY has been set 
                                   wrong (<host>:0.0) */
#define H_ERR_TMF          5136 /* Too many fonts loaded */
#define H_ERR_WFN          5137 /* Wrong font name */
#define H_ERR_WCP          5138 /* No valid cursor postion */
#define H_ERR_NTW          5139 /* Window is not a textual window */
#define H_ERR_NPW          5140 /* Window is not a image window */
#define H_ERR_STL          5141 /* String too long or too high */
#define H_ERR_NSS          5142 /* Too little space in the window rightw. */
#define H_ERR_NMS          5143 /* Window is not suitable for the mouse */ 
#define H_ERR_DWNA         5144 /* Here Windows on a equal machine is 
                                   permitted only */
#define H_ERR_WOM          5145 /* Wrong mode while opening a window */
#define H_ERR_WWM          5146 /* Wrong window mode for operation */
#define H_ERR_LUTF         5147 /* Operation not possible with fixed pixel */
#define H_ERR_LUTN8        5148 /* Color tables for 8 image levels only */
/* pseudo true-color */
#define H_ERR_WTCM         5149 /* Wrong mode for pseudo real colors */
#define H_ERR_WIFTL        5150 /* Wrong pixel value for LUT */
#define H_ERR_WSOI         5151 /* Wrong image size for pseudo real colors */
#define H_ERR_HRLUT        5152 /* Error in procedure HRLUT */
#define H_ERR_WPFSL        5153 /* Wrong number of entries in color table 
                                   for set_lut */

#define H_ERR_WPVS         5154 /* Wrong values for image area */
#define H_ERR_WLPN         5155 /* Wrong line pattern */
#define H_ERR_WLPL         5156 /* Wrong number of parameters for 
                                   line pattern */
#define H_ERR_WNOC         5157 /* Wrong number of colors */
#define H_ERR_WPST         5158 /* Wrong value for mode of area creation */

#define H_ERR_SWNA         5159 /* Spy window is not set (set_spy) */
#define H_ERR_NSFO         5160 /* No file for spy has been set (set_spy) */
#define H_ERR_WSPN         5161 /* Wrong parameter output depth (set_spy) */

#define H_ERR_WIFFD        5162 /* Wrong window size for window dump */
#define H_ERR_WLUTF        5163 /* Wrong color table: 
                                   Wrong file name or query_lut() */
#define H_ERR_WLUTE        5164 /* Wrong color table:
                                   Empty string ? */
#define H_ERR_WLUTD        5165 /* Using this hardware set_lut('default') 
                                   is allowed only */

#define H_ERR_CNDP         5166 /* Error while calling online help */

#define H_ERR_LNPR         5167 /* Row can not be projected */
#define H_ERR_NFSC         5168 /* Operation is unsuitable using a computer 
                                   with fixed color table */
#define H_ERR_NACD         5169 /* Computer represents gray scales only */

#define H_ERR_LUTO         5170 /* LUT of this display is full */
#define H_ERR_WCC          5171 /* Internal error: wrong color code */
#define H_ERR_WWATTRT      5172 /* Wrong type for window attribute */
#define H_ERR_WWATTRN      5173 /* Wrong name for window attribute */
#define H_ERR_WRSPART      5174 /* negativ height of area (or 0) */
#define H_ERR_WCSPART      5175 /* negativ width of area (or 0) */

/* Window dump */
#define H_ERR_WNCV         5176 /* Window not completely visible */

/* Image windows */
#define H_ERR_CHA3         5180 /* Internal error: only RGB-Mode */
#define H_ERR_NMWA         5181 /* No more (image-)windows available */

/* File i/o, 52xx */
#define H_ERR_FNF          5200 /* File not found */
#define H_ERR_DWI          5201 /* Error while writing image data 
                                   (sufficient memory ?) */
#define H_ERR_DWID         5202 /* Error while writing image descriptor 
                                   (sufficient memory ?) */
#define H_ERR_DRI1         5203 /* Error while reading image data 
                                   (format of image too small ?) */
#define H_ERR_DRI2         5204 /* Error while reading image data 
                                   (format of image too big ?) */
#define H_ERR_DRID1        5205 /* Error while reading image descriptor: 
                                   File too small */
#define H_ERR_DIMMAT       5206 /* Image matrices are different */
#define H_ERR_HNF          5207 /* Help file not found (setenv HALCONROOT) */
#define H_ERR_XNF          5208 /* Help index not found (setenv HALCONROOT) */
#define H_ERR_CNCSI        5209 /* File <standard_input> can not be closed */
#define H_ERR_CNCSO        5210 /* <standard_output/error> can not be closed */
#define H_ERR_CNCF         5211 /* File can not be closed */
#define H_ERR_EDWF         5212 /* Error while writing to file */
#define H_ERR_NFA          5213 /* Exceeding of maximum number of files */
#define H_ERR_WFIN         5214 /* Wrong file name */
#define H_ERR_CNOF         5215 /* Error while opening the file */
#define H_ERR_WFMO         5216 /* Wrong file mode */
#define H_ERR_WPTY         5217 /* Wrong type for pixel (e.g. byte) */
#define H_ERR_WIW          5218 /* Wrong image width (too big ?) */
#define H_ERR_WIH          5219 /* Wrong image height (too big ?) */
#define H_ERR_FTS1         5220 /* File already exhausted before reading 
                                   an image */
#define H_ERR_FTS2         5221 /* File exhausted before terminating 
                                   the image */
#define H_ERR_WDPI         5222 /* Wrong value for resolution (dpi) */
#define H_ERR_WNOW         5223 /* Wrong output image size (width) */
#define H_ERR_WNOH         5224 /* Wrong output image size (height) */
#define H_ERR_WNFP         5225 /* Wrong number of parameter values: 
                                   Format description */
#define H_ERR_WPNA         5226 /* Wrong parameter name for operator */
#define H_ERR_WSNA         5227 /* Wrong slot name for parameter */
#define H_ERR_NPCF         5228 /* Operator class is missing in help file */
#define H_ERR_WHIF         5229 /* Wrong or inconsistent help/ *.idx 
                                   or help/ *.sta */
#define H_ERR_HINF         5230 /* File help/ *.idx not found */
#define H_ERR_HSNF         5231 /* File help/ *.sta not found */
#define H_ERR_ICSF         5232 /* Inconsistent file help/ *.sta */
#define H_ERR_EFNF         5233 /* No explication file (.exp) found */
#define H_ERR_NFWKEF       5234 /* No file found in known graphic format */
#define H_ERR_WIFT         5235 /* Wrong graphic format */
#define H_ERR_ICNF         5236 /* Inconsistent file halcon.num */
#define H_ERR_WTIFF        5237 /* File with extension 'tiff' is no 
                                   Tiff-file */
#define H_ERR_WFF          5238 /* Wrong file format */
#define H_ERR_NOGPPROC     5239 /* gnuplot could not be started */
#define H_ERR_NOGPFILE     5240 /* Output file for gnuplot could not be 
                                   opened */
#define H_ERR_NOGPOUT      5241 /* Not a valid gnuplot output stream */
#define H_ERR_NOPNM        5242 /* No PNM format */
#define H_ERR_ICODB        5243 /* Inconsistent or old help file */
#define H_ERR_WFID         5244 /* Wrong file handle */
#define H_ERR_FNO          5245 /* File not open */
#define H_ERR_NO_FILES     5246 /* No files in use so far (none opened) */

/* Serial interface */
#define H_ERR_WSID         5250 /* Invalid handle for a serial connection */
#define H_ERR_SNO          5251 /* Serial port not open */
#define H_ERR_NSA          5252 /* No serial port available */
#define H_ERR_CNOS         5253 /* Could not open serial port */
#define H_ERR_CNCS         5254 /* Could not close serial port */
#define H_ERR_CNGSA        5255 /* Could not get serial port attributes */
#define H_ERR_CNSSA        5256 /* Could not set serial port attributes */
#define H_ERR_WRSBR        5257 /* Wrong baud rate for serial connection */
#define H_ERR_WRSDB        5258 /* Wrong number of data bits for 
                                   serial connection */
#define H_ERR_WRSFC        5259 /* Wrong flow control for serial connection */
#define H_ERR_CNFS         5260 /* Could not flush serial port */
#define H_ERR_EDWS         5261 /* Error during write to serial port */
#define H_ERR_EDRS         5262 /* Error during read from serial port */

/* Frame grabber */
#define H_ERR_NFS          5300 /* No frame grabber opened */
#define H_ERR_FGWC         5301 /* FG: Wrong color depth */
#define H_ERR_FGWD         5302 /* FG: Wrong device */
#define H_ERR_FGVF         5303 /* FG: Determination of video format 
                                   not possible */
#define H_ERR_FGNV         5304 /* FG: No video signal */
#define H_ERR_UFG          5305 /* Unknown frame grabber */
#define H_ERR_FGF          5306 /* FG: Failed grabbing of an image */
#define H_ERR_FGWR         5307 /* FG: Wrong resolution chosen */
#define H_ERR_FGWP         5308 /* FG: Wrong image part chosen */
#define H_ERR_FGWPR        5309 /* FG: Wrong pixel ratio chosen */
#define H_ERR_FGWH         5310 /* FG: Handle not valid */
#define H_ERR_FGCL         5311 /* FG: Instance not valid (already closed?) */
#define H_ERR_FGNI         5312 /* Frame grabber cannot be initialized */
#define H_ERR_FGET         5313 /* FG: External triggering not supported */
#define H_ERR_FGLI         5314 /* FG: Wrong camera input line (multiplex) */
#define H_ERR_FGCS         5315 /* FG: Wrong color space */
#define H_ERR_FGPT         5316 /* FG: Wrong port */
#define H_ERR_FGCT         5317 /* FG: Wrong camera type */
#define H_ERR_FGTM         5318 /* FG: Maximum number of frame grabber 
                                   classes exceeded */
#define H_ERR_FGDV         5319 /* FG: Device busy */
#define H_ERR_FGASYNC      5320 /* FG: Asynchronous grab not supported */
#define H_ERR_FGPARAM      5321 /* FG: Unsupported parameter */
#define H_ERR_FGTIMEOUT    5322 /* FG: Timeout */
#define H_ERR_FGGAIN       5323 /* FG: Invalid gain  */
#define H_ERR_FGFIELD      5324 /* FG: Invalid field */
#define H_ERR_FGPART       5325 /* FG: Invalid parameter type */
#define H_ERR_FGPARV       5326 /* FG: Invalid parameter value */
#define H_ERR_FGFNS        5327 /* FG: Function not supported */
#define H_ERR_FGIVERS      5328 /* FG: Incompatible interface version */
#define H_ERR_FGSETPAR     5329 /* FG: Could not set parameter value */
#define H_ERR_FGGETPAR     5330 /* FG: Could not query parameter setting */
#define H_ERR_FGPARNA      5331 /* FG: Parameter not available in current 
                                   configuration */

/* Images from file */
/* General */
#define H_ERR_LIB_FILE_CLOSE          5500 /* Error while closing the 
                                              image file */
#define H_ERR_LIB_FILE_OPEN           5501 /* Error while opening the 
                                              image file */
#define H_ERR_LIB_UNEXPECTED_EOF      5502 /* Premature end of the 
                                              image file */

/* PCX files */
#define H_ERR_PCX_NO_PCX_FILE         5510 /* File is no PCX-File */
#define H_ERR_PCX_UNKNOWN_ENCODING    5511 /* Unknown encoding */
#define H_ERR_PCX_MORE_THAN_4_PLANES  5512 /* More than 4 image plains */
#define H_ERR_PCX_COLORMAP_SIGNATURE  5513 /* Wrong magic in color table */
#define H_ERR_PCX_REPEAT_COUNT_SPANS  5514 /* Wrong number of bytes in span */
#define H_ERR_PCX_TOO_MUCH_BITS_PIXEL 5515 /* Wrong number of bits/pixels */
#define H_ERR_PCX_PACKED_PIXELS       5516 /* Wrong number of plains */

/* GIF files */
#define H_ERR_GIF_NO_GIF_PICTURE      5520 /* File is no GIF-File */
#define H_ERR_GIF_BAD_VERSION         5521 /* GIF: Wrong version */
#define H_ERR_GIF_SCREEN_DESCRIPTOR   5522 /* GIF: Wrong descriptor */
#define H_ERR_GIF_COLORMAP            5523 /* GIF: Wrong color table */
#define H_ERR_GIF_READ_ERROR_EOF      5524 /* GIF: Premature end of file */
#define H_ERR_GIF_NOT_ENOUGH_IMAGES   5525 /* GIF: Wrong number of images */
#define H_ERR_GIF_ERROR_ON_EXTENSION  5526 /* GIF: Wrong image extension */
#define H_ERR_GIF_LEFT_TOP_WIDTH      5527 /* GIF: Wrong left top width */
#define H_ERR_GIF_CIRCULAR_TABL_ENTRY 5528 /* GIF: Cyclic index of table */
#define H_ERR_GIF_BAD_IMAGE_DATA      5529 /* GIF: Wrong image data */

/* SUN-Raster files  */
#define H_ERR_SUN_RASTERFILE_TYPE     5530 /* File is no Sun-Raster-File */
#define H_ERR_SUN_RASTERFILE_HEADER   5531 /* Wrong header */
#define H_ERR_SUN_COLS                5532 /* Wrong image width */
#define H_ERR_SUN_ROWS                5533 /* Wrong image height */
#define H_ERR_SUN_COLORMAP            5534 /* Wrong color map */
#define H_ERR_SUN_RASTERFILE_IMAGE    5535 /* Wrong image data */
#define H_ERR_SUN_IMPOSSIBLE_DATA     5536 /* Wrong type of pixel */

/* XWD files */
#define H_ERR_XWD_IMPOSSIBLE_DATA     5540  /* Wrong type of pixel */
#define H_ERR_XWD_VISUAL_CLASS        5541  /* Wrong visual class */
#define H_ERR_XWD_X10_HEADER          5542  /* Wrong X10 header */
#define H_ERR_XWD_X11_HEADER          5543  /* Wrong X11 header */
#define H_ERR_XWD_X10_COLORMAP        5544  /* Wrong X10 colormap */
#define H_ERR_XWD_X11_COLORMAP        5545  /* Wrong X11 colormap */
#define H_ERR_XWD_X11_PIXMAP          5546  /* Wrong pixmap */
#define H_ERR_XWD_UNKNOWN_VERSION     5547  /* Unknown version */
#define H_ERR_XWD_READING_IMAGE       5548  /* Error while reading an image */

/* TIFF files */
#define H_ERR_TIF_BAD_INPUTDATA      5550 /* Error while reading a file */
#define H_ERR_TIF_COLORMAP           5551 /* Wrong colormap */
#define H_ERR_TIF_BAD_CHANNEL_COLOR  5552 /* Wrong number of color channels */
#define H_ERR_TIF_TOO_MANY_COLORS    5553 /* Too many colors */
#define H_ERR_TIF_BAD_PHOTOMETRIC    5554 /* Wrong photometric 
                                             interpretation */
#define H_ERR_TIF_PHOTOMETRIC_DEPTH  5555 /* Wrong photometric depth */
#define H_ERR_TIF_PHOTOMETRIC_MASK   5556 /* Wrong photometric mask */
#define H_ERR_TIF_SAMPLE_TOO_LARGE   5557 /* Number of samples too large */
#define H_ERR_TIF_NO_REGION          5558 /* Image is no binary file */


/* BMP files */
#define H_ERR_BMP_NO_BMP_PICTURE      5560  /* File is no BMP-File */
#define H_ERR_BMP_READ_ERROR_EOF      5561  /* Premature end of file */
#define H_ERR_BMP_INCOMPLETE_HEADER   5562  /* Incomplete header */
#define H_ERR_BMP_UNKNOWN_FORMAT      5563  /* Unknown bitmap format */
#define H_ERR_BMP_UNKNOWN_COMPRESSION 5564  /* Unknown compression format */
#define H_ERR_BMP_COLORMAP            5565  /* Wrong color table */
#define H_ERR_BMP_WRITE_ERROR         5566  /* Write error on output */
#define H_ERR_BMP_NO_REGION           5567  /* File does not contain a 
                                               binary image */

/* Jpeg files */
#define H_ERR_JPG_COMP_NUM     5570 /* Wrong number of components in image */
#define H_ERR_JPGLIB_UNKNOWN   5571 /* Unknown error from libjpeg */
#define H_ERR_JPGLIB_NOTIMPL   5572 /* No implementet feature in libjpeg */
#define H_ERR_JPGLIB_FILE      5573 /* File access error in libjpeg */
#define H_ERR_JPGLIB_TMPFILE   5574 /* Tmp file access error in libjpeg */
#define H_ERR_JPGLIB_MEMORY    5575 /* Memory error in libjpeg */
#define H_ERR_JPGLIB_INFORMAT  5576 /* Error in input image */

/* PNG files */
#define H_ERR_PNG_NO_PNG_FILE            5580  /* File is not a PNG file */
#define H_ERR_PNG_UNKNOWN_INTERLACE_TYPE 5581  /* Unknown interlace type */
#define H_ERR_PNG_UNSUPPORTED_COLOR_TYPE 5582  /* Unsupported color type */


/* Socket communication and virtual links */
#define H_ERR_SOCKET_BLOCK                5600 /* Socket can not be set to 
                                                  block */
#define H_ERR_SOCKET_UNBLOCK              5601 /* Socket can not be set to 
                                                  unblock */
#define H_ERR_SOCKET_NO_CPAR              5602 /* Received data is no tuple */
#define H_ERR_SOCKET_NO_IMAGE             5603 /* Received data is no image */
#define H_ERR_SOCKET_NO_RL                5604 /* Received data is no region */
#define H_ERR_SOCKET_NO_XLD               5605 /* Received data is no 
                                                  xld object */
#define H_ERR_SOCKET_READ_DATA_FAILED     5606 /* Error while reading 
                                                  from socket */
#define H_ERR_SOCKET_WRITE_DATA_FAILED    5607 /* Error while writing 
                                                  to socket */
#define H_ERR_SOCKET_WRONG_BYTE_NUMBER    5608 /* Illegal number of bytes 
                                                  with get_rl */
#define H_ERR_SOCKET_BUFFER_OVERFLOW      5609 /* Buffer overflow in 
                                                  read_data */
#define H_ERR_SOCKET_CANT_ASSIGN_FD       5610 /* Socket can not be created */
#define H_ERR_SOCKET_CANT_BIND            5611 /* Bind on socket failed */
#define H_ERR_SOCKET_CANT_GET_PORTNUMBER  5612 /* Socket information is not 
                                                  available */
#define H_ERR_SOCKET_CANT_LISTEN          5613 /* Socket cannot listen for 
                                                  incoming connections */
#define H_ERR_SOCKET_CANT_ACCEPT          5614 /* Connection could not be 
                                                  accepted */
#define H_ERR_SOCKET_CANT_CONNECT         5615 /* Connection request failed */
#define H_ERR_SOCKET_GETHOSTBYNAME        5616 /* Hostname could not be 
                                                  resolved */
#define H_ERR_SOCKET_RECV_IS_NEG          5617 /* No data on socket */
#define H_ERR_SOCKET_ILLEGAL_TUPLE_TYPE   5618 /* Unknown tuple type on 
                                                  socket */
#define H_ERR_SOCKET_TIMEOUT              5619 /* Timeout occured on socket */
#define H_ERR_SOCKET_NA                   5620 /* No more sockets available */
#define H_ERR_SOCKET_NI                   5621 /* Socket is not initialized */
#define H_ERR_SOCKET_OOR                  5622 /* Invalid socket */
#define H_ERR_SOCKET_IS                   5623 /* Socket is NULL */


/* Memory management */
#define H_ERR_NP           6000 /* Access to undefined memory area */
#define H_ERR_MEM          6001 /* Not enough memory available */
#define H_ERR_ICM          6002 /* Memory partition on heap has been 
                                   overwritten */
#define H_ERR_WMS          6003 /* HAlloc: 0 bytes requested */
#define H_ERR_NOTMP        6004 /* Tmp-memory management: 
                                   Call freeing memory although nothing had
                                   been allocated */
#define H_ERR_TMPNULL      6005 /* Tmp-memory management: 
                                   Null pointer while freeing */
#define H_ERR_CNFMEM       6006 /* Tmp-memory management: 
                                   Could not find memory element */
#define H_ERR_NRA          6041 /* No memory block allocated at last */
#define H_ERR_IAD          6040 /* System parameter for memory-allocation 
                                   inconsistent */

/* Language interfaces */
/* General  */
#define H_ERR_WOCPI        7000 /* Wrong index for output control par. */
#define H_ERR_WOCPVN       7001 /* Wrong number of values: 
                                   Output control parameter */
#define H_ERR_WOCPT        7002 /* Wrong type: Output control parameter */
#define H_ERR_WKT          7003 /* Wrong data type for object key 
                                   (input objects) */
#define H_ERR_IOOR         7004 /* Range for integer had been passed */
#define H_ERR_IHV          7005 /* Inconsistent Halcon version */
#define H_ERR_NISS         7006 /* Not enough memory for strings allocated */
#define H_ERR_PROC_NULL    7007 /* Internal error: Proc is NULL */

/* PRO */
#define H_ERR_WLST         7100 /* Wrong list structure using input objects */
#define H_ERR_WIOP         7101 /* Wrong input object parameter (not bound) */
#define H_ERR_WICP         7102 /* Wrong input control par. (not bound) */
#define H_ERR_WOOP         7103 /* Wrong output object par. (already bound) */
#define H_ERR_WOCP         7104 /* Wrong output control par.(already bound) */
#define H_ERR_UNKN         7105 /* Unknown symbolic object key (input obj.) */

/* VAX */
#define H_ERR_WOON         7200 /* Wrong number of output object parameter */

/* OPS5 */
#define H_ERR_WNOIP        7300 /* Wrong number of input parameter */

/* C */
#define H_ERR_OTSE         7400 /* Output type <string> expected */
#define H_ERR_OTLE         7401 /* Output type <long> expected */
#define H_ERR_OTFE         7402 /* Output type <float> expected */
#define H_ERR_OPINP        7403 /* Object parameter is a zero pointer */
#define H_ERR_TWC          7404 /* Tupel had been deleted; values are not 
                                   valid any more */

/* C++ */
#define H_ERR_CPPWOM       7430 /* CPP-interface internal error: 
                                   Wrong object mode */
#define H_ERR_CPPWNOR      7431 /* Wrong number of regions (> 1) for 
                                   type HRegion */
#define H_ERR_CPPWNOI      7432 /* Wrong number of images (> 1) for 
                                   type HImage */
#define H_ERR_TNOVAL       7433 /* Tupel with undefined values */

/* RPC  */
#define H_ERR_RPCS         7500 /* No contact to RPC server */
#define H_ERR_RPC          7501 /* Error in remote procedure call */

/* SWI-Prolog */
#define H_ERR_SWI_NOLIST   7600 /* Parameter value is neither a list 
                                   nor a atom */

/* Cgpx */
#define H_ERR_WPRN         8000 /* Unknown operator name */
#define H_ERR_RCNA         8001 /* register_comp_used is not activated */
#define H_ERR_WPC          8002 /* Unknown operator class */

/* Convolution and rank */
/* Error codes concerning getMask() (RMF = Read Mask-File) */
#define H_ERR_ORMF        8101  /* convol/mask: Error while opening file */
#define H_ERR_EOFRMF      8102  /* convol/mask: Premature end of file */
#define H_ERR_CVTRMF      8103  /* convol/mask: Conversion error */
#define H_ERR_LCNRMF      8104  /* convol/mask: Wrong row-/column number */
#define H_ERR_WCOVRMF     8105  /* convol/mask: Mask size overflow */
#define H_ERR_NEOFRMF     8106  /* convol/mask: Too many elements entered */
/* IPconvol() and IPRank()                             */
#define H_ERR_WRRA        8107  /* convol: Wrong margin type */
#define H_ERR_MCN0        8108  /* convol: No mask object has got 
                                   empty region */
#define H_ERR_FCN0        8109  /* convol: No filter object has got 
                                   empty region */
#define H_ERR_WF0         8110  /* convol: Weight factor is 0 */
#define H_ERR_NWC         8111  /* convol: Inconsistent number of weights */
#define H_ERR_WRRV        8112  /* rank: Wrong rank value */
/* Boarder treatment */
#define H_ERR_ROVFL       8113  /* convol/rank: Error while handling margin */

#define H_ERR_WNUMM       8120  /* Wrong number of coefficients for 
                                   convolution (sigma too big?) */

/* Background estimation (Kalman) */
#define H_ERR_WBEDN       8200  /* No valid ID for data set */
#define H_ERR_NBEDA       8201  /* No data set active (set_bg_esti) */
#define H_ERR_BEDNAU      8202  /* ID already used for data set */
#define H_ERR_NBEDC       8204  /* No data set created (create_bg_esti) */
#define H_ERR_NTM         8205  /* Not possible to pass an object list */
#define H_ERR_WISBE       8206  /* Image has other size than the background 
                                   image in data set */
#define H_ERR_UDNSSBE     8207  /* Up-date-region is bigger than 
                                   background image */
#define H_ERR_SNBETS      8208  /* Number of statistic data sets is 
                                   too small */
#define H_ERR_WAMBE       8209  /* Wrong value for adapt mode */
#define H_ERR_WFMBE       8210  /* Wrong value for frame mode */


/* OCR */
#define H_ERR_OCR_MEM1    8300  /* Maximum number of fonts exceeded */
#define H_ERR_OCR_WID     8301  /* Wrong ID (Number) for font */
#define H_ERR_OCR1        8302  /* OCR internal error: wrong ID */
#define H_ERR_OCR_NNI     8303  /* OCR not initialised: no font was read in */
#define H_ERR_OCR_NAI     8304  /* No font activated */
#define H_ERR_OCR_WTP     8305  /* OCR internal error: Wrong threshold in 
                                   angle determination */
#define H_ERR_OCR_WF      8306  /* OCR internal error: Wrong attribute */
#define H_ERR_OCR_READ    8307  /* OCR: Error during reading file */
#define H_ERR_OCR_NODES   8308  /* OCR File: Inconsistent number of nodes */
#define H_ERR_OCR_EOF     8309  /* OCR File: File too short */
#define H_ERR_OCR_INC1    8310  /* OCR: Internal error 1 */
#define H_ERR_OCR_INC2    8311  /* OCR: Internal error 2 */
#define H_ERR_WOCRTYPE    8312  /* Wrong type of OCR tool 
                                   (no 'box' or 'net') */
#define H_ERR_OCR_TRF     8313  /* Unknown OCR training file version */

#define H_ERR_OCR_MLP_NOCLASSFILE 8320 /* Not a valid OCR classifier file */
#define H_ERR_OCR_MLP_WRCLASSVERS 8321 /* Wrong OCR classifier file version */

/* OCV */
#define H_ERR_OCV_NI      8350  /* OCV system not initialized */
#define H_ERR_WOCVTYPE    8351  /* Wrong type of OCV features */
#define H_ERR_OCV_NOFID   8352  /* No more free OCV handle available */
#define H_ERR_OCV_WNAME   8353  /* Wrong name for an OCV object */
#define H_ERR_OCV_II      8354  /* Training has already been applied */
#define H_ERR_OCV_NOTTR   8355  /* No training has been applied */


/* Function 1D */
#define H_ERR_WLENGTH       8370 /* Wrong number of function points */
#define H_ERR_NO_FUNCTION   8371 /* List of values is not a function */
#define H_ERR_NOT_ASCENDING 8372 /* Wrong ordering of values (not ascending)*/
#define H_ERR_ILLEGAL_DIST  8373 /* Illegal distance of function points */
#define H_ERR_NOT_MONOTONIC 8374 /* Function is not monotonic. */


/* Camera calibration */
#define H_ERR_CAL_LCALP     8400 /* At least 3 calibration points have to be 
                                    indicated */
#define H_ERR_CAL_NCPF      8402 /* No calibration table found */
#define H_ERR_CAL_RECPF     8403 /* Error while reading calibration table 
                                    description file */
#define H_ERR_CAL_LTMTH     8404 /* Minimum threshold while searching for 
                                    ellipses */
#define H_ERR_CAL_FRCP      8405 /* Read error / format error in calibration 
                                    table description file */
#define H_ERR_CAL_PROJ      8406 /* Error in projection: 
                                    s_x = 0 or s_y = 0 or z = 0 */
#define H_ERR_CAL_UNPRO     8407 /* Error in inverse projection */
#define H_ERR_CAL_RICPF     8408 /* Not possible to open camera parameter 
                                    file */
#define H_ERR_CAL_FICP1     8409 /* Format error in file: No colon */
#define H_ERR_CAL_FICP2     8410 /* Format error in file: 
                                    2. colon is missing */
#define H_ERR_CAL_FICP3     8411 /* Format error in file: 
                                    Semicolon is missing */
#define H_ERR_CAL_REPOS     8412 /* Not possible to open camera parameter 
                                    (pose) file */
#define H_ERR_CAL_FOPOS     8413 /* Format error in camera parameter 
                                    (pose) file */
#define H_ERR_CAL_OCPDF     8414 /* Not possible to open calibration target 
                                    description file */
#define H_ERR_CAL_OCPPS     8415 /* Not possible to open postscript file of 
                                    calibration target */
#define H_ERR_CAL_EVECN     8416 /* Error while norming the vector */
#define H_ERR_CAL_NPLAN     8417 /* Fitting of calibration target failed */
#define H_ERR_CAL_NNMAR     8418 /* No next mark found */
#define H_ERR_CAL_NNEQU     8419 /* Normal equation system is not solvable */
#define H_ERR_CAL_QETHM     8420 /* Average quadratic error is too big for 
                                    3D position of mark */
#define H_ERR_CAL_NOELL     8421 /* Non elliptic contour */
#define H_ERR_CAL_WPARV     8422 /* Wrong parameter value slvand() */
#define H_ERR_CAL_WFRES     8423 /* Wrong function results slvand() */
#define H_ERR_CAL_ECPDI     8424 /* Distance of marks in calibration target 
                                    description file is not possible */
#define H_ERR_CAL_WEFLA     8425 /* Specified flag for degree of freedom 
                                    not valid */
#define H_ERR_CAL_NOMER     8426 /* Minimum error did not fall below */
#define H_ERR_CAL_WPTYP     8427 /* Wrong type in Pose 
                                    (rotation / translation) */
#define H_ERR_CAL_WIMSZ     8428 /* Image size does not match the measurement
                                    in camera parameters */
#define H_ERR_CAL_NPILS     8429 /* Point could not be projected into 
                                    linescan image */
#define H_ERR_CAL_DIACM     8430 /* Diameter of calibration marks could
                                    not be determined */
#define H_ERR_CAL_ORICP     8431 /* Orientation of calibration plate could
                                    not be determined */
#define H_ERR_CAL_CPNII     8432 /* Calibration plate does not lie completely
                                    inside the image */
#define H_ERR_CAL_WNCME     8433 /* Wrong number of calibration marks
                                    extracted */
#define H_ERR_CAL_UNKPG     8434 /* Unknown name of parameter group */
#define H_ERR_CAL_NEGFL     8435 /* Focal length must be non-negative */
#define H_ERR_CAL_TELNA     8436 /* Function not available for cameras
                                    with telecentric lenses */
#define H_ERR_CAL_LSCNA     8437 /* Function not available for line scan
                                    cameras */
#define H_ERR_CAL_ELLDP     8438 /* Ellipse is degenerated to a point */
#define H_ERR_CAL_NOMF      8439 /* No orientation mark found */

/* Matching */
/* Gray-value-based matching */
#define H_ERR_NOAP          8500 /* Not a pattern file */
#define H_ERR_WPFV          8501 /* Wrong pattern file version */
#define H_ERR_MATCH_MODE    8502 /* Error during changing the file mode */
#define H_ERR_MATCH_OOR     8503 /* Inconsistent match file: 
                                    Coordinates out of range */
#define H_ERR_NOTAP         8505 /* The image(s) is not a pyramid */

/* Shape-based matching */
#define H_ERR_NTPTS         8510 /* Number of shape model points too small */

/* Component-based matching */
#define H_ERR_COMP_DRT      8530 /* Initial components have different 
                                    region types */
#define H_ERR_COMP_SAMF     8531 /* Solution of ambiguous matches failed */
#define H_ERR_IGF_NC        8532 /* Computation of the incomplete gamma 
                                    function not converged */
#define H_ERR_MSA_TMN       8533 /* Too many nodes while computing the minimum
                                    spanning arborescence */

/* Image comparison */
#define H_ERR_VARIATION_WS    8540 /* Size of the training image and the 
                                      variation model differ */
#define H_ERR_VARIATION_PREP  8541 /* Variation model has not been prepared 
                                      for segmentation */
#define H_ERR_VARIATION_WRMD  8542 /* Invalid variation model training mode */
#define H_ERR_VARIATION_NOVF  8543 /* File does not contain a var. model */
#define H_ERR_VARIATION_WVFV  8544 /* Invalid variation model file version */

/* Measure */
#define H_ERR_MEASURE_NA    8550 /* No more measure objects available */
#define H_ERR_MEASURE_NI    8551 /* Measure object is not initialized */
#define H_ERR_MEASURE_OOR   8552 /* Invalid measure object */
#define H_ERR_MEASURE_IS    8553 /* Measure object is NULL */
#define H_ERR_MEASURE_WS    8554 /* Measure object has wrong image size */

/* Dynamic libraries */
#define H_ERR_DLOPEN        8600 /* Dynamic library could not be opened */
#define H_ERR_DLCLOSE       8601 /* Dynamic library could not be closed */
#define H_ERR_DLLOOKUP      8602 /* Symbol not found in dynamic library */

/* Radiometric calibration */
#define H_ERR_EAD_CAL_NII   8650 /* Not enough information for rad. calib. */

/* Barcode */
#define H_ERR_BAR_UNKNOWN    8700 /* Unkown bar code */
#define H_ERR_BAR_WNOM       8701 /* Wrong number of modules */
#define H_ERR_BAR_WNOE       8702 /* Wrong number of elements */
#define H_ERR_BAR_UNCHAR     8703 /* Unknown character (for this code) */
#define H_ERR_BAR_WRONGDESCR 8705 /* Wrong name for attribute in barcode 
                                     descriptor */
#define H_ERR_BAR_EL_LENGTH  8706 /* Wrong thickness of element */
#define H_ERR_BAR_NO_REG     8707 /* No region found */

/* 2D Barcode */
#define H_ERR_BAR2D_UNKNOWN_TYPE     8800 /* Specified code type is not 
                                             supported */
#define H_ERR_BAR2D_WRONG_FOREGROUND 8801 /* Wrong foreground specified */
#define H_ERR_BAR2D_WRONG_SIZE       8802 /* Wrong matrix size specified */
#define H_ERR_BAR2D_WRONG_SHAPE      8803 /* Wrong symbol shape specified */
#define H_ERR_BAR2D_WRONG_PARAM_NAME 8804 /* Wrong generic parameter name */
#define H_ERR_BAR2D_WRONG_PARAM_VAL  8805 /* Wrong generic parameter value */
#define H_ERR_BAR2D_WRONG_MODE       8806 /* Wrong symbol printing mode */
#define H_ERR_BAR2D_SYMBOL_ON_BORDER 8807 /* Symbol region too near to image 
                                             border */
#define H_ERR_BAR2D_MODULE_CONT_NUM  8808 /* No rectangular modul boundings 
                                             found */
#define H_ERR_BAR2D_SYMBOL_FINDER    8809 /* Couldn't identify symbol 
                                             finder */
#define H_ERR_BAR2D_SYMBOL_DIMENSION 8810 /* Symbol region with wrong 
                                             dimension */
#define H_ERR_BAR2D_CLASSIF_FAILED   8811 /* Classification failed */
#define H_ERR_BAR2D_DECODING_FAILED  8812 /* Decoding failed */
#define H_ERR_BAR2D_DECODING_READER  8813 /* Reader programing not 
                                             supported */

/* Error codes for errors on all types 2d data codes */
#define H_ERR_DC2D_GENERAL             8820 /* General 2d data code error */
#define H_ERR_DC2D_BROKEN_SIGN         8821 /* Corrupt signature of 2d data 
                                               code handle */
#define H_ERR_DC2D_INVALID_HANDLE      8822 /* Invalid 2d data code handle */
#define H_ERR_DC2D_EMPTY_MODEL_LIST    8823 /* List of 2d data code models is
                                               empty */
#define H_ERR_DC2D_NOT_INITIALIZED     8824 /* Access to uninitialized (or not
                                               persistent) internal data */
#define H_ERR_DC2D_INVALID_CANDIDATE   8825 /* Invalid 'Candidate' parameter */
#define H_ERR_DC2D_INDEX_PARNUM        8826 /* It's not possible to return more
                                               than one parameter for several
                                               candidates */
#define H_ERR_DC2D_EXCLUSIV_PARAM      8827 /* One of the parameters returns 
                                               several values and has to be
                                               used exclucively for a single 
                                               candidate */
#define H_ERR_DC2D_DEF_SET_NOT_FIRST   8828 /* Parameter for default settings
                                               must be the first in the
                                               parameter list */
#define H_ERR_DC2D_INTERNAL_UNEXPECTED 8829 /* Unexpected 2d data code error */
#define H_ERR_DC2D_WRONG_PARAM_VALUE   8830 /* Invalid parameter value */
#define H_ERR_DC2D_WRONG_PARAM_NAME    8831 /* Unknown parameter name */
#define H_ERR_DC2D_WRONG_POLARITY      8832 /* Invalid 'polarity' */
#define H_ERR_DC2D_WRONG_SYMBOL_SHAPE  8833 /* Invalid 'symbol_shape' */
#define H_ERR_DC2D_WRONG_SYMBOL_SIZE   8834 /* Invalid symbol size */
#define H_ERR_DC2D_WRONG_MODULE_SIZE   8835 /* Invalid module size */
#define H_ERR_DC2D_WRONG_MODULE_SHAPE  8836 /* Invalid 'module_shape' */
#define H_ERR_DC2D_WRONG_ORIENTATION   8837 /* Invalid 'orientation' */
#define H_ERR_DC2D_WRONG_CONTRAST      8838 /* Invalid 'contrast_min' */
#define H_ERR_DC2D_WRONG_MEAS_THRESH   8839 /* Invalid 'measure_thresh' */
#define H_ERR_DC2D_WRONG_ALT_MEAS_RED  8840 /* Invalid 'alt_measure_red' */
#define H_ERR_DC2D_WRONG_SLANT         8841 /* Invalid 'slant_max' */
#define H_ERR_DC2D_WRONG_L_DIST        8842 /* Invalid 'L_dist_max' */
#define H_ERR_DC2D_WRONG_L_LENGTH      8843 /* Invalid 'L_length_min' */
#define H_ERR_DC2D_WRONG_GAP           8844 /* Invalid module gap */
#define H_ERR_DC2D_WRONG_DEF_SET       8845 /* Invalid 'default_parameters' */
#define H_ERR_DC2D_WRONG_TEXTURED      8846 /* Invalid 'back_texture' */
#define H_ERR_DC2D_WRONG_MIRRORED      8847 /* Invalid 'mirrored' */
#define H_ERR_DC2D_WRONG_CLASSIFICATOR 8848 /* Invalid 'classificator' */
#define H_ERR_DC2D_WRONG_PERSISTENCE   8849 /* Invalid 'persistence' */
#define H_ERR_DC2D_WRONG_MODEL_TYPE    8850 /* Invalid model type */
#define H_ERR_DC2D_WRONG_MOD_ROI_PART  8851 /* Invalid 'module_roi_part' */
#define H_ERR_DC2D_READ_HEAD_FORMAT    8860 /* Invalid header in 2d data code
                                               model file */
#define H_ERR_DC2D_READ_HEAD_SIGN      8861 /* Invalid code signature in 2d
                                               data code model file */
#define H_ERR_DC2D_READ_LINE_FORMAT    8862 /* Corrupted line in 2d data code
                                               model file */
#define H_ERR_DC2D_WRONG_MODULE_ASPECT 8863 /* Invalid module aspect ratio */


/* Misc */
#define H_ERR_NOT_IMPL     9000 /* Function not implemented on this machine */
#define H_ERR_WIT          9001 /* Image to process has wrong gray 
                                   value type */
#define H_ERR_WIC          9002 /* Wrong image component */
#define H_ERR_UNDI         9003 /* Undefined gray values */
#define H_ERR_WIS          9004 /* Wrong image format for operation 
                                   (too big or too small) */
#define H_ERR_WCN          9005 /* Wrong number of image components for 
                                   image output */
#define H_ERR_STRTL        9006 /* String is too long 
                                   (max. 1024 characters) */
#define H_ERR_WITFO        9007 /* Wrong pixel type for this operation */
#define H_ERR_NIIT         9008 /* Operation not realized yet for this 
                                   pixel type */
#define H_ERR_NOCIMA       9009 /* Image is no color image with three 
                                   channels */

#define H_ERR_DEMO_NOFG    9010 /* Frame grabbers are not supported in the 
                                   demo version */
#define H_ERR_DEMO_NOPA    9011 /* Packages are not supported in the 
                                   demo version */
   
#define H_ERR_STUD_OPNA    9050 /* Operator is not available in the 
                                   student version of HALCON */
#define H_ERR_STUD_PANA    9051 /* Packages are not available in the 
                                   student version of HALCON */
#define H_ERR_STUD_FGNA    9052 /* The selected frame grabber is not available
                                   in the student version of HALCON */

/* Linear equations */
#define H_ERR_TMU          9100 /* Too many unknown variables in 
                                   linear equation */
#define H_ERR_NUS          9101 /* No (unique) solution for the 
                                   linear equation */
#define H_ERR_NEE          9102 /* Too little equations in linear equation */

/* Matrix operations */
#define H_ERR_MNI          9200 /* Matrix is not invertible */
#define H_ERR_SVD_CNVRG    9201 /* Singular value decomposition did not 
                                   converge */
#define H_ERR_SVD_FEWROW   9202 /* Matrix has too few rows for singular 
                                   value partition */
#define H_ERR_TQLI_CNVRG   9203 /* Eigenvalue computation did not converge */
#define H_ERR_JACOBI_CNVRG 9204 /* Eigenvalue computation did not converge */
#define H_ERR_MATRIX_SING  9205 /* Matrix is singular */
#define H_ERR_MATCH_CNVRG  9206 /* Function matching did not converge */

#define H_ERR_MAT_UNDEF    9207 /* Input matrix undefined */
#define H_ERR_MAT_WDIM     9208 /* Input matrix with wrong dimension */
#define H_ERR_MAT_NSQR     9209 /* Input matrix is not quadratic */
#define H_ERR_MAT_FAIL     9210 /* Matrix operation failed */
#define H_ERR_MAT_NPD      9211 /* Matrix is not positive definite */

#define H_ERR_CMP_INCONSISTENT  9212 

#define H_ERR_LAPACK_PAR   9250 /* Internal error */

/* Orthogonal Projection */
#define H_ERR_WSPVP        9300 /* Eye point and reference point coincide */

/************************************************************************/
#define H_ERR_START_EXT      10000 /* User defined error codes must be  */
                                   /* larger than that!                 */
/************************************************************************/











/*****************************************************************************/
/*****************************************************************************/
/*             General constants for the HALCON library                      */
/*****************************************************************************/
/*****************************************************************************/




/* Data Base */
#define H_UNDEFINED  UNDEF_KEY /* Ctype.h, CORE*.c do not change */


/*****************************************************************************/
/* Library defaults                                                          */
/*****************************************************************************/
#define PIXEL_RATIO               1.0        /* Default pixel ratio          */
#define NEIGHBOURHOOD             8          /* 4 or 8                       */
#define DEF_COMPACT_OBJ           FALSE      /* Use compact key for tuples   */
#define DEF_INIT_NEW_IMAGE        TRUE       /* set new image to 0           */
#define DEF_NO_OBJ_RESULT         H_MSG_TRUE /* if input-objs == no objects  */
#define DEF_EMPTY_OBJ_RESULT      H_MSG_TRUE /* if input-objs == empty region*/


/*****************************************************************************/
/* Max. values for the library                                               */
/*****************************************************************************/
#define RL_LENGTH                 1       /* Only for typedef                */
#define DEF_RL_LENGTH             50000   /* initial value for CurrentRL     */
#define MAX_CONTOUR_LENGTH        200000  /* max. # of contour points        */
#define MAX_CONTOURS_LENGTH       4000    /* Short contour (>= 2000 !!)      */
#define MAX_POLYGON_LENGTH        10000   /* max. # of polygon points        */
#define MAX_CHAIN_LENGTH          100000  /* max. # chain code points        */
#define MAX_GRAY_CHANNELS         1000    /* max. # of channels per image    */
#define MAX_OBJ_IMAGES            MAX_GRAY_CHANNELS   /* old */
#define MAX_OBJ_PER_PAR           100000  /* max. # of objets per parameter  */
#define OBJ_PER_PROC              5000    /* Typical # of objects per param. */
#define MAX_LINE                  MAX_FORMAT /* max. extend of a region      */
#define MAX_COLUMN                MAX_FORMAT /* max. extend of a region      */
#define MIN_LINE                  (-MAX_LINE)  /* min. extend of a region    */
#define MIN_COLUMN                (-MAX_COLUMN) /* min. extend of a region   */
#define DEF_LS_R                  "LS-R"  /* File containing image file names*/
#define FILE_TRANS_SIZE           1024*16 /* max. # of byte per read call    */
#define MAX_FILES                 20      /* max. # of open files            */
#define MAX_EDGE_LENGTH1          101     /* max. filter size                */
#define MAX_CLUSTER               1024    /* LearnNDim,ClassNDim             */
#define MAX_WC_NUM                3000    /* IPConvol.c                      */
#define MAX_CONVOL                50000   /* IPConvol.c (> 10000!)           */
#define ILLEGAL_VV                (INT1_MIN)  /* illegal vector              */
#define LD_MAX_FORMAT             15      /*  < 2^15 -1 (short!)             */
#define MAX_FORMAT                (1<<LD_MAX_FORMAT)
#define MAX_IMAGES                100000  /* max. total number of gray images*/
#define MAX_HSQRT                 10000   /* Hisqrt/Hfsqrt (max. 255 * 255)  */
#define MAX_WSTRINGS              2000    /* number of strings for write_*** */
#define MAX_LINE_NUM              2000    /* length of any normal text       */
#define MAX_IMAGE_DIR             (16*MAX_STRING) /* length of the image dir */


/*****************************************************************************/
/* Environment variables of HALCON                                           */
/*****************************************************************************/
#define HALCONROOT                "HALCONROOT"       /* Environment variable */
#define HALCONIMAGES              "HALCONIMAGES"     /* Environment variable */
#define HALCONHELP                "HALCONHELP"       /* Environment variable */
#define HALCONSPY                 "HALCONSPY"        /* Environment variable */
#define HALCONEXTENSIONS          "HALCONEXTENSIONS" /* Environment variable */


/*****************************************************************************/
/* Core Interface and operator implementation                                */
/*****************************************************************************/
#define MAX_PROC                  2000    /* Maximum number of operators     */
#define MAX_INP_OBJ_PAR           9       /* max # input object parameters   */
#define MAX_OUTP_OBJ_PAR          9       /* max # output object parameters  */
#define MAX_INP_CTRL_PAR          20      /* max # inpput control parameters */
#define MAX_OUTP_CTRL_PAR         20      /* max # output control parameters */

#define MAX_KEY_NAME              5       /* old */
#define KEY_NAME_LENGTH           20      /* old */
#define MAX_BUFFER                10      /* old */

/* Shortcut for object access */
#define REGION                    0       /* object component: region        */
#define CHORD                     0       /* object component: region (old)  */
#define IMAGE1                    1       /* object component: 1st image     */
#define IMAGE2                    2       /* object component: 2nd image     */
#define IMAGE3                    3       /* object component: 3rd image     */
#define IMAGE4                    4       /* object component: 4th image     */
#define IMAGE5                    5       /* object component: 5th image     */
#define IMAGE6                    6       /* object component: 6th image     */
#define IMAGE7                    7       /* object component: 7th image     */
#define IMAGE8                    8       /* object component: 8th image     */

/* Language interfaces */
#define PROG_LANGUAGE_C           "c"
#define PROG_LANGUAGE_CPP         "cpp"
#define PROG_LANGUAGE_SMALLTALK   "smalltalk"
#define PROG_LANGUAGE_PROLOG      "pro"
#define PROG_LANGUAGE_HDEVELOP    "hdevelop"
#define PROG_LANGUAGE_COM         "com"
#define MAX_PROG_LANG             40      /* max # language interfaces       */

#define NO_ACTION                 1       /* Language interface <-> CORE0    */
#define ONLY_CHECKS               2       /*              =#=                */
#define ACTION                    3       /*              =#=                */

/*****************************************************************************/
/* Help system                                                               */
/*****************************************************************************/
#define HELPFILE_NAME             "halcon"
#define HELPFILE_EXT              "hlp"
#define INDEXFILE_EXT             "idx"
#define STARTFILE_EXT             "sta"
#define NUMFILE_EXT               "num"
#define KEYWORD_EXT               "key"
#define SPRACHEN                  {"german", "english", ""}
#define PROGSPRACHEN              {"trias", "c", "c++", "smalltalk", ""}

/*****************************************************************************/
/* File extensions                                                           */
/*****************************************************************************/

#define TRAINF_EXT                "trf"   /* OCR training file               */
#define OCR_EXT                   "fnt"   /* OCR                             */
#define OCV_EXT                   "ocv"   /* OCV                             */
#define PS_EXTENSION              "ps"    /* Postscript                      */
#define TIFF_EXTENSION            "tiff"  /* TIFF                            */
#define EXP_EXTENSION             "exp"   /* Extension image description     */
#define IMAGE_EXTENSION           "ima"   /* Extension HALCON image          */
#define REGION_EXTENSION          "reg"   /* Extension region file           */
#define FILTER_EXTENSION          "fil"   /* Extension convol filters        */
#define LUT_EXTENSION             "lut"   /* Extension LUT                   */
#define GREYSE_EXT                "gse"   /* Extension gray struct element   */
#define BMP_EXTENSION             "bmp"   /* Extension Windows-BMP           */


/*****************************************************************************/
/* Runtime checking                                                          */
/*****************************************************************************/

#define RL_DUMP          "rl.dmp" /* File name for runlength dump data */
#define MAX_CHECK        10       /* Number of possible checks */
#define CHECK_ALL        ((1<<MAX_CHECK)-1) /* All checks */
#define CHECK_NONE       0       /* No checks */
#define CHECK_INTERFACE  (1<<0)  /* CORE0: all */
#define CHECK_PARAMETER  (1<<1)  /* CORE0: Parameters */
#define CHECK_DATA       (1<<2)  /* CORE1: Consistence/correctness 
                                    (data,parameters) */
#define CHECK_COLOR      (1<<3)  /* Error message or "best color" */
#define CHECK_TEXT       (1<<4)  /* Error message or window clipping */
#define CHECK_GIVE_ERROR (1<<5)  /* Suppress error message */
#define CHECK_DB         (1<<6)  /* DB0 + DB1 */
#define CHECK_CHORD      (1<<7)  /* Chord data during call */
#define CHECK_CLEAR      (1<<8)  /* DB error at ClearObj */
#define CHECK_FATHER     (1<<9)  /* For OpenXWindow */
#define DEF_CHECK        (CHECK_ALL & (~CHECK_CHORD) & (~CHECK_COLOR) & (~CHECK_TEXT))







/*****************************************************************************/
/* Graphics (Max/Min values)                                                 */
/*****************************************************************************/
/* Min/Max values */
#define MAX_WINDOW          600     /* Max. number of windows                */
#define XWINDOW             1       /* Internal code for graphic type        */
#define POSTSCRIPT_WINDOW   4       /* Internal code for graphic type        */
#define IMAGE_WINDOW        5       /* Internal code for graphic type        */
#define WIN32WINDOW         6       /* Internal code for graphic type        */
#define MAX_WINDOW_TYPES    6       /* Max. number of internal window types  */
#define MAX_WINDOW_CODE     (MAX_WINDOW_TYPES+1)
#define NUM_CURSOR          79      /* number of cursors in CURSOR           */
#define MAX_LINE_PATTERN    10      /* IOXSetLineStyle                       */
#define MAX_DEFAULT_FONT    10      /* Max. # fonts for X-Windows            */
#define MAX_FONT_LENGTH     255     /* Max. length of font name              */
#define MAX_LUT             40      /* Max. # of LUTs per screen (NUM_CMAPS) */
#define MAX_GRAPHIC_COLOR   64      /* max. number of graphics colors in LUT */
#define MAX_NUM_GREY        210     /* max. number of private gray values/LUT*/
#define MAX_LOADED_FONT     30      /* loaded fonts                          */
#define MAX_COLOR_NAME_LENGTH 40    /* max. length of a color name           */
#define MAX_DISP_PIXEL      256     /* Max. # of colors per HALCON call      */
#define MAX_SHAPE_STYLE     30      /* set_shape                             */
#define MAX_PAINT_STYLE     30      /* set_paint                             */
#define MAX_INSERT_STYLE    10      /* set_insert                            */
#define MAX_TEXTCURSOR      10      /* set_tshape                            */
#define MAX_CURSOR_LENGTH   20      /* Max. length of name in set_mshape     */
#define NUM_GRAPHIC_COLOR   30      /* number of graphic-colors used in LUT  */
#define MIN_GRAPHIC_PIXEL   50      /* index for first graphics color        */
#define MAX_FONT            2000    /* Max. # of predefined fonts            */
#define MAX_LUT_SAVE        60      /* max number of lut's to be cached      */


/*****************************************************************************/
/* Shortcuts (grahpics windows)                                              */
/*****************************************************************************/

/* set_window_type() */
#define XWINDOW_S           "X-Window"
#define IMAGE_WINDOW_S      "pixmap"
#define WIN32WINDOW_S       "WIN32-Window" 
#define POSTSCRIPT_WINDOW_S "PostScript"
#define EPS_WINDOW_S        "PostScript-EPSF"

#define SOLID_LINE          0       /* for IODisp0: line_style               */
#define DASHED_LINE         1       /*          -#-                          */
#define DASHED_APPROX       3       /* Approximation for dashed_line         */

#define LEFT_BUTTON         1       /* Code for left mouse button            */
#define MIDDLE_BUTTON       2       /* Code for center mouse button          */
#define RIGHT_BUTTON        4       /* Code for right mouse button           */

#define VISIBLE_MODE        0       /* normal visible window                 */
#define INVISIBLE_MODE      1       /* invisible window for query_*)         */
#define TRANSPARENT_MODE    2       /* transparent window                    */
#define BUFFER              3       /* Pixmap instead of window              */

#define CURSOR_L            1       /* Code for Cursor left                  */
#define CURSOR_R            2       /* Code for Cursor right                 */
#define CURSOR_U            3       /* Code for Cursor up                    */
#define CURSOR_D            4       /* Code for Cursor down                  */
#define INSERT              5       /* Code for Insert key                   */
#define CHARACTER           6       /* Code for "normal key"                 */
#define NONE                0       /* Code for keys to be ignored           */


/*****************************************************************************/
/* Default values (grahpics windows)                                         */
/*****************************************************************************/

#define DEF_PART_STYLE             0       /* Zoom mode: 0,1,2 */
#define DEF_GRAPHIC_BORDER_WIDTH   2       /* open_window() */
#define TV                         "television"  /* RGB color reduction  */
#define GRID_SCAN                  "grid_scan"
#define GRID_SCAN_FLOYD            "grid_scan_floyd_steinberg"
#define FLOYD_STEINBERG            "floyd_steinberg"   /* alt */
#define MEDIAN_CUT                 "median_cut"
#define MEDIAN_CUT_FLOYD           "median_cut_floyd_steinberg"
#define DEF_TRANS_RGB              GRID_SCAN_FLOYD
#define DEF_DRAW_MODE              "complement"
#define DEF_WINDOW_TITLE           "default"
#define DEFAULT_CURSOR             "arrow"
#define DEFAULT_TCURSOR            "xterm"
#define NO_CURSOR                  "none" 
#define DEFAULT_LUT                "default"
#define DEF_GRAPH_COLOR_2          2  /* default # graphic colors / 2 planes */
#define DEF_GRAPH_COLOR_4          5         /* 4 planes displays            */
#define DEF_GRAPH_COLOR_6          10        /* 6 planes displays            */
#define DEF_GRAPH_COLOR_8          20        /* 8 planes displays            */
#define DEF_NUM_GREY_4             8         /* 4 planes displays            */
#define DEF_NUM_GREY_6             50        /* 6 planes displays            */
#define DEF_NUM_GREY_8             140       /* 8 planes displays            */
#define DEF_NUM_GREY_PERCENTAGE    30        /* HGNumGreyPercentage          */
#define DEF_NUM_GRAPH_COLOR_PERCENTAGE 60    /* HGNumGraphicColorsPercentage */
#define DEF_HISTO_SCALE            1
#define DEF_PAINT_THRESH           127
#define DEF_XPACKAGE               (20*1024) /* Transfer to X-Server         */
#define DEF_WAVE_STEP              10        /* set_paint('3D-plot')         */
#define DEF_EYE_HEIGHT             120       /* set_paint('3D-plot')         */
#define DEF_EYE_DIST               150       /* set_paint('3D-plot')         */
#define DEF_WAVE_COLORED           FALSE     /* set_paint('3D-plot')         */
#define DEF_WAVE_HEIGHT            250       /* set_paint('3D-plot')         */
#define DEF_VECT_STEP              8         /* set_paint('vectorfield')     */
#define DEF_VECT_MIN_LENGTH        1         /* set_paint('vectorfield')     */
#define DEF_VECT_SCALE             2         /* set_paint('vectorfield')     */
#define DEF_CONTOUR_STEP           30        /* set_paint('contourline')     */
#define DEF_CONTOUR_COLORED        FALSE     /* set_paint('contourline')     */
#define DEF_GAMMA                  1.0       /* Gamma correction             */



/*****************************************************************************/
/* Mathematical constants                                                    */
/*****************************************************************************/

#ifndef PI
#ifdef  M_PI
#define PI               M_PI
#else
#define PI               3.14159265358979323846
#endif
#endif
#ifndef PI_2
#define PI_2             (PI / 2.0)
#endif
#ifndef PI_4
#define PI_4             (PI / 4.0)
#endif


#if defined (_WIN32) || defined (TRIMEDIA)
#ifndef M_PI
#define M_PI             PI
#endif
#ifndef M_PI_2
#define M_PI_2           (PI / 2.0)
#endif
#ifndef M_PI_4
#define M_PI_4           (PI / 4.0)
#endif
#endif


/*****************************************************************************/
/* Thread handling                                                           */
/*****************************************************************************/

#define GLOBAL_ID             NULL         /* 'global' operator handle       */
#define DEFAULT_AGENTS_NR     4            /* default # for agents           */

/* controlling the access to global context variables (see HInstance.c)      */
#define GV_WRITE_INFO         0            /* Flag: write global context var.*/
#define GV_READ_INFO          1            /* Flag: read global context var. */
#define GV_INIT_INFO          2            /* Flag: init. global context var.*/
#define GV_GET_ADRESS         3            /* Flag: get address of var.      */
#define GV_REALLOC_A          4            /* Flag: realloc an array         */
#define GV_LOCK               5            /* Flag: lock a mutex variable    */
#define GV_UNLOCK             6            /* Flag: unlock a mutex variable  */
#define GV_BOR_INFO           7            /* Flag: bitwise OR with variable */
#define GV_BAND_INFO          8            /* Flag: bitwise AND with variable*/
#define GV_WRITE_FORCE        9            /* Flag: force write in gl. var.; */
                                    /* (forces changes in reference version) */

/*****************************************************************************/
/* H_SYS_INFO_READ_ONLY                                                      */
/*****************************************************************************/

#define CLOCK_MODE_PROCESSOR_TIME      0  /* clock mode */
#define CLOCK_MODE_ELAPSED_TIME        1
#define CLOCK_MODE_PERFORMANCE_COUNTER 2
#define OCR_TRAINFILE_VERSION1_0       1  /* file version when writing OCR */
#define OCR_TRAINFILE_VERSION2_0       2  /* trainf */
#define OCR_TRAINFILE_VERSION3_0       3  /* trainf + UINT2 images */



/*****************************************************************************/
/* Defaults for operators get_image_pointer1_rect() and gen_image1_rect()    */
/*****************************************************************************/

#define DEFAULT_HORI_BIT_PITCH 8 
#define DEFAULT_BITS_PER_PIX 8

#endif
