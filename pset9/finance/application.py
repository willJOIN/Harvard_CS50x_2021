import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # No method defined, default is GET
    # Remember which user has logged in
    user_id = session["user_id"]
    # "?" is used to prevent SQL injections
    stocks = db.execute("SELECT name, SUM(shares) as totalShares, price, symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    # "[0][cash]" selects the value at key [0] from dict [cash]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total = cash
    for stock in stocks:
        total += stock["price"] * stock["totalShares"]
    # Renders and sends variables to HTML file
    return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if not symbol:
            # 400 Bad Request is user fault
            return apology("must provide symbol", 400)
        # Lookup function defined in helpers.py, returns a dict with stock info, stock = {'name': 'Apple Inc', 'price': 154.06, 'symbol': 'AAPL'}
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("number of shares needs to be a positive integer", 400)
        if not shares:
            return apology("must provide number of shares", 400)
        if shares <= 0:
            return apology("number of shares needs to be a positive integer", 400)
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        stock_name = stock["name"]
        stock_price = stock["price"]
        stock_symbol = stock["symbol"]
        total_price = stock_price * shares
        if cash < total_price:
            return apology("can't afford", 400)
        # Else request method is GET
        else:
            # Updates user cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
            # Updates user transactions
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, stock_name, shares, stock_price, "bought" , stock_symbol)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT shares, price, type, symbol, time FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol", 400)
        return render_template("quoted.html", stock=stock, usd=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide confirmation", 400)
        if password != confirmation:
            return apology("Passwords don't match", 400)
        # Hashes user password
        hash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect("/")
        except:
            return apology("Username already exists", 400)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("number of shares needs to be a positive integer", 400)
        if not shares:
            return apology("must provide number of shares", 400)
        if shares <= 0:
            return apology("number of shares needs to be a positive integer", 400)
        stock = lookup(symbol)
        stock_name = stock["name"]
        stock_price = stock["price"]
        stock_symbol = stock["symbol"]
        cash = shares * stock_price
        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]
        if shares_owned < shares:
            return apology("not enough shares", 400)
        cash_owned = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_owned + cash, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, stock_name, -shares, stock_price, "sold" , stock_symbol)
        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=symbols)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add cash"""
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    if request.method == "POST":
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + 200.0, user_id)
        return redirect("/")
    else:
        return render_template("add.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
