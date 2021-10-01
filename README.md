# Complexity-Tools
Complexity: Reductions, Scripts, Tools.

## Reduction from 3SAT to Max2SAT:

3sat-to-max2sat-reduction.c

## Conver SAT to MIP

  usage: python3 sat2mip.py instance.cnf

  This convert a CNF instance to lpsolve https://sourceforge.net/projects/lpsolve/ this provide many format converts like mps.
  
  x0 = SAT (1) or UNSAT (0)
  x1 -> var1
  x2 -> var2
  .
  .
  .
  xn -> varn
  
sat2mip.py
