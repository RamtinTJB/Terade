## Use Case Specification: Buy Assets
Version: 1.0

1. **Use Case Name: Buy Assets**
    * **Brief Description**
    
    The Buy Assets use case allows the player to purchase an asset by spending his/her available cash.
    * **Actor(s):** Player

2. **Flow of Events**
    * **Basic Flow**
        * The **Player** selects an asset to purchase from the main list.
        * The **Player** enters the number of tokens he/she wants to purchase
        * The **Player** is presented with all the information about the transaction (Total price, total token holding after purchase, date and time) and has to confirm by pressing **Enter**
        * The money is spent is reduced form the **Player's** spendable cash.
        * The purchased tokens are added to the **Player's** portfolio.
    * **Alternative Flows**
        * The **Player** may cancel the purchase in step 3 by pressing **ESC** instead of **Enter**; in which case the use case ends.
        
3. **Requirements**
    * **First Requirement:** The User must have sufficient funds available to purchase the indicated number of tokens from the selected asset.
    * **Second Requirement:** Internet connection is required for the program to pull the data from the CoinGecko API.
    
4. **Post-Conditions**
    * **First Post-Condition:** The sum of buy-price of the purchased token times the quantitiy purchased and fees and the available cash after the purchase, must equal the amount of cash available before the purchase. In other words, no money should be losst or created during the purchase.
    
5. **Extension Points**
    * **First Extension Point: Insufficient Funds** This extension is invoked if there are insufficient funds to purchase the indicated quantity of selected asset. In this case, the error is shown to the **Player** and he/she is prompted to enter a different quantity of choose a different asset.
    * **Second Extension Point: No Cash Available** This exetnsion point is invoked if the **Player** has no cash available. In this case, the user cannot purchase any assets.
