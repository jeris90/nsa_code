Code for gradual semantics (nsa, h-cat and M&T)
===================================================

Author :
* Jérôme Delobelle (mailto:jerome.delobelle@u-paris.fr), Université de Paris
* Vivien (mailto:vivien@beuselinck.fr), Université Fédéral
* Srdjan Vesic (mailto:vesic@cril.fr), Université d'Artois

To compile:
```
make clean
make sem
```

Usage :
```
./sem [HCAT | NSA | MT] <path_AF_file>
where HCAT represents the h-categorizer semantics
      NSA represents the no self-attack h-categorizer semantics
      MT representes the M&T semantics

<path_AF_file> : Path of the file containing the argumentation graph (two available formats: apx or cnf).
