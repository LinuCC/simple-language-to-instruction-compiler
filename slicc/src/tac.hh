#ifndef TAC_HH
#define TAC_HH
namespace slicc_tac {

/**
 * Operationen des TACs
 */
typedef enum {
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  AND,
  OR,
  NOT,
  LT,
  GT,
  LE,
  GE,
  EQ,
  NE,
  ASSIGN,
  GOTO,
  LABEL,
} TacOperation;

typedef struct _TacArg {
  char *var_ref;
  char *func_ref;
  int int_val;
} TacArg;

/**
 * Three-address code (TAC) Struktur als Zwischensprache zwischen
 * Compilerfrontend und Compilerbackend
 */
typedef struct _TacEntry {
  /**
   * Operation des TACs
   */
  TacOperation op;
  TacArg arg1;
  TacArg arg2;
  char *res_ref;
} TacEntry;

/**
 * Typ des Symboltabelleneintrags
 */
typedef enum {
  INT,
  INT_ARRAY,
  FUNCTION,
  PROGRAM,
} SymbolType;

/**
 * Eintrag in der Symboltabelle
 *
 * Eintrag einer einfachen Liste da er einen Zeiger auf den nächsten Eintrag
 * besitzt
 */
typedef struct _SymbolTableEntry {

  /**
   * Name des Symbols
   */
  char *name;

  /**
   * Typ des Symbols
   */
  SymbolType type;

  /**
   * Zeile in der das Symbol definiert wurde
   * (Funktionen sind nicht davon abhängig)
   */
  unsigned int line;

  /**
   * Wenn der Typ ein Integer Array ist, ist dies die deklarierte Größe des
   * Arrays
   */
  unsigned int elementCount;

  /**
   * Der nächste Eintrag in der Symboltabelle
   */
  // struct _SymbolTableEntry *next;

  /**
   * 'program' oder der Name der Funktion in der das Symbol definiert wurde
   */
  char *parent;

  /**
   * Wenn der Parent eine Funktion und das Symbol ein Funktionsargument ist,
   * speicher die Position des Arguments
   */
  unsigned int funcArgPosition;

  /**
   * Wenn das Symbol ein Funktionsargument ist, speicher ob es ein
   * call-by-reference Argument ist
   */
  bool isRef;
} SymbolTableEntry;

} // namespace slicc_tac
#endif
