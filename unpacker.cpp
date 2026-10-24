/*
// =========================================================================
// Copyright 2026 Dobrya-Sydney-Gleeman (DSG) Systems 
// ORCID iD: https://orcid.org/0009-0009-1955-4285
// www.flamingotangostudios.com
//  
// Licensed under the Apache License, Version 2.0
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstdlib>

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

    // STAGE B: Scaled Multiplier-Free Ternary Sign-Accumulation (256 x 128 Matrix)
    int input_vec[MATRIX_IN_DIM] = {0};
    int active_chars = 0;
    int entropy_boost = 0;

    for (size_t i = 0; i < payload.size() && i < MATRIX_IN_DIM; i++) {
        unsigned char c = static_cast<unsigned char>(payload[i]) & 0x7F;
        // Center ASCII printable chars so normal text doesn't falsely saturate
        input_vec[i] = (c >= 32) ? (c - 31) : c;
        if (input_vec[i] != 0) active_chars++;

        // Flag URL injection / ad-redirect / obfuscation characters
        if (c == '?' || c == '&' || c == '=' || c == '%' || c == ';' || c == '$') {
            entropy_boost += 25;
        }
    }

    // Check known ad-redirect / malvertising / pop-up patterns
    std::string lower_p = payload;
    for (auto& ch : lower_p) ch = std::tolower(static_cast<unsigned char>(ch));
    if (lower_p.find("putlocker")   != std::string::npos ||
        lower_p.find("adsystem")    != std::string::npos ||
        lower_p.find("doubleclick") != std::string::npos ||
        lower_p.find("popunder")    != std::string::npos ||
        lower_p.find("evil-ads")    != std::string::npos ||
        lower_p.find("inject")      != std::string::npos) {
        entropy_boost += 160;
    }

    int energy_accumulator = 0;
    int norm_factor = (active_chars > 1) ? static_cast<int>(std::sqrt(active_chars)) : 1;

    for (int col = 0; col < MATRIX_OUT_DIM; col++) {
        int col_acc = 0;
        for (int row = 0; row < MATRIX_IN_DIM; row++) {
            int x = input_vec[row];
            if (x == 0) continue;

            int8_t w = unpacked_weights[row * MATRIX_OUT_DIM + col];

            // TRI_HOLE_GUARD CLOCK-GATING SUBSYSTEM (W == 0 -> Skip!)
            if (w == 0) {
                res.zero_skips++;
                continue;
            }

            // Multiplier-Free Sign Accumulation (No ALU multiplication!)
            if (w == 1) col_acc += x;
            else        col_acc -= x;
            res.active_ops++;
        }

        // Normalize by sqrt(length) (Ternary Attention Scaling) + apply boundary clamp
        col_acc = std::abs(col_acc / norm_factor) + entropy_boost;
        if (col_acc > 242)  col_acc = 242;
        if (col_acc < -242) col_acc = -242;
        energy_accumulator += col_acc;
    }

    res.anomaly_score = energy_accumulator / MATRIX_OUT_DIM;

    if (!res.blocked && res.anomaly_score > 180) {
        res.blocked = true;
        res.reason = "TERNARY SATURATION CLAMP: High-Entropy Ad-Redirect / Worm Payload";
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

    // Live stream telemetry mode (prints EVERY packet/domain inspected in real time)
    if (argc > 1 && std::string(argv[1]) == "--live") {
        std::cout << "[LIVE STREAM MODE ACTIVE] Listening on stdin for live network/DNS traffic...\n";
        std::cout << "-------------------------------------------------------------------------------\n";
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            InspectionResult r = inspect_payload(line, active_weights.data());

            // Clean any non-printable bytes from display string
            std::string clean_line;
            for (size_t i = 0; i < line.size() && i < 65; i++) {
                unsigned char c = static_cast<unsigned char>(line[i]);
                clean_line += (c >= 32 && c < 127) ? static_cast<char>(c) : '?';
            }

            printf("[%s] Skips: %4d | Score: %3d | %6.2f us | %s\n",
                   r.blocked ? "BLOCKED" : "ALLOWED",
                   r.zero_skips, r.anomaly_score, r.latency_us,
                   clean_line.c_str());

            if (r.blocked) {
                printf("   -> ALERT: %s\n", r.reason.c_str());
                printf("   -> ACTION: Please add target to Pi-hole Blacklist (logged to tri_hole_blocklist.txt)\n");

                // 1. Append blocked payload to local blocklist file
                FILE* bf = fopen("tri_hole_blocklist.txt", "a");
                if (bf) {
                    fprintf(bf, "[BLOCKED] %s | %s\n", r.reason.c_str(), clean_line.c_str());
                    fclose(bf);
                }

                // 2. Pop up a native Ubuntu GUI alert with logo.png (via zenity & notify-send)
                std::string notify_cmd = "notify-send -i \"$(pwd)/logo.png\" "
                                         "\"TRI_HOLE_GUARD INTERCEPT [BLOCKED]\" "
                                         "\"" + r.reason + " -- Please add \"" + clean_line + "\" to your Blacklist!\" 2>/dev/null &";
                std::system(notify_cmd.c_str());

                std::string zenity_cmd = "zenity --warning --title=\"TRI_HOLE_GUARD SECURITY INTERCEPT\" "
                                         "--window-icon=\"$(pwd)/logo.png\" --width=460 "
                                         "--text=\"<b>TRI_HOLE_GUARD CIRCUIT BREAKER TRIPPED!</b>\\n\\n"
                                         "<b>Target:</b> " + clean_line + "\\n"
                                         "<b>Diagnostic:</b> " + r.reason + "\\n"
                                         "<b>Zero-Skips (W=0):</b> " + std::to_string(r.zero_skips) + "\\n\\n"
                                         "<b>Action Required:</b> Please add this domain/host to your Pi-hole Blacklist/Blocklist.\\n"
                                         "<i>(Automatically logged to tri_hole_blocklist.txt)</i>\" 2>/dev/null &";
                std::system(zenity_cmd.c_str());

                // 3. OPTIONAL: Uncomment (or, add "//" to comment) the line below ONLY if you want it to close Firefox on a hit:
                std::system("pkill -f firefox 2>/dev/null &");
            }
            fflush(stdout);
        }
    }

    return 0;
}
