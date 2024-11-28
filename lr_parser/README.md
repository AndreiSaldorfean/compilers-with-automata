# Generateing the actions and goto tables for the pda

Example:

````
S->AA
A->aA
A->b
````

# Steps
## 1. Create the **DFA** (Deterministic Finite Automata) which in turns recognizes the *viable prefixes*
### 1.1 Augment the grammar
Add Augment Production, insert '.' symbol at the first position for every production in G and also add the look ahead and the new produciton for the start symbol.
````
S`->.S, $
S->.AA, $
A->.aA, a/b
A->.b, a/b
````
And these will be the new augmented productions.

### 1.2 Find the LR(1) items for each production rule
To find the ``LR(0)`` items for each produciton rule we will need to place a dot on each position possibile, like so:

**Eg:**

For `S->aA` the `LR(0)` item will be:
````
S->.aA
S->a.A
S->aA.
````
And this is the ``LR(0)`` item for the production rule ``S->aA``.

### 1.3 Constructing the DFA using the LR(0) items
We need to use 2 functions ``closure`` and ``goto``:

#### <u>1.3.1 Defining the `closure` function</u>
The `closure`  takes in as a parameter a production rule, and returns a set of production rules. To be more specific, the input is a LR(0) production rule and the output is a LR(0) item.

These are the inputs and outputs, but lets define the function itself. I will present it in steps so it's easier to follow:
1. Add the parameter in the set.
2. Look at the latest added item in set and check the following condition
3. If the position of the dot from the right hand item is proceding a non-terminal, than take that non-terminal and look if it has production rule in the LR(0) item where the position of the dot is at the left-most position in the right hand item.
4. If the condition is met than add it to the set and check for the same condition on the current production rule. Otherwise stop.

**Eg:**
`````
A->x.Bb
B->.AA
A->.q
`````
`````c
closure( A -> x.Bb ) =
{
    A -> x.Bb, // The parameter
    B -> .AA, // B is the non-terminal proceding '.',
              // with the '.' at the leftmost position in the production rule
    A -> .q
}
`````



#### <u>1.3.2 Defining the `goto` function</u>
The `goto` function takes in as parameter a LR(0) item, that represents a state of the `DFA`, and a symbol, terminal or non-terminal. And the output is a LR(0) item.
Now this function has two steps:
- Fining a production rule in the LR(0) item where the dot is before the symbol.
- Take that production rule and compute it's closure.
> The output of the `goto` function is the closure of that production rule.

**Eg:**
`````c
I0 = {
    A->x.Bb,
    B->.AA,
    A->.q,
}
`````
`goto( I0, B)`:

- Find a production rule where the dot is before `B`, that is `I0[0]`.
- Move the dot one position to the left, that is  `A->xB.b`
- Compute its closure: `I1 = {A->xB.b}`

> So the output of `goto(I0,B)` = I1, which means that the DFA has a possible transition through B to I1.

#### <u>1.3.3 Finding the initial state of the DFA</u>
So for our initial production rule:
````
S1->S
S->aA
A->aA|b
````
We will need to the find all the LR(0) items which will be 4:
````
S1->.S
S1->S.

S->.aA
S->a.A
S->aA.

A->aA
A->.aA
A->a.A
A->aA.

A->.b
A->b.
````

And the initial state will be I0=`closure(S1->.S)`.
#### <u>1.3.4 Finding the transitions of I0</u>

To find the transition of a LR(0) item, or a *state*, you need to take all the symbols imediatly befor dot, for all the items in the LR(0) item set, and compute goto of them.

#### <u>1.3.5 Repeat for the rest of the states untill you create the DFA</u>

## 2. Generate the actions and goto table.

### 2.1 For the goto part of the table

If there is a transition in the DFA from a state to another through a non-terminal you mark that cell with the transition index of the state.

**Eg:**

goto(I0,S) = I1

than at cell [I0,S] = 1
