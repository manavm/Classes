########
# Your name and EID: Manav Mandhani, mm58926

#########
# Problem 1:
(h) Cannot have spaces
(c) Hyphen
(d) Start with number

(f) Sum shouldn't be used because it is also the name of a python function
#########
input_string = "After the glimpse I had had of the Martians emerging from the cylinder in which they had come to the earth from their planet, a kind of fascination paralysed my actions. I remained standing knee-deep in the heather, staring at the mound that hid them. I was a battleground of fear and curiosity. I did not dare to go back towards the pit, but I felt a passionate longing to peer into it. I began walking, therefore, in a big curve, seeking some point of vantage and continually looking at the sand heaps that hid these new-comers to our earth. Once a leash of thin black whips, like the arms of an octopus, flashed across the sunset and was immediately withdrawn, and afterwards a thin rod rose up, joint by joint, bearing at its apex a circular disk that spun with a wobbling motion. What could be going on there?"

# Problem 2:
input_string.count("of")
#########

# Problem 3:
import string
exclude = [".", ",", "?"]
splitted = input_string.split()
for i in range(len(splitted)):
	if splitted[i][-1] in exclude:
		splitted[i] = splitted[i][:-1]
		
#########
# Problem 4:
count = 0
#Using splitted from problem 3
for i in splitted:
	if i.endswith("ing"):
		count += 1

#########
# Problem 5:
stemmed = []
for i in splitted:
	if i.endswith("ing"):
		stemmed.append(i.replace("ing",""))
	elif i.endswith("s"):
		stemmed.append(i.replace("s",""))
	elif i.endswith("ed"):
		stemmed.append(i.replace("ed",""))
	else:
		stemmed.append(i)
print " ".join(stemmed)

#########
# Problem 6:
f = open("/Users/manavm/Documents/School/Spring_2015/NLP/Homework_1/pg768.txt") 
bronte_string = f.read() 
f.close()
start_index = bronte_string.index("***", bronte_string.index("***START") + 1)
end_index = bronte_string.index("***END")
final_string = bronte_string[start_index:end_index]
