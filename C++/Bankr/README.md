## Bankr

Bankr is an all-in-one banking app built for ease-of-use. Features data crude data saving methods.

---
## Usage

**Main Menu:**
- `1` Opens the Account if you are logged in or an account is found. Otherwise, starts account creation.
- `2` Opens the settings menu.

---
**Account Menu:**
- `1` allows you to deposit money into your account.
- `2` allows you to withdraw money from your account.
- `3` lists out all your account details. (eg. name, dob, balance)
- `4` pulls all records from `history.txt` and lets you see them.
- `5` purges the `history.txt` file entirely. (irreversible)

---
**Settings Menu:**
- `1` lets you change your name.
- `2` lets you change your password.
- `3` lets you change your dob.
- `4` logs you out of your account.
- `5` deletes your account entirely. (irreversible)
- `6` toggles debug. Debug also prints `log.txt` entries into the console under the [DEBUG] prefix.
- `7` applies your interest rate to your current balance.
- `8` generates a new interest rate between 2% and 4%. 

## Compiling

This project has a small increase in complexity with multiple classes needing to also be compiled:

```bash
g++ Bankr.cpp Account.cpp Logger.cpp -o Bankr
```

## Logger

This project also includes a logger. Accessible inside the data folder under `log.txt`. It logs every actions under the prefix of either [INFO], [WARN] or [ERROR].

- `[ERROR]` indicates a massive issue resulting in highly reduced functionality.
- `[WARN]` indicates a possible issue, sometimes results in reduced functionality.
- `[INFO]` is general information, useful to make sure certain events actually happen.

---
## Patch Notes

**16/03/26|Prototype**
- Initial Prototype version, has basic withdraw and deposit functionality.
- Keeps track of banking history with second-precision timestamps.

---
**27/03/26|V0.1**
- An improved version. Has functionality for changing everything associated with your account (eg. name, password, date of birth). 
- Has logout and account deletion functionality. 
- Started debug implementation, not actually functioning yet though.

---
**05/04/26|V0.2**
- An upgraded data handling system where the account and history is stored respectively on seperate .txt files. This allows for data to carry over instead of being lost upon closing the .exe file
- Plans to also add a "config.txt" file, where the settings are saved, are in the works, but will not be realised until much later into the project.
- Small work towards implementing proper debugging. All console debug prints start with the prefix "[DEBUG]".

---
**10/04/26|V0.4**
- Even better data handling system. Account.txt now also says what the line is meant to contain. eg: "name=bloo".
- Added a config.txt file where settings are stored. Currently only stores the debug setting. Uses versions to make sure that if you're loading a file from version 1, but the data loader function is, lest say version 5 for example, you don't start looking for data that doesnt exist.
- Small code cleanup to hopefully look more readable and be more closely aligned with OOP related best practices.
- Loading an Account from a file will now prompt the user to log in again instead of being already logged in. Better security? Yeah idk.

---
**18/04/26|V0.6**
- Implemented new logging system.
- Changed file structures so that account and logger have their own folder. Moved the .txt files into their own data folder.
- Small code cleanup and implementing forgotten file.is_open() checks.
- Comeplete code restructure. Every class now has its own .h and .cpp file. Bankr.cpp now just includes the .h files instead of containign the implementation alltogether.
- Project renamed to "Bankr" (sounds cool idk).

---
## Personal Note

Bankr, like my previous projects, follows the increase in complexity. File handling and data saving, also logging. Pretty cool but mostlikely not well made. Let me know how I could improve this project.
