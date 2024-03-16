# Password-Policies
Creating a password policy library to implement rules on user passwords.

These rules are:
1.Length - the restriction can specify either the minimum length or both the minimum and maximum length of a password.
2.Class - the restriction indicates how many different classes of characters the password must have at least; the classes are: lowercase letter, uppercase letter, digit, and other characters.
3.Must Include - the password must include at least one character from the specified class.
4.Must Not Include - the password must not include any character from the specified class.
5.Repetition - the restriction specifies how many times the same character can be consecutively repeated in the password.
6.Consecutive - the restriction imposes a maximum number of consecutive characters (e.g., abc or 123).

Requirement
Given a set of secure password policies and then a list of passwords, display OK or NOK for each of them, depending on whether they comply with all these policies.

Input
The first line contains a positive integer n, representing the number of rules to be followed. The following n lines contain the definition of a rule, in the following possible formats:

-length <min_length> - the password must have min_length characters (inclusive); 0 < min_length
-length <min_length> <max_length> - the password must have between min_length and max_length characters (inclusive); 0 < min_length <= max_length
-class <min_class_count> - the password must have at least min_class_count different types of characters (lowercase letter, uppercase letter, digit, and other characters); 0 < min_class_count < 5
-include <class> - the password must include at least one character from the specified class; class can be a, A, 0, or $, denoting the desired class
-ninclude <class> - the password must not include any character from the specified class; class follows the same rules as above
-repetition <max_count> - the same character can be consecutively repeated at most max_count times; 0 < max_count
-consecutive <max_count> - the password can have at most max_count consecutive characters in sequence; 0 < max_count

Following lines, until EOF, contain one password per line, which will be checked against the specified rules.

Output
For each verified password, display OK if the password complies with ALL specified rules, or NOK if there is at least one rule that is not respected.
