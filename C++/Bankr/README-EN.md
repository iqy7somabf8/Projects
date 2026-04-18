## Bank.cpp Documentation
    This README server to give you some insight, as to how you can navigate and understand Bank's menu.

## Tutorial
    The whole "app" is comprised of 3 different menus. First one allows you to choose wether you want to open the Account menu or the Settings menu.
    In the Account menu you can deposit, withdraw, check your account details, check your banking history, and delete your banking history.
    In the Settings menu you can change everything to do with your account, like for example, your name, password, and date of birth. You can also log out of your account and delete your account.

## Patch Notes

    Quick preface: I have negative clue how versioning works lol, I'm just typing in whatever I like. 

    16/03/26|Prototype
    -Initial Prototype version, has basic withdraw and deposit functionality.
    -Keeps track of banking history with second-precision timestamps.

    27/03/26|V0.1
    -An improved version. Has functionality for changing everything associated with your account (eg. name, password, date of birth). 
    -Has logout and account deletion functionality. 
    -Started debug implementation, not actually functioning yet though.

    05/04/26|V0.2
    -An upgraded data handling system where the account and history is stored respectively on seperate .txt files. This allows for data to carry over instead of being lost upon closing the .exe file
    -Plans to also add a "config.txt" file, where the settings are saved, are in the works, but will not be realised until much later into the project.
    -Small work towards implementing proper debugging. All console debug prints start with the prefix "[DEBUG]".

    10/04/26|V0.4
    -Even better data handling system. Account.txt now also says what the line is meant to contain. eg: "name=bloo".
    -Added a config.txt file where settings are stored. Currently only stores the debug setting. Uses versions to make sure that if you're loading a file from version 1, but the data loader function is, lest say version 5 for example, you don't start looking for data that doesnt exist.
    -Small code cleanup to hopefully look more readable and be more closely aligned with OOP related best practices.
    -Loading an Account from a file will now prompt the user to log in again instead of being already logged in. Better security? Yeah idk.

    18/04/26|V0.6
    -Implemented new logging system.
    -Changed file structures so that account and logger have their own folder. Moved the .txt files into their own data folder.
    -Small code cleanup and implementing forgotten file.is_open() checks.
    -Comeplete code restructure. Every class now has its own .h and .cpp file. Bankr.cpp now just includes the .h files instead of containign the implementation alltogether.
    -Project renamed to "Bankr" (sounds cool idk).