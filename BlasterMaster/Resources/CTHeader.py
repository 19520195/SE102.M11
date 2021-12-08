HEADERS = ["TEXTURES", "SPRITES", "ANIMATIONS"]
ALIASES = ["TEX"     , "SPR"    , "ANM"       ]

if __name__ == '__main__':
  counters = dict()
  for header in HEADERS:
    counters[header] = 0

  definers = list()
  header = str("NONES")
  with open('Area3.ini', 'r') as config:
    for buffer in config.readlines():
      buffer = buffer.strip()
      if len(buffer) == 0 or buffer[0] == '#': continue

      if buffer[0] == '[': header = buffer[1:-1]
      elif header in HEADERS:
        counters[header] += 1
        name = buffer.split()[0]
        name = name.replace('-', '_').upper()
        pref = ALIASES[HEADERS.index(header)]
        definers.append((f"{pref}ID_{name}", counters[header]))

  max_header_len = (max(map(lambda _: len(_[0]), definers)) + 2) // 2 * 2
  with open('Resources.hh', 'w') as header_file:
    print("#pragma once", file=header_file)
    prev_constant = "NONES"
    for constant, index in definers:
      if prev_constant[:2] != constant[:2]:
        print(file=header_file)
        print(f"/* {HEADERS[ALIASES.index(constant[:3])]} ID */", file=header_file)
      prev_constant = constant

      index = str(index)
      index = ' ' * (2 - len(index)) + index

      print(f"#define {constant}{' ' * (max_header_len - len(constant))}{index}", file=header_file)
