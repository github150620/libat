#include "at.h"

static char *split(char src[], char *dst, uint8_t n) {
    int i;
    for (i=0;i<n;i++) {
        if ((*p != '\0') && (*p != ',') && (*p != '\r') && (*p != '\n')) {
            break;
        }
        dst[i] = src[i];
    }
    dst[i] = '\0';

    return &src[i];
}

static char *atou8(char s[], uint8_t *i) {
    char *p = s;

    *i = 0;
    while ( *p >= '0' && *p <= '9') {
        *i = (*i) * 10 + (*p - '0');
        p++;
    }
    return p;
}


int AT_Parse_common(char response[], at_common_t *r) {
    r->result = AT_UNKNOWN;

    if (strncmp(response, "\r\nOK\r\n") == 0) {
        r->result = AT_OK;
        return 0;
    }
    if (strncmp(response, "\r\nERROR\r\n") == 0) {
        r->result = AT_ERROR;
        return 0;
    }
    return -1;
}

int AT_Parse_CPIN(char response[], at_cpin_t *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) == 0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n+CPIN: ", 9) == 0) {
        p += 9;
    } else {
        return -1;
    }

    split(p, r->cpin, sizeof(r->cpin));
    if (*p == '\r') {
        p++;
    } else {
        return -1;
    }

    if (*p == '\n') {
        p++;
    } else {
        return -1;
    }

    if (strncmp(p, "\r\nOK\r\n", 6) == 0) {
        r->result = AT_OK;
    } else {
        return -1;
    }

    return 0;
}

int AT_Parse_CCID (char *response, at_ccid_t *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) == 0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n", 2) == 0) {
        p += 2;
    } else {
        return -1;
    }

    p = split(p, r->iccid, sizeof(r->iccid));

    if (*p == '\r') {
        p++;
    } else {
        return -1;
    }

    if (*p == '\n') {
        p++;
    } else {
        return -1;
    }

    if (strncmp(p, "\r\nOK\r\n", 6) == 0) {
        r->result = AT_OK;
    } else {
        return -1;
    }

    return 0;
}

int AT_Parse_CSQ(char response[], at_csq_t *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) ==0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n+CSQ: ", 8) == 0) {
        p += 8;
    } else {
        return -1;
    }

    p = atou8(p, &(csq->rssi));
    
    if (*p == ',') {
        p++;
    } else {
        return -1;
    }

    if (*p == ' ') {
        p++;
    }

    p = atou8(p, &(csq->ber));

    if (*p == '\r') {
        p++;
    } else {
        return -1;
    }

    if (*p == '\n') {
        p++;
    } else {
        return -1;
    }

    if (strncmp(p, "\r\nOK\r\n", 6) == 0) {
        r->result = AT_OK;
    } else {
        return -1;
    }

    return 0;
}

int AT_Parse_CGATT(char *response, at_cgatt_t *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) ==0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n+CGATT: ", 10) == 0) {
        p += 10;
    } else {
        return -1;
    }

    p = atou8(p, &(r->cgatt));

    return 0;
}

int AT_Parse_CSTT(char response[], at_cstt_t *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) ==0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n+CSTT: ", 10) == 0) {
        p += 10;
    } else {
        return -1;
    }

    p = split(p, &(r->apn), sizeof(r->apn));
    if (*p == ',') {
        p++;
    } else {
        return -1;
    }

    p = split(p, &(r->user), sizeof(r->user));
    if (*p == ',') {
        p++;
    } else {
        return -1;
    }

    p = split(p, &(r->pwd), sizeof(r->pwd));
    if (*p == '\r') {
        p++;
    } else {
        return -1;
    }

    if (*p == '\n') {
        p++;
    } else {
        return -1;
    }

    return 0;
}

int AT_Parse_CIFSR(char *response, at_cifsr *r) {
    char *p = response;
    r->result = AT_UNKNOWN;

    if (strncmp(p, "\r\nERROR\r\n", 9) ==0) {
        r->result = AT_ERROR;
        return 0;
    }

    if (strncmp(p, "\r\n", 2) == 0) {
        p += 2;
    } else {
        return -1;
    }

    p = split(p, r->ip, sizeof(r->ip));

    if (*p == '\r') {
        p++;
    } else {
        return -1;
    }

    if (*p == '\n') {
        p++;
    } else {
        return -1;
    }

    return 0;
}


