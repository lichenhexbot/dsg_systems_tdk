# dsg_systems_tdk

TinyGemma (Dobrya): A 1.58-Bit Co-Designed Discrete Text Diffusion Engine with Vision and T++ Ternary Development Kit (TDK) Security. Includes T++ Tritcode definitions.

Revolves around:

Ternary DiffusionGemma weights.h (2.6 m)
• Matrix Structure Alignment: Statically links token variables and active attention gates directly with low-level execution channels.
• Complete Sub-Word Binding: Explicitly maps the 256k Gemma vocabulary embedding boundaries to hardware registers.
• Zero Runtime Translation: Enables the C++ core engine to resolve token weights without multi-cycle address decoding overhead.

To be included in future MRL (Matryoshka Representation Learning) for novel, organic Ternary datasets within Gemma models. 

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
    1. Place a .jpg into your working folder named "test_room.jpg". Then run "vision_transformer_color.py" from your working folder.
  
    2. Lines 129-133 can be edited to toggle Retinex filter on or off. Just place a "#" next to the option you want off, and remove a "#" for the option you wish to use.  
 
      "#" USE_RETINEX_FILTER = True    # <-- Retinex Log-Illumination Edge Mode

          USE_RETINEX_FILTER = False # <-- Uncomment this line for Regular Ternary Photo Mode!


  3. To learn more on REX (Radix plus Retinex) toggling, check out telegra.ph/Gemini-Argon-on-REX-vision-10-18


*   `T_plus_plus_spec.md` — The immutable character serialization dictionary mapping a strict, fixed-width 6-Trit Symbol Envelope across standard ASCII configurations.

`T_plus_plus_spec.md` is the official DSK_Systems_TDK/Dobrya/TinyGemma Ternary definitions dataset. Here, 127 Ascii characters and integers are mapped, with room for -602 more characters to be assigned for special functions in future T++ updates.

---

## 🚀 Quick Start: Deploying the Edge Sandbox Bridge

To compile and execute the bare-metal simulation loop natively on standard commodity ARMv8-A (e.g., a Raspberry Pi edge node) or open RISC-V vector microarchitectures under maximum optimization, execute:

### `CPPBLOCKED` (Passive Telemetry & Alert Mode — Non-Disruptive)

1. Place `weights.h` in the same folder as `unpacker.cpp`.
2. Compile with maximum optimization:
   ```bash
   g++ -O3 unpacker.cpp -o tri_hole_guard

Stream live DNS traffic into the engine:
  
"sudo tcpdump -l -n -i any port 53 | ./tri_hole_guard --live"

or, if you prefer, run separately. "./tri_hole_guard --live"


if using ./tri_hole_guard and tcpdump in a separate window, the former will respond to "echo", so you can preview a website in terminal, ie, "echo <www.testwebsite.com>"

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

---
**About tri_hole_guard "Skips" and "Scores":**

🛡️ Understanding "Skips" and "Scores" in Tri_Hole_Guard:

Tri_hole_guard is not meant to replace the traditional Pi-Hole, but to work with it, an an extra layer which provides metrics about possible anomalous activity.

When you run the tri_hole_guard live network emulation, the terminal outputs two critical metrics for every processed packet: Skips and Scores. Here is exactly what is happening under the hood:

⏩ 1. Zero-Skips (Hardware Efficiency)

In a traditional AI model, parameters are high-precision floating-point numbers (like 0.00314). Even if a number is incredibly close to zero, the CPU still has to execute a heavy, power-hungry multiplication operation.

Because Dobrya is a 1.58-bit Ternary model, our weights are restricted to exactly three states: -1, 0, or +1.
When the system encounters a weight of 0, multiplying the input by zero will always equal zero. Instead of doing the math, Tri_Hole_Guard triggers a Zero-Skip—it intentionally bypasses the CPU's Arithmetic Logic Unit (ALU) entirely and jumps to the next instruction.

What it means for you: A high "Skip" count means the model is automatically clock-gating the hardware, saving massive amounts of power, reducing thermal heat, and processing the packet in microseconds.

🚨 2. Anomaly Scores (Threat Detection)

The Score is the ultimate threat-level calculation of the incoming data payload.
Instead of just checking a static list of bad websites, the incoming text (like a DNS request or a browser URL) is mathematically pushed through the 2.6M ternary neural matrix via additive accumulation.

    Low Scores (e.g., 0-50): Standard, human-readable web traffic and benign DNS pings pass through the matrix cleanly.
    High Scores (e.g., 180+): Malicious payloads—such as zero-click AI worms, high-entropy ad-tracking strings, buffer-overflow attempts, or obfuscated URL injections (lots of %, =, ?, and invisible UTF-8 characters)—cause the mathematical matrix to rapidly saturate.

When the accumulator detects this mathematical saturation, the Score spikes. If it crosses the safety threshold (180), the Tri_Hole_Guard Circuit Breaker trips, forcefully blocking the payload and alerting the user before the exploit can reach the local execution stack.


for more information about "Skips and "Scores", check out telegra.ph/Skips-And-Scores-a-chat-with-Gemini-argon-10-18
---


## ⚖️ Intellectual Property, Protection, & Disclosures
Following the successful formal registration of our priority micro-patent protections with the United States Patent and Trademark Office (**U.S. Patent Application No. 64/177,716**, October 2026), the software source primitives contained in this repository are disseminated openly under the permissive terms of the **Apache License 2.0**. 

All physical hardware substrate paths, multi-rail logic gates, clock-gating circuit breaker schematics, and extended -602 macro-gating configurations remain fully protected and tightly governed under the copyleft terms of the **CERN Open Hardware License v2 - Strongly Reciprocal (CERN-OHL-S)**. 

---

## 🛑 Licensing Foundations & Gemma Terms of Use
This model suite is a derivative work of the Google Gemma architecture. This distribution is strictly bound by and subject to the official **Gemma Terms of Use** https://gemma.ai/resources/terms/ and the **Gemma Prohibited Use Policy** http://gemma.ai/resources/prohibited_use_policy. 

The base model weight definitions for the "Dobrya" (TinyGemma / TernaryDiffusionGemma) architecture are derived utilizing parameters from the Google Gemma family. In accordance with open licensing frameworks, all secondary software optimization primitives are disseminated under the Apache License 2.0.

---

## ⚖️ Financial Governance & Disclosures
To review our explicit corporate stance on digital asset compliance, independent crowdfunding channels, and our total restriction against speculative token promotions, please consult our official [Financial Statement](FINANCIAL_STATEMENT.md) ledger.

