/* Machine description pattern tests.  */

/* { dg-do compile { target { lp64 } } } */
/* { dg-options "-mzarch -save-temps -dP" } */
/* { dg-do run { target { lp64 && s390_useable_hw } } } */
/* Skip test if -O0 is present on the command line:

    { dg-skip-if "" { *-*-* } { "-O0" } { "" } }

   Skip test if the -O option is missing from the command line
    { dg-skip-if "" { *-*-* } { "*" } { "-O*" } }
*/

__attribute__ ((noinline))
unsigned long andc_vv(unsigned long a, unsigned long b)
{ return ~b & a; }
/* { dg-final { scan-assembler ":16:.\* \{\\*anddi3\}" } } */
/* { dg-final { scan-assembler ":16:.\* \{\\*xordi3\}" } } */

__attribute__ ((noinline))
unsigned long andc_pv(unsigned long *a, unsigned long b)
{ return ~b & *a; }
/* { dg-final { scan-assembler ":22:.\* \{\\*anddi3\}" } } */
/* { dg-final { scan-assembler ":22:.\* \{\\*xordi3\}" } } */

__attribute__ ((noinline))
unsigned long andc_vp(unsigned long a, unsigned long *b)
{ return ~*b & a; }
/* { dg-final { scan-assembler ":28:.\* \{\\*anddi3\}" } } */
/* { dg-final { scan-assembler ":28:.\* \{\\*xordi3\}" } } */

__attribute__ ((noinline))
unsigned long andc_pp(unsigned long *a, unsigned long *b)
{ return ~*b & *a; }
/* { dg-final { scan-assembler ":34:.\* \{\\*anddi3\}" } } */
/* { dg-final { scan-assembler ":34:.\* \{\\*xordi3\}" } } */

/* { dg-final { scan-assembler-times "\tngr\?k\?\t" 4 } } */
/* { dg-final { scan-assembler-times "\txgr\?\t" 4 } } */

int
main (void)
{
  unsigned long a = 0xc00000000000000cllu;
  unsigned long b = 0x500000000000000allu;
  unsigned long e = 0x8000000000000004llu;
  unsigned long c;

  c = andc_vv (a, b);
  if (c != e)
    __builtin_abort ();
  c = andc_pv (&a, b);
  if (c != e)
    __builtin_abort ();
  c = andc_vp (a, &b);
  if (c != e)
    __builtin_abort ();
  c = andc_pp (&a, &b);
  if (c != e)
    __builtin_abort ();
  return 0;
}
