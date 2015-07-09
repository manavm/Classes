# Name: Manav Mandhani
# Ut EID: mm58926

#########
# Problem 1

import math

def euclidean_distance(point1, point2):
    return math.sqrt((point1[0]-point2[0])**2 + (point1[1]-point2[1])**2)
euclidean_distance((1,2),(9,5))

#########
# Problem 2

For function 1, ABC will return False, AbC will return True and ABc will return True. The function checks whether the character is lowercase and returns True if any of the characters in the sentence are lowercase. 

For function 2, ABC will return True, AbC will return True and ABc will return True. The function returns True for everything since it checks if the character "c" is lowercase, which it is. It also returns True or False as strings and not as boolean values.

For function 3, ABC will return False, AbC will return False and ABc will return False. The function returns False if either of the characters in the string is uppercase.

For function 4, ABC will return False, AbC will return True and ABc will return True. The function uses a counter and increments it only when it notices a lowercase character in the string. It returns True if the counter has been incremented at all and False if not.

#########
# Problem 3

def veclean(vector):
    sum = 0
    for i in vector:
        sum += i**2
    return math.sqrt(sum)

def printVecWithIndex(vector):
    for i in range(len(vector)):
        print i, vector[i]

def print2VecWithIndex(vector1, vector2):
    for i in range(len(vector1)):
        print i, vector1[i], vector2[i]

def printproducts_withindex(vector1, vector2):
    for i in range(len(vector1)):
        print i, (vector1[i]*vector2[i])

def dotproduct(vector1, vector2):
    sum = 0
    for i in range(len(vector1)):
        sum += vector1[i]*vector2[i]
    return sum
dotproduct([10,20,30],[333,222,111])

def cosine(vector1, vector2):
    return dotproduct(vector1,vector2)/(veclean(vector1)*veclean(vector2))
cosine([1,5,2,6],[3,3,3,3])



