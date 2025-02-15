/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/opentls/tls.h"

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void fossil_tls_init(void) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

fossil_tls_session_t *fossil_tls_create_session(int socket_fd) {
    fossil_tls_session_t *session = malloc(sizeof(fossil_tls_session_t));
    if (!session) return NULL;
    
    session->ctx = SSL_CTX_new(TLS_client_method());
    if (!session->ctx) {
        free(session);
        return NULL;
    }
    
    session->ssl = SSL_new(session->ctx);
    if (!session->ssl) {
        SSL_CTX_free(session->ctx);
        free(session);
        return NULL;
    }
    
    SSL_set_fd(session->ssl, socket_fd);
    return session;
}

int fossil_tls_load_certificates(fossil_tls_session_t *session, const char *cert_file, const char *key_file) {
    if (SSL_CTX_use_certificate_file(session->ctx, cert_file, SSL_FILETYPE_PEM) <= 0) return -1;
    if (SSL_CTX_use_PrivateKey_file(session->ctx, key_file, SSL_FILETYPE_PEM) <= 0) return -1;
    return 0;
}

int fossil_tls_handshake(fossil_tls_session_t *session) {
    return SSL_connect(session->ssl);
}

int fossil_tls_send(fossil_tls_session_t *session, const void *buf, size_t len) {
    return SSL_write(session->ssl, buf, len);
}

int fossil_tls_recv(fossil_tls_session_t *session, void *buf, size_t len) {
    return SSL_read(session->ssl, buf, len);
}

void fossil_tls_close_session(fossil_tls_session_t *session) {
    if (!session) return;
    SSL_shutdown(session->ssl);
    SSL_free(session->ssl);
    SSL_CTX_free(session->ctx);
    free(session);
}

void fossil_tls_cleanup(void) {
    EVP_cleanup();
    ERR_free_strings();
}
