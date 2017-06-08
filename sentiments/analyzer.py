import nltk

class Analyzer():
    """Implements sentiment analysis."""
    
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.plist = positives
        self.nlist = negatives
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        count =0
        for t in tokens:
            t=str.lower(t)
            #print(t)
            if t in self.plist:
                count=count+1
            elif t in self.nlist:
                count = count -1
            
        return count
