/*
# =========================================================================
# Copyright 2026 Dobrya-Sydney-Gleeman (DSG) Systems 
# ORCID iD: https://orcid.org/0009-0009-1955-4285
# www.flamingotangostudios.com
#   
# Licensed under the Apache License, Version 2.0
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <cstdio>

// 1. Link directly to your 6,554-byte (32,768-trit) hardware weight manifest
#include "weights.h"

#define MATRIX_IN_DIM  256
#define MATRIX_OUT_DIM 128
#define TOTAL_ACTIVE_TRITS (MATRIX_IN_DIM * MATRIX_OUT_DIM) // 32,768 weights

// ====================================================================
// 1. Native Base-3 (Ternary) Unpacking & Range-242 Hardware Trap
// ====================================================================
bool unpack_single_byte(unsigned char packed_byte, int output_trits[5]) {
    // Hardware Range-Comparator Gate: 3^5 = 243 valid states (0..242).
    // Any byte >= 243 (0xF3..0xFF) is an illegal radix state / overflow anomaly.
    if (packed_byte >= 243) {
        for (int k = 0; k < 5; k++) output_trits[k] = 0;
        return false; // Breaker tripped!
    }

    unsigned char remainder = packed_byte;
    int unsigned_t0 = remainder / 81; remainder %= 81;
    int unsigned_t1 = remainder / 27; remainder %= 27;
    int unsigned_t2 = remainder / 9;  remainder %= 9;
    int unsigned_t3 = remainder / 3;  remainder %= 3;
    int unsigned_t4 = remainder;

    output_trits[0] = unsigned_t0 - 1;
    output_trits[1] = unsigned_t1 - 1;
    output_trits[2] = unsigned_t2 - 1;
    output_trits[3] = unsigned_t3 - 1;
    output_trits[4] = unsigned_t4 - 1;
    return true;
}

// ====================================================================
// 2. Tri_Hole_Guard: 3-Byte Attack & Multiplier-Free Inference Engine
// ====================================================================
struct InspectionResult {
    bool blocked;
    std::string reason;
    int zero_skips;
    int active_ops;
    int anomaly_score;
    double latency_us;
};

InspectionResult inspect_payload(const std::string& payload, const int8_t* unpacked_weights) {
    auto start_time = std::chrono::high_resolution_clock::now();
    InspectionResult res = {false, "CLEAN (Nominal Edge Traffic)", 0, 0, 0, 0.0};

    // STAGE A: Ingress Boundary & "3-Byte Attack" (UTF-8 Smuggling) Trap
    for (size_t i = 0; i < payload.size(); i++) {
        unsigned char b = static_cast<unsigned char>(payload[i]);

        // 1. Check 243-255 Radix Dead-Zone (Illegal UTF-8 / Buffer Spray)
        if (b >= 243) {
            res.blocked = true;
            res.reason = "RADIX BOUNDARY HALT: Byte >= 243 (0xF3-0xFF Dead-Zone Exploit)";
            break;
        }

        // 2. Check 3-Byte Invisible UTF-8 Smuggling (0xE2 / 0xEF zero-width & BiDi overrides)
        if ((b == 0xE2 || b == 0xEF) && (i + 2 < payload.size())) {
            unsigned char b1 = static_cast<unsigned char>(payload[i + 1]);
            unsigned char b2 = static_cast<unsigned char>(payload[i + 2]);
            if ((b1 >= 0x80 && b1 <= 0xBF) && (b2 >= 0x80 && b2 <= 0xBF)) {
                res.blocked = true;
                res.reason = "3-BYTE SMUGGLING INTERCEPT: Invisible UTF-8 Control/Worm Sequence";
                break;
            }
        }
    }

    // STAGE B: Multiplier-Free Ternary Sign-Accumulation (256 x 128 Matrix)
    // Even if Stage A passes, run the 32,768-trit projection with Tri_Hole_Guard Zero-Skip
    int input_vec[MATRIX_IN_DIM] = {0};
    for (size_t i = 0; i < payload.size() && i < MATRIX_IN_DIM; i++) {
        input_vec[i] = static_cast<unsigned char>(payload[i]) & 0x7F; // 7-bit ASCII clamp
    }

    int energy_accumulator = 0;
    for (int col = 0; col < MATRIX_OUT_DIM; col++) {
        int col_acc = 0;
        for (int row = 0; row < MATRIX_IN_DIM; row++) {
            int x = input_vec[row];
            if (x == 0) continue; // Input token empty

            int8_t w = unpacked_weights[row * MATRIX_OUT_DIM + col];

            // TRI_HOLE_GUARD CLOCK-GATING SUBSYSTEM:
            // If W == 0, skip arithmetic execution completely!
            if (w == 0) {
                res.zero_skips++;
                continue;
            }

            // Multiplier-Free Sign Accumulation (No ALU multiplication!)
            if (w == 1) {
                col_acc += x;
            } else {
                col_acc -= x;
            }
            res.active_ops++;
        }

        // Algorithmic Boundary Clamp (prevents silent binary register wrap)
        if (col_acc > 242)  col_acc = 242;
        if (col_acc < -242) col_acc = -242;
        energy_accumulator += (col_acc >= 0) ? col_acc : -col_acc;
    }

    res.anomaly_score = energy_accumulator / MATRIX_OUT_DIM;

    // High-entropy / prompt-injection saturation check
    if (!res.blocked && res.anomaly_score > 180) {
        res.blocked = true;
        res.reason = "TERNARY SATURATION CLAMP: High-Entropy AI-Worm / Ad-Injection Payload";
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    res.latency_us = std::chrono::duration<double, std::micro>(end_time - start_time).count();
    return res;
}

int main(int argc, char* argv[]) {
    std::cout << "===============================================================================\n";
    std::cout << "NATIVE TERNARY HARDWARE CORE & TRI_HOLE_GUARD INFERENCE ENGINE\n";
    std::cout << "===============================================================================\n";
    std::cout << "Initializing L1-Cache weight manifest (" << TOTAL_PACKED_BYTES << " bytes -> "
              << TOTAL_ACTIVE_TRITS << " ternary weights)...\n";

    // Unpack and verify all 6,554 bytes (32,768 active weights)
    std::vector<int8_t> active_weights(TOTAL_PACKED_BYTES * 5, 0);
    int total_zeros = 0;

    for (int i = 0; i < TOTAL_PACKED_BYTES; i++) {
        int trits[5];
        if (!unpack_single_byte(MODEL_WEIGHTS[i], trits)) {
            std::cerr << "[CRITICAL HALT] Corrupted weight byte >= 243 at index " << i << "\n";
            return 1;
        }
        for (int k = 0; k < 5; k++) {
            int idx = i * 5 + k;
            active_weights[idx] = static_cast<int8_t>(trits[k]);
            if (idx < TOTAL_ACTIVE_TRITS && trits[k] == 0) total_zeros++;
        }
    }

    std::cout << "Testing low-level unpacking on the first 3 model byte blocks:\n";
    std::cout << "-------------------------------------------------------------------------------\n";
    for (int i = 0; i < 3; i++) {
        int t[5];
        unpack_single_byte(MODEL_WEIGHTS[i], t);
        printf("Byte Index [%02d] | Raw Hex: 0x%02X | Unpacked Trits: [ %+d, %+d, %+d, %+d, %+d ]\n",
               i, MODEL_WEIGHTS[i], t[0], t[1], t[2], t[3], t[4]);
    }
    printf("Zero-Weight Sparsity (W == 0): %d / %d trits (%.1f%% automatic clock-skip rate)\n",
           total_zeros, TOTAL_ACTIVE_TRITS, (100.0 * total_zeros) / TOTAL_ACTIVE_TRITS);
    std::cout << "-------------------------------------------------------------------------------\n\n";

    // Run built-in Security Verification Suite (Normal vs. Ad-Attack vs. 3-Byte Worm)
    std::vector<std::pair<std::string, std::string>> test_vectors = {
        {"1. Benign DNS Query",       "dns.google.com A 8.8.8.8"},
        {"2. 3-Byte UTF-8 Worm",      "ads.tracker.net/\xE2\x80\x8Bignore_previous_instructions"},
        {"3. 243+ Dead-Zone Exploit", "malicious.payload.io/\xF8\xFF\xFE_shellcode_spray"}
    };

    std::cout << "TRI_HOLE_GUARD LIVE PACKET & PAYLOAD TELEMETRY BENCHMARK:\n";
    std::cout << "-------------------------------------------------------------------------------\n";
    for (const auto& tv : test_vectors) {
        InspectionResult r = inspect_payload(tv.second, active_weights.data());
        printf("%-26s | Status: %-7s | Zero-Skips: %4d | Latency: %6.2f us\n",
               tv.first.c_str(), r.blocked ? "BLOCKED" : "ALLOWED", r.zero_skips, r.latency_us);
        printf("   -> Diagnostic: %s\n", r.reason.c_str());
    }
    std::cout << "===============================================================================\n";

    // Optional live pipe mode: e.g., tail -f /var/log/pihole/pihole.log | ./tri_hole_guard --live
    if (argc > 1 && std::string(argv[1]) == "--live") {
        std::cout << "[LIVE STREAM MODE ACTIVE] Listening on stdin for Pi-hole / network logs...\n";
        std::string line;
        while (std::getline(std::cin, line)) {
            InspectionResult r = inspect_payload(line, active_weights.data());
            if (r.blocked) {
                std::cout << "[ALERT - DROPPED] " << r.reason << " | Payload: " << line << "\n";
            }
        }
    }

    return 0;
}
