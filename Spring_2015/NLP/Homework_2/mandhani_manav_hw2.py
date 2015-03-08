###
# Name and EID: Manav Mandhani, mm58926


#########
# Problem 1a:
import re
f = open("/Users/manavm/Documents/School/Spring_2015/NLP/Homework_2/pg36.txt") 
worlds_string = f.read() 
f.close()
one_syll = re.compile(r"([bcdfghjklmnpqrstvwxz]+[aeiou]+[bcdfghjklmnpqrstvwxz]*)$")
worlds_list = worlds_string.split()
count = 0
for i in worlds_list:
	if one_syll.match(i):
		count += 1
print count

# 19556

#########
# Problem 1b:

The word "same" has two vowels between consonants but is not caught by the rule. 
The word "pious" has two syllabels but follows the given rule
