// Yagmur TUgran 231ADB263
//   cd src
//   gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c
//
//   echo "2 + 2"           > input1.txt
//   echo "8 / 2 + 3*4"     > input2.txt
//   echo "10 / 0"          > input3.txt
//
//./calc input1.txt
// cat input1_Yagmur_TUgran_231ADB263.txt
//
//./calc input2.txt
// cat input2_Yagmur_TUgran_231ADB263.txt
//
//./calc input3.txt
// cat input3_Yagmur_TUgran_231ADB263.txt
//
//   rm -f input*.txt *_Yagmur_TUgran_231ADB263.txt calc
//   This creates output file: input_Yagmur_TUgran_231ADB263.txt
//   Notes: first error is reported as ERROR:<pos> (1-based). Operators: + - * /
//   (From repo root instead) gcc -O2 -Wall -Wextra -std=c17 -o src/calc
//   src/calc.c && src/calc src/input.txt

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* These tags are used to form the output file name */
#define STUDENT_NAME "Yagmur"
#define STUDENT_LASTNAME "TUgran"
#define STUDENT_ID "231ADB263"

/* Keep only the first error position (0 => no error yet) */
static size_t g_error_pos = 0;
static void fail_at(size_t pos) {
  if (!g_error_pos) g_error_pos = pos;
}

/* Simple byte stream */
typedef struct {
  const char* buf;
  size_t len, idx;
} Stream;
static size_t pos1(const Stream* s) { return s->idx + 1; }

/* Whitespace is irrelevant for the grammar */
static void skip_ws(Stream* s) {
  while (s->idx < s->len) {
    char c = s->buf[s->idx];
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
      s->idx++;
    else
      break;
  }
}

/* Token kinds I actually need */
typedef enum {
  T_NUM,
  T_PLUS,
  T_MINUS,
  T_STAR,
  T_SLASH,
  T_EOF,
  T_INVALID
} TokKind;

typedef struct {
  TokKind kind;
  long long ival; /* valid when kind == T_NUM */
  size_t start;   /* token’s starting index (1-based) */
} Token;

static int isdig(char c) { return c >= '0' && c <= '9'; }

/* When an operand is expected, a leading +/− belongs to the number */
static int scan_signed_int(Stream* s, long long* out, size_t* start_out) {
  size_t i = s->idx;
  if (i >= s->len) return 0;
  int sign = 1;
  if (s->buf[i] == '+' || s->buf[i] == '-') {
    sign = (s->buf[i] == '-') ? -1 : 1;
    i++;
  }
  if (i >= s->len || !isdig(s->buf[i])) return 0;

  long long v = 0;
  while (i < s->len && isdig(s->buf[i])) {
    /* integer overflow checks are out of scope here */
    v = v * 10 + (s->buf[i] - '0');
    i++;
  }
  *out = (sign == 1) ? v : -v;
  *start_out = s->idx + 1;
  s->idx = i;
  return 1;
}

/* Minimal tokenizer: number/operator/EOF/INVALID */
static Token next_token(Stream* s, int expecting_operand) {
  skip_ws(s);
  Token t = (Token){T_EOF, 0, pos1(s)};
  if (s->idx >= s->len) return t;

  char c = s->buf[s->idx];

  if (expecting_operand) {
    long long v;
    size_t st;
    if (scan_signed_int(s, &v, &st)) {
      t.kind = T_NUM;
      t.ival = v;
      t.start = st;
      return t;
    }
  } else {
    if (isdig(c)) {
      long long v;
      size_t st;
      if (scan_signed_int(s, &v, &st)) {
        t.kind = T_NUM;
        t.ival = v;
        t.start = st;
        return t;
      }
    }
  }

  if (c == '+') {
    t.kind = T_PLUS;
    t.start = pos1(s);
    s->idx++;
    return t;
  }
  if (c == '-') {
    t.kind = T_MINUS;
    t.start = pos1(s);
    s->idx++;
    return t;
  }
  if (c == '*') {
    t.kind = T_STAR;
    t.start = pos1(s);
    s->idx++;
    return t;
  }
  if (c == '/') {
    t.kind = T_SLASH;
    t.start = pos1(s);
    s->idx++;
    return t;
  }

  /* Anything else is outside this grammar */
  t.kind = T_INVALID;
  t.start = pos1(s);
  s->idx++;
  return t;
}

/* Grammar (no parentheses here):
   expr := term { ('+'|'-') term }
   term := factor { ('*'|'/') factor }
   factor := NUMBER
*/
typedef struct {
  Stream* s;
  Token look;
  int expecting_operand;
  int have_look;
} Parser;

static void load(Parser* p) {
  p->look = next_token(p->s, p->expecting_operand);
  p->have_look = 1;
}
static void eat(Parser* p) {
  p->have_look = 0;
  /* After a number → expect operator; after an operator → expect operand */
  switch (p->look.kind) {
    case T_NUM:
      p->expecting_operand = 0;
      break;
    case T_PLUS:
    case T_MINUS:
    case T_STAR:
    case T_SLASH:
      p->expecting_operand = 1;
      break;
    default:
      break;
  }
}

static int parse_expr(Parser* p, long long* out);

/* I return both the numeric value and where that number started.
   The start index is useful for division-by-zero reporting. */
