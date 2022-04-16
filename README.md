Program to calculate First and Follow sets of given grammar


Introduction:
First and Follow are two functions associated with grammar that help us fill in the entries of an M-table.
First: It is a function that gives the set of terminals that begin the strings derived from the production rule. A symbol c is in FIRST (α) if and only if α -> cβ for some sequence β of grammar symbols.
A terminal symbol a is in FOLLOW (N) if and only if there is a derivation from the start symbol S of the grammar such that S -> αNαβ, where α and β are a (possible empty) sequence of grammar symbols. In other words, a terminal c is in FOLLOW (N) if c can follow N at some point in a derivation.
Benefit of First and Follow:
1. It can be used to prove the LL (K) characteristic of grammar.
2. It can be used to promote in the construction of predictive parsing tables.
3. It provides selection information for recursive descent parsers.

Algorithm to compute First of a given grammar:
To compute First(X) for all grammar symbols X, apply following rules until no more terminals or ɛ can be added to any First set:
1. If X is a terminal then First(X) = {X}.
2. If X is a nonterminal and X→Y1 Y2 … Y𝑘 is a production for some k>=1,
then place a in First(X) if for some ‘I’ a is in First(Y𝑖) and ɛ is in all of
First(Y1) ...First(Y𝑖−1) that is Y1 … Y𝑖−1 => ɛ. if ɛ is in First(Y𝑗) for
j=1…k then add ɛ to First(X).
3. If X → ɛ is a production then add ɛ to First(X)

Algorithm to compute Follow of a given grammar:
To compute First(A) for all non-terminals A, apply following rules until nothing
can be added to any follow set:
1. Place $ in Follow(S) where S is the start symbol
2. If there is a production A→ αBβ then everything in First(β) except ɛ is in
Follow(B).
3. If there is a production A → B or a production A → αBβ where First(β)
contains ɛ, then everything in Follow(A) is in Follow(B)

Input Format: 
1. Epsilon is represented by ‘#’.
2. Productions are of the form A=B, where ‘A’ is a single Non-Terminal and ‘B’ can be any combination of Terminals and Non- Terminals.
3. L.H.S. of the first production rule is the start symbol.
4. Grammar is not left recursive.
5. Each production of a non-terminal is entered on a different line.
6. Only Upper-Case letters are Non-Terminals and everything else is a terminal.
7. Do not use ‘!’ or ‘$’ as they are reserved for special purposes.


Working Method and Function explanation:
The code implementation is divided into 4 phases.
	1. Storing the input in a dictionary
	2. Validity Check
	3. Calculate First
	4. Calculate Follow
                                                                                                                                                                                                                                                                    
Phase 1: Soring the input(grammar) in a dictionary (std::map is C++)
Input:
The input function keeps taking string as input until “end” is entered 
and keeps sending the strings into generateProd()  function where std::map
data structure is used to store the production rules.


Store: 
The input strings are then seperated into non-terminal and terminal 
symbols and kept in a dictionary for efficient use.

Assume a grammer: 
	A->aAb|#
Here s = “A->aAb|#” and the dictionary is created as
production[“A”] = {“aAb”,”#”}
 

Phase 2: Validity Check
We know that, to be valid to calculate first and follow; left factoring and left recursion cannot occur. So, validity of the grammar must be checked.

A grammar is left recursive if it has a non-terminal A such that there is a derivation A→ Aα and a grammar
is left factoring if we have A→αβ1 | αβ2
Both of these conditions are checked in this function.
The function returns a true-false value respectively if the grammar is valid or not.
If the function returns false, the respective production rules are marked and printed with invalid message and the program stops with return value of 0.	


Phase 3: Calculating First
The non-terminal symbols are sent to the function void first() to calculate the First of the respective non-terminal symbol.


Every possible condition are checked according to the algorithm to compute first.
If we find the first we store it into “ans” and later into map<string,string> firsts for later use.
The first of a non-terminal symbol is printed at the end of the function.

There is a problem occurs then a non-terminal symbol is found as the first. Then we need to find the first of that non-terminal symbol and again if non-terminal symbol is found we need to visit again and this goes on.
 
The solution to this problem is to use recursion.


This problem is solved recursively. If a non-terminal symbol is found as first then we find the first of that non-terminal symbol by recursion because this cycle can go on and on. This string recurse() function calls itself until all the terminal first are found.
The function returns all the terminal first symbols after all the recursive calls are done.






Sample input: 			
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
end

Sample output:
First(E)-> {(,i}
First(E')-> {+,#}
First(F)-> {(,i}
First(T)-> {(,i}
First(T')-> {*,#}



Phase 4: Calculating Follow
According to the algorithm to calculate follow we need to push Epsilon (“#”) to the starting 
symbol’s follow and then derive follow for other starting symbols by calling follow function.


Every condition described in the algorithm to calculate follow is implemented. The follows of a given non-terminal symbol is then stored in a dictionary called map<string, string> follows.
 


The derived follows from void follow() function are then put in a set
to avoid redundancy.
Then the set of follows are printer with their respective non-terminal symbols.


Sample Input:
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
end


Sample Output:
Follow(E)->{#,)}
Follow(E')->{#,)}
Follow(F)->{#,),*,+}
Follow(T)->{#,),+}
Follow(T')->{#,),+}



Conclusion: The executable C++ code for this program can be found in the following link.
https://github.com/labidz/Programe-to-calculate-First-and-Follow-of-a-grammer/blob/3fe0a6c1a162734e8c23ca8ea162c5be4e984234/code.cpp
