#!/usr/bin/env python3
import argparse
import csv
import re
import sys
from pathlib import Path


RESULT_PATTERN = re.compile(
    r"^(?P<structure>\w+)\s*\|\s*"
    r"(?P<operation>[^|]+?)\s*\|\s*"
    r"suma:\s*(?P<sum_ns>\d+)\s*ns\s*\|\s*"
    r"srednia:\s*(?P<average_ns>\d+)\s*ns"
)

FIELD_NAMES = [
    "source",
    "n",
    "repeat_count",
    "seed_choice",
    "structure",
    "operation",
    "sum_ns",
    "average_ns",
]


def read_input(path):
    if str(path) == "-":
        return sys.stdin.read(), "stdin"

    input_path = Path(path)
    return input_path.read_text(encoding="utf-8"), str(input_path)


def parse_measurements(text, source, metadata):
    measurements = []

    for line in text.splitlines():
        match = RESULT_PATTERN.search(line.strip())
        if not match:
            continue

        measurements.append(
            {
                "source": source,
                "n": metadata["n"],
                "repeat_count": metadata["repeat_count"],
                "seed_choice": metadata["seed_choice"],
                "structure": match.group("structure"),
                "operation": match.group("operation").strip(),
                "sum_ns": int(match.group("sum_ns")),
                "average_ns": int(match.group("average_ns")),
            }
        )

    return measurements


def save_csv(measurements, output_path):
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with output_path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=FIELD_NAMES)
        writer.writeheader()
        writer.writerows(measurements)


def build_parser():
    parser = argparse.ArgumentParser(
        description="Zamienia tekstowe wyniki programu na plik CSV do wykresow."
    )
    parser.add_argument(
        "inputs",
        nargs="+",
        help="Pliki tekstowe z wynikami programu. Uzyj '-' zeby czytac ze standardowego wejscia.",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="data/pomiary.csv",
        help="Sciezka pliku CSV z wynikami. Domyslnie: data/pomiary.csv.",
    )
    parser.add_argument(
        "--n",
        type=int,
        required=True,
        help="Liczba elementow uzyta w pomiarze.",
    )
    parser.add_argument(
        "--repeat-count",
        type=int,
        default=30,
        help="Liczba powtorzen dla jednego seeda. Domyslnie: 30.",
    )
    parser.add_argument(
        "--seed-choice",
        default="5",
        help="Wybrany seed, np. 0, 1 albo 5 dla wszystkich seedow. Domyslnie: 5.",
    )
    return parser


def main():
    args = build_parser().parse_args()
    output_path = Path(args.output)
    metadata = {
        "n": args.n,
        "repeat_count": args.repeat_count,
        "seed_choice": args.seed_choice,
    }

    measurements = []
    for input_path in args.inputs:
        text, source = read_input(input_path)
        measurements.extend(parse_measurements(text, source, metadata))

    if not measurements:
        print("Nie znaleziono linii z wynikami pomiarow.", file=sys.stderr)
        return 1

    save_csv(measurements, output_path)
    print(f"Zapisano {len(measurements)} pomiarow do {output_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
