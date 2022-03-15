## Use Case Specification: Buy Assets

1. **Use Case Name: Buy Assets**
    * **Brief Description**
    The Buy Assets use case allows the player to purchase an asset by spending his/her available cash.
    * **Actor(s):** Player

2. **Preconditions**
	* The **Player** should have a cash balance of greater than zero to be able to purchase any assets.
	* Internet connection is required for the program to pull the data from the CoinGecko API.

3. **Flow of Events**
    * **Basic Flow**
        1. The **Player** selects an asset to purchase from the main list.
        2. The **Player** enters the number of tokens he/she wants to purchase. If current_price*token_quantity exceeds the **Player's** available cash balance, he/she is prompted to enter a smaller value.
        3. The **Player** is presented with all the information about the transaction (Total buy price, total token holdings after purchase, date and time) and has to confirm by pressing **Enter**
        4. The money spent is reduced from the **Player's** spendable cash.
        5. The purchased tokens are added to the **Player's** portfolio.
    * **Alternative Flows**
        * The **Player** may cancel the purchase in step 3 or step 2 by pressing **ESC** instead of **Enter**; in which case the use case ends.
        
4. **Post-Conditions**
    * **First Post-Condition:** The sum of buy-price of the purchased token times the quantitiy purchased and fees and the available cash after the purchase, must equal the amount of cash available before the purchase. In other words, no money should be losst or created during the purchase.

## Use Case Specification: Sell Assets

1. **Use Case Name: Sell Assets**
    * **Brief Description** 
    The Sell Assets use case allows the player to purchase an already purchased asset from his/her portfolio.
    * **Actor(s):** Player

2. **Preconditions**
    * The **Player's** portfolio value in dollars must be a greater than zero; in other words, he/she needs to have an asset to sell.
    * Internet connection is required.
    
3. **Flow of Events**
    * **Basic Flow**
        1. The **Player** selects an asset from his/her portfolio.
        2. The **Player** enters the quantity of the tokens he/she wishes to sell. If this number is less than zero or greater than the **Player's** current holdings of that particular asset, he/she is prompted to enter a value in the appropriate range.
        3. The **Player** is presented with all the information about the transaction (Total sell price, total token holdings after sell, date and time) and has to confirm by pressing **Enter**.
        4. The money earned by selling the tokens is added to the **Player's** available cash balance.
        5. The quantity of tokens sold is removed from **Player's** portfolio.
    * **Alternative Flows**
        * The **Player** may cancel the transaction in step 2 or step 3 by pressing **ESC** instead of **Enter**; in which case the use case ends.

4. **Post-conditions**
    * **First Post-Condition:** The sell_price*quantity_sold must be equal to the difference of the **player's** available cash balance before and after the transaction.

## Use Case Specification: Save

1. **Use Case Name: Save**
    * **Brief Description**
    The Save use case allows the **Player** to save the state of the game and freeze the game's clock so that he/she can continue playing at a later time.
    * **Actor(s):** Player

2. **Preconditions**
    * The available storage on **Player's** local hard drive must be greater than 0 bytes.

3. **Flow of Events**
    * **Basic Flow**
        1. The **Player** selects the **Save** option from the main screen.
        2. The **Player** enters the filename in which he/she wishes to save the game.
        3. If the file name is not valid or there is no input provided, the **Player** is prompted again to enter an appropriate value. 
        4. The state of the game is written to the filename specified by the **Player** with .terade as the file extension.
    * **Alternative Flows**
        * The **Player** may cancel the save operation in step 2 by pressing **ESC** instead of entering a value for the filename, in which case the use case ends.
        * If the game has already been saved or had been loaded from a file, it will be automatically saved in the same file instead of prompting the **Player** for a filename.
    
4. **Post-Conditions**
    * **First Post-Condition:** The state of the simulation must match that of the saved file after the save operation is performed.

## Use Case Specification: Load

1. **Use Case Name: Load**
    * **Brief Description**
    The Load use case allows the **Player** to load a previsouly saved state of the game and continue playing where he/she had left off.
    * **Actor(s):** Player

2. **Preconditions:** None

3. **Flow of Events**
    * **Basic Flow**
        1. Upon execution of the program, the **Player** can choose to load the game from a file instead of starting a new game.
        2. The **Player** enters the name of the file from which he/she wishes to load the game.
        3. If the **{filename}.terade** doesn't exist in the current working directory, the **Player** is asked to enter a valid filename.
        4. The game data and **Player's** portfolio and available cash balance is populated with the data in the **{filename}.terade**.
    * **Alternative Flows**
        * The **Player** may cancel the load operation in step 2 by pressing **ESC** instead of entering a filename, in which case a new game will start.
        
4. **Post-Conditions**
    * **First Post-Condition:** The state of the simulation must match that of the saved file after the load operation is performed.
    * **Second Post-Condition:** Further invokations of the save use case will automatically save the game to the same file from which the game had been loaded.
