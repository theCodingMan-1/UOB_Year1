## Useful cabal commands

- Update package list: `cabal update`
- Compile Simplify.hs and tests: `cabal build`
- Run tests: `cabal test`
- Open Simplify.hs in GHCi: `cabal repl`
- Run marking script: `cabal run mark`
  - This will produce a feedback file (`fb.md`) that tells you what mark and feedback you should get if you submit your current `Simplify.hs` file, assuming:
    1. you haven't changed any files other than `Simplify.hs`,
    2. you haven't changed the names or type signatures of the functions in `Simplify.hs`,
    3. you *only* submit `Simplify.hs`,
    4. you submit on time.
  - This cuts both ways. If you run this command, you can be sure what mark you'll get before even submitting your coursework (again, assuming you've followed all our instructions correctly). If you *don't* run this command before submitting, you can't complain if you get a bad mark!
  - If your code doesn't compile *you will get 0 marks*.
  - We reserve the right to adjust your mark according to our individual judgement in exceptional circumstances.
