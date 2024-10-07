## Building

- `cmake . && make`
- `cmake . -G"Unix Makefiles"`
- `cmake . -DCMAKE_BUILD_TYPE=Debug`
- `make`

## Der Parser

Flex arbeitet mit der Datei `scan.ll` um den lexikalischen Parser zu generieren (z.B. `scanner.cc`, `scanner.hh`).
GNU Bison benutzt die Definitionen in `parse.yy` um den Syntaxparser zu generieren (`parser.cc`, `parser.hh`).
