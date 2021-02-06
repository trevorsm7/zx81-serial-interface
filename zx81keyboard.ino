////////////////////////////////////////////////////////////////////////////////
// Arduino pin mappings
////////////////////////////////////////////////////////////////////////////////

// Map from ZX81 keyboard diodes to Arduino pins
const byte PIN_D1 = 10;
const byte PIN_D2 = 9;
const byte PIN_D3 = 8;
const byte PIN_D4 = 7;
const byte PIN_D5 = 6;
const byte PIN_D6 = 5;
const byte PIN_D7 = 4;
const byte PIN_D8 = 3;

// Map from ZX81 ULA lines to Arduino pins
const byte PIN_KBD0 = 14;
const byte PIN_KBD1 = 15;
const byte PIN_KBD2 = 16;
const byte PIN_KBD3 = 17;
const byte PIN_KBD4 = 18;

////////////////////////////////////////////////////////////////////////////////
// Keyboard matrix mappings
////////////////////////////////////////////////////////////////////////////////

//          KBD0 KBD1 KBD2 KBD3 KBD4
// D1(A11)    1    2    3    4    5
// D2(A10)    Q    W    E    R    T
// D3(A12)    0    9    8    7    6
// D4(A9)     A    S    D    F    G
// D5(A13)    P    O    I    U    Y
// D6(A8)   SHIFT  Z    X    C    V
// D7(A14)  NEWLN  L    K    J    H
// D8(A15)  SPACE  .    M    N    B

enum KeyIndex : byte {
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,

  KEY_Q,
  KEY_W,
  KEY_E,
  KEY_R,
  KEY_T,

  KEY_0,
  KEY_9,
  KEY_8,
  KEY_7,
  KEY_6,

  KEY_A,
  KEY_S,
  KEY_D,
  KEY_F,
  KEY_G,
  
  KEY_P,
  KEY_O,
  KEY_I,
  KEY_U,
  KEY_Y,

  KEY_SHIFT,
  KEY_Z,
  KEY_X,
  KEY_C,
  KEY_V,

  KEY_NEWLINE,
  KEY_L,
  KEY_K,
  KEY_J,
  KEY_H,

  KEY_SPACE,
  KEY_PERIOD,
  KEY_M,
  KEY_N,
  KEY_B,
};

struct KeyMap {
  byte pin_d;
  byte pin_kbd;
};

// Map from keyboard diode to ULA line for a given keypress
const KeyMap KEY_MAP[] PROGMEM = {
  [KEY_1]       = {PIN_D1, PIN_KBD0},
  [KEY_2]       = {PIN_D1, PIN_KBD1},
  [KEY_3]       = {PIN_D1, PIN_KBD2},
  [KEY_4]       = {PIN_D1, PIN_KBD3},
  [KEY_5]       = {PIN_D1, PIN_KBD4},

  [KEY_Q]       = {PIN_D2, PIN_KBD0},
  [KEY_W]       = {PIN_D2, PIN_KBD1},
  [KEY_E]       = {PIN_D2, PIN_KBD2},
  [KEY_R]       = {PIN_D2, PIN_KBD3},
  [KEY_T]       = {PIN_D2, PIN_KBD4},

  [KEY_0]       = {PIN_D3, PIN_KBD0},
  [KEY_9]       = {PIN_D3, PIN_KBD1},
  [KEY_8]       = {PIN_D3, PIN_KBD2},
  [KEY_7]       = {PIN_D3, PIN_KBD3},
  [KEY_6]       = {PIN_D3, PIN_KBD4},

  [KEY_A]       = {PIN_D4, PIN_KBD0},
  [KEY_S]       = {PIN_D4, PIN_KBD1},
  [KEY_D]       = {PIN_D4, PIN_KBD2},
  [KEY_F]       = {PIN_D4, PIN_KBD3},
  [KEY_G]       = {PIN_D4, PIN_KBD4},

  [KEY_P]       = {PIN_D5, PIN_KBD0},
  [KEY_O]       = {PIN_D5, PIN_KBD1},
  [KEY_I]       = {PIN_D5, PIN_KBD2},
  [KEY_U]       = {PIN_D5, PIN_KBD3},
  [KEY_Y]       = {PIN_D5, PIN_KBD4},

  [KEY_SHIFT]   = {PIN_D6, PIN_KBD0},
  [KEY_Z]       = {PIN_D6, PIN_KBD1},
  [KEY_X]       = {PIN_D6, PIN_KBD2},
  [KEY_C]       = {PIN_D6, PIN_KBD3},
  [KEY_V]       = {PIN_D6, PIN_KBD4},

  [KEY_NEWLINE] = {PIN_D7, PIN_KBD0},
  [KEY_L]       = {PIN_D7, PIN_KBD1},
  [KEY_K]       = {PIN_D7, PIN_KBD2},
  [KEY_J]       = {PIN_D7, PIN_KBD3},
  [KEY_H]       = {PIN_D7, PIN_KBD4},

  [KEY_SPACE]   = {PIN_D8, PIN_KBD0},
  [KEY_PERIOD]  = {PIN_D8, PIN_KBD1},
  [KEY_M]       = {PIN_D8, PIN_KBD2},
  [KEY_N]       = {PIN_D8, PIN_KBD3},
  [KEY_B]       = {PIN_D8, PIN_KBD4},
};

