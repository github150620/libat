#ifndef _AT_H_
#define _AT_H_

typedef enum {
  AT_RESPONSE_OK      = 0,
  AT_RESPONSE_ERROR   = 1,
  AT_RESPONSE_UNKNOWN = 99
}at_result_t;

typedef struct {
  at_result_t result;
}at_common_t;

/* 
 * Command
 *   AT+CPIN?
 * Response
 *   \r\n+CPIN: <code>\r\n
 *   \r\nOK\r\n
 * Parameters
 * <code>
 *   READY
 *   SIM PIN
 *   SIM PUK
 *   PH_SIM PIN
 *   PH_SIM PUK
 *   SIM PIN2
 */
typedef struct {
  at_result_t result;
  char cpin[11];
}at_cpin_t;

/*
 * Command
 *   AT+CCID
 * Response
 *   \r\n<ccid>\r\n
 *   \r\nOK\r\n
 */
typedef struct {
  at_result_t result;
  char        iccid[21];
}at_iccid_t;

/*
 * Command
 *   AT+CSQ?
 * Parameters
 * <rssi>
 *   0       -115dBm or less
 *   1       -111dBm
 *   2...30  -110...-54 dBm
 *   31      -52 dBm or greater
 *   99      not known or not detectable
 * <ber>
 *   0...7   As RXQUAL values in the table in GSM 05.08 [20] subclass 7.2.4
 *   99      Not known or not detectable
 */
typedef struct {
  at_result_t result;
  uint8_t rssi;
  uint8_t ber;
}at_csq_t;

/*
 * Command
 *   AT+CREG?
 * Response
 *   \r\n+CREG: <n>,<stat>[,<lac>,<ci>]\r\n
 *   \r\nOK\r\n
 * Parameters
 * <n>
 *   0  Disable network registration unsolicited result code
 *   1  +CREG: <stat>
 *   2  +CREG: <stat>[,<lac>,<ci>]
 * <stat>
 *   0  Not registered
 *   1  Registered, home network
 *   2  Not registered
 *   3  Registration denied
 *   4  Unknown
 *   5  Registered, roaming
 */
typedef struct {
  at_result_t result;
  uint8_t     n;
  uint8_t     stat;
  char        lac[4];
  char        ci[4];
}at_creg_t;

/*
 * Command
 *   AT+CGREG?
 * Response
 *   \r\n+CGREG: <n>,<stat>[,<lac>,<ci>]\r\n
 *   \r\nOK\r\n
 * Parameters
 * <n>
 *   0  Disable network registration unsolicited result code
 *   1  +CREG: <stat>
 *   2  +CREG: <stat>[,<lac>,<ci>]
 * <stat>
 *   0  Not registered
 *   1  Registered, home network
 *   2  Not registered
 *   3  Registration denied
 *   4  Unknown
 *   5  Registered, roaming
 */
typedef struct {
  at_result_t result;
  uint8_t     n;
  uint8_t     stat;
  char        lac[4];
  char        ci[4];
}at_cgreg_t;

typedef struct {
  at_result_t result;
  uint8_t     cgatt;
}at_cgatt_t;

typedef struct {
    at_result_t result;
    char apn[8];
    char user[3];
    char pwd[3];
}at_cstt_t;

typedef struct {
  at_result_t result;
  char        ip[16];
}at_cifsr_t;

int AT_Parse_Common(char response[], at_common_t *r);
int AT_Parse_CPIN  (char response[], at_cpin_t   *r);
int AT_Parse_ICCID (char response[], at_iccid_t   *r);
int AT_Parse_CSQ   (char response[], at_csq_t    *r);
int AT_Parse_CREG  (char response[], at_creg_t   *r);
int AT_Parse_CGREG (char response[], at_cgreg_t  *r);
int AT_Parse_CSTT  (char response[], at_cstt_t   *r);
int AT_Parse_CGATT (char response[], at_cgatt_t  *r);
int AT_Parse_CIICR (char response[], at_common_t *r);
int AT_Parse_CIFSR (char response[], at_cifsr_t  *r);

#endif
