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
count_text = f.read()
for line in count_text.splitlines():
	for word in line.split():	
		matching_exp = re.match(r'(stand|stood|stands|standing)$',word)
		if matching_exp:
			print line[(line.find(word)-20):(line.find(word)+21)]

#########
# Problem 3a:
import nltk
from nltk.corpus import brown
brown_tagged_words = brown.tagged_words(categories = "news")
for tag in brown_tagged_words:
	tags_list.append(tag[1][:2])
print tags_list

#########
# Problem 3b:
f = open('pg1184.txt')
text = f.read()
word_list = []
for word in text.split():
	word.lower()
	match = re.match(r'^(in)',word)
	if match and len(word[2:]) != 0:
		word_list.append(word[2:])
print word_list[:10]

# Words that use in as a prefix: invariable, invisible
# Words that don't use in as a prefix: instructions, interrupted

#########
# Problem 4:
import nltk
from nltk.corpus import brown
brown_tagged_words = brown.tagged_words(categories = "news")
tagged_dict = {}
for tag in range(len(brown_tagged_words)-1):
    if brown_tagged_words[tag][1][0] == 'V':
        if brown_tagged_words[tag+1][1] == 'IN':
            if brown_tagged_words[tag][0] in tagged_dict:
				tagged_dict[brown_tagged_words[tag][0]].append(brown_tagged_words[tag+1][0])
            else:
                tagged_dict[brown_tagged_words[tag][0]] = [brown_tagged_words[tag+1][0]]

max_verb = ""
max_count = 0
for i in tagged_dict:
	if len(set(tagged_dict[i])) > max_count:
		max_count = len(set(tagged_dict[i]))
		max_verb = i
print max_count
print max_verb

# The verb "made" occurs with the highest number of prepositions.
# There are 11 different prepositions for that verb.

#########
# Problem 5a:
import nltk
import string
f = open('pg345.txt')
text = f.read()
word_list = text.split()
new_word_list = []
for word in word_list:
    word = word.lower().lstrip(string.punctuation).rstrip(string.punctuation)
    new_word_list.append(word)
    
word_freq = nltk.FreqDist(new_word_list)
bigram_list = nltk.bigrams(new_word_list)
bigram_freq = nltk.FreqDist(bigram_list)

final_words = []
final_bigrams = []

for word in word_freq.keys()[:10]:
    final_words.append((word, word_freq[word]))
for bigram in bigram_freq.keys()[:10]:
    final_bigrams.append((bigram, bigram_freq[bigram]))

print final_words
print final_bigrams

# Words
# ([('the', 8036),
#   ('and', 5896),
#   ('i', 4712),
#   ('to', 4539),
#   ('of', 3738),
#   ('a', 2961),
#   ('in', 2558),
#   ('he', 2543),
#   ('that', 2455),
#   ('it', 2141)],

# Bigrams
#  [(('of', 'the'), 896),
#   (('in', 'the'), 629),
#   (('', ''), 526),
#   (('to', 'the'), 383),
#   (('and', 'the'), 340),
#   (('and', 'i'), 329),
#   (('on', 'the'), 324),
#   (('it', 'was'), 311),
#   (('it', 'is'), 303),
#   (('van', 'helsing'), 299)])

#########
# Problem 5b:
prob_there =  float(word_freq["there"])/len(modifiedtext)
prob_is_there = float(bigram_freq["there","is"])/word_freq["there"]
prob_is_a = float(bigram_freq["is","a"])/word_freq["is"]
prob_a_vampire = float(bigram_freq["a","vampire"])/word_freq["a"]
prob_vampire_in = float(bigram_freq["vampire","in"])/word_freq["vampire"]
prob_in_the = float(bigram_freq["in","the"])/word_freq["in"]
prob_the_room = float(bigram_freq["the","room"])/word_freq["the"]
print (prob_there * prob_isthere * prob_is_a * prob_a_vampire * prob_vampire_in * prob_in_the * prob_the_room)


#########
# Problem 5c:
cfreq = nltk.ConditionalFreqDist(bigram_list)
cprob = nltk.ConditionalProbDist(cfreq, nltk.MLEProbDist)
cprob_is_there = cprob["there"].prob("is")
cprob_is_a = cprob["is"].prob("a")
cprob_a_vampire = cprob["a"].prob("vampire")
cprob_vampire_in = cprob["vampire"].prob("in")
cprob_in_the = cprob["in"].prob("the")
cprob_the_room = cprob["the"].prob("room")
print (prob_there * cprob_is_there * cprob_is_a * cprob_a_vampire * cprob_vampire_in * cprob_in_the * cprob_the_room)