////////////////////////////////////////////////////////////////////////////////
// Parser notes
////////////////////////////////////////////////////////////////////////////////

// Escape characters
// Prefix with ! to enter keyword/function
// Enclose text in [ ] to toggle inverse ([G]raphics) mode

// BASIC input modes
// [K]eyword                  (default for first character)
// [L]etter                   (default for subsequent characters)
// [F]unction  SHIFT+NEWLINE  (only affects next keystroke)
// [G]raphics  SHIFT+9        (terminated by [F]/[G]/NEWLINE)

// TTY escapes to emulate
// https://en.wikipedia.org/wiki/ANSI_escape_code
// Edit    SHIFT+1
// Left    SHIFT+5
// Down    SHIFT+6
// Up      SHIFT+7
// Right   SHIFT+8
// Delete  SHIFT+0

// Keywords/Functions (use !prefix)
// ABS      [F] G
// ACS      [F] S  (ARCCOS)
// AND    SHIFT+2
// ASN      [F] A  (ARCSIN)
// AT       [F] C
// ATN      [F] D  (ARCTAN)
// CLEAR        X
// CLS          V
// CHR$     [F] U
// CODE     [F] I
// CONT         C
// COPY         Z
// COS      [F] W
// DIM          D
// EXP      [F] X
// FAST   SHIFT+F
// FOR          F
// GOSUB        H
// GOTO         G
// IF           U
// INKEY$   [F] B  (IN KEY$)
// INPUT        I
// INT      [F] R
// LEN      [F] K
// LET          L
// LIST         K
// LLIST  SHIFT+G
// LN       [F] Z
// LOAD         J
// LPRINT SHIFT+S
// NEW          A
// NEXT         N
// NOT      [F] N
// OR     SHIFT+W
// PAUSE        M
// PEEK     [F] O
// PI       [F] M  (π {CF 80})
// PLOT         Q
// POKE         O
// PRINT        P
// RAND         T
// REM          E
// RETURN       Y
// RND      [F] T
// RUN          R
// SAVE         S
// SCROLL       B
// SGN      [F] F
// SIN      [F] Q
// SLOW   SHIFT+D
// SQR      [F] H
// STEP   SHIFT+E
// STOP   SHIFT+A
// STR$     [F] Y
// TAB      [F] P
// TAN      [F] E
// THEN   SHIFT+3
// TO     SHIFT+4
// UNPLOT       W
// USR      [F] L
// VAL      [F] J

// Unsupported half-shaded block characters
// NOTE these have UTF-32 code points (too big for UTF-16), but are uncommon
// ?  SHIFT+S  {F0 9F AE 8F}  (upper shaded, lower blank)
// ?  SHIFT+D  {F0 9F AE 8E}  (upper blank, lower shaded)
// ?  SHIFT+F  {F0 9F AE 92}  (upper shaded, bottom filled)
// ?  SHIFT+G  {F0 9F AE 91}  (upper filled, bottom shaded)
// ?  SHIFT+H  {F0 9F AE 90}  (inverse shaded)

////////////////////////////////////////////////////////////////////////////////
// Serial UTF-8 parser
////////////////////////////////////////////////////////////////////////////////

// [0aaaaaaa] ASCII, 7-bits in A
const byte UTF_PREFIX_ASCII = 0b00000000; // prefix code of ASCII byte
const byte UTF_MASK_ASCII   = 0b01111111; // data mask of ASCII byte

