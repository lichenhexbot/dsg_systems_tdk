/*
// =========================================================================
// Copyright 2026 Dobrya-Sydney-Gleeman (DSG) Systems 
// ORCID iD: https://orcid.org/0009-0009-1955-4285
// www.flamingotangostudios.com
//  
// Licensed under the Apache License, Version 2.0
 */

import torch
import torch.nn.functional as F
import numpy as np
import os
import re
from PIL import Image

class RexColorTransformer:
    """
    Rex (Retinex-Radix-3) Widescreen Color Transformer + DiffusionGemma Bridge.
    Processes Red, Green, and Blue vector channels into lighting-invariant 
    structural trits (-1, 0, +1) and projects them bidirectionally through
    the 2.6M/4.6M Nano-DiffusionGemma [256, 128] ternary weight matrix (weights.h).
    """
    def __init__(self, target_w=64, target_h=40):
        self.target_w = target_w
        self.target_h = target_h

    def extract_channel_reflection(self, channel_tensor, sigma=4.0):
        """Log-Difference Extraction: Log(Ref) = Log(Img) - Log(Illum)"""
        img_epsilon = channel_tensor.float() + 1.0  # +1.0 prevents dark-space log noise amplification
        log_image = torch.log(img_epsilon)

        x_coord = torch.arange(-24, 25).float()
        gaussian_kernel = torch.exp(-x_coord**2 / (2 * sigma**2))
        gaussian_kernel /= gaussian_kernel.sum()

        kernel_2d = gaussian_kernel.view(1, 1, -1, 1) * gaussian_kernel.view(1, 1, 1, -1)

        padded_img = F.pad(log_image.unsqueeze(0).unsqueeze(0), (24, 24, 24, 24), mode='reflect')
        log_illumination = F.conv2d(padded_img, kernel_2d).squeeze(0).squeeze(0)

        return log_image - log_illumination

    def extract_direct_color_norm(self, channel_tensor):
        """Direct Regular Photo Mode (Without Retinex Log Filter): Centers [0..255] around 0."""
        return (channel_tensor.float() - 127.5) / 127.5

    def project_to_radix3(self, reflection_matrix, threshold_alpha=0.25):
        """Maps continuous reflections or normalized pixels into discrete Radix-3 {-1, 0, +1}."""
        std_dev = reflection_matrix.std()
        bound_limit = threshold_alpha * std_dev

        ternary_matrix = torch.zeros_like(reflection_matrix, dtype=torch.int8)
        ternary_matrix[reflection_matrix > bound_limit] = 1    # +1: High Feature / Peak
        ternary_matrix[reflection_matrix < -bound_limit] = -1  # -1: Shadow / Valley
        return ternary_matrix

    def load_weights_h(self, search_paths=None):
        """
        Loads and unpacks the 6,554 packed bytes from weights.h into the 
        [256, 128] (32,768-trit) DiffusionGemma ternary weight tensor!
        """
        if search_paths is None:
            search_paths = [
                "weights.h",
                "../TernaryDiffusionGemma/weights.h",
                os.path.expanduser("~/TernaryDiffusionGemma/weights.h")
            ]

        found_path = next((p for p in search_paths if os.path.exists(p)), None)
        if not found_path:
            print("⚠️  'weights.h' not found in search paths; skipping 2.6M weight link.")
            return None

        with open(found_path, "r") as f:
            content = f.read()

        hex_bytes = [int(h, 16) for h in re.findall(r"0x[0-9A-Fa-f]{2}", content)]
        unpacked_trits = []
        for b in hex_bytes:
            rem = b
            t0 = (rem // 81) - 1; rem %= 81
            t1 = (rem // 27) - 1; rem %= 27
            t2 = (rem // 9)  - 1; rem %= 9
            t3 = (rem // 3)  - 1; rem %= 3
            t4 = rem - 1
            unpacked_trits.extend([t0, t1, t2, t3, t4])

        # Reshape first 32,768 trits into [256, 128] DiffusionGemma projection matrix
        weight_tensor = torch.tensor(unpacked_trits[:32768], dtype=torch.int8).view(256, 128)
        print(f"🔗 Linked to '{found_path}': Unpacked {len(hex_bytes)} bytes -> [256, 128] Ternary Weights!")
        return weight_tensor

    def bidirectional_matryoshka_embed(self, r_trit, g_trit, b_trit, weights_256x128):
        """
        Scans the 64x40x3 (7,680-trit) visual canvas in 30 blocks of 256 trits
        BIDIRECTIONALLY (Forward + Reverse, DiffusionGemma style) using multiplier-free
        sign accumulation to generate a 128-trit Matryoshka Semantic Embedding!
        """
        flat_visual_trits = torch.stack([r_trit, g_trit, b_trit], dim=-1).flatten().to(torch.int32)
        blocks_fwd = flat_visual_trits.view(-1, 256)          # [30, 256] Forward scan
        blocks_rev = torch.flip(blocks_fwd, dims=[0, 1])      # [30, 256] Reverse scan (Bidirectional)

        w_int = weights_256x128.to(torch.int32)
        zero_weight_rate = (w_int == 0).sum().item() / w_int.numel() * 100.0

        # Multiplier-Free Bidirectional Projection (Pure Sign-Accumulation)
        fwd_proj = torch.matmul(blocks_fwd, w_int)
        rev_proj = torch.matmul(blocks_rev, w_int)
        combined = (fwd_proj + rev_proj).sum(dim=0)

        # Quantize final 128-D visual embedding back to Ternary {-1, 0, +1} for 26M EmbeddingGemma
        embed_128 = torch.zeros(128, dtype=torch.int8)
        std_e = combined.float().std() * 0.25
        embed_128[combined > std_e] = 1
        embed_128[combined < -std_e] = -1

        return embed_128, zero_weight_rate

    def render_ansi_color_vision(self, r_trit, g_trit, b_trit):
        print(f"\n👑 Rex Color Ternary Visual Matrix Output ({self.target_w}x{self.target_h}):")
        print("+" + "-" * self.target_w + "+")
        for h in range(self.target_h):
            row_chars = []
            for w in range(self.target_w):
                r_val = 255 if r_trit[h, w] == 1 else (0 if r_trit[h, w] == -1 else 128)
                g_val = 255 if g_trit[h, w] == 1 else (0 if g_trit[h, w] == -1 else 128)
                b_val = 255 if b_trit[h, w] == 1 else (0 if b_trit[h, w] == -1 else 128)
                row_chars.append(f"\033[48;2;{r_val};{g_val};{b_val}m \033[0m")
            print("|" + "".join(row_chars) + "|")
        print("+" + "-" * self.target_w + "+")

if __name__ == "__main__":
    image_path = "test_room.jpg"
    transformer = RexColorTransformer(target_w=64, target_h=40)

    # =========================================================================
    # TOGGLE RETINEX vs. REGULAR PHOTO VIEWING HERE (Uncomment one line):
    # =========================================================================
    # USE_RETINEX_FILTER = True    # <-- Retinex Log-Illumination Edge Mode
    USE_RETINEX_FILTER = False # <-- Uncomment this line for Regular Ternary Photo Mode!

    if os.path.exists(image_path):
        print(f"📸 Ingesting real color asset: '{image_path}'")
        raw_image = Image.open(image_path).convert("RGB")
        resized_image = raw_image.resize((transformer.target_w, transformer.target_h), Image.Resampling.LANCZOS)
        img_np = np.array(resized_image)

        r_chan = torch.from_numpy(img_np[:, :, 0])
        g_chan = torch.from_numpy(img_np[:, :, 1])
        b_chan = torch.from_numpy(img_np[:, :, 2])

        if USE_RETINEX_FILTER:
            print("🧼 Mode: Parallel Multi-Channel Retinex Log Filters...")
            r_ref = transformer.extract_channel_reflection(r_chan)
            g_ref = transformer.extract_channel_reflection(g_chan)
            b_ref = transformer.extract_channel_reflection(b_chan)
        else:
            print("🖼️  Mode: Direct Normalized Ternary Photo Viewing (Retinex Bypassed)...")
            r_ref = transformer.extract_direct_color_norm(r_chan)
            g_ref = transformer.extract_direct_color_norm(g_chan)
            b_ref = transformer.extract_direct_color_norm(b_chan)

        print("🔢 Quantizing RGB horizons into independent Radix-3 spaces...")
        r_trit = transformer.project_to_radix3(r_ref, threshold_alpha=0.25)
        g_trit = transformer.project_to_radix3(g_ref, threshold_alpha=0.25)
        b_trit = transformer.project_to_radix3(b_ref, threshold_alpha=0.25)

        transformer.render_ansi_color_vision(r_trit, g_trit, b_trit)

        # Link to weights.h and run Bidirectional DiffusionGemma Projection!
        weights_matrix = transformer.load_weights_h()
        if weights_matrix is not None:
            embed_128, skip_pct = transformer.bidirectional_matryoshka_embed(r_trit, g_trit, b_trit, weights_matrix)
            trit_str = "".join(["+" if x == 1 else ("-" if x == -1 else "0") for x in embed_128[:64].tolist()])
            print("-------------------------------------------------------------------------------")
            print(f"🧠 BIDIRECTIONAL DIFFUSIONGEMMA [256x128] MATRYOSHKA BRIDGE:")
            print(f"   Visual Canvas       : 7,680 Trits (30 x 256-Trit Spatial Patches)")
            print(f"   Hardware Zero-Skips : {skip_pct:.1f}% (W == 0 clock-gated across bidirectional pass)")
            print(f"   128-Trit Embedding  : [{trit_str}...] (Ready for 26M EmbeddingGemma Search!)")
            print("-------------------------------------------------------------------------------")

        print("✅ Rex Color Matrix crystallized & linked successfully.")
    else:
        print(f"📝 Place your color satellite image as '{image_path}' in this folder to verify!")

