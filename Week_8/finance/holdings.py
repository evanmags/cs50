from helpers import lookup

def generate_holdings(buys, sells):
    holdings = []
    def add_new_holding(trans):
        quote = lookup(trans['symbol'])
        holdings.append({
            'symbol': trans['symbol'],
            'company': quote['name'],
            'shares': trans['quantity'],
            'avg_cost': trans['price'],
            'cur_price': quote['price'],
            'value': quote['price'] * trans['quantity']
        })

    # loop through transactions
    for trans in buys:
        # if nothing in holdings, need to add first as a seed
        if len(holdings) > 0:

            # loop through holdings
            for index,stock in enumerate(holdings):

                # check if symbols match
                if stock['symbol'].upper() == trans['symbol'].upper():
                    stock['avg_cost'] = ((stock['avg_cost'] * stock['shares']) + (trans['price'] * trans['quantity'])) / (stock['shares'] + trans['quantity'])
                    stock['shares'] += trans['quantity']
                    stock['value'] = stock['cur_price'] * stock['shares']
                    break
                # check if last index
                elif index == len(holdings) - 1:
                    add_new_holding(trans)
                    break

        # add seed to holdings
        else:
            add_new_holding(trans)

    for trans in sells:
        for index,stock in enumerate(holdings):
            if stock['symbol'].upper() == trans['symbol'].upper():
                stock['shares'] -= trans['quantity']
                stock['value'] = stock['cur_price'] * stock['shares']
                if stock['shares'] <= 0:
                    holdings.pop(index)

    return holdings