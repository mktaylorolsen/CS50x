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
    tweets = helpers.get_user_timeline(screen_name)
    if tweets == None:
        return redirect(url_for("index"))
    else:
        #create the counters
        positive, negative, neutral = 0.0, 0.0, 100.0
        # instantiate analyzer
        analyzer = Analyzer()
        # iterate over the list of tweets
        for tweet in tweets:
		    # analyze the tweet to get it’s score
            score = analyzer.analyze(tweet)
		    # determine if the score is positive, negative or neutral.
		    # print out the score and the tweet
            if score > 0.0:
                positive += 1
            elif score < 0.0:
                negative += 1
            else:
                neutral += 1


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
