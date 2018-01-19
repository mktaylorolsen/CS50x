import nltk

"""The purpose of this analyzer is to analyze words to determine if they are positive, negative or neutral and then assign
a number value to that word."""

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        #Create lists for positive and negatives words.
        self.positives = set()
        self.negatives = set()

        #POSITIVE WORDS
        #Open the correlated text file in read form.
        file = open(positives, "r")
        #Skip over the comments
        for line in file:
            if line.startswith(';'):
                continue
        #Add to list without whitespace
            else:
                self.positives.add(line.strip())
        #Close text file.
        file.close()

        #NEGATIVE WORDS
        #Open the correlated text file in read form.
        file = open(negatives, "r")
        #Skip over the comments
        for line in file:
            if line.startswith(';'):
                continue
        #Add to list without whitespace
            else:
                self.negatives.add(line.strip())
        #Close text file.
        file.close()


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        #implement tokenizer to break up the text into multiple words
        tokenizer = nltk.tokenize.TweetTokenizer()
        #tokenize the text
        tokens = tokenizer.tokenize(text)
        #Set counter for the text's score
        score = 0
        #iterate over each word in text
        for word in tokens:
            #determine if the lower cased version of the word is positive
            if word.lower() in self.positives:
                score += 1
            #determine if the lower cased version of the word is negative
            elif word.lower() in self.negatives:
                score -= 1
            #if the word is not positive or negative, then it must be neutral
            else:
                continue
        #return the score
        return score
