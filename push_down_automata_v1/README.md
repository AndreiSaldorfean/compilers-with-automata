# Hard-coded Push down automata

This PDA takes in as input a hard-coded grammar, actions table and jump/goto table

Input:

- `grammar.txt`

    - First line conatins the `staring symbol`
    - Second line contains the `non-terminals`
    - Third line contains the `terminals`
    - Next lines contain the `productions`

- `actions.txt`
- `goto.txt`
- {argument} (eg: ./main.exe "id+id")

Output: Succes or Fail

The PDA checks whether a given expression belongs to the grammar it has been configured with and return true or false.