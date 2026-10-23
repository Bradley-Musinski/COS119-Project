# Milestone 4 – The Fallen Kingdom

Use this worksheet to plan the next phase of your project before you begin coding. Be clear, specific, and intentional—this will guide your development this week.

## 📌 Project Overview

Project Name:

→ The Fallen Kingdom

What does your program currently do? (1–3 sentences)

→ The Fallen Kingdom is a turn-based RPG with a D&D-inspired initiative system, character creation, class selection, and a SafeZone town to return to between battles. Players can now collect and use items, buy Health Potions from the store, and save their progress to load it later from the main menu.

## 🔍 Current Progress Check

What is working right now?

→ The main menu, character creation, class selection, battles, inventory, store, and save/load system are all working. Players can buy Health Potions in town, use them during battle through the Bag, and their stats, leaderboard, gold, inventory, and abilities are saved to a file named after their character.

What is NOT working or incomplete?

→ Some abilities, like Rallying Cry and Armor of Agathys, only deal damage and don't apply their healing or armor yet. I'm still fixing small UI bugs, such as menus not clearing the right number of lines, and balancing the combat.

What feels confusing or messy in your code?

→ The BattleSequence class still handles a lot of different jobs (menus, targeting, abilities, and the Bag). Line clearing in the console is also easy to get wrong, because every menu has to know exactly how many lines it printed.

## 🚀 Feature Planning

### Feature 1

Name:

→ Save and Load System

What does this feature do?

→ Saves the player's stats, leaderboard, gold, inventory, and abilities to a text file in a SavedGames folder, named after the player. The Load Game menu lists every save, lets the player type the name to load it, and lets them go back to the main menu.

Why is this feature important?

→ Players can keep their progress between play sessions instead of starting over every time.

### Feature 2

Name:

→ Store and Using Items in Battle

What does this feature do?

→ The store in the SafeZone sells Health Potions for gold. During battle, players can open their Bag and use items, with stackable items showing how many they have and how much they restore.

Why is this feature important?

→ Gives players a reason to earn gold and adds strategy to battles by letting them heal when they need it.

### Feature 3 (optional)

Name:

→ UI Polish and Bug Fixing

What does this feature do?

→ Cleans up menus and dialogue, fixes input bugs that caused menus to print twice, adds class-specific dialogue for the Warlock and Soldier, and italicizes the narrator's lines.

Why is this feature important?

→ Makes the game easier to read and navigate, and makes it feel more polished and immersive.

## 🧩 System Design Updates

Will you need to create any new classes? If so, which ones?

→ Yes. I created a SaveSystem namespace for saving and loading, and a Store class for buying Health Potions.

Will you modify any existing classes? How?

→ Yes. I updated GameManager with a Load Game menu, GameSession to load a save file and reset the game loop when returning from the main menu, Inventory with a way to set gold, and BattleSequence to use items from the Bag.

What data structures will you use (vectors, 2D vectors, etc.)?

→ Vectors for the inventory, abilities, and the list of save files. Structs for item and ability data, and an enum for item types, which is saved to the file as a number.

## 🔄 Program Flow

Describe how a user interacts with your program:

1. Program starts → Displays the main menu where players can start a new game, load a game, or quit.
    
2. User chooses → Creates a new character and class, or picks a save file to continue.
    
3. Program responds → Sends the player to the SafeZone, where they can visit the store, then enter battles where they can attack, use abilities, or use items.
    
4. Loop/next step → Players move between the SafeZone and battles, saving their progress so they can return to the main menu and load it later.
    

## 🎯 Usability Improvements

How will you make your program easier to use this week?

- Clearer prompts:

→ The Load Game and store menus show clear options, item counts, and prices, and the save list shows player names instead of file names.

- Better error handling:

→ The game handles having no saves, typing a save name that doesn't exist, not having enough gold, a full bag, and bad input that used to make menus repeat.

- Improved menu/navigation:

→ Players can back out of the Load Game menu, the store, and the Bag at any time, and returning to the main menu now works correctly for both new and loaded games.

## ⚠️ Potential Challenges

What do you think will be the hardest part this week?

→ Getting saves to load back correctly. Items were being saved from the wrong list and missing data like stack counts, so everything had to be saved and loaded in the exact same order.

What is your plan if you get stuck?

→ Check the data instead of guessing: open the save file, add temporary debug prints, and compare what was saved to what the game shows.

## 📈 Level Up Goal

What skill are you focusing on improving this week?

→ File I/O and debugging.

What will you do to improve it?

→ Build the save system step by step, test each part (stats, inventory, abilities, gold) on its own, and use the save file and debug prints to find where things go wrong.

## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

- Create the SaveSystem namespace to save and load player data.
    
- Add a Load Game menu that lists save files and lets the player go back.
    
- Implement the store for buying Health Potions.
    
- Let players use items from the Bag during battle.
    
- Fix the game loop not restarting after returning to the main menu.
    
- Fix battle menu input and line-clearing bugs.
    
- Add class dialogue and polish the UI.