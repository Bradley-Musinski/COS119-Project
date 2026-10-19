
# Milestone 3 – The Fallen Kingdom

Use this worksheet to plan the next phase of your project before you begin coding. Be clear, specific, and intentional—this will guide your development this week.

## 📌 Project Overview

Project Name:

→ The Fallen Kingdom

What does your program currently do? (1–3 sentences)

→ The Fallen Kingdom now features a working turn-based battle system with an initiative system inspired by D&D. Players can create characters, select classes, enter battles, and return to the SafeZone. The custom game engine also handles actor management, deferred destruction, dialogue, and input validation.

## 🔍 Current Progress Check

What is working right now?

→ The main menu, character creation, class selection, enemy creation, and battle sequence are functioning. The initiative system determines turn order, and the game loop allows players to transition between the SafeZone and battles without restarting the program.

What is NOT working or incomplete?

→ The inventory, item management, and store systems still need to be implemented. I also need to improve the user interface, fix existing bugs, and refine some gameplay mechanics.

What feels confusing or messy in your code?

→ The BattleSequence class feels a bit disorganized because it handles several combat-related functions. I want to improve its structure and make the code easier to read, maintain, and expand.

## 🚀 Feature Planning

### Feature 1

Name:

→ Inventory and Item System

What does this feature do?

→ Allows players to collect, store, and manage items such as weapons, armor, and potions. Players will also be able to use items during gameplay.

Why is this feature important?

→ Gives players more control over their characters and introduces resource management to the game.

### Feature 2

Name:

→ Store System

What does this feature do?

→ Allows players to purchase and sell items using in-game currency while visiting the SafeZone.

Why is this feature important?

→ Gives players a way to spend earned currency, obtain better equipment, and prepare for future battles.

### Feature 3 (optional)

Name:

→ UI Improvements and Bug Fixing

What does this feature do?

→ Improves menu layouts, dialogue formatting, and player feedback while addressing bugs in existing gameplay systems.

Why is this feature important?

→ Makes the game easier to navigate, improves readability, and helps ensure the existing systems function properly.

## 🧩 System Design Updates

Will you need to create any new classes? If so, which ones?

→ Yes, I plan to create classes or structs for Items, Inventory, and Store. These will handle item properties, inventory management, and buying or selling items.

Will you modify any existing classes? How?

→ Yes, I plan to update the Player class to support inventory and equipment. I will also modify the SafeZone to include the store and make improvements to the BattleSequence and game engine where necessary.

What data structures will you use (vectors, 2D vectors, etc.)?

→ I plan to use vectors to store inventory and store items. I will also use structs to organize item properties such as names, values, and effects.

## 🔄 Program Flow

Describe how a user interacts with your program:

1. Program starts → Displays the main menu where players can start a new game, view credits, or quit.
    
2. User chooses → Creates a character, selects a class, and enters the SafeZone.
    
3. Program responds → Allows players to enter battles, manage their inventory, and visit the store to buy or sell items.
    
4. Loop/next step → Players continue transitioning between the SafeZone and battles while collecting items and improving their characters.
    

## 🎯 Usability Improvements

How will you make your program easier to use this week?

- Clearer prompts:

→ Improve instructions and item descriptions so players understand their available options.

- Better error handling:

→ Handle invalid selections, prevent players from purchasing items without enough currency, and fix existing bugs.

- Improved menu/navigation:

→ Improve the UI formatting and make it easier to navigate between the SafeZone, inventory, store, and battles.

## ⚠️ Potential Challenges

What do you think will be the hardest part this week?

→ Making sure the inventory, item, and store systems work together properly without introducing bugs into the existing gameplay loop.

What is your plan if you get stuck?

→ Break the problem into smaller tasks, use debugging tools, research solutions, and test each system individually before connecting them.

## 📈 Level Up Goal

What skill are you focusing on improving this week?

→ Class design, object-oriented programming (OOP), and debugging.

What will you do to improve it?

→ Practice designing reusable classes, reducing unnecessary dependencies, and testing new features as I implement them. I also want to improve how I organize my code.

## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

- Create and implement the item system.
    
- Develop the player inventory and item management system.
    
- Implement the SafeZone store with buying and selling functionality.
    
- Improve UI formatting, navigation, and player feedback.
    
- Debug and refine existing gameplay systems.