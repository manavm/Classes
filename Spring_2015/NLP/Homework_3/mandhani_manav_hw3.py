#########
# Problem 1:
import nltk
brown_news = nltk.corpus.brown.tagged_words(categories="news")
new_brown_news = [(i[0].lower(), i[1]) for i in brown_news]
print new_brown_news[:10]

import operator
word_dict = {}
pos_dict = {}
for tag in new_brown_news:
    if tag[0] in word_dict:
        word_dict[tag[0]] += 1
    else:
        word_dict[tag[0]] = 1
    if tag[1] in pos_dict:
        pos_dict[tag[1]] += 1
    else:
        pos_dict[tag[1]] = 1
word_sorted = sorted(word_dict.items(), key=operator.itemgetter(1))
pos_sorted = sorted(pos_dict.items(), key=operator.itemgetter(1))

print word_sorted[-1]
print pos_sorted[-1]

#########
# Problem 2a:

#########
# Problem 2b:
amb_dict = {}
for tag in new_brown_news:
    if tag[0] in amb_dict:
        if tag[1] not in amb_dict[tag[0]]:
            amb_dict[tag[0]].append(tag[1])
    else:
        amb_dict[tag[0]] = [tag[1]]
total_count = 0
word_count = 0
max_ambi_word = ""
max_ambi_count = 0
for word in amb_dict.keys():
    total_count += 1
    if len(amb_dict[word]) > 1:
        word_count += 1
    if len(amb_dict[word]) > max_ambi_count:
        max_ambi_count = len(amb_dict[word])
        max_ambi_word = word
print word_count
print max_ambi_word, max_ambi_count

#########
# Problem 3:
brown_news = nltk.corpus.brown.tagged_sents(categories="news")
for sentence in brown_news:
    for word in sentence:
    	new_word = word[0].lower()
        if  new_word == max_ambi_word:
            if word[1] in amb_dict[new_word]:
                amb_dict[new_word].remove(word[1])
                print sentence