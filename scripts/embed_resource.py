#!/usr/bin/env python3

"""Convert a binary file into a C header with an embedded byte array.

Usage: embed_resource.py <input_file> <output_header> <variable_name>

Generates a header containing:
  - const unsigned char <variable_name>[]
  - const unsigned int  <variable_name>_len
"""

from typing import Never
from dataclasses import dataclass
import sys
from pathlib import Path

SYS_ARGV_LEN = 4


@dataclass
class Args:
    argv_0: str | Path
    input_path: Path
    output_path: Path
    var_name: str

    def __init__(self, argv: list[str]) -> None | int:
        if len(sys.argv) != SYS_ARGV_LEN:
            print(
                f"usage: {sys.argv[0]} <input> <output> <variable_name>",
                file=sys.stderr,
            )
            raise SystemExit(1)

        self.argv_0 = argv[0]
        self.input_path = Path(argv[1])
        self.output_path = Path(argv[2])
        self.var_name = str(argv[3])
        # self.validate()

    # def validate(self) -> None:
    # pass

    def input_path_bytes(self) -> bytes:
        return bytes(self.input_path.read_bytes())


def main() -> int:
    try:
        args = Args(sys.argv)
    except SystemExit as e:
        print(
            f"embed_resource.py failed with exit code {e.code}", file=sys.stderr
        )
        if type(e.code) is int:
            return e.code
        else:
            return 1

    data: bytes = bytes(args.input_path_bytes())

    lines: list[str] = [
        "#pragma once",
        f"// Auto-generated from {args.input_path.name} — do not edit",
        "",
        f"static const unsigned char {args.var_name}[] = {{",
    ]

    # 12 bytes per line keeps the file readable
    for i in range(0, len(data), 12):
        chunk: bytes = data[i : i + 12]
        hex_vals: str = ", ".join(f"0x{b:02x}" for b in chunk)
        lines.append(f"  {hex_vals},")

    lines.append("};")
    lines.append("")
    lines.append(
        f"static const unsigned int {args.var_name}_len = sizeof({args.var_name});"  # noqa: E501
    )
    lines.append("")

    args.output_path.write_text("\n".join(lines))
    return 0


if __name__ == "__main__":
    try:
        ec = main()
        if ec != 0:
            print(
                f"embed_resource.py failed with exit code {ec}", file=sys.stderr
            )
            sys.exit(ec)
    except Exception as e:  # noqa: BLE001
        print(f"embed_resource.py failed with exception: {e}", file=sys.stderr)
        print("embed_resource.py failed with exit code 1", file=sys.stderr)
        sys.exit(1)
