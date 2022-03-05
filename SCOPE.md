## Goal and Vision

Terade is a trading simulator inside the command line and its goal is to provide an opportunity the users to practice trading with close to real-life data.

## High Level Requirements

- Ability to trade different assets
- Ability to view the portfolio and the general trend of it using stats or charts

## Details 

After the user executes the program, she will see an ASCII art with two prompts asking for her username and password. They can also press Ctrl-R to register if they don't have an account yet. After successfully logging in, she will be presented with a prompt (`Terade >`), a list of top ten assets based on the applied filters, and a status bar at the bottom of the command line window. Using the left and right arrow keys, the user can scroll the list of assets and see the next/prev 10 assets.

Each item in the list of assets includes the following information (These pieces of data are obtained from the CoinGecko API):
	- Asset's tick (eg. BTC, ETH, ADA, ...)
	- Current price (eg. $1.45)
	- Precentage change of the price in the past 24 hours. The number will be shown in green or red depending on the price movement. If the price has increased in the past 24 hours, then the number will be shown in green. 
	- Precentage change of the price in the past 7 days.
	- Market Cap of the asset. This is calculated by multiplying the number of circulating coins by the price of each individual coin.

Status Bar:

	- The data in the list will be updated every T seconds and the status bar shows whether the program is pulling the data from the CoinGecko API or it is synced.
	- Filters that are applied to the list.
	- Total amount of cash that can be used to purchase assets.
	- Username

Commands that are supported by the program and are entered at the prompt (`Terade >`):

	- `help` or `h`
	- `filter`
	- `search`
	- `portfolio`
	- `buy`
	- `sell`

The details and the arguments that these commands take need to be completed in the future. All the commands accept a `-h` argument that displays the relevant informations about that command.

The portfolio page contains the list of user's holdings. At the top of the page, the total value of the portfolio in dollars is printed. Each entry in the portfolio contains the following information:
	
	- Asset's tick
	- Current price in dollars
	- Holdings (Both the number of the coins and their value in dollars `$1800  2000 ADA`)
	- Average buy price: this is calculated by dividing the number of tokens by the total amount of money paid in dollars to purchase them. This measurement shows if the user is in a profit or a loss with one specific asset.
	- Profit/Loss: either in dollars (eg. +$50) or in percentages (eg. -3.2%) 

## Deliverables

* Trading

	- Buy and sell assets
	- Historical price data
	- Display various information and stats about an asset
	- Market order and limit order

* Portfolio

	- Show profit and loss on each individual asset
	- Ability to create different portfolios
	- Convert the value of the portfolio to different currencies

* Connecting with the CoinGecko API to pull real time data about crypto currencies.

## Out of Scope

- Options trading
- Shorting stocks
- Leverage trading
- Candle chart
- Assets besides cryptocurrencies

## Milestones

- [ ] March 3rd: Final scope document and honors contract
- [ ] Narch 17th: UML Design / tools that will be used / cmake project structure
- [ ] March 31st: Final Design / Header files with documentation / some unit tests
- [ ] April 28th: Prototype demonstration
- [ ] May 24th: Final demonstration and class presentation
