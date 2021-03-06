/* Copyright (C) 2003  Free Software Foundation.

   Verify that built-in math function constant folding of functions
   with one constant argument is correctly performed by the compiler.

   Written by Roger Sayle, 30th March 2003.  */

/* { dg-do run } */
/* { dg-options "-O2 -ffast-math" } */

extern void abort(void);

void test(double x)
{
  if (pow(x,-1.0) != 1.0/x)
    abort ();

  if (pow(x,2.0) != x*x)
    abort ();

  if (pow(x,-2.0) != 1.0/(x*x))
    abort ();

  if (pow(x,0.5) != sqrt(x))
    abort ();
}

int main()
{
  test (1.0);
  test (2.0);
  return 0;
}

