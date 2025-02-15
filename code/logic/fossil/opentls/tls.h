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
#ifndef FOSSIL_OPENTLS_TLS_H
#define FOSSIL_OPENTLS_TLS_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    SSL_CTX *ctx;
    SSL *ssl;
} fossil_tls_session_t;

/**
 * Initialize the OpenSSL library.
 * This function must be called before any other OpenSSL functions are used.
 */
void fossil_tls_init(void);

/**
 * Create a new TLS session.
 * 
 * @param socket_fd The file descriptor of the socket to be used for the TLS session.
 * @return A pointer to the newly created TLS session structure.
 */
fossil_tls_session_t *fossil_tls_create_session(int socket_fd);

/**
 * Load certificates for the TLS session.
 * 
 * @param session The TLS session structure.
 * @param cert_file The path to the certificate file.
 * @param key_file The path to the private key file.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_tls_load_certificates(fossil_tls_session_t *session, const char *cert_file, const char *key_file);

/**
 * Perform the TLS handshake.
 * 
 * @param session The TLS session structure.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_tls_handshake(fossil_tls_session_t *session);

/**
 * Send data over the TLS session.
 * 
 * @param session The TLS session structure.
 * @param buf The buffer containing the data to be sent.
 * @param len The length of the data to be sent.
 * @return The number of bytes sent, or a negative error code on failure.
 */
int fossil_tls_send(fossil_tls_session_t *session, const void *buf, size_t len);

/**
 * Receive data over the TLS session.
 * 
 * @param session The TLS session structure.
 * @param buf The buffer to store the received data.
 * @param len The maximum length of data to be received.
 * @return The number of bytes received, or a negative error code on failure.
 */
int fossil_tls_recv(fossil_tls_session_t *session, void *buf, size_t len);

/**
 * Close the TLS session.
 * 
 * @param session The TLS session structure to be closed.
 */
void fossil_tls_close_session(fossil_tls_session_t *session);

/**
 * Cleanup the OpenSSL library.
 * This function should be called to free any resources allocated by OpenSSL.
 */
void fossil_tls_cleanup(void);

#ifdef __cplusplus
}
#include <string>

/**
 * This namespace provides a set of functions for handling input and output operations.
 */
namespace fossil {

    namespace tls {
        
        class Session {
        public:
            Session(int socket_fd) {
                session_ = fossil_tls_create_session(socket_fd);
            }

            ~Session() {
                fossil_tls_close_session(session_);
            }

            int load_certificates(const char *cert_file, const char *key_file) {
                return fossil_tls_load_certificates(session_, cert_file, key_file);
            }

            int load_certificates(const std::string &cert_file, const std::string &key_file) {
                return fossil_tls_load_certificates(session_, cert_file.c_str(), key_file.c_str());
            }

            int handshake() {
                return fossil_tls_handshake(session_);
            }

            int send(const void *buf, size_t len) {
                return fossil_tls_send(session_, buf, len);
            }

            int recv(void *buf, size_t len) {
                return fossil_tls_recv(session_, buf, len);
            }

            void close() {
                fossil_tls_close_session(session_);
            }

        private:
            fossil_tls_session_t *session_;
        };
    }
}

#endif

#endif /* FOSSIL_IO_FRAMEWORK_H */