static int parse_factor(Parser* p, long long* out, size_t* out_start) {
  if (!p->have_look) load(p);
  if (p->look.kind == T_NUM) {
    *out = p->look.ival;
    *out_start = p->look.start;
    eat(p);
    return 1;
  }
  /* I was expecting a number; record the first location it goes wrong */
  fail_at(p->look.start);
  return 0;
}

static int parse_term(Parser* p, long long* out) {
  long long acc;
  size_t lhs_pos;
  if (!parse_factor(p, &acc, &lhs_pos)) return 0;

  for (;;) {
    if (!p->have_look) load(p);
    if (p->look.kind == T_STAR || p->look.kind == T_SLASH) {
      TokKind op = p->look.kind;
      size_t op_pos = p->look.start; /* kept in case factor fails */
      eat(p);

      long long rhs;
      size_t rhs_pos;
      if (!parse_factor(p, &rhs, &rhs_pos)) {
        if (!g_error_pos) fail_at(op_pos + 1);
        return 0;
      }

      if (op == T_STAR) {
        acc = acc * rhs;
      } else { /* division */
        if (rhs == 0) {
          /* I report division-by-zero at the divisor’s first character */
          fail_at(rhs_pos);
          return 0;
        }
        acc = acc / rhs; /* C integer division semantics (trunc toward zero) */
      }
      continue;
    }
    break;
  }
  *out = acc;
  return 1;
}

static int parse_expr(Parser* p, long long* out) {
  long long acc;
  if (!parse_term(p, &acc)) return 0;
  for (;;) {
    if (!p->have_look) load(p);
    if (p->look.kind == T_PLUS || p->look.kind == T_MINUS) {
      TokKind op = p->look.kind;
      size_t op_pos = p->look.start;
      eat(p);
      long long rhs;
      if (!parse_term(p, &rhs)) {
        if (!g_error_pos) fail_at(op_pos + 1);
        return 0;
      }
      acc = (op == T_PLUS) ? (acc + rhs) : (acc - rhs);
      continue;
    }
    break;
  }
  *out = acc;
  return 1;
}

/* Read entire file into memory */
static char* read_all(const char* path, size_t* out_len) {
  FILE* f = fopen(path, "rb");
  if (!f) return NULL;
  if (fseek(f, 0, SEEK_END) != 0) {
    fclose(f);
    return NULL;
  }
  long sz = ftell(f);
  if (sz < 0) {
    fclose(f);
    return NULL;
  }
  if (fseek(f, 0, SEEK_SET) != 0) {
    fclose(f);
    return NULL;
  }
  size_t n = (size_t)sz;
  char* buf = (char*)malloc(n + 1);
  if (!buf) {
    fclose(f);
    return NULL;
  }
  size_t rd = fread(buf, 1, n, f);
  fclose(f);
  if (rd != n) {
    free(buf);
    return NULL;
  }
  buf[n] = '\0';
  if (out_len) *out_len = n;
  return buf;
}

/* Output name: <input_stem>_Yagmur_TUgran_231ADB263.txt */
static void build_out_name(const char* in, char* out, size_t cap) {
  const char* slash = strrchr(in, '/');
#ifdef _WIN32
  const char* bslash = strrchr(in, '\\');
  if (!slash || (bslash && bslash > slash)) slash = bslash;
#endif
  const char* base = slash ? slash + 1 : in;

  char stem[512];
  size_t blen = strlen(base);
  if (blen >= sizeof(stem)) blen = sizeof(stem) - 1;
  memcpy(stem, base, blen);
  stem[blen] = '\0';

  size_t slen = strlen(stem);
  if (slen >= 4 && strcmp(stem + slen - 4, ".txt") == 0) stem[slen - 4] = '\0';

  snprintf(out, cap, "%s_%s_%s_%s.txt", stem, STUDENT_NAME, STUDENT_LASTNAME,
           STUDENT_ID);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s input.txt\n", argv[0]);
    return 1;
  }

  size_t len = 0;
  char* buf = read_all(argv[1], &len);
  if (!buf) {
    fprintf(stderr, "Failed to read '%s': %s\n", argv[1], strerror(errno));
    return 1;
  }

  Stream s = {buf, len, 0};
  Parser p = {&s, {0}, 1, 0};
  long long result = 0;
  int ok = parse_expr(&p, &result);

  /* After parsing, only whitespace is allowed */
  if (g_error_pos == 0) {
    skip_ws(&s);
    if (s.idx < s.len) {
      size_t junk = pos1(&s);
      (void)next_token(&s, 0); /* lock a stable position for trailing junk */
      fail_at(junk);
      ok = 0;
    }
  } else
    ok = 0;

  char out_path[1024];
  build_out_name(argv[1], out_path, sizeof(out_path));

  FILE* out = fopen(out_path, "wb");
  if (!out) {
    fprintf(stderr, "Failed to open output '%s': %s\n", out_path,
            strerror(errno));
    free(buf);
    return 1;
  }

  if (ok && g_error_pos == 0) {
    fprintf(out, "%lld\n", result);
  } else {
    size_t pos = g_error_pos ? g_error_pos : (len + 1);
    fprintf(out, "ERROR:%zu\n", pos);
  }

  fclose(out);
  free(buf);
  return 0;
}
