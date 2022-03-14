## Use Case Specification: Buy Assets

1. **Use Case Name: Buy Assets**
    * **Brief Description**
    
    The Buy Assets use case allows the player to purchase an asset by spending his/her available cash.
    * **Actor(s):** Player

2. **Preconditions**
	* The user should have a cash balance of greater than zero to be able to purchase any assets.
	* Internet connection is required for the program to pull the data from the CoinGecko API.

3. **Flow of Events**
    * **Basic Flow**
        1 The **Player** selects an asset to purchase from the main list.
        2 The **Player** enters the number of tokens he/she wants to purchase. If current_price*token_quantity exceeds the **Player's** available cash balance, he/she is prompted to enter a smaller value.
        3 The **Player** is presented with all the information about the transaction (Total price, total token holdings after purchase, date and time) and has to confirm by pressing **Enter**
        4 The money spent is reduced from the **Player's** spendable cash.
        5 The purchased tokens are added to the **Player's** portfolio.
    * **Alternative Flows**
        * The **Player** may cancel the purchase in step 3 or step 2 by pressing **ESC** instead of **Enter**; in which case the use case ends.
        
4. **Post-Conditions**
    * **First Post-Condition:** The sum of buy-price of the purchased token times the quantitiy purchased and fees and the available cash after the purchase, must equal the amount of cash available before the purchase. In other words, no money should be losst or created during the purchase.
