# Name: Manav Mandhani
# Ut EID: mm58926

#########
# Problem 1:


{<NN.*>+<CD>}
{<PRP.*><JJ.*>?<NN.*>+}
{<NN.*>+<CC><NN.*>+}
{<DT>?<JJ.*>*<NN.*>+}
{<DT|PP\$>?<JJ>*<NN>}

Precision:  63.45%
Recall:     54.27%
F-score:    58.60%

When there are two Noun chunks, the chunker doesn't behave as expected. The chunker also behaved different than expected with cardinal numbers especially when appended with decimal points or percentage symbols. 

#########
# Problem 2:
Precision = TP / (TP + FP)
Precision = 511 / (511 + 83) = 0.8602 = 86.02%

Recall = TP / (TP + FN)
Recall = 511 / (511 + 302) = 0.6285 = 62.85%

F-score = 2*Precision*Recall / (Precision + Recall)
F-score = 2*0.8602*0.6285 / (0.8602+0.6285) = 0.7263 = 72.63%