// [10xxxxxx] UTF-8 continuation byte (must follow UTF-8 leader byte)
const byte UTF_PREFIX_NEXT  = 0b10000000; // prefix code of continuation byte
const byte UTF_MASK_NEXT    = 0b00111111; // data mask of continuation byte
const byte UTF_BITS_NEXT    = 6; // number of data bits in continuation byte

// [110aaaaa] [10bbbbbb] 2-byte UTF-8, 13-bits in AB
const byte UTF_PREFIX_TWO   = 0b11000000; // prefix code of two-byte leader
const byte UTF_MASK_TWO     = 0b00011111; // data mask of two-byte leader

// [1110aaaa] [10bbbbbb] [10cccccc] 3-byte UTF-8, 16-bits in ABC
const byte UTF_PREFIX_THREE = 0b11100000; // prefix code of three-byte leader
const byte UTF_MASK_THREE   = 0b00001111; // data mask of three-byte leader

// Parse up to 3-byte UTF-8 and return UTF-16 (as int)
// NOTE could support 4-byte UTF-8, but would need to return UTF-32 (as long)
int16_t read_utf8() {
  // Non-blocking read for first byte
  int16_t input = Serial.read();
  byte remaining_bytes;

  // ASCII character: return as-is
  if (((byte)input & ~UTF_MASK_ASCII) == UTF_PREFIX_ASCII) {
    return input;
  }
  // 2-byte UTF-8 leader: mask data and read one more byte
  else if (((byte)input & ~UTF_MASK_TWO) == UTF_PREFIX_TWO) {
    input &= UTF_MASK_TWO;
    remaining_bytes = 1;
  }
  // 3-byte UTF-8 leader: mask data and read two more bytes
  else if (((byte)input & ~UTF_MASK_THREE) == UTF_PREFIX_THREE) {
    input &= UTF_MASK_THREE;
    remaining_bytes = 2;
  }
  // Other (4-byte leader, continuation byte, or garbage)
  else {
    return -1;
  }

  // Blocking read for UTF-8 continuation bytes
  byte bytes[remaining_bytes];
  if (Serial.readBytes(bytes, remaining_bytes) != remaining_bytes) {
    return -1; // Fail if read timed-out (set with Serial.setTimeout)
  }

  // Push data from continuation bytes into shift register
  for (const byte next : bytes) {
    if ((next & ~UTF_MASK_NEXT) == UTF_PREFIX_NEXT) {
      input = (input << UTF_BITS_NEXT) | (next & UTF_MASK_NEXT);
    } else {
      return -1;
    }
  }

  return input;
}

////////////////////////////////////////////////////////////////////////////////
// Ring buffer
////////////////////////////////////////////////////////////////////////////////

template <typename T, byte N>
class RingBuffer {
  static constexpr byte MASK_ = N - 1;

  T buffer_[N];
  byte head_;
  byte size_;

public:
  RingBuffer(): head_{0}, size_{0} {
    // TODO can this be in the class body instead of the ctor?
    static_assert((N & MASK_) == 0, "size N must be a power of two");
  }

  byte read_available() {
    return size_;
  }

  byte write_available() {
    return N - size_;
  }

  T read() {
    const T data = buffer_[head_];
    if (size_ > 0) {
      head_ = (head_ + 1) & MASK_;
      size_ -= 1;
    }
    return data;
  }

  void write(T data) {
    buffer_[(head_ + size_) & MASK_] = data;
    if (size_ < N) {
      size_ += 1;
    } else {
      head_ = (head_ + 1) & MASK_;
    }
  }
};

////////////////////////////////////////////////////////////////////////////////
// Main loop
////////////////////////////////////////////////////////////////////////////////

RingBuffer<KeyIndex, 64> key_buffer;

