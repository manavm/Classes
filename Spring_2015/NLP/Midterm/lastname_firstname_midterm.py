# Midterm exam answers
#
# Name: Manav Mandhani
# EID: mm58926

#########
# Problem 1:
def summed_wordlength(words_array):
	total_sum = 0
	for i in words_array:
		total_sum += len(i)
	return total_sum

#########
# Problem 2:
import re
f = open('pg1184.txt')
text = f.read()
realtext = text[text.find("*** START OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***") + len("*** START OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***"):text.find("*** END OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***")]
for line in realtext.splitlines():
	for word in line.split():	
		match = re.match(r'(stand|stood|stands|standing)$',word)
		if match:
			print line[line.find(word)-20:line.find(word)+20]

#########
# Problem 3a:
import nltk
from nltk.corpus import brown
brown_tagged_words = brown.tagged_words(categories = "news")
for tag in brown_tagged_words:
	tags_list.append(tag[1][:2])
return tags_list

#########
# Problem 3b:
def remove_prefixes(words):
	for word in words:
		word.lower()
		match = re.match(r'^(in)',word)
		#don't consider in as a prefix for "in"
		if match and not len(word[2:]) == 0:
			print word[2:]
f = open('pg1184.txt')
text = f.read()
realtext = text[text.find("*** START OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***") + len("*** START OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***"):text.find("*** END OF THIS PROJECT GUTENBERG EBOOK THE COUNT OF MONTE CRISTO ***")]
remove_prefixes(realtext.split())

#########
# Problem 4:
import nltk
from nltk.corpus import brown
brown_tagged_words = brown.tagged_words(categories = "news")

#########
# Problem 5a:

#########
# Problem 5b:

#########
# Problem 5c:
