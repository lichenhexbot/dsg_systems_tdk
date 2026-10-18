# dsg_systems_tdk

TinyGemma (Dobrya): A 1.58-Bit Co-Designed Discrete Text Diffusion Engine with Vision and T++ Ternary Development Kit (TDK) Security. Includes T++ Tritcode definitions.

revolves around:

Ternary DiffusionGemma weights.h (2.6 m)
• Matrix Structure Alignment: Statically links token variables and active attention gates directly with low-level execution channels.
• Complete Sub-Word Binding: Explicitly maps the 256k Gemma vocabulary embedding boundaries to hardware registers.
• Zero Runtime Translation: Enables the C++ core engine to resolve token weights without multi-cycle address decoding overhead.

To be included in future MRL (Matryoshka Representation Learning) for novel, organic Ternary datasets for future Gemma models. 

# DSG Systems: TinyGemma (Dobrya 2.6M)
## Full-Stack Ternary Development Kit (TDK) & Implementation Architecture

[![License: Apache 2.0](https://shields.io)](https://opensource.org)
[![License: CERN-OHL-S](https://shields.io)](https://ohwr.org)
[![Patent Priority: USPTO](https://shields.io)]()

Welcome to the public-facing deployment toolkit for **TernaryDiffusionGemma 2.6M 1.0 (Tri-Hole Firmware)**, code-named **"Dobrya"** (TinyGemma). This full-stack, hardware-software co-designed computing engine is engineered to dismantle the traditional "Binary Tax" at the decentralized edge. By binding a bidirectional discrete text-diffusion canvas to the open-weights Google Gemma 256k vocabulary matrix, this ecosystem entirely replaces dynamic, high-precision floating-point Multiply-Accumulate (MAC) routines with single-cycle conditional instruction branches.

---

## 🛠️ The Ternary Development Kit (TDK) File Manifest

This repository contains the complete open-source primitives required to build, optimize, and simulate the multiplier-free ternary execution loop:

### 💻 1. Core Software & Firmware Interface Modules
*   `unpacker.cpp` — Bare-metal, maximum-optimization C++ execution bridge that converts compressed radix-3 data arrays into lightning-fast conditional branch loops.
*   `weights.h` — Static C++ structural header mapping active tensor parameters and vocabulary array configurations directly to hardware register channels.
*   `nano_weights.bin` — The ultra-compact, fully-quantized 2.6M model brain file. Restricted to base-3 bounds, the entire payload is compressed by **~95%** down to a microscopic **~520 KB**, residing entirely within local CPU L3 cache windows.

### 🧠 2. Quantization-Aware Training (QAT) Modules
*   `run_gemma_automaton.py` — Native PyTorch training loop orchestrating multi-directional text-diffusion canvas masking utilizing a custom Straight-Through Estimator (STE) gradient-passing layer.
*   `trit_packer.py` — Mathematical matrix compression utility that serializes signed ternary vectors into unsigned 8-bit byte formats (3⁵ = 243 ≤ 255) to fit standard binary block storage boundaries.

### 👁️ 3. Cross-Modal Ingestion & Data Protocols
*   `vision_transformer_color.py` — Dual-mode cross-modal frontend vision pipeline. Natively processes Retinex log-reflectance operations to extract illumination-invariant structural signatures, mapping raw frames directly to 128-Trit Matryoshka Semantic Embeddings for fast similarity search.
*   `T_plus_plus_spec.md` — The immutable character serialization dictionary mapping a strict, fixed-width 6-Trit Symbol Envelope across standard ASCII configurations.

---

## 🚀 Quick Start: Deploying the Edge Sandbox Bridge

To compile and execute the bare-metal simulation loop natively on standard commodity ARMv8-A (e.g., a Raspberry Pi edge node) or open RISC-V vector microarchitectures under maximum optimization, execute:

### `CPPBLOCKED` (Passive Telemetry & Alert Mode — Non-Disruptive)

1. Place `weights.h` in the same folder as `unpacker.cpp`.
2. Compile with maximum optimization:
   ```bash
   g++ -O3 unpacker.cpp -o tri_hole_guard

Stream live DNS traffic into the engine:

sudo tcpdump -l -n -i any port 53 | ./tri_hole_guard --live

if using ./tri_hole_guard and tcpdump in a separate window, the former will respond to "echo", so you can preview a website in terminal, ie, "echo <www.hotmail.com>"
---

## 🌿 Multi-Branch Verification Setup
To accommodate varying research, development, and testing methodologies, this repository maintains separate file branches to switch between runtime enforcement profiles:

1.  **`main` Branch (Production Shield):** Contains the hardened, absolute zero-trust configuration of Tri_Hole_Guard. All unvetted or out-of-bounds streams are forcefully blocked at the silicon register entry point.
2.  **`zenity-demo` Branch (Interactive Verification):** Implements thresholding rules paired with native Linux graphical warnings. To observe active clock-gating resets, sign-inversions, and automated process-breaker alerts visually on your desktop environment, pull and build the demo branch, same as above:
   . Place `weights.h` in the same folder as `unpacker.cpp`.
2. Compile with maximum optimization:
   ```bash
   g++ -O3 unpacker.cpp -o tri_hole_guard

Stream live DNS traffic into the engine:

sudo tcpdump -l -n -i any port 53 | ./tri_hole_guard --live

NOTE: THIS VERSION WILL CLOSE ALL TABS OF MOZILLA BROWSER, IF THE EMULATION IS TESTED, OR AN ATTACK NOTICED. PLEASE SAVE YOUR WORK AND PROCEED ACCORDINGLY!

More information about "Skips" and "Scores", here: https://telegra.ph/Skips-And-Scores-a-chat-with-Gemini-Argon-10-18
---

## ⚖️ Intellectual Property, Protection, & Disclosures
Following the successful formal registration of our priority micro-patent protections with the United States Patent and Trademark Office (**U.S. Patent Application No. 64/177,716**, October 2026), the software source primitives contained in this repository are disseminated openly under the permissive terms of the **Apache License 2.0**. 

All physical hardware substrate paths, multi-rail logic gates, clock-gating circuit breaker schematics, and extended -602 macro-gating configurations remain fully protected and tightly governed under the copyleft terms of the **CERN Open Hardware License v2 - Strongly Reciprocal (CERN-OHL-S)**. 

---

## 🛑 Licensing Foundations & Gemma Terms of Use
This model suite is a derivative work of the Google Gemma architecture. This distribution is strictly bound by and subject to the official **Gemma Terms of Use** https://gemma.ai/resources/terms/ and the **Gemma Prohibited Use Policy** http://gemma.ai/resources/prohibited_use_policy. 

The base model weight definitions for the "Dobrya" (TinyGemma / TernaryDiffusionGemma) architecture are derived utilizing parameters from the Google Gemma family. In accordance with open licensing frameworks, all secondary software optimization primitives are disseminated under the Apache License 2.0.