void setup() {
  // Initialize USB serial and wait for port to open
  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("ZX81 Serial Keyboard Interface");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int16_t input = read_utf8();
  if (input >= 0) {
    // Convert upper-case letters to lower-case
    // TODO upper-case could maybe be used for block characters in graphics mode
    bool upper_case = false;
    if (input >= 'A' && input <= 'Z') {
      input += 'a' - 'A';
      upper_case = true;
    }

    switch (input) {
      case u'1':
        key_buffer.write(KEY_1);
        break;
      case u'2':
        key_buffer.write(KEY_2);
        break;
      case u'3':
        key_buffer.write(KEY_3);
        break;
      case u'4':
        key_buffer.write(KEY_4);
        break;
      case u'5':
        key_buffer.write(KEY_5);
        break;
      case u'6':
        key_buffer.write(KEY_6);
        break;
      case u'7':
        key_buffer.write(KEY_7);
        break;
      case u'8':
        key_buffer.write(KEY_8);
        break;
      case u'9':
        key_buffer.write(KEY_9);
        break;
      case u'0':
        key_buffer.write(KEY_0);
        break;

      case u'q':
        key_buffer.write(KEY_Q);
        break;
      case u'w':
        key_buffer.write(KEY_W);
        break;
      case u'e':
        key_buffer.write(KEY_E);
        break;
      case u'r':
        key_buffer.write(KEY_R);
        break;
      case u't':
        key_buffer.write(KEY_T);
        break;
      case u'y':
        key_buffer.write(KEY_Y);
        break;
      case u'u':
        key_buffer.write(KEY_U);
        break;
      case u'i':
        key_buffer.write(KEY_I);
        break;
      case u'o':
        key_buffer.write(KEY_O);
        break;
      case u'p':
        key_buffer.write(KEY_P);
        break;
      case u'a':
        key_buffer.write(KEY_A);
        break;
      case u's':
        key_buffer.write(KEY_S);
        break;
      case u'd':
        key_buffer.write(KEY_D);
        break;
      case u'f':
        key_buffer.write(KEY_F);
        break;
      case u'g':
        key_buffer.write(KEY_G);
        break;
      case u'h':
        key_buffer.write(KEY_H);
        break;
      case u'j':
        key_buffer.write(KEY_J);
        break;
      case u'k':
        key_buffer.write(KEY_K);
        break;
      case u'l':
        key_buffer.write(KEY_L);
        break;
      case u'z':
        key_buffer.write(KEY_Z);
        break;
      case u'x':
        key_buffer.write(KEY_X);
        break;
      case u'c':
        key_buffer.write(KEY_C);
        break;
      case u'v':
        key_buffer.write(KEY_V);
        break;
      case u'b':
        key_buffer.write(KEY_B);
        break;
      case u'n':
        key_buffer.write(KEY_N);
        break;
      case u'm':
        key_buffer.write(KEY_M);
        break;

      case u'\n':
        // NOTE terminates [G]raphics/[F]unction modes
        key_buffer.write(KEY_NEWLINE);
        break;

      case u'$':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_U);
        break;
      case u'(':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_I);
        break;
      case u')':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_O);
        break;
      case u'\"':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_P);
        break;
      case u'-':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_J);
        break;
      case u'+':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_K);
        break;
      case u'=':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_L);
        break;
      case u':':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_Z);
        break;
      case u';':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_X);
        break;
      case u'?':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_C);
        break;
      case u'/':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_V);
        break;
      case u'*':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_B);
        break;
      case u'<':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_N);
        break;
      case u'>':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_M);
        break;
      case u'.':
        key_buffer.write(KEY_PERIOD);
        break;
      case u',':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_PERIOD);
        break;
      case u' ':
        key_buffer.write(KEY_SPACE);
        break;
      case u'£':
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_SPACE);
        break;

      case u'\'': // ""
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_Q);
        break;
      case u'≤': // <=
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_R);
        break;
      case u'≠': // <>
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_T);
        break;
      case u'≥': // >=
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_Y);
        break;
      case u'^': // **
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_H);
        break;
      
      // Block characters (all in [G]raphics mode)
      case u'▘':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_1);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▝':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_2);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▗':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_3);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▖':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_4);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▌':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_5);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▄':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_6);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▀':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_7);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▐':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_8);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▟':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_Q);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▙':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_W);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▛':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_E);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▜':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_R);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▞':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_T);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▚':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_Y);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'▒':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_A);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;
      case u'█':
        // Enter graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);

        key_buffer.write(KEY_SPACE);

        // Exit graphics mode
        key_buffer.write(KEY_SHIFT);
        key_buffer.write(KEY_9);
        break;

      default:
        Serial.print("Unhandled: ");
        Serial.println(input, HEX);
        break;
    }
  } else {
    while (key_buffer.read_available()) {
      KeyIndex key = key_buffer.read();
      bool shifted = false;
      if (key == KEY_SHIFT) {
        // TODO assert not empty, block until ready, or push SHIFT back
        key = key_buffer.read();
        Serial.print("SHIFT + ");
        shifted = true;
      }

      union {
        uint16_t map_raw;
        KeyMap map;
      };
      map_raw = pgm_read_word(KEY_MAP + key);
      Serial.print(map.pin_d);
      Serial.print(", ");
      Serial.println(map.pin_kbd);
    }
  }
}
