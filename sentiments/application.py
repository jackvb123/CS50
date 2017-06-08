from flask import Flask, redirect, render_template, request, url_for

import helpers
import os 
import sys
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    try :
        tweets = helpers.get_user_timeline(screen_name, 100)
        if tweets is None:
            sys.exit()
        
    except RuntimeError as e:
        sys.exit(e)
    total =0
    pos =0
    neg = 0
    neu=0
    positive, negative, neutral = 0.0, 0.0, 100.0
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    with open(positives) as f:
        plines = f.read().splitlines()
   # print (plines)
    with open(negatives) as f:
        nlines = f.read().splitlines()
   # print (nlines)
    analyzer = Analyzer(plines, nlines)
    # generate chart
    for t in tweets:
         score = analyzer.analyze(t)
         if score > 0.0:
             pos=pos+1
             total=total+1
         elif score < 0.0:
             neg=neg+1
             total=total+1
         else:
             neu =neu+1
             total=total+1
    positive = pos/total
    negative = neg/total
    neutral = neu/total
    
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
