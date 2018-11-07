# Prefix notation calculator

During an interview with Google (Zürich) the task was (referring to my major in Compiler & Software Engineering):

Design and write a compiler to process prefix notation, e.g.

**+ 1 3**

**+ 1 3 5**

**+ 1 3 * 5 7**

Challenge: 
Design and implement error processing (syntactic and semantic checks).

**+ * 1 2 * 3 4 * 4 5** should be a valid input.

To what evaulates the expression **\* + 2 \* 4 6 + 3 5 7** ?</br>
Note: The program evaulates to 362, the solution of the exercise for **(\* (+ 2 (\* 4 6)) (+ 3 5 7))** is 390. (See Exercise 1.1 of the SICP book).</br>
So paranthesis can play an important role (I said during the interview that parenthesis may be not important. Maybe that was a mistake. I wanted to start simple.)

