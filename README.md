# RegexModule
Project checks if a given string matches with a certain regular expression using Thompson’s NFA method.

#REGEX ENGINE USING epsilon-NFA and DFA

##(PES1201700921 – Namrata R, PES1201700282- Gaurav H Sangappa)

The given project, checks if a given string matches with a certain regular expression.
It uses the Thompson’s NFA method. Initially the regular expression is converted to the form of NFA transitions. This is further converted to an epsilon-NFA transition table. Using the algorithm to convert NFA to DFA, the NFA is converted to its respective DFA. 
Now the user can enter a string, to see if it matches the regex.

##INPUT:
1) A regular expression: 
Allowed operators: + (one or more), . (Any character),  ? (0 or 1 character),* (0 or more characters),| (or operation), ( , ) (brackets for regex within) , {with number of repetitions} ( character with lower and upper limit for repetitions) ,\ (escape sequence)
As of now, the alphabets to be used have been hardcoded as a, b, * and + (to show working of escape sequence). This can be extended by increasing size of the arrays and for the corresponding tables.
2) The string to check for matching.
Once again, the same alphabets will show as valid.

##OUTPUT:
The concatenated form of the NFA
The transitions for the NFA
The e closure for each state of the NFA
The NFA transition table
The corresponding DFA transition table
The final states of DFA
Finally, if the given string matches the regex or not. 
