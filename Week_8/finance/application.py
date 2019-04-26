import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from holdings import generate_holdings

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get all transactions
    funds = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])[0]['cash']
    buys = db.execute("SELECT * FROM buys WHERE user_id = :id", id=session['user_id'])
    sells = db.execute("SELECT * FROM sells WHERE user_id = :id", id=session['user_id'])
    holdings = generate_holdings(buys, sells)

    return render_template('index.html', holdings=holdings, funds = funds)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # check for post
    if request.method == "POST":

        # check for symbol
        if not request.form.get("symbol"):
            return apology("You forgot to pick a stock")

        # check for shares
        if not request.form.get("shares"):
            return apology("You forgot to specify a quantity")

        # check if input is number
        if not request.form.get("shares").isdigit():
            return apology("You must specify a number")

         # check for shares
        if int(request.form.get("shares")) <= 0 or not isinstance(int(request.form.get("shares")), int):
            return apology("You must specify a positive whole number")

        # look up stock
        stock = lookup(request.form.get("symbol"))

        # check stock exists
        if not stock:
            return apology("That stock does not exist")

        # check for user
        user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])

        # check that we only have one user
        if len(user) != 1:
            return apology("Something bad happened, please try again")

        # check user has more cash than stock costs
        if (stock['price'] * int(request.form.get('shares')) > user[0]['cash']):
            return apology("You do not have enough cash for this")

        db.execute("INSERT INTO 'buys' ('user_id', 'symbol', 'price', 'quantity') VALUES (:id, :symbol, :price, :quantity)",
                    id=user[0]['id'], symbol=stock['symbol'], price=stock['price'], quantity=request.form.get('shares'));

        total_cost = stock['price'] * int(request.form.get('shares'))

        db.execute('UPDATE "users" SET cash=:cash WHERE id=:id',
                    id=user[0]['id'], cash=(user[0]['cash']-total_cost))

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    user = db.execute("SELECT * FROM users WHERE username = :username", username=request.args.get('username'))
    return jsonify(True if len(user) == 0 else False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    buys = db.execute("SELECT * FROM buys WHERE user_id = :id", id=session['user_id'])
    sells = db.execute("SELECT * FROM sells WHERE user_id = :id", id=session['user_id'])
    for buy in buys:
        buy['type'] = 'buy'
    for sell in sells:
        sell['type'] = 'sell'
    transactions = [*buys, *sells]

    def DTsort(a):
        return a['trans_date']

    transactions.sort(key=DTsort, reverse=True)

    return render_template("history.html", history=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        # their method
        # stock = lookup(request.form.get('symbol'))
        # if not stock:
        #     return apology("That stock does not exist")
        # return render_template("quoted.html", quotes=[stock])

        # my method
        quotes = [lookup(symbol) for symbol in request.form.getlist('stock[]')]
        return render_template("quoted.html", quotes=quotes)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # check username provided
        if not request.form.get('username'):
            return apology("You must provide a username")

        # check username not taken
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get('username'))
        if len(rows) != 0:
            return apology("This username is already taken")

        # check password provided
        if not request.form.get('password'):
            return apology("You must provide a password")

        # check password and confirm match
        if request.form.get('password') != request.form.get('confirmation'):
            return apology("Your passwords must match")

        db.execute("INSERT INTO 'users' ('id','username','hash') VALUES (NULL, :username, :hashed)",
                    username=request.form.get('username'),
                    hashed=generate_password_hash(request.form.get('password')))

        # check that registration happened
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get('username'))
        if len(rows) != 1:
            return apology("Oh no! something bad happend...")

        # log user in (from log in route)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        buys = db.execute("SELECT * FROM buys WHERE user_id = :id", id=session['user_id'])
        sells = db.execute("SELECT * FROM sells WHERE user_id = :id", id=session['user_id'])
        holdings = generate_holdings(buys, sells)
        return render_template('sell.html', holdings=holdings)

    else:
        # check for post
        if request.method == "POST":

            # check for symbol
            if not request.form.get("symbol"):
                return apology("You forgot to pick a stock")

            # check for shares
            if not request.form.get("shares"):
                return apology("You forgot to specify a quantity")

            # check if input is number
            if not request.form.get("shares").isdigit():
                return apology("You must specify a number")

             # check for shares
            if int(request.form.get("shares")) <= 0 or not isinstance(int(request.form.get("shares")), int):
                return apology("You must specify a positive whole number")

            # look up stock
            stock = lookup(request.form.get("symbol"))

            # check stock exists
            if not stock:
                return apology("That stock does not exist")

            buys = db.execute("SELECT * FROM buys WHERE user_id = :id AND symbol = :symbol", id=session['user_id'], symbol=request.form.get("symbol"))
            sells = db.execute("SELECT * FROM sells WHERE user_id = :id AND symbol = :symbol", id=session['user_id'], symbol=request.form.get("symbol"))
            holdings = generate_holdings(buys, sells)

            # check for user
            user = db.execute("SELECT * FROM users WHERE id = :id", id=session['user_id'])

            # check that we only have one user
            if len(user) != 1:
                return apology("Something bad happened, please try again", 403)

            # check user has more cash than stock costs
            if int(request.form.get("shares")) > holdings[0]['shares']:
                return apology("You do not own that many shares")

            shares = int(request.form.get("shares"))

            db.execute("INSERT INTO 'sells' ('user_id', 'symbol', 'price', 'quantity') VALUES (:id, :symbol, :price, :quantity)",
                        id=user[0]['id'], symbol=stock['symbol'], price=stock['price'], quantity=shares);

            total_profit = stock['price'] * shares

            db.execute('UPDATE "users" SET cash=:cash WHERE id=:id',
                        id=user[0]['id'], cash=(user[0]['cash']+total_profit))
            return redirect('/')

    return apology('something went wrong')


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
