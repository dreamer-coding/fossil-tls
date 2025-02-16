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
#include <fossil/test/framework.h>

#include "fossil/opentls/framework.h"


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(c_tls_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_tls_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_tls_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_tls_create_session) {
    int socket_fd = 1; // Example socket file descriptor

    // Create a new TLS session
    fossil_tls_session_t *session = fossil_tls_create_session(socket_fd);

    // Check if the session was created successfully
    ASSUME_NOT_CNULL(session);

    // Close the session
    fossil_tls_close_session(session);
}

FOSSIL_TEST_CASE(c_test_tls_load_certificates) {
    int socket_fd = 1; // Example socket file descriptor
    fossil_tls_session_t *session = fossil_tls_create_session(socket_fd);

    const char *cert_file = "cert.pem";
    const char *key_file = "key.pem";

    // Load certificates
    ASSUME_ITS_EQUAL_I32(0, fossil_tls_load_certificates(session, cert_file, key_file));

    // Close the session
    fossil_tls_close_session(session);
}

FOSSIL_TEST_CASE(c_test_tls_handshake) {
    int socket_fd = 1; // Example socket file descriptor
    fossil_tls_session_t *session = fossil_tls_create_session(socket_fd);

    // Perform the TLS handshake
    ASSUME_ITS_EQUAL_I32(0, fossil_tls_handshake(session));

    // Close the session
    fossil_tls_close_session(session);
}

FOSSIL_TEST_CASE(c_test_tls_send_and_recv) {
    int socket_fd = 1; // Example socket file descriptor
    fossil_tls_session_t *session = fossil_tls_create_session(socket_fd);

    const char *send_data = "Hello, TLS!";
    char recv_data[1024];

    // Perform the TLS handshake
    ASSUME_ITS_EQUAL_I32(0, fossil_tls_handshake(session));

    // Send data
    ASSUME_ITS_EQUAL_I32(strlen(send_data), fossil_tls_send(session, send_data, strlen(send_data)));

    // Receive data
    ASSUME_ITS_EQUAL_I32(strlen(send_data), fossil_tls_recv(session, recv_data, sizeof(recv_data)));

    // Close the session
    fossil_tls_close_session(session);
}

FOSSIL_TEST_CASE(c_test_tls_close_session) {
    int socket_fd = 1; // Example socket file descriptor
    fossil_tls_session_t *session = fossil_tls_create_session(socket_fd);

    // Close the session
    fossil_tls_close_session(session);

    // Check if the session was closed successfully
    ASSUME_ITS_CNULL(session);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_tls_tests) {
    FOSSIL_TEST_ADD(c_tls_suite, c_test_tls_create_session);
    FOSSIL_TEST_ADD(c_tls_suite, c_test_tls_load_certificates);
    FOSSIL_TEST_ADD(c_tls_suite, c_test_tls_handshake);
    FOSSIL_TEST_ADD(c_tls_suite, c_test_tls_send_and_recv);
    FOSSIL_TEST_ADD(c_tls_suite, c_test_tls_close_session);

    FOSSIL_TEST_REGISTER(c_tls_suite);
}